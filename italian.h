/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  Italian language strings
 *
 */

#define INTERFACE_OPENFILEFILTER "Documenti immagine SCI (*.p56, *.v56)\0*.p56;*.v56\0Documenti SCI Picture (*.p56)\0*.p56\0Documenti SCI View (*.v56)\0*.v56\0Tutti i tipi (*.*)\0*.*\0\0"
#define INTERFACE_SAVEFILEFILTERP56 "Documenti SCI Picture (*.p56)\0*.p56\0\0"
#define INTERFACE_SAVEFILEFILTERV56 "Documenti SCI View (*.v56)\0*.v56\0\0"
#define INTERFACE_BMPFILTER "Documento Bitmap (*.bmp)\0*.bmp\0Tutti i tipi (*.*)\0*.*\0\0"
#define INTERFACE_PALFILTER "Documenti SCI Palette (*.pal)\0*.pal\0Tutti i tipi (*.*)\0*.*\0\0"
#define INTERFACE_PALINFILTER "Documenti SCI Palette (*.pal)\0*.pal\0Documento Bitmap (*.bmp)\0*.bmp\0\0"

#define INTERFACE_ABOUTTITLE "Informazioni"

#define INTERFACE_PROPERTIES "Propriet�"
#define INTERFACE_P56PROPSTR "%20c   -> Informazioni Generali%20c\nCelle: %d\n%sCompresso\nRisoluzione: %s\nDimensione Celle: %d\n"
#define INTERFACE_P56CELLPROPSTR "\n%20c   -> Cella Selezionata %d%20c\n\nDimensioni: %d x %d\nPosizione: %d,%d\nColore Trasparente: %d\nCompressione: %d\nAttributi: %X\nPriorit� asse Z: %d\nxyPos: %d,%d\n"
#define INTERFACE_NOTSTR "Non "
#define INTERFACE_SEEVIEWRESSTR " (vedi Risoluzione View)"
#define INTERFACE_PROPVIEWSTR "%20c   -> Informazioni Generali%20c\nCicli: %d\nStrip View: %d\n%sCompresso\nRisoluzione View: %s\nCelle Complessive: %d\nDimensione Cicli: %d\nDimensione Celle: %d\nRisoluzione: %s\n\n%20c   -> Ciclo Selezionato %d%20c\nCelle: %d\nBasato sul Ciclo: %d\n%sCapovolto\nCiclo Cont.: %d\nCella inizio: %d\nCella fine: %d\nRipetizioni: %d\nDim. Passo: %d\n"
#define INTERFACE_VIEWCELLPROPSTR "\n%20c   -> Cella Selezionata %d%20c\n\nDimensioni: %d x %d\nPosizione: %d,%d\nColore Trasparente: %d\nCompressione: %d\nAttributi: %X\n"
#define INTERFACE_VECTORSIZESTR "Dimensione Vettori: "
#define INTERFACE_PRIORITYSTR   "\nLinee di Priorit�: %d\nNumero di Linee: %d\n"
#define INTERFACE_LINKCOUNTSTR  "Numero di Links: %d"

#define INTERFACE_SKIPCOLORSTR "Colore Trasparente %d"
#define INTERFACE_CELLSSTR "Cella %d di %d"
#define INTERFACE_LOOPSSTR "Ciclo %d di %d"
#define INTERFACE_MIRROREDSTR "Copia capovolta del Ciclo %d"

#define INTERFACE_CHANGEFRAMESIZE "Cambia Posizione Cella..."
#define INTERFACE_CANCEL	"Annulla"
#define INTERFACE_LEFT		"Sinistra"
#define INTERFACE_TOP		"Alto"
#define INTERFACE_WIDTH		"Larghezza"
#define INTERFACE_HEIGHT	"Altezza"

#define INTERFACE_CHANGEDSTR "Modificata"

#define INTERFACE_MISSINGCOLORSSTR "Colori mancanti"
#define INTERFACE_LOCKEDCOLORSSTR "Colori non sostituibili"
#define INTERFACE_MISSINGPALETTE "Tavola dei Colori mancante!"

#define INTERFACE_SEARCHTITLE "Stato della Ricerca"
#define INTERFACE_ENDOFFILESSTR "Non ci sono altri file successivi. La ricerca proseguir� dal primo file della cartella."
#define INTERFACE_INVALIDSEARCHHANDLE "La ricerca non pu� essere proseguita, il file potrebbe essere stato spostato o rimosso."

#define INTERFACE_LICENSE "Questo programma � open source (licenza GNU GPL), pu� essere distribuito e modificato purch� resti open source.\n"
#define INTERFACE_UPDATES "In memoria di Michele Del Bene (Micartu).\n\nAggiornamenti su http://erolfi.wordpress.com\n\nPer problemi, suggerimenti o altro scrivimi a:\nerolfi su gmail.com\n"
#define INTERFACE_NOTICE "L'autore declina da ogni responsabilit� circa eventuali danni causati dal suo utilizzo.\n\nSCI (Sierra Creative Interpreter) � un marchio registrato di Sierra On-Line che ne detiene i diritti.  "                

#define MENU_FILE "&File"
#define MENU_OPEN "&Carica...\tCtrl+O"
#define MENU_NEXTFILE "Prossimo File\tCtrl+N"
#define MENU_OPENV56VOL "Carica V56 da Volume..."
#define MENU_OPENP56VOL "Carica P56 da Volume..."
#define MENU_SAVE "&Salva"
#define MENU_SAVEAS "S&alva come...\tCtrl+S"
#define MENU_QUIT "&Esci\tCtrl+Q"

