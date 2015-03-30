//
//Elements Class declaration
//

#ifndef ELEMENTS_CLASS_DEF_H_
#define ELEMENTS_CLASS_DEF_H_

class Elements
{
private:
	int start_; //starting location of the element
	int end_; // ending location of the element
	std::string name_; //name of the element

	bool hasData_; // variable to keep track of whether an object has been initialized by the user

	static int active_; // number of elements active

public:
	//Constructor Destructor
	Elements();
	~Elements();

	//Mutators
	void setStart(int);
	void setEnd(int);
	void setName(std::string);
	void modified(bool);

	//Accessors
	int getStart();
	int getEnd();
	std::string getName();

	//Predicate Functions
	bool isEmpty();
	int in_mem();
	void toCout();

	
};

//Function prototype for overload
std::ostream& operator<<(std::ostream &out, Elements &Elem);

#endif 