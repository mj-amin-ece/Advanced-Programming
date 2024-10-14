<center>
<h1>
In The Name Of ALLAH
</h1>
<h2>
Advanced Programming - Homework 8
</h2>
<h2>
Dr.Amir Jahanshahi
</h2>
<h3>
Deadline: Friday, 20 Tir
</center>
    
<img src="stuff/f1.jpg" width="500" class="center" />

# Part1: Image Viewer
In this part, you would design and implement a simple image viewer. The requirements are shown on the video file **APHW8.mp4**. You must create something like that shown on the video. Your GUI must be in **gui.ui** and your codes for this part must be in **aphw8.py**.

# Part2
Implement all the codes in `module.py` file. Test case will be in `main.py`.

### Question: Functional programming 1

The following code retrieves column `c` from any matrix `data`:

```
def get_column(data, c=0):
    column = []
    for row in data:
        column.append(row[c])
    return column

```

Please write a consize one liner function `get_column2` doing the same thing. It is not
allowed to use loops, nor list comprehension.

Hint: See functional programming tools in Python: `map filter reduce` and `operator` library

### Question: Functional programming 2

implement another function called `get_split` which retrieves column `c` from the following data:

```
data = [
    "1 2 3 4",
    "5 6 7 8",
    "9 10 11 12"
]
```

Neither loop, nor list comprehension is allowed. Code needs to be consize and readable.

Hint: you might want to use `get_column` function here.

### Question: Decorator 1

Implement `timeit` decorator in such a way that, the decorated function returns the execution time instead of its original return value. e.g.:

```
@timeit
def random_delay(delay=0):
    """DELAY"""
    sleep(delay)
    return 0

delay = 1.5 # e.g.
delay == random_delay(delay) # approximately true
```

Hint: Use `functools` library to keep the **doc** and pass the `unittest`.

### Question: Decorator 2

Define the `random_divide` function as:

```
def random_divide(a, b):
    """DIVIDE"""
    return a / b
```

This function is prone to `ZeroDivision` for obvious reasons. Please implement `noexcept` decorator, in order to catch all the possible exceptions from the decorated function. All exceptions not just `ZeroDivision`. Please note that in case there is any exception, the exception message, type and input arguments to the function should be printed to console:

`args: (1, 0), kwargs: {} -> ZeroDivisionError: division by zero`

The function needs to return `None` in case of exception.

### Question: Decorator 3

Define `static_vars` decorator to add any number of static variables to any function. e.g.,

```
@static_vars(count=0)
def static_func():
    """STATIC"""
    static_func.count += 1
    return static_func.count

static_func() # returns 1
static_func() # returns 2
static_func() # returns 3
```

Please note that any number of static variables could be defined as:

`static_vars(var1=0, var2=2, ...)`

Compared to previous questions, this type of decorator can accept input arguments.

Hint: you can use `setattr` function to add extra attributes to any object. Functions are also objects in functional programming paradigm.

<img src="stuff/f2.jpg" width="550" class="center" />
