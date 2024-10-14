CXX = g++
CXXFLAGS = -std=c++17 -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++17 -Ih -pthread
OBJECTS = ./obj/aphw4.o ./obj/main.o ./obj/aphw4_unittest.o ./obj/student.o ./obj/apds.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/aphw4.o: ./cpp/aphw4.cpp
	$(CXX) $(CXXFLAGS) ./cpp/aphw4.cpp -o ./obj/aphw4.o
./obj/aphw4_unittest.o: ./cpp/aphw4_unittest.cpp
	$(CXX) $(CXXFLAGS) ./cpp/aphw4_unittest.cpp -o ./obj/aphw4_unittest.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/student.o: ./cpp/student.cpp
	$(CXX) $(CXXFLAGS) ./cpp/student.cpp -o ./obj/student.o
./obj/apds.o: ./cpp/apds.cpp
	$(CXX) $(CXXFLAGS) ./cpp/apds.cpp -o ./obj/apds.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
