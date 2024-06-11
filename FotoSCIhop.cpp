/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  This file defines the entry point for the application, GUI events, etc.
 *
 *  FotoSCIhop is a tool to modify .P56 and .V56 image files from Sierra SCI games
 *
 *  This program is part of the TraduSCI package
 *
 */
 
#include "stdafx.h"
#include "FotoSCIhop.h"
#define MAX_LOADSTRING 100

#include "english.h" // Dhel


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_PATH+20];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
char szFileName[MAX_PATH] = "";
char szNextFileName[MAX_PATH] = "";



// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


void ShowLoopCell(unsigned char newloop, unsigned char newcell)
{
	Loop **tloop=globalView->Loops()->getItem(newloop);
	if (tloop)
	{	
		curCell=(*tloop)->Cells()->getItem(newcell);
		if (curCell || (*tloop)->Mirrored())
		{
			globalView->SelectedLoop(newloop);
			if (curCell)
			{
				(*curCell)->GetImage(&curShownImageHeader, &curShownImage);
				(*tloop)->SelectedCell(newcell);
			}
			else
			{	
				curShownImage=0;
				curShownImageHeader=0;
			}

			HMENU menu = GetMenu(hWnd); 
		
			//EnableMenuItem(menu, ID_INGRANDIMENTO_NORMALE, ((*tloop)->Mirrored() ?MF_GRAYED :MF_ENABLED));
			//EnableMenuItem(menu, ID_INGRANDIMENTO_X2, ((*tloop)->Mirrored() ?MF_GRAYED :MF_ENABLED));
			//EnableMenuItem(menu, ID_INGRANDIMENTO_X3, ((*tloop)->Mirrored() ?MF_GRAYED :MF_ENABLED));
			//EnableMenuItem(menu, ID_INGRANDIMENTO_X4, ((*tloop)->Mirrored() ?MF_GRAYED :MF_ENABLED));

			EnableMenuItem(menu, ID_IMPORTABMP, ((*tloop)->Mirrored() ?MF_GRAYED :MF_ENABLED));
			EnableMenuItem(menu, ID_ESPORTABMP, ((*tloop)->Mirrored() ?MF_GRAYED :MF_ENABLED));
			EnableMenuItem(menu, ID_CICLOPRECEDENTE, MF_ENABLED);
			EnableMenuItem(menu, ID_CICLOSUCCESSIVO, MF_ENABLED);
			if (newloop == globalView->LoopsCount() -1)
				EnableMenuItem(menu, ID_CICLOSUCCESSIVO, MF_GRAYED);
		
			if (newloop == 0)
				EnableMenuItem(menu, ID_CICLOPRECEDENTE, MF_GRAYED);

			EnableMenuItem(menu, ID_CELLAPRECEDENTE, MF_ENABLED);
			EnableMenuItem(menu, ID_CELLASUCCESSIVA, MF_ENABLED);
			if ((newcell == (*tloop)->CellsCount() -1) || ((*tloop)->CellsCount()==0) )
				EnableMenuItem(menu, ID_CELLASUCCESSIVA, MF_GRAYED);
		
			if (newcell == 0)
				EnableMenuItem(menu, ID_CELLAPRECEDENTE, MF_GRAYED);


			InvalidateRgn(hWnd, NULL, true);
		}
	}
}

void SetMagnify(int value)
{
	MagnifyFactor=value;

	HMENU menu = GetMenu(hWnd);
	CheckMenuItem(menu, ID_INGRANDIMENTO_NORMALE, MF_UNCHECKED);
	CheckMenuItem(menu, ID_INGRANDIMENTO_X2, MF_UNCHECKED);
	CheckMenuItem(menu, ID_INGRANDIMENTO_X3, MF_UNCHECKED);
	CheckMenuItem(menu, ID_INGRANDIMENTO_X4, MF_UNCHECKED);

	long tID;
	switch (value)
	{
		case 1:
			tID = ID_INGRANDIMENTO_NORMALE;
			break;
		case 2:
			tID = ID_INGRANDIMENTO_X2;
			break;
		case 3:
			tID = ID_INGRANDIMENTO_X3;
			break;
		case 4:
			tID = ID_INGRANDIMENTO_X4;
			break;
		default:
			tID = ID_INGRANDIMENTO_NORMALE;

	}

	CheckMenuItem(menu, tID, MF_CHECKED);

	InvalidateRgn(hWnd,NULL,true);

}
void ShowCell(unsigned char newcell)
{
	curCell=globalPicture->Cells()->getItem(newcell);
	if (curCell)
	{	
		(*curCell)->GetImage(&curShownImageHeader, &curShownImage);
		globalPicture->SelectedCell(newcell);

		HMENU menu = GetMenu(hWnd); 

		//EnableMenuItem(menu, ID_INGRANDIMENTO_NORMALE, MF_ENABLED);
		//EnableMenuItem(menu, ID_INGRANDIMENTO_X2, MF_ENABLED);
		//EnableMenuItem(menu, ID_INGRANDIMENTO_X3, MF_ENABLED);
		//EnableMenuItem(menu, ID_INGRANDIMENTO_X4, MF_ENABLED);
	
		EnableMenuItem(menu, ID_CELLAPRECEDENTE, MF_ENABLED);
		EnableMenuItem(menu, ID_CELLASUCCESSIVA, MF_ENABLED);
		if (newcell == globalPicture->CellsCount() -1)
			EnableMenuItem(menu, ID_CELLASUCCESSIVA, MF_GRAYED);
		
		if (newcell == 0)
			EnableMenuItem(menu, ID_CELLAPRECEDENTE, MF_GRAYED);


		InvalidateRgn(hWnd, NULL, true);
	
	}
}


