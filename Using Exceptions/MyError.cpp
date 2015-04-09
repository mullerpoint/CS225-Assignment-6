//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// MyError Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MYERROR_CLASS_IMPL_H_
#define MYERROR_CLASS_IMPL_H_

//Header files standard libraries and classes
#ifndef MEDIA_DEPENDENCIES_CORE_H_
#define MEDIA_DEPENDENCIES_CORE_H_
#include <iostream> //default include
#include <string> // included to get strings to work
#include <locale> // included to get locale info for output
#include <io.h> // isatty for windows
//#include <unistd.h> // isatty  for linux
#include <iomanip> // included to make pretty output
#include <typeinfo> //included to use typeid()
#include <list> //included for use of list template
#include <vector> //included for use of vector template
#include <algorithm> //included to use sort()
#include <stdexcept> // include to derive from runtime_error
#endif

// Include header file
#include "MyError.hpp"


//Constructor
MyError::MyError(MyError::ERRTYPE Error)
	: runtime_error(getTypeStr(Error))
{
	Error_ = Error;
}

//Implicit Destructor used



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Accessors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//get Error Enum Type
MyError::ERRTYPE MyError::getType()
{
	return MyError::Error_;
}

//get Error type as a string
std::string MyError::getTypeStr(MyError::ERRTYPE Type)
{
	switch (Type)
	{
	case MyError::NOT_EXIST:
		return "The Item Does Not Exist";
		break;
	case MyError::OUT_OF_BOUNDS:
		return "Value Out of Bounds";
		break;
	case MyError::WRONG_CLASS:
		return "Selected Item is of Wrong Class";
		break;
	case MyError::UNK_ERROR:
		return "";
		break;
	default:
		break;
	}
}

#endif