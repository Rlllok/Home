CC=g++
OBJECTS=main.o Analyzer.o

.PHONE:clean

all: LeksAnalis

clean:
	rm -f *.o LeksAnalis

LeksAnalis: $(OBJECTS)
	$(CC) $^ -o LeksAnalis

%.o: %.cpp
	$(CC) -c $^ -o $@
