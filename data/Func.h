#ifndef  __FUNC_H__
#define  __FUNC_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

namespace func
{
	//搜索ui控件
	Node* seekNodeByTag(Node* root, int tag);
	Node* seekNodeByName(Node* root, const std::string& name);
	Vec2 getNodeWorldPos(Node* node);	//获取节点世界坐标

	std::string getValueStrBySplit(int num,int dividend =1000,std::string split ="/");
	Color4F getPixelColor(const Vec2& mPos);
	void afterSomeTimeToDo(Node* node, float time, const std::function<void()> &func);
	void afterSomeTimeToDo(float time, const std::function<void()> &func);	//以当前页面作为定时器场景

	void addTouchSwallow(Node* node);
	Texture2D* getScreenTexture(Node* parent); 	//要绘制的父节点,该方法同时绘制父节点下的子节点，需保证要绘制的节点都在该父节点上且只有要绘制的才在
	Texture2D* getScreenTexture(const Vector<Node*>& nodeVec);

	/*****************************************************************
	* 时间相关函数
	*********************************************/	
	long getCurrentTime();
	int getTodayId();		//获取当天天数
	int getMonthDays();		//获取该月天数
	int getMaxDaysByYearAndMonth(int y, int m);

	//获取标准格式的日期，用-分隔年月日
	std::string getFormatData(long t, const std::string& split = "-");

	//获得获得输入时间到当前时间间隔的分钟数，两个都是UTC时间
	long getUTCMinuteToCurr(long t);


	//获取随机数组
	void randomArray(int* temp, int num);
	int* randomArray(int num); //返回0~num-1的一串无序数组

	//线段是否与矩形相交
	int PointAtLineLeftRight(Vec2 ptStart, Vec2 ptEnd, Vec2 ptTest);
	bool IsTwoLineIntersect(const Vec2& ptLine1Start, const Vec2& ptLine1End, const Vec2& ptLine2Start, const Vec2& ptLine2End);
	bool IsLineIntersectRect(const Vec2& ptStart, const Vec2& ptEnd, const Rect& rect);

	//模板函数，获取随机对象
	template <typename T>
	T getRandomObject(const std::vector<T>& _data)
	{
		//if (!_data.empty())
		//{
		ssize_t randIdx = rand() % _data.size();
		return *(_data.begin() + randIdx);
		//}
		//return nullptr;
	};
	template <typename T>
	int getRandomIndex(const std::vector<T>& _data)
	{
		if (!_data.empty())
		{
			ssize_t randIdx = rand() % _data.size();
			return randIdx;
		}
		return 0;
	};
	template <typename T,int size>
	T getRandomType(const std::pair<T, int>(&_array)[size])
	{
		//int size = sizeof(_array) / sizeof(_array[0]);
		int allRateNum = 0;
		int chooseInd = 0;

		for (int i = 0; i < size; i++){
			allRateNum += _array[i].second;
		}
		int randNum = rand() % allRateNum;
		for (int i = 0; i < size; i++){
			allRateNum -= _array[i].second;
			if (allRateNum <= randNum){
				chooseInd = i;
				break;
			}
		}
		return _array[chooseInd].first;
	}
	template <typename T>
	T getRandomType(const std::vector<std::pair<T, int>> &_vector)
	{
		int allRateNum = 0;
		T chooseInd;
		for (auto key : _vector)
			allRateNum += key.second;
		int randNum = rand() % allRateNum;

		for (auto key : _vector){
			allRateNum -= key.second;
			if (allRateNum <= randNum){
				chooseInd = key.first;
				break;
			}
		}
		return chooseInd;
	}
	template <typename T>
	T randomType(std::vector<T> mTotal, std::vector<T> mRemove)
	{
		std::vector<T> restType;
		for (auto needType : mTotal)
		{
			bool flag = true;
			for (auto removeType : mRemove){
				if (needType == removeType){
					flag = false;
				}
			}
			if (flag){
				restType.push_back(needType);
			}
		}

		int restSize = restType.size();
		int randomIndex = rand() % restSize;
		return restType.at(randomIndex);
	}
	template <typename T>
	void randomsort(std::vector<T>& _data)
	{
		std::vector<T> restType = _data;
		int* _randomArray = func::randomArray(restType.size());
		_data.clear();
		for (int i = 0; i < restType.size(); i++){
			_data.push_back(restType.at(_randomArray[i]));
		}
		CC_SAFE_DELETE(_randomArray);
	}
	//void randomsort(ValueVector& _data)
	//{
	//	ValueVector restType = _data;
	//	int* _randomArray = func::randomArray(restType.size());
	//	_data.clear();
	//	for (int i = 0; i < restType.size(); i++){
	//		_data.push_back(restType.at(_randomArray[i]));
	//	}
	//	CC_SAFE_DELETE(_randomArray);
	//}

	//清理list列表内容
	template <typename T>
	void cleanList(std::list<T*>& _data)
	{
		for (T* item : _data)	{
			CC_SAFE_DELETE(item);
		}
		_data.clear();
	};

	//数组拷贝
	template <typename T>
	void ArrayCopy(T* src, T*desc, int arrayNum)
	{
		for (int i = 0; i < arrayNum; i++){
			desc[i] = src[i];
		}
	}


	////////////////////////////////////////////////////////////
	//正则表达式
	bool IsChineseCh(const std::string& input);

	bool IsEmail(const std::string& input);

	//手机号判断
	bool IsPhone(const std::string& input);

	//验证码判断（5位有效数字）
	bool IsVerification(const std::string& input);

	bool Is6To18Pwd(const std::string& input);

	//是否是纯数字（没有负号）
	bool IsOnlyNumeric(const std::string& input);

	//获取描述Desc文本
	std::string GetDescHintText(const std::string& szKey);

	//获取美术字文本
	std::string GetMSZHintText(const std::string& szKey);

	//根据key显示提示信息
	void ShowDescHintText(const std::string& szKey);

	//根据key显示提示信息
	void ToastDescHintText(const std::string& szKey);

	//显示提示的内容
	void ShowBoxHint(const std::string& szMsg);

	//显示提示的内容
	void ShowToastHint(const std::string& szMsg);


	std::string GetImagePath(const char* szKey);

	//设置默认字体
	void SetTextDefaultFont(Node* nFather,const std::string& textname);

	//设置所有Text节点的字体为默认字体
	void SetAllTextChildDefaultFont(Node* root);


	//添加全局点击事件，即在点击屏幕前优先触发的事件
	void addGlobalClickEvent(Node* pParent, const std::function<void()>& func, int nTag = 99);

	//进行缩放，使其最大高度为height
	void ScaleToMatchHeight(Node* pNode, float height);

	//图片等适应模式（有黑边）
	void ScaleToMatchAdapt(Node* pNode, float width,float height);

	//图片等填充模式（无黑边）
	void ScaleToMatchFill(Node* pNode, float width, float height);

	//图片等拉伸模式
	void ScaleToMatchStretch(Node* pNode, float width, float height);

	//预加载所有Plist文件
	void PreLoadAllPlist();

	//显示在左上角的版本号信息
	Node* GetVersionNode();

	////手机号绑定成功的提示
	//void BindPhoneSucceedHint();

	//按钮点击效果,点击效果在其父节点
	void setBtnParentTouchEffect(ui::ImageView* btn, const std::function<void()>& func =nullptr);

	//设置按钮是否允许点击,设置父节点通用颜色为灰色
	void setParentTouchEnableAndColor(ui::ImageView* btn, bool bEnable);
};

#endif
