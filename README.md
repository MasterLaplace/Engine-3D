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
  <a href="https://github.com/MasterLaplace/Engine-3D/actions/workflows/test.yml">
    <img src="https://github.com/MasterLaplace/Engine-3D/actions/workflows/test.yml/badge.svg" alt="Build Status">
  </a>
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
```


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

* [![GitHub MasterLaplace](https://img.shields.io/github/followers/MasterLaplace?label=follow&style=social)](https://github.com/MasterLaplace)

---
<p align="center">ME.inc</p>
