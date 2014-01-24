SRC_LIB_FILES := $(shell find src/ -type f -name '*.cpp' -not -name 'main.cpp')
VENDOR_LIB_FILES := $(shell find vendor/ -type f -name '*.cpp')
OBJ_LIB_FILES := $(shell find . -maxdepth 1 -type f -name '*.o' -not -name 'main.o')

all: obj

obj:
	@echo "Compiling objects"
	g++ -c -Wall -fpic -Iinclude -Ivendor $(SRC_LIB_FILES) $(VENDOR_LIB_FILES)
	@echo "Run 'make lib'"
	
lib:
	@echo "Compiling bin/libkrafter.so"
	g++ -shared -o bin/libkrafter.so $(OBJ_LIB_FILES)
	@echo "Run 'make exec'"

exec:
	@echo "Compiling bin/krafter"
	g++ -Wall -Lbin -Iinclude -Ivendor -o bin/krafter src/main.cpp -lkrafter 
	@echo "All done"

clean:
	rm -rf *.o *.out

