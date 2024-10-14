#ifndef APQUEUE_H
#define APQUEUE_H

#include<iostream>
#include<iomanip>
#include<vector>
#include <memory>
#include"normalstudent.h"
#include"exponentialstudent.h"

template<typename T>
class APQueue
{
private:
	class Item                //class Item
	{
	public:
		T* pvalue;           //current object
		Item* pnext;         //adress next item
		Item(T&);            //constructor class Item
	};

	Item* phead;          //adress of the head in queue
	Item* ptail;          //adress of the tail in queue
	size_t size;          //number of students in data struture

public:
	APQueue(std::vector<T>&);       //constructor
	APQueue(std::vector<T>&&);      //constructor for rvalue
	~APQueue();                     //destructor

	void enqueue(T&);               //gets a object and push it to queue
	APQueue<T>* enqueue(T&&);       //gets a object rvalue and push it to queue
	T dequeue();                    //removes the first thing in queue
	void show();                    //show detail

	T operator[](size_t i);         //operator []
};

template <>                        //specializations 
class APQueue<std::unique_ptr<Student>>
{
private:
	class Item                   //class Item
	{
	public:
		Student* pvalue;         //current student
		Item* pnext;             //adress next item
		inline Item(Student*&);  //constructor class Item
	};

	Item* phead;                 //adress of the head in queue
	Item* ptail;                 //adress of the tail in queue
	size_t size;                 //number of students in data struture

public:
	inline APQueue(std::vector<std::unique_ptr<Student>>&&); //constructor for rvalue
	inline~APQueue();                                        //destructor
	inline void enqueue(Student*&);                          //gets a object and push it to queue
	inline void show();                                      //show detail
};

#include"apqueue.hpp"


#endif 


