TARGET = test
SRC = test.c LinkedList.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ) Makefile
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

Makefile.deps: $(SRC) Makefile
	$(CC) -MM $(SRC) > $@

clean: Makefile
	$(RM) -f $(TARGET) $(OBJ) Makefile.deps

-include Makefile.deps
