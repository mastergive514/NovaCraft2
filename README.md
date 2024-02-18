# NovaCraft
a CC (Classicube) Plugin made to give you more features :D

# Setup Compiling

1. Download Classicube Source code [here](https://github.com/UnknownShadow200/ClassiCube/archive/refs/heads/master.zip)
2. Download main.c [here](https://raw.githubusercontent.com/mastergive514/NovaCraft2/main/main.c)
3. Extract Classicube source code , and put main.c in classicube-master folder (make sure in classicube-master folder, there src folder)
4. if you have Windows, use [w64devkit](https://github.com/skeeto/w64devkit). if you have Linux, just make sure that u have gcc installed
# Compiling in Windows

1. download Classicube.exe [here](https://www.classicube.net/download/)
2. put Classicube.exe in classicube-master folder
3. open `w64devkit.exe`, cd to your classicube-master folder
4. do `gendef ClassiCube.exe` 
5. do `x86_64-w64-mingw32-dlltool -d ClassiCube.def -l libClassiCube.a -D ClassiCube.exe`

and for compiling , do `x86_64-w64-mingw32-gcc main.c -o novacraft.dll -s -shared -L . -lClassiCube`


# Compiling in Linux
note: you do not need to download Classicube

do `cc main.c -o novacraft.so -shared -fPIC`, and copy and paste `novacraft.so` in classicube plugins folder


**Have Fun** :D
