/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  Spanish language strings
 *
 */
 
#define INTERFACE_OPENFILEFILTER "Archivos de imagen SCI (*.p56, *.v56)\0*.p56;*.v56\0Archivos de fondos SCI (*.p56)\0*.p56\0Archivos de imagen dinámica SCI (*.v56)\0*.v56\0Todos los archivos (*.*)\0*.*\0\0"
#define INTERFACE_SAVEFILEFILTERP56 "Archivos de fondos SCI (*.p56)\0*.p56\0\0"
#define INTERFACE_SAVEFILEFILTERV56 "Archivos de imagen dinámica SCI (*.v56)\0*.v56\0\0"
#define INTERFACE_BMPFILTER "Mapa de Bits (*.bmp)\0*.bmp\0Todos los archivos (*.*)\0*.*\0\0"
#define INTERFACE_PALFILTER "Archivos de paleta SCI (*.pal)\0*.pal\0Todos los archivos (*.*)\0*.*\0\0"
#define INTERFACE_PALINFILTER "Archivos de paleta SCI (*.pal)\0*.pal\0Mapa de Bits (*.bmp)\0*.bmp\0\0"

#define INTERFACE_ABOUTTITLE "Acerca de..."

#define INTERFACE_PROPERTIES "Propiedades"
#define INTERFACE_P56PROPSTR "%20c   -> Material global%20c\nCeldas: %d\n%sComprimido\nResolución: %s\nTamaño registrado de la celda: %d\n"
#define INTERFACE_P56CELLPROPSTR "\n%20c   -> Celda Elegida %d%20c\n\nDimensión: %d x %d\nPosición: %d,%d\nColor de transparencia: %d\nCompresión: %d\nMarcas: %X\nZ prioridad: %d\nxyPos: %d,%d\n"
#define INTERFACE_NOTSTR "No "
#define INTERFACE_SEEVIEWRESSTR " (información en Ver Resolución)"
#define INTERFACE_PROPVIEWSTR "%20c   -> Material global%20c\nBucles: %d\nStrip View: %d\n%sComprimido\nVer Resolución: %s\nCeldas totales: %d\nTamaño registrado del bucle: %d\nTamaño registrado de la celda: %d\nResolución: %s\n\n%20c   -> Bucle elegido %d%20c\nCeldas: %d\nEn base al bucle: %d\n%sReflejos\nCirculo: %d\nBucle inicial: %d\nBucle final: %d\nRepeticiones: %d\nTamaño del Paso: %d\n"
#define INTERFACE_VIEWCELLPROPSTR "\n%20c   -> Celda elegida %d%20c\n\nDimensión: %d x %d\nPosición: %d,%d\nColor de transparencia: %d\nCompresión: %d\nMarcas: %X\n"
#define INTERFACE_VECTORSIZESTR "Tamaño de los vectores: "
#define INTERFACE_PRIORITYSTR   "\nPrioridades: %d\nRecuento de lineas prioritarias: %d\n"
#define INTERFACE_LINKCOUNTSTR  "Recuento de Links: %d"

#define INTERFACE_SKIPCOLORSTR "Color de transparencia %d"
#define INTERFACE_CELLSSTR "Celda %d de %d"
#define INTERFACE_LOOPSSTR "Bucle %d de %d"
#define INTERFACE_MIRROREDSTR "Versión reflejada del bucle %d"

#define INTERFACE_CHANGEFRAMESIZE "Cambiar Ubicación de la Celda..."
#define INTERFACE_CANCEL	"Cancelar"
#define INTERFACE_LEFT		"Izquierda"
#define INTERFACE_TOP		"Alto"
#define INTERFACE_WIDTH		"Amplitud"
#define INTERFACE_HEIGHT	"Altura"

#define INTERFACE_CHANGEDSTR "Cambiado"

#define INTERFACE_MISSINGCOLORSSTR "Colores perdidos"
#define INTERFACE_LOCKEDCOLORSSTR "Colores no mapeables"
#define INTERFACE_MISSINGPALETTE "¡La paleta está desaparecida!"

#define INTERFACE_SEARCHTITLE "Resultados de la búsqueda"
#define INTERFACE_ENDOFFILESSTR "No hay más archivos después. La búsqueda continuará desde el primer archivos de este directorio."
#define INTERFACE_INVALIDSEARCHHANDLE "La búsqueda no puede continuar, el archivo podría haber sido movido o eliminado."

#define INTERFACE_LICENSE "Este programa es de código abierto (Licencia GNU GPL) y puede ser libremente distribuido y modificado siempre y cuando permanezca como código abierto."
#define INTERFACE_UPDATES "\nEn memoria de Michele Del Bene (Micartu).\n\nActualizaciones en http://erolfi.wordpress.com\nPara problemas, sugerencias y otros escribid a: \n erolfi en gmail.com"
#define INTERFACE_NOTICE "El autor rechaza cualquier responsabilidad de los posibles daños causados por su uso.\n\nSCI (Sierra Creative Interpreter) es una marca registrada de Sierra On-Line que mantiene los derechos.  "


#define MENU_FILE "&Archivo"
#define MENU_OPEN "A&brir...\tCtrl+A"
#define MENU_NEXTFILE "Siguiente archivo\tCtrl+S"
#define MENU_OPENV56VOL "Abrir V56 del volumen..."
#define MENU_OPENP56VOL "Abrir P56 del volumen..."
#define MENU_SAVE "&Guardar\tCtrl+G"
#define MENU_SAVEAS "G&uardar cómo..."
#define MENU_QUIT "&Salir\tCtrl+S"

