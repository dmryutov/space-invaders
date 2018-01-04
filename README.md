# Space Invaders (C++ clone)

[![Build Status](https://travis-ci.org/dmryutov/space-invaders.svg?branch=master)](https://travis-ci.org/dmryutov/space-invaders)
[![Build status](https://ci.appveyor.com/api/projects/status/o356khe88xs1y1xh?svg=true)](https://ci.appveyor.com/project/dmryutov/space-invaders)
[![Github Releases](https://img.shields.io/github/release/dmryutov/space-invaders.svg)](https://github.com/dmryutov/space-invaders/releases)
[![MIT Licence](https://badges.frapsoft.com/os/mit/mit.svg?v=103)](https://opensource.org/licenses/mit-license.php)

C++ clone of famous retro game "Space Invaders" for atom.mail.ru

## Building
Make sure the Qt (>= 5.6) development libraries are installed:

* In Ubuntu/Debian: `apt-get install qt5-default qttools5-dev-tools zlib1g-dev`
* In Fedora:        `sudo dnf builddep tiled`
* In Arch Linux:    `pacman -S qt`
* In Mac OS X with [Homebrew](http://brew.sh/):
  + `brew install qt5`
  + `brew link qt5 --force`
* Or you can download Qt from: https://www.qt.io/download-open-source/

Now you can compile by running:
```
qmake (or qmake-qt5 on some systems)
make
```
To do a shadow build, you can run qmake from a different directory and refer
it to space-invaders.pro, for example:
```
mkdir build
cd build
qmake ../src/space-invaders.pro
make
```

## Controls
* Menu
  + <kbd>&uparrow;</kbd> / <kbd>&downarrow;</kbd> - Navigate menu
  + <kbd>Enter</kbd> - Select option
  + <kbd>&leftarrow;</kbd> / <kbd>&rightarrow;</kbd> - Change parameters
* Game
  + <kbd>&leftarrow;</kbd> / <kbd>&rightarrow;</kbd> - Move
  + <kbd>Space</kbd> - Shoot
  + <kbd>P</kbd> - Pause
  + <kbd>Esc</kbd> / <kbd>Q</kbd> - Exit game

## Authors:
- Дмитрий Рютов (https://github.com/dmryutov)
- Дмитрий Ставицкий (https://github.com/Dm94st)
