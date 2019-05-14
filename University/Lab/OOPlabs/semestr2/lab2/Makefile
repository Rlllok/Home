CC=g++
OBJECTS=main.o Person.o Employee.o Manager.o Database.o
.PHONY: clean run

all:lab2

lab2: $(OBJECTS)
	$(CC) -o lab2 $^

%.o: %.cpp
	$(CC) -c $< -o $@

clean:
	rm $(OBJECTS)

run: lab2
	./lab2