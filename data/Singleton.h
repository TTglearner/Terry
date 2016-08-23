#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <assert.h>

template <typename T> class Singleton
{
private:
	/** \brief Explicit private copy constructor. This is a forbidden operation.*/
	Singleton(const Singleton<T> &);

	/** \brief Private operator= . This is a forbidden operation. */
	Singleton& operator=(const Singleton<T> &);

protected:

	static T* msSingleton;

public:
	Singleton(void)
	{
		assert(!msSingleton);
#if defined( _MSC_VER ) && _MSC_VER < 1200	 
		int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
		msSingleton = (T*)((int)this + offset);
#else
		msSingleton = static_cast<T*>(this);
#endif
	}
	~Singleton(void)
	{
		assert(msSingleton);

		msSingleton = 0;
	}

	static T* getInstance(void){

		if (!msSingleton)
		{
			msSingleton = new T;
			//msSingleton->init();
		}
		return msSingleton;
	}

	static void clean(void){
		auto ref = T::getInstance();
		CC_SAFE_DELETE(ref);
	}

	static T& getSingleton(void)
	{
		assert(msSingleton);
		return (*msSingleton);
	}

	static T* getSingletonPtr(void)
	{
		return msSingleton;
	}

//protected:
//	virtual void init(){};
};

template <typename T> T *Singleton<T>::msSingleton = 0;
#endif
