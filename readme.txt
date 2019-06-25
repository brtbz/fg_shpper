Fantasy General SHP-file extractor v1.0 by brtbz
================================================
Extracts images from Fantasy General SHP-files and saves them in 32-bit RGBA PNGs.
Fantasy General is a cool computer game by SSI originally released in 1996.
Tested on Linux and Windows. Would probably work on Mac too.


USAGE
=====
examples:
shpper.exe UIF0.SHP
shpper.exe -x UIF0.SHP (same as above)
shpper.exe -d UIF0.SHP (transparent pixels replaced by weird debug colors, oh yeah!)


DOWNLOADS
=========
Binaries for Windows will be here as soon as I can figure how it's done here on github


BUILDING
========
Building shouldn't require anything but the basic build tools that can compile C programs.

Linux
GCC: (tested with GCC 7.4.0)
cc -std=c99 shpper.c -lm -o fg_shpper

Windows
MSVC: (tested with MSVC 2015 (cl.exe version 19.00.24210 for x64))
cl.exe /TC /Fefg_shpper shpper.c /link /subsystem:console


NOTES AND LIMITATIONS
=====================
Takes only single input file, but you can use the provided .bat and .sh script-files that run
the program for all the SHP files in the current directory. If you run either of them in FG's
SHP directory, that should produce over 4800 png files.

I'm not absolutely certain about the palette used, but it seems to be pretty close.

Parser might have some (off-by-one) errors, but then again it seems to produce the correct output.


ADDITIONAL CREDITS
==================
Panzer General 2 file specifications by Luis Guzman
PNG writer by Sean Barrett
