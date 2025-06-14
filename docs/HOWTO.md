# How to use the VDP_SPRITES_MSXBIOS Library

| Attention! |
| :---       |
| The following document has been written using an English translator.<br/>You can participate in the improvement of this document, transmitting your corrections or suggestions in the issues of this project or the main fR3eL project.<br/>Thanks for understanding. |

<br/>

## Index

- [1 Description](#1-Description)
- [2 Requirements](#2-Requirements)
- [3 Definitions](#3-Definitions)
    - [3.1 Color Names](#31-Color-Names)
- [4 Functions](#4-Functions)
	- [4.1 SetSpritePattern](#41-SetSpritePattern)
	- [4.2 SetSpriteColor](#42-SetSpriteColor)
	- [4.3 SetSpritePosition](#43-SetSpritePosition)
	- [4.4 SetSpriteVisible](#44-SetSpriteVisible)
	- [4.5 SetEarlyClock](#45-SetEarlyClock)
	- [4.6 UnsetEarlyClock](#46-UnsetEarlyClock)
- [5 How does it work?](#5-How-does-it-work)
	- [5.1 TEXT 1 and TEXT 2 modes](#51-TEXT-1-and-TEXT-2-modes)
	- [5.2 GRAPHIC 1 mode](#52-GRAPHIC-1-mode)
	- [5.2.1 Set GRAPHIC 1 Colors](#521-Set-GRAPHIC-1-Colors)
	- [5.3 More things](#53-More-things)
- [6 Code Example](#6-Code-Example)
- [7 References](#8-References)


- [7 Appendices](#7-Appendices)
    - [7.1 Escape sequences](#71-Escape-sequences)
	- [7.2 Other scape codes](#72-Other-scape-codes)
	- [7.3 Extended Graphic Characters](#73-Extended-Graphic-Characters)



<br/>

---

## 1 Description



<br/>

---

## 2 Requirements

- [Small Device C Compiler (SDCC) v4.4](http://sdcc.sourceforge.net/)
- [Hex2bin v2.5](http://hex2bin.sourceforge.net/)
- fR3eL [VDP_TMS9918A_MSXBIOS](https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib) Library


<br/>

---

## 3 Definitions

### 3.1 Color Names

Label		| Value
:---		| ---:
TRANSPARENT	| 0
BLACK		| 1
GREEN		| 2
LIGHT_GREEN	| 3
DARK_BLUE	| 4
LIGHT_BLUE	| 5
DARK_RED	| 6
CYAN		| 7
RED			| 8
LIGHT_RED	| 9
DARK_YELLOW	| 10
LIGHT_YELLOW	| 11
DARK_GREEN	| 12
MAGENTA		| 13
GRAY		| 14
GREY		| 14
WHITE		| 15


<br/>

---


## 4 Functions


### 4.1 SetSpritePattern

<table>
<tr><td colspan=3><b>SetSpritePattern</b></td></tr>
<tr><td colspan=3>Assign a pattern to a sprite plane</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetSpritePattern(char plane, char pattern)</td></tr>
<tr><th rowspan=2>Input</th><td><pre>char</pre></td><td>sprite plane (0-31)</td></tr>
<tr><td><pre>char</pre></td><td>pattern</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetSpritePattern(4, 2);
	SetSpritePattern(7, numPat);
```

<br/>

### 4.2 SetSpriteColor

<table>
<tr><td colspan=3><b>SetSpriteColor</b></td></tr>
<tr><td colspan=3>Assign a color to a sprite plane</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetSpriteColor(char plane, char color)</td></tr>
<tr><th rowspan=2>Input</th><td><pre>char</pre></td><td>sprite plane (0-31)</td></tr>
<tr><td><pre>char</pre></td><td>color (0-15)</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetSpriteColor(4, 6);
	SetSpriteColor(7, DARK_RED); //Color label requires include in VDP_TMS9918A_MSXBIOS.h
```

<br/>

### 4.3 SetSpritePosition

<table>
<tr><td colspan=3><b>SetSpritePosition</b></td></tr>
<tr><td colspan=3>Assigns the position coordinates of a sprite plane</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetSpritePosition(char plane, char x, char y)</td></tr>
<tr><th rowspan=3>Input</th><td><pre>char</pre></td><td>sprite plane (0-31)</td></tr>
<tr><td><pre>char</pre></td><td>x</td></tr>
<tr><td><pre>char</pre></td><td>y</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetSpritePosition(4, 100, 80);
	SetSpritePosition(7, spr_Xpos, spr_Ypos);
```

<br/>

### 4.4 SetSpriteVisible

<table>
<tr><td colspan=3><b>SetSpriteVisible</b></td></tr>
<tr><td colspan=3>Hides or shows a sprite plane</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetSpriteVisible(char plane, char state)</td></tr>
<tr><th rowspan=2>Input</th><td><pre>char</pre></td><td>sprite plane (0-31)</td></tr>
<tr><td><pre>char</pre></td><td>[char] or [boolean]/[switcher] visible state:<br/>0/false/OFF = hidden; 1/true/ON = visible</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetSpriteVisible(4,0);		//hidden
	SetSpriteVisible(7,false);	//hidden ()
	SetSpriteVisible(8,ON);		//visible ()
```

<br/>

### 4.5 SetEarlyClock

<table>
<tr><td colspan=3><b>SetEarlyClock</b></td></tr>
<tr><td colspan=3>Apply the Early Clock of a sprite plane.<br/>Move 32 points to the left the X position of the Sprite.</td></tr>
<tr><td><b>Function</b></td><td colspan=2>SetEarlyClock(char plane)</td></tr>
<tr><th>Input</th><td><pre>char</pre></td><td>sprite plane (0-31)</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	SetEarlyClock(4);
```

<br/>

### 4.6 UnsetEarlyClock

<table>
<tr><td colspan=3><b>UnsetEarlyClock</b></td></tr>
<tr><td colspan=3>Disables the Early Clock.<br/>Restore the position of a Sprite plane.</td></tr>
<tr><td><b>Function</b></td><td colspan=2>UnsetEarlyClock(char plane)</td></tr>
<tr><th>Input</th><td><pre>char</pre></td><td>sprite plane (0-31)</td></tr>
<tr><th>Output</th><td colspan=2>---</td></tr>
</table>

#### Example:

```c
	UnsetEarlyClock(4);
```

<br/>

---

## 5 How does it work?



<br/>

### 5.1 

<br/>

---

## 6 Code Example

In the following source code you can see a simple example of using the library. 

You can find more extensive examples in the git project sources.

<br/>

### Source
```c
/* =====================================================
   Example TEXTMODE MSX ROM Library (fR3eL Project)
======================================================== */

#include "../include/textmode_MSX.h"

const char text01[] = "Example TEXTMODE Lib\n";
const char text02[] = "Press a key to continue";

void main(void)
{
  unsigned int uintValue=1234;
  char charValue=71;
  
  COLOR(WHITE,DARK_BLUE,LIGHT_BLUE);
  WIDTH(40);
  SCREEN0();
  
  PrintLN(text01);
  
  PRINT("Line 1\n");
  PrintLN("Line 2");
  PrintLN("Line 3\n");
    
  PRINT("\1\x42");   //print smile (2 + 64) = 42 hexadecimal
  PRINT("\n");
  
  PRINT("\n>PrintNumber:");
  PrintNumber(1024);
  
  PRINT("\n>PrintFNumber:");
  PrintFNumber(charValue,'0',4); //"0071"
  
  PRINT("\n>Print Integer:");
  PrintFNumber(uintValue,32,5); //" 1234"
  
  PRINT("\n>Print cut number:");
  PrintFNumber(uintValue,32,2); //"34"
  
  LOCATE(8,20);
  PRINT(text02);
    
__asm   
  call  0x009F ;BIOS CHGET One character input (waiting)
  rst   0
__endasm;
}
```

### Output

![Example screenshot](pics/ExampleROM_screenshot.png)


<br/>

---

## 7 References

- MSX Resource Center > [Wiki](https://www.msx.org/wiki/) > Main-ROM BIOS > [1.3 Displaying ](https://www.msx.org/wiki/Main-ROM_BIOS#Displaying)
- MSX Resource Center > [Wiki](https://www.msx.org/wiki/) > [MSX Characters and Control Codes](https://www.msx.org/wiki/MSX_Characters_and_Control_Codes)
- Wikipedia > [Escape sequences in C](https://en.wikipedia.org/wiki/Escape_sequences_in_C)
- Wikipedia > [Newline](https://en.wikipedia.org/wiki/Newline)

<br/>

---

![Creative Commons License](https://i.creativecommons.org/l/by-nc/4.0/88x31.png) 
<br/>This document is licensed under a [Creative Commons Attribution-NonCommercial 4.0 International License](http://creativecommons.org/licenses/by-nc/4.0/).
