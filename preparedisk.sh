#!/bin/bash

echo "setting up virtual floppy drive..."
sudo losetup /dev/loop0 dist/floppy.img
sudo mkdir /mnt/floppy
sudo mount -t ext2 /dev/loop0 /mnt/floppy

echo "copying kernel..."
sudo cp dist/Debug/GNU-Linux-x86/titanium /mnt/floppy/
sudo cp dist/menu.lst /mnt/floppy/grub/

echo "disconnecting virtual floppy drive..."
sudo umount /mnt/floppy
sudo rm -Rf /mnt/floppy
sudo losetup -d /dev/loop0
