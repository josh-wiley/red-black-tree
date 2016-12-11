# Variables.
CC = g++
STD = -std=c++14
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
OFLAGS = -o PA07


# Executable.
PA07: PA07.o data_generator.o
	$(CC) $(STD) $(LFLAGS) PA07.o data_generator.o $(OFLAGS)


# PA07.
PA07.o: src/PA07.cpp src/utils/data_generator.h
	$(CC) $(STD) $(CFLAGS) src/PA07.cpp


# Data generator.
data_generator.o: src/utils/data_generator.h src/utils/data_generator.cpp
	$(CC) $(STD) $(CFLAGS) src/utils/data_generator.cpp


# Clean.
clean:
	rm -rf *.o PA07
