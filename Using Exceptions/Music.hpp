//
//Music Class declaration
//

#ifndef MUSIC_CLASS_DEF_H_
#define MUSIC_CLASS_DEF_H_

#include "MediaItems.hpp"



class Music :
	public MediaItems
{
	//need to declare the Genre enum as public so it can be used in comparisons in other functions
	//Genre is declared first so that the atribute musicGENRE will be allowed
public:
	enum GENRE {
		ROC, COU, HIP, TEC, REG, OTHER, UDEF, END
	}; //enum of the music genre

private:
	std::string Producer_; //name_ of the producer of the music
	double minutes_; // time in minutes of the music
	//std::string sequel_;
	GENRE musicGENRE_; //genre enum

public:
	//Constructor Destructor
	Music();
	~Music();

	//Mutators
	virtual int setExecutive(std::string);
	int setrunTime(double);
	int setGENRE(GENRE UDEF);
	//int setSequel(MediaItems*);
	//int setSequel(std::string);

	//Accessors
	const std::string getProducer();
	const virtual double getrunTime();
	const Music::GENRE getGENRE();
	std::string getSequel();
	const virtual int toCout();

	//predicate
	const int in_mem();
	int clear();
	std::string dispGENRE(Music::GENRE = Music::GENRE::OTHER);
	std::string dispGENRESht(Music::GENRE = Music::GENRE::OTHER);
};

#endif 