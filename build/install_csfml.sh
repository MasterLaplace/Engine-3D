#!/usr/bin/env bash

URL="https://github.com/SFML/CSFML.git"
DIR="CSFML"
INSTALL_DIR=~/csfml

# install SFML dependencies
sudo apt-get update
sudo apt-get install -y libsfml-dev libcsfml-dev

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
