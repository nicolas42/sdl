@echo off
IF "%vcvarsall_has_been_run%"=="" (
    SET vcvarsall_has_been_run=1
    call "c:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
)

cl /Zi /I "include\SDL2" "lazyfoo_examples.cpp" /link "build_win64\SDL2.lib" "build_win64\SDL2main.lib" "build_win64\SDL2_image.lib" "build_win64\SDL2_mixer.lib" "build_win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"build_win64\lazyfoo_examples.exe"

cl /Zi /I "include\SDL2" "sobel_edge_detection.cpp" /link "build_win64\SDL2.lib" "build_win64\SDL2main.lib" "build_win64\SDL2_image.lib" "build_win64\SDL2_mixer.lib" "build_win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"build_win64\sobel_edge_detection.exe"

cl /Zi /I "include\SDL2" "render_random_pixels.cpp" /link "build_win64\SDL2.lib" "build_win64\SDL2main.lib" "build_win64\SDL2_image.lib" "build_win64\SDL2_mixer.lib" "build_win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"build_win64\render_random_pixels.exe"

cl /Zi /I "include\SDL2" "show_mandelbrot_bw.cpp" /link "build_win64\SDL2.lib" "build_win64\SDL2main.lib" "build_win64\SDL2_image.lib" "build_win64\SDL2_mixer.lib" "build_win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"build_win64\show_mandelbrot_bw.exe"

cl /Zi /I "include\SDL2" "render_text.cpp" /link "build_win64\SDL2.lib" "build_win64\SDL2main.lib" "build_win64\SDL2_image.lib" "build_win64\SDL2_mixer.lib" "build_win64\SDL2_ttf.lib" "kernel32.lib" "user32.lib" "shell32.lib" /SUBSYSTEM:WINDOWS /OUT:"build_win64\render_text.exe"

del *.manifest *.ilk *.obj *.pdf *.idb *.pdb 
del build_win64\*.manifest build_win64\*.ilk build_win64\*.obj build_win64\*.pdf build_win64\*.idb build_win64\*.pdb


