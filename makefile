
build:
	bcc32x -tWD src/*.cpp -n bin -o bin/NTLibrary.dll

build2:
	bcc32x -tWD src/MinHook/*.c -n bin -o bin/MinHook.dll

clean:
	del /f /q bin\*