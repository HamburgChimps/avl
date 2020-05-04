INCLUDE=./include
DEPS=$(wildcard ./deps/*.c)
OBJ=hc_avl_test
SRC=$(wildcard ./src/*.c)

.PHONY=clean

all:
	gcc -I $(INCLUDE) -o $(OBJ) \
		$(DEPS) \
		$(SRC)

clean:
	rm -rf $(OBJ)
