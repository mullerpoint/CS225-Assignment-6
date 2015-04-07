#include <exception>
#include "MyError.hpp"


MyError::MyError()
	: runtime_error("Error in Input")
{
}


MyError::~MyError()
{
}
