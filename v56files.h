/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *  Copyright (C) Daniel Arnold 'Dhel', 2022-2024.
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

#pragma pack()

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

class V56file
{   
private:
	
	unsigned long totalImageSize = 0;
		
public:
		
	V56file(void){}
	~V56file(void);

	int LoadFile(HWND hwnd, LPSTR pszFileName);
	bool SaveFile(HWND hwnd, LPSTR szFileName);

	Palette *palSCI;
	ViewHeader Head;
	Loop *loops[MAX_LOOPS];
	
	int addLoops( int base, int amount );
	int addCells( int loop, int base, int amount );
			
	int loadCellOffset( void );

	int writeFileHeader(FILE *cfilebuf);
	int writeViewHeader(FILE *cfilebuf);
	int writeLoopHeaders(FILE *cfilebuf);
	int writeCellHeaders(FILE *cfilebuf);
	int writeImages(FILE *cfilebuf);
	int writeScanLines(FILE *cfilebuf);
	int writeLinks(FILE *cfilebuf);
};




#endif
