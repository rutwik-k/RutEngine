@echo off
set compile_flags= -nologo -DBUILD_WIN32=1 -DRENDERER_OPENGL=1 /Zi -I ../code/
set linker_flags= user32.lib gdi32.lib opengl32.lib winmm.lib

if not exist build mkdir build
pushd build
cl %compile_flags% ../code/platform/win32/win32_main.cpp /link %linker_flags%
popd