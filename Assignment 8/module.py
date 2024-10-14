from time import time, sleep


def get_column(data, c=0):
    column = []
    for row in data:
        column.append(row[c])
    return column


# Question: Functional Programming 1
def get_column2(data, c=0):
    # retrieving the c-th element of each row 
    return list(map(lambda x: x[c], data))


# Question: Functional Programming 2
def get_split(data, c=0):
    # Using get_column over the list of divided string tokens with split()
    return get_column(list(map(lambda x: x.split(" "), data)), c)


# Question: Decorator 1
def timeit(func, *args):
    def timer(*args):
        # calculating the exec time in seconds
        start = time()
        func(*args)
        end = time()
        return end - start
    return timer


# Question: Decorator 2
def noexcept(func, *args):
    def exception_catcher(*args):
        # Catching any exception
        try:
            a = func(*args)
            return a
        except Exception as e:
            # Printing the exception with its repr function
            print(f'Exception catched: {e.__repr__()}')
    return exception_catcher


@timeit
def random_delay(delay=0):
    """DELAY"""
    sleep(delay)
    return 0


@noexcept
def random_divide(a, b):
    """DIVIDE"""
    return a / b


def static_func():
    """STATIC"""
    static_func.count += 1
    return static_func.count
