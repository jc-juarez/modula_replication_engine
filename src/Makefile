# *************************************
# Modula Replication Engine
# Utilities
# 'Makefile'
# Author: jcjuarez
# *************************************

modula: main.o modula.o filesystem_monitor.o directory.o logger.o utilities.o thread_pool.o
	-rm -r build
	mkdir build
	g++ -std=c++20 -g main.o modula.o filesystem_monitor.o directory.o logger.o utilities.o thread_pool.o -o ./build/modula -pthread
	rm *.o

main.o: ./main.cc
	g++ -std=c++20 -g -c ./main.cc -pthread

modula.o: ./modula.cc
	g++ -std=c++20 -g -c ./modula.cc -pthread

filesystem_monitor.o: ./filesystem_monitor.cc
	g++ -std=c++20 -g -c ./filesystem_monitor.cc -pthread

directory.o: ./directory.cc
	g++ -std=c++20 -g -c ./directory.cc -pthread

logger.o: ./logger.cc
	g++ -std=c++20 -g -c ./logger.cc -pthread

utilities.o: ./utilities.cc
	g++ -std=c++20 -g -c ./utilities.cc -pthread

thread_pool.o: ./thread_pool.cc
	g++ -std=c++20 -g -c ./thread_pool.cc -pthread

clean:
	-rm *.o
	-rm -r build
