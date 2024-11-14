# NovaCraft

A Classicube (CC) plugin designed to enhance your experience with additional features! :D

## Download

[![Download Latest Release](https://img.shields.io/badge/Download-Last%20Release-brightgreen?style=for-the-badge&logo=github)](https://github.com/mastergive514/NovaCraft2/releases/latest)

## Setup Compiling

### Prerequisites

1. **Download the Classicube Source Code:** [here](https://github.com/UnknownShadow200/ClassiCube/archive/refs/heads/master.zip).
2. **Download `main.c`:** [here](https://raw.githubusercontent.com/mastergive514/NovaCraft2/main/main.c).
3. **Extract the Classicube Source Code:** Place `main.c` in the `classicube-master` folder (make sure the `src` folder is present in the `classicube-master` directory).

### Windows Instructions

#### For 64-bit Windows:

1. **Download Classicube.exe:** [here](https://www.classicube.net/download/) (64-bit version).
2. **Place Classicube.exe** in the `classicube-master` folder.
3. **Open `w64devkit.exe`** and navigate to your `classicube-master` folder using `cd`.
4. **Run the command:** 
   ```gendef ClassiCube.exe```
5. **Execute:** ```x86_64-w64-mingw32-dlltool -d ClassiCube.def -l libClassiCube.a -D ClassiCube.exe```
6. **For compiling, run:** ```x86_64-w64-mingw32-gcc main.c -o novacraft.dll -s -shared -L . -lClassiCube```
#### For 32-bit Windows:
1. **Download Classicube.exe:** [here](https://www.classicube.net/download/) (32-bit version).
2. **Place Classicube.exe** in the `classicube-master` folder.
3. **Run** ```msys.bat```: Located in the ```C:\MinGW\msys\1.0``` folder, then navigate to your ```classicube-master``` folder using ```cd```.
4. **Run the command:** ```gendef ClassiCube.exe```
5. **Execute**: ```dlltool -d ClassiCube.def -l libClassiCube.a -D ClassiCube.exe```
6. **For compiling, run:** ```gcc main.c -o novacraft.dll -s -shared -L . -lClassiCube```
### Linux Instructions
**Note:** You do not need to download Classicube.
1. **Run The Command:** ```gcc main.c -o novacraft.so -shared -fPIC```


## Have Fun!


## Thanking:

Thanks to [ToastyBred](https://github.com/1ToastyBred1/) for working on ChangeAppnname Command.
