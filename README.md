dwm is a dynamic window manager for X.

Requirements
------------
In order to build dwm you need the Xlib header files.

Installation
------------
Afterwards enter the following command to build and install dwm (if
necessary as root):

WITH `libxft-bgra` library:
NOTE: `libxft-bgra` is no longer needed with regular xft lib installed >= 2.5 versions.

BUILDING DEPENDENCIES
on debian based distros:
```sh
  sudo apt install dh-autoreconf xutils-dev libxrender-dev libfreetype-dev libfontconfig-dev
```

```sh
sudo apt install libxft-dev libxinerama-dev
```

```sh
   git clone --recurse-submodules 'https://github.com/khonsaloh/dwm.git'
   cd dwm/libxft-bgra
   sh autogen.sh --prefix=/build/libxft-bgra
   sudo make install
   cd ..
   sudo make clean install
```

WITHOUT `libxft-bgra` library:
```sh
   git clone 'https://github.com/khonsaloh/dwm.git'
#   patch -R < color_emoji.diff #remove color emoji patch (optional)
   sudo make clean install
```

Configuration
-------------
The configuration of dwm is done by creating a custom config.h
and (re)compiling the source code.
The manual page was removed due to the difficulty of keeping up to date with changes made here and there.
