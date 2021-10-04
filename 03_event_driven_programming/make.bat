call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
cl -Zi /I "include" 03_event_driven_programming\03_event_driven_programming.cpp /link "lib\SDL2.lib" "lib\SDL2main.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS
del *.manifest *.ilk *.obj *.pdf *.idb *.pdb
