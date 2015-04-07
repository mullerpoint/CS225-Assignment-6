#include <exception>
#include "MyError.hpp"


MyError::MyError(MyError::ERRTYPE)
{
	switch (ERRTYPE)
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
