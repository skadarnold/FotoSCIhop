/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  This class represents a SCI palette
 *
 */
 
#ifndef PALETTE_H
#define PALETTE_H

#pragma pack(1)

struct PalEntryOld
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
#define PalEntryOldSIZE (sizeof(PalEntryOld))

struct PalEntry
{
	unsigned char remap;
	unsigned char red;
	unsigned char green;
	unsigned char blue;
};
#define PalEntrySIZE (sizeof(PalEntry))

struct PalHeader
{
	short palID; //0x000E or 0x900E are constant values?
    char unkBytes1[11];    //the first 8 bytes seems to contain palette name sometimes
    short dataLength;  //Size of remaining data (from unkbytes2 to end of palet)
    char unkBytes2[10];
    short firstColor;  //Starting entry
    short unkShort;
    short numColors;   //Number of entries in palette
    char  exfourColor;
    char  tripleColor; //Triad entries instead quad
    long  unkLong;

};
#define PalHeaderSIZE (sizeof(PalHeader))

#pragma pack()



class Palette
{
	short _palID;
	short _firstColor;
	short _numColors;
	
	bool _hasFourEntries;
	char _exfourColor;

	PalEntry _palData[256];

	char _unkBytes1[11];
	char _unkBytes2[10];
	short _unkShort;
	long  _unkLong;
 
    bool _hasPalette;

public:
	Palette(void) : _firstColor(0), _numColors(0), _hasPalette(false) 
	{ for (int i = 0; i<256; i++)
	  {
          if (i>224)
          {
		      _palData[i].blue = i;//255;
		      _palData[i].green = i;//255;
		  
          } else {
              _palData[i].blue = 224;
		      _palData[i].green = 224;
          }
          
          _palData[i].red = 0;	//red=255  green=0  => violet
		  _palData[i].remap = 0;
	  }
    /*  _palData[255].blue = 0;// 255;
	  _palData[255].green = 255;
	  _palData[255].red =255;//red=255  green=0  => violet
	  _palData[255].remap = 0;    */

	}
	//~Palette(void);

	unsigned short FirstColor() const { return _firstColor; }
	void FirstColor(unsigned short value) { _firstColor = value; }
	unsigned short NumColors() const { return _numColors; }
	void NumColors(unsigned short value) { _numColors = value; }

	bool HasFourEntries() const { return _hasFourEntries; }
	void HasFourEntries(bool value) { _hasFourEntries = value; }
	
	PalEntry *GetPalEntry(unsigned short which);
	bool SetPalEntry(PalEntry value, unsigned short which);

	bool loadPalette(FILE *cfilebuf, unsigned long palsize);
    void noPalette() { 
                       for (int i = 0; i<256; i++)
	                   {
		                    _palData[i].blue = 255-i;
		                    _palData[i].green = 255-i;
		                    _palData[i].red = 255-i;	
		                    _palData[i].remap = 0;
	                   }
                       _hasPalette = false;
                     }
    bool HasPalette() const { return _hasPalette; }
	

	void WritePalette(FILE *cfb, bool writesciheader);

};

#endif
