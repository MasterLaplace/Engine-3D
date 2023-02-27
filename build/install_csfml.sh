#!/usr/bin/env bash
URL="https://github.com/SFML/CSFML.git"
DIR="CSFML"
SUDO=/usr/bin/sudo

if [ $UID -eq "0" ]; then
    SUDO=""
    echo "[no sudo for root]"
fi

cd build
$SUDO rm -rf $DIR
git clone $URL
if [ $? != 0 ]; then
    echo "failled, exiting"
    exit;
fi

echo
cd $DIR
echo "build $DIR"
$SUDO cmake . && $SUDO make install
if [ $? != 0 ]; then
    echo "failled, exiting"
    exit;
fi
