PROG   := map-examples
LIB    := map.so
CC     := gcc
CFLAGS := -g -O2 -Wall -Wextra -Wwrite-strings -Wformat=2 -Wconversion -Wmissing-declarations -Wmissing-prototypes
LDFLAGS:=
CCDYNAMICFLAGS := ${CFLAGS} -fPIC
LDDYNAMICFLAGS := -shared

INSTALL=install -D

SRC := $(wildcard *.c)
OBJ := $(patsubst %.c,%.o,$(SRC))
DEP := $(patsubst %.c,%.deps,$(SRC))

BINDIR=$(DESTDIR)/usr/lib

all: $(PROG) $(LIB)

-include $(DEP)

%.deps: %.c
	$(CC) -MM $< >$@

%.o: %.c
	$(CC) $(CCDYNAMICFLAGS) -c -MMD $< -o $@

%.so: %.o
	${CC} ${LDDYNAMICFLAGS} -o $@ $< -o $@

install:
	$(INSTALL) $(LIB) $(BINDIR)/lib$(LIB)

clean:
	rm $(PROG)
	find . -name '*.o' -delete -o -name '*.d' -delete -o -name '*.deps' -delete  -o -name '*.so' -delete

$(PROG): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
