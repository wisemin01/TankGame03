#pragma once

template <class T>
class Singleton
{
private:
	static T* pInst;

public:
	Singleton() {}
	virtual ~Singleton() {}

	static T& GetInstance()
	{
		if (!pInst)
		{
			pInst = new T;
		}
		return *pInst;
	}

	static void ReleaseInstance()
	{
		if (pInst) {
			delete pInst;
			pInst = nullptr;
		}
	}
};

template <class T>
T* Singleton<T>::pInst = nullptr;