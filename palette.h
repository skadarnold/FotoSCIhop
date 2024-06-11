/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *  Copyright (C) Daniel Arnold 'Dhel', 2022-2024.
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

struct BMPColorHead
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	unsigned char alpha;
	unsigned char color_space_type;
	unsigned char unused;
};
#define BMPColorHeadSize (sizeof(BMPColorHead))

struct PalHeader
{
	short palID;
	char hdSize;
	char palName[9];
	char palCount;
	short reserved;
};

const int PALHEADERSIZE = sizeof(PalHeader);

struct CompPal : public PalHeader
{
	char title[10]; //  8 chars, 0 terminated
	uchar startOffset;
	uchar nCycles;	//  number of cycling ranges following header
	UInt16 fe;		//  future expansion (0)
	UInt16 nColors; //  number of "colors" defined in this palette
	uchar def;		//  "Default" flag setting (1)
	uchar type;		//  (0 = each RGB has flag)
					//  (1 = All RGBs share default flag)
	UInt32 valid;
};

const int COMPPALSIZE = sizeof(CompPal);

#define PALPATCH80    0x008B
#define PALPATCH      0x000B


#define PALETTE_POS 0x0300

#pragma pack()

class Palette
{
	
public:
	Palette(void)
	{ for (int i = 0; i<256; i++)
	  {
          if (i>224)
          {
		      palData[i].blue = i;//255;
		      palData[i].green = i;//255;
		  
          } else {
              palData[i].blue = 224;
		      palData[i].green = 224;
          }
          
          palData[i].red = 0;	//red=255  green=0  => violet
		  palData[i].remap = 0;
	  }
    /*  palData[255].blue = 0;// 255;
	  palData[255].green = 255;
	  palData[255].red =255;//red=255  green=0  => violet
	  palData[255].remap = 0;    */

	}
	//~Palette(void);

	PalEntry palData[256];

    //bool _hasPalette;

	CompPal Head;
	
	PalEntry *GetPalEntry(unsigned short which);
	bool SetPalEntry(PalEntry value, unsigned short which);

	bool loadPalette(FILE *cfilebuf, unsigned long palsize);
    void noPalette() { 
                       for (int i = 0; i<256; i++)
	                   {
		                    palData[i].blue = 255-i;
		                    palData[i].green = 255-i;
		                    palData[i].red = 255-i;	
		                    palData[i].remap = 0;
	                   }
                       //_hasPalette = false;
                     }

	void WritePalette(FILE *cfb, bool writesciheader);

};

#endif
