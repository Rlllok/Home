CC=g++
OBJECTS=main.o Cfile.o
.PHONY: clean run

all:lab2

lab2: $(OBJECTS)
	$(CC) -o lab2 $(OBJECTS)

%.o: %.cpp List.h Iterator.h
	$(CC) -c $< -o $@

clean:
	rm $(OBJECTS)

run: lab2
	./lab2