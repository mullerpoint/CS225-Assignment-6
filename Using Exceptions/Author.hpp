//
//Author Class declaration
//

#ifndef AUTHOR_CLASS_DEF_H_
#define AUTHOR_CLASS_DEF_H_

class Author
{
private:
	int birthYear_; // birth year of the author
	int deathYear_; // death year of the author
	std::string name_; // name of the author

	bool hasData_; // variable to keep track of whether an object has been initialized by the user

	static int active_; //number of active author objects

public:
	//Constructor Destructor
	Author();
	~Author();

	//Mutators
	void setBirth(int);
	void setDeath(int);
	void setName(std::string);
	void modified(bool);

	//Accessors 
	const std::string getName();

	//Predicate Functions
	bool isEmpty();
	int in_mem();
	void toCout();
};

//Function prototypes for overloads
std::ostream& operator<<(std::ostream &out, Author &Auth);
std::istream& operator>>(std::istream &in, Author &Auth);


#endif 