//
// MyError Class Implementation
//

#ifndef MYERROR_CLASS_DEF_H_
#define MYERROR_CLASS_DEF_H_

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
#include <stdexecpt>
#endif


class MyError :
	public std::runtime_error
{
public:
	enum ERRTYPE{
		NOT_EXIST, OUT_OF_BOUNDS, WRONG_CLASS, UNK_ERROR
	};
private:
	ERRTYPE Error_;
public:
	/*MyError(MyError::ERRTYPE = UNK_ERROR) : runtime_error("testing")
	{
		
	};*/
	/*explicit MyError(const ERRTYPE& error_message) : 
		Error_(UNK_ERROR){}*/
	//MyError
	//MyError(MyError::ERRTYPE = UNK_ERROR);
	MyError(ERRTYPE);
	ERRTYPE getType();
	std::string getTypeStr(ERRTYPE);
};

#endif