#!/usr/bin/env bash

BUILD="build.log"
ERRORS="errors.log"
rm -rf "${BUILD}" "${ERRORS}"
time `make clean && make > >(tee "${BUILD}") 2> >(tee "${ERRORS}" >&2)`
