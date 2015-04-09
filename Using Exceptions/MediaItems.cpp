//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Media Item Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef MEDIAITEMS_CLASS_IMPL_H_
#define MEDIAITEMS_CLASS_IMPL_H_

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

//includes for external dependencies
#ifndef MEDIA_DEPENDENCIES_H_
#define MEDIA_DEPENDENCIES_H_
#include "Author.hpp"
#include "Elements.hpp"
#endif

// include header file
#include "MediaItems.hpp"

//defines for default vaules and text output options
#define DEF_NAME ""
#define DEF_PRICE 0.00
#define DEF_PUB 1970
#define DEF_SEQUEL ""
#define TEXT_WIDTH 20

//Function prototype for insertion operator
std::ostream& operator<<(std::ostream &out, MediaItems &MI);

//active mediaitem objects to start
int MediaItems::active_ = 0;

//constructor
MediaItems::MediaItems()
{
	MediaItems::setName(DEF_NAME); //set default name of author

	MediaItems::setPrice(DEF_PRICE); //set default price of item

	MediaItems::setPubYear(DEF_PUB); //set default publication year 1970
	pub_year_def_ = true; // set that the publication year is default

	element_.clear(); // make the list of elements clear
	element_count_ = 0; // set the element count to zero(0)

	setAuthor(NULL); //set the author to a null pointer
	setSequel_str(DEF_SEQUEL); //set the sequel to blank

	hasData = false; //set the item hasdata flag to false

	active_++;
}

//destructor
MediaItems::~MediaItems()
{
	//clear the elements array (not pointers so nothing special needs to be done)
	element_.clear();
	//lower active
	active_--;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mutators
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//set name of item
int MediaItems::setName(std::string new_name_)
{
	MediaItems::name_ = new_name_;
	modified(true);
	return 0;
}

//set publication year of item
int MediaItems::setPubYear(int new_year)
{
	if (new_year >= 0)
	{
		MediaItems::pub_year_ = new_year;
		MediaItems::pub_year_def_ = false;
		modified(true);
		return 0;
	}
	else
	{
		std::cout << "Please enter a valid Year.";
		return -1;
	}
}

//set the Media Item price - validate that the price is not negative
int MediaItems::setPrice(double new_price)
{
	if (new_price >= 0)
	{
		MediaItems::price = new_price;
		modified(true);
		return 0;
	}
	else
	{
		std::cout << "Please enter a valid positive price.";
		return -1;
	}
}

//add a new item element
int MediaItems::addElement(int start, int end, std::string name_, int elementNum)
//elementNum is not used but I included it to make it easier to change the program over later
{
	Elements* new_element = new Elements;

	(*new_element).setStart(start);
	(*new_element).setEnd(end);
	(*new_element).setName(name_);

	element_.push_back(*new_element);

	MediaItems::element_count_++;
	modified(true);
	return 0;
}

//set author
int MediaItems::setAuthor(Author* new_author)
{
	MediaItems::auth_ptr_ = new_author;
	MediaItems::modified(true);
	return 0;
}

//Set Sequel
int MediaItems::setSequel(MediaItems* new_sequel)
{
	MediaItems::sequel_ = (*(new_sequel)).getName();
	
	MediaItems::modified(true);
	return 0;
}

int MediaItems::setSequel_str(std::string new_sequel)
{
	MediaItems::sequel_ = new_sequel;

	MediaItems::modified(true);
	return 0;
}

// set a modified flag
int MediaItems::modified(bool data)
{
	MediaItems::hasData = data;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Accessors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//get Item name
const std::string MediaItems::getName()
{
	return MediaItems::name_;
}

//get pulication year
const int MediaItems::getPubYear()
{
	return MediaItems::pub_year_;
}

// get if the publication year is default
const bool MediaItems::getPubYearDef()
{
	return MediaItems::pub_year_def_;
}

//get author pointer
Author* MediaItems::getAuthor()
{
	return MediaItems::auth_ptr_;
}

//get price of item
const double MediaItems::getPrice()
{
	return MediaItems::price;
}

//!!!--Inefficient for large lists--!!!///
//pass a copy of the element list to the function caller
std::list<Elements> MediaItems::getElement()
{
	return element_;
}

//get the sequel pointer
std::string MediaItems::getSequel()
{
	return sequel_;
}

//print out item
const int MediaItems::toCout()
{
	std::cout << (*this);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Predicate Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//returns if the item is empty
const bool MediaItems::isEmpty()
{
	return !(hasData);
}

//return the number of constructed items
const int MediaItems::in_mem()
{
	return active_;
}

int MediaItems::clear()
{
	(*this) = MediaItems();
	MediaItems::active_ = MediaItems::active_ - 1; //active is increased when calling the constructor
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Overloads
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &out, MediaItems &MI)
{
	//check if the item is empty
	if (MI.isEmpty() == true); //if empty print nothing
	else if (MI.isEmpty() == false) //if not empty print data thats available
	{
		// display item name_ if present
		if (MI.getName() == DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item Name" << " : " << "No Name Set" << std::endl;
		}
		else if (MI.getName() != DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item" << " : " << MI.getName() << std::endl;
		}

		// print out the author object
		if (MI.getAuthor() == NULL);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << (*MI.getAuthor());
		}

		//display publication year if set; check if the value is default
		if (MI.getPubYearDef() == true);
		else if (MI.getPubYearDef() == false)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Pub Year" << " : " << MI.getPubYear() << std::endl;
		}

		//display price if set
		if (MI.getPrice() == DEF_PRICE);
		else if (MI.getPrice() != DEF_PRICE)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Price" << " : $" << std::fixed << MI.getPrice() << std::endl;
		}

		//display sequel if set
		if (MI.getSequel() == DEF_SEQUEL);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Sequel" << " : " << MI.getSequel() << std::endl;
		}

		//open an arbitrary scope for displaying the elements in the item
		{
			//copy the list to allow full access and protect the real list from accedental/intentional modification
			std::list<Elements>local_list = MI.getElement();

			//display elements if they exist; 
			if (local_list.empty() == true); // check if the list is empty
			else //if ((local_list.empty() == false)
			{
				//for loop to cycle through all the elements in local_list
				for (Elements elem : local_list)
				{
					out << elem;
				}//for

			}//else
		}//close scope

	}//close the if empty
	return out;
}//close the overload



#endif 