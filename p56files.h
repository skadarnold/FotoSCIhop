/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  This class represents a P56 file 
 *
 */
 
#ifndef P56FILES_H
#define P56FILES_H

#include "list.h"
#include "scicell.h"
#include "palette.h"
#include "language.h"


#pragma pack(1)


//v1.3 - unknown fields were compared to recently surfaced SCI sources
struct P56HEADOLD {
	unsigned short	RestofHeaderSize; //+2 must be added!!!
 //   short	UnkShort;			// 0x0e10=3600		SCI source:  byte 1 = nPriorities ;  byte 2 = priLineCount
    char nPriorities;
    char priLineCount;
    char    NumCells;	
    char	UnkByte;			//SCI source: dummy
    unsigned short    Width; //0x00A0				//constant 160         SCI source: vanishX  ??
    short	 ZDepth;	//0xd8f0		//constant -10000                  SCI source: vanishY  ??
    unsigned short	Height;	//0x0046				//constant 70          SCI source: viewAngle  ??
    unsigned long    VectorDataLenght;	
    unsigned long	 VectorDataOffset;		//Offset to the EoF character 0xFF
  	unsigned long	priCelOffset; //UnkLong1;		//00000000                    SCI source: priCelOffset
   	unsigned long	controlCelOffset; //UnkLong2;		//00000000                SCI source: controlCelOffset
    unsigned long	PaletteOffset;	//another size but smaller this time
    unsigned long   CellsOffset;		//start of cell rec(44 or 48)         SCI source: visualHeaderOffset
    unsigned long	polygonOffset; //UnkLong3;	//00000000                        SCI source: polygonOffset
	unsigned short PriBars[14]; //always 14 bars


};

#define P56HEADOLDSIZE (sizeof(P56HEADOLD))


//v1.3 - "isCompressed" field seems to be different in recently surfaced SCI sources
//       Moreover, the SCI source checks for the "compression" byte in the Cell Header to determine if an image is compressed,
//        while splitFlag field is never read
struct P56HEAD32 {
	unsigned short CellsOffset;      //Offset of Cells table
	char  NumCells;                  //Num of cells
	bool  IsCompressed;		//DRIGO: is compression used                      //SCI source: uchar splitFlag
	short CellRecSize;      //Size of Cell's table record (0x2A)
	unsigned long  PaletteOffset;    //Offset of Palette struc
	short Width;            //if Height==0 : 0-320x200, 1-640x480, 2-640x400
	short Height;           // <- Screen res sizes
};

#define P56HEAD32SIZE (sizeof(P56HEAD32))

union P56HEAD {
	P56HEADOLD oldhead;
	P56HEAD32 newhead;
};

#pragma pack()

class P56file32
{
	bool _isOldFormat;

	List<Cell*> *_cells;
	unsigned char _cellsCount;
	unsigned char _selectedCell;

	bool _isCompressed;

	unsigned short _cellRecSize;

	Palette *_palSCI;

	unsigned short _maxWidth;
	unsigned short _maxHeight;

    //short	_unkShort;			// 0x0e10=3600		//might be the file version as in MSG files
    char _nPriorities;
    char _priLineCount;
    
    char	_unkByte;			//sempre 0

	short	 _zDepth;	//0xd8f0		//constant -10000

	unsigned long    _vectorSize;	
    unsigned char	 *_vector;		//Offset to the EoF character 0xFF


  	unsigned long	_priCelOffset;		//00000000
   	unsigned long	_controlCelOffset;		//00000000

  	unsigned long	_polygonOffset;		//00000000

	unsigned short _priBars[14]; //sono sempre 14!!!

		//these two exist only when cellcount > 0
   	short	_unkShort1;			//usually FFFF
    short	_unkShort2;   		//usually FFFF

	//unsigned long totalDataSize; //image+tags

	HWND _myHwnd;

    const bool _hasLinks;   //added in v1.3 - N/A to pics, but added here anyway, for easier compatibility with View cells

public:
	
	P56file32(void) : _cellsCount(0), _cells(0), _selectedCell(0), _palSCI(0), _isOldFormat(false), _vector(0), _hasLinks(false) {}
	P56file32(int ncells) : _cellsCount(ncells), _selectedCell(0), _palSCI(0), _isOldFormat(false), _vector(0), _hasLinks(false) 
			{ _cells = new List<Cell*>(ncells); }
	~P56file32(void);

	List<Cell*> *Cells() const { return _cells; }
	void Cells(List<Cell*> *tl) { _cells = tl; }

	unsigned char CellsCount() const { return _cellsCount; }
	void CellsCount(unsigned char value) { _cellsCount = value; }

	unsigned char SelectedCell() const { return _selectedCell; }
	void SelectedCell(unsigned char value) { _selectedCell = value; }

	bool IsCompressed() const { return _isCompressed; }
	void IsCompressed(bool isit) { _isCompressed = isit; }

	bool IsOldFormat() const { return _isOldFormat; }
	void IsOldFormat(bool isit) { _isOldFormat = isit; }

	unsigned short CellRecSize() const { return _cellRecSize; }
	void CellRecSize(unsigned short value) { _cellRecSize = value; }

	Palette *PalSCI() const { return _palSCI; }
	void PalSCI(Palette *tp) { _palSCI = tp; }

	unsigned short MaxWidth() const { return _maxWidth; }
	void MaxWidth(unsigned short value) { _maxWidth = value; }
	unsigned short MaxHeight() const { return _maxHeight; }
	void MaxHeight(unsigned short value) { _maxHeight = value; }
	unsigned short GetPriBar(char value) const { return _priBars[value]; }

	unsigned long VectorSize() const { return _vectorSize; }

    char nPriorities() const { return _nPriorities; }
    char PriLineCount() const { return _priLineCount; }

	bool AddCell(Cell *newcell);
	int LoadFile(HWND hwnd, LPSTR pszFileName);
	bool SaveFile(HWND hwnd, LPSTR szFileName);

	HWND MyHWnd() { return _myHwnd; }
	void MyHWnd(HWND mhw) { _myHwnd = mhw; }
};




#endif
