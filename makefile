.PHONY: launcher library all clean

launcher:
	bcc32x -g -tW util/*.cpp -n bin -o bin/NTLauncher.exe

library:
	bcc32x --jobs=8 -std=c++1y -g -tWD src/*.cpp src/Delphi/*.cpp src/OpenGL/*.cpp src/Nostale/*.cpp -n bin -o bin/NTLibrary.dll

all: launcher library

clean:
	del /f /q bin\*
	