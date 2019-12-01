COMPILER = clang++
COMPILER_ARGS = -lAdvapi32 -std=c++17

build/black-titlebars.exe: objects/main.o
	mkdir -p build
	$(COMPILER) objects/main.o -o build/black-titlebars.exe $(COMPILER_ARGS)

objects/main.o: source/main.cxx
	mkdir -p objects
	$(COMPILER) source/main.cxx -c -o objects/main.o $(COMPILER_ARGS)

rebuild: clean build/black-titlebars.exe

clean:
	rm -rf build
	rm -rf objects