CC=gcc
OBJECTS=main.o creatMatrix.o printMatrix.o lastMax.o

.PHONE:clean

all: test

clean:
	rm -f *.o test

test: $(OBJECTS)
	$(CC) $^ -o test

%.o: %.c
	$(CC) -c $^ -o $@
