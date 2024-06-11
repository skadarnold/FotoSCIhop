/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  This class represents a single Cell from a SCI P56/V56 file
 *
 */

#ifndef SCICELL_H
#define SCICELL_H

#include "stdafx.h"
#include "palette.h"



#pragma pack(1)

struct CellHeader
{
	short width;
	short height;
	short xShift;
	short yShift;
	char  transparentClr;   // Transparent color idx (Skip)
	char  compression;      // 0 - none, 8A - rle
	short flags;            // &0x80 -> &1 - UseSkip, &2 - remap_status
							// Note: if hibit is clear, UseSkip must be rechecked for uncompr., set 4 compr
	unsigned long imageandPackSize;      //Size of compressed image + size of pack image
				//if uncompressed, size of image block only
	unsigned long imageSize;       	//Size of compressed image
				//if uncompressed, 0x06 (for some displacement matter, I believe)

	unsigned long  paletteOffs;    //0x00000000		nu in later SCI
							//IMPORTANT WHEN EDITING OR LOADING CHECK IF != 0
						    //TODO check: in later SCI32, the palette is missing and the number here is strange
						    //            GK2: x01 FF FF FF  and lighthouse: x01 00 00 00 .... what does it mean? check SCI source
	unsigned long  imageOffs;        //Offset of Cell's image or pack data tags (if compressed)
	unsigned long  packDataOffs;    //Offset of Pack data image 
	unsigned long  linesOffs;     //Offset of Scan Lines Table (if compressed)
	short zDepth; //-> -1000 - normal bg
	short xPos;
	short yPos;

};
#define CellHeaderSIZE (sizeof(CellHeader))
#define CellHeaderSIZE_MIN (CellHeaderSIZE-6)

struct ViewCellHeader
{
	short width;
	short height;
	short xShift;
	short yShift;
	char  transparentClr;   // Transparent color idx (Skip)
	char  compression;      // 0 - none, 8A - rle
	short flags;            // &0x80 -> &1 - UseSkip, &2 - remap_status
							// Note: if hibit is clear, UseSkip must be rechecked for uncompr., set 4 compr
	unsigned long imageandPackSize;      //Size of compressed image + size of pack image
				//if uncompressed, size of image block only
	unsigned long imageSize;       	//Size of compressed image
				//if uncompressed, 0x06 (for some displacement matter, I believe)

	unsigned long  paletteOffs;    //0x00000000		nu in later SCI32
							//IMPORTANT WHEN EDITING OR LOADING CHECK IF != 0
	unsigned long  imageOffs;        //Offset of Cell's image or pack data tags (if compressed)
	unsigned long  packDataOffs;    //Offset of Pack data image 
	unsigned long  linesOffs;     //Offset of Scan Lines Table (if compressed)
//Link stuff...only for most recent file version
    unsigned long linkTableOffs;  //SCI source : Int32 linkTableOffset   
    short linkTableCount;         //SCI source : Int16 linkTableCount 
    unsigned char unknown[10];      //padding?   

};
#define ViewCellHeaderSIZE_MAX (sizeof(ViewCellHeader))
#define ViewCellHeaderSIZE (_hasLinks ? ViewCellHeaderSIZE_MAX : ViewCellHeaderSIZE_MAX-16)

union CELLS {
	CellHeader newcell;
	ViewCellHeader oldcell;
};


//based from SCI source
struct LinkPoint {
 short x;   
 short y;
 unsigned char positionType;
 char priority;
};


#pragma pack()

class Cell		//size 2A
{
	unsigned short _width;
	unsigned short _height;
	short _left;
	short _top;

	unsigned char _skipColor;
	unsigned char _compression; 
	unsigned short _flags;
	
	unsigned char *_image;
	unsigned long _imageSize;
	unsigned char *_pack;
	unsigned long _packSize;
	unsigned char *_lines;

	BITMAPINFO *_cachedHeader;
	unsigned char *_cached;

	bool _changed;
	//if set to true, the new image is the one referenced by _cached
	//that was the initial Idea, but now it is suddenly converted

	short _zDepth;
	unsigned short _xPos;
	unsigned short _yPos;
 
    Palette *_palette;
    
    bool _hasLinks;         //added in v1.3
    LinkPoint _links[10];
	short _linksCount;
	
public:
	Cell(void) : _image(0), _pack(0), _lines(0), _cached(0), _cachedHeader(0),
                 _changed(false), _palette(0), _hasLinks(false), _linksCount(0) {}
    ~Cell(void) { if (_image) delete _image; if (_pack) delete _pack;
					if (_lines) delete _lines; 
					if (_cached && (_image != _cached)) delete _cached;
					if (_cachedHeader) delete _cachedHeader;}

	unsigned short Width() const { return _width; }
	void Width(unsigned short value) { _width = value; }
	unsigned short Height() const { return _height; }
	void Height(unsigned short value) { _height = value; }
	short Left() const { return _left; }
	void Left(short value) { _left = value; }
	short Top() const { return _top; }
	void Top(short value) { _top = value; }
	
	unsigned char SkipColor() const { return _skipColor; }
	void SkipColor(unsigned char value) { _skipColor = value; }
	
	unsigned char Compression() const { return _compression; }
	void Compression(unsigned char value) { _compression = value; }
	
	unsigned short Flags() const { return _flags; }
	void Flags(unsigned short value) { _flags = value; }

	void GetImage(BITMAPINFO **imhd, unsigned char **im) {  if (_cached==0) makeBitmap();
															*imhd=_cachedHeader;
															*im=_cached; }
                                                            
	void SetImage(BITMAPINFO *imhd, unsigned char *im) { if (_cached && (_image != _cached))
														 	delete _cached;
														 if (_cachedHeader)
															delete _cachedHeader;
														_cached = im; 
														_cachedHeader = imhd;
														_changed = true;
														makeSCI(); }

	long makeBitmap();	
	void makeSCI();


	short ZDepth() const { return _zDepth; }
	void ZDepth(short value) { _zDepth = value; }

	unsigned short XPos() const { return _xPos; }
	void XPos(unsigned short value) { _xPos = value; }
	unsigned short YPos() const { return _yPos; }
	void YPos(unsigned short value) { _yPos = value; }

	void LoadCell(CellHeader *chead, unsigned char *im, unsigned char *pk, unsigned char *lin, bool isView, bool hasLinks);

	Palette **MyPalette() { return &_palette; }
	void MyPalette(Palette **value) {
									_palette = *value;
									if (_cached && (_image != _cached))
										delete _cached;
									if (_cachedHeader)
										delete _cachedHeader;

										_cachedHeader = 0;
										_cached=0;
									}

	unsigned long ImageSize() const { return _imageSize; }
	void ImageSize(unsigned long value) { _imageSize = value; }

	unsigned long PackSize() const { return _packSize; }
	void PackSize(unsigned long value) { _packSize = value; }

	bool HasLines() const { return (_lines!=0); }

	bool Changed() const { return _changed; }

	ViewCellHeader RestoreViewCellHeader();
	CellHeader RestoreCellHeader();

	void WriteImage(FILE *cfb);
	void WritePack(FILE *cfb);

	void WriteScanLines(FILE *cfb);

    void ReadLinks(FILE *cfb);
    void WriteLinks(FILE *cfb) const;

    //void HasLinks(bool value) { _hasLinks = value; }

    bool getLinkPoint(unsigned char n, LinkPoint &lp) const; 

    short LinksCount() const { return _linksCount; }
    void LinksCount(short value) { _linksCount = value; }

};

#endif
