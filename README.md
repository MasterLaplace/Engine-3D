# ME : <p align="center">Rastérisation</p>

<p align="center">
  <a href="https://github.com/MasterLaplace/Engine-3D/blob/main/LICENSE">
    <img src="https://img.shields.io/badge/License-MIT-brightgreen.svg?style=for-the-badge" alt="License: MIT">
  </a><a>
    <img src="https://img.shields.io/badge/CSFML-2.5-blue?style=for-the-badge" alt="CSFML: 2.5">
  </a><a>
    <img src="https://img.shields.io/badge/vosk--api-0.3.30-blue?style=for-the-badge" alt="vosk-api: 0.3.30">
  </a><a>
    <img src="https://img.shields.io/badge/C-11-blue?style=for-the-badge" alt="C: 11">
  </a><a>
    <img src="https://img.shields.io/badge/OS-Linux-blue?style=for-the-badge" alt="OS: Linux">
  </a>
  <a href="https://github.com/MasterLaplace/Engine-3D/actions/workflows/test_engine.yml">
    <img src="https://github.com/MasterLaplace/Engine-3D/actions/workflows/test_engine.yml/badge.svg" alt="Build Status">
  </a>
  <a href="https://github.com/MasterLaplace/Engine-3D/releases/latest/">
    <img src="https://img.shields.io/github/v/release/MasterLaplace/Engine-3D.svg?label=version" alt="Version">
  <a>
</p>

Rastérisation in C with CSFML lib

Status: in progress


## :placard: Table of Contents
- [Description](#description)
- [Goal](#goal)
- [Running](#running)
- [Documentation](#documentation)
- [License](#license)
- [Contacts](#contacts)


<div id='description'/>

### :pencil: **DESCRIPTION**

Le but de ce projet est d’implémenter la méthode de rastérisation utilisé par de
nombreux moteurs 3D pour sa rapidité et ses possibilités comparé au Ray Tracing.<br>
Mon objectif final est de pouvoir proposer un rendu 3d graphique de n’importe quel
objet importé ainsi que de pouvoir me déplacer pour l’observer sous d’autres angles en
temps réel.<br>


<div id='goal'/>

### **GOAL**

Il faut : ✅

    0.1 dans un premier temps parser un fichier (.obj). ✅
    0.2 dans un second temps implémenter une Projection matricielle. ✅
    0.3 dans un troisième temps implémenter le Clipping de Cohen-Sutherland. ✅
    0.4 dans un quatrième temps ajout des déplacements de la caméra. ✅
    0.5 dans un cinquième temps implémenter le Texture mapping.
    0.6 dans un sixième temps implémenter un Z-buffer/Deph-buffer.


<div id='running'/>

### :truck: **RUNNING**

```shell
# Clone repository
$ git clone https://github.com/MasterLaplace/Engine-3D.git
$ cd Engine-3D

# Engine
$ make re
$ ./bin/engine.out

# Server
$ make server
$ ./src/server/server.out

# Client
$ make client
$ ./src/client/client.out [vocal mode: -v]

# Manager
$ make manager
$ ./src/manager/manager.out [help|clean|create] [layer_name]
```


### INTERACTIONS

| Key | Action |
| --- | --- |
| <kbd>`W`</kbd> | Move forward |
| <kbd>`S`</kbd> | Move backward |
| <kbd>`A`</kbd> | Move left |
| <kbd>`D`</kbd> | Move right |
| <kbd>`Q`</kbd> | Move up |
| <kbd>`E`</kbd> | Move down |
| <kbd>`↑`</kbd> | Rotate up |
| <kbd>`↓`</kbd> | Rotate down |
| <kbd>`←`</kbd> | Rotate left |
| <kbd>`→`</kbd> | Rotate right |
| <kbd>`R`</kbd> | Reset camera |
| <kbd>`ESC`</kbd> | Quit |
| <kbd>`SPACE`</kbd> | Pause |
| <kbd>`ENTER`</kbd> | Next layer |
| <kbd>`BACKSPACE`</kbd> | Previous layer |
| <kbd>`TAB`</kbd> | Toggle layer |
| <kbd>`F1`</kbd> | Toggle debug |
| <kbd>`F2`</kbd> | Toggle wireframe |
| <kbd>`F3`</kbd> | Toggle texture |
| <kbd>`F4`</kbd> | Toggle normals |
| <kbd>`F5`</kbd> | Toggle lights |
| <kbd>`F6`</kbd> | Toggle shadows |
| <kbd>`F7`</kbd> | Toggle ambient occlusion |
| <kbd>`F8`</kbd> | Toggle bloom |
| <kbd>`F9`</kbd> | Toggle motion blur |
| <kbd>`F10`</kbd> | Toggle depth of field |
| <kbd>`F11`</kbd> | Toggle anti-aliasing |
| <kbd>`F12`</kbd> | Toggle vignette |
| <kbd>`MOUSE WHEEL`</kbd> | Zoom |
| <kbd>`MOUSE LEFT`</kbd> | Rotate |
| <kbd>`MOUSE RIGHT`</kbd> | Translate |
| <kbd>`MOUSE MIDDLE`</kbd> | Select |
| <kbd>`MOUSE LEFT`</kbd> | Select |
| <kbd>`MOUSE RIGHT`</kbd> | Select |


<div id='documentation'/>

### :wrench: **DOCUMENTATION**

- [**CSFML**](https://www.sfml-dev.org/download/csfml/)
- [**vosk-api**](https://alphacephei.com/vosk/)
- [**GCC-C**](https://gcc.gnu.org/onlinedocs/)
- [**my and link**](https://github.com/MasterLaplace/Engine-3D/blob/main/libs/README.md)


<div id='license'/>

## :scroll: **LICENSE**

This project is licensed under the terms of the [MIT License](./LICENSE).

Copyright © 2023-2024 [Master_Laplace](https://github.com/MasterLaplace).


<div id='contacts'/>

### :mailbox_with_mail: **CONTACTS**

This libs has been carried out by:

* [![GitHub MasterLaplace](https://img.shields.io/github/followers/MasterLaplace?label=MasterLaplace&style=social)](https://github.com/MasterLaplace)

---
<p align="center">ME.inc</p>
