<center>
<h1>
In The Name Of ALLAH
</h1>
<h2>
Advanced Programming - Homework 1
</h2>
<h2>
Dr.Amir Jahanshahi
</h2>
<h3>
Deadline: Friday, 9 Esfand - 23:00
</center>

#  Introduction

In this homework, you're gonna code a program to estimate grade of a student in Dr.Jahanshahi's Advanced Programming course! Isn't that amazing?!

After hours of analysis, we found that grade of a student in this course is effected by the following factors:


1.   Attention in the class (Between 0 and 1)
2.   Attention in the TA class (Between 0 and 1)
3.   Hours of coding and practicing in the week
4.   Hours of studing and reading books in the week
5.   Previous background (Between 0 and 1)
6.   Talent (Between 0 and 1)

As a professional programmer, you're supposed to code something that, by learning from previous students and their grades, estimates grade of a new student (maybe yourself!) by having these factors of him or her!

<img src="staff/MEME.jpg" width="400" class="center" />

# Importing Data
Data of previous students is gathered in **AP-Data.csv**. First of all, implement **getData** function such that it gets the path to the data file and returns a vector consisting of vectors of type double for data given. Each member of this returned vector, is itself a vector consisting of the features of a student. In the AP-Data file, each row is the information of a student. The first 6 numbers of each row are the 6 factors told above and the last number is the grade of the student.

For example, one of the rows of this file is

0.9, 0.9, 10, 3, 0.4, 0.6, 15

So this row is about a student who had a good attention in classes and coded about 10 hours a week (not counting his time on homeworks!) but had little time reading and so on. Finally he got a high grade! 

In your returning vector, each element is itself a vector representing each student. In the vector of each student you must enter a **1** in the first place and after that the 6 parameters and the grade. So your vector for the above student should be like the following.

1, 0.9, 0.9, 10, 3, 0.4, 0.6, 15

Don't forget to divide the 2 features of hours (feature3 and feature4) by 100 to normalize them. It will make your convergence way too fast!

Prototype for your function is
``` c++
std::vector <std::vector <double >> getData(const char*);
```

# Displaying Data
Time for displaying imported data in a beautiful way! Implement **displayDataset** function to do this. 

``` c++
void displayDataset(std::vector <std::vector <double >>);
```
Your output should look like this...

<img src="staff/F1.PNG" width="800" />

# Estimator Function
For estimating the grade, we assume that the grade is a linear function of the above factors. So it can be parameterized by

<img src="staff/eqn1.png" width="300" />

where x_0 is the **1** element you took in the first place of each students vector and x_1 to x_6 are the above factors. For having a reasonable estimation, we must just find appropriate values for w's (weights). Now implement **grade** function. It gets a vector of student features and a vector of weights and returns the estimated grade from the above formula. Prototype is 

``` c++
double grade(std::vector <double > w, std::vector <double > x);
```

# Cost Function
By having data of previous students, we form the following cost function.

<img src="staff/eqn2.png" width="400" />

**m** is the number of students in the dataset, **x**^(i) is the vector of features correspondeing to the i-th student **y^(i)** is the grade of the $i^{th}$ student. As you can see from this function, if you estimate grades properly, this function will get closer and closer to zero. Conversely, if your estimation isn't good enough, the cost function would blow up. So by minimizing this function and finding appropriate weights (w's) we can hope to have a good estimator. Isn't that brilliant?! 

Now, implement **J** function such that it gets the weights vector and the vector of data (returned from getData function) and returns the cost function computed from the above formula with the following prototype.

```c++
double J(std::vector<double>, std::vector<std::vector<double>>);
```

#  Finding Appropriate Weights
It suffices now to find the weights that minimize the cost function so that we can hope to have a good estimator! As you now, to minimize a function, we can start from an arbitrary point and in each step, go in the opposite direction of the gradient at that point. First of all, we must find the partial derivative of the cost function with respect to each weight.

<img src="staff/eqn3.png" width="600" />

Now for minimizing the function, we use the following formula.

<img src="staff/eqn4.png" width="250" />

In this relation, \alpha is the step size and is known as **learning rate**. It usually is a small positive constant number less 1 like 0.01 or 0.001. Actually, by selecting a proper learning rate, the above procedure will run iteratively so that our cost function be minimized more and more and we get the appropriate weights.

Now you're supposed to implement the **train** function to do the above procedure. Arguments of the train function are


*   **data**:  Data of previous students
*   **w**:  Initial weights vector
*   **alpha**:  Learning rate. Default value = 0.01
*   **max_iters**:  Maximum no iterations to do the following procedure. Default value = 500
*   **min_cost**:  Minimum cost function to stop the iterations. If the cost function in an iteration reaches this value, the iterations should stop. Default value = 0.01
*   **verbose**:  If this argument is 1, in each iteration you must print last value of the cost function, current value of cost function in a beautiful manner. Default value = 0

In the end it must return the final weights it has obtained.

``` c++
std::vector<double> train(std::vector<std::vector<double>>, std::vector<double>, double, size_t, double, bool);
```

# Displaying Output
Now implement **displayOutput**. It gets data of previous students and the weight vector obtained from the **train** function. It must print the actual grade and the estimated grade of each student in each row in a beautiful manner like the following figure.

<img src="staff/F2.PNG" width="800" />

# Saving and Loading Weights
Write **Save** and **Load** functions to be able to save and load the weights vector you got from the **train** function. **Save** gets the weights vector and a name and saves the weights in a file with given name in the *csv* format. **Load** gets the name of the file and return a vector containing the weights.
```c++
void save(std::vector<double>, const char*);
```
```c++
std::vector<double> load(const char*);
```

# Prediction
Last step is in front of you. Implement **predict** function such that it gets features of a new student and the weights obtained from the **train** function and predicts his or her grade. Your function should get features from user in proper messages.

For a hard working or lazy student your function may estimate grades more than 20 or less than 0. What would you do to solve this?

```c++
void predict(std::vector<double>);
```
# main File
You must not alter the main file at all. Just write all your codes in the **aphw1.cpp** and **aphw1.h**. Good luck!

<img src="staff/MEME2.jpg" width="500" />
