#include "apds.h"

APDS::Item::Item(Student& S)
{
	ps = &S;
	pnext = nullptr;        //initialize pnext
	pprev = nullptr;        //initialize pprev
}

APDS::APDS(std::vector<Student>& students, size_t capacity)   //constructor
{
	phead = nullptr;            //initialize phead
	ptail = nullptr;            //initialize ptail
	size = 0;                   //initialize size
	this->capacity = capacity;  //save capacity
	for (auto & x : students)
		push(x);
}

APDS::APDS(std::vector<Student>&& students, size_t capacity) //constructor for rvalue
{
	static std::vector<Student> stu{ students };  //to save students vector

	phead = nullptr;                              //initialize phead
	ptail = nullptr;                              //initialize ptail
	size = 0;                                     //initialize size
	this->capacity = capacity;                    //save capacity
	for (auto &x : stu)
		push(x);
}

APDS::APDS(const APDS& A)
{
	capacity = A.capacity;   //save capacity
	size = A.size;           //save size
	name = A.name;           //save name

	phead = new Item{ *(A.phead->ps) };   //save item phead
	Item* new_item{ phead };
	Item* temp = A.phead;

	while (temp->pnext != A.ptail)        //copy all item in data structure
	{
		temp = temp->pnext;
		new_item->pnext = new Item{ *(temp->ps) };
		new_item->pnext->pprev = new_item;
		new_item->pprev = temp->pprev;
		new_item = new_item->pnext;
	}
	new_item->pnext = new Item{ *(A.ptail->ps) };   //save ptail
	new_item->pnext->pprev = new_item;
	ptail = new_item->pnext;
	phead->pprev = ptail;
	ptail->pnext = phead;
}

APDS::APDS()               //default constructor
{
	phead = nullptr;       //initialize phead
	ptail = nullptr;       //initialize ptail
	size = 0;              //initialize size
	capacity = 3;          //default capacity

}

APDS::~APDS()  //destructor
{              //remove all item in data structure
	Item* temp{ phead->pnext };

	for (size_t i{}; i < size-1; i++)
	{
		delete temp->pprev;
		temp = temp->pnext;
	}
	delete ptail;
}

bool APDS::push(Student& S)     //gets a student and tries to push it to the data structure if possible
{
	if (!(capacity - size) && (ptail->ps->value() > S.value()))      //if this value of this student less than ptail return false 
		return false;
	else if (!(capacity - size) && (ptail->ps->value() < S.value())) //if this value of this student bigger than ptail ,remove ptail and get the new student 
		pop();                                                       //removes the student with the least value (tail)

	Item* new_s =new Item{S} ;    //create new item with this new student
	
	if (size == 0)                //for save first data 
	{
		new_s->pnext = new_s;     //save adresses  
		new_s->pprev = new_s;
		phead = new_s;            //phead and ptail for size 1 is same 
		ptail = new_s;
		size++;

		return true;
	}

	Item* temp{ phead };     //strat with phead
	size_t counter{ size };  //for save size befor change it

	for (size_t i{}; i < counter; i++)      //search for a good pleace  
	{
		if (S.value() > temp->ps->value())  //if find a good place
		{
			temp->pprev->pnext = new_s;     //save this item
			new_s->pprev = temp->pprev;     //save new adresses and update old adrsses
			new_s->pnext = temp;
			temp->pprev = new_s;
			if (i == 0)                     //if phead change
				phead = new_s;
			size++;                         //increase size data structure

			return true;
		}
		temp = temp->pnext;                //go to next student
	}

	//if there is no good place so save this data as new ptail
	new_s->pnext = phead;         //save new adresses and update old adrsses       
	new_s->pprev = temp->pprev;
	temp->pprev->pnext = new_s;
	phead->pprev = new_s;
	ptail = new_s;                //save new ptail
	size++;                       //increase size data structure

	return true;
}

bool APDS::pop()     //removes the student with the least value (tail)
{
	if(!size)        //If the data structure is empty return false
		return false;

	//removes last data and update adress
	ptail->pprev->pnext = phead;
	phead->pprev = ptail->pprev;
	delete ptail;           //delete ptail
	ptail = phead->pprev;
	
	size--;                 //decrease size data structure

	return true;
}

Student& APDS::go(int n)  //go n step in data structure
{
	if (n >= 0)                    //positive n
	{
		Item* temp{ phead };       //first student
		for (int i{}; i < n; i++)  //go  next student
			temp = temp->pnext;

		return *(temp->ps);        //return derefrence student*
	}
	else                           //negitive n
	{
		Item* temp{ phead };       //first student

		for (int i{}; i > n; i--)  //go pervious student
			temp = temp->pprev;

		return *(temp->ps);       //return derefrence student*
	}
}

