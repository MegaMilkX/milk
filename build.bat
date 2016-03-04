call "%VS120COMNTOOLS%..\..\VC\vcvarsall"

mkdir build
pushd build
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
/D "_USING_V110_SDK71_" ^
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
..\src\resource.res ^
..\src\main.cpp ^
..\src\transform.cpp ^
..\src\node.cpp ^
..\src\scene.cpp ^
..\src\glextutil.cpp ^
..\src\gfx.cpp ^
..\src\gfxcamera.cpp ^
..\src\gfxmesh.cpp ^
..\src\gfxtarget.cpp ^
..\src\window.cpp ^
..\src\input.cpp ^
/link ^
/OUT:"game.exe" ^
kernel32.lib ^
user32.lib ^
gdi32.lib ^
winspool.lib ^
comdlg32.lib ^
advapi32.lib ^
shell32.lib ^
ole32.lib ^
oleaut32.lib ^
uuid.lib ^
odbc32.lib ^
odbccp32.lib ^
opengl32.lib ^
freetype26MT.lib ^
/DEBUG ^
/MACHINE:X86 ^
/OPT:REF ^
/SAFESEH ^
/MAP ^
/OPT:ICF ^
/ERRORREPORT:PROMPT ^
/NOLOGO ^
/LIBPATH:"F:\libs\openssl-1.0.2d-vs2013\lib" ^
/LIBPATH:"F:\libs\SQLITE3\Release" ^
/LIBPATH:"F:\milk\repos\ExcelFormat\Release" ^
/LIBPATH:"F:\libs\boost_1_55_0\stage\lib" ^
/LIBPATH:"..\external" ^
/TLBID:1
popd