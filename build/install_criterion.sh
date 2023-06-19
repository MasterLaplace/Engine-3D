#!/usr/bin/env bash

URL="https://github.com/Snaipe/Criterion.git"
DIR="Criterion"
INSTALL_DIR=~/criterion

# install Criterion dependencies
sudo apt-get update
sudo apt-get install -y libeigen3-dev libgsl-dev

# clone Criterion repository
cd build
rm -rf $DIR
git clone $URL
if [ $? != 0 ]; then
    echo "failed to clone Criterion repository, exiting"
    exit 1
fi

# build Criterion
cd $DIR
echo "building $DIR"
cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR . && make install
if [ $? != 0 ]; then
    echo "failed to build Criterion, exiting"
    exit 1
fi

rm -rf ../$DIR
echo "Criterion successfully installed to $INSTALL_DIR"
