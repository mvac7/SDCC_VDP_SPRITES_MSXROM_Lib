/* ============================================================================= 
  VDP SPRITE MSX ROM SDCC Library (fR3eL Project)
  Version: 1.2 (22/12/2020)
  Author: mvac7 [mvac7303b@gmail.com]
  Architecture: MSX
  Format: C Object (SDCC .rel)
  Programming language: C and Z80 assembler

  Description:
    Open Source library with functions to directly access to sprites of the 
    TMS9918A.
    
    It uses the functions from the MSX BIOS, so it is designed to create 
    applications in ROM format.
    
    It's complemented with the SDCC TMS9918A MSX ROM Library.
    https://github.com/mvac7/SDCC_VDP_TMS9918A_MSXROM_Lib
    
    For SDCC 3.9 or higher. 
    
  History of versions:
    v1.2 (22/12/2020) Removed sprite mode initialization functions.
    v1.1 (2/2/2017)
    v1.0 ?                   
============================================================================= */ 

#include "../include/VDP_SPRITES.h"

#include "../include/msxSystemVars.h"
#include "../include/msxBIOS.h"


#define YHIDDEN  217


char SPRITEYBUFF[32];




/* =============================================================================
 ClearSprites
 Description: 
             Initialises all sprite data The sprite pattern is cleared to
             null, the sprite number to the sprite plane number, the
             sprite colour to the foregtound colour. The vertical location
             of the sprite is set to 209 (mode 0 to 3) or 217 (mode 4 to 8).
 Input:       -
 Output:      -
============================================================================= */
void ClearSprites()
{
__asm
  call CLRSPR
__endasm;
}    



/* =============================================================================
 PUTSPRITE
 Description: Displays the sprite pattern.
 Input:       [char] sprite plane (0-31) 
              [char] x 
              [char] y
              [char] color (0-15)
              [char] pattern
 Output:      -
============================================================================= */
void PUTSPRITE(char plane, char x, char y, char color, char pattern)
{
plane;x;y;color;pattern;
__asm
  push IX
  ld   IX,#0
  add  IX,SP

  ld   A,4(IX) ;num sprite plane
  call CALATR
  
  ld   A,6(IX) ;y
  call WRTVRM
  
  inc  HL  
  ld   A,5(IX) ;x
  call WRTVRM
  
  inc  HL  
  ld   E,8(IX)
  call SPRPATNOV  ;pattern
  
  inc  HL
  ld   A,7(IX) ;color
  call WRTVRM
  
  pop  IX
__endasm;
}



/* =============================================================================
 SetSpritePattern
 Description: Assign a pattern to a sprite plane.
 Input:       [char] sprite plane (0-31) 
              [char] pattern
 Output:      -
============================================================================= */
void SetSpritePattern(char plane, char pattern)
{
plane;pattern; 
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   A,4(ix) ;num sprite plane  
  call CALATR  ;get vram address
  inc  HL
  inc  HL
  
  ld   E,5(ix) ;number of pattern to assign  
  call SPRPATNOV
  
  pop  IX
  ret
  


; set sprite pattern number
; Multiply * 4 when its a 16x16 sprite.
; E - Sprite Number  
SPRPATNOV:  ;sprite pattern no calc vram address
  call GSPSIZ          ;0x008A get sprite size in bytes 
  cp   #32             ;16x16
  jr   NZ,WRTPAT

  ;si es 16x16
  SLA  E
  SLA  E ;multiplica x4  

WRTPAT:
  LD   A,E
  call WRTVRM
   
  ;ret  
__endasm;
}



/* =============================================================================
 SetSpriteColor
 Description: Assign a color to a sprite plane.
 Input:       [char] sprite plane (0-31) 
              [char] color (0-15)
 Output:      -
============================================================================= */
void SetSpriteColor(char plane, char color)
{
plane;color;
__asm
  push IX
  ld   IX,#0
  add  IX,SP

  ld   A,4(IX) ;num sprite plane
  call CALATR

  inc  HL
  inc  HL
  inc  HL
  
  ld   A,5(IX) ;color
  call WRTVRM
  
  pop  IX

__endasm;
}



/* =============================================================================
 SetSpritePosition
 Description: Assigns the position coordinates of a sprite plane.
 Input:       [char] sprite plane (0-31) 
              [char] x 
              [char] y
 Output:      -
============================================================================= */
void SetSpritePosition(char plane, char x, char y)
{
plane;x;y;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   A,4(ix) ;num sprite
  call CALATR
  
  ld   A,6(ix)   ;y
  call WRTVRM
  
  inc  HL
  ld   A,5(ix)   ;x
  call WRTVRM
  
  pop  IX
__endasm;
}



/* =============================================================================
 SetSpriteVisible
 Description: Hides or shows a sprite plane.
 Input:       [char] sprite plane (0-31) 
              [boolean] visible state
 Output:      -
============================================================================= */
void SetSpriteVisible(char plane, boolean state)
{
plane;state;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
        
  ld   A,4(ix) ;num sprite
  
  ld   IY,#_SPRITEYBUFF
  ld   D,#0
  ld   E,A
  ADD  IY,DE
  
  call CALATR

  ld   A,5(ix) ;state
  or   A ;0 = off
  jr   Z,SPRITEOFF
  
;sprite ON
  ld   A,(IY)
  
  call WRTVRM
    
  pop  IX
  ret


;sprite OFF
SPRITEOFF:
  call RDVRM
  cp   #YHIDDEN
  jr   Z,ENDOFF ;if not visible then Dont overwrite. 
  
  ld   (IY),A
  ld   A,#YHIDDEN
  call WRTVRM
  
ENDOFF:
  pop  IX
__endasm;
}



/* =============================================================================
 SetEarlyClock
 Description: Apply the Early Clock of a sprite plane. Move 32 points to the 
              left the X position of the sprite.
 Input:       [char] sprite plane (0-31) 
 Output:      -
============================================================================= */
void SetEarlyClock(char plane)
{
plane;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   A,4(IX) 
  call CALATR
  
  inc  HL
  inc  HL
  inc  HL
  push HL
  call RDVRM  ;VPEEK
  OR   #128
  pop  HL
  call WRTVRM ;VPOKE
  

  pop  IX
__endasm;
}



/* =============================================================================
 UnsetEarlyClock
 Description: Disables the Early Clock. Restore the position of a sprite plane.
 Input:       [char] sprite plane (0-31)
 Output:      -
============================================================================= */
void UnsetEarlyClock(char plane)
{
plane;
__asm
  push IX
  ld   IX,#0
  add  IX,SP

  ld   A,4(IX) 
  call CALATR
  
  inc  HL
  inc  HL
  inc  HL
  call RDVRM
  and  #127
  call WRTVRM
  
  pop  IX
  ret



;ASM FUNCTIONS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

; >A - sprite plane
; <HL - VRAM addr
getVRAMcolorspr:
  ld   HL,#0x1C00    ;vram address color table base (screen 4)
  ld   D,#0          
  ld   E,A
  SLA  E             ;multiplico A por 16 para identificar la posicion en la VRAM
  RL   D             ;con cuatro rotaciones
  SLA  E
  RL   D
  SLA  E
  RL   D
  SLA  E
  RL   D
  add  HL,DE  
   
  ;ret
__endasm;
}