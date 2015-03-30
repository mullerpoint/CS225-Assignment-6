//
//Media Item Class declaration
//
#ifndef MEDIAITEMS_CLASS_DEF_H_
#define MEDIAITEMS_CLASS_DEF_H_



#ifndef MEDIA_DEPENDENCIES_H_
#define MEDIA_DEPENDENCIES_H_
#include "Author.hpp"
#include "Elements.hpp"
#endif

class MediaItems
{
private:

	bool hasData; // variable to keep track of whether an object has been initialized by the user

protected:
	std::string name_; //name_ of the media item
	int pub_year_; // publication year of the media item
	bool pub_year_def_; // if the publicaiton year is default
	Author* auth_ptr_; // pointer to the author of the mediaitem object

	double price; // price of the media item

	std::list<Elements>element_; // list of element pointers that are containend within the media item
	int element_count_;// the element number being worked on

	static int active_; // number of media items active

	std::string sequel_;

public:
	//Constructor Destructor
	MediaItems();
	virtual ~MediaItems();

	//Mutators
	int setName(std::string);
	int setPubYear(int);
	int setPrice(double);
	int addElement(int, int, std::string, int);
	int setAuthor(Author*);
	virtual int setSequel(MediaItems*);
	virtual int setSequel_str(std::string);
	virtual int modified(bool);
	
	//Accessors
	const std::string getName();
	const int getPubYear();
	const bool getPubYearDef();
	Author* getAuthor();
	const double getPrice();
	std::list<Elements> getElement();
	std::string getSequel();
	const virtual int toCout();

	//Predicate Functions
	const virtual bool isEmpty();
	const int in_mem();
	virtual int clear();
};

#endif 