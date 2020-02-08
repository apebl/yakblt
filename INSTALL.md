# Installation

## Flatpak

[![Download on Flathub](https://flathub.org/assets/badges/flathub-badge-en.svg)](https://flathub.org/apps/details/org.kosmospredanie.Yakblt)

## Building

### Build requirements

- meson >= 0.49
- ninja (or other meson backend to use)

### Dependencies

- sfml >= 2.5.1
	- sfml-system
	- sfml-window
	- sfml-graphics
	- sfml-audio
- tgui >= 0.8
- libgnome-games-support >= 1.4.4

#### Install dependencies

##### Ubuntu

```sh
sudo add-apt-repository ppa:texus/tgui-0.8
sudo apt-get update
sudo apt-get install libsfml-dev libtgui-dev
```

##### Arch Linux

```sh
sudo pacman -S yay sfml
yay -S tgui
```

### Build

```sh
cd yakblt
meson _build --buildtype=release
ninja -C _build
```

And run the game:

```sh
_build/src/yakblt
```

#### Debug mode

In order to enable debug mode, add `-Ddebug_mode=true` option to meson build:

```sh
meson _build --buildtype=release -Ddebug_mode=true
```

![Debug mode](debug.jpg)

#### Install

Run (sudo) `ninja -C _build install` after meson build.

You can specify the installation prefix by adding a `--prefix` option to meson
build.

#### Uninstall

```sh
ninja -C _build uninstall
```
