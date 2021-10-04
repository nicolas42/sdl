@echo off
IF "%vcvarsall_has_been_run%"=="" (
    SET vcvarsall_has_been_run=1
    call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

cl /Zi /std:c++latest /I "include\SDL2" "examples/6_show_stb_image_with_sdl.cpp" /link "build_win64\SDL2.lib" "build_win64\SDL2main.lib" "build_win64\SDL2_image.lib" "build_win64\SDL2_mixer.lib" "build_win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"build_win64\6_show_stb_image_with_sdl.exe"



del *.manifest *.ilk *.obj *.pdf *.idb *.pdb 
del build_win64\*.manifest build_win64\*.ilk build_win64\*.obj build_win64\*.pdf build_win64\*.idb build_win64\*.pdb


