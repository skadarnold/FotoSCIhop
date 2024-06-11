/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *	Used to define string costants and messages in different languages
 *	
 */

 
#ifndef LANGUAGE_H
#define LANGUAGE_H

//UNCOMMENT ONE OF THESE LINES IF YOUR COMPILER
//DOESN'T SUPPORT -D PRECOMPILER PARAMETER
 //#define ITALIAN
//#define ENGLISH
//ALSO UNCOMMENT IN RESOURCE.H


#define ID_NOERROR						0
#define ID_CANTOPENFILE					-1
#define ID_WRONGHEADER					-100
#define ID_WRONGLOOPRECSIZE				-105
#define ID_WRONGCELLRECSIZE				-110
#define ID_WRONGPALETTELOC				-120
#define ID_NOPALETTE					-121
#define ID_LINKS						-200

#ifdef ITALIAN
#include "italian.h"
#endif //ITALIAN




#ifdef ENGLISH
#include "english.h"
#endif //ENGLISH



#ifdef SPANISH
#include "spanish.h"
#endif //SPANISH



#endif //LANGUAGE_H


