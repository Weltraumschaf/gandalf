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
PREFIX="${PROGRAM_DIRECTORY}/build-tools/cross/bin"

echo "#"
echo "# Setting compiler flags and PATH ..."
echo "#"
export CC="${PREFIX}/i586-elf-gcc"
echo "CC=${CC}"
export CXX="${PREFIX}/i586-elf-g++"
echo "CXX=${CXX}"
export CPP="${PREFIX}/i586-elf-cpp"
echo "CPP=${CPP}"
export LD="${PREFIX}/i586-elf-gcc"
echo "LD=${LD}"
export PATH="${PREFIX}/bin:${PATH}"
echo "Prepended ${PREFIX} to PATH"
