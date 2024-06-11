/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  global stuff
 *
 */
 
#ifndef FOTOSCIHOP_H
#define FOTOSCIHOP_H

#include "resource.h"
#include "language.h"
#include "list.h"
#include "palette.h"
#include "scicell.h"
#include "sciloop.h"
#include "p56files.h"
#include "v56files.h"


P56file32 *globalPicture = NULL;
V56file *globalView = NULL;
bool isPicture=true;

unsigned char *curShownImage = 0;
BITMAPINFO *curShownImageHeader = 0; 
Cell **curCell =0;

int MagnifyFactor = 1;
bool showpbars = false;

bool datasaved =true;

RECT rc;

HWND hWndTopBar;
HFONT hfDefault;

int picX = 0;

#endif