#define MENU_COLORS "Colori"
#define MENU_SHOWTABLE "Mostra Tavolozza"
#define MENU_IMPORTPAL "Importa Colori..."
#define MENU_EXPORTPAL "Esporta Colori..."

#define MENU_IMAGE "&Immagine"
#define MENU_IMPORTBMP "&Importa BMP...\tCtrl+I"
#define MENU_EXPORTBMP "&Esporta BMP...\tCtrl+E"
#define MENU_INFO "&Propriet�"
#define MENU_CHANGEFRAMESIZE "&Cambia Posizione Cella..."

#define MENU_MAGNIFICATION "Ingrandimento"
#define MENU_NORMAL "Normale\tCtrl+1"
#define MENU_PRIORITYBARS "Mostra Linee di Priorit�"

#define MENU_GO "&Vai"
#define MENU_PREVCELL "Cella &Precedente\t<-"
#define MENU_NEXTCELL "&Next Cell\t->"
#define MENU_PREVLOOP "&Ciclo Precedente\tFrecciaSu"
#define MENU_NEXTLOOP "C&iclo Successivo\tFrecciaGi�"

#define MENU_MANUAL "&Manuale di TraduSCI..."
#define MENU_ABOUT "&Informazioni..."


#define ERR_TITLE "Errore"
#define ERR_CANTLOADFILE "Non posso caricare il file."
#define ERR_FILEMOVED "Il file non esiste, � stato spostato o rimosso."
#define ERR_CANTSAVECHANGES "Non posso salvare le modifiche al file. Prova a salvare su un nuovo file."
#define ERR_CANTSAVE "Non posso salvare il nuovo file."
#define ERR_CANTEXPORTBMP "Non posso esportare l'immagine Bitmap."
#define ERR_INVALIDBMP "File Bitmap non valido."
#define ERR_INVALIDCBITBMP "Il file Bitmap deve essere a 256 colori e con una tavolozza di colori analoga all'originale."
#define ERR_INVALIDCOMPBMP "I file Bitmap compressi non sono supportati, salvare il file nel formato non compresso e riprovare."
#define ERR_INVALIDSIZEBMP "Il file Bitmap ha una grandezza diversa da quella attesa."
#define WARN_DIFFERENTDIM "L'immagine che si sta importando ha dimensioni geometriche differenti da quella originale, e potrebbe non essere visualizzata correttamente nel gioco. Continuare?"
#define WARN_DIFFERENTPAL "L'immagine che si sta importando ha una tavolozza di colori differente dall'originale, e si cercher� di adattarla con un operazione non raccomandabile. Procedere?"
#define ERR_DIFFERENTPALBIS "L'immagine che si sta importando ha una tavolozza di colori differente dall'originale, modificare l'immagine da importare in un programma di disegno affinch� abbia gli stessi colori."
#define ERR_REMAPNOTIMPLEMENTEDYET "Remapping non ancora implementato!!!!"                
                
#define ERR_WRONGHEADER	"Il formato dell'intestazione del file non � corretto o supportato."
#define ERR_WRONGLOOPRECSIZE "Il file ha una dimensione dei Cicli non standard."
#define ERR_WRONGCELLRECSIZE "Il file ha una dimensione delle Celle non supportata."
#define ERR_WRONGPALETTELOC	"La tavola dei colori non si trova nella posizione indicata nel file."
#define ERR_CANTLOADPALETTE "La tavola dei colori non pu� essere caricata."
#define ERR_CANTEXPORTPALETTE "La tavola dei colori non pu� essere salvata su disco."

#define ERR_UNKNOWNGAME "Il file selezionato sembra appartenere ad un gioco che non posseggo. Per favore, contattami cos� potro aggiungerne il supporto. (VersionTag = 0x%X)"
#define ERR_MESSAGEFROMAUTHOR "Messaggio da Enrico Rolfi (Endroz)"

#define ERR_CANTLOADDLL "Impossibile caricare la libreria SCIdump.DLL! Il programma si bloccher� qualora si tentasse di caricare un Volume."

#define WARN_ATTENTION "Attenzione!"
#define WARN_OVERWRITE "Salvando le modifiche il file originale verr� modificato irreversibilmente. Continuare?"
#define WARN_UNSAVEDCHANGES "Salvare le modifiche al file attuale prima di continuare?"
#define WARN_LINKS "Questo file contiene delle strutture LINKS che non sono supportate da questa versione del programma. Si tenga presente che salvando il file queste strutture non verranno ricostruite e il gioco potrebbe non funzionare correttamente."
#define WARN_MISSINGPALETTE "Non c'� una tavola dei colori in questo file, quindi le immagini non saranno visualizzate correttamente. Caricare un file di colori esterno per risolvere il problema."

#define MANUAL_PATH "Manuale\\istruzioni.html"

//#define WIN_FILEDESCRIPTION "Programma per tradurre giochi SCI1.1/SCI32.\0"
#define WIN_LEGALCOPYRIGHT "\251 Enrico Rolfi (Endroz), 2004-2021.\0"
//#define WIN_LEGALTRADEMARKS "SCI (Sierra Creative Interpreter) � un marchio registrato di Sierra On-Line che ne detiene i diritti.\0"

