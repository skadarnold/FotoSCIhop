/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *  Copyright (C) Daniel Arnold 'Dhel', 2022-2024.
 *
 *  This class represents a SCI Cell from a P56/V56 file
 *
 */
 
#include "StdAfx.h"
#include "scicell.h"
#include "p56files.h"
//#include "palette.h"

// Dhel
#include "v56files.h"

void Cell::makeSCI()
{	
	if (bmImage && bmInfo)
	{
		if ( cellImage->image)
			delete cellImage->image;

		cellImage->image = 0;

		if (cellImage->pack)
			delete cellImage->pack;

		cellImage->pack = 0;

		bool hasLines = (cellImage->lines != 0);

		if (hasLines)
			delete cellImage->lines;

		cellImage->lines = 0; 

		unsigned short width = (unsigned short) bmInfo->bmiHeader.biWidth;
		unsigned short height = (unsigned short) -bmInfo->bmiHeader.biHeight;

		CelBase *bCell = new CelBase;
		bCell = (CelBase *)&Head;

		bCell->xDim = width;
		bCell->yDim = height;

		cellImage->imageSize = width*height;
		cellImage->packSize = 0;

	    cellImage->image = (unsigned char *) new char [cellImage->imageSize];


		int dwremainder = width%4;
		if (dwremainder)
			dwremainder = 4-dwremainder; //bmp requires DWORD align for each scanline

		unsigned short bmpwidth = width +dwremainder;

		if (!bCell->compressType)
			for (unsigned short i=0; i<height; i++)
				for (unsigned short j=0; j<width; j++)
					cellImage->image[i*width +j] = bmImage[i*bmpwidth +j];

		else	//compressed
		{
			cellImage->pack = (unsigned char *) new char [cellImage->imageSize];
			if (hasLines)
				cellImage->lines = (unsigned char *) new char [height*4*2];

			unsigned short i=0;
			unsigned short j=0, oldj=0;

			unsigned char *ppack = cellImage->pack;
			unsigned char *pimage = cellImage->image;

			unsigned long *ptaglines;
			unsigned long *pdatalines;
			if (hasLines)
			{
				ptaglines = (unsigned long *) cellImage->lines;
				pdatalines = ((unsigned long *) cellImage->lines) +height;		
			}
			unsigned char *pcached = bmImage;
						
			for (i=0; i<height; i++)
			{
				j = 0;
				pcached = bmImage + (i*bmpwidth);

				if (hasLines)
				{
					ptaglines[i]=(unsigned long)(pimage - cellImage->image);
					pdatalines[i]=(unsigned long)(ppack - cellImage->pack);
				}

				unsigned char b1, b2, b3, cont;

				
			
				do
				{
					if (width-j>2)
					{
						b1 = pcached[0];
						b2 = pcached[1];
						b3 = pcached[2];
						if ((b1==b2) || (b1==255))
						{
							pcached +=1;
							j+=1;
							cont =1;
							while ((j<width) && (cont<0x3F))
							{
								b2=pcached[0];
								if (b2!=b1)
									break;
								else
								{
									cont++;
									pcached++;
									j++;
								}

							}
							if (b1==255)
							{
								pimage[0]=0xC0 + cont;
								pimage++;
							}
							else
							{
								pimage[0]=0x80 + cont;
								pimage++;
								ppack[0]=b1;
								ppack++;
							}
						}
						else	//b1!=b2 || b2!=b3
						{
							cont =1;

							while ((j+cont<width-2) && (cont<0x3F)) //NOTE WAS 0x7F in Gabriel Knight, when scanlines are used, the max value allowed is 3F even here.
							{                                        //TODO fix, perhaps adding a HasLines switch, because it's making the file bigger than the original
								b1=b2;                               //NOTE a better optimization, could be to use the same algorithm of Sierra's original tool
								b2=b3;
								b3=pcached[cont+2];
								
								if ((b1==b2) && ((b2==b3) || (b2 ==255)))
									break;
								else
									cont++;
							}
                            if ((j+cont==width-2) && (cont<0x3E) && (b3!=b2)) //NOTE as in the upper note
                               cont+=2;
							
							pimage[0]=cont;
							pimage++;
							for(int z=0;z<cont;z++)
							{
								ppack[0]=pcached[0];
								ppack++;
								pcached++;
							}
							j+=cont;
						}
				
					}
					else		//width-j <3
					{
						cont =width-j;
						b1=pcached[0];
                        if (cont==2)
                           b2=pcached[1];
                        
                        if ((b1==b2) || (cont ==1))
                        {
                           if (b1==255)
                           {
	                           pimage[0]=0xC0 + cont;
							   pimage++;  
             			   }
						   else
						   {
							   pimage[0]=0x80 + cont;
							   pimage++;
							   ppack[0]=b1;
							   ppack++;
						   }    
						}
						else
                        {	
						    pimage[0]=cont;
						    pimage++;

							ppack[0]=b1;
							ppack[1]=b2;
                            ppack+=cont;
							
						}
      
                        pcached+=cont;   
						j+=cont;
							
					}
				} while (j<width);
			}
	
			cellImage->packSize = (unsigned long) (ppack - cellImage->pack);
			cellImage->imageSize = (unsigned long) (pimage - cellImage->image);
			
		}

		
	}
}

