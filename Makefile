#
# Scuffed since I dont know make very well but works
#

COMPILER := g++
CVERSION := -std=c++20
CFLAGS := -g -O3
EXECUTABLENAME := runner

standard:
	@mkdir -p build
	cd build; \
	$(COMPILER) $(CFLAGS) -I ./../include*.cpp ../src/*.cpp $(CVERSION) -o $(EXECUTABLENAME)

clean:
	rm -f -r build/*