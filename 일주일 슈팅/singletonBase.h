#pragma once

template<class T>
class singletonBase
{
protected:
	static T* _single;
public:
	singletonBase() {}
	virtual ~singletonBase() {}

	inline static T* getSingleton()
	{
		if (!_single) _single = new T;
		return _single;
	}
	inline void releaseSingleton()
	{
		if (_single)
		{
			delete _single;
			_single = nullptr;
		}
	}

};

template<class T>
T* singletonBase<T>::_single = 0;