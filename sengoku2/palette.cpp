#include "stdafx.h"

#define OPTIONS_COLOR 0x00F8F8F8

void setPaletteHooks()
{
	//243 -> 68
	setByte(0x00516927, 68);
	setByte(0x0051C9A8, 68);
	setByte(0x0051EF4F, 68);
	setByte(0x005232BE, 68);
	setByte(0x005233DA, 68);
	setByte(0x005236B1, 68);
	setByte(0x00523791, 68);
	setByte(0x0052383E, 68);
	setByte(0x005239DE, 68);
	setByte(0x00523CEE, 68);
	setByte(0x00523D3E, 68);
	setByte(0x00523DFE, 68);
	setByte(0x00523F5E, 68);
	setByte(0x00524127, 68);
	setByte(0x0052417E, 68);
	setByte(0x00524A0E, 68);
	setByte(0x00524D67, 68);
	setByte(0x00524DBE, 68);
	setByte(0x00524E6C, 68);
	setByte(0x00524ED8, 68);
	setByte(0x00524FCC, 68);
	setByte(0x007E9F9C, 68);

	//options
	setInt(0x0050D45B, OPTIONS_COLOR);
	setInt(0x0050D46D, OPTIONS_COLOR);
	setInt(0x0050D47F, OPTIONS_COLOR);
	setInt(0x0050D491, OPTIONS_COLOR);
	setInt(0x0050D4A3, OPTIONS_COLOR);
	setInt(0x0050D4B5, OPTIONS_COLOR);
	setInt(0x0050D4C7, OPTIONS_COLOR);
	setInt(0x0050D4D9, OPTIONS_COLOR);
	setInt(0x0050D4EB, OPTIONS_COLOR);
	setInt(0x0050D4FD, OPTIONS_COLOR);
	setInt(0x0050D50F, OPTIONS_COLOR);
	setInt(0x0050D529, OPTIONS_COLOR);
	setInt(0x0050D53B, OPTIONS_COLOR);
	setInt(0x0050D553, OPTIONS_COLOR);
	setInt(0x0050D565, OPTIONS_COLOR);
	setInt(0x0050D577, OPTIONS_COLOR);
	setInt(0x0050D589, OPTIONS_COLOR);
}