/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  English language strings
 *
 */
 
#define INTERFACE_OPENFILEFILTER "SCI Image files (*.p56, *.v56)\0*.p56;*.v56\0SCI Picture files (*.p56)\0*.p56\0SCI View files (*.v56)\0*.v56\0All files (*.*)\0*.*\0\0"
#define INTERFACE_SAVEFILEFILTERP56 "SCI Picture file (*.p56)\0*.p56\0\0"
#define INTERFACE_SAVEFILEFILTERV56 "SCI View file (*.v56)\0*.v56\0\0"
#define INTERFACE_BMPFILTER "Bitmap file (*.bmp)\0*.bmp\0Jpeg file (*.jpg)\0*.jpg\0Png files (*.png)\0*.png\0All files (*.*)\0*.*\0\0"
#define INTERFACE_PALFILTER "SCI Palette file (*.pal)\0*.pal\0All files (*.*)\0*.*\0\0"
#define INTERFACE_PALINFILTER "Bitmap file (*.bmp)\0*.bmp\0SCI Palette file (*.pal)\0*.pal\0\0"

#define INTERFACE_ABOUTTITLE "About"

#define INTERFACE_PROPERTIES "Properties"
#define INTERFACE_P56PROPSTR "%20c   -> Global Stuff%20c\nCells: %d\n%sCompressed\nResolution: %s\nCell Record Size: %d\n"
#define INTERFACE_P56CELLPROPSTR "\n%20c   -> Selected Cell %d%20c\n\nDimension: %d x %d\nPosition: %d,%d\nTransparent color: %d\nCompression: %d\nFlags: %X\nZ priority: %d\nxyPos: %d,%d\n"
#define INTERFACE_NOTSTR "Not "
#define INTERFACE_SEEVIEWRESSTR " (see View Resolution)"
#define INTERFACE_PROPVIEWSTR "%20c   -> Global Stuff%20c\nLoops: %d\nStrip View: %d\n%sCompressed\nView Resolution: %s\nTotal Cells: %d\nLoop Record Size: %d\nCell Record Size: %d\nResolution: %s\n\n"
#define INTERFACE_VIEWLOOPPROPSTR "%20c   -> Selected Loop %d%20c\nCells: %d\nBased on Loop: %d\n%sMirrored\nCont. Loop.: %d\nStart Cell: %d\nEnd Cell: %d\nRepeat Count: %d\nStep Size: %d\n"
#define INTERFACE_VIEWCELLPROPSTR "\n%20c   -> Selected Cell %d%20c\n\nSize: %d x %d\nPosition: %d,%d\nTransparent color: %d\nCompression: %d\nFlags: %X\n\n"
#define INTERFACE_PROPTABLE propstr
#define INTERFACE_VECTORSIZESTR "Vectors Size: "
#define INTERFACE_PRIORITYSTR   "\nPriorities: %d\nPriority Lines Count: %d\n"

#define INTERFACE_SKIPCOLORSTR "Transparent Color %d"
#define INTERFACE_CELLSSTR "Cell %d of %d"
#define INTERFACE_LOOPSSTR "Loop %d of %d"
#define INTERFACE_MIRROREDSTR "Mirrored version of Loop %d"

#define INTERFACE_CHANGEFRAMESIZE "Change Cell Position..."
#define INTERFACE_MODIFY_PROPERTIES "Modify Properties..."
#define INTERFACE_CANCEL	"Cancel"
#define INTERFACE_LEFT		"Left"
#define INTERFACE_TOP		"Top"
#define INTERFACE_WIDTH		"Width"
#define INTERFACE_HEIGHT	"Height"
#define INTERFACE_RESX		"Res X"
#define INTERFACE_RESY		"Res Y"
#define INTERFACE_POSX		"Pos X"
#define INTERFACE_POSY		"Pos Y"

#define INTERFACE_CHANGEDSTR "Changed"

#define INTERFACE_MISSINGCOLORSSTR "Missing Colors"
#define INTERFACE_LOCKEDCOLORSSTR "Unremappable Colors"
#define INTERFACE_MISSINGPALETTE "Palette is Missing!"

#define INTERFACE_SEARCHTITLE "Search Status"
#define INTERFACE_ENDOFFILESSTR "There are no more files next. Searching will continue from the first file in this directory."
#define INTERFACE_INVALIDSEARCHHANDLE "Searching cannot be continued, the file might have been moved or deleted."

#define INTERFACE_LICENSE "This program is open source (GNU GPL license), and can be freely distributed and modified provided that it stays open source."
#define INTERFACE_UPDATES "In Memory of Michele Del Bene (Micartu).\n\nUpdates on http://erolfi.wordpress.com\n\nFor problems, suggestions and other write to: \n erolfi on gmail.com"
#define INTERFACE_NOTICE "The author declines from every responsibility on possible damages caused by its use.\n\nSCI (Sierra Creative Interpreter) is a trademark of Sierra On-line that holds copyrights on it.  "

