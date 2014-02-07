# Gandalf OS

[How to][1] make an operating system from scratch.

## [Cross Compiler][2]

## libiconv

  LDFLAGS:  -L/usr/local/opt/libiconv/lib
  CPPFLAGS: -I/usr/local/opt/libiconv/include
  
### GCC

  export CC=/usr/local/bin/gcc-4.2
  export CXX=/usr/local/bin/g++-4.2
  export CPP=/usr/local/bin/cpp-4.2
  export LD=/usr/local/bin/gcc-4.2
  ./configure --with-libiconv-prefix=/usr/local/opt

[1]: http://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
[2]: http://wiki.osdev.org/GCC_Cross-Compiler
