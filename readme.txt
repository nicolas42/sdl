Cross platform SDL
----------------------------

This is an attempt to make a cross platform SDL repo full of examples.
The windows builds use batch files and 


executables go into the build_win64 directory with the DLLs

gotta run vcvarsall.bat before visual studio will work on the command line 


Visual studio on the command line 
----------------------------------------------------------------------

To compile a project with visual studio from the command line you first have to call a script called vcvarsall 
and pass it either x86 or x64 depending on whether you want visual studio to compile in 32 or 64 bit mode.
They move it every time they update visual studio unfortunately.

call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64


After this you can call visual studio using the cl command  e.g.

cl myprogram.c 

cl -Zi /I "include" main.cpp /link "lib\SDL2.lib" "lib\SDL2main.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS 

It'll createt a bunch of files that you might not want to look at.

del *.manifest *.ilk *.obj *.pdf *.idb *.pdb


DLL Locations
---------------------------------------

Windows searches for DLL files in the directory where they're executed from.  Then it'll search all the PATH directories.

The path variable can be updated like this 

SET PATH=%PATH%;c:\nick\sdl_cross_platform\lib_win64

Unfortunately this appears not to work when executables are launched through a GUI like windows explore :(



