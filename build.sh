#!/bin/bash

if [ -f ./boot_sector.bin ] ; then
    rm ./boot_sector.bin
fi

nasm ./boot_sector.asm -f bin -o ./boot_sector.bin
