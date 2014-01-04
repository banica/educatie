/*------------------------------------------------------------------------------
   SYSMETS.H -- Structura de afisare a metricilor de sistem
------------------------------------------------------------------------------*/

#define NUMLINES (sizeof (sysmetrics)/sizeof (sysmetrics [0]))

typedef struct {
  int	nIndex;
  char*	szLabel;
  char*	szDesc;
} SYSMETRICS;

SYSMETRICS sysmetrics [] =
  {{SM_CXSCREEN,    "SM_CXSCREEN", 		"Dimensiunea orizontala a ecranului in pixeli"},
   {SM_CYSCREEN,    "SM_CYSCREEN", 		"Dimensiunea verticala a ecranului in pixeli"},
   {SM_CXVSCROLL, 	"SM_CXVSCROLL", 	"Latimea scroll bar-ului vertical"},
   {SM_CYHSCROLL, 	"SM_CYHSCROLL", 	"Inaltimea scroll bar-ului orizontal"},
   {SM_CYCAPTION, 	"SM_CYCAPTION", 	"Inaltimea caption bar-ului"},
   {SM_CXBORDER, 	"SM_CXBORDER", 		"Latimea marginii ferestrei"},
   {SM_CYBORDER, 	"SM_CYBORDER", 		"Inaltimea marginii ferestrei"},
   {SM_CXDLGFRAME, 	"SM_CXDLGFRAME", 	"Latimea marginii ferestrei de dialog"},
   {SM_CYDLGFRAME, 	"SM_CYDLGFRAME", 	"Inaltimea marginii ferestrei de dialog"},
   {SM_CYVTHUMB, 	"SM_CYVTHUMB", 		"Inaltimea butonului scroll bar-ului vertical"},
   {SM_CXHTHUMB, 	"SM_CXHTHUMB", 		"Latimea butonului scroll bar-ului orizontal"},
   {SM_CXICON, 		"SM_CXICON", 		"Latimea icon-ului"},
   {SM_CYICON, 		"SM_CYICON", 		"Inaltimea icon-ului"},
   {SM_CXCURSOR, 	"SM_CXCURSOR", 		"Latimea cursorului de mouse"},
   {SM_CYCURSOR, 	"SM_CYCURSOR", 		"Inaltimea cursorului de mouse"},
   {SM_CYMENU, 		"SM_CYMENU", 		"Inaltimea menu bar-ului asociat ferestrei"},
   {SM_CXFULLSCREEN,"SM_CXFULLSCREEN", 	"Latimea zonei client a ferestrei maximizate"},
   {SM_CYFULLSCREEN,"SM_CYFULLSCREEN", 	"Inaltimea zonei client a ferestrei maximizate"},
   {SM_MOUSEPRESENT,"SM_MOUSEPRESENT", 	"Flag-ul de prezenta a mouse-ului"},
   {SM_CYVSCROLL, 	"SM_CYVSCROLL", 	"Inaltimea sagetii scroll bar-ului vertical"},
   {SM_CXHSCROLL, 	"SM_CXHSCROLL", 	"Latimea sagetii scroll bar-ului orizontal"},
   {SM_DEBUG, 		"SM_DEBUG", 		"Flagul de versiune de debug"},
   {SM_SWAPBUTTON, 	"SM_SWAPBUTTON", 	"Flagul de inversare a butoanelor de mouse"},
   {SM_RESERVED1, 	"SM_RESERVED1", 	"Rezervat"},
   {SM_RESERVED2, 	"SM_RESERVED2", 	"Rezervat"},
   {SM_RESERVED3, 	"SM_RESERVED3", 	"Rezervat"},
   {SM_RESERVED4, 	"SM_RESERVED4", 	"Rezervat"},
   {SM_CXMIN, 		"SM_CXMIN", 		"Dimensiunea orizontala minima a unei ferestre"},
   {SM_CYMIN, 		"SM_CYMIN", 		"Dimensiunea verticala minima a unei ferestre"},
   {SM_CXSIZE, 		"SM_CXSIZE", 		"Latimea butonului de maximizare / minimizare"},
   {SM_CYSIZE, 		"SM_CYSIZE", 		"Inaltimea butonului de maximizare / minimizare"},
   {SM_CXFRAME, 	"SM_CXFRAME", 		"Latimea marginii de dimensionare a ferestrei"},
   {SM_CYFRAME, 	"SM_CYFRAME", 		"Inaltimea marginii de dimensionare a ferestrei"},
   {SM_CXMINTRACK, 	"SM_CXMINTRACK", 	"Latimea de tracking a ferestrei"},
   {SM_CYMINTRACK, 	"SM_CYMINTRACK", 	"Inaltimea de tracking a ferestrei"},
   {SM_CMETRICS,	"SM_CMETRICS", 		"Numarul de valori ale metricilor de sistem"}
  };

