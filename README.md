# Gandalf OS

[How to][how-to] make an operating system from scratch.

Why "Ganfdalf"? I needed a "code name" for the GitHub repo and Gandalf was
my first thought. Don't know why. I'm not really a Hobbit-fan.

## Prerequisites

What you need:

- [NASM][nasm] assembler
- [binutils][binutils]
- [GCC][gcc] Compiler (only for building cross compiler)
- [QEMU][qemu] to run the compiler

On Linux this should be no problem at all. On Mac OS X [home brew][brew] is
recommended to install the tools. On Windows I guess [CygWin][cyg] is a good
choice.

## Cross Compiler

To build the kernel you need a croo compiler. An how to is provided [here][cross].
You have to edit the file `build-tools/environment` with the correct paths to
your GGC you have installed on your host (development) machine. After that
invoke the built script: `build-tools/build.sh`. This will take a while and 
build a standalone C compiler for the kernel in `build-tools/cross` used by
the `Makefile`.

## Build the kernel

After you have installed the prerequisites and cross compiler yu can build
the kernel by invoking:

    $> make
    
And running it in [QEMU][qemu] by invoking:

    $> make run

[how-to]:   http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
[nasm]:     http://www.nasm.us/
[binutils]: https://www.gnu.org/software/binutils/
[gcc]:      http://gcc.gnu.org/
[brew]:     http://brew.sh/
[cyg]:      http://www.cygwin.com/
[cross]:    http://wiki.osdev.org/GCC_Cross-Compiler
[qemu]:     http://wiki.qemu.org/Main_Page
