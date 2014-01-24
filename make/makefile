SRC_LIB_FILES := $(shell find ../src/ -type f -name '*.cpp' -not -name 'main.cpp')
VENDOR_LIB_FILES := $(shell find ../vendor/ -type f -name '*.cpp')
OBJ_LIB_FILES := $(shell find . -maxdepth 1 -type f -name '*.o' -not -name 'main.o')
#OBJ_LIB_FILES := $(wildcard *.o)

all: obj

obj:
	@echo "Compiling objects"
	g++ -c -Wall -fpic -I../include -I../vendor $(SRC_LIB_FILES) $(VENDOR_LIB_FILES)
	@echo "Run 'make exec'"
	
exec:
	@echo "Compiling ../bin/libkrafter.so"
	g++ -shared -o ../bin/libkrafter.so $(OBJ_LIB_FILES)
	@echo "Compiling ../bin/krafter"
	g++ -Wall -L../bin -I../include -I../vendor -o ../bin/krafter ../src/main.cpp -lkrafter 
	@echo "All done"

clean:
	rm -rf *.o *.out

