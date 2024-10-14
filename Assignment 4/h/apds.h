#pragma once

#include<vector>
#include"student.h"

class APDS
{
private:                      //member variable class APDS
	class Item                //class Item
	{
	public:
		Student* ps;          //current student
		Item* pnext;          //adress next item
		Item* pprev;          //adress previos item
		Item(Student&);       //constructor class Item
	};

	Item* phead;              //adress of the student with the maximum value in the data structure
	Item* ptail;              //adress of the student with the minimum value in the data structure
	size_t size;              //number of students in data struture
	size_t capacity;          //capacity of our data structure
	std::string name{ "AP Data Structure" };  //name

public:                                                          //member function class APDS

	APDS(std::vector<Student>& students, size_t capacity = 3);   //constructor
	APDS(std::vector<Student>&& students, size_t capacity = 3);  //constructor for rvalue
	APDS(const APDS&);                                           //copy constructor
	APDS();                                                      //default costructor
	~APDS();                                                     //destructor

	bool push(Student&);                                         //gets a student and tries to push it to the data structure if possible
	bool pop();                                                  //removes the student with the least value (tail)
	Student& go(int n);                                          //go n step in data structure
	Student* searchByID(long id);                                //searches for a particular student in the data structure
	void setCapacity(size_t i);                                  //changes the capacity
	size_t getCapacity();                                        //get capacity
	void setName(std::string s) const;                           //changes the data structure name
	size_t getSize();                                            //get size
	Student* getHeadStudent();                                   //get phead
	void show() const;                                           //display our data structure
	                                                             //operators
	Student& operator[](int n) const;                            //operator []
	APDS& operator=(const APDS& A);                              //operator =
	friend std::ostream& operator<<(std::ostream& os, APDS& input); //display our data structure
};

