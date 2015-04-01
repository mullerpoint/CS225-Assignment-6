#include <iostream>
#include <exception>

class MyError :
	public std::exception
{
public:
	MyError();
	virtual ~MyError();
};