Student* APDS::searchByID(long id)//searches for a particular student in the data structure
{
	Item* temp{ phead };               // start from first student

	for (size_t i{}; i < size; i++)    //search for id
	{
		if (!(temp->ps->getID() - id)) //check is that student or not 
			return temp->ps;           
		temp = temp->pnext;            //go to next student
	}
	return nullptr;                    //if there is no student with this id return nullptr
}

void APDS::setCapacity(size_t i)   //changes the capacity
{
	capacity = i;
	int def{ static_cast<int>(size - i) };//number of student which we must remove

	if (def > 0)
		for (int j{}; j < def; j++)
			pop();                 //removes the student with the least value (tail)
}

size_t APDS::getCapacity()  //get capacity
{
	return capacity;
}

void APDS::setName(std::string s) const     //changes the data structure name to s
{
	auto p = const_cast<APDS*>(this);
	p->name = s;
}

size_t APDS::getSize()  //get size
{
	return size;
}

Student* APDS::getHeadStudent() //get phead
{
	return phead->ps;
}

void APDS::show() const //display our data structure
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Capacity: " << capacity << std::endl;
	std::cout << "Size: " << size << std::endl;
	std::cout << std::setw(20) << "N" << std::setw(20) << "ID" << std::setw(20) << "Homework" << std::setw(20);
	std::cout << "MidProject" << std::setw(20) << "MidExam" << std::setw(20) << "Party" << std::setw(20);
	std::cout << "Value" << std::endl;

	Item* temp{ phead };      //first student

	for (size_t i{}; i < size; i++)
	{
		std::cout << std::setw(20) << i + 1 << std::setw(20) << temp->ps->getID() << std::setw(20) << temp->ps->getHomework();
		std::cout << std::setw(20) << temp->ps->getMidtermProject() << std::setw(20) << temp->ps->getMidtermExam();
		std::cout << std::setw(20) << temp->ps->getParty() << std::setw(20) << temp->ps->value() << std::endl;
		temp = temp->pnext;
	}

}

Student& APDS::operator[](int n) const    //operator []
{
	if (n >= 0 && n < static_cast<int>(size))               //positive n
	{
		Item* temp{ phead };              //first student
		for (int i{}; i < n; i++)         //go  next student
			temp = temp->pnext;

		return *(temp->ps);               //return derefrence student*
	}
	else if (n < 0 && n >= -static_cast<int>(size))      //negitive n
	{
		Item* temp{ phead };       //first student

		for (int i{}; i > n; i--)  //go pervious student
			temp = temp->pprev;

		return *(temp->ps);        //return derefrence student*
	}
	else                           //out of range n
	{
		static Student new_student{};

		return new_student;        //reference to new student which has zero information
	}
}

APDS& APDS::operator=(const APDS& A)  //operator =
{
	Item* temp = nullptr;

	if (size != 0)
	{
		temp = phead->pnext;         //remove all item in data structure
		for (size_t i{}; i < size - 1; i++)
		{
			delete temp->pprev;
			temp = temp->pnext;
		}
		delete ptail;
	}
	
	capacity = A.capacity;   //save capacity
	size = A.size;           //save size
	name = A.name;           //save name

	phead = new Item{ *(A.phead->ps) };   //save item phead
	Item* new_item{ phead };
	temp = A.phead;
	while (temp->pnext != A.ptail)        //copy all item in data structure
	{
		temp = temp->pnext;
		new_item->pnext = new Item{ *(temp->ps) };
		new_item->pnext->pprev = new_item;
		new_item->pprev = temp->pprev;
		new_item = new_item->pnext;
	}
	new_item->pnext = new Item{ *(A.ptail->ps) };   //save ptail
	new_item->pnext->pprev = new_item;
	ptail = new_item->pnext;
	phead->pprev = ptail;
	ptail->pnext = phead;

	return *this;
}

std::ostream& operator<<(std::ostream& os, APDS& input)      //display our data structure
{
	os << "Name: " << input.name << std::endl;
	os << "Capacity: " << input.capacity << std::endl;
	os << "Size: " << input.size << std::endl;
	os << std::setw(20) << "N" << std::setw(20) << "ID" << std::setw(20) << "Homework" << std::setw(20);
	os << "MidProject" << std::setw(20) << "MidExam" << std::setw(20) << "Party" << std::setw(20);
	os << "Value" << std::endl;

	APDS::Item* temp{ input.phead }; //first student

	for (size_t i{}; i < input.size; i++)
	{
		os << std::setw(20) << i + 1 << std::setw(20) << temp->ps->getID() << std::setw(20) << temp->ps->getHomework();
		os << std::setw(20) << temp->ps->getMidtermProject() << std::setw(20) << temp->ps->getMidtermExam();
		os << std::setw(20) << temp->ps->getParty() << std::setw(20) << temp->ps->value() << std::endl;
		temp = temp->pnext;
	}

	return os;   //return out put
}
