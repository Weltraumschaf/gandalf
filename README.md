# Gandalf OS

- [Writing an OS in Rust][os-tutorial]
- [Bare Metal Rust: Building kernels in Rust](http://www.randomhacks.net/bare-metal-rust/)
- [x86 Disassembly](https://en.wikibooks.org/wiki/X86_Disassembly)
- [Redox](https://github.com/redox-os/redox)
- Rust
    - [Rust Documentation](https://www.rust-lang.org/en-US/documentation.html)
    - [A bunch of links](https://github.com/ctjhoa/rust-learning)
    - [Setting up a Rust Development Environment](http://asquera.de/blog/2017-03-03/setting-up-a-rust-devenv/)

## Preparation

Before you can begin you need some cross compiled tools (this will take a while)

```
./build-tools.sh
```

and the generated `opt/bin` to your path

```
export PROJECT_HOME=`pwd`
export PATH="${PROJECT_HOME}/opt/bin:${PATH}"
```

Or if you have [direnv](https://direnv.net/) installed just run

```
direnv allow .
```

After that you need to set up [Rust](https://www.rust-lang.org) as described in [the tutorial](https://os.phil-opp.com/set-up-rust/) this OS is based on

```
rustup override add nightly
```

Then you can build the kernel

```
make
```

and run it (you need [QEMU](https://www.qemu.org/) installed)

```
make run
```

## Debugging

Start GDB with:

```
rust-gdb "build/kernel-x86_64.bin" -ex "target remote :1234"
```

## Memory Layout

By default the QEMU VM has 128 mb memory size:

- this is equal to 134.217.728 bytes
- in 64 bit: 134.217.728 / 8 bytes = 16.777.216, so
    - start address is `0x0000_0000` 
    - end address is `0x0100_0000`

```
                        +-----------------------------+<-- 0x0100_0000
                        | +---------bottom----------+ |
                        | |      kernel stack       | | (4096 * 4 = 16 KiB)
                        | +----------top------------+ |
                        |             |               | 
                        |             v               |
                        |            ...              |
                        | +-------------------------+ |
reused to grow stack----->|        p2 table         | | (4096 = 4 KiB)
                        | +-------------------------+ |
                        | +-------------------------+ |
reused to grow stack----->|        p3 table         | | (4096 = 4 KiB)
                        | +-------------------------+ |
                        | +-------------------------+ |
become gurad page-------->|        p4 table         | | (4096 = 4 KiB)
                        | +-------------------------+ |
                        |            ...              |
                        | +-------------------------+<+--- 0x0016_3160
                        | |    multiboot header     | |
                        | +-------------------------+<+--- 0x0016_2a58
                        |            ...              |
                        | +-------------------------+<+--- 0x0015_99b0
                        | |         kernel          | |
below is reserved ------->+-------------------------+<+--- 0x0010_0000
                        |            ...              |
                        | +-------------------------+<+--- 0x000B_87D0
25 * 80 = 2000 bytes ---->|       vga buffer        | |
                        | +-------------------------+<+--- 0x000b_8000
                        |            ...              |
                        +-----------------------------+<-- 0x0000_0000
```

## Licenses and Copying

Almost all code is from the tutorial [Writing an OS in Rust][os-tutorial] from _Philipp Oppermann_ hosted on [GitHub](https://github.com/phil-opp/blog_os). So I copied the licenses from that repo too.

[os-tutorial]:  https://os.phil-opp.com