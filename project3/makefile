CXX = g++
CXXFLAGS = -Wall -g
IODIR = ../../proj3_IO/
proj3: Route.o Port.o Navigator.o proj3.cpp 
	$(CXX) $(CXXFLAGS) Route.o Port.o Navigator.o proj3.cpp -o proj3

Navigator.o: Port.o Route.o Navigator.h Navigator.cpp
	$(CXX) $(CXXFLAGS) -c Navigator.cpp

Route.o: Port.o Route.h Route.cpp
	$(CXX) $(CXXFLAGS) -c Route.cpp

Port.o: Port.h Port.cpp
	$(CXX) $(CXXFLAGS) -c Port.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj3 proj3_data.txt

run1:
	./proj3 proj3_data.txt

val1:
	valgrind ./proj3 proj3_data.txt

submit:
	cp Port.h Port.cpp Route.h Route.cpp Navigator.h Navigator.cpp proj3.cpp ~/cs202proj/proj3

ta1:
	valgrind ./proj3 proj3_ta1.txt
