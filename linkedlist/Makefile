TARGET = test
SRC = test.c
OBJ = $(SRC:.c=.o) ../contrib/cutest/CuTest.o
CFLAGS = -I../contrib/

$(TARGET): $(OBJ) Makefile
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

Makefile.deps: $(SRC) Makefile
	$(CC) -MM $(SRC) > $@

clean: Makefile
	$(RM) -f $(TARGET) $(OBJ) Makefile.deps

-include Makefile.deps
