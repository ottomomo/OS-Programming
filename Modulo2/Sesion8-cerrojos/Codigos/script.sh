#!/bin/bash

set -x 
trap read debug

dd if=/dev/zero of=/tmp/disk.img bs=1024 count=100k
sudo mkfs -t ext2 -b 1024 /tmp/disk.img

mkdir /tmp/disk
sudo mount -t ext2 -o defaults,loop /tmp/disk.img /tmp/disk
cd /tmp/disk

sudo dd if=/dev/urandom of=file.bin bs=1024 count=1 seek=0
ls -la file.bin
du -hs file.bin

sudo rm file.bin
sudo dd if=/dev/urandom of=file.bin bs=1024 count=1 seek=11
ls -la file.bin
du -hs file.bin

sudo rm file.bin
sudo dd if=/dev/urandom of=file.bin bs=1024 count=1 seek=12
ls -la file.bin
du -hs file.bin

sudo rm file.bin
sudo dd if=/dev/urandom of=file.bin bs=1024 count=1 seek=268
ls -la file.bin
du -hs file.bin
