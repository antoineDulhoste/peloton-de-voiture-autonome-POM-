WINDOWSARGS = -static-libgcc -static-libstdc++
WIN32 = i686-w64-mingw32-
WIN64 = x86_64-w64-mingw32-

all :
	make release/main.exe WIN32='' WIN64='' SDL2ARGS='-lSDL2' INCLUDEDIR='' LIBDIR=''
win :
	make release/main.exe WIN32='i686-w64-mingw32-' WIN64='x86_64-w64-mingw32-' SDL2ARGS='-static-libgcc -static-libstdc++ -lSDL2' INCLUDEDIR='-I ./include' LIBDIR='-L ./lib'

clean:
	rm obj/*.o
	rm release/*.exe




release/main.exe: obj/main.o
	$(WIN32)g++ -Wall obj/main.o $(SDL2ARGS) $(INCLUDEDIR) $(LIBDIR) -o release/main.exe

obj/main.o  : src/main.cpp
	$(WIN32)g++ -Wall src/main.cpp $(SDL2ARGS) $(INCLUDEDIR) $(LIBDIR) -c -o obj/main.o
