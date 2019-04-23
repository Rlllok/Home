CC=gcc
OBJECTS=main.o creatMatrix.o printMatrix.o lastMax.o

.PHONY:clean

test: $(OBJECTS)
	$(CC)  -g $^ -o test

%.o: %.c
	$(CC) -g -c $^ -o $@

clean:
	rm -f *.o test

# all: test main.o creatMatrix.o printMatrix.o
# ssss	$(CC) -c lastMax.c -o lastMax.o
