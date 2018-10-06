
### Building from Source

<!--
#### Arch, Parabola:
```
### build and install with makepkg ###
$ wget https://raw.githubusercontent.com/bill-auger/juce-boilerplate/master/Builds/Packaging/PKGBUILD
# makepkg -sri ./PKGBUILD
```
-->

#### Debian, Ubuntu, Trisquel:
```
### build dependencies ###
$ sudo apt-get install build-essential libasound2-dev libcurl4-gnutls-dev             \
                       libfreetype6-dev libgtk-3-dev libwebkit2gtk-4.0-dev libx11-dev \
                       libxcursor-dev libxinerama-dev libxrandr-dev

### runtime dependencies ###
$ sudo apt-get install freeglut3 libcurl3-gnutls libfreetype6 libgl1-mesa-glx libgtk-3-0 \
                       libwebkit2gtk-4.0-37 libx11-6 libxcomposite1 libxcursor1 libxext6 \
                       libxinerama1 libxrender1

### compile ###
$ cd Builds/Makefile
$ make
$ sudo make install

### run ###
$ juce-boilerplate
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
$ juce-boilerplate
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
$ juce-boilerplate
```

#### Other GNU/Linux:
Install the corresponding libraries as above for your system and compile similarly.
