INCLUDEDIR = -I/usr/include
LIBDIR = -L/usr/lib
WINDOWSARGS = -static-libgcc -static-libstdc++
SDL2ARGS = -lSDL2
WIN32 = i686-w64-mingw32-
WIN64 = x86_64-w64-mingw32-


all : obj/main.o
	$(WIN64)g++ -Wall obj/main.o -o release/main.exe

obj/main.o  : src/main.cpp
	$(WIN64)g++ -Wall src/main.cpp -c -o obj/main.o $(SDL2ARGS) $(INCLUDEDIR)

run:
	make
	./release/main.exe

clean:
	rm obj/*.o
	rm release/*.exe
