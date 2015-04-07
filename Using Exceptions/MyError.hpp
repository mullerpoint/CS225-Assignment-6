#include <iostream>
#include <stdexcept>

class MyError :
	public std::runtime_error
{
public:
	MyError();
	virtual ~MyError();
};

