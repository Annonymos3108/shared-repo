xcopy /s /Y "C:\Program Files\SFML-2.5.1\bin\sfml-window-2.dll" .\bin\
xcopy /s /Y "C:\Program Files\SFML-2.5.1\bin\sfml-system-2.dll" .\bin\
xcopy /s /Y "C:\Program Files\SFML-2.5.1\bin\sfml-graphics-2.dll" .\bin\
mkdir .\bin\Polyhedron_Lightning
mingw32-make
pause