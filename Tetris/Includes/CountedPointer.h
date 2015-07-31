#ifndef _COUNTEDPOINTER_H_
#define _COUNTEDPOINTER_H_


template<class _T>
class CountedPointer
{
public:

	CountedPointer(_T* Ptr = 0) : _Ptr(0), _Counter(0)
	{
		*this = Ptr;
	}


  CountedPointer(const CountedPointer<_T>& rh) : _Ptr(0), _Counter(0)
	{
		*this = rh;
	}


~CountedPointer()
	{
		Release();
	}


	CountedPointer<_T>& operator=(_T* Ptr)
	{
		Release();
		if (Ptr)
		{
			_Ptr = Ptr;
			_Counter = new int(1);
		}
		return *this;
	}


	CountedPointer<_T>& operator=(const CountedPointer<_T>& rh)
	{
		if (this != &rh)
		{
			Release();
			_Ptr = rh._Ptr;
			_Counter = rh._Counter;
			++*_Counter;
		}
		return *this;
	}


	_T* operator->() const
	{
		return _Ptr;
	}


	_T& operator*() const
	{
		return *_Ptr;
	}


	operator _T*() const
	{
		return _Ptr;
	}

protected:

	void Release()
	{
		if (_Counter && --*_Counter == 0)
		{
			if (_Ptr != 0) delete _Ptr;
			delete _Counter;
			_Ptr = 0;
			_Counter = 0;
		}
	}

private:

	_T*			_Ptr;
	int*		_Counter;
};

#endif
