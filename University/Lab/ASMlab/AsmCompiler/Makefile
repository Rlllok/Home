CC=g++
OBJECTS=main.o Analyzer.o Syntax.o

.PHONY:clean run

all: LeksAnalis


LeksAnalis: $(OBJECTS)
	$(CC) $^ -o LeksAnalis

%.o: %.cpp
	$(CC) -c $^ -o $@

clean:
	rm -f *.o LeksAnalis

run:
	./LeksAnalis