@REM You have to call these things first
@REM call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
@REM SET PATH=%PATH%;c:\nick\sdl_cross_platform\lib_win64

cl /I "include" 05_optimized_surface_loading_and_soft_stretching\05_optimized_surface_loading_and_soft_stretching.cpp /link "lib_win64\SDL2.lib" "lib_win64\SDL2main.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS 

@REM To set the output file path use the following option
@REM  /OUT:"05_optimized_surface_loading_and_soft_stretching.exe"

@REM del *.manifest *.ilk *.obj *.pdf *.idb *.pdb