long Cell::makeBitmap()
{
	if (bmImage)
		delete bmImage;

	if (bmInfo)
		delete bmInfo;

	unsigned long width;
	unsigned long height;

	CelBase *bCell = new CelBase;
	bCell = (CelBase *)&Head;

	width = bCell->xDim;
	height = bCell->yDim;

	unsigned long imsize = width*height;
	int dwremainder = width%4;
	if (dwremainder)
		imsize+= height*(4-dwremainder); //bmp requires DWORD align for each scanline
	unsigned char *initdata;

	long tsizep = ((sizeof(BITMAPINFO)) + 256*(sizeof(RGBQUAD)));

	BITMAPINFO *binfo = (BITMAPINFO *) new char[tsizep];
	

	binfo->bmiHeader.biBitCount=8;
	binfo->bmiHeader.biClrImportant=256;
	binfo->bmiHeader.biClrUsed=256;//TODO ok?
	binfo->bmiHeader.biCompression=BI_RGB;
	binfo->bmiHeader.biHeight=-height; //so that it will be a top-down DIB
	binfo->bmiHeader.biPlanes=1;
	binfo->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);//???
	binfo->bmiHeader.biSizeImage=imsize;//was 0;
	binfo->bmiHeader.biWidth=width;
	binfo->bmiHeader.biXPelsPerMeter=0; //nu
	binfo->bmiHeader.biYPelsPerMeter=0; //nu

	RGBQUAD tquad;
	for (int i=0; i<256; i++)
	{
		PalEntry *tpal = palette->GetPalEntry(i);
        
		if (tpal != NULL)
		{
			tquad.rgbBlue=tpal->blue;
			tquad.rgbGreen=tpal->green;
			tquad.rgbRed=tpal->red;
			tquad.rgbReserved=0;
		}
		else
		{
			tquad.rgbBlue=0;
			tquad.rgbGreen=0;
			tquad.rgbRed=0;
			tquad.rgbReserved=0;
		}
		binfo->bmiColors[i]= tquad;

	}


	if (!bCell->compressType)
	{
		if (!dwremainder)
			initdata =  cellImage->image;
		else
		{
			initdata = (unsigned char *) (new char[imsize]);
			
			unsigned char *pdata = cellImage->image;

			unsigned char *pinit = initdata;
			for (int i=0; i<height; i++)
			{
				memcpy(pinit, pdata, width);
				pinit += width;
				pdata += width;
				for (int j=0; j<4-dwremainder;j++)
				{
					pinit[0] = 0;
					pinit++;	
				}
			}

		}
	}
	else
	{
		initdata = (unsigned char *) (new char[imsize]);

		unsigned char *ptags = cellImage->image;
		unsigned char *pdata = cellImage->pack;

		unsigned char *pinit = initdata;

        unsigned long *plines = (unsigned long *)cellImage->lines;
	
		//TODO add position verification using scan lines!!
		int i=0;
		do
		{
            
            if (cellImage->lines)
			{
                //HWND thwnd = ((P56file32*)_parent)->MyHWnd();
				if (plines[i] != (unsigned long)(ptags - cellImage->image))
                    MessageBox(hWnd, "Lines tags are wrong!", "Error",
                                MB_OK | MB_ICONEXCLAMATION);
				if (plines[i+height] != (unsigned long)(pdata - cellImage->pack))
                    MessageBox(hWnd, "Lines colors are wrong!", "Error",
                                MB_OK | MB_ICONEXCLAMATION);
		    }
            
			int curwidth=0;
			do
			{
				switch ((*ptags)>>6)
				{
				case 2:	//80
				{
					unsigned char color = *pdata;
					pdata++;
					for (int j=0; j<((*ptags)-0x80); j++)
					{
						pinit[0] = color; 
						pinit++;
						curwidth++;
					}
					break;
				}
				case 3:	//C0
					for (int j=0; j<((*ptags)-0xC0); j++)
					{
						pinit[0] = 255; 
						pinit++;
						curwidth++;
					}
					break;
				default:
					for (int j=0; j<*ptags; j++)
					{
						pinit[0] = *pdata;
						pdata++;
						pinit++;	
						curwidth++;
					}

				}

				ptags++;
			
			} while (curwidth<width);
			//TODO check the line here!!!

			if (dwremainder) //if it can't be divided by 4
				for (int j=0; j<4-dwremainder;j++)
				{
					pinit[0] = 0;
					pinit++;	
				}

			i++;

		} while (i<height);
		
		//HWND thwnd = ((P56file32*)_parent)->MyHWnd();
		if (imsize!=(long)(pinit-initdata))
			MessageBox(hWnd, "The uncompressed length is different than the expected!", "Error",
            MB_OK | MB_ICONEXCLAMATION);
		imsize = imsize-((long)(pinit-initdata));

	}



