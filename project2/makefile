CXX = g++
CXXFLAGS = -Wall

proj2: Chemist.o Lab.o Substance.h proj2.cpp
	$(CXX) $(CXXFLAGS) Chemist.o Substance.h Lab.o proj2.cpp -o proj2

Lab.o: Chemist.o Substance.h Lab.cpp Lab.h
	$(CXX) $(CXXFLAGS) -c Lab.cpp

Chemist.o: Chemist.h Chemist.cpp Substance.h
	$(CXX) $(CXXFLAGS) -c Chemist.cpp

clean:
	rm *.o*
	rm *~ 

run:
	./proj2
