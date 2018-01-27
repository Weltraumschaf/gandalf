# Gandalf OS

- [Writing an OS in Rust ](https://os.phil-opp.com)
    - [Set Up Rust](https://os.phil-opp.com/set-up-rust/)
- [A bunch of links](https://github.com/ctjhoa/rust-learning)
- [Setting up a Rust Development Environment](http://asquera.de/blog/2017-03-03/setting-up-a-rust-devenv/)

## Memory Layout

```
                        +-----------------------------+
                        | +-------------------------+ |
                        | |      kernel stack       | | 4096 * 4
                        | +-------------------------+ |
                        | +-------------------------+ |
reused to grow stack----+->        p2 table         | | 4096
                        | +-------------------------+ |
                        | +-------------------------+ |
reused to grow stack----+->        p3 table         | | 4096
                        | +-------------------------+ |
                        | +-------------------------+ |
become gurad page-------+->        p4 table         | | 4096
                        | +-------------------------+ |
                        |            ...              |
                        | +-------------------------+ | 0x0016_3160
                        | |    multiboot header     | |
                        | +-------------------------+ | 0x0016_2a58
                        | +-------------------------+ | 0x0015_99b0
                        | |         kernel          | |
                        | +-------------------------+ | 0x0010_0000
                        | +-------------------------+ |
                        | |       vga buffer        | |
                        | +-------------------------+ | 0x000b_8000
                        |            ...              |
                        +-----------------------------+ 0x0000_0000
```