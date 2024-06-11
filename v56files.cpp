/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  This class represents a V56 file
 *
 */

#include "stdafx.h"

//#include "Immagina.h"
#include "v56files.h"

/* 0x808000 or 0x808400 identifies a V56 file.
*  +00 Pascal String (& NULL terminated)
*  +xx short 320
*  +x2 short 200
*  +x4 short 5
*  +x6 short 6
*  +x8 short 256
* +xa short[6] dunno (TODO check what these are for)
*/

#define V56PATCH      0x008080 
#define V56PATCH84    0x008480


V56file::~V56file(void)
{
	if (_palSCI != 0)
		delete _palSCI;

	if (_loops != 0)
	{
		for (unsigned short i=0; i<_loops->getLast(); i++)
		{
			Loop **texloop = _loops->getItem(i);
			delete (*texloop);		
		}
		
		delete _loops;
	}
}

bool V56file::AddLoop(Loop *newloop)
{
	return _loops->addItem(&newloop);
}


int V56file::LoadFile(HWND hwnd, LPSTR pszFileName)
{
	_myHwnd = hwnd;
    FILE *cfilebuf = fopen(pszFileName, "rb");
    if (cfilebuf)
    {
		//dispose old file structs from memory:
        if (_loops)
           delete _loops;
        _loops = 0;

		if (_palSCI)
           delete _palSCI;
        _palSCI = 0;
			
		//first check for the Patches header:
        unsigned char offset = 0;
		unsigned long patchID =0;
        

		fread((void *) &patchID, 3, 1, cfilebuf);
        if (patchID == V56PATCH84 || patchID == V56PATCH)
		{
			fread((void *) &offset, 1, 1, cfilebuf);
			offset += 26;
		}
		else if (((patchID&0xFFFF) == 16) || ((patchID&0xFFFF) == 18))  //typical offset used
			offset = 0;
		else
			return ID_WRONGHEADER;
		

		fseek(cfilebuf, offset+12, SEEK_SET);
		unsigned char tlooprecsize=0;
		fread(&tlooprecsize, 1, 1, cfilebuf);
		if (tlooprecsize != 0x10)
			return ID_WRONGLOOPRECSIZE;

		fseek(cfilebuf, offset+13, SEEK_SET);
		unsigned char tcellrecsize=0;
		fread(&tcellrecsize, 1, 1, cfilebuf);
		switch (tcellrecsize)
		{
		case 0x24:
			
			break;
		case 0x34:
			_hasLinks = true;
            
            break;
		default:
			return ID_WRONGCELLRECSIZE;
		}

		fseek(cfilebuf, offset, SEEK_SET);

		V56HEAD pheader;

        fread(&pheader, V56HEADSIZE, 1, cfilebuf);
				
		_loopsCount = pheader.LoopCount;
		_loops = new List<Loop*>(_loopsCount);

		_isCompressed = pheader.Compressed;
		_cellRecSize = pheader.CellRecSize;
		_loopRecSize = pheader.LoopRecSize;

		_maxWidth = pheader.ResolutionX;
		_maxHeight = pheader.ResolutionY;

		_viewSize = pheader.ViewSize;
		_cellsCount = pheader.CellsCount;

		_stripView =pheader.stripView;

        if (_hasLinks)
        {
            _linkVersion = pheader.LinkVersion;
            _reserved = pheader.reserved;   
        }

		if (pheader.PalOffset!=0)
		{
			fseek(cfilebuf, offset+pheader.PalOffset-6, SEEK_SET);

			int ttag = 0;
			fread(&ttag, 2, 1, cfilebuf);
			if (ttag != 0x0300)
				return ID_WRONGPALETTELOC;

			unsigned long tpalsize=0;
			fread(&tpalsize, 4, 1, cfilebuf);

			_palSCI= new Palette;

			_palSCI->loadPalette(cfilebuf, tpalsize);
		}
		else
		{
			_palSCI= new Palette;
			//MessageBox(hwnd, WARN_MISSINGPALETTE, WARN_ATTENTION, MB_OK | MB_ICONEXCLAMATION);
            //MessageBox replaced with a string (lighter)
            _palSCI->noPalette();
		}


		//palette loading completed, now load loops and cells:

		fseek(cfilebuf, offset+pheader.LoopTblOff+2, SEEK_SET);  //2 additional bytes for the counter

		LOOPHEADER *tloopheader = new LOOPHEADER [pheader.LoopCount];
		fread(tloopheader, LOOPHEADERSIZE, pheader.LoopCount, cfilebuf);

		for (int z=0; z<pheader.LoopCount; z++)
		{
			Loop *tempnewloop = new Loop;
			tempnewloop->LoadLoop(&(tloopheader[z]));
			
			fseek(cfilebuf, offset+tloopheader[z].CellsOffs, SEEK_SET);

			ViewCellHeader *tcellheader = new ViewCellHeader [tloopheader[z].NumberOfCells];
			for (unsigned short k=0; k<tloopheader[z].NumberOfCells; k++)
			{
				fread(&(tcellheader[k]), ViewCellHeaderSIZE, 1, cfilebuf); 
				fseek(cfilebuf, _cellRecSize-ViewCellHeaderSIZE, SEEK_CUR);     //skips remaining data 
			    /* DEBUG ONLY!
                if (_hasLinks)
                    if (tcellheader[k].linkTableCount)
    			    {
                        MessageBox(hwnd, "Link Table defined", WARN_ATTENTION, MB_OK | MB_ICONEXCLAMATION);                        
                    }
                */
            }

			for (int i=0; i<tloopheader[z].NumberOfCells; i++)
			{
					unsigned char *tim=0;
					unsigned char *tpk=0;
					unsigned char *tln=0; 

					unsigned long timsize=0;
					if (tcellheader[i].compression==0)
						//timsize = tcellheader[i].imageandPackSize;
						//NOTE in certain files it is wrong, Sierra's tool writes this only on two bytes,
                        //but if the image is too big, it gets cut.
                        timsize = tcellheader[i].width*tcellheader[i].height;
					else
						timsize = tcellheader[i].imageSize;

					fseek(cfilebuf, offset+tcellheader[i].imageOffs, SEEK_SET);
			
					tim = (unsigned char*)new char[timsize];
					fread(tim, timsize,1,cfilebuf);

					if (tcellheader[i].compression != 0)
					{
						fseek(cfilebuf, offset+tcellheader[i].packDataOffs, SEEK_SET);
						unsigned long tpksize = tcellheader[i].imageandPackSize-tcellheader[i].imageSize;
						tpk= (unsigned char* )new char[tpksize];
						fread(tpk, tpksize,1,cfilebuf);
						
						if (tcellheader[i].linesOffs!=0)
						{
							fseek(cfilebuf, offset+tcellheader[i].linesOffs, SEEK_SET);
							unsigned long tlnsize = tcellheader[i].height*4*2;
							tln= (unsigned char* )new char[tlnsize];
							fread(tln, tlnsize,1,cfilebuf);
						}


					}
			
			
			
					Cell *tempnewcell = new Cell;
					tempnewcell->MyPalette(&_palSCI);
					tempnewcell->LoadCell((CellHeader *)&tcellheader[i],tim,tpk,tln,true,_hasLinks);

           	        //ADDED in v1.3 - Links
			        if (_hasLinks)
                    {
                        tempnewcell->LinksCount(tcellheader[i].linkTableCount);
                        if (tcellheader[i].linkTableCount)
                        {
                            fseek(cfilebuf, offset+tcellheader[i].linkTableOffs, SEEK_SET);
                            tempnewcell->ReadLinks(cfilebuf);

                        }
                    }

					tempnewloop->AddCell(tempnewcell);

			}
			delete [] tcellheader;



			_loops->addItem(&tempnewloop);


		}


		_cellRecSize=ViewCellHeaderSIZE;

		fclose(cfilebuf);

		return ID_NOERROR;		
	}

	return ID_CANTOPENFILE;
}

