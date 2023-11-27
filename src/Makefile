# *************************************
# Modula Replication Engine
# Utilities
# 'Makefile'
# Author: jcjuarez
# *************************************

modula: main.o thread_pool.o
	-rm -r build
	mkdir build
	g++ -std=c++17 main.o thread_pool.o -o ./build/modula -O3 -pthread
	rm *.o

main.o: ./main.cc
	g++ -std=c++17 -c ./main.cc -O3 -pthread

thread_pool.o: ./thread_pool.cc
	g++ -std=c++17 -c ./thread_pool.cc -O3 -pthread

clean:
	-rm *.o
	-rm -r build
