call "%VS120COMNTOOLS%..\..\VC\vcvarsall"

mkdir lib
mkdir obj
pushd obj
cl /I F:\libs\openssl-1.0.2d-vs2013\include ^
/I F:\libs\SQLITE3\sqlite\H ^
/I F:\milk\repos\ExcelFormat\include ^
/I F:\libs\koicxx ^
/I C:\Users\milk\Documents\libs\MetaTraderManagerAPI ^
/I F:\libs\MetaTraderServerAPI\include ^
/I C:\Users\milk\Documents\libs\t4b-license\include ^
/I F:\milk\repos\t4b-lib\include ^
/I F:\libs\boost_1_55_0 ^
/I F:\milk\repos\websocketpp ^
/I C:\My_Documents\libs\freetype-2.6\include ^
/I ..\external ^
/D "_UNICODE" ^
/D "UNICODE" ^
/GS ^
/GL ^
/analyze- ^
/W3 ^
/Gy ^
/Zc:wchar_t ^
/EHsc ^
/MT ^
/WX- ^
/Zc:forScope ^
/Gd ^
/Oy- ^
/Oi ^
/Zi ^
/Gm- ^
/O2 ^
/nologo ^
/c ^
..\src\filesystem\file.cpp ^
..\src\transform.cpp ^
..\src\node.cpp ^
..\src\scene.cpp ^
..\src\glextutil.cpp ^
..\src\gfx.cpp ^
..\src\geometrybuffer.cpp ^
..\src\gfxmesh.cpp ^
..\src\gfxs_atom.cpp ^
..\src\gfxs_slot.cpp ^
..\src\gfxs_stage.cpp ^
..\src\gfxshader.cpp ^
..\src\gfxtexture2d.cpp ^
..\src\gfxtarget.cpp ^
..\src\window.cpp ^
..\src\input.cpp ^
..\src\camera.cpp ^
..\src\renderable.cpp
lib /out:"..\lib\libgame.lib" ^
main.obj ^
file.obj ^
transform.obj ^
node.obj ^
scene.obj ^
glextutil.obj ^
gfx.obj ^
geometrybuffer.obj ^
gfxmesh.obj ^
gfxs_atom.obj ^
gfxs_slot.obj ^
gfxs_stage.obj ^
gfxshader.obj ^
gfxtexture2d.obj ^
gfxtarget.obj ^
window.obj ^
input.obj ^
camera.obj ^
renderable.obj
popd