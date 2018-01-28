# Gandalf OS

- [Writing an OS in Rust ](https://os.phil-opp.com)
- [Bare Metal Rust: Building kernels in Rust](http://www.randomhacks.net/bare-metal-rust/)
- [x86 Disassembly](https://en.wikibooks.org/wiki/X86_Disassembly)
- [Redox](https://github.com/redox-os/redox)
- [Rust Documentation](https://www.rust-lang.org/en-US/documentation.html)
- Rust
    - [A bunch of links](https://github.com/ctjhoa/rust-learning)
    - [Setting up a Rust Development Environment](http://asquera.de/blog/2017-03-03/setting-up-a-rust-devenv/)

## Preparation

Before you can begin you need some cross compiled tools

```
./build-tools.sh
```

and the generated `opt/bin` to your path

```
export PROJECT_HOME=`pwd`
export PATH="${PROJECT_HOME}/opt/bin:${PATH}"
```

Or if you have `direnv` installed just run

```
direnv allow .
```

After that you need to set up Rust as described in [the tutorial](https://os.phil-opp.com/set-up-rust/) this OS is based on.

## Debugging

Start GDB with:

```
rust-gdb "build/kernel-x86_64.bin" -ex "target remote :1234"
```

## Memory Layout

```
                        +-----------------------------+
                        | +---------bottom----------+ |
                        | |      kernel stack       | | 4096 * 4
                        | |            |            | |
                        | |            v            | |
                        | +----------top------------+ |
                        | +-------------------------+ |
reused to grow stack------>        p2 table         | | 4096
                        | +-------------------------+ |
                        | +-------------------------+ |
reused to grow stack------>        p3 table         | | 4096
                        | +-------------------------+ |
                        | +-------------------------+ |
become gurad page--------->        p4 table         | | 4096
                        | +-------------------------+ |
                        |            ...              |
                        | +-------------------------+ | 0x0016_3160
                        | |    multiboot header     | |
                        | +-------------------------+ | 0x0016_2a58
                        |            ...              |
                        | +-------------------------+ | 0x0015_99b0
                        | |         kernel          | |
                        | +-------------------------+ | 0x0010_0000
                        |            ...              |
                        | +-------------------------+ |
                        | |       vga buffer        | |
                        | +-------------------------+ | 0x000b_8000
                        |            ...              |
                        +-----------------------------+ 0x0000_0000
```