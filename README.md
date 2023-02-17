# ME : <p align="center">Rastérisation</p>

Rastérisation in C with CSFML lib

Status: in progress


## Table of Contents
- [Description](#description)
- [Goal](#goal)
- [Running](#running)
- [Documentation](#documentation)
- [Contacts](#contacts)


<div id='description'/>

### **DESCRIPTION**

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

### **RUNNING**

```shell
# Engine
$ make fclean all
$ ./bin/engine.out

# Server
$ make server
$ ./src/server/server.out

# Client
$ make client
$ ./src/client/client.out [vocal mode: -v]
```

<div id='documentation'/>

### **DOCUMENTATION**

- lib CSFML
- vosk-api
- langage C


<div id='contacts'/>

### **CONTACTS**

[![GitHub MasterLaplace](https://img.shields.io/github/followers/MasterLaplace?label=follow&style=social)](https://github.com/MasterLaplace)

---
<p align="center">ME.inc</p>
