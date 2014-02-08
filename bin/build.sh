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
PREFIX="${PROGRAM_DIRECTORY}/../build-tools/cross/bin/i586-elf"

# Cleaning:
if [ -d "${TARGET}" ] ; then
  echo "Deleting direcotry ${TARGET} ..."
  rm -rf "${TARGET}"
fi

mkdir -p ${TARGET}

# Compile kernel:
if [ -f "${KERNEL_OBJ}" ] ; then
  echo "Deleteing ${KERNEL_OBJ} ..."
  rm "${KERNEL_OBJ}"
fi

echo "Compiling ${KERNEL_SRC} ..."
${PREFIX}-gcc -ffreestanding \
  -c "${KERNEL_SRC}" \
  -o "${KERNEL_OBJ}"

echo "Linking ${KERNEL_BIN} ..."
${PREFIX}-ld "${KERNEL_OBJ}" \
  -o "${KERNEL_BIN}" \
  -Ttext "${KERNEL_OFFSET}" \
  --oformat binary

# Assembling boot sector:
echo "Assembling ${BOOT_SRC} ..."
cd "${SRC_ASM}"
nasm "${BOOT_SRC}" \
  -f bin \
  -o "${BOOT_BIN}"

echo "Generate image ${IMAGE} ..."
cat "${BOOT_BIN}" "${KERNEL_BIN}" > "${IMAGE}"

cd "${PROGRAM_DIRECTORY}"
echo "Done :)"
