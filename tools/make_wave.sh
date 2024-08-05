#!/bin/bash

# This script is to build wave executable

GCC_LINUX=gcc
GCC_WINDW=i686-w64-mingw32-gcc

# Build wave for Linux to run on both 32 & 64 bit OS
$GCC_LINUX -o wave.run wave.c -static #-m32
file wave.run

# Build wave for Windows to run on both 32 & 64 bit OS
$GCC_WINDW -o wave.exe wave.c -static #-m32
file wave.exe
