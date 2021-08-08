INCLUDES= -I ./include
FLAGS= -g -std=c++20 -Wall -pedantic
CXX=g++

OBJECTS=./build/apple.o ./build/worm.o
all: ${OBJECTS}
	${CXX} ${FLAGS} ${INCLUDES} ./src/main.cpp ${OBJECTS} -lSDL2main -lSDL2 -o ./bin/main

./build/apple.o:src/apple.cpp
	${CXX} ${FLAGS} ${INCLUDES} ./src/apple.cpp -c -o ./build/apple.o

./build/worm.o:src/worm.cpp
	${CXX} ${FLAGS} ${INCLUDES} ./src/worm.cpp -c -o ./build/worm.o

clean:
	rm -rf build/*

run:
	bin/main
