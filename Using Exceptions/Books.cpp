//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
// Books Class Implementation
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef BOOKS_CLASS_IMPL_H_
#define BOOKS_CLASS_IMPL_H_

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

// include header file
#include "Books.hpp"

//defines for default vaules and text output options
#define DEF_NAME ""
#define DEF_PRICE 0.00
#define DEF_PUB 1970
#define ELEMENT_ZERO 0
#define DEF_PAGES 0
#define DEF_PUB 1970
#define DEF_ISBN ""
#define DEF_SEQUEL ""
#define TEXT_WIDTH 20

//Function prototype for insertion operator
std::ostream& operator<<(std::ostream &out, Books &Book);

//constructor
Books::Books() : MediaItems()
{
	setPages(DEF_PAGES);

	setInPrint(false);
	in_print_def = true;

	//setSequel(NULL);

	setISBN(DEF_ISBN);
	
	setSequel_str(DEF_SEQUEL);

	modified(false);
}

//destructor
Books::~Books()
{
	active_--;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Mutators
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//set book page count - validate that the book doesnt have a negative page count
int Books::setPages(int new_pages)
{
	if (new_pages >= 0)
	{
		Books::pages = new_pages;
		Books::modified(true);
		return 0;
	}
	else
	{
		std::cout << "Please enter a valid positive page number.";
		return -1;
	}

}

//set book in print status
int Books::setInPrint(bool printStatus)
{
	in_print = printStatus;
	in_print_def = false;
	Books::modified(true);
	return 0;
}

//Set Sequel
//int Books::setSequel(Books* new_sequel)
//{
//	sequel_ = (*(new_sequel)).getName();
//
//	MediaItems::modified(true);
//	return 0;
//}
//
//int Books::setSequel_str(std::string new_sequel)
//{
//	Books::sequel_ = new_sequel;;
//
//	MediaItems::modified(true);
//	return 0;
//}

//set book isbn
int Books::setISBN(std::string new_isbn)
{
	Books::isbn = new_isbn;
	MediaItems::modified(true);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Accessors
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//get page count
const int Books::getPages()
{
	return pages;
}

//get in print status
const bool Books::getInPrint()
{
	return in_print;
}

//get if in print is default
const bool Books::getInPrintDef()
{
	return in_print_def;
}

//get the sequel pointer
std::string Books::getSequel()
{
	return sequel_;
}

//get the isbn number
const std::string Books::getISBN()
{
	return isbn;
}

//call overloaded print out function
const int Books::toCout()
{
	std::cout << (*this);
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Predicate Functions
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//return the number of constructed items
const int Books::in_mem()
{
	return active_;
}

//clear book
int Books::clear()
{
	*this = Books();
	Books::active_ = Books::active_ - 2; //active is increased by two when calling the constructor
	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Overloads
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream &out, Books &Book)
{

	//check if the item is empty
	if (Book.isEmpty() == true); //if empty print nothing
	else if (Book.isEmpty() == false) //if not empty print data thats available
	{
		// display item name_ if present
		if (Book.getName() == DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item Name" << " : " << "No Name Set" << std::endl;
		}
		else if (Book.getName() != DEF_NAME)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "Media Item" << " : " << Book.getName() << std::endl;
		}

		// print out the author object
		if (Book.getAuthor() == NULL);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << (*(Book.getAuthor()));
		}

		//display publication year if set; check if the value is default
		if (Book.getPubYearDef() == true);
		else if (Book.getPubYearDef() == false)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Pub Year" << " : " << Book.getPubYear() << std::endl;
		}

		//display price if set
		if (Book.getPrice() == DEF_PRICE);
		else if (Book.getPrice() != DEF_PRICE)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Price" << " : $" << std::fixed << Book.getPrice() << std::endl;
		}

		//display director_ if set
		if (Book.getPages() == DEF_PAGES);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Page Count" << " : " << Book.getPages() << std::endl;
		}

		//display print status if set
		if (Book.getInPrintDef() == true);
		else if (Book.getInPrintDef() == false)
		{
			if (Book.getInPrint() == true)
			{
				out << std::left << std::setw(TEXT_WIDTH) << "  Print Status" << " : " << "In Print" << std::endl;
			}
			else
			{
				out << std::left << std::setw(TEXT_WIDTH) << "  Print Status" << " : " << "Out of Print" << std::endl;
			}
		}

		//display isbn
		if (Book.getISBN() == DEF_ISBN);
		else if (Book.getISBN() != DEF_ISBN)
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  ISBN" << " : " << Book.getISBN() << std::endl;
		}

		//display sequel if set
		if (Book.getSequel() == DEF_SEQUEL);
		else
		{
			out << std::left << std::setw(TEXT_WIDTH) << "  Sequel" << " : " << Book.getSequel() << std::endl;
		}

		//open an arbitrary scope for displaying the elements in the item
		{
			//copy the list to allow full access and protect the real list from accedental/intentional modification
			std::list<Elements>local_list = Book.getElement();

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
	}//else if
	return out;
}//close overload




#endif 