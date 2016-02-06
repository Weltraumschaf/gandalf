#!/usr/bin/env bash

set -e

BUILD="build.log"
ERRORS="errors.log"

rm -rf "${BUILD}" "${ERRORS}"
make clean && make > >(tee "${BUILD}") 2> >(tee "${ERRORS}" >&2)
