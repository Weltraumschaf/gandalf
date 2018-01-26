# Gandalf OS

- [Writing an OS in Rust ](https://os.phil-opp.com)
    - [Set Up Rust](https://os.phil-opp.com/set-up-rust/)
- [A bunch of links](https://github.com/ctjhoa/rust-learning)
- [Setting up a Rust Development Environment](http://asquera.de/blog/2017-03-03/setting-up-a-rust-devenv/)

## Memory Layout

```
+-----------------------------+
| +-------------------------+ |
| |          stack          | |
| +------------+------------+ |
|              |              |
|              v              |
|                             |
|              ^              |
|              |              |
| +------------+------------+ |
| |          heap           | |
| +-------------------------+ |
| +-------------------------+ |
| |         kernel          | |
| +-------------------------+ | 0x0010_0000
| +-------------------------+ |
| |       vga buffer        | |
| +-------------------------+ | 0x000b_8000
|                             |
+-----------------------------+ 0x0000_0000
```