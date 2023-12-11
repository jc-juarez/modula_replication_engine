# *************************************
# Modula Replication Engine
# Build
# 'Makefile'
# Author: jcjuarez
# *************************************

modula: main.o modula.o filesystem_monitor.o directory.o logger.o utilities.o thread_pool.o replication_engine.o replication_manager.o
	-rm -r build
	mkdir build
	g++ -std=c++20 -g main.o modula.o filesystem_monitor.o directory.o logger.o utilities.o thread_pool.o replication_engine.o replication_manager.o -o ./build/modula -pthread
	@echo "Modula build succeeded."
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

replication_engine.o: ./replication_engine.cc
	g++ -std=c++20 -g -c ./replication_engine.cc -pthread

replication_manager.o: ./replication_manager.cc
	g++ -std=c++20 -g -c ./replication_manager.cc -pthread

clean:
	-rm *.o
	-rm -r build
