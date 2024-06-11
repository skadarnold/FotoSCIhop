/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *  Copyright (C) Daniel Arnold 'Dhel', 2022-2024.
 *
 *  This class represents a SCI palette
 *
 */
 
#include "stdafx.h"

#include "palette.h"

PalEntry *Palette::GetPalEntry(unsigned short which)
{
	if (which < 256)
		return &palData[which];

	return 0;
}
bool Palette::SetPalEntry(PalEntry value, unsigned short which)
{
	if (which < 256)
	{
		palData[which] = value;

		if (which < Head.startOffset)
		{
			Head.nColors += (Head.startOffset-which);
			Head.startOffset = which;
		} else if (which > Head.startOffset+Head.nColors)
			Head.nColors = which-Head.startOffset;

		return true;
	}

	return false;
}


bool Palette::loadPalette(FILE *cfilebuf, unsigned long palsize)
{
    // Check if the file buffer is valid
    if (cfilebuf)
    {
        // Read the first 2 bytes of the file buffer
        unsigned short tcheck=0;
        fread(&tcheck, 2, 1, cfilebuf);     
        
        // Check the value of tcheck, if it is not PALPATCH80 or PALPATCH
        // then set the file pointer back by 2 bytes and read the header
        if ((tcheck != PALPATCH80) && (tcheck != PALPATCH))
        {
            fseek(cfilebuf, -2, SEEK_CUR);
            //fread(&head, PalHeaderSIZE,1,cfilebuf);

			fread(&Head, COMPPALSIZE,1,cfilebuf);
            
            // Check if the data length plus 15 is equal to the size of the palette
            // If not, return false
			// Dhel - not sure what this is used for, but using it now breaks p56 importing of different size images.
            // if ((Head.reserved + 15) != palsize)    
            //    return false;             
        }
        else
            fread(&Head, COMPPALSIZE,1,cfilebuf);
        
        // Allocate memory for the data based on the tripleColor value in the header
        void *data = 0;
        if (Head.type)
        {
            data = new PalEntryOld[Head.nColors];
            fread(data, PalEntryOldSIZE,Head.nColors,cfilebuf);
        }
        else
        {
            data = new PalEntry[Head.nColors];
            fread(data, PalEntrySIZE,Head.nColors,cfilebuf);
        }

		// Copy the data to the palData array based on the value of (bool)(Head.type == 0)
		if (!Head.type)
			for (int i = 0; i < Head.nColors; i++)
				palData[i + Head.startOffset] = ((PalEntry *)data)[i];
		else
		{
			PalEntryOld tpalold;
			for (int i = 0; i < Head.nColors; i++)
			{
				tpalold = ((PalEntryOld *)data)[i];
				palData[i + Head.startOffset].red = tpalold.red;
				palData[i + Head.startOffset].green = tpalold.green;
				palData[i + Head.startOffset].blue = tpalold.blue;
				palData[i + Head.startOffset].remap = 0;
			}
		}

		// set the _hasPalette variable to true indicating that a palette has been loaded
		//_hasPalette = true;
		// Return true indicating that the function has executed successfully
		return true;
	}
	// Return false if the file buffer is invalid
	return false;
}

void Palette::WritePalette(FILE *cfb, bool writesciheader)
{
	if (cfb && palData)
	{
				
		unsigned long tsize = COMPPALSIZE + (Head.nColors * (!Head.type ?4 :3));

		unsigned short ttag = PALPATCH80;
		if (writesciheader)
			fwrite(&ttag, 2,1,cfb);
		else
		{
			ttag = PALETTE_POS;
			fwrite(&ttag, 2,1,cfb);
			fwrite(&tsize, 4,1,cfb);
		}

		fwrite(&Head, COMPPALSIZE, 1, cfb);
		for (int i=0;i<Head.nColors;i++)
			if (!Head.type)
				fwrite(&(palData[i+Head.startOffset]), PalEntrySIZE, 1, cfb);
			else
				fwrite(((char*)&(palData[i+Head.startOffset]))+1, PalEntryOldSIZE, 1, cfb);
	
	}

}
