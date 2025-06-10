# VDP SPRITES MSX ROM SDCC Library (fR3eL Project)

<table>
<tr><td>Architecture</td><td>MSX</td></tr>
<tr><td>Format</td><td>C Object (SDCC .rel)</td></tr>
<tr><td>Programming language</td><td>C and Z80 assembler</td></tr>
<tr><td>Compiler</td><td>SDCC v4.4 or newer</td></tr>
</table>

---

## Description

Open Source library with functions to directly access to sprites of the TMS9918A.

Provides a set of functions for displaying Sprites, both fully (PUTSPRITE) and specific (positioning, color, pattern, visibility and EarlyClock).

Contains the PUTSPRITE function similar to that of MSX BASIC.

Allows you to work with in G3 screen mode (V9938), but color cannot be assigned. 
I require that we write the colors of the 8/16 lines of each sprite plane in the Sprite Color Table (VRAM 1C00h). 
The same will happen, for the Early Clock attribute. 
The functions of this library will not take effect. 
Bit 7 (EC) must be modified for each line of the sprite plane of the same color table. 
More information in the [9938 Technical Data Book](http://map.grauw.nl/resources/video/v9938/v9938.xhtml).

It is complemented with the [VDP TMS9918A MSX ROM Library](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib), necessary for the initialization of the screen (screen and sprites mode).

It uses the functions from the MSX BIOS, so it is designed to create applications in ROM format.
  
You can access the documentation here with [`How to use the library`](docs/HOWTO.md).

These libraries are part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

Use them for developing MSX applications using Small Device C Compiler [`SDCC`](http://sdcc.sourceforge.net/).

This project is an Open Source. 
You can add part or all of this code in your application development or include it in other libraries/engines.

Enjoy it!

<br/>



### About the Sprite libraries

I'm developing several libraries for the management of MSX Sprites, both for the creation of ROMs (using the BIOS), and MSX-DOS executables.
 
They are designed for the development of applications for the first generation of MSX but some of the variations are directed in how certain functions behave when using the G3 mode of the video processor V9938 and thus be able to take advantage of it, when it is executed in a MSX2 or higher.

To optimize our development, I recommend building your library with only those functions you need.

I have yet to develop a library to work with the multi-colored Sprites of the V9938.



## History of versions

- v1.2 (22/12/2020) Removed sprite mode initialization functions.
- v1.1 (2/02/2017)
- v1.0 ?



## Requirements

- [Small Device C Compiler (SDCC) v4.4](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)
- fR3eL [VDP TMS9918A MSX BIOS Library](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib).




## Functions

| Name | Declaration | Description |
| ---  | ---   | ---         |
| PUTSPRITE         | `PUTSPRITE(char plane, char x, char y, char color, char pattern)` | Displays the sprite pattern |
| SetSpritePattern  | `SetSpritePattern(char plane, char pattern)` | Assign a pattern to a sprite plane |
| SetSpriteColor    | `SetSpriteColor(char plane, char color)` | Assign a color to a sprite plane |
| SetSpritePosition | `SetSpritePosition(char plane, char x, char y)` | Assigns the position coordinates of a sprite plane |
| SetSpriteVisible  | `SetSpriteVisible(char plane, char state)` | Hides or shows a sprite plane |
| SetEarlyClock     | `SetEarlyClock(char plane)` | Apply the Early Clock of a sprite plane. Move 32 points to the left the X position of the sprite |
| UnsetEarlyClock   | `UnsetEarlyClock(char plane)` | Disables the Early Clock. Restore the position of a sprite plane |
