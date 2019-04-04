CC=g++
OBJECTS=main.o CTranslate.o vectorFunctions.o
.PHONY: clean

all:lab1

lab1: $(OBJECTS)
	$(CC) -o lab1 $^

%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm $(OBJECTS)
