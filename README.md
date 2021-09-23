qimgv | Current version: 1.0.0
=====
Image viewer. Fast, easy to use. Optional video support.

## Screenshots

Main window & panel        |  Folder view   |  Settings window  
:-------------------------:|:-------------------------:|:-------------------------:|
[![img1](qimgv/distrib/screenshots/qimgv0.9_1_thumb.jpg)](qimgv/distrib/screenshots/qimgv0.9_1.jpg?raw=true)  |  [![img2](qimgv/distrib/screenshots/qimgv0.9_2_thumb.jpg)](qimgv/distrib/screenshots/qimgv0.9_2.jpg?raw=true) | [![img3](qimgv/distrib/screenshots/qimgv_3_thumb.jpg)](qimgv/distrib/screenshots/qimgv_3.jpg?raw=true)

## [qimgv v0.6 video overview](https://www.youtube.com/watch?v=AODRGCRPCpw)

## Key features:

- Simple UI

- Fast

- Easy to use

- Fully configurable, including themes, shortcuts

- High quality scaling

- Basic image editing: Crop, Rotate and Resize

- Ability to quickly copy / move images to different folders

- Experimental video playback via libmpv

- Folder view mode

- Ability to run shell scripts

## Default control scheme:

| Action  | Shortcut |
| ------------- | ------------- |
| Next image  | Right arrow / MouseWheel |
| Previous image  | Left arrow / MouseWheel |
| Goto first image  | Home |
| Goto last image  | End |
| Zoom in  | Ctrl+MouseWheel / Crtl+Up |
| Zoom out  | Ctrl+MouseWheel / Crtl+Down |
| Zoom (alt. method) | Hold right mouse button & move up / down |
| Fit mode: window | 1 |
| Fit mode: width | 2 |
| Fit mode: 1:1 (no scaling) | 3 |
| Switch fit modes  | Space |
| Toggle fullscreen mode  | DoubleClick / F / F11 |
| Exit fullscreen mode | Esc |
| Show EXIF panel  | I |
| Crop image  | X |
| Resize image  | R |
| Rotate left  | Ctrl+L |
| Rotate Right  | Ctrl+R |
| Open containing directory | Ctrl+D |
| Slideshow mode | ~ |
| Shuffle mode | Ctrl+~ |
| Quick copy  | C |
| Quick move  | M |
| Move to trash | Delete |
| Delete file  | Shift+Delete |
| Save  | Ctrl+S |
| Save As  | Ctrl+Shift+S |
| Folder view | Enter / Backspace |
| Open | Ctrl+O |
| Print / Export PDF | Ctrl+P |
| Settings  | P |
| Exit application | Esc / Ctrl+Q / Alt+X / MiddleClick |

... and more.

Note: you can configure every shortcut by going to __Settings > Controls__

# User interface

The idea is to have a uncluttered, simple and easy to use UI. You can see UI elements only when you need them.

There is a pull-down panel with thumbnails, as well as folder view. You can also bring up a context menu via right click.

## Using quick copy / quick move panels

Bring up the panel with C or M shortcut. You will see 9 destination directories, click them to set them up.

With panel visible, use 1 - 9 keys to copy/move current image to corresponding directory.

When you are done press C or M again to hide the panel.

## Running scripts

You can run custom scripts on a current image.

Open __Settings > Scripts__. Press Add. Here you can choose between a shell command and a shell script. 

Example of a command: 

`convert %file% %file%_.pdf`

Example of a shell script file (`$1` will be image path): 
```
#!/bin/bash
gimp "$1"
```
_Note: The script file must be an executable. Also, "shebang" (`#!/bin/bash`) needs to be present._

When you've created your script go to __Settings > Controls > Add__, then select it and assign a shortcut like for any regular action.

## HiDPI (Linux / MacOS only)

If qimgv appears too small / too big on your display, you can override the scale factor. Example:
```
QT_SCALE_FACTOR="1.5" qimgv /path/to/image.png
```
You can put it in `qimgv.desktop` file to make it permanent. Using values less than `1.0` is not supported.

qimgv should also obey the global scale factor set in KDE's systemsettings.

## High quality scaling

