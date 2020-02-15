WINDOWSARGS = -static-libgcc -static-libstdc++
WIN32 = i686-w64-mingw32-
WIN64 = x86_64-w64-mingw32-
SDL2ARGS=-lSDL2

all :
	make release/main.exe WIN32='' WIN64='' WINDOWSARGS=''  INCLUDEDIR='' LIBDIR=''
win :
	make release/main.exe WIN32='i686-w64-mingw32-' WIN64='x86_64-w64-mingw32-' WINDOWSARGS='-static-libgcc -static-libstdc++' INCLUDEDIR='-I ./include' LIBDIR='-L ./lib'

clean:
	rm obj/*.o
	rm release/*.exe




release/main.exe: obj/main.o obj/voiture.o
	$(WIN32)g++ -Wall obj/main.o obj/voiture.o $(SDL2ARGS) $(WINDOWSARGS) $(INCLUDEDIR) $(LIBDIR) -o release/main.exe

obj/main.o  : src/main.cpp
	$(WIN32)g++ -Wall src/main.cpp $(SDL2ARGS) $(WINDOWSARGS) $(INCLUDEDIR) $(LIBDIR) -c -o obj/main.o

obj/voiture.o : src/voiture.cpp
	$(WIN32)g++ -Wall src/voiture.cpp $(WINDOWSARGS) $(INCLUDEDIR) $(LIBDIR) -c -o obj/voiture.o
