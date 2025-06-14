/* ============================================================================= 
# VDP SPRITE MSX BIOS SDCC Library (fR3eL Project)

- Version: 1.4 (12/06/2025)
- Author: mvac7/303bcn
- Architecture: MSX
- Format: C object (SDCC .rel)
- Programming language: C and Z80 assembler
- Compiler: SDCC 4.4 or newer 

## Description:
Open Source library with functions to directly access to sprites of the 
TMS9918A.

It uses the functions from the MSX BIOS, so it is designed to create 
applications in ROM format.

It's complemented with the VDP TMS9918A MSX ROM SDCC Library
https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib

## History of versions (dd/mm/yyyy):
- v1.4 (12/06/2025) Remove PUTSPRITE function (add to VDP_TMS9918A_MSXBIOS Lib)
- v1.3 (09/06/2025) Update to SDCC (4.1.12) Z80 calling conventions
- v1.2 (22/12/2020) Removed sprite mode initialization functions.
- v1.1 ( 2/ 2/2017) 
- v1.0 ?                   
============================================================================= */ 

#include "../include/msxSystemVariables.h"
#include "../include/msxBIOS.h"

#include "../include/VDP_SPRITES.h"



#define YHIDDEN  217


char SPRITEYBUFF[32];




/* =============================================================================
SetSpritePattern
Description: 
		Assign a pattern to a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] pattern
Output:	-
============================================================================= */
void SetSpritePattern(char plane, char pattern)
{
plane;		//A
pattern;	//L
__asm

	ld   C,L
	
//num sprite plane  
	call BIOS_CALATR	//Returns the address of the sprite attribute table --> HL
	inc  HL
	inc  HL

//Set sprite pattern number
//Multiply * 4 when its a 16x16 sprite 
	call BIOS_GSPSIZ          ;0x008A get sprite size in bytes (Carry flag set when size is 16×16)
	jr   NC,_setSprPat

//IF 16x16
	SLA  C
	SLA  C ;x 4 

//write to VRAM (OAM)
_setSprPat:
	ld   A,C
	jp   BIOS_WRTVRM 
__endasm;
}



/* =============================================================================
SetSpriteColor
Description: 
		Assign a color to a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] color (0-15)
Output:	-
============================================================================= */
void SetSpriteColor(char plane, char color) __naked
{
plane;	//A
color;	//L
__asm

	ld   C,L
	
	call BIOS_CALATR	//Returns the address of the sprite attribute table --> HL

	inc  HL
	inc  HL
	inc  HL
	
//read the value and check if the EarlyClock bit is set
	call BIOS_RDVRM		//Read VRAM
	bit  7,A
	ld   A,C
	jp   Z,BIOS_WRTVRM	//write to VRAM (OAM) without EarlyClock
	OR   #128			//turn EarlyClock bit ON
	jp   BIOS_WRTVRM	//write to VRAM (OAM)

__endasm;
}



/* =============================================================================
SetSpritePosition
Description: 
		Assigns the position coordinates of a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] x 
		[char] y
Output:	-
============================================================================= */
void SetSpritePosition(char plane, char x, char y)
{
plane;	//A
x;		//L
y;		//Stack
__asm
	push IX
	ld   IX,#0
	add  IX,SP
	
	ld   C,L
  
;A=sprite plane
	call BIOS_CALATR	//Returns the address of the sprite attribute table --> HL
  
;y value
	ld   A,4(ix)   ;x
	call BIOS_WRTVRM	//write to VRAM (OAM)

;x value
	inc  HL
	ld   A,C
	call BIOS_WRTVRM	//write to VRAM (OAM)

	pop  IX
__endasm;
}



/* =============================================================================
SetSpriteVisible
Description: 
		Hides or shows a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] or [boolean]/[switcher] visible state: 
									0/false/OFF = hidden; 1/true/ON = visible
Output:	-
============================================================================= */
void SetSpriteVisible(char plane, char state)  __naked
{
plane;	//A
state;	//L
__asm
        
	ld   C,L

	ld   IY,#_SPRITEYBUFF
	ld   D,#0
	ld   E,A
	ADD  IY,DE
  
	call BIOS_CALATR	//Returns the address of the sprite attribute table --> HL

	ld   A,C
	or   A ;0 = off
	jr   Z,SPRITEOFF
  
;sprite ON
	ld   A,(IY)

	jp   BIOS_WRTVRM	//write to VRAM (OAM)


;sprite OFF
SPRITEOFF:
	call BIOS_RDVRM
	cp   #YHIDDEN
	ret   Z		//if not visible then Dont overwrite. 
  
	ld   (IY),A
	ld   A,#YHIDDEN
	jp   BIOS_WRTVRM	//write to VRAM (OAM)
  
__endasm;
}



/* =============================================================================
SetEarlyClock
Description: 
		Apply the Early Clock of a sprite plane. 
		Move 32 points to the left the X position of the sprite.
Input:	[char] sprite plane (0-31) 
Output:	-
============================================================================= */
void SetEarlyClock(char plane) __naked
{
plane;	//A
__asm

  call BIOS_CALATR	//Returns the address of the sprite attribute table --> HL
  
  inc  HL
  inc  HL
  inc  HL
  call BIOS_RDVRM  ;VPEEK
  OR   #128
  jp   BIOS_WRTVRM ;VPOKE  

__endasm;
}



/* =============================================================================
UnsetEarlyClock
Description:
		Disables the Early Clock. Restore the position of a sprite plane.
Input:	[char] sprite plane (0-31)
Output:	-
============================================================================= */
void UnsetEarlyClock(char plane) __naked
{
plane;	//A
__asm

  call BIOS_CALATR	//Returns the address of the sprite attribute table --> HL
  
  inc  HL
  inc  HL
  inc  HL
  call BIOS_RDVRM
  and  #127
  jp   BIOS_WRTVRM
  
__endasm;
}