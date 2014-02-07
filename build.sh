#!/bin/bash

IN_FILE="./boot_sector.asm"
OUT_FILE="./boot_sector.bin"

if [ -f "${OUT_FILE}" ] ; then
  echo "Deleteing ${OUT_FILE} ..."
  rm "${OUT_FILE}"
fi

echo "Assembling ${IN_FILE} ..."
nasm "${IN_FILE}" \
  -f bin \
  -o "${OUT_FILE}"

echo "Done :)"
