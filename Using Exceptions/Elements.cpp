//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Elements Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef ELEMENTS_CLASS_IMPL_H_
#define ELEMENTS_CLASS_IMPL_H_

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
#include <cctype> //for isalpha()
#endif

// include header file
#include "Elements.hpp"


//Defines for default vaules
#define DEF_START 0
#define DEF_END 0
#define DEF_NAME ""
#define TEXT_WIDTH 20

//Active elements objects to start
int Elements::active_ = 0;

//constructor
Elements::Elements()
{
	Elements::setEnd(DEF_END);
	Elements::setStart(DEF_START);
	Elements::setName(DEF_NAME);
	Elements::modified(false);
	active_++;
}

//destructor
Elements::~Elements()
{
	active_--;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mutators
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//set element start
void Elements::setStart(int new_start)
{
	if (new_start >= 0)
	{
		Elements::start_ = new_start;
		Elements::modified(true);
	}
	else
	{
		std::cout << "Please enter a valid start.";
	}
}

//set element end
void Elements::setEnd(int new_end)
{
	if (new_end >= 0)
	{
		Elements::end_ = new_end;
		Elements::modified(true);
	}
	else
	{
		std::cout << "Please enter a valid end.";
	}
}

//set element name
void Elements::setName(std::string new_name_)
{
	Elements::name_ = new_name_;
	modified(true);
}

//set element as modified/unmodified
void Elements::modified(bool data)
{
	Elements::hasData_ = data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Accessors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Elements::getStart()
{
	return start_;
}

int Elements::getEnd()
{
	return end_;
}

std::string Elements::getName()
{
	return name_;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Predicate Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Object empty check
bool Elements::isEmpty()
{
	return !hasData_;
}

//return objects in memory
int Elements::in_mem()
{
	return active_;
}

//display all object attributes
void Elements::toCout()
{
	if (isEmpty());
	else if (!isEmpty())
	{
		if (name_ == "");
		else if (true)
		{
			std::cout << std::left << std::setw(TEXT_WIDTH) << "Element name" << " : " << name_;
		}
		if (start_ == 0);
		else if (start_ > 0)
		{
			std::cout << std::left << std::setw(TEXT_WIDTH) << "Start" << " : " << start_;
		}
		if (end_ == 0);
		else if (end_ > 0)
		{
			std::cout << std::left << std::setw(TEXT_WIDTH) << "End" << " : " << end_;
		}

	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Overloads
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &out, Elements &Elem)
{
	//have element name_, start, and end set
	if ((Elem.getName() != DEF_NAME) && (Elem.getEnd() != DEF_END) && (Elem.getStart() != DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.getName() << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element Start" << " : " << Elem.getStart() << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element End" << " : " << Elem.getEnd() << std::endl;
	}
	//have element name_ and start set
	else if ((Elem.getName() != DEF_NAME) && (Elem.getEnd() == DEF_END) && (Elem.getStart() != DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.getName() << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element Start" << " : " << Elem.getEnd() << std::endl;
	}
	//have element name_ and end set
	else if ((Elem.getName() != DEF_NAME) && (Elem.getEnd() != DEF_END) && (Elem.getStart() == DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.getName() << std::endl <<
			std::left << std::setw(TEXT_WIDTH) << "      Element End" << " : " << Elem.getEnd() << std::endl;
	}
	//only have element name_ set
	else if ((Elem.getName() != DEF_NAME) && (Elem.getEnd() == DEF_END) && (Elem.getStart() == DEF_START))
	{
		out <<
			std::left << std::setw(TEXT_WIDTH) << "    Element Name" << " : " << Elem.getName() << std::endl;
	}

	return out;
}

#endif 