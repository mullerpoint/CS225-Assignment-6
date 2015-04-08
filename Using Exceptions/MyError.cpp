#include <exception>
#include "MyError.hpp"

MyError::MyError()
{

}

MyError::MyError(MyError::ERRTYPE errorType = You)
{
	
	switch (errorType)
	{
	case MyError::You:
		break;
	case MyError::don:
		break;
	case MyError::messd:
		break;
	case MyError::up:
		break;
	default:
		break;
	}
}


MyError::~MyError()
{
}
