all: build

build:
	clang++ -std=c++17 -I./SDL2/include/ -lSDL2main -lSDL2 linal/*.cpp engine/*.hpp engine/*.cpp math/*.hpp math/*.cpp
	mkdir -p ./bin
	mv ./a.out ./bin/linal
