@REM You have to call these things first
@REM call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
@REM SET PATH=%PATH%;c:\nick\sdl_cross_platform\lib_win64

cl /I "include" "sdl\1_open_a_window.c" /link "lib_win64\SDL2.lib" "lib_win64\SDL2main.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS 

