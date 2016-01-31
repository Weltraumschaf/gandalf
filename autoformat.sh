#!/usr/bin/env bash

# From https://matt.sh/howto-c

FORMAT_STYLE="{BasedOnStyle: llvm, IndentWidth: 4, AllowShortFunctionsOnASingleLine: None, KeepEmptyLinesAtTheStartOfBlocks: false}"

find src \( -name \*.c -or -name \*.cpp -or -name \*.cc -or -name \*.h \) | \
    xargs -n12 -P4 clang-format -style="${FORMAT_STYLE}" -i  
