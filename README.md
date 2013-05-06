![Whitebox](https://raw.github.com/testaco/whitebox/master/docs/img/whitebox.png)
The Smart Software Radio Device
===============================

Welcome to the Whitebox Software Radio Project, a cross between a smartphone
and a software defined radio with an open hardware and software license.

Directory Structure
-------------------
* cmake: Toolchains and modules for cmake
* docs: Documentation for the project
* driver: The Kernel driver for the Whitebox radio board
* gnuradio: Tools for using the Whitebox as a GNURadio peripheral
* hdl: Hardware description in MyHDL for the FPGAs DSP flow
* lib: A userspace library for interacting with the radio board
* linux-cortexm: Tools for building the uClinux Kernel for the ARM Cortex-M
  class of processors.
* util: Utility Python scripts

Getting Started
---------------

# Get the repo
$ git clone https://github.com/testaco/whitebox
$ cd whitebox
# Bootstrap your toolchain
whitebox$ sh bootstrap.sh
whitebox$ cd build
# Configure with cmake
whitebox/build$ cmake ..
# Build the user space library
whitebox/build$ make
# Patch the kernel, do this only ONCE
whitebox/build$ make linux_patch
# Build the kernel
whitebox/build$ make linux
# Build the drivers
whitebox/build$ make drivers
# Generate and test the hdl Verilog code
whitebox/build$ make hdl
# Build the documentation
whitebox/build$ make docs