bool V56file::SaveFile(HWND hwnd, LPSTR szFileName)
{
	FILE *cfilebuf = fopen(szFileName, "wb");
    if (cfilebuf)
    {
		unsigned long patchID =0;
		patchID += V56PATCH;
		fwrite(&patchID,4,1,cfilebuf);

		unsigned short tshort=320;
		fwrite(&tshort,2,1,cfilebuf);
		tshort=200;
		fwrite(&tshort,2,1,cfilebuf);
		tshort=5;
		fwrite(&tshort,2,1,cfilebuf);
		tshort=6;
		fwrite(&tshort,2,1,cfilebuf);
		tshort=256;
		fwrite(&tshort,2,1,cfilebuf);
		tshort=0;
		for (int i=0;i<6;i++)
			fwrite(&tshort,2,1,cfilebuf);


		unsigned long offset = 26;


		V56HEAD pheader;

		unsigned long imageAllSize=0;
		unsigned long tagsTotalSize=0;
		//unsigned short totalCells=0;
		unsigned long linesTotalSize=0;
		for (int i=0; i<_loopsCount; i++)
		{
			Loop **tloop=_loops->getItem(i);
			for (int j=0; j<(*tloop)->CellsCount();j++)
			{
				Cell **tcell=(*tloop)->Cells()->getItem(j);
				imageAllSize += (*tcell)->ImageSize() + (*tcell)->PackSize();
				tagsTotalSize += (*tcell)->ImageSize();
				
				//added in v1.3 for links
				if ((*tcell)->HasLines())
                {	
					linesTotalSize += (*tcell)->Height()*4*2;
                }
			}
			//totalCells += (*tloop)->CellsCount;
		}
  
        unsigned long paletteSize;
        if (_palSCI->HasPalette())
		    paletteSize = PalHeaderSIZE + (_palSCI->NumColors() * (_palSCI->HasFourEntries() ?4 :3));
        else
            paletteSize=0;
        
		pheader.CellRecSize=_cellRecSize;
		pheader.CellsCount=_cellsCount;//totalCells;
		pheader.Compressed=_isCompressed;
		pheader.LoopCount=_loopsCount;
		pheader.LoopRecSize=_loopRecSize;
		pheader.LoopTblOff=V56HEADSIZE-2;
		pheader.ResolutionX=_maxWidth;
		pheader.ResolutionY=_maxHeight;
		pheader.stripView=_stripView;
		pheader.ViewSize=_viewSize;
		if (_hasLinks)
		{
            pheader.LinkVersion = _linkVersion;
            pheader.reserved = _reserved;
        }
        
        unsigned long paletteOffset = 2 +pheader.LoopTblOff +  _loopRecSize * _loopsCount + _cellRecSize * _cellsCount + 6; 

        pheader.PalOffset = (_palSCI->HasPalette()? paletteOffset :0);
		
		fwrite(&pheader, V56HEADSIZE, 1, cfilebuf);

		
		//now write loops:

		LOOPHEADER headloop;
		unsigned long cellpos=V56HEADSIZE + LOOPHEADERSIZE*_loopsCount;
		for (int i=0;i<_loopsCount;i++)
		{
			Loop **tloop=_loops->getItem(i);
			headloop = (*tloop)->RestoreLoopHeader();

			headloop.CellsOffs =cellpos;
			//if (!headloop.Mirror) //NOTE Check removed because a mirrored loop could still have an additional cell (I suppose)
			cellpos += _cellRecSize * headloop.NumberOfCells;

			fwrite(&headloop, LOOPHEADERSIZE,1,cfilebuf);
		}

		//writing cells now:

		bool hasScanLines = false;
		ViewCellHeader headcell;
		memset(&headcell, 0, ViewCellHeaderSIZE);
		unsigned long imagepos = paletteOffset +paletteSize + (_palSCI->HasPalette() ?6 :0); 
		unsigned long packpos = (_isCompressed ?imagepos + tagsTotalSize :0); //TODO check 0!!
		unsigned long linespos=imagepos + imageAllSize +6;
		unsigned long linkspos=linespos + linesTotalSize +6;     //added in v1.3 for links
		for (int j=0; j<_loopsCount; j++)
		{
			Loop **tloop=_loops->getItem(j);
			for (int i=0; i<(*tloop)->CellsCount(); i++)
			{
				Cell **tcell=(*tloop)->Cells()->getItem(i);
				headcell = (*tcell)->RestoreViewCellHeader();
			
				headcell.imageOffs = imagepos;
				headcell.packDataOffs = packpos;

				imagepos += (_isCompressed ?headcell.imageSize :headcell.imageandPackSize);
				packpos += (_isCompressed ?headcell.imageandPackSize -headcell.imageSize :0);
				if (_isCompressed)
				{	
					if (!hasScanLines)
						hasScanLines =(*tcell)->HasLines();
					headcell.linesOffs = (hasScanLines ?linespos :0);
					linespos += headcell.height*4*2;
				}

				headcell.paletteOffs = 0; //TODO CHECK if it's 0//(_isOldFormat ?pheader.oldhead.PaletteOffset :0);
						
		        if (_hasLinks)
			    {
                    headcell.linkTableOffs = linkspos;
                                        
                    linkspos +=  sizeof(LinkPoint)* headcell.linkTableCount;    
                }
                
                fwrite(&headcell, ViewCellHeaderSIZE,1,cfilebuf);
		  
			}
		}

		_palSCI->WritePalette(cfilebuf, false);

		//writing images now:

		if (_cellsCount)
		{
			unsigned short ttag = 0x0400;
			fwrite(&ttag, 2,1,cfilebuf);
			fwrite(&imageAllSize, 4,1,cfilebuf);
			for (int j=0; j<_loopsCount; j++)
			{
				Loop *tloop = *_loops->getItem(j);
				for (int i=0; i<tloop->CellsCount(); i++)
					(*tloop->Cells()->getItem(i))->WriteImage(cfilebuf);
			}
			if (_isCompressed)
				for (int j=0; j<_loopsCount; j++)
				{
					Loop *tloop = *_loops->getItem(j);
					for (int i=0; i<tloop->CellsCount(); i++)
						(*tloop->Cells()->getItem(i))->WritePack(cfilebuf);
				}
		}

		if (_isCompressed && hasScanLines)  //writing scan lines
		{
			unsigned short ttag = 0x0500;
			fwrite(&ttag, 2,1,cfilebuf);
			unsigned long tzero = 0;
			fwrite(&tzero, 4,1,cfilebuf);
			for (int j=0; j<_loopsCount; j++)
			{
				Loop *tloop = *_loops->getItem(j);
				for (int i=0; i<tloop->CellsCount(); i++)
					(*tloop->Cells()->getItem(i))->WriteScanLines(cfilebuf);
			}

		}

        if (_hasLinks)       //added in v1.3- write links
        {
            //first there is an unknown 00 06 00 00 00 00 in all files:
            LinkPoint tlp;
            memset(&tlp, 0, sizeof(tlp));
            tlp.x = 0x0600;
            fwrite(&tlp, sizeof(tlp),1,cfilebuf);
			            
           	for (int j=0; j<_loopsCount; j++)
			{
				Loop *tloop = *_loops->getItem(j);
				for (int i=0; i<tloop->CellsCount(); i++)
					(*tloop->Cells()->getItem(i))->WriteLinks(cfilebuf);
			}
   
        }


		fclose(cfilebuf);

		return true;
	}

	return false;
}
