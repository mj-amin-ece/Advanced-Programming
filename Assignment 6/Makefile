CXX = g++
CXX_FLAGS = -std=c++17 -Wall -I h -I /usr/local/include/gtest/ -c
LXX_FLAGS = -std=c++17 -pthread
TARGET = main
GTEST = /usr/local/lib/libgtest.a
OBJECTS = obj/main.o ./obj/aphw6.o ./obj/food.o ./obj/basicGoods.o ./obj/appliance.o ./obj/Storehouse.o ./obj/productID.o ./obj/product.o ./obj/material.o ./obj/customer.o ./obj/realCustomer.o ./obj/legalCustomer.o


$(TARGET): $(OBJECTS)
	$(CXX) $(LXX_FLAGS) $(OBJECTS) $(GTEST) -o $(TARGET)

./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/main.cpp -o $@

./obj/aphw6.o: ./cpp/aphw6_unittests.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/aphw6_unittests.cpp -o $@

./obj/basicGoods.o: ./cpp/basicGoods.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/basicGoods.cpp -o $@

./obj/food.o: ./cpp/food.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/food.cpp -o $@
	
./obj/appliance.o: ./cpp/appliance.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/appliance.cpp -o $@
	
./obj/Storehouse.o: ./cpp/Storehouse.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/Storehouse.cpp -o $@
	
./obj/productID.o: ./cpp/productID.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/productID.cpp -o $@

./obj/product.o: ./cpp/product.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/product.cpp -o $@
	
./obj/material.o: ./cpp/material.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/material.cpp -o $@
	
./obj/customer.o: ./cpp/customer.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/customer.cpp -o $@

./obj/realCustomer.o: ./cpp/realCustomer.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/realCustomer.cpp -o $@

./obj/legalCustomer.o: ./cpp/legalCustomer.cpp
	$(CXX) $(CXX_FLAGS) ./cpp/legalCustomer.cpp -o $@
clean:
	rm -f $(TARGET) $(OBJECTS)
