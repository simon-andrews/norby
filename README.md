# Norby [![Build Status](https://travis-ci.org/simon-andrews/norby.svg?branch=master)](https://travis-ci.org/simon-andrews/norby)
A hobby operating system. It's pretty okay. Here, enjoy a pretty GIF of a bug ([that has since been fixed](https://github.com/simon-andrews/norby/commit/b44de621e2c2d98cf7743f1b96d67912b7d24f2c)):

![Norby breaking.](https://gitlab.com/simon-andrews/norby/uploads/726fe5e6dd69d1e41d6fe2ce541c69fa/colortest_recording.gif)

## Requirements
 * A [cross-compilation toolchain targeting `i686-elf`](http://wiki.osdev.org/GCC_Cross-Compiler), based on [GCC](https://gcc.gnu.org/).
 * Regular old GCC would be useful, especially for running the libc test suite.
 * [NASM](http://www.nasm.us/), for compiling some of the project's assembly code.
 * [Paver](https://pythonhosted.org/Paver/), the project's build automation tool.
 * [Python 3](https://www.python.org/), for some other scripts.
 * [GRUB](https://www.gnu.org/software/grub/), because `grub-mkrescue` is used for generating bootable ISO images.
 * [QEMU](https://www.qemu.org/), for running Norby on a virtual machine.
 
 ## Repository structure
  * `grub/`: Configuration files for GRUB.
  * `kernel/`: The "meat" of the repository. Contains kernel code.
    * `asm/`: Assembly code for some stuff that can't be done in C.
    * `include/`: Header files for kernel C sources.
  * `libc/`: Source code for an implementation of the C standard library.
    * `include/`: Header files for the libc C sources.
    * `tests/`: Unit tests framework and suite for the libc. Linux only.