#define MENU_FILE "&File"
#define MENU_OPEN "&Open...\tCtrl+O"
#define MENU_NEXTFILE "Next File\tCtrl+N"
#define MENU_OPENV56VOL "Open V56 from Volume..."
#define MENU_OPENP56VOL "Open P56 from Volume..."
#define MENU_SAVE "&Save"
#define MENU_SAVEAS "S&ave as...\tCtrl+S"
#define MENU_QUIT "&Quit\tCtrl+Q"

#define MENU_COLORS "Colors"
#define MENU_SHOWTABLE "Show Table"
#define MENU_IMPORTPAL "Import Palette..."
#define MENU_EXPORTPAL "Export Palette..."

#define MENU_IMAGE "&Image"
#define MENU_IMPORTBMP "&Import BMP...\tCtrl+I"
#define MENU_EXPORTBMP "&Export BMP...\tCtrl+E"
#define MENU_INFO "&Info"
#define MENU_CHANGEFRAMESIZE "&Change Cell Position..."
#define MENU_PROPERTIES "&Properties..."
#define MENU_LINKPOINTS "&Link Points..."

#define MENU_MAGNIFICATION "Magnification"
#define MENU_NORMAL "Normal\tCtrl+1"
#define MENU_PRIORITYBARS "Show Priority Bars"

#define MENU_GO "&Go"
#define MENU_PREVCELL "&Previous Cell\t<-"
#define MENU_NEXTCELL "&Next Cell\t->"
#define MENU_PREVLOOP "P&revious Loop\tUpArrow"
#define MENU_NEXTLOOP "N&ext Loop\tDownArrow"

#define MENU_MANUAL "&TraduSCI Manual..."
#define MENU_ABOUT "&About..."

    
    
#define ERR_TITLE "Error"
#define ERR_CANTLOADFILE "Sorry, this file can't be loaded."
#define ERR_FILEMOVED "The file does not exists, it has been moved or deleted."
#define ERR_CANTSAVECHANGES "Sorry, file changes cannot be saved. Try again saving on a new file."
#define ERR_CANTSAVE "Sorry, the new file cannot be saved."
#define ERR_CANTEXPORTBMP "The Bitmap image cannot be exported."
#define ERR_INVALIDBMP "The Bitmap file is corrupted."
#define ERR_INVALIDCBITBMP "The Bitmap file must be a 256 colors one and its color table must be the same as the original one."
#define ERR_INVALIDCOMPBMP "This program can't read compressed Bitmap. Please save your image as uncompressed from your imaging program and try again."
#define ERR_INVALIDSIZEBMP "The Bitmap file size is different from the expected value."
#define WARN_DIFFERENTDIM "The selected image file has different dimensions compared to the original picture, and it might not be displayed correctly in the game. Continue anyway?"
#define WARN_DIFFERENTPAL "The selected image has a different color table than the original one. Do you to import the palette from the incoming file?"
#define ERR_DIFFERENTPALBIS "The selected image has a different color table than the original one. Please revert back to the original palette using your painting program."
#define ERR_REMAPNOTIMPLEMENTEDYET "Remapping non yet implemented!!!!" 

#define ERR_WRONGHEADER	"The file header is of an unsupported format or damaged."
#define ERR_WRONGLOOPRECSIZE "The size of Loops is not correct."
#define ERR_WRONGCELLRECSIZE "The Cells format of this file is not supported."
#define ERR_WRONGPALETTELOC	"The color table is not located where the files directs to."
#define ERR_CANTLOADPALETTE "The color table can't be loaded."
#define ERR_CANTEXPORTPALETTE "The color table can't be saved to disk."

#define ERR_UNKNOWNGAME "The selected file seems to belong to a game that I don't own. Please contact me so that I can add support for that. (VersionTag = 0x%X)"
#define ERR_MESSAGEFROMAUTHOR "Message from Enrico Rolfi (Endroz)"

#define ERR_CANTLOADDLL "Couldn't load SCIdump.dll! This program will crash if you will try to load a Volume file."

#define WARN_ATTENTION "Warning!"
#define WARN_OVERWRITE "By saving changes, the original file will be irreversibly replaced. Continue anyway?"
#define WARN_UNSAVEDCHANGES "Do you want to save changes to the current file before continuing?"
#define WARN_LINKS "There are some LINKS structures inside this file, which are not supported by this version of the program. Keep in mind that by saving the file, these structures will be discarded and the file might not work with the game."
#define WARN_MISSINGPALETTE "There is no color table in this file, therefore images will not be displayed correctly. Please load an External palette file."

#define MANUAL_PATH "Manual\\instructions.html"

//#define WIN_FILEDESCRIPTION "Program to translate SCI1.1/SCI32 games.\0"
#define WIN_LEGALCOPYRIGHT "\251 Enrico Rolfi (Endroz), 2004-2021\nDhel, 2022\0"
//#define WIN_LEGALTRADEMARKS "SCI (Sierra Creative Interpreter) is a registered trademark of Sierra On-Line, all rights reserved.\0"

//Dhel
#define MODIFY_PROPERTIES "Manual\\instructions.html"



