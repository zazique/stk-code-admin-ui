# Building from source

This SuperTuxKart fork already inludes all assets, so you can just clone it:

```bash
git clone https://github.com/zazique/stk-code-admin-ui stk-code
```

## Building SuperTuxKart on Linux

### Dependencies

To build SuperTuxKart from source, you'll need to install the following packages:

* OpenAL (recommended: openal-soft-devel)
* Ogg (libogg-dev)
* Vorbis (libvorbis-dev)
* Freetype (libfreetype6-dev)
* Harfbuzz (libharfbuzz-dev)
* libcurl (libcurl-devel)
* libbluetooth (bluez-devel)
* openssl (openssl-dev)
* libpng (libpng-devel)
* zlib (zlib-devel)
* jpeg (libjpeg-turbo-devel)
* SDL2 (libsdl2-devel)

Debian-based Distributions command:

```bash
sudo apt-get install build-essential cmake libbluetooth-dev libsdl2-dev \
libcurl4-openssl-dev libenet-dev libfreetype6-dev libharfbuzz-dev \
libjpeg-dev libogg-dev libopenal-dev libpng-dev \
libssl-dev libvorbis-dev libmbedtls-dev pkg-config zlib1g-dev
```

Fedora command:

```bash
sudo dnf install @development-tools angelscript-devel \
bluez-libs-devel cmake desktop-file-utils SDL2-devel \
freealut-devel freetype-devel \
gcc-c++ git-core libcurl-devel libjpeg-turbo-devel \
libpng-devel libsquish-devel libtool libvorbis-devel \
openal-soft-devel openssl-devel libcurl-devel harfbuzz-devel \
libogg-devel openssl-devel pkgconf \
wiiuse-devel zlib-devel
```

Arch-based Distributions command:

```bash
sudo pacman -S openal libogg libvorbis freetype2 harfbuzz curl \
bluez-libs openssl libpng zlib libjpeg-turbo sdl2 gcc cmake \
pkgconf make git subversion
```

openSUSE command:

```bash
sudo zypper install gcc-c++ cmake openssl-devel libcurl-devel libSDL2-devel \
freetype-devel harfbuzz-devel libogg-devel openal-soft-devel libpng-devel \
libvorbis-devel pkgconf zlib-devel enet-devel \
libjpeg-devel bluez-devel freetype2-devel
```

Mageia 6 command:

```bash
su -c 'urpmi gcc-c++ cmake openssl-devel libcurl-devel freetype-devel harfbuzz-devel \
libjpeg-turbo-devel libogg-devel openal-soft-devel SDL2-devel \
libpng-devel libvorbis-devel nettle-devel zlib-devel git subversion \
libbluez-devel libfreetype6-devel
```

Solus command:
```bash
sudo eopkg it cmake openal-soft-devel libogg-devel libvorbis-devel freetype2-devel \
harfbuzz-devel curl-devel bluez-devel openssl-devel libpng-devel zlib-devel \
libjpeg-turbo-devel sdl2-devel enet-devel libjpeg-turbo-devel bluez-devel curl-devel
```

#### In-game recorder

To build the in-game recorder for STK, you have to install
`libopenglrecorder` from your distribution, or compile it yourself from [here](https://github.com/Benau/libopenglrecorder).
Compilation instruction is explained there. If you don't need this feature, pass `-DBUILD_RECORDER=off` to CMake.

#### Shaderc for Vulkan support

You need to compile [Shaderc](https://github.com/google/shaderc) for Vulkan support in SuperTuxKart if you are not building for Windows or macOS. If you don't need this feature, pass `-DNO_SHADERC=on` to CMake.

### Compiling

To compile SuperTuxKart, run the following commands inside the `stk-code` directory:

```bash
# go into the stk-code directory
cd stk-code

# create and enter the cmake_build directory
mkdir cmake_build
cd cmake_build

# run cmake to generate the makefile
cmake ..

# compile
make -j$(nproc)
```

STK can then be run from the build directory with `bin/supertuxkart`.

#### Keeping your build up to date

To recompile the latest code without redownloading the entire source, run the following commands inside the 'stk-code' directory:

```bash
git pull
cd cmake_build
cmake ..
make -j$(nproc)
```

#### Build Speed Optimization

The `-j$(nproc)` option is an example. For a faster build, use `-jx` instead, where "x" is the amount of CPU threads you have, minus one.

#### Further options

To create a debug version of STK, run:

```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

You can install your build system-wide:

```bash
sudo make install
```

The default install location is `/usr/local`, i.e. the data files will
be written to `/usr/local/share/games/supertuxkart` and the executable
will be copied to `/usr/local/bin`. To change the default installation
location, specify `CMAKE_INSTALL_PREFIX` when running CMake, e.g.:
`cmake .. -DCMAKE_INSTALL_PREFIX=/opt/stk`.

## Building SuperTuxKart on Windows

To Build SuperTuxKart on Windows, follow these instructions:

1. Download and install Visual Studio from here: [Visual Studio - Download](https://www.visualstudio.com/downloads/). The free Visual Studio Community edition works fine. Remember to select "Desktop development with C++" in the installer.

2. Clone the repository: 

```bash
git clone [https://github.com/zazique/stk-code-admin-ui](https://github.com/zazique/stk-code-admin-ui) stk-code
```

3. Download the Windows dependencies package from [SuperTuxKart on GitHub - Dependencies latest preview release](https://github.com/supertuxkart/dependencies/releases/tag/preview)
and unpack the archive into the `stk-code` directory. Download `i686` if you use Win32 generator of MSVC, `x86_64` for x64, `armv7` for ARM and `aarch64` for ARM64.

Build: Open `SuperTuxKart.sln` in Visual Studio, right-click the `supertuxkart` project, select "Set as StartUp project", and press `CTRL + SHIFT + B`.

## Building SuperTuxKart on macOS

### Getting Started

Install the developer tools, either from the OS X Install DVD or from Apple's website.

Clone the repository: 

```bash
git clone [https://github.com/zazique/stk-code-admin-ui](https://github.com/zazique/stk-code-admin-ui) stk-code
```

Build STK:

```bash
cd /path/to/stk-code
mkdir cmake_build
cd cmake_build
cmake .. -DCMAKE_FIND_ROOT_PATH=$(pwd)/../dependencies-macosx -DUSE_CRYPTO_OPENSSL=FALSE
make
```

Add ` -DCMAKE_OSX_DEPLOYMENT_TARGET=10.9` for 10.9 compatibility.

#### (Optional) packaging for distribution

By default, the executable that is produced is not ready for distribution. Install <https://github.com/auriamg/macdylibbundler> and run:

```bash
dylibbundler -od -b -x ./bin/SuperTuxKart.app/Contents/MacOS/supertuxkart -d ./bin/SuperTuxKart.app/Contents/libs/ -p @executable_path/../libs/ -s ../dependencies-macosx/lib
```

Add `-ns` to disable ad-hoc codesigning.
