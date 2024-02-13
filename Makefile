COMPILER := g++
CVERSION := -std=c++20
CFLAGS := -g -O3
EXECUTABLENAME := runner
SRC := ./../src/*.cpp 
INC := ./../include*.cpp

standard:
	@mkdir -p build
	cd build; \
	$(COMPILER) $(CFLAGS) $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)

test:
	@mkdir -p build
	cd build; \
	$(COMPILER) -DTESTMODE $(CFLAGS) $(CVERSION) -I $(INC) $(SRC) -o $(EXECUTABLENAME)

clean:
	rm -f -r build/*