
#include "Func.h"
#include <regex>
#include "cocostudio/CocoStudio.h"
using namespace cocostudio;

namespace func{

	std::string getValueStrBySplit(int num, int dividend, std::string split)
	{
		std::string str = "";
		while (num >= dividend){
			str += Value(num / dividend).asString() + split;
			num = num % dividend;
		}
		str += Value(num).asString();
		return str;
	}

	long getCurrentTime()
	{
		struct timeval tv;
		gettimeofday(&tv, NULL);
		return tv.tv_sec * 1000 + tv.tv_usec / 1000;
	}

	int getTodayId()
	{
		time_t now_time = time(NULL);
		return  localtime(&now_time)->tm_mday;
	}

	int getMonthDays()
	{
		time_t now_time = time(NULL);
		tm* tTm = localtime(&now_time);
		int y = tTm->tm_year;
		int m = tTm->tm_mon+1;

		return getMaxDaysByYearAndMonth(y, m);
	}

	int getMaxDaysByYearAndMonth(int y, int m)
	{
		int days = 0;
		switch (m)
		{
		case 1:case 3:case 5:case 7:case 8:case 10:case 12:
			days = 31;
			break;
		case 4:case 6:case 9:case 11:
			days = 30;
			break;
		case 2:
			if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)
				days = 29;
			else
				days = 28;
			break;
		}
		return days;
	}

    void randomArray(int* temp, int num)
	{
		for (int i = 0; i< num; i++) temp[i] = i;
		for (int i = num; i > 0; i--)
		{
			int n = rand() % i;
			std::swap(temp[i - 1], temp[n]);
		}
	}

	int* randomArray(int num)
	{
		int* temp = new int[num];
		for (int i = 0; i< num; i++) temp[i] = i;
		for (int i = num; i > 0; i--)
		{
			int n = rand() % i;
			std::swap(temp[i - 1], temp[n]);
		}
		return temp;
	}

	Color4F getPixelColor(const Vec2& mPos)
	{
		auto glView = Director::getInstance()->getOpenGLView();

		auto designSize = glView->getDesignResolutionSize();
		if (mPos.x < 0 || mPos.x >= designSize.width || mPos.y < 0 || mPos.y >= designSize.height)
			return Color4F::WHITE;


		auto frameSize = glView->getFrameSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		frameSize = frameSize * glView->getFrameZoomFactor() * glView->getRetinaFactor();
#endif
		int t_x = mPos.x*frameSize.width / designSize.width;
		int t_y = mPos.y*frameSize.height / designSize.height;

		GLubyte bits[4] = { 0, 0, 0, 0 };
		glReadPixels(t_x, t_y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &bits);
		return Color4F(bits[0], bits[1], bits[2], bits[3]);
	}

	void afterSomeTimeToDo(Node* node, float time, const std::function<void()> &func){
		if (node&&func)
			node->runAction(Sequence::create(DelayTime::create(time),
			CallFunc::create(func), NULL));
	}

	void afterSomeTimeToDo(float time, const std::function<void()> &func)
	{
		auto node = Director::getInstance()->getRunningScene();
		if (node&&func)
			node->runAction(Sequence::create(DelayTime::create(time),
			CallFunc::create(func), NULL));
	}

	void addTouchSwallow(Node* node)
	{
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(true);
		listener->onTouchBegan = [](Touch *pTouch, Event *pEvent){
			return true;
		};
		Director::getInstance()->getEventDispatcher()
			->addEventListenerWithSceneGraphPriority(listener, node);
	}

	Texture2D* getScreenTexture(Node* parent)
	{
		auto size = Director::getInstance()->getWinSize();
		RenderTexture *rendertex = RenderTexture::create(size.width, size.height);
		rendertex->setAutoDraw(true);
		rendertex->begin();
		parent->visit();
		rendertex->end();
		return rendertex->getSprite()->getTexture();
	}
	Texture2D* getScreenTexture(const Vector<Node*>& nodeVec)
	{
		auto size = Director::getInstance()->getWinSize();
		RenderTexture *rendertex = RenderTexture::create(size.width, size.height);
		rendertex->setAutoDraw(false);
		rendertex->begin();
		for (auto node : nodeVec)
			node->visit();
		rendertex->end();
		return rendertex->getSprite()->getTexture();
	}

	int PointAtLineLeftRight(Vec2 ptStart, Vec2 ptEnd, Vec2 ptTest)
	{
		ptStart.x -= ptTest.x;
		ptStart.y -= ptTest.y;
		ptEnd.x -= ptTest.x;
		ptEnd.y -= ptTest.y;

		int nRet = ptStart.x * ptEnd.y - ptStart.y * ptEnd.x;
		if (nRet == 0)
			return 0;
		else if (nRet > 0)
			return 1;
		else if (nRet < 0)
			return -1;

		return 0;
	}

	// ≈–∂œ¡ΩÃıœﬂ∂Œ «∑Òœ‡Ωª
	bool IsTwoLineIntersect(const Vec2& ptLine1Start, const Vec2& ptLine1End, const Vec2& ptLine2Start, const Vec2& ptLine2End)
	{
		int nLine1Start = PointAtLineLeftRight(ptLine2Start, ptLine2End, ptLine1Start);
		int nLine1End = PointAtLineLeftRight(ptLine2Start, ptLine2End, ptLine1End);
		if (nLine1Start * nLine1End > 0)
			return false;

		int nLine2Start = PointAtLineLeftRight(ptLine1Start, ptLine1End, ptLine2Start);
		int nLine2End = PointAtLineLeftRight(ptLine1Start, ptLine1End, ptLine2End);

		if (nLine2Start * nLine2End > 0)
			return false;

		return true;
	}

	//≈–∂œœﬂ∂Œ «∑Ò”Îæÿ–Œœ‡Ωª
	bool IsLineIntersectRect(const Vec2& ptStart, const Vec2& ptEnd, const Rect& rect)
	{
		// Two point both are in rect
		if (rect.containsPoint(ptStart) && rect.containsPoint(ptEnd))
			return true;

		// One point is in rect, another not.
		if (rect.containsPoint(ptStart) && !rect.containsPoint(ptEnd))
			return true;
		if (!rect.containsPoint(ptStart) && rect.containsPoint(ptEnd))
			return true;

		// Two point both aren't in rect
		if (IsTwoLineIntersect(ptStart, ptEnd, Vec2(rect.getMinX(), rect.getMaxY()), Vec2(rect.getMinX(), rect.getMinY())))
			return true;
		if (IsTwoLineIntersect(ptStart, ptEnd, Vec2(rect.getMinX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMinY())))
			return true;
		if (IsTwoLineIntersect(ptStart, ptEnd, Vec2(rect.getMaxX(), rect.getMinY()), Vec2(rect.getMaxX(), rect.getMaxY())))
			return true;
		if (IsTwoLineIntersect(ptStart, ptEnd, Vec2(rect.getMinX(), rect.getMaxY()), Vec2(rect.getMaxX(), rect.getMaxY())))
			return true;

		return false;
	}

	Node* seekNodeByTag(Node* root, int tag){
		if (!root)
		{
			return nullptr;
		}
		if (root->getTag() == tag)
		{
			return root;
		}
		const auto& arrayRootChildren = root->getChildren();
		ssize_t length = arrayRootChildren.size();
		for (ssize_t i = 0; i<length; i++)
		{
			Node* child = dynamic_cast<Node*>(arrayRootChildren.at(i));
			if (child)
			{
				Node* res = seekNodeByTag(child, tag);
				if (res != nullptr)
				{
					return res;
				}
			}
		}
		return nullptr;
	}
    
    //rootNode , "scrollView"
    //backGroud, "scrollView"
    //sp,        "scrollView"
    //scrollview "scrollView"
    
	Node* seekNodeByName(Node* root, const std::string& name)
	{
        //首先判断是否空
		if (!root)
		{
			return nullptr;
		}
        //是否是本身
		if (root->getName() == name)
		{
			return root;
		}
        
        //获取node下面的子类
        //第二次子类为空
        //第三次子类（4个）
		const auto& arrayRootChildren = root->getChildren();
        
        
		for (auto& subWidget : arrayRootChildren)
		{
            //第一次循环是背景图background
            //sp
            //scroview
			Node* child = dynamic_cast<Node*>(subWidget);
            
			if (child)
			{
				Node* res = seekNodeByName(child, name);
				if (res != nullptr)
				{
					return res;
				}
			}
		}
		return nullptr;
	}

	Vec2 getNodeWorldPos(Node* node){
		return node->getParent()->convertToWorldSpace(node->getPosition());
		//return node->convertToWorldSpace(Vec2::ZERO);
	}


