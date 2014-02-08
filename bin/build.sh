#!/bin/bash

set -e

PROGRAM="${0}"

while [ -h "${PROGRAM}" ]; do
  LS=`ls -ld "${PROGRAM}"`
  LINK=`expr "${LS}" : '.*-> \(.*\)$'`

  if expr "${LINK}" : '.*/.*' > /dev/null; then
    PROGRAM="${LINK}"
  else
    PROGRAM=`dirname "${PROGRAM}"`/"${LINK}"
  fi
done

DIR=`dirname "${PROGRAM}"`
PROGRAM_DIRECTORY=$(cd "${DIR}" ; pwd)

source "${PROGRAM_DIRECTORY}/vars.sh"

PREFIX="${PROGRAM_DIRECTORY}/../build-tools/cross/bin"
export PATH="${PREFIX}/bin:${PATH}"

# Cleaning:
if [ -d "${TARGET}" ] ; then
  echo "Deleting direcotry ${TARGET} ..."
  rm -rf "${TARGET}"
fi

mkdir -p ${TARGET}

# Assembling boot sector:
echo "Assembling ${BOOT_SRC} ..."
cd "${PROGRAM_DIRECTORY}/.."
nasm "${BOOT_SRC}" \
  -f bin \
  -o "${BOOT_BIN}"
nasm "${SRC_ASM}/kernel_entry.asm" \
  -f elf \
  -o "${TARGET}/kernel_entry.o"

cd "${PROGRAM_DIRECTORY}"

echo "Compiling ${KERNEL_SRC} ..."
${PREFIX}/i586-elf-gcc -ffreestanding \
  -c "${KERNEL_SRC}" \
  -o "${KERNEL_OBJ}"

echo "Linking ${KERNEL_BIN} ..."
${PREFIX}/i586-elf-ld "${KERNEL_OBJ}" "${TARGET}/kernel_entry.o" \
  -o "${KERNEL_BIN}" \
  -Ttext "${KERNEL_OFFSET}" \
  --oformat binary

echo "Generate image ${IMAGE} ..."
cat "${BOOT_BIN}" "${KERNEL_BIN}" > "${IMAGE}"

cd "${PROGRAM_DIRECTORY}"
echo "Done :)"
