#include"apqueue.h"

template<typename T>
APQueue<T>::Item::Item(T& S)
{
	pvalue = &S;             //save object
	pnext = nullptr;         //initialize pnext
}

template<typename T>
APQueue<T>::APQueue(std::vector<T> &input_vector)   //constructor
{
	size = {};          //initialize size
	ptail = nullptr;    //initialize ptail
	phead = nullptr;    //initialize phead

	for (size_t i = 0; i < input_vector.size(); i++)  //push object to queue
		enqueue(input_vector[i]);
}

template<typename T>
APQueue<T>::APQueue(std::vector<T> &&input_vector_in) //constructor for rvalue
{
	static std::vector<T> input_vector{input_vector_in}; //to save input object

	size = {};         //initialize size
	ptail = nullptr;   //initialize ptail
	phead = nullptr;   //initialize phead
	for (size_t i = 0; i < input_vector.size(); i++) //push object to queue
		enqueue(input_vector[i]);
}

template<typename T>
APQueue<T>::~APQueue() //destructor
{                      //remove all item in queue
	if(size)
	{
		Item* temp{ phead };
		Item* temp_next{ temp->pnext };
		for (size_t i = 0; i < size-1; i++)
		{
			delete temp;
			temp = temp_next;
			temp_next = temp->pnext;
		}
		delete ptail;
	}
}

template<typename T>
void APQueue<T>::enqueue(T& in)    //get object in queue
{
	Item* new_input{ new Item{in} }; //create new item with input

	if (size > 0)
		ptail->pnext = new_input;
	ptail = new_input;
	if (size == 0)   //for save phead
		phead = new_input;
	size++;
}

template<typename T>
APQueue<T>* APQueue<T>::enqueue(T&& in) //get object in queue for rvalue
{
	Item* new_input{ new Item{in} };    //create new item with input

	if (size > 0)
		ptail->pnext = new_input;
	ptail = new_input;
	if (size == 0)               //for save phead
		phead = new_input;
	size++;

	return this;
}

template<typename T>
T APQueue<T>::dequeue() //removes the first thing in queue
{
	if (size == 0)  //If the queue is empty return 0
	{
		ptail = phead = nullptr;
		std::cout<<"queue is empty"<<std::endl;
		return 0;
	}
	//removes last data and update adress
	Item* temp{ phead->pnext };
	T item{ *(phead->pvalue) };

	delete phead;   //delete phead
	phead = temp;
	size--;    //decrease size queue

	return item;
}

template<typename T>
void APQueue<T>::show()       //show detail
{
	Item* temp{ phead };

	std::cout << "APQueue of size: " << size << std::endl;
	for (size_t i = 0; i < size; i++)
	{
		std::cout << std::setw(5) << "NO : " << i + 1 << std::setw(8) << *(temp->pvalue) << std::endl;
		temp = temp->pnext;
	}
}

template<typename T>    //operator[]
T APQueue<T>::operator[](size_t j)
{
	Item* temp{ phead };

	for (size_t i = 0; i < size; i++)
	{
		if (!(i - j))
			return *(temp->pvalue);
		temp = temp->pnext;
	}
	std::cout<<"object not fined!"<<std::endl;  //if i-th is out of the range
	return 0;
}

//specializations 

inline APQueue<std::unique_ptr<Student>>::Item::Item(Student*& S)
{
	pvalue = S;        //save object
	pnext = nullptr;  //initialize pnext
}

inline APQueue<std::unique_ptr<Student>>::APQueue(std::vector<std::unique_ptr<Student>>&& input_vector_in)   //constructor for rvalue
{
	static std::vector<Student*> input_vector(input_vector_in.size(),nullptr);     //to save input object

	size = {};         //initialize size
	ptail = nullptr;   //initialize ptail
	phead = nullptr;   //initialize phead
	for (size_t i = 0; i < input_vector.size(); i++)
	{
		input_vector[i] = input_vector_in[i].release();  //save object
		enqueue(input_vector[i]);    //get in queue
	}
}

inline APQueue<std::unique_ptr<Student>>::~APQueue()   //destructor
{                                                      //remove all item in queue
	if (size)
	{
		Item* temp{ phead };
		Item* temp_next{ temp->pnext };
		for (size_t i = 0; i < size - 1; i++)
		{
			delete temp;
			temp = temp_next;
			temp_next = temp->pnext;
		}
		delete ptail;
	}
}

inline void APQueue<std::unique_ptr<Student>>::enqueue(Student*& in)  //get object in queue
{
	Item* new_input{ new Item{in} };  //create new item with input

	if (size > 0)
		ptail->pnext = new_input;
	ptail = new_input;
	if (size == 0)   //save phead
		phead = new_input;
	size++;
}

inline void APQueue<std::unique_ptr<Student>>::show()  //show detail
{
	Item* temp{ phead };

	std::cout << "APQueue of size: " << size << std::endl;
	for (size_t i{}; i < size; i++)
	{
		std::cout << std::setw(5) << "NO : " << i + 1 << std::setw(6) << ", Name: " << temp->pvalue->getName() << std::endl;
		std::cout << "\t\t  " << "Pr{A Grade} =" << std::setprecision(5) << std::fixed << temp->pvalue->between(17, 20);
		std::cout << "\t\t  " << "Pr{B Grade} =" << temp->pvalue->between(14, 17);
		std::cout << "\t\t  " << "Pr{C Grade} =" << temp->pvalue->between(10, 14);
		std::cout << "\t\t  " << "Pr{D Grade} =" << temp->pvalue->between(0, 10) << std::endl;
		temp = temp->pnext;
	}
}
