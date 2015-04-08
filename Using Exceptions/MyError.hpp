#include <iostream>
#include <stdexcept>

class MyError :
	public std::runtime_error
{
public:
	enum ERRTYPE{
		You, don, messd, up
	};
	
	MyError(MyError::ERRTYPE);
	virtual ~MyError();
};

