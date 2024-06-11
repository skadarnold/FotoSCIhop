/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *  Copyright (C) Daniel Arnold 'Dhel', 2022-2024.
 *
 *  This class represents a loop from a V56 file
 *
 */
 
#ifndef SCILOOP_H
#define SCILOOP_H

#include "list.h"
#include "scicell.h"
//#include "palette.h"

#pragma pack(1)

#pragma pack()

class Loop
{

public:
	
	Loop(void){}
	~Loop(void);

    Cell *cells[MAX_CELLS];
    LoopHeader Head;
};

#endif