#pragma region ’˝‘Ú±Ì¥Ô Ω
	// ≈–∂œ ‰»Îµƒ◊÷∑˚¥Æ÷ª∞¸∫¨∫∫◊÷
	bool IsChineseCh(const std::string& input){
		const std::regex pattern("^[\\u4e00-\\u9fa5]+$");
		return std::regex_match(input, pattern);
	}


	bool IsEmail(const std::string& input)
	{
		const std::regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
		return std::regex_match(input, pattern);
	}

	bool IsPhone(const std::string& input)
	{
		//const std::regex pattern("^\\(0\\d{2}\\)[- ]?\\d{8}$|^0\\d{2}[- ]?\\d{8}$|^\\(0\\d{3}\\)[- ]?\\d{7}$|^0\\d{3}[- ]?\\d{7}$");
		const std::regex pattern("^[1][358][0-9]{9}$");
		return std::regex_match(input, pattern);
	}

	
	bool IsVerification(const std::string& input)
	{
		const std::regex pattern("[0-9]{5}");
		return std::regex_match(input, pattern);
	}

	
	bool Is6To18Pwd(const std::string& input)
	{
		const std::regex pattern("^.{6,18}");
		//const std::regex pattern("^[a-zA-Z0-9]{6,18}");
		return std::regex_match(input, pattern);
	}

	bool IsOnlyNumeric(const std::string& input)
	{
		const std::regex pattern("[0-9]+");
		return std::regex_match(input, pattern);
	}
    
	void SetAllTextChildDefaultFont(Node* root){
		if (!root)
			return;
		const auto& arrayRootChildren = root->getChildren();
		ssize_t length = arrayRootChildren.size();
		for (ssize_t i = 0; i<length; i++){
			auto child = dynamic_cast<ui::Text*>(arrayRootChildren.at(i));
			if (child){
				//auto label =dynamic_cast<Label*>(child->getVirtualRenderer());
				//label->setSystemFontName(FONT_DEFAULT);
				//label->requestSystemFontRefresh()
				SetAllTextChildDefaultFont(child);
			}

		}
	}

	void addGlobalClickEvent(Node* pParent, const std::function<void()>& func, int nTag){
		auto layer = Layer::create();
		pParent->addChild(layer, nTag);
		auto listener = EventListenerTouchOneByOne::create();
		listener->setSwallowTouches(false);
		listener->onTouchBegan = [=](Touch *pTouch, Event *pEvent){
			if (func)
				func();
			return false;
		};
		Director::getInstance()->getEventDispatcher()
			->addEventListenerWithSceneGraphPriority(listener, layer);
	}

	void ScaleToMatchHeight(Node* pNode, float height)	{
		pNode->setScale(height / pNode->getContentSize().height);
	}

	void ScaleToMatchAdapt(Node* pNode, float width, float height)
	{
		pNode->setScale(MIN(width / pNode->getContentSize().width,height / pNode->getContentSize().height));
	}

	void ScaleToMatchFill(Node* pNode, float width, float height)	
	{
		pNode->setScale(MAX(width / pNode->getContentSize().width, height / pNode->getContentSize().height));
	}

	void ScaleToMatchStretch(Node* pNode, float width, float height)	
	{
		pNode->setScaleX(width / pNode->getContentSize().width);
		pNode->setScaleY(height / pNode->getContentSize().height);
	}

	void setParentTouchEnableAndColor(ui::ImageView* btn, bool bEnable)
	{
		btn->getParent()->setCascadeColorEnabled(true);
		if (bEnable)
			btn->getParent()->setColor(Color3B::WHITE);
		else
			btn->getParent()->setColor(Color3B::GRAY);

		btn->setTouchEnabled(bEnable);

	}
};


