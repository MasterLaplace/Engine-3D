#!/usr/bin/env bash
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
# File name: install_csfml.sh
# Author: MasterLaplace
# Created on: 2023-10-12

URL="https://github.com/SFML/CSFML.git"
DIR="CSFML"
INSTALL_DIR=~/csfml

# install SFML dependencies
if command -v apt-get &> /dev/null; then
    sudo apt-get update
    sudo apt-get install -y libsfml-dev libcsfml-dev
elif command -v dnf &> /dev/null; then
    sudo dnf update
else
    echo "DNF or APT package manager not found, exiting"
    exit 1
fi

# clone CSFML repository
cd build
rm -rf $DIR
git clone $URL
if [ $? != 0 ]; then
    echo "failed to clone CSFML repository, exiting"
    exit 1
fi

# build CSFML
cd $DIR
echo "building $DIR"
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR . && make install
if [ $? != 0 ]; then
    echo "failed to build CSFML, exiting"
    exit 1
fi

rm -rf ../$DIR
echo "CSFML successfully installed to $INSTALL_DIR"
