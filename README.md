
### Building from Source

<!--
#### Arch:
```
### build and install with makepkg ###
$ wget https://raw.githubusercontent.com/bill-auger/audio-tag-too/master/Builds/Packaging/PKGBUILD
# makepkg -sri ./PKGBUILD
```
-->

#### Debian >= 9, Ubuntu >= 15.10:
```
### build dependencies ###
$ sudo apt-get install build-essential libfreetype6-dev libx11-dev libxcursor-dev \
                       libxinerama-dev libxrandr-dev

### runtime dependencies ###
$ sudo apt-get install freeglut3 libfreetype6 libgl1-mesa-glx libx11-6 libxcomposite1 \
                       libxcursor1 libxext6 libxinerama1 libxrender1

### compile ###
$ cd Builds/Makefile
$ make
$ sudo make install

### run ###
$ audio-tag-too
```

#### Fedora >= 23 (plus rpmfusion repositories):
```
### build dependencies ###
$ su -c "dnf install freetype-devel gcc-c++ libX11-devel libXcursor-devel \
                     libXinerama-devel libXrandr-devel"

### runtime dependencies ###
$ su -c "dnf install freetype libX11 libXcursor libXinerama libXrandr"


### compile ###
$ cd Builds/Makefile
$ make
$ su -c "make install"

### run ###
$ audio-tag-too
```

#### OpenSuse Leap >= 42, OpenSuse Tumbleweed, Suse SLE >= 12:
```
### build dependencies ###
$ sudo zypper install freetype2-devel gcc-c++ libX11-devel libXinerama-devel \
                      libXcursor-devel libXrandr-devel

### runtime dependencies ###
$ sudo zypper install freetype2 libX11 libXinerama libXcursor libXrandr

### compile ###
$ cd Builds/Makefile
$ make
$ sudo make install

### run ###
$ audio-tag-too
```

#### Other GNU/Linux:
Install the corresponding libraries as above for your system and compile similarly.
