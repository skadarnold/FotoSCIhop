/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  This class represents a SCI palette
 *
 */
 
#include "stdafx.h"

#include "palette.h"

#define PALPATCH80    0x008B
#define PALPATCH      0x000B

PalEntry *Palette::GetPalEntry(unsigned short which)
{
	if (which < 256)
		return &_palData[which];

	return 0;
}
bool Palette::SetPalEntry(PalEntry value, unsigned short which)
{
	if (which < 256)
	{
		_palData[which] = value;

		if (which < _firstColor)
		{
			_numColors += (_firstColor-which);
			_firstColor = which;
		} else if (which > _firstColor+_numColors)
			_numColors = which-_firstColor;

		return true;
	}

	return false;
}


bool Palette::loadPalette(FILE *cfilebuf, unsigned long palsize)
{
	if (cfilebuf)
	{
		unsigned short tcheck=0;
		fread(&tcheck, 2, 1, cfilebuf);

        PalHeader head;
                
		if ((tcheck != PALPATCH80) && (tcheck != PALPATCH))
        {
            fseek(cfilebuf, -2, SEEK_CUR);
            fread(&head, PalHeaderSIZE,1,cfilebuf);
                      
            if ((head.dataLength + 15) != palsize)    
                return false;             
        }
        else
            fread(&head, PalHeaderSIZE,1,cfilebuf);
        
			
		void *data = 0;

		if (head.tripleColor)
		{
			data = new PalEntryOld[head.numColors];
			fread(data, PalEntryOldSIZE,head.numColors,cfilebuf);
		}
		else
		{
			data = new PalEntry[head.numColors];
			fread(data, PalEntrySIZE,head.numColors,cfilebuf);
		}

		_palID=head.palID;
		_firstColor = head.firstColor;
		_numColors = head.numColors;

		_hasFourEntries = (bool) (head.tripleColor==0);
		_exfourColor = head.exfourColor;
	
		for (int i=0; i<11; i++)
			_unkBytes1[i] = head.unkBytes1[i];
		for (int i=0; i<10; i++)
			_unkBytes2[i] = head.unkBytes2[i]; 

		_unkShort = head.unkShort;
		_unkLong = head.unkLong;

		if (_hasFourEntries)
			for (int i=0; i<_numColors; i++)
				_palData[i+_firstColor] = ((PalEntry *)data)[i];
		else
		{
			PalEntryOld tpalold;
			for (int i=0; i<_numColors; i++)
			{	
				tpalold = ((PalEntryOld *)data)[i];
				_palData[i+_firstColor].red=tpalold.red;
				_palData[i+_firstColor].green=tpalold.green;
				_palData[i+_firstColor].blue=tpalold.blue;
				_palData[i+_firstColor].remap=0;
			}
		}
                                    
        _hasPalette = true;
	
		return true;
	}
	return false;
}

void Palette::WritePalette(FILE *cfb, bool writesciheader)
{
	if (cfb && _hasPalette)
	{
				
		unsigned long tsize = PalHeaderSIZE + (_numColors * (_hasFourEntries ?4 :3));

		unsigned short ttag = PALPATCH80;
		if (writesciheader)
			fwrite(&ttag, 2,1,cfb);
		else
		{
			ttag = 0x0300;
			fwrite(&ttag, 2,1,cfb);
			fwrite(&tsize, 4,1,cfb);
		}

		PalHeader tph;

		tph.palID=_palID; 

		for (int i=0; i<11; i++)
			tph.unkBytes1[i] = _unkBytes1[i];

		tph.dataLength=(unsigned short)tsize-15;

		for (int i=0; i<10; i++)
			tph.unkBytes2[i] = _unkBytes2[i]; 

		tph.firstColor=_firstColor;
		tph.unkShort=_unkShort;
		tph.numColors=_numColors;
		tph.exfourColor=_exfourColor;
		tph.tripleColor=!_hasFourEntries;
		tph.unkLong=_unkLong;


		fwrite(&tph, PalHeaderSIZE, 1, cfb);
		for (int i=0;i<_numColors;i++)
			if (_hasFourEntries)
				fwrite(&(_palData[i+_firstColor]), PalEntrySIZE, 1, cfb);
			else
				fwrite(((char*)&(_palData[i+_firstColor]))+1, PalEntryOldSIZE, 1, cfb);
	
	}

}
