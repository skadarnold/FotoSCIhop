/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  This class represents a V56 file
 *
 */

#ifndef V56FILES_H
#define V56FILES_H

#include "list.h"
//#include "scicell.h"
#include "sciloop.h"
#include "palette.h"
#include "language.h"


#pragma pack(1)


//v1.3 - defined unknown fields as in recently surfaced SCI sources (CELOBJ.HPP CELOBJ.CPP)
//      splitView == Compressed ? Perhaps it means that the view is split in ImageData and PackData?
struct V56HEAD {
	unsigned short LoopTblOff;   //-2 (size of rest of View header)
    unsigned char  LoopCount;
    unsigned char  stripView;	//was Unk		//always 0?                 //SCI source: uchar stripView
    unsigned char  Compressed;					//always 1?                 //SCI source: uchar splitView
    char  ViewSize;     //0-320x200, 1-640x480, 2-640x400                   //SCI source: resolution
    unsigned short	CellsCount;	//total number of cell records
    unsigned long  PalOffset;
    unsigned char  LoopRecSize;
    unsigned char  CellRecSize;
    unsigned short ResolutionX;  //if ResX==0 && ResY==0 - look at ViewSize  
    unsigned short ResolutionY;  //
    unsigned char LinkVersion;  ///absent in early SCI32 Must be at least 0x84 to be valid??
    unsigned char reserved;  ///absent in early SCI32
};

#define V56HEADSIZE_MAX (sizeof(V56HEAD))
#define V56HEADSIZE (_hasLinks ? V56HEADSIZE_MAX : V56HEADSIZE_MAX -2)

#pragma pack()

class V56file
{
	List<Loop*> *_loops;
	unsigned char _loopsCount;
	unsigned char _selectedLoop;

	char  _stripView;		//always 0?

	bool _isCompressed;
	char  _viewSize; 

    unsigned short	_cellsCount;

	Palette *_palSCI;

	unsigned char _cellRecSize;
	unsigned char  _loopRecSize;
	

	unsigned short _maxWidth;
	unsigned short _maxHeight;

	//unsigned long totalDataSize; //image+tags
    bool _hasLinks;
    
    unsigned char _linkVersion;
    unsigned char _reserved;

	HWND _myHwnd;

public:
	
	V56file(void) : _loopsCount(0), _loops(0), _selectedLoop(0), _palSCI(0), _hasLinks(false) {}
	V56file(int nloops) : _loopsCount(nloops), _selectedLoop(0),_palSCI(0), _hasLinks(false) 
			{ _loops = new List<Loop*>(nloops); }
	~V56file(void);

	List<Loop*> *Loops() const { return _loops; }
	void Loops(List<Loop*> *tl) { _loops = tl; }

	unsigned char LoopsCount() const { return _loopsCount; }
	void LoopsCount(unsigned char value) { _loopsCount = value; }

	unsigned short TotalCellsCount() const { return _cellsCount; }
	void TotalCellsCount(unsigned short value) { _cellsCount = value; }

	unsigned char SelectedLoop() const { return _selectedLoop; }
	void SelectedLoop(unsigned char value) { _selectedLoop = value; }

    char StripView() const { return _stripView; }

	bool IsCompressed() const { return _isCompressed; }
	void IsCompressed(bool isit) { _isCompressed = isit; }

	unsigned char CellRecSize() const { return _cellRecSize; }
	void CellRecSize(unsigned char value) { _cellRecSize = value; }

	unsigned char LoopRecSize() const { return _loopRecSize; }
	void LoopRecSize(unsigned char value) { _loopRecSize = value; }

	Palette *PalSCI() const { return _palSCI; }
	void PalSCI(Palette *tp) { _palSCI = tp; }

	unsigned short MaxWidth() const { return _maxWidth; }
	void MaxWidth(unsigned short value) { _maxWidth = value; }
	unsigned short MaxHeight() const { return _maxHeight; }
	void MaxHeight(unsigned short value) { _maxHeight = value; }

	char ViewSize() const { return _viewSize; }
	void ViewSize(char value) { _viewSize = value; }
 
    bool HasLinks() const { return _hasLinks; }

	bool AddLoop(Loop *newloop);
	int LoadFile(HWND hwnd, LPSTR pszFileName);
	bool SaveFile(HWND hwnd, LPSTR szFileName);

	HWND MyHWnd() { return _myHwnd; }
	void MyHWnd(HWND mhw) { _myHwnd = mhw; }
};




#endif
