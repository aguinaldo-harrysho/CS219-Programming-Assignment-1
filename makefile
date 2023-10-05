armSim: driver.o
	g++ -o armSim driver.o

driver: driver.cpp simulator.hpp
	g++ -c driver.cpp

clean:
	rm *.o
	rm armSim

