/* ============================================================================= 
  VDP SPRITES MSX SDCC Library (fR3eL Project)          
============================================================================= */

#ifndef  __VDP_SPRITES_H__
#define  __VDP_SPRITES_H__



/* =============================================================================
SetSpritePattern
Description: 
		Assign a pattern to a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] pattern
Output:	-
============================================================================= */
void SetSpritePattern(char plane, char pattern);



/* =============================================================================
SetSpriteColor
Description: 
		Assign a color to a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] color (0-15)
Output:	-
============================================================================= */
void SetSpriteColor(char plane, char color);



/* =============================================================================
SetSpritePosition
Description: 
		Assigns the position coordinates of a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] x 
		[char] y
Output:	-
============================================================================= */
void SetSpritePosition(char plane, char x, char y);



/* =============================================================================
SetSpriteVisible
Description: 
		Hides or shows a sprite plane.
Input:	[char] sprite plane (0-31) 
		[char] or [boolean]/[switcher] visible state: 
									0/false/OFF = hidden; 1/true/ON = visible
Output:	-
============================================================================= */
void SetSpriteVisible(char plane, char state);



/* =============================================================================
SetEarlyClock
Description: 
		Apply the Early Clock of a sprite plane. Move 32 points to the 
		left the X position of the sprite.
Input:	[char] sprite plane (0-31) 
Output:	-
============================================================================= */
void SetEarlyClock(char plane);



/* =============================================================================
UnsetEarlyClock
Description:
		Disables the Early Clock. Restore the position of a sprite plane.
Input:	[char] sprite plane (0-31)
Output:	-
============================================================================= */
void UnsetEarlyClock(char plane);



#endif