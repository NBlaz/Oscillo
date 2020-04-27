#!/bin/sh

st-util & gdb ./build/TemplateProjekt.elf -ex "target extended-remote:4242" -ex "layout src" && fg
