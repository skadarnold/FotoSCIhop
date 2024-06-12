# FotoSCIhop
SCI32 / SCI1.1 Pic and View editor

## About
FotoSCIhop is the only modern application that I have found which is capable of editing SCI32 compatible view and pic files. Over the several years I have been expanding and restructuring FotoSCIhop too allow additional editing other than it's original bitmap / palette importing. 

This version of FotoSCIhop is in public beta testing status. While most things should be stable and working, there are many things that are not ready for mainstream use. There are few safe guards in place when modifying file properties which could break them. Use at your own risk. Over time I plan to improve these things as needed. 

## Installation
It is recommended that you download and install FotoSCIhop bundled through TraduSCI from here https://drive.google.com/file/d/1sf6rbpnvArRtQ0GmeKKGe-xbdP9FeVv6/view?usp=sharing. This will give you all of the additional content and documentation usually included with FotoSCIhop. Then replace FotoSCIhop.exe with your choice from the github release section. 

## Compiling
Use Visual Studio and open immagina.sln. 

### Features that have been added
- All properties per cell can be modified
- All link points can be modified
- Cells can be added and removed (alpha)
- Ini file to change core properties of the program (game resolution, magnification multiplier, etc)
- Link Points are overlayed in multi-color formatting to help distinguish different points
- Priority line overlay for cell positioning
- CLI option for mass file editing

Much of the original code has been redesigned at it's core to allow more flexibility and to better match the original structuring of SCI32 view and pic files. 

### Features I hope to add
- Palette editing and shifting
- Image conversion / color quantization when importing
- Better cell / loop management (copy paste, new from base)
- Better multi cell pic designer (drag and drop)
- Better property editing (drag and drop)
- Better link point editing (drag and drop)

Eventually I would also like to continue to support multiple languages as was the original intention of the author, Enrico. 

### Disclaimer
The author / authors declines from every responsibility on possible damages caused by its use.

## Original Credits 
All credit and thanks goes to the original author of FotoSCIhop, Enrico Rolfi (Endroz). The original program and source code can be found at http://erolfi.wordpress.com. 

In Memory of Michele Del Bene (Micartu).

SCI (Sierra Creative Interpreter) is a trademark of Sierra On-line that holds copyrights on it.

