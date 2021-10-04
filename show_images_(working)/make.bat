@REM call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64

cl /Zi /std:c++latest /I "include\SDL2" "show_images\show_images.cpp" /link "build_win64\SDL2.lib" "build_win64\SDL2main.lib" "build_win64\SDL2_image.lib" "build_win64\SDL2_mixer.lib" "build_win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"build_win64\show_images.exe"

del *.manifest *.ilk *.obj *.pdf *.idb *.pdb 