BOOL DoFileOpen(HWND hwnd, char *filename, char *ext)
{
   OPENFILENAME ofn;
   bool proceed = false;

   if (filename == NULL)
   {
		ZeroMemory(&ofn, sizeof(OPENFILENAME));
		//szFileName[0] = 0;

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = hwnd;
		ofn.lpstrFilter = INTERFACE_OPENFILEFILTER; 
		ofn.lpstrFile = szFileName;
		ofn.nMaxFile = MAX_PATH;

		ofn.Flags = OFN_EXPLORER | OFN_HIDEREADONLY | OFN_NOVALIDATE | OFN_FILEMUSTEXIST;
		proceed = (GetOpenFileName(&ofn)!=0);
   }
   else
   {
	    strcpy(szFileName, filename);
		proceed=true;
   }

   if(proceed)
   {
      strcpy(szNextFileName, szFileName);
      
	  if (!stricmp((ext==NULL?szFileName+ofn.nFileExtension:ext), "v56"))
		isPicture=false;
	  else   //default is .p56 when extension in unknown
		isPicture=true; 

	  int result;
	  
	  curShownImageHeader = 0;
	  curShownImage = 0;
	  curCell=0;

	  if (globalPicture)
	  {
		  delete globalPicture;
		  globalPicture=0;
	  }
	  if (globalView)
	  {
		  delete globalView;
		  globalView=0;
	  }

	  if (isPicture)
	  {
			P56file32 *newPicture = new P56file32;
			result = newPicture->LoadFile(hwnd, szFileName);
			if ( result != ID_NOERROR )
			{
				delete newPicture;
				newPicture = 0;

				char *emsg;
				switch (result)
				{
					case ID_CANTOPENFILE:
						emsg = ERR_CANTLOADFILE;
						break;
					case ID_WRONGHEADER:
						emsg = ERR_WRONGHEADER;
						break;
					case ID_WRONGCELLRECSIZE:
						emsg = ERR_WRONGCELLRECSIZE;
						break;
					case ID_WRONGPALETTELOC:
						emsg = ERR_WRONGPALETTELOC;
						break;
					default:
						emsg = ERR_CANTLOADFILE;
				}
				MessageBox(hwnd, emsg, ERR_TITLE,
							MB_OK | MB_ICONSTOP);
				
			}
			else
			{	
				globalPicture = newPicture;
				ShowCell(0);
			}

	  }
	  else //isView
	  {
			V56file *newView = new V56file;
			result = newView->LoadFile(hwnd, szFileName);
			if (result!=ID_NOERROR)
			{
				delete newView;
				newView = 0;

				char *emsg=0;
				switch (result)
				{
					case ID_CANTOPENFILE:
						emsg = ERR_CANTLOADFILE;
						break;
					case ID_WRONGHEADER:
						emsg = ERR_WRONGHEADER;
						break;
					case ID_WRONGLOOPRECSIZE:
						emsg = ERR_WRONGLOOPRECSIZE;
						break;
					case ID_WRONGCELLRECSIZE:
						emsg = ERR_WRONGCELLRECSIZE;
						break;
					case ID_WRONGPALETTELOC:
						emsg = ERR_WRONGPALETTELOC;
						break;
					default:
						emsg = ERR_CANTLOADFILE;
				}
			
				MessageBox(hwnd, emsg, ERR_TITLE, MB_OK | MB_ICONSTOP);
			
			}
			else
			{
				globalView = newView;
				ShowLoopCell(0,0);
			}

	  }

	  HMENU menu = GetMenu(hwnd); 
		

	  EnableMenuItem(menu, ID_IMPORTABMP, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_ESPORTABMP, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_SALVA, MF_GRAYED);
	  datasaved = true;
	  EnableMenuItem(menu, ID_FILE_NEXTFILE, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_SALVACOME, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_IMPORTABMP, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_ESPORTABMP, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_PROPRIET, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_CHANGEFRAMESIZE, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_PRIORITYBARS, (((result==ID_NOERROR)&&(isPicture)) ?(globalPicture->IsOldFormat()?MF_ENABLED:MF_GRAYED):MF_GRAYED));

	  EnableMenuItem(menu, ID_PALETTE, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
	  EnableMenuItem(menu, ID_COLORI_IMPORTACOLORI, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
 	  EnableMenuItem(menu, ID_COLORI_ESPORTACOLORI, (result==ID_NOERROR ?MF_ENABLED:MF_GRAYED));
   
	  if (result!=ID_NOERROR)
	  {
			EnableMenuItem(menu, ID_CICLOPRECEDENTE, MF_GRAYED);
			EnableMenuItem(menu, ID_CICLOSUCCESSIVO, MF_GRAYED);
			EnableMenuItem(menu, ID_CELLAPRECEDENTE, MF_GRAYED);
			EnableMenuItem(menu, ID_CELLASUCCESSIVA, MF_GRAYED);
	  }


	  InvalidateRgn(hwnd, NULL, true);

      char wname[MAX_PATH + 15] = "FotoSCIhop";
      if (result==ID_NOERROR)
	  {
		  GetWindowRect(hWnd, &rc);
		  unsigned long maxstrlen=(rc.right-rc.left)/8 -12;
		  if (maxstrlen<0)
			  maxstrlen = 10;
		  strcat(wname, " - ");
		  if (strlen(szFileName)<maxstrlen)
			strcat(wname, szFileName);
		  else
		  {
			int pos = 2;
			for (int i=strlen(szFileName); i>strlen(szFileName)-maxstrlen+3; i--) 
				if (szFileName[i] == '\\')
					pos = i;
			
			strcat(wname, "...");
			strcat(wname, (char *)(((long)szFileName)+pos));
		  }
      }
      SetWindowText(hwnd, wname);    
              
      return (result==ID_NOERROR);
   }
   return FALSE;
}

BOOL DoFileSave(HWND hwnd)
{
   if (FILE *tempf = fopen(szFileName, "rb"))
      fclose(tempf);
   else {
      MessageBox(hwnd, ERR_FILEMOVED, ERR_TITLE, MB_OK | MB_ICONSTOP);
      return FALSE;
   }
   
   int btn;   

   btn = MessageBox (hwnd, WARN_OVERWRITE, WARN_ATTENTION,
                              MB_APPLMODAL | MB_ICONQUESTION | MB_OKCANCEL);
   if (btn == IDCANCEL)
         return FALSE; 

  
   if(!(isPicture ?globalPicture->SaveFile(hwnd, szFileName):globalView->SaveFile(hwnd, szFileName)))
   { 
       MessageBox(hwnd, ERR_CANTSAVECHANGES, ERR_TITLE,
                  MB_OK | MB_ICONSTOP);
       return FALSE;
   } else {
       datasaved = true;
	   HMENU menu = GetMenu(hwnd); 
       EnableMenuItem(menu, ID_SALVA, MF_GRAYED);
   }

   InvalidateRect(hwnd, NULL, true); 

   return TRUE;
}

BOOL DoNextFile(HWND hwnd)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	char *fname=0;

	int pos = 0;
	char fpath[MAX_PATH];
	for (unsigned int i=0; i<strlen(szNextFileName); i++) 
		if (szNextFileName[i] == '\\')
			pos = i;

	fname = (char *)(((unsigned long) szNextFileName) + pos+1);
	strncpy(fpath, szNextFileName,pos+1);
	fpath[pos+1]=0;


	char searchstr[MAX_PATH];
	sprintf(searchstr, "%s*.?56", fpath); 

	hFind = FindFirstFile(searchstr, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE) 
	{
		MessageBox(hwnd, INTERFACE_INVALIDSEARCHHANDLE, INTERFACE_SEARCHTITLE,
                  MB_OK | MB_ICONEXCLAMATION);
		
	} 
	else 
	{
		bool retvalue = true;
		bool passed =false;
		char *extension=0;
		


		if (!stricmp(szNextFileName, fpath))
			passed = true;
		

		do
		{			
			if (retvalue)
			{
				if (passed)
				{
					extension = (char *)(((unsigned long) FindFileData.cFileName) + strlen(FindFileData.cFileName)-3);
					strcat(fpath, FindFileData.cFileName);				
                    DoFileOpen(hwnd, fpath, extension);
					FindClose(hFind);
                    
					return TRUE;
				}
				if (!stricmp(FindFileData.cFileName, fname))
					passed = true;
			}
			retvalue = (FindNextFile(hFind, &FindFileData) != 0);
		}
		while (retvalue);
			

		MessageBox(hwnd, INTERFACE_ENDOFFILESSTR, INTERFACE_SEARCHTITLE,
                  MB_OK | MB_ICONINFORMATION);

		strcpy(szNextFileName, fpath);
		
		FindClose(hFind);
		
	}

	return FALSE;
}


BOOL DoFileSaveAs(HWND hwnd)
{
   OPENFILENAME ofn;
   char szSaveFileName[MAX_PATH] = "";

   ZeroMemory(&ofn, sizeof(ofn));
   //szSaveFileName[0] = 0;

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hwnd;
   ofn.lpstrFilter = (isPicture ?INTERFACE_SAVEFILEFILTERP56 :INTERFACE_SAVEFILEFILTERV56);
   //ofn.nFilterIndex = 2;
   ofn.lpstrFile = szSaveFileName;
   ofn.nMaxFile = MAX_PATH;
   ofn.lpstrDefExt = (isPicture ?"p56" :"v56"); 

   ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY |
               OFN_OVERWRITEPROMPT;
   
   if(GetSaveFileName(&ofn))
   {
        if(!(isPicture ?globalPicture->SaveFile(hwnd, szSaveFileName):globalView->SaveFile(hwnd, szSaveFileName)))
		{ 
			MessageBox(hwnd, ERR_CANTSAVE, ERR_TITLE,
                  MB_OK | MB_ICONSTOP);
			return FALSE;
		} else {
			datasaved = true;
			HMENU menu = GetMenu(hwnd); 
			EnableMenuItem(menu, ID_SALVA, MF_GRAYED);
		}

		char wname[MAX_PATH + 15] = "FotoSCIhop";
        strcat(wname, " - ");
        strcat(wname, szSaveFileName);
		
		SetWindowText(hwnd, wname); 

       memcpy(szFileName, szSaveFileName, MAX_PATH); 
       //FIX is this the best solution? by doing this, the source folder is always changed!
   }

   InvalidateRect(hwnd, NULL, true);

   return TRUE;
}

int DoSaveChangesDialog(HWND hwnd)
{
	
	int btn;

	if (!datasaved)
	{
	
		btn = MessageBox (hwnd, WARN_UNSAVEDCHANGES, WARN_ATTENTION, 
								MB_APPLMODAL | MB_ICONQUESTION | MB_YESNOCANCEL);
		if (btn == IDYES)
			if (!DoFileSave(hwnd))
				return IDCANCEL;
	}
	else
		btn = IDNO;


	return btn;	
}

BOOL DoFileExport(HWND hwnd)
{
   OPENFILENAME ofn;
   char szBMPFileName[MAX_PATH] = "";

   ZeroMemory(&ofn, sizeof(ofn));

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hwnd;
   ofn.lpstrFilter = INTERFACE_BMPFILTER;
   ofn.lpstrFile = szBMPFileName;
   ofn.nMaxFile = MAX_PATH;
   ofn.lpstrDefExt = "bmp";

   ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY |
               OFN_OVERWRITEPROMPT;
         
   if(GetSaveFileName(&ofn))
   {
		FILE *tempfile = fopen(szBMPFileName,"wb");
		if (tempfile)
		{
			BITMAPFILEHEADER tfileheader;
			tfileheader.bfType='MB';
			tfileheader.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+256*(sizeof(RGBQUAD));
			tfileheader.bfSize=tfileheader.bfOffBits+curShownImageHeader->bmiHeader.biSizeImage;
			tfileheader.bfReserved1=0;
			tfileheader.bfReserved2=0;

			fwrite(&tfileheader, sizeof(BITMAPFILEHEADER),1,tempfile);
			BITMAPINFOHEADER tbmiheader;
            memcpy(&tbmiheader, &(curShownImageHeader->bmiHeader),sizeof(BITMAPINFOHEADER));
            tbmiheader.biHeight = abs(tbmiheader.biHeight);
   
            fwrite(&tbmiheader,sizeof(BITMAPINFOHEADER),1,tempfile);
			fwrite(curShownImageHeader->bmiColors,256*sizeof(RGBQUAD),1,tempfile);
			
            long mywidth = tbmiheader.biSizeImage / tbmiheader.biHeight; 
            
            for (long i=tbmiheader.biHeight-1; i>=0; i--)
                fwrite((void *)((unsigned long)curShownImage+ i*mywidth),mywidth,1,tempfile);

			fclose(tempfile);
		} else
		{
           MessageBox(hWnd, ERR_CANTEXPORTBMP, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
           return FALSE;
        }

   }

   return TRUE;
}

BOOL DoFileImport(HWND hwnd)
{
   OPENFILENAME ofn;
   char szBMPFileName[MAX_PATH] = "";

   ZeroMemory(&ofn, sizeof(OPENFILENAME));
   //szFileName[0] = 0;

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hwnd;
   ofn.lpstrFilter = INTERFACE_BMPFILTER; 
   ofn.lpstrFile = szBMPFileName;
   ofn.nMaxFile = MAX_PATH;

   ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
   if(GetOpenFileName(&ofn))
   {
		FILE *tempfile = fopen(szBMPFileName,"rb");
		if (tempfile)
		{
			BITMAPFILEHEADER tfh;	
			fread(&tfh, sizeof(BITMAPFILEHEADER),1,tempfile);

			if (tfh.bfType!='MB')
			{
				MessageBox(hWnd, ERR_INVALIDBMP, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
				fclose(tempfile);
				return FALSE;
			}

			BITMAPINFOHEADER tbih;
			fread(&tbih,sizeof(BITMAPINFOHEADER),1,tempfile);

			if (tbih.biBitCount!=8)
			{
				MessageBox(hWnd, ERR_INVALIDCBITBMP, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
				fclose(tempfile);
				return FALSE;
			}

			if (tbih.biCompression != BI_RGB)
			{
				MessageBox(hWnd, ERR_INVALIDCOMPBMP, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
				fclose(tempfile);
				return FALSE;
			}

			//user will decide:

			if ((abs(tbih.biHeight) != abs(curShownImageHeader->bmiHeader.biHeight))
										||
				(tbih.biWidth != curShownImageHeader->bmiHeader.biWidth))
			{			
				int btn;   

				btn = MessageBox (hwnd, WARN_DIFFERENTDIM, WARN_ATTENTION,
                              MB_APPLMODAL | MB_ICONQUESTION | MB_OKCANCEL);
				if (btn == IDCANCEL)
				{
					fclose(tempfile);
					return FALSE;
				}
			}
			
			RGBQUAD tctab[256];
			fread(tctab,256*sizeof(RGBQUAD),1,tempfile);

			bool remap = false;
			if (memcmp(tctab, curShownImageHeader->bmiColors, 256*sizeof(RGBQUAD)))
	/*		{			
				int btn;   

				btn = MessageBox (hwnd, WARN_DIFFERENTPAL, WARN_ATTENTION,
                              MB_APPLMODAL | MB_ICONQUESTION | MB_OKCANCEL);
				if (btn == IDCANCEL)
				{
					fclose(tempfile);
					return FALSE;
				}
				remap =true;
			}*/
			{
				MessageBox(hWnd, ERR_DIFFERENTPALBIS, ERR_TITLE,
                            MB_OK | MB_ICONEXCLAMATION);
				fclose(tempfile);
				return FALSE;
			}

			bool isBottomTop=(tbih.biHeight>0);

			unsigned long newheight = abs(tbih.biHeight);

			unsigned long expectedsize = tbih.biWidth*newheight;
			int dwremainder = tbih.biWidth%4;
			if (dwremainder)
				expectedsize+= newheight*(4-dwremainder); //bmp requires DWORD align for each scanline

			fseek(tempfile, 0, SEEK_END);
			unsigned long imsize = ftell(tempfile) -tfh.bfOffBits;

			fseek(tempfile, tfh.bfOffBits, SEEK_SET);

			if (expectedsize>imsize)//(expectedsize!=imsize)      changed to support Photoshop BMPs
			{
				MessageBox(hWnd, ERR_INVALIDSIZEBMP, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
				fclose(tempfile);
				return FALSE;
			}

			unsigned long newwidth = tbih.biWidth + (dwremainder ?4-dwremainder :0);
			unsigned char *timage = (unsigned char *) new char[imsize];
			if (!isBottomTop)
				fread(timage, imsize, 1, tempfile);
			else
				for (long i = newheight-1; i>=0; i--)
					fread(&(timage[newwidth*i]),newwidth,1,tempfile);

			if (remap)
			{
				//for (unsigned long i=0; i<imsize; i++)

				//TODO implement REMAPPING!!!!!!
				MessageBox(hWnd, ERR_REMAPNOTIMPLEMENTEDYET, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
				fclose(tempfile);
				return FALSE;
			}

			long tsizep = ((sizeof(BITMAPINFO)) + 256*(sizeof(RGBQUAD)));

			BITMAPINFO *tbinfo = (BITMAPINFO *) new char[tsizep];

			tbinfo->bmiHeader.biBitCount=8;
			tbinfo->bmiHeader.biClrImportant=256;
			tbinfo->bmiHeader.biClrUsed=256;
			tbinfo->bmiHeader.biCompression=BI_RGB;
			tbinfo->bmiHeader.biHeight=-newheight; //so that it will be a top-down DIB
			tbinfo->bmiHeader.biPlanes=1;
			tbinfo->bmiHeader.biSize=sizeof(BITMAPINFOHEADER);
			tbinfo->bmiHeader.biSizeImage=imsize;
			tbinfo->bmiHeader.biWidth=tbih.biWidth;
			tbinfo->bmiHeader.biXPelsPerMeter=0; 
			tbinfo->bmiHeader.biYPelsPerMeter=0;
			 
						
			for (int i=0; i<256; i++)
				tbinfo->bmiColors[i]= tctab[i];

			
			if (curCell)
			{
				(*curCell)->SetImage(tbinfo, timage);

				curShownImage = timage;
				curShownImageHeader = tbinfo;
					  
				HMENU menu = GetMenu(hwnd); 
		
				EnableMenuItem(menu, ID_SALVA, MF_ENABLED);
				datasaved = false;
			}
			else
			{
				delete timage;
				delete tbinfo;
			}

			InvalidateRect(hwnd, NULL, true); 

			fclose(tempfile);
			return TRUE;
		}

        MessageBox(hwnd, ERR_CANTLOADFILE, ERR_TITLE,
							MB_OK | MB_ICONSTOP);
   }
   return TRUE;
}

BOOL DoPaletteImport(HWND hwnd)
{
   OPENFILENAME ofn;
   char szPALFileName[MAX_PATH] = "";

   ZeroMemory(&ofn, sizeof(OPENFILENAME));
   //szFileName[0] = 0;

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hwnd;
   ofn.lpstrFilter = INTERFACE_PALINFILTER; 
   ofn.lpstrFile = szPALFileName;
   ofn.nMaxFile = MAX_PATH;

   ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
   if(GetOpenFileName(&ofn))
   {
		FILE *tempfile = fopen(szPALFileName,"rb");
		if (tempfile)
		{
            Palette *tnewpal;
            if (!stricmp(szPALFileName+ofn.nFileExtension, "bmp"))
			{
                //load a palette from a bitmap
                BITMAPFILEHEADER tfh;	
                fread(&tfh, sizeof(BITMAPFILEHEADER),1,tempfile);

                if (tfh.bfType!='MB')
                {
				  MessageBox(hWnd, ERR_INVALIDBMP, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
				  fclose(tempfile);
				  return FALSE;
			    }

                BITMAPINFOHEADER tbih;
			    fread(&tbih,sizeof(BITMAPINFOHEADER),1,tempfile);

			    if (tbih.biBitCount!=8)
			    {
				  MessageBox(hWnd, ERR_INVALIDCBITBMP, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
				  fclose(tempfile);
				  return FALSE;
			    }

			    if (tbih.biCompression != BI_RGB)
			    {
				  MessageBox(hWnd, ERR_INVALIDCOMPBMP, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
				  fclose(tempfile);
				  return FALSE;
			    }
			
			    RGBQUAD tctab[256];
			    fread(tctab,256*sizeof(RGBQUAD),1,tempfile);
                
                if (isPicture)
					tnewpal = globalPicture->PalSCI();
                else
                    tnewpal = globalView->PalSCI(); 
                                                      
			    for (int i=0; i<256; i++)
				{
                   PalEntry *pe = tnewpal->GetPalEntry(i);
                   PalEntry npe;
                   npe.remap = (pe == NULL ? 0: pe->remap);
                   npe.blue = tctab[i].rgbBlue;
			       npe.green = tctab[i].rgbGreen;
                   npe.red = tctab[i].rgbRed;
                   tnewpal->SetPalEntry(npe, i);
                }
                
                
            } else {
              tnewpal= new Palette;
   
              fseek(tempfile, 0, SEEK_END);
              unsigned long tpsize = ftell(tempfile);
              fseek(tempfile, 0, SEEK_SET);
			  if (tnewpal->loadPalette(tempfile, tpsize))
			  {
				if (isPicture)
				{
					delete globalPicture->PalSCI();
					globalPicture->PalSCI(tnewpal);
                }
				else
				{
					delete globalView->PalSCI();
					globalView->PalSCI(tnewpal);	
				}
              }
			  else
			  {
				delete tnewpal;
				MessageBox(hwnd, ERR_CANTLOADPALETTE, ERR_TITLE,
							MB_OK | MB_ICONSTOP);
       
                fclose(tempfile);
			    return TRUE;
				
			  }

            }

            curShownImage = 0;
			curShownImageHeader = 0;
   
            if (isPicture)
            {   
                //cycle for clearing images cache
                for (int i=0; i<globalPicture->CellsCount(); i++)
				{
						(*globalPicture->Cells()->getItem(i))->MyPalette(&tnewpal);
				}
     
                ShowCell(globalPicture->SelectedCell());                                                      
            } else
            {            
                 //cycle for clearing images cache
                for (int j=0; j<globalView->LoopsCount(); j++)
				{
						Loop **tloop=globalView->Loops()->getItem(j);
						for (int i=0; i<(*tloop)->CellsCount(); i++)
						{
							(*(*tloop)->Cells()->getItem(i))->MyPalette(&tnewpal);
							
						}
						
				}
                
                ShowLoopCell(globalView->SelectedLoop(), (*globalView->Loops()->getItem(globalView->SelectedLoop()))->SelectedCell());
            }

            HMENU menu = GetMenu(hwnd); 
		
			EnableMenuItem(menu, ID_SALVA, MF_ENABLED);
			datasaved = false;
    
			InvalidateRect(hwnd, NULL, true); 

			fclose(tempfile);
			return TRUE;
		}

		MessageBox(hwnd, ERR_CANTLOADFILE, ERR_TITLE,
							MB_OK | MB_ICONSTOP);
   }
   return TRUE;
}

BOOL DoPaletteExport(HWND hwnd)
{
   OPENFILENAME ofn;
   char szPALFileName[MAX_PATH] = "";

   ZeroMemory(&ofn, sizeof(ofn));

   ofn.lStructSize = sizeof(ofn);
   ofn.hwndOwner = hwnd;
   ofn.lpstrFilter = INTERFACE_PALFILTER;
   ofn.lpstrFile = szPALFileName;
   ofn.nMaxFile = MAX_PATH;
   ofn.lpstrDefExt = "pal";

   ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY |
               OFN_OVERWRITEPROMPT;
         
   if(GetSaveFileName(&ofn))
   {
		FILE *tempfile = fopen(szPALFileName,"wb");
		if (tempfile)
		{
			if (isPicture)
				globalPicture->PalSCI()->WritePalette(tempfile, true);
			else
				globalView->PalSCI()->WritePalette(tempfile, true);

			fclose(tempfile);
		} else
		{
           MessageBox(hWnd, ERR_CANTEXPORTPALETTE, ERR_TITLE,
                            MB_OK | MB_ICONSTOP);
           return FALSE;
        }

   }

   return TRUE; 
}

BOOL CALLBACK ChangeFrameSizeProc(HWND hwndDlg, 
                             UINT message, 
                             WPARAM wParam, 
                             LPARAM lParam) 
{ 
    switch (message) 
    { 
        case WM_INITDIALOG:
        {
       		if (curCell)
            {
               SetDlgItemInt(hwndDlg, IDDI_LEFT, (*curCell)->Left(), TRUE);
               SetDlgItemInt(hwndDlg, IDDI_TOP, (*curCell)->Top(), TRUE);
               SetDlgItemInt(hwndDlg, IDDI_WIDTH, (*curCell)->Width(), TRUE);
               SetDlgItemInt(hwndDlg, IDDI_HEIGHT, (*curCell)->Height(), TRUE);
            }
        
            return TRUE;
        }   
    
        case WM_COMMAND: 
            switch (LOWORD(wParam)) 
            { 
                case IDOK: 
                
       		       if (curCell)
                   {
                        (*curCell)->Left(GetDlgItemInt(hwndDlg, IDDI_LEFT, NULL, TRUE));
                        (*curCell)->Top(GetDlgItemInt(hwndDlg, IDDI_TOP, NULL, TRUE));
                        (*curCell)->Width(GetDlgItemInt(hwndDlg, IDDI_WIDTH, NULL, TRUE));
                        (*curCell)->Height(GetDlgItemInt(hwndDlg, IDDI_HEIGHT, NULL, TRUE));
                   }
 
                case IDCANCEL: 
                    EndDialog(hwndDlg, wParam); 
                    return TRUE; 
            } 
    } 
    return FALSE; 
} 


void DoChangeFrameSize(HWND hwnd)
{
            if (DialogBox(NULL, 
                          MAKEINTRESOURCE(IDD_CHANGEFRAMESIZE), 
                          hwnd, 
                          (DLGPROC)ChangeFrameSizeProc)==IDOK) 
            {
                HMENU menu = GetMenu(hwnd); 
		
				EnableMenuItem(menu, ID_SALVA, MF_ENABLED);
				datasaved = false;
                
                RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW);
            
            }

            else 
            {
                // Cancel the command. 
            } 
}

void DoPropertyBox(HWND hwnd)
{
	char propstr[1024]="";

	if (isPicture)
	{
		char tscreenres[64];
		sprintf(tscreenres, "%d x %d", globalPicture->MaxWidth(), globalPicture->MaxHeight());
		if (globalPicture->MaxHeight()==0)
			switch (globalPicture->MaxWidth())
			{
			case 0:
				strcat(tscreenres, " (320 x 200)");
				break;
			case 1:
				strcat(tscreenres, " (640 x 480)");
				break;
			case 2:
				strcat(tscreenres, " (640 x 400)");
				break;
			}
		sprintf(propstr, INTERFACE_P56PROPSTR,
						' ',' ',
						globalPicture->CellsCount(),
						(globalPicture->IsCompressed()?"":INTERFACE_NOTSTR),
						tscreenres,
						globalPicture->CellRecSize());
						
		if (globalPicture->IsOldFormat())
		{
			sprintf(tscreenres, "\n%s%ld\n", INTERFACE_VECTORSIZESTR, globalPicture->VectorSize());
			strcat(propstr, tscreenres);
			
			sprintf(tscreenres, INTERFACE_PRIORITYSTR, globalPicture->nPriorities(), globalPicture->PriLineCount());
			strcat(propstr, tscreenres);
		}
		
		if (curCell)
		{
            char tcell[256];
            sprintf(tcell, INTERFACE_P56CELLPROPSTR,
						' ',
						globalPicture->SelectedCell()+1,
						' ',
						(*curCell)->Width(),(*curCell)->Height(),
						(*curCell)->Left(),(*curCell)->Top(),
						(*curCell)->SkipColor(),
						(*curCell)->Compression(),
						(*curCell)->Flags(),
						(*curCell)->ZDepth(),
						(*curCell)->XPos(),
						(*curCell)->YPos()
						);
			strcat(propstr, tcell);
        }
	}
	else //isView
	{
		char tviewres[64], tscreenres[64], tcell[256];
		sprintf(tviewres, "%d", globalView->ViewSize());
		switch (globalView->ViewSize())
		{
		case 0:
			strcat(tviewres, " (320 x 200)");
			break;
		case 1:
			strcat(tviewres, " (640 x 480)");
			break;
		case 2:
			strcat(tviewres, " (640 x 400)");
			break;
		}

		sprintf(tscreenres, "%d x %d", globalView->MaxWidth(), globalView->MaxHeight());
		if ((globalView->MaxWidth() == 0) && (globalView->MaxHeight() == 0))
		{
			strcat(tscreenres, INTERFACE_SEEVIEWRESSTR);
		}

		Loop **tloop=globalView->Loops()->getItem(globalView->SelectedLoop());
		sprintf(propstr, INTERFACE_PROPVIEWSTR,
						' ', ' ',
						globalView->LoopsCount(),
						globalView->StripView(),
						(globalView->IsCompressed()?"":INTERFACE_NOTSTR),
						tviewres,
						globalView->TotalCellsCount(),
						globalView->LoopRecSize(),
						globalView->CellRecSize(),
						tscreenres,

						' ',
						globalView->SelectedLoop()+1,
						' ',
						(*tloop)->CellsCount(),
						(*tloop)->BasedOn(),
						((*tloop)->Mirrored()?"":INTERFACE_NOTSTR),
						(*tloop)->ContLoop(),                
                        (*tloop)->StartCel(),                                   
                        (*tloop)->EndCel(),
                        (*tloop)->RepeatCount(),                       
                        (*tloop)->StepSize()
						);
		
		if (curCell)
		{
			sprintf(tcell, INTERFACE_VIEWCELLPROPSTR,
							' ',
							(*tloop)->SelectedCell()+1,
							' ',
							(*curCell)->Width(),(*curCell)->Height(),
							(*curCell)->Left(),(*curCell)->Top(),
							(*curCell)->SkipColor(),
							(*curCell)->Compression(),
							(*curCell)->Flags()
							);
			strcat(propstr, tcell);
			
			if (globalView->HasLinks())
			{
                sprintf(tcell, INTERFACE_LINKCOUNTSTR, (*curCell)->LinksCount());
			    strcat(propstr, tcell);
            }
		}

	}

	MessageBox(hwnd, propstr, INTERFACE_PROPERTIES, MB_OK);
}


typedef BOOL (WINAPI*Func)(HWND, char *, unsigned char, char *, char *);
 
/* this is what is going to hold our function, I like to name it like the function we are importing,
    but you can make it whatever you like. */
Func ExtractFromVolume;


#ifdef __DEVC

int STDCALL WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPTSTR    lpCmdLine,
                    int       nCmdShow)
{

#else 
int APIENTRY _tWinMain (HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{      
#endif
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_IMMAGINA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_IMMAGINA);

    HINSTANCE DLL = LoadLibrary("SCIdump.dll");
    /* check for error on loading the DLL */
    if(DLL==NULL) 
              MessageBox(NULL, ERR_CANTLOADDLL, ERR_TITLE, MB_OK | MB_ICONERROR);

    ExtractFromVolume=(Func)GetProcAddress((HMODULE)DLL, "?ExtractFromVolumeSkel@@YAHPAUHWND__@@PADE11@Z");
    /* check for error on getting the function */
    if(ExtractFromVolume==NULL) 
    {
       FreeLibrary((HMODULE)DLL);
       MessageBox(NULL, ERR_CANTLOADDLL, ERR_TITLE, MB_OK | MB_ICONERROR);
    }         
    
    if (lpCmdLine[0]!=0)
    {
	   char startupfile[MAX_PATH];
       if (lpCmdLine[0]=='\"')
	   {
		   strncpy(startupfile, lpCmdLine+1,strlen(lpCmdLine)-2);
		   startupfile[strlen(lpCmdLine)-2]=0;
	   }
	   else
		   strcpy(startupfile, lpCmdLine);

       DoFileOpen(hWnd, startupfile, startupfile+(strlen(startupfile)-3));
	}
 
    // Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

    FreeLibrary((HMODULE)DLL);
 
	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_IMMAGINA);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName	= (LPCTSTR)IDC_IMMAGINA;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon((HINSTANCE)wcex.hInstance, (LPCTSTR)IDI_SMALL);

	return RegisterClassEx(&wcex);
}



//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 400, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);

   hfDefault = CreateFont(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_SWISS, "MS Sans Serif");

   UpdateWindow(hWnd);

   return TRUE;
}



void exit_proc(HWND hwnd)
{
	if (globalPicture)
		  delete globalPicture;


	 if (globalView)
		  delete globalView;

	DeleteObject(hfDefault);
	DestroyWindow(hwnd);
}


//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
// 
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message) 
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam); 
		wmEvent = HIWORD(wParam); 
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
  
			break;
        case IDM_MANUAL:
          {
            char szAppPath[MAX_PATH];
            GetModuleFileName(NULL, szAppPath, MAX_PATH);
            szAppPath[strrchr(szAppPath, '\\') - szAppPath] = '\0'; 
            ShellExecute(hWnd, "open", MANUAL_PATH, NULL, szAppPath, SW_SHOW);
            break; 
          }
	    case ID_CARICA:
			if (DoSaveChangesDialog(hWnd) != IDCANCEL) 
				DoFileOpen(hWnd, NULL, NULL);
			break;
        case ID_CARICAV56VOL:
        {
            char exFile[MAX_PATH]="";
            if (ExtractFromVolume(hWnd, NULL, 0x80, "v56", exFile))
                DoFileOpen(hWnd, exFile, "v56");         
            break;
		}
        case ID_CARICAP56VOL:
        {
            char exFile[MAX_PATH]="";
            if (ExtractFromVolume(hWnd, NULL, 0x81, "p56", exFile))
                DoFileOpen(hWnd, exFile, "p56");         
            break;
		}
        case ID_FILE_NEXTFILE:
			DoNextFile(hWnd);
            RedrawWindow(hWnd, NULL, NULL, RDW_UPDATENOW);
            Sleep(200);
			break;
		case ID_SALVA:
			DoFileSave(hWnd);
			break;
		case ID_SALVACOME:
			DoFileSaveAs(hWnd);
			break;
		case ID_IMPORTABMP:
			DoFileImport(hWnd);
			break;
		case ID_ESPORTABMP:
			DoFileExport(hWnd);
			break;
		case ID_PROPRIET:
			DoPropertyBox(hWnd);
			break;
   
        case ID_CHANGEFRAMESIZE:
             DoChangeFrameSize(hWnd);
             break;
             
		case ID_PALETTE:
			{
				HMENU menu = GetMenu(hWnd);
				switch (CheckMenuItem(menu, ID_PALETTE, MF_BYCOMMAND))
				{
				case MF_CHECKED:
					CheckMenuItem(menu, ID_PALETTE, MF_UNCHECKED);
					picX=0;
					break;

				case MF_UNCHECKED:
					CheckMenuItem(menu, ID_PALETTE, MF_CHECKED);
					picX=190;
					break;
				}
				
				InvalidateRgn(hWnd, NULL, true);
				
				break;
			}
		case ID_COLORI_IMPORTACOLORI:
			DoPaletteImport(hWnd);
			break;
		case ID_COLORI_ESPORTACOLORI:
			DoPaletteExport(hWnd);
			break;
		case ID_INGRANDIMENTO_NORMALE:
			SetMagnify(1);
			break;
		case ID_INGRANDIMENTO_X2:
			SetMagnify(2);
			break;
		case ID_INGRANDIMENTO_X3:
			SetMagnify(3);
			break;
		case ID_INGRANDIMENTO_X4:
			SetMagnify(4);
			break;
		case ID_PRIORITYBARS:
			{
				HMENU menu = GetMenu(hWnd);
				switch (CheckMenuItem(menu, ID_PRIORITYBARS, MF_BYCOMMAND))
				{
				case MF_CHECKED:
					CheckMenuItem(menu, ID_PRIORITYBARS, MF_UNCHECKED);
					showpbars=false;
					break;

				case MF_UNCHECKED:
					CheckMenuItem(menu, ID_PRIORITYBARS, MF_CHECKED);
					showpbars=true;
					break;
				}
				
				InvalidateRgn(hWnd, NULL, true);
				
				break;
			}
		case ID_CICLOPRECEDENTE:
			if (!isPicture)
				ShowLoopCell(globalView->SelectedLoop()-1,0);
			break;
		case ID_CICLOSUCCESSIVO:
			if (!isPicture)
				ShowLoopCell(globalView->SelectedLoop()+1,0);
			break;

		case ID_CELLAPRECEDENTE:
			if (isPicture)
				ShowCell(globalPicture->SelectedCell()-1);
			else
			{
				Loop **tloop = globalView->Loops()->getItem(globalView->SelectedLoop());
				if (tloop)
				{
					ShowLoopCell(globalView->SelectedLoop(),(*tloop)->SelectedCell()-1);
				}
			}
			break;
		case ID_CELLASUCCESSIVA:
			if (isPicture)
				ShowCell(globalPicture->SelectedCell()+1);
			else
			{
				Loop **tloop = globalView->Loops()->getItem(globalView->SelectedLoop());
				if (tloop)
				{
					ShowLoopCell(globalView->SelectedLoop(),(*tloop)->SelectedCell()+1);
				}
			}
			break;
		case IDM_EXIT:
			if (DoSaveChangesDialog(hWnd) != IDCANCEL)   
				exit_proc(hWnd);
            break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		{
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hfDefault);
		GetClientRect (hWnd, &rc);
		SetBkMode(hdc, TRANSPARENT);
		GetWindowRect(hWnd, &rc);
		long int twidth = rc.right-rc.left;
		SetRect(&rc, 0, 0, twidth, 20);
		FillRect(hdc, &rc, GetSysColorBrush(COLOR_BTNFACE));
		
		if (curCell)
			{
				char finalstr[64];
				sprintf(finalstr, INTERFACE_SKIPCOLORSTR, (*curCell)->SkipColor());
				SetRect(&rc, 250, 0, 390, 20);
				DrawText (hdc, finalstr, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				//or TextOut(hdc, 230,0, finalstr,strlen(finalstr));
				if (curShownImageHeader)
				{
					RGBQUAD tquad = curShownImageHeader->bmiColors[(*curCell)->SkipColor()];
					HBRUSH tbrush =CreateSolidBrush(RGB(tquad.rgbRed,tquad.rgbGreen,tquad.rgbBlue));
					SelectBrush(hdc, tbrush);
					Rectangle(hdc, 225,2,245,18);

					DeleteObject(tbrush);
				}
				if ((*curCell)->Changed())
				{
					SetTextColor(hdc, RGB(255,0,0));
					SetRect(&rc, 480, 0, 530, 20);
					DrawText (hdc, INTERFACE_CHANGEDSTR, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
					SetTextColor(hdc, RGB(0,0,0));
				}
			}

		if ((isPicture) && (globalPicture!=0))
		{
			char vers[10];
			strcpy(vers, (globalPicture->IsOldFormat() ?"SCI1.1":"SCI32"));
            SetRect(&rc, 25, 0, 100, 20);   
            DrawText (hdc, vers, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

			char finalstr[64];
			sprintf(finalstr, INTERFACE_CELLSSTR, globalPicture->SelectedCell() +1, globalPicture->CellsCount());
			SetRect(&rc, 125, 0, 250, 20);    
            DrawText (hdc, finalstr, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

		}

		if ((!isPicture) && (globalView!=0))
		{
			char finalstr[64];
			sprintf(finalstr, INTERFACE_LOOPSSTR, globalView->SelectedLoop() +1, globalView->LoopsCount());
            SetRect(&rc, 25, 0, 125, 20);    
            DrawText (hdc, finalstr, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

			

			Loop **tloop =globalView->Loops()->getItem(globalView->SelectedLoop());
			if (tloop)
			{
				if ((*tloop)->Mirrored())
				{
					char mirr[64];
					sprintf(mirr, INTERFACE_MIRROREDSTR, (*tloop)->BasedOn() +1);
					SetRect(&rc, 125, 0, 325, 20);
					DrawText (hdc, mirr, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

				}
				else
				{
					sprintf(finalstr, INTERFACE_CELLSSTR, (*tloop)->SelectedCell() +1, (*tloop)->CellsCount());
					SetRect(&rc, 125, 0, 225, 20);    
					DrawText (hdc, finalstr, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
				}
			}
            
            if (globalView->HasLinks())
            {
               sprintf(finalstr, "LINKS");
               SetRect(&rc, 400, 0, 450, 20);    
			   DrawText (hdc, finalstr, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
            }
			
			
		}

		if (curShownImage)
		{	
			//palette will be drawn only if the image exists
			if (picX>0)
			{
                HPEN redpen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
			           
				HBRUSH tbrush;
				Palette *tpalette=(isPicture?globalPicture->PalSCI():globalView->PalSCI());
				for (int i=0; i<16; i++)
					for (int j=0; j<16; j++)
					{
						PalEntry *tentry=tpalette->GetPalEntry(i*16 +j);
						
					
						tbrush=CreateSolidBrush(RGB(tentry->red, tentry->green, tentry->blue));

						SetRect(&rc, 10+(j*11), 30+(i*16), 20+(j*11), 40+(i*16));
						FillRect(hdc, &rc, tbrush);
						DeleteObject(tbrush);


						if (tentry->remap==1)
						{
							HPEN tpen = CreatePen(PS_SOLID, 1, RGB(255,0,0));
							SelectObject(hdc, tpen);
							MoveToEx(hdc, 10+(j*11), 41+(i*16), NULL);
							LineTo(hdc, 20+(j*11), 41+(i*16));

							MoveToEx(hdc, 10+(j*11), 40+(i*16), NULL);
							LineTo(hdc, 20+(j*11), 40+(i*16));
							SelectObject(hdc, GetStockObject(WHITE_PEN));
							DeleteObject(tpen);
							MoveToEx(hdc, 10+(j*11), 39+(i*16), NULL);
							LineTo(hdc, 20+(j*11), 39+(i*16));
							SelectObject(hdc, GetStockObject(BLACK_PEN));

						}

						if (((i*16 +j) < tpalette->FirstColor())
									||
							((i*16 +j) >= tpalette->FirstColor()+tpalette->NumColors()))
						{
                            SelectObject(hdc, redpen);
							MoveToEx(hdc, 9+(j*11), 29+(i*16), NULL);
							LineTo(hdc, 21+(j*11), 41+(i*16));
							MoveToEx(hdc, 9+(j*11), 40+(i*16), NULL);
							LineTo(hdc, 21+(j*11), 28+(i*16));
                            SelectObject(hdc, GetStockObject(BLACK_PEN));
						}

					}
                
			    if (tpalette->HasPalette())
                {
                    tbrush=CreateSolidBrush(RGB(0,255,255));

                    SetRect(&rc, 20, 300, 30, 310);
				    FillRect(hdc, &rc, tbrush);
				    DeleteObject(tbrush);

                    SelectObject(hdc, redpen);
				    MoveToEx(hdc, 19,299, NULL);
				    LineTo(hdc, 31, 311);
				    MoveToEx(hdc, 19, 310, NULL);
				    LineTo(hdc, 31, 298);
                    SelectObject(hdc, GetStockObject(BLACK_PEN));
                
				    SetRect(&rc, 40, 295, 190, 315);    
				    DrawText (hdc, INTERFACE_MISSINGCOLORSSTR, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

                    if (tpalette->HasFourEntries())
   				    {
					    SetRect(&rc, 20, 320, 30, 330);
					    FillRect(hdc, &rc, tbrush);
					    DeleteObject(tbrush);

					    SelectObject(hdc, redpen);
					    MoveToEx(hdc, 20, 332, NULL);
					    LineTo(hdc, 30, 332);										
					    MoveToEx(hdc, 20, 331, NULL);
					    LineTo(hdc, 30, 331);

					    SelectObject(hdc, GetStockObject(WHITE_PEN));
					
					    MoveToEx(hdc, 20, 330, NULL);
					    LineTo(hdc, 30, 330);
					    SelectObject(hdc, GetStockObject(BLACK_PEN));

					    SetRect(&rc, 40, 316, 190, 336);    
					    DrawText (hdc, INTERFACE_LOCKEDCOLORSSTR, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);

				    }             
                }
                else
                {
                    SetRect(&rc, 30, 300, 190, 320);    
				    DrawText (hdc, INTERFACE_MISSINGPALETTE, -1, &rc, DT_SINGLELINE | DT_LEFT | DT_VCENTER);
                }

				
                DeleteObject(redpen);
			}

			if (MagnifyFactor>1)
				StretchDIBits(hdc,10+picX,30,curShownImageHeader->bmiHeader.biWidth*MagnifyFactor,-curShownImageHeader->bmiHeader.biHeight*MagnifyFactor,0,0,curShownImageHeader->bmiHeader.biWidth,-curShownImageHeader->bmiHeader.biHeight,curShownImage,curShownImageHeader,DIB_RGB_COLORS,SRCCOPY);
			else
				SetDIBitsToDevice(hdc,10+picX,30,curShownImageHeader->bmiHeader.biWidth,-curShownImageHeader->bmiHeader.biHeight,0,0,0,-curShownImageHeader->bmiHeader.biHeight,curShownImage,curShownImageHeader,DIB_RGB_COLORS);
			if (isPicture && showpbars)
			{
				if (globalPicture->IsOldFormat())
				{
					for (int i=0;i<14;i++)
					{
						MoveToEx(hdc, 5+picX, 30+globalPicture->GetPriBar(i)*MagnifyFactor, NULL);
						LineTo(hdc, 15+picX+(*curCell)->Width()*MagnifyFactor, 30+globalPicture->GetPriBar(i)*MagnifyFactor);
					}

				}
			}
		}
		EndPaint(hWnd, &ps);
		break;
		}
	case WM_CLOSE:
		if (DoSaveChangesDialog(hWnd) != IDCANCEL)   
			exit_proc(hWnd);
        break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}


