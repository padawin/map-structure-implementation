# Map (associative array) implementation

C Implementation of a map structure (associative array)

The current features are:
- search an item from a key
- insert an item
- update an item
- delete an item

A test file is provided as example.

## Usage

Compile it:
```
make
```

Once it is compiled, you can run an example binary:
```
./map-examples
```

Or install the library to use it in your own projects:
```
make install
```

By default, the libmap.so will be installed in /usr/lib and the map.h in
/usr/include. Those values can be changed in the Makefile before compiling it
(variables $LIBDIR and $INCLDIR).
