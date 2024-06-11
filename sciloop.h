/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
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

struct LOOPHEADER {
     char  BasedOnLoop;   //Number of loop
     bool  Mirror;        //IsMirror                       SCI source : uchar flags 
     unsigned char  NumberOfCells; //NumCells -> 0 if based on another loop (?)
     //long  UnkLong1;		//always FF ? 
     char contLoop;                                     // SCI source : char contLoop,
     char startCel;                                     //              char startCel,
     char endCel;                                       //              char endCel,
     unsigned char repeatCount;                         //              uchar repeatCOunt
     unsigned char  StepSize;		//always 3              //SCI source : uchar stepSize
     long  PaletteOffset;	//unklong2	//always 0          //SCI source: Int32 paletteOffset
     unsigned long  CellsOffs;                          //SCI source: Int32 
};

#define LOOPHEADERSIZE (sizeof(LOOPHEADER))

#pragma pack()

class Loop
{
	List<Cell*> *_cells;
	unsigned char _cellsCount;
	unsigned char _selectedCell;

	char  _basedOnLoop;   //Number of loop
    bool  _mirror;        //IsMirror

    char _contLoop;                                 
    char _startCel;                                
    char _endCel;                                 
    unsigned char _repeatCount;                       
    unsigned char  _StepSize;	
    long  _PaletteOffset;	

public:
	
	Loop(void) : _cellsCount(0), _cells(0), _selectedCell(0) {}
	~Loop(void);

	List<Cell*> *Cells() const { return _cells; }
	void Cells(List<Cell*> *tl) { _cells = tl; }

	unsigned char CellsCount() const { return _cellsCount; }
	void CellsCount(unsigned char value) { _cellsCount = value; }

	unsigned char SelectedCell() const { return _selectedCell; }
	void SelectedCell(unsigned char value) { _selectedCell = value; }

	bool Mirrored() const { return _mirror; }
	void Mirrored(bool value) { _mirror = value; }

	char BasedOn() const { return _basedOnLoop; }
	void BasedOn(char value) { _basedOnLoop = value; }

    char ContLoop() const { return _contLoop; }                                   
    char StartCel() const { return _startCel; }                              
    char EndCel() const { return _endCel; }                                 
    unsigned char RepeatCount() const { return _repeatCount; }                   
    unsigned char StepSize() const { return _StepSize; }

	bool AddCell(Cell *newcell) { return _cells->addItem(&newcell); }

	LOOPHEADER RestoreLoopHeader();

	bool LoadLoop(LOOPHEADER *plh);
};




#endif
