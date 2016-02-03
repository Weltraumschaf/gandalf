# Gandalf OS

[How to][how-to] make an operating system from scratch.

Why "Gandalf"?  I needed a "code  name" for the  GitHub repo and Gandalf  was my
first thought. Don't know why. I'm not really a Hobbit-fan.

## I only want to run it

If you don't want  to build your own cross compiler and build  the OS image from
scratch you  can use a  binary distribution from  the `dist` direcotry.  You can
run it e.g. with [QEMU][qemu]:

    $> qemu-system-i386 -cpu 486 -m 32 -fda dist/gandalf.img

## Prerequisites

What you need (for hacking and compiling):

- [NASM][nasm] assembler
- [binutils][binutils] for make and such
- [GCC][gcc] compiler (only for building cross compiler)
- [QEMU][qemu] to run the OS
- pbzip2 for creating the build tools

On Linux  this should be  no problem at  all. On Mac  OS X [home  brew][brew] is
recommended to  install the tools.  On Windows I  guess [CygWin][cyg] is  a good
choice (but I never tested it on Windows).

## Cross Compiler

To build the kernel  you need a cross compiler. A how-to  which explains qhy you
needa  cross compiler  is  provided [here][cross].  You have  to  edit the  file
`build-tools/environment` with the correct paths  to your GGC you have installed
on your  host (development)  machine as  a prerequisite.  After that  invoke the
built  script:  `build-tools/build.sh`. This  will  take  a  while and  build  a
freestanding  C compiler  for  the  kernel in  `build-tools/cross`  used by  the
`Makefile`.

__ATTENTION__: You  have to set  your GCC compiler  in `build-tools/environment`
first.

    $> cd build-tools
    $> ./build.sh

## Build the kernel

You should use a new temrinal session  so that your environment is fresh and not
polluted by environment varibales from building the cross compiler.

Build the kernel by invoking in the main direcotry:

    $> make

And running it in [QEMU][qemu] by invoking:

    $> make run

You can connect with gdb to the kernel. (Currently the whole kernel is compiled
with debug symbols by defautl.) First run OS in debug mode:

    $> make debug

Then connect with gdb:

    $> gdb
    (gdb) target remote localhost:1234

## Legal stuff

All my  work is licensed under  [the Beer-Ware License][beer]. But  I reuse some
third party libraries such as [klibc][klibc].  They may have less open licenses.
I add a license and source notice in each when it is not already mentioned.

## Architecture

How to [code C][howto-c].

### Terminal emulation - tty

The tty is defined in `kernel/tty.h`. It ptovides kernel API to initialize the
tty, set curos, color, and print characters and messages on the screen.

[how-to]:           http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
[nasm]:             http://www.nasm.us/
[binutils]:         https://www.gnu.org/software/binutils/
[gcc]:              http://gcc.gnu.org/
[brew]:             http://brew.sh/
[cyg]:              http://www.cygwin.com/
[cross]:            http://wiki.osdev.org/GCC_Cross-Compiler
[qemu]:             http://wiki.qemu.org/Main_Page
[beer]:             http://www.weltraumschaf.de/the-beer-ware-license.txt
[klibc]:            https://en.wikipedia.org/wiki/Klibc
[howto-c]:          https://matt.sh/howto-c
[howto-doxygen]:    http://fnch.users.sourceforge.net/doxygen_c.html