@echo off
IF "%vcvarsall_has_been_run%"=="" (
    SET vcvarsall_has_been_run=1
    call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

cl -Zi /I "include" 04_key_presses\04_key_presses.cpp /link "lib\SDL2.lib" "lib\SDL2main.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS
del *.manifest *.ilk *.obj *.pdf *.idb *.pdb


REM # HELP
REM subsystem can also be console or posix e.g. /SUBSYSTEM:CONSOLE . more info https://docs.microsoft.com/en-us/cpp/build/reference/subsystem-specify-subsystem?view=vs-2019
REM handmade hero with simple windows build command https://youtu.be/Ee3EtYb8d1o?t=3921