#define MENU_COLORS "Colores"
#define MENU_SHOWTABLE "Mostrar tabla"
#define MENU_IMPORTPAL "Importar paleta..."
#define MENU_EXPORTPAL "Exportar paleta..."

#define MENU_IMAGE "&Imagen"
#define MENU_IMPORTBMP "I&mportar BMP...\tCtrl+I"
#define MENU_EXPORTBMP "&Exportar BMP...\tCtrl+E"
#define MENU_PROPERTIES "&Propiedades"
#define MENU_CHANGEFRAMESIZE "&Cambiar Ubicación de la Celda..."

#define MENU_MAGNIFICATION "Ampliación"
#define MENU_NORMAL "Normal\tCtrl+1"
#define MENU_PRIORITYBARS "Mostrar barras prioritarias"

#define MENU_GO "&Navegación"
#define MENU_PREVCELL "Celda anterior\t<-"
#define MENU_NEXTCELL "Celda siguiente\t->"
#define MENU_PREVLOOP "Bucle anterior\tCursor arriba"
#define MENU_NEXTLOOP "Bucle siguiente\tCursor abajo"

#define MENU_MANUAL "Manual de &TraduSCI..."
#define MENU_ABOUT "Acerca de..."

    
    
#define ERR_TITLE "Error"
#define ERR_CANTLOADFILE "Lo siento, este archivo no puede ser cargado."
#define ERR_FILEMOVED "El archivo no existe, ha sido movido o eliminado."
#define ERR_CANTSAVECHANGES "Lo siento, el archivo no puede ser guardado. Intenta guardar en un archivo nuevo."
#define ERR_CANTSAVE "Lo siento, el nuevo archivo no puede ser guardado."
#define ERR_CANTEXPORTBMP "La imagen de Mapa de Bits no puede ser exportada."
#define ERR_INVALIDBMP "El archivo de Mapa de Bits está corrupto."
#define ERR_INVALIDCBITBMP "El archivo de Mapa de Bits debe tener 256 colores y su tabla de colores debe ser la misma que el original."
#define ERR_INVALIDCOMPBMP "Este programa no puede leer Mapas de Bits comprimidos. Por favor, guarda tu imagen sin comprimir con tu programa de diseño gráfico e inténtalo de nuevo."
#define ERR_INVALIDSIZEBMP "El tamaño del archivo de Mapa de Bits es diferente del valor esperado."
#define WARN_DIFFERENTDIM "El archivo de imagen tiene dimensiones diferentes comparado con la imagen original, y podría no ser mostrado corréctamente en el juego. ¿Continuar de todos modos?"
#define WARN_DIFFERENTPAL "La imagen elegida tiene una tabla de colores diferentes al original, pero podría ser ajustado con una acción no recomendada (también conocida como adivinar-colores). ¿Quieres realizar esta acción?"
#define ERR_DIFFERENTPALBIS "La imagen elegida tiene una tabla de colores diferentes al original. Por favor, usa la paleta original usando tu programa de diseño gráfico."
#define ERR_REMAPNOTIMPLEMENTEDYET "¡¡¡¡Remapear no está aún implementado!!!!" 

#define ERR_WRONGHEADER	"La cabecera del archivo tiene un formato no soportado o está dañado."
#define ERR_WRONGLOOPRECSIZE "El tamaño de los Bucles no es correcto."
#define ERR_WRONGCELLRECSIZE "El tamaño de las Celdas de este archivo no está soportado."
#define ERR_WRONGPALETTELOC	"La tabla de colores no está localizada donde los archivos se dirigen."
#define ERR_CANTLOADPALETTE "La tabla de colores no puede ser cargada."
#define ERR_CANTEXPORTPALETTE "La tabla de colores no puede ser guardada en disco."

#define ERR_UNKNOWNGAME "El archivo elegido parece pertenecer a un juego que no reconozco. Por favor, contacta conmigo para así poder darle soporte. (VersionTag = 0x%X)"
#define ERR_MESSAGEFROMAUTHOR "Mensaje de Enrico Rolfi (Endroz)"

#define ERR_CANTLOADDLL "¡No se puede cargar SCIdump.dll! Este programa fallará si intentas cargar un archivo de Volumen."

#define WARN_ATTENTION "¡Aviso!"
#define WARN_OVERWRITE "Al guardar los cambios, el archivo original será irreversiblemente reemplazado. ¿Continuar de todos modos?"
#define WARN_UNSAVEDCHANGES "¿Quieres guardar los cambios del archivo actual antes de continuar?"
#define WARN_LINKS "Hay algunas estructuras de ENLACES dentro del archivo, las cuales no son soportadas por esta versión del programa. Ten en mente que al guardar el archivo, esas estructuras serán excluídas y el archivo podría no funcionar con el juego."
#define WARN_MISSINGPALETTE "No hay tabla de colores en este archivo, y las imágenes no se mostrarán corréctamente. Por favor, carga un archivo de paleta externo."

#define MANUAL_PATH "Manual\\instrucciones.html"

//#define WIN_FILEDESCRIPTION "Programa para traducir juegos SCI1.1/SCI32.\0"
#define WIN_LEGALCOPYRIGHT "\251 Enrico Rolfi (Endroz), 2004-2021. Traducción al Español de SkaZZ.\0"
//#define WIN_LEGALTRADEMARKS "SCI (Sierra Creative Interpreter) es una marca registrada de Sierra On-Line que mantiene los derechos.\0"


