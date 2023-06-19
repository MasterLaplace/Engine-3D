#!/usr/bin/env bash
URL="https://github.com/Snaipe/Criterion/releases/download/v2.3.2"
TARBALL="criterion-v2.3.2-linux-x86_64.tar.bz2"
DIR="criterion-v2.3.2"
DST="~/"
SUDO=sudo

cd /tmp
rm -f $TARBALL
rm -fr $DIR

wget $URL/$TARBALL
if [ $? != 0 ]; then
    echo "failled, exiting"
    exit;
fi

echo
echo "untaring $TARBALL"
tar xjf $TARBALL
if [ $? != 0 ]; then
    echo "failled, exiting"
    exit;
fi

echo "creating custom ld.conf"
$SUDO sh -c "echo "~/" > ~/criterion.conf"
echo "all good."
