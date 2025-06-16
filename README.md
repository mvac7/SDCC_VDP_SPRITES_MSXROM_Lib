# VDP SPRITES MSX BIOS SDCC Library (fR3eL Project)

<table>
<tr><td>Name</td><td>VDP_SPRITES_MSXBIOS</td></tr>
<tr><td>Architecture</td><td>MSX</td></tr>
<tr><td>Format</td><td>C Object (SDCC .rel)</td></tr>
<tr><td>Programming language</td><td>C and Z80 assembler</td></tr>
<tr><td>Compiler</td><td>SDCC v4.4 or newer</td></tr>
</table>

<br/>

## Description

Open Source library with functions to directly access to sprites of the TMS9918A.

Provides a set of specific functions to handle Sprites such as positioning, color, pattern assignment, visibility and EarlyClock.

This is intended for use only with the TMS9918A VDP. It can be used in Graphic3 mode (Screen 4) on the V9938 or higher, but will not display correctly, as the color mapping and EarlyClock functions will not work because they must write to a separate color table. 
This functionality has not been added to reduce size.



It is complemented with the [VDP TMS9918A MSXBIOS Library](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib), necessary for the initialization of the screen (screen and sprites mode).



It uses the functions from the MSX BIOS, so it is designed to create applications in ROM or MSXBASIC environments.

Since the current version you can display moving figures (Sprites), using the PUTSPRITE function (similar to MSX-BASIC), but you also have the [VDP_SPRITES_MSXBIOS](https://github.com/mvac7/SDCC_VDP_SPRITES_MSXROM_Lib) library that improves the management of Sprite parameters.

You also have a [VDP_TMS9918A](https://github.com/mvac7/SDCC_VDP_TMS9918A_Lib) library where all functions are programmed without using the BIOS. It is designed for use in environments such as DOS or 48K ROMs, although you can also use it in other environments such as ROMs or MSX-BASIC. 
The advantage of using the BIOS is that the library is more compact and guarantees compatibility between different MSX models, but it has the disadvantage of being slow.

Use them for developing MSX applications using [Small Device C Compiler (SDCC)](http://sdcc.sourceforge.net/) cross compiler.

You can access the documentation here with [`How to use the library`](docs/HOWTO.md).

These libraries are part of the [MSX fR3eL Project](https://github.com/mvac7/SDCC_MSX_fR3eL).

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
- fR3eL [VDP_TMS9918A_MSXBIOS](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib) Library




## Functions

| Name | Declaration | Description |
| ---  | ---   | ---         |
| SetSpritePattern  | `SetSpritePattern(char plane, char pattern)` | Assign a pattern to a sprite plane |
| SetSpriteColor    | `SetSpriteColor(char plane, char color)` | Assign a color to a sprite plane |
| SetSpritePosition | `SetSpritePosition(char plane, char x, char y)` | Assigns the position coordinates of a sprite plane |
| SetSpriteVisible  | `SetSpriteVisible(char plane, char state)` | Hides or shows a sprite plane |
| SetEarlyClock     | `SetEarlyClock(char plane)` | Apply the Early Clock of a sprite plane. Move 32 points to the left the X position of the sprite |
| UnsetEarlyClock   | `UnsetEarlyClock(char plane)` | Disables the Early Clock. Restore the position of a sprite plane |
