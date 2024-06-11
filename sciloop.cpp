/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *  Copyright (C) Daniel Arnold 'Dhel', 2022-2024.
 *
 *  This class represents a SCI loop from a V56 file
 *
 */
 
#include "StdAfx.h"
#include "sciloop.h"

Loop::~Loop() 
{ 	
	if (cells)
	{
		for (unsigned short i=0; i < Head.numCels; i++)
		{
			Cell *texcell = cells[i];
			delete (texcell);		
		}
	}
}
