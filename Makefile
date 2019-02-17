CC = g++
CFLAGS = -g3
SDIR = src
BDIR = bin

IDIR = include
_DEPS = classes.h plants.h animals.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

ODIR = build
_OBJ = main.o classes.o plants.o animals.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@  $< $(CFLAGS)

output: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o