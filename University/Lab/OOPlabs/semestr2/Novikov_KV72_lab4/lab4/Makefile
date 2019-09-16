CC=g++
OBJECTS=main.o TextClasifier.o Sort.o
.PHONY: clean run

all:lab4

lab4: $(OBJECTS)
	$(CC) -o lab4 $(OBJECTS)

%.o: %.cpp 
	$(CC) -c $< -o $@

clean:
	rm $(OBJECTS)

run: lab4
	./lab4