qimgv supports nicer scaling filters when compiled with `opencv` support (ON by default, but might vary depending on your linux distribution). Filter options are available in __Settings > Scaling__. `Bicubic` or `bilinear+sharpen` is recommended.

# Additional image formats

qimgv can open some extra formats via third-party image plugins. All of them are included with windows package.

| Format  | Plugin |
| ------- | ------------- |
| JPEG-XL | [github.com/novomesk/qt-jpegxl-image-plugin](https://github.com/novomesk/qt-jpegxl-image-plugin) |
| AVIF | [github.com/novomesk/qt-avif-image-plugin](https://github.com/novomesk/qt-avif-image-plugin) |
| APNG | [github.com/Skycoder42/QtApng](https://github.com/Skycoder42/QtApng) |
| HEIF / HEIC | [github.com/jakar/qt-heif-image-plugin](https://github.com/jakar/qt-heif-image-plugin) |
| RAW | [https://gitlab.com/mardy/qtraw](https://gitlab.com/mardy/qtraw) |

# Installation

### Windows builds

  [Grab the latest release here](https://github.com/easymodo/qimgv/releases)
  
  Windows builds are portable (everything is contained within install folder).
  
  Installer additionally sets up file associations.

### GNU+Linux

__Arch Linux / Manjaro / etc.:__ 

AUR package: 

```
qimgv-git
```
  
__Ubuntu / Linux Mint / Pop!\_OS / etc.__

```
sudo add-apt-repository ppa:easymodo/qimgv
sudo apt-get update
sudo apt install qimgv
```

_Alternative package with kde support:_

```
sudo apt install qimgv-kde
```

__Gentoo:__

```
emerge qimgv
```

__OpenSUSE__: 

```
zypper install qimgv
```

__Void linux__: 

```
xbps-install -S qimgv
```

__Alpine Linux__:

```
apk add qimgv
```

__Fedora__: 

```
sudo dnf install qimgv
```

This list may be incomplete. If your favorite distro is not included refer to [Manual install] section below.

### Manual install
 
__Install dependencies ( `gcc` >= 9.0, `git`, `cmake` >= 3.13, `qt` >= 5.14, `exiv2`, `mpv`, `opencv (core and imgproc)`__

_Ubuntu & derivatives (21.04 or later):_
     
```
sudo apt install build-essential git cmake qtbase5-dev libqt5svg5-dev libexiv2-dev libmpv-dev libopencv-dev kimageformat-plugins gcc g++
```
Optional: `libkf5windowsystem-dev`
     
_Fedora:_

Enable RPMFusion [https://rpmfusion.org/Configuration](https://rpmfusion.org/Configuration).

It is needed for video playback (mpv), but you also can build without it. See __CMake build options__ at the end.

```
sudo dnf install git cmake make qt5 qt5-devel gcc-c++ mpv mpv-libs-devel exiv2-devel opencv opencv-devel
```
Optional: `kf5-kwindowsystem`
		
__Configure & install__

Get sources

```
git clone https://github.com/easymodo/qimgv.git
cd qimgv && mkdir -p build && cd build
```

Configure

```
cmake ../ -DCMAKE_INSTALL_PREFIX=/usr/ -DCMAKE_INSTALL_LIBDIR=lib
```

Build

```
make -j`nproc --ignore=1`
```

Install

```
sudo make install
```

### Possible build issues

- If you get errors like "/usr/lib64 exists in filesystem" during install:

add `-DCMAKE_INSTALL_LIBDIR:PATH=/usr/lib` to cmake command.

### CMake build options

| Option  | Default value | Description |
| ------- | ------------- | ----------- |
| VIDEO_SUPPORT | ON | Enables video playback via `mpv` |
| EXIV2 | ON | Support reading exif tags via `exiv2` |
| OPENCV_SUPPORT | ON | Enables high quality scaling options |
| KDE_SUPPORT | OFF | Use some features from KDE, like background blur |

Usage example:
```
cmake ../ -DKDE_SUPPORT=ON  -DCMAKE_INSTALL_PREFIX=/usr/
```

### Donate

If you wish to throw me a few bucks, you can do it here:

<a href="https://www.buymeacoffee.com/easymodo" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/default-orange.png" alt="Donate" height="41" width="174"></a>

Any support is appreciated!