//if (tbmap)
	bmImage = initdata;
	bmInfo = binfo;

	return imsize;
}

void Cell::loadImageOffset()
{
	
}


void Cell::loadImage( FILE *cfilebuf, unsigned char offset )
{
	CellImage *sciImage = new CellImage;

	sciImage->lines = 0;
	sciImage->pack = 0;
	sciImage->lines = 0;
	sciImage->imageSize = 0;

	CelBase *bCell = new CelBase;
	bCell = (CelBase *)&Head;

	if (!bCell->compressType)
		// timsize = cells[i]->Head.pic.imageandPackSize;
		// NOTE in certain files it is wrong, Sierra's tool writes this only on two bytes,
		// but if the image is too big, it gets cut.
		sciImage->imageSize = bCell->xDim * bCell->yDim;
	else
	{
		sciImage->imageSize = bCell->controlByteCount;
	}

	fseek(cfilebuf, offset + bCell->controlOffset, SEEK_SET);

	sciImage->image = (unsigned char *)new char[sciImage->imageSize];
	fread(sciImage->image, sciImage->imageSize, 1, cfilebuf);

	if (bCell->compressType)
	{
		fseek(cfilebuf, offset + bCell->colorOffset, SEEK_SET);
		sciImage->packSize = bCell->dataByteCount - bCell->controlByteCount;
		sciImage->pack = (unsigned char *)new char[sciImage->packSize];
		fread(sciImage->pack, sciImage->packSize, 1, cfilebuf);

		if (bCell->rowTableOffset)
		{
		fseek(cfilebuf, offset + bCell->rowTableOffset, SEEK_SET);
		sciImage->lineSize = bCell->yDim * 4 * 2;
		sciImage->lines = (unsigned char *)new char[sciImage->lineSize];
		fread(sciImage->lines, sciImage->lineSize, 1, cfilebuf);
		}
	}

	if (!bCell->compressType)
	{

		//_imageSize = chead->imageandPackSize;
		// unreliable!!! it's better to calculate it again
		
		sciImage->imageSize = bCell->xDim * bCell->yDim;

		sciImage->packSize = 0;
	}

	cellImage = sciImage;	
}
	
void Cell::WriteImage(FILE *cfb)
{
	if (cfb)
	{
		fwrite(cellImage->image, cellImage->imageSize, 1, cfb);
		changed = false;
	}
}

void Cell::WritePack(FILE *cfb)
{
	CelBase *bCell = new CelBase;
	bCell = (CelBase *)&Head;
	
	if (cfb)
	{
		if (bCell->compressType)
			fwrite(cellImage->pack, cellImage->packSize, 1, cfb);
	}
}

void Cell::WriteScanLines(FILE *cfb)
{
	CelBase *bCell = new CelBase;
	bCell = (CelBase *)&Head;

	if (cfb)
	{
		if (cellImage->lines)
		{

			fwrite(cellImage->lines, bCell->yDim *4*2, 1, cfb);
		}
	}
}

void Cell::ReadLinks(FILE *cfb)
{
	CelHeaderView *bCell = new CelHeaderView;
	bCell = (CelHeaderView *)&Head;

	if (cfb && bCell->linkTableCount)
	{
		for (int i = 0; i < bCell->linkTableCount; ++i)
		{
			fread(&(linkPoints[i]), sizeof(LinkPoint), 1, cfb);
        }	
	}
}

void Cell::WriteLinks(FILE *cfb)
{
	CelHeaderView *bCell = new CelHeaderView;
	bCell = (CelHeaderView *)&Head;

	if (cfb && bCell->linkTableCount)
	{
		for (int i = 0; i < bCell->linkTableCount; ++i)
				fwrite(&(linkPoints[i]), sizeof(LinkPoint), 1, cfb);
	}
}
