#!/bin/bash

MPOINT="./mount-point"
TMP="./tmp"

if [ ! -e $MPOINT ]; then
    echo "MPOINT not exist"
   exit 1
fi

if  [ ! -e $TMP ]; then
    mkdir $TMP
fi

cp ./src/fuseLib.c $MPOINT/
cp ./src/myFS.h $MPOINT/

cp ./src/fuseLib.c $TMP/
cp ./src/myFS.h $TMP/

printf "\n\n\n\t[[COPY fuseLib.c AND myFS.h]]\n\n\n"

./my-fsck-static-64 virtual-disk

if [ "$(diff ./src/fuseLib.c $MPOINT/fuseLib.c)" != "" ] ; then
    echo "fuseLib.c is not equal"
	exit 1
fi
if [ "$(diff ./src/myFS.h $MPOINT/myFS.h)" != "" ] ; then
    echo "myFS.h is not equal"
	exit 1
fi

printf "\n\n\n\t[[TRUNCATE -1]]\n\n\n"

truncate -s -1 $TMP/fuseLib.c
truncate -s -1 $TMP/myFS.h

truncate -s -1 $MPOINT/fuseLib.c
truncate -s -1 $MPOINT/myFS.h

./my-fsck-static-64 virtual-disk

if [ "$(diff $TMP/fuseLib.c $MPOINT/fuseLib.c)" != "" ] ; then
    echo "fuseLib.c is not equal"
	exit 1
fi
if [ "$(diff $TMP/myFS.h $MPOINT/myFS.h)" != "" ] ; then
    echo "myFS.h is not equal"
	exit 1
fi

printf "\n\n\n\t[[COPY MAKEFILE]]\n\n\n"

cp ./Makefile $MPOINT/

./my-fsck-static-64 virtual-disk

if [ "$(diff ./Makefile $MPOINT/Makefile)" != "" ] ; then
    echo "Makefile is not equal"
	exit 1
fi

printf "\n\n\n\t[[TRUNCATE +1]]\n\n\n"

truncate -s +1 $TMP/myFS.h
truncate -s +1 $MPOINT/myFS.h

./my-fsck-static-64 virtual-disk

if [ "$(diff $TMP/myFS.h $MPOINT/myFS.h)" != "" ] ; then
    echo "myFS.h is not equal"
	exit 1
fi

printf "\n\n\n\t[[All is OK]]\n\n\n"
exit 0
