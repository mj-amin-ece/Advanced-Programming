CXX = g++
CXXFLAGS = -std=c++17 -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++17 -Ih -pthread
OBJECTS = ./obj/apmidterm.o ./obj/main.o ./obj/apmidterm_unittest.o ./obj/exponentialstudent.o ./obj/normalstudent.o ./obj/student.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/apmidterm.o: ./cpp/apmidterm.cpp
	$(CXX) $(CXXFLAGS) ./cpp/apmidterm.cpp -o ./obj/apmidterm.o
./obj/apmidterm_unittest.o: ./cpp/apmidterm_unittest.cpp
	$(CXX) $(CXXFLAGS) ./cpp/apmidterm_unittest.cpp -o ./obj/apmidterm_unittest.o
./obj/main.o: ./cpp/main.cpp ./h/apqueue.h
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/student.o: ./cpp/student.cpp
	$(CXX) $(CXXFLAGS) ./cpp/student.cpp -o ./obj/student.o
./obj/normalstudent.o: ./cpp/normalstudent.cpp
	$(CXX) $(CXXFLAGS) ./cpp/normalstudent.cpp -o ./obj/normalstudent.o
./obj/exponentialstudent.o: ./cpp/exponentialstudent.cpp
	$(CXX) $(CXXFLAGS) ./cpp/exponentialstudent.cpp -o ./obj/exponentialstudent.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
