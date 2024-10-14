CXX = g++
CXXFLAGS = -std=c++17 -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++17 -Ih -pthread
OBJECTS = ./obj/aphw3.o ./obj/main.o ./obj/aphw3_unittest.o ./obj/Matrix.o ./obj/result.o ./obj/dataset.o ./obj/neuralnet.o
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/aphw3.o: ./cpp/aphw3.cpp
	$(CXX) $(CXXFLAGS) ./cpp/aphw3.cpp -o ./obj/aphw3.o
./obj/aphw3_unittest.o: ./cpp/aphw3_unittest.cpp
	$(CXX) $(CXXFLAGS) ./cpp/aphw3_unittest.cpp -o ./obj/aphw3_unittest.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
./obj/Matrix.o: ./cpp/Matrix.cpp
	$(CXX) $(CXXFLAGS) ./cpp/Matrix.cpp -o ./obj/Matrix.o
./obj/dataset.o: ./cpp/dataset.cpp
	$(CXX) $(CXXFLAGS) ./cpp/dataset.cpp -o ./obj/dataset.o
./obj/result.o: ./cpp/result.cpp
	$(CXX) $(CXXFLAGS) ./cpp/result.cpp -o ./obj/result.o
./obj/neuralnet.o: ./cpp/neuralnet.cpp
	$(CXX) $(CXXFLAGS) ./cpp/neuralnet.cpp -o ./obj/neuralnet.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
