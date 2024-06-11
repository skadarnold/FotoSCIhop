/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  This class represents a SCI loop from a V56 file
 *
 */
 
#include "StdAfx.h"
#include "sciloop.h"

Loop::~Loop() 
{ 	
	if (_cells != 0)
	{
		for (unsigned short i=0; i<_cells->getLast(); i++)
		{
			Cell **texcell = _cells->getItem(i);
			delete (*texcell);		
		}
		
		delete _cells;
	}


}

bool Loop::LoadLoop(LOOPHEADER *plh)
{
	_cellsCount=plh->NumberOfCells;

	if (_cells)
		delete _cells;

	_cells = new List<Cell*>(_cellsCount);

	_basedOnLoop = plh->BasedOnLoop;
	_mirror = plh->Mirror;
	/*_unkByte = plh->UnkByte;
	_unkLong1=plh->UnkLong1;
	_unkLong2=plh->UnkLong2;
	*/
	_contLoop = plh->contLoop;                                   
    _startCel = plh->startCel;                             
    _endCel = plh->endCel;                               
    _repeatCount = plh->repeatCount;                 
    _StepSize = plh->StepSize;		
    _PaletteOffset = plh->PaletteOffset;	

	return (_cells != 0);
}

LOOPHEADER Loop::RestoreLoopHeader()
{
	LOOPHEADER tlh;

	tlh.BasedOnLoop=_basedOnLoop;
	tlh.CellsOffs=0;
	tlh.Mirror=_mirror;
	tlh.NumberOfCells=_cellsCount;
/*	tlh.UnkByte=_unkByte;
	tlh.UnkLong1=_unkLong1;
	tlh.UnkLong2=_unkLong2;
*/
	tlh.contLoop = _contLoop;                                   
    tlh.startCel = _startCel;                             
    tlh.endCel = _endCel;                               
    tlh.repeatCount = _repeatCount;                 
    tlh.StepSize = _StepSize;		
    tlh.PaletteOffset = _PaletteOffset;	


	return tlh;

}
