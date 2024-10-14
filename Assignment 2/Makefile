CXX = g++
CXXFLAGS = -std=c++17 -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++17 -Ih -pthread
OBJECTS = ./obj/aphw2.o ./obj/main.o ./obj/aphw2_unittest.o ./obj/Matrix.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/aphw2.o: ./cpp/aphw2.cpp
	$(CXX) $(CXXFLAGS) ./cpp/aphw2.cpp -o ./obj/aphw2.o
./obj/aphw2_unittest.o: ./cpp/aphw2_unittest.cpp
	$(CXX) $(CXXFLAGS) ./cpp/aphw2_unittest.cpp -o ./obj/aphw2_unittest.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/Matrix.o: ./cpp/Matrix.cpp
	$(CXX) $(CXXFLAGS) ./cpp/Matrix.cpp -o ./obj/Matrix.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
