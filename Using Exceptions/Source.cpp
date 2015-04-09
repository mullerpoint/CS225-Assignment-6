//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Gary Muller
// Spring 2015
// CS 225 Assignment 5
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

//User Defined Class Includes
#include "Author.hpp"
#include "Elements.hpp"
#include "MediaItems.hpp"
#include "Books.hpp"
#include "Music.hpp"
#include "Videos.hpp"
#include "MyError.hpp"


//Gloabal Variables and Defines
#define TEXT_WIDTH 20
bool done = false;

//determine if interactive or scripted
int interactive = _isatty(_fileno(stdin)); //windowns statement
//int interactive = isatty(STDIN_FILENO); //unix statement

//define global pointers for media item objects
std::vector<MediaItems *>items;
int ItemNum = -1;
//

//define global pointers for author objects
std::vector<Author *>Authors;
int AuthNum = 0;
//

//define global locale pointer for the locale imbue functionality
std::locale* locale;
//

//Function Prototypes
void process_menu_in(char);
void print_menu();
int printAuthors();
int printItems();
int memUse();
std::string trim(const std::string&, const std::string& whitespace = " \t");
bool alphaSort(MediaItems*, MediaItems*);
bool valueSort(MediaItems*, MediaItems*);
bool typeSort(MediaItems*, MediaItems*);
bool doesMIExist();
bool doesAuthExist();
bool limitCheck(int, int, int);
bool limitCheck(int, int);
bool isBook();
bool isVideo();
bool isMusic();
//


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Main Declaration
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{

	//use the imbue functionality to make the output look pretty
	std::locale mylocal("");
	locale = &mylocal;
	std::cout.imbue(*locale);

	//core program 
	std::string menu_in;
	print_menu();

	std::string itmstr;

	while (!done)
	{
		if (ItemNum == -1)
		{
			itmstr = "-";
		}
		else
		{
			itmstr = std::to_string(ItemNum);
		}

		std::cout << std::endl << "Menu [" << itmstr << "]: ";
		try
		{
			if (interactive)
			{
				std::getline(std::cin, menu_in);
			}
			else if (!interactive)
			{
				std::cin >> menu_in;
			}
			process_menu_in(menu_in[0]);
		}
		catch (MyError)
		{
			std::cout << "testing";
		}
		catch (std::exception)
		{
			std::cout << "testing 123";
		}
		catch (...)
		{
			std::cout << "If you see this you have broken the code" << std::endl << "Quiting ..." << std::endl;
			std::terminate();
		}
	}
	std::cout << std::endl << "Goodbye" << std::endl;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Function Declarations
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Process Menu Function
void process_menu_in(char inchar)
{
	std::cout.imbue(*locale);
	std::cout.precision(2);

	switch (toupper(inchar))
	{

	case '/':
	{
		std::string junk_line;
		std::getline(std::cin, junk_line);
	}
	break;

	//add new item and set current item to that item
	case '+':
	{
		//query user as to what kind of item they want to add
		std::cout << "What kind of item do you want to add : (M)usic, (V)ideo, (B)ook, (I)tem" << std::endl;
		std::string type;
		MediaItems* item_ptr;

		//based on if the session is interactive read in the type
		if (interactive)
		{
			std::getline(std::cin, type);
		}
		else if (!interactive)
		{
			std::cin >> type;
		}

		//based on the type create the item
		switch (toupper(type[0]))
		{
		case 'M':
			item_ptr = new Music;
			break;

		case 'V':
			item_ptr = new Videos;
			break;

		case 'B':
			item_ptr = new Books;
			break;

		default:
			item_ptr = new MediaItems;
			break;
		}


		items.push_back(item_ptr);
		ItemNum = items.size() - 1;
	}
	break;

	//delete the current item
	case '-':
	{
		if (doesMIExist())
		{
			delete items[ItemNum];
			items.erase(items.begin() + (ItemNum));
			std::cout << "Item " << (ItemNum) << " deleted; Plese select a new item before continuing." << std::endl;
			(ItemNum) = -1;
		}

	}
	break;

	// Print all objects
	case '*':
	{
		printAuthors();
		printItems();
	}
	break;

	// set a custom item number between 0-items.size()
	case '#':
	{
		if (doesMIExist())
		{

			//declare temp vaiable and read in user value
			unsigned int new_itemNum;
			std::cout << "Enter new item number : ";
			std::cin >> new_itemNum;

			//validate input
			if (limitCheck(new_itemNum, 0, (items.size()-1)))
			{
				(ItemNum) = new_itemNum;
			}

			//clear buffer for next input
			std::cin.ignore(10000, '\n');
			std::cout << std::endl;
		}
	}
	break;

	// clear item menu option
	case '0':
	{
		if (doesMIExist())
		{
				(*items[ItemNum]).clear();
				std::cout << "Item " << (ItemNum) << " Cleared" << std::endl;
		}
	}
	break;

	//set media item duration or time
	case 'B':
	{
		if (isMusic() || isVideo())
		{
			double runTime;
			std::cout << "Please enter the run time : ";
			std::cin >> runTime;
			if (typeid(items[ItemNum]) == typeid(Music))
			{
				Music* music_ptr = (Music*)items[ItemNum];
				(*music_ptr).setrunTime(runTime);
			}
			else
			{
				Videos* video_ptr = (Videos*)(items[ItemNum]);
				(*video_ptr).setrunTime(runTime);
			}

		}
		else
		{
			MyError oops(MyError::ERRTYPE::WRONG_CLASS);
			throw(oops);
		}
	}
	break;

	//Create an author object
	case 'C':
	{
		Author* temp_ptr = new Author;
		Authors.push_back(temp_ptr);
		AuthNum = Authors.size() - 1;

		int born, died;
		std::string name;

		if (interactive)
		{
			std::cout << "Please enter the Authors name :";
			std::getline(std::cin, name);
			name = trim(name);
			(*Authors[AuthNum]).setName(name);


			std::cout << "Please enter the Authors birth year (yyyy), Zero(0) for none :";
			std::cin >> born;
			(*Authors[AuthNum]).setBirth(born);
			std::cin.ignore(10000, '\n');

			std::cout << "Please enter the Authors death year (yyyy), Zero(0) for none :";
			std::cin >> died;
			(*Authors[AuthNum]).setDeath(died);
			std::cin.ignore(10000, '\n');

			AuthNum = AuthNum + 1;
		}
		else //scripted
		{
			std::cin >> (*Authors[AuthNum]);
			//std::cin.ignore(256, '\n');

			AuthNum = AuthNum + 1;
		}
	}
	break;

	// display item menu option
	case 'D':
	{
		if (doesMIExist())
		{
			std::cout << std::endl << "Item [" << (ItemNum) << "] :" << std::endl;
			(*items[ItemNum]).toCout();
		}
	}
	break;

	//Create an element object in the media item object
	case 'E':
	{
		if (doesMIExist())
		{
			int num, start, end;
			std::string name;

			if (interactive)
			{
				//get start
				std::cout << "Please enter the Element name_ : ";
				std::getline(std::cin, name);

				//get end
				std::cout << "Please enter the Element start, Zero(0) for none : ";
				std::cin >> start;
				std::cin.ignore(1, '\n');

				//get end
				std::cout << "Please enter the Element end, Zero(0) for none : ";
				std::cin >> end;
				std::cin.ignore(1, '\n');

			}
			else //scripted
			{
				//get start
				std::cin >> start;
				std::cin.ignore(1, '\n');

				//get end
				std::cin >> end;
				std::cin.ignore(1, '\n');

				//get name
				std::getline(std::cin, name);
				//(*Authors[AuthNum]).setName(name);
			}

			//clear leading whitespace
			name = trim(name);

			//pass all acquired data to the add element funciton
			(*items[ItemNum]).addElement(start, end, name, num = 0);

		}
	}
	break;

	//set music/video Producer/director respectivly
	case 'F':
	{
		if (isMusic()|| isVideo())
		{
			std::string executive;
			std::cout << "Please enter the Producer or director : ";
			std::getline(std::cin, executive);

			//clear leading whitespace
			executive = trim(executive);

			if (typeid(*items[ItemNum]) == typeid(Music))
			{
				//create a simple variable that points to cast version of the object
				Music* music_ptr = (Music*)items[ItemNum];
				//set the Producer
				(*music_ptr).setExecutive(executive);
			}
			else
			{
				//create a simple variable that points to cast version of the object
				Videos* video_ptr = (Videos*)items[ItemNum];
				//set the director
				(*video_ptr).setExecutive(executive);
			}
		}
		else
		{

			MyError oops(MyError::ERRTYPE::WRONG_CLASS);
			throw(oops);
		}
	}
	break;

	// set the item in print status
	case 'I':
	{
		if (doesMIExist())
		{
			if (isBook())
			{
				//create a simple variable that points to cast version of the object
				Books* book_ptr = (Books*)items[ItemNum];

				bool printStatus;
				std::cout << "Is the book still in print (0/1) : ";
				std::cin >> printStatus;
				std::cin.ignore(10000, '\n');
				(*book_ptr).setInPrint(printStatus);
			}
			else
			{
				MyError oops(MyError::ERRTYPE::WRONG_CLASS);
				throw(oops);
			}
		}
	}
	break;

	//set Book ISBN
	case 'J':
	{
		if (doesMIExist())
		{
			if (isBook())
			{
				//create a simple variable that points to cast version of the object
				Books* book_ptr = (Books*)items[ItemNum];

				std::string isbn;
				std::cout << "Please enter the Book ISBN :";
				std::getline(std::cin, isbn);
				isbn = trim(isbn);
				(*book_ptr).setISBN(isbn);
			}
			else
			{
				MyError oops(MyError::ERRTYPE::WRONG_CLASS);
				throw(oops);
			}
		}
	}
	break;

	//set Music GENRE
	case 'K':
	{
		if (doesMIExist())
		{
			if (isMusic())
			{
				//create a simple variable that points to cast version of the object
				Music* music_ptr = (Music*)items[ItemNum];

				//get the GENRE string from input
				std::string GenreStr;
				std::cout << "Please enter the GENRE : ";
				std::getline(std::cin, GenreStr);
				for (auto & c : GenreStr) c = toupper(c); //convert to uppercase

				//create a bool variable to determine if the GENRE has been set
				bool GENRESet = false;

				//variable to keep track of type
				Music::GENRE type = Music::GENRE::ROC;

				//for loop to try find a match to one of the defined GENREs
				while ((type != Music::GENRE::END) && (GENRESet == false))
				{
					//get the token for searching the GENRE string
					std::string typeStr = (*music_ptr).dispGENRESht(type);

					//if the token matches something in the GENRE string set the object to the GENRE
					if (GenreStr.find(typeStr) != std::string::npos)
					{
						(*music_ptr).setGENRE(type);
						GENRESet = true;
					} //if GenreStr
					type = Music::GENRE(type + 1);
				}//while
				if (GENRESet == false)
				{
					(*music_ptr).setGENRE(Music::GENRE::OTHER);
				}
			} //if isMusic()
			else
			{
				MyError oops(MyError::ERRTYPE::WRONG_CLASS);
				throw(oops);
			}
		}
	}//case
	break;

	//List Music by GENRE
	case 'L':
	{
		unsigned int count = 0;
		int numPrinted = 0;
		bool found = false;
		Music* firstMusicObj = NULL;

		//determine if their are any music objects and save the location of the first one 
		while ((count < items.size()) && (found == false))
		{
			if (typeid(*(items[count])) == typeid(Music))
			{
				found = true;
				firstMusicObj = (Music*)items[count];
			}
			count++;
		}

		//if a music was not found tell the user
		if (found == false)
		{
			std::cout << "There are no Music items to sort" << std::endl;
		}

		// if a music was found print out 
		else if (found == true)
		{
			Music::GENRE type = Music::GENRE::ROC;
			while (type != Music::GENRE::END)
			{
				std::cout << std::endl << "===== GENRE : " << (*firstMusicObj).dispGENRE(type) << " =====" << std::endl;
				count = 0;
				numPrinted = 0;
				while (count < items.size())
				{
					if (typeid(*items[count]) == typeid(Music))
					{
						Music* music_ptr = (Music*)items[count];
						if ((*music_ptr).dispGENRESht((*music_ptr).getGENRE()) == (*music_ptr).dispGENRESht(type))
							//comparing strings to allow comparison, enums refused to compile
						{
							if (!((*music_ptr).isEmpty()))
							{
								std::cout << std::endl << "Item [" << count << "]" << std::endl;
								(*items[count]).toCout();
								numPrinted++;
							} //if isEmpty
						} //if GENRE
					} //if type id
					count++;
				}//while

				// if there were no songs of that GENRE print that out
				if (numPrinted == 0)
				{
					std::cout << "No Songs Found" << std::endl;
				} //if numPrinted

				type = Music::GENRE(type + 1);
			} //while
		} //else if

	}//case
	break;

	// display menu again menu option
	case 'M':
		print_menu();
		break;

		// enter item name menu option
	case 'N':
	{
		if (doesMIExist())
		{
			std::string new_name;
			std::cout << "Enter Media Item Title : ";
			std::getline(std::cin, new_name);
			new_name = trim(new_name);
			(*items[ItemNum]).setName(new_name);
		}
	}
	break;

	// enter item page count menu option
	case 'P':
	{
		if (doesMIExist())
		{
			if (isBook())
			{
				Books* book_ptr = (Books*)items[ItemNum];

				int new_pages;
				std::cout << "Enter Media Item Pages : ";
				std::cin >> new_pages;
				(*book_ptr).setPages(new_pages);
				std::cin.ignore(10000, '\n');
			}
			else
			{
				MyError oops(MyError::ERRTYPE::WRONG_CLASS);
				throw(oops);
			}
		}
	}
	break;

	// quit program menu option
	case 'Q':
		done = true;
		break;

		// show memory useage
	case 'R':
	{
		memUse();
	}
	break;

	//Set Sequel index
	case 'S':
	{
		if (doesMIExist())
		{
			int temp_num;
			std::cout << "Enter Sequel index number : ";
			std::cin >> temp_num;
			std::cin.ignore(1, '\n');

			if (isBook())
			{
				Books* book_ptr = (Books*)items[ItemNum];
				Books* sql_ptr = (Books*)items[temp_num];

				(*book_ptr).setSequel(sql_ptr);
			}
			else
			{
				Videos* video_ptr = (Videos*)items[ItemNum];
				Videos* sql_ptr = (Videos*)items[temp_num];

				(*video_ptr).setSequel(sql_ptr);
			}

		}
	}
	break;

	//Set author pointer
	case 'T':
	{
		if (doesMIExist())
		{
			int temp_num;
			std::cout << "Enter Author index number : ";
			std::cin >> temp_num;
			std::cin.ignore(1, '\n');
			(*items[ItemNum]).setAuthor(Authors[temp_num]);
		}
	}
	break;

	//sort items
	case 'U':
	{
		if (doesMIExist())
		{
			//query user as to what kind of sort they want to do
			std::cout << "What kind of sort do you want to do : (A)lphabetic, (V)alue, (T)ype" << std::endl;
			std::string sortType;

			//based on if the session is interactive read in the type
			if (interactive)
			{
				std::getline(std::cin, sortType);
			}
			else if (!interactive)
			{
				std::cin >> sortType;
			}

			switch (sortType[0])
			{
			case 'V':
				std::sort(std::begin(items), std::end(items), valueSort);
				break;

			case 'T':
				std::sort(std::begin(items), std::end(items), typeSort);
				break;

			case 'A':
			default:
				std::sort(std::begin(items), std::end(items), alphaSort);
				break;
			}

		}
	}
	break;

	// set the item value ($)
	case 'V':
	{
		if (doesMIExist())
		{
			double new_price;
			std::cout << "Enter Media Item value : ";
			std::cin >> new_price;
			std::cin.ignore(10000, '\n');
			(*items[ItemNum]).setPrice(new_price);
		}
	}
	break;

	// set the item publication year
	case 'Y':
	{
		if (doesMIExist())
		{
			int new_year;
			std::cout << "Enter Media Item publication year : ";
			std::cin >> new_year;
			std::cin.ignore(10000, '\n');
			(*items[ItemNum]).setPubYear(new_year);
		}
	}
	break;

	// default option if wrong key entered
	default:
		std::cout << "Please select an option from the menu" << std::endl << "to see the menu again type 'm'";
		break;
	}
}

//Print Menu Function
void print_menu()
{
	std::cout << std::endl
		<< "+ - Create & Select new Media Item of[B, M, V, *] types" << std::endl
		<< "- - Delete selected Media Item" << std::endl
		<< "* - Display / Print all Media Items" << std::endl
		<< "# - Set the selected Media Item" << std::endl
		<< "0 - Clear selected Media Item data" << std::endl
		<< "B - set Media Item duration / time" << std::endl
		<< "C - Create author" << std::endl
		<< "D - Display selected Media Item data" << std::endl
		<< "E - Add Media Item element" << std::endl
		<< "F - Set Music / Video Producer / Director respectively" << std::endl
		<< "I - Set Media Item In Print Status(0 / 1)" << std::endl
		<< "J - Set Book ISBN" << std::endl
		<< "K - set Music Genre" << std::endl
		<< "L - Display Music Items by Genre" << std::endl
		<< "M - Print this menu" << std::endl
		<< "N - Set Media Item name" << std::endl
		<< "Q - Quit this program" << std::endl
		<< "P - Set Media Item pages" << std::endl
		<< "R - Display program memory usage" << std::endl
		<< "S - Set Media Item Sequel from Index" << std::endl
		<< "T - Set Media Item Author Index" << std::endl
		<< "U - Sort Media Item Aggregation by Name" << std::endl
		<< "V - Set Media Item Value" << std::endl
		<< "Y - Set Media Item Year Produced" << std::endl << std::endl;
}

//Print Authors
int printAuthors()
{
	//Print out all author objects
	std::cout << std::endl << std::endl << "==== All Authors Start ====" << std::endl;

	if (!Authors.empty())//check if there are any authors to print out
	{
		unsigned int count = 0;

		while (count <= (Authors.size() - 1))
		{
			if ((*Authors[count]).isEmpty());
			//isempty() returns the hasData value which is false for an object with no data and true for an object with data, hence the ! to invert the return value
			else
			{
				std::cout << std::endl << std::endl << "Author [" << count << "] :" << std::endl;
				(*Authors[count]).toCout();
			}
			count++;
		}
	}
	else //if (Authors.empty())
	{
		std::cout << "There are no Authors to Print" << std::endl;
	}

	std::cout << std::endl << "===== All Authors End =====" << std::endl;

	return 0;
}

//Print out all the Media Items
int printItems()
{
	//Print out all Media Item Objects
	std::cout << std::endl << std::endl << "===== All Items Start =====" << std::endl;

	if (!items.empty()) //check if there are any items to print out
	{
		unsigned int count = 0;

		while (count <= (items.size() - 1))
			//the '- 1' is to account for the fact that item '1' is array position '0'
		{
			if ((*items[count]).isEmpty());
			else //if (mixed_array[count].isEmpty() == true)
			{
				std::cout << std::endl << std::endl << "Item [" << count << "]" << std::endl;
				(*items[count]).toCout();
			}
			count++;
		}
	}
	else //if (items.empty())
	{
		std::cout << "There are no Items to Print" << std::endl;
	}

	std::cout << std::endl << "====== All Items End ======" << std::endl;

	return 0;
}

int memUse()
{

	//create a count for each of the types of item
	unsigned int numBooks = 0, numMusic = 0, numVideos = 0, numMIs = 0, numAuths = 0;

	//set the authors count
	if (Authors.empty());
	else
	{
		numAuths = Authors.size();
	}

	//tally each of the media item types
	if ((items.empty()) && (Authors.empty()));
	else
	{
		for (MediaItems *element : items)
		{
			if (typeid(*element) == typeid(MediaItems)) numMIs++;
			else if (typeid(*element) == typeid(Books)) numBooks++;
			else if (typeid(*element) == typeid(Music)) numMusic++;
			else if (typeid(*element) == typeid(Videos)) numVideos++;

		}
	}


	std::cout
		<< std::endl << "[" << std::setw(3) << std::right << (numAuths + numBooks + numMIs + numMusic + numVideos) << "] "
		<< std::left << std::setw(TEXT_WIDTH + 2) << "Total Memory Used" << " : "
		<< (sizeof(MediaItems)*numMIs + (sizeof(Author)*numAuths) + sizeof(Books)*numBooks +
		sizeof(Music)*numMusic + sizeof(Videos)*numVideos) << " Bytes"
		<< std::endl << "  [" << std::setw(3) << std::right << numAuths << "] "
		<< std::left << std::setw(TEXT_WIDTH) << "Authors" << " : " << sizeof(Author)*numAuths << " Bytes"
		<< std::endl << "  [" << std::setw(3) << std::right << numMIs << "] "
		<< std::left << std::setw(TEXT_WIDTH) << "Media Items" << " : " << sizeof(MediaItems)*numMIs << " Bytes"
		<< std::endl << "  [" << std::setw(3) << std::right << numBooks << "] "
		<< std::left << std::setw(TEXT_WIDTH) << "Book Items" << " : " << sizeof(Books)*numBooks << " Bytes"
		<< std::endl << "  [" << std::setw(3) << std::right << numMusic << "] "
		<< std::left << std::setw(TEXT_WIDTH) << "Music Items" << " : " << sizeof(Music)*numMusic << " Bytes"
		<< std::endl << "  [" << std::setw(3) << std::right << numVideos << "] "
		<< std::left << std::setw(TEXT_WIDTH) << "Video Items" << " : " << sizeof(Videos)*numVideos << " Bytes";

	return 0;
}

//remove leading white space 
std::string trim(const std::string& str, const std::string& whitespace)
{
	const auto strBegin = str.find_first_not_of(whitespace);
	if (strBegin == std::string::npos)
		return ""; // no content

	const auto strEnd = str.find_last_not_of(whitespace);
	const auto strRange = strEnd - strBegin + 1;

	return str.substr(strBegin, strRange);
}

//define sort function for alphabetic sort
bool alphaSort(MediaItems* lhs, MediaItems* rhs)
{
	return (int)(((*lhs).getName())[0]) < (int)(((*rhs).getName())[0]);
}

//define sort function for value sort
bool valueSort(MediaItems* lhs, MediaItems* rhs)
{
	return (int)((*lhs).getPrice()) < (int)((*rhs).getPrice());
}

//define sort function for type sort
bool typeSort(MediaItems* lhs, MediaItems* rhs)
{
	//mediaitem is 1st in terms of sorting
	if (typeid(*lhs) == typeid(MediaItems))
	{
		return true;
	}

	//book is 2nd in terms of sorting
	else if (typeid(*lhs) == typeid(Books))
	{
		//if the right side is a media item the book is less
		if (typeid(*rhs) == typeid(MediaItems))
		{
			return false;
		}

		//but if right side is not a media item left side is greater
		else
		{
			return true;
		}
	}

	//music is 3rd in terms of sorting
	else if (typeid(*lhs) == typeid(Music))
	{
		//if the right side is a video then left side is greater
		if ((typeid(*rhs) == typeid(MediaItems)) || (typeid(*rhs) == typeid(Books)))
		{
			return false;
		}

		//if right side is video or music left side is greater
		else
		{
			return true;
		}
	}

	//video is 4th in terms of sorting
	else if (typeid(*lhs) == typeid(Videos))
	{
		//if right side is also a video return true to maintain consistency across all cases
		if (typeid(*rhs) == typeid(Videos))
		{
			return true;
		}

		//if right side is not video left side is less
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


bool doesMIExist()
{
	if (items.size() > 0)
	{
		return 1;
	}
	else
	{
		MyError oops(MyError::ERRTYPE::NOT_EXIST);
		throw(oops);
		return 0;
	}
}

bool doesAuthExist()
{
	if (Authors.size() > 0)
		return 1;
	else
	{
		MyError oops(MyError::ERRTYPE::NOT_EXIST);
		throw(oops);
		return 0;
	}
}

bool limitCheck(int user_input, int low, int high)
{
	if (user_input>low && user_input<high)
		return 1;
	else
	{
		MyError oops(MyError::ERRTYPE::OUT_OF_BOUNDS);
		throw(oops);
		return 0;
	}
}

bool limitCheck(int user_input, int low)
{
	if (user_input>low)
		return 1;
	else
	{
		MyError oops(MyError::ERRTYPE::OUT_OF_BOUNDS);
		throw(oops);
		return 0;
	}
}

bool isBook()
{
	if (typeid(*(items[ItemNum])) == typeid(Books))
		return 1;
	else
	{
		return 0;
	}
}

bool isVideo()
{
	if (typeid(*(items[ItemNum])) == typeid(Videos))
		return 1;
	else
	{
		return 0;
	}
}

bool isMusic()
{
	if (typeid(*(items[ItemNum])) == typeid(Music))
		return 1;
	else
	{
		return 0;
	}
}