CXX = g++
CXXFLAGS = -Wall -g
IODIR =../../proj5_IO/

proj5: Question.o Lqueue.o Trivia.o proj5.cpp
	$(CXX) $(CXXFLAGS) Trivia.o Question.o Lqueue.cpp proj5.cpp -o proj5

Trivia.o: Trivia.cpp Lqueue.o Question.o
	$(CXX) $(CXXFLAGS) -c Trivia.cpp

Lqueue.o: Lqueue.cpp
	$(CXX) $(CXXFLAGS) -c Lqueue.cpp

Question.o: Question.cpp
	 $(CXX) $(CXXFLAGS) -c Question.cpp

clean:
	rm *.o*
	rm *~ 

string:
	./proj5 proj5_string.txt string

string1:
	valgrind ./proj5 proj5_string.txt string

int:
	./proj5 proj5_int.txt int

int1:
	valgrind ./proj5 proj5_int.txt int

double:
	./proj5 proj5_double.txt double

double1:
	valgrind ./proj5 proj5_double.txt double

lqueue:
	g++ -Wall lqueue_test.cpp Lqueue.cpp -o lqueue_test

test:
	valgrind ./lqueue_test

submit:
	cp Lqueue.cpp Trivia.cpp Question.cpp  proj5.cpp ~/cs202proj/proj5

##Used for grading and testing

copy:
	cp $(IODIR)tf* .

tf1:
	g++ -Wall tf_test.cpp Lqueue.cpp -o tf_test

tf2:
	valgrind ./tf_test

tf3:
	valgrind ./proj5 proj5_data.txt
