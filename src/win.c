#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <stdarg.h>
#include <string.h>
#include <dos.h>
#include <direct.h>
#include <ctype.h>
#include <malloc.h>
#include <bios.h>
#include <io.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>

#include "kk.h"
#include "win.h"
#include "idf.h"

int *TailleX;


void ErrWin95(void)
{
int x,y;
char c=0;

while (c!=27) {
	  for (x=0;x<(*TailleX);x++)
          for (y=0;y<Cfg->TailleY;y++)  {
			  AffChr(x,y,rand()&255);
			  AffCol(x,y,26 + (rand()&1));
			  }
	  PrintAt(26,11,"*************************");
	  PrintAt(26,12,"* WINDOWS 95 KEYBOARD ! *");
	  PrintAt(26,13,"*************************");
      if (kbhit()) c=getch();
	  }

AfficheTout();
}

int InfoIDF(struct fenetre *Fen)
{
struct file *F;
struct info Info;

F=Fen->F[Fen->pcur];

if ( (F->attrib & _A_SUBDIR)==_A_SUBDIR)    {
   PrintAt(0,0,"%-40s%-40s","Directory",F->name);
   return 0;
   }

strcpy(Info.path,DFen->path);
if (Info.path[strlen(Info.path)-1]!='\\') strcat(Info.path,"\\");
strcat(Info.path,F->name);

Traitefic(F->name,&Info);


// sprintf(Info.path,"%s%s",drive,dir);

PrintAt(0,0,"%-40s%-40s",Info.format,Info.fullname);

return Info.numero;
}

void ClearNor(struct fenetre *Fen)
{
int i;
int x,y;
int yl;

char a;

a=Cfg->Tfont[0];

ColWin(Fen->x,Fen->y,Fen->x+Fen->xl,Fen->y+Fen->yl,7*16+6);


// Couleur uniquement pour fentype=1,2 ou 3 (le 4 le fait 2 fois !)
for(x=Fen->x;x<=Fen->x+Fen->xl;x++)
    AffCol(x,Fen->y,10*16+1);
for(y=Fen->y;y<=Fen->y+Fen->yl;y++)
    AffCol(Fen->x,y,10*16+1);

for(x=Fen->x+1;x<=Fen->x+Fen->xl;x++)
    AffCol(x,Fen->y+Fen->yl,10*16+3);
for(y=Fen->y+1;y<Fen->y+Fen->yl;y++)
    AffCol(Fen->x+Fen->xl,y,10*16+3);


x=Fen->x;
y=Fen->y;

yl=(Fen->yl)+(Fen->y);

switch (Cfg->fentype)  {
    case 1:
        Cfg->Tfont[0]=179;
        Fen->x2=Fen->x-1;
        Fen->y2=Fen->y-1;
        Fen->xl2=Fen->xl;
        Fen->yl2=Fen->yl-4;
        Fen->x3=Fen->x+2;
        Fen->y3=Fen->y+Fen->yl-1;

        PrintAt(x,y     ,"浜様様様様様用様様様様様冤様様様用様様融");
        PrintAt(x,y+1,   "�    Name    �    Size  �  Date  � Time�");
        for (i=2;i<yl-3;i++)
           PrintAt(x,y+i,"�            �          �        �     �");
        PrintAt(x,y+yl-3,"把陳陳陳陳陳珍陳陳陳陳陳祖陳陳陳珍陳陳超");
        PrintAt(x,y+yl-2,"�                                      �");
        PrintAt(x,y+yl-1,"藩様様様様様様様様様様様様様様様様様様夕");

        break;
    case 2:
        Cfg->Tfont[0]=179;
        Fen->x2=Fen->x-1;
        Fen->y2=Fen->y-2;
        Fen->xl2=(Fen->xl);
        Fen->yl2=Fen->yl-3;
        Fen->x3=Fen->x+2;
        Fen->y3=Fen->y+Fen->yl-1;

        ColLin(x,y,40,Cfg->bkcol);
        PrintAt(x,y,     "     Name    �    Size  �  Date  � Time ");
        for (i=1;i<yl-3;i++)
           PrintAt(x,y+i,"�            �          �        �     �");
        PrintAt(x,y+yl-3,"桎烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝炳");
        PrintAt(x,y+yl-2,"�                                      �");
        PrintAt(x,y+yl-1,"烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝烝");
        break;
    case 3:
        Cfg->Tfont[0]=179;
        Fen->x2=Fen->x-1;
        Fen->y2=Fen->y-2;
        Fen->xl2=Fen->xl;
        Fen->yl2=Fen->yl-3;
        Fen->x3=Fen->x+2;
        Fen->y3=Fen->y+Fen->yl-1;

        PrintAt(x,y     ,"敖�艇Name�艇賃�艇Size�艇堕�Date�賃Time��");
        for (i=1;i<yl-3;i++)
           PrintAt(x,y+i,"�            �          �        �     �");
        PrintAt(x,y+yl-3,"楽陳陳陳陳陳珍陳陳陳陳陳祖陳陳陳珍陳陳審");
        PrintAt(x,y+yl-2,"�                                      �");
        PrintAt(x,y+yl-1,"誓陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳捶");
        break;
    case 4:
        Fen->x2=Fen->x-1;
        Fen->y2=Fen->y-1;
        Fen->xl2=Fen->xl;
        Fen->yl2=Fen->yl-4;
        Fen->x3=Fen->x+2;
        Fen->y3=Fen->y+Fen->yl-1;

        ColLin(x+ 5,y+1,4,7*16+5);
        ColLin(x+18,y+1,4,7*16+5);
        ColLin(x+27,y+1,4,7*16+5);
        ColLin(x+34,y+1,4,7*16+5);
        ChrLin(x+1,y+yl-2,38,32);

        PrintAt(x+1,y+1,   "    Name    %c    Size  %c  Date  %cTime ",a,a,a);
        for (i=2;i<yl-3;i++)
           PrintAt(x+1,y+i,   "            %c          %c        %c     ",a,a,a);

        WinLine(x+1,y+yl-3,38,1);
        WinCadre(x,y,x+39,y+yl-1,1);

        break;
    }
}


void FenNor(struct fenetre *Fen)
{
int j,n;  // Compteur
int date,time;
char chaine[255];
char temp[16];
char nom[13],ext[4];

short i;

char a;                 // Separator Character

int x1,y1;
int x=2,y=3;

if (Fen->init==1)
    ClearNor(Fen);



if (Fen->scur>Fen->pcur) Fen->scur=Fen->pcur;

while (Fen->pcur<0)
    {
    Fen->scur++;
    Fen->pcur++;
    }

while (Fen->pcur>=Fen->nbrfic)
    {
    Fen->pcur--;
    Fen->scur--;
    }

if (Fen->scur<0)
    Fen->scur=0;

if (Fen->scur>Fen->yl2-1)
    Fen->scur=Fen->yl2-1;

a=Cfg->Tfont[0];

x1=Fen->x2;
y1=Fen->y2;

n=(Fen->pcur)-(Fen->scur);			  // premier

InfoSelect(Fen);

for (i=0;(i<Fen->yl2) & (n<Fen->nbrfic);i++,n++,y++)
    {
// ------------------ Line Activity ------------------------------------
    if ((Fen->actif==1) & (n==(Fen->pcur)) )
        {
        if (Fen->F[n]->select==0)
            ColLin(x+x1,y+y1,38,1*16+6);
            else
            ColLin(x+x1,y+y1,38,1*16+5);
        }
        else
        {
        if (Fen->F[n]->select==0)
            ColLin(x+x1,y+y1,38,7*16+6);
            else
            ColLin(x+x1,y+y1,38,7*16+5);
        }

// ---------------------------------------------------------------------
    date=Fen->F[n]->date;
    time=Fen->F[n]->time;

    strcpy(nom,Fen->F[n]->name);
    if ((Fen->F[n]->attrib& _A_SUBDIR)!=_A_SUBDIR)
        strlwr(nom);


    ext[0]=0;
    j=0;

    if (nom[0]!='.')
        while(nom[j]!=0)
            {
            if (nom[j]=='.')
                {
                memcpy(ext,nom+j+1,4);
                ext[3]=0;
                nom[j]=0;
                break;
                }
            j++;
            }
    nom[8]=0;


    Int2Char((date>>9)+80,temp,2);

    sprintf(chaine,"%-8s %-3s%c%10s%c%02d/%02d/%2s%c%02d:%02d",
                      nom,ext,a,Long2Str(Fen->F[n]->size),a,
                     (date&31),(date>>5)&15,temp,a,
					 (time>>11)&31,(time>>5)&63
					 );

    if ((Fen->F[n]->attrib & _A_SUBDIR)==_A_SUBDIR)
        memcpy(chaine+13,"SUB--DIR",10);

    if ((Fen->F[n]->attrib & _A_VOLID)==_A_VOLID)
        sprintf(chaine,"%-8s%-3s %c##Vol-ID##%c%02d/%02d/%2s%c%02d:%02d",
                     nom,ext,a,a,
                     (date&31),(date>>5)&15,temp,a,
					 (time>>11)&31,(time>>5)&63
					 );

    if (nom[1]==':')
        sprintf(chaine,"%-8s    %c##Reload##%c        %c     ",nom,a,a,a);

    if (nom[0]=='.')
        {
        if (nom[1]!='.')
            memcpy(chaine+13," RELOAD ",10);
            else
        memcpy(chaine+13," UP-DIR ",10);
        }


    PrintAt(x+x1,y+y1,"%s",chaine);
    }

Fen->paff=Fen->pcur;
Fen->saff=Fen->scur;

if (Fen->FenTyp==3)
    FenInfo(Fen);   //  Affiche les infos sur les fichiers si type=3

Fen->init=0;
}


/********************************************
             For the FILE_ID.DIZ
 ********************************************/

void Makediz(struct info *Info,char *Buf)
{
struct dosdate_t Date;
char ligne[256];

_dos_getdate(&Date);


sprintf(ligne,"                                    \r\n");
strcpy(Buf,ligne);
sprintf(ligne,"      Ketchup Killers  (C) %4d     \r\n",Date.year);
strcat(Buf,ligne);
sprintf(ligne,"陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳\r\n");
strcat(Buf,ligne);

if (*Info->fullname!=0)  {
        ClearSpace(Info->fullname);
        Info->fullname[30]=0;

        if (strlen(Info->fullname)<=26)
                sprintf(ligne," Title: %27s \r\n",Info->fullname); //34
                else
                sprintf(ligne," T.:%31s \r\n",Info->fullname); //34
        strcat(Buf,ligne); }

if (*Info->format!=0) {
        sprintf(ligne," Type : %27s \r\n",Info->format); //34
        strcat(Buf,ligne); }

if (*Info->info!=0) {
        sprintf(ligne," %-14s : %17s \r\n",Info->Tinfo,Info->info); //34
        strcat(Buf,ligne); }

if (*Info->composer!=0) {
        sprintf(ligne," Composer: %24s \r\n",Info->composer); //34
        strcat(Buf,ligne); }

if (*Info->message[0]!=0) {
        short m;
        sprintf(ligne,"陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳陳\r\n");
        strcat(Buf,ligne);
        for (m=0;m<9;m++)
                {
                if (*Info->message[m]!=0)
                        {
                        sprintf(ligne,"%-36s\r\n",Info->message[m]); //36
                        strcat(Buf,ligne);
                        }
                }
        }

if (Info->taille!=0) {
        sprintf(ligne," True Size: %23ld \r\n",Info->taille);
        strcat(Buf,ligne); }
sprintf(ligne,"                                    \r\n");
strcat(Buf,ligne);

return;
}

void FenDIZ(struct fenetre *Fen)
{
char *Buf;
struct info Info;
struct fenetre *Fen2;
struct file *F;
int x,y,i;

Fen2=Fen->Fen2;
F=Fen2->F[Fen2->pcur];
if ( (F->attrib & _A_SUBDIR)==_A_SUBDIR) return;

WinCadre(Fen->x,Fen->y,Fen->x+Fen->xl,Fen->y+Fen->yl,1);

strcpy(Info.path,Fen2->path);
if (Info.path[strlen(Info.path)-1]!='\\') strcat(Info.path,"\\");
strcat(Info.path,F->name);

Traitefic(F->name,&Info);

Buf=malloc(4000);

Makediz(&Info,Buf);

ChrWin(Fen->x+1,Fen->y+1,Fen->x+Fen->xl-1,Fen->y+4,' ');
ColWin(Fen->x+1,Fen->y+1,Fen->x+Fen->xl-1,Fen->y+4,170);

x=Fen->x+2;
y=Fen->y+6;

i=0;
while (Buf[i]!=0)  {
	switch (Buf[i]) {
           case 10: x=Fen->x+2; break;
		   case 13: y++; break;
		   default: AffChr(x,y,Buf[i]); x++; break;
		   }
	i++;
	}

WinCadre(Fen->x+1,Fen->y+5,Fen->x+Fen->xl-1,y,2);
ColWin(Fen->x+2,Fen->y+6,Fen->x+Fen->xl-2,y-1,10*16+1);

ChrWin(Fen->x+1,y+1,Fen->x+Fen->xl-1,Fen->y+Fen->yl-1,' ');
ColWin(Fen->x+1,y+1,Fen->x+Fen->xl-1,Fen->y+Fen->yl-1,170);

free (Buf);

Fen->init=0;
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/

void ClearInfo(struct fenetre *Fen)
{
int i;
struct file *F;
struct info Info;
struct fenetre *Fen2;

SaveEcran();

Fen2=Fen->Fen2;

WinCadre(19,9,61,11,0);
ColWin(20,10,60,10,10*16+4);
ChrWin(20,10,60,10,32);

PrintAt(23,10,"Wait Please");

for (i=0;i<Fen->nbrfic;i++)
    {
    F=Fen->F[i];

    if (F->info==NULL)
        F->info=GetMem(41);

    if ( (F->attrib & _A_SUBDIR)==_A_SUBDIR)
        {
        sprintf(F->info,"%cDirectory",0);
        }
        else
        {
        strcpy(Info.path,Fen->path);
        if (Info.path[strlen(Info.path)-1]!='\\') strcat(Info.path,"\\");
        strcat(Info.path,F->name);

        Traitefic(F->name,&Info);
        strcpy(F->info+1,Info.format);
        F->info[0]=Info.Btype;
        }
    }

ChargeEcran();

WinCadre(Fen2->x,Fen2->y,Fen2->x+Fen2->xl,Fen2->y+Fen2->yl,1);

ChrWin(Fen2->x+1,Fen2->y+1,Fen2->x+Fen2->xl-1,Fen2->y+Fen2->yl-1,' ');
ColWin(Fen2->x+1,Fen2->y+1,Fen2->x+Fen2->xl-1,Fen2->y+Fen2->yl-1,7*16+6);

ChrLin(Fen2->x+1,Fen2->y+Fen2->yl-2,Fen2->xl-1,196);
PrintAt(Fen2->x+1,Fen2->y+Fen2->yl-1,"Use this at your own risk ;)");
}

void FenInfo(struct fenetre *Fen)
{
int n;  // Compteur
struct fenetre *Fen2;

short i;

char a;                 // Separator Character

int x1,y1;
int x=2,y=3;

Fen2=Fen->Fen2;

if (Fen->init==1)
    ClearInfo(Fen);

a=Cfg->Tfont[0];

x1=Fen2->x2;
y1=Fen2->y2;

n=(Fen->pcur)-(Fen->scur);            // premier

for (i=0;(i<Fen2->yl2) & (n<Fen->nbrfic);i++,n++,y++)
    {
// ------------------ Line Activity ------------------------------------
    if (n==(Fen->pcur))
        ColLin(x+x1,y+y1,38,1*16+5);
        else
        {
        if (Fen->F[n]->info!=NULL)
            switch(Fen->F[n]->info[0])
                {
                case 1:
                    ColLin(x+x1,y+y1,38,4*16+11);
                    break;
                case 2:
                    ColLin(x+x1,y+y1,38,4*16+1);
                    break;
                case 3:
                    ColLin(x+x1,y+y1,38,4*16+13);
                    break;
                case 4:
                    ColLin(x+x1,y+y1,38,3*16+11);
                    break;
                case 5:
                    ColLin(x+x1,y+y1,38,3*16+1);
                    break;
                case 6:
                    ColLin(x+x1,y+y1,38,3*16+13);
                    break;
                default:
                    ColLin(x+x1,y+y1,38,7*16+5);
                    break;
                }
            else
                ColLin(x+x1,y+y1,38,7*16+5);
        }

    if (Fen->F[n]->info!=NULL)
        PrintAt(x+x1,y+y1,"%-38s",Fen->F[n]->info+1);
    }
}

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/


/**********************************************
            Display about select
 **********************************************/


void InfoSelect(struct fenetre *Fen)
{
if (Fen->nbrsel==0)  {
   if (Fen->nbrfic==1)
      PrintAt(Fen->x3,Fen->y3,"%-10s bytes in one file         ",Long2Str(Fen->taillefic));
	  else
      PrintAt(Fen->x3,Fen->y3,"%-10s bytes in %3d files        ",Long2Str(Fen->taillefic),Fen->nbrfic);
   }
   else {
   if (Fen->nbrsel==1)
      PrintAt(Fen->x3,Fen->y3,"%-10s b. in one selected file   ",Long2Str(Fen->taillesel));
	  else
      PrintAt(Fen->x3,Fen->y3,"%-10s b. in %3d selected files  ",Long2Str(Fen->taillesel),Fen->nbrsel);
   }

}


//-----------------------------------------------------------------------------
// The KEY's menu
//-----------------------------------------------------------------------------
void CtrlMenu(void)
{
if (DFen->nbrfic==1)
    PrintAt(DFen->x3,DFen->y3,"%-10s bytes in one file         ",Long2Str(DFen->taillefic));
    else
    PrintAt(DFen->x3,DFen->y3,"%-10s bytes in %3d files        ",Long2Str(DFen->taillefic),DFen->nbrfic);
}

void ShiftMenu(void)
{
char chaine[37];
memcpy(chaine,DFen->path,37);
chaine[36]=0;
PrintAt(DFen->x3,DFen->y3,"%-36s",chaine);
}

void SetTaille(void)
{
TXTMode(Cfg->TailleY);
NoFlash();


switch (Cfg->TailleY)  {
   case 50:
        Font8x8();
        break;
   case 25:
   case 30:
        Font8x16();
        break;
   }
DFen->yl=(Cfg->TailleY)-4;
DFen->Fen2->yl=(Cfg->TailleY)-4;

AfficheTout();

LoadPal();

}



void AltMenu(void)
{
PrintAt(DFen->x3,DFen->y3,"[ Hello World !!!                  ]");
}

void MenuBar(char c)
{
static char bar[4][60]=
   { " Help  ----  View  Edit  Copy  Move  MDir Delete ----  Quit ",      // NORMAL
     " ----  ----  View  ----  ---- Rename ----  ----  ----  ---- ",      // SHIFT
     "On-OffOn-Off Name  .Ext  Date  Size Unsort ----  ----  ---- ",      // CONTROL
     " Drv1  Drv2  FDiz  ----  ----  ---- Search Type  Line  ---- "       // ALT
   };
char i,j,n;
static char d=-1;
int TY;

TY=Cfg->TailleY;

if (d==c) return;
d=c;


if (DFen->FenTyp==0)    // Fenetre Normale
switch(c) {
    case 0:
        InfoSelect(DFen);
        break;
    case 1:
        ShiftMenu();
        break;
    case 2:
        CtrlMenu();
        break;
    case 3:
        AltMenu();
        break;
    }

n=0;
for (i=0;i<10;i++)	{
	PrintAt(n,TY-1,"F%d",(i+1)%10);
    for(j=0;j<2;j++,n++) AffCol(n,TY-1,1*16+8);
	for(j=0;j<6;j++,n++) {
       AffCol(n,TY-1,1*16+2);
	   AffChr(n,TY-1,*(bar[c]+i*6+j));
	   }
	}

}

//-----------------------------------------------------------------------------


void Int2Char(int n,char *s,char length)
{
if ((length>=3) & (n==1)) {
   strcpy(s,"One");
   return;
   }

ltoa(n,s,10);

if (strlen(s)<=length) return;

strcpy(s,s+strlen(s)-length);
}

char *Long2Str(long entier)
{
static char chaine[20];
char chaine2[20];
short i,j,n;

ltoa(entier,chaine2,10);
if ((n=strlen(chaine2))<9)
    {
    chaine[0]=chaine2[0];
    i=j=1;
    n--;

    while(n!=0)
        {
        if ((n==6) | (n==3))
            {
            chaine[i]='.';
            i++;
            }
        chaine[i]=chaine2[j];
        i++;
        j++;
        n--;
        }
    chaine[i]=0;
    }
    else
    {
    strcpy(chaine,chaine2);
    }

return chaine;
}

//--------------
// ASCII Table -
//--------------
void ASCIItable(void)
{
int n,x,y;

SaveEcran();

for (n=0;n<256;n++) {
    x=(n/16)*5;
    y=(n%16)+6;

    PrintAt(x,y,"%2X   ",n);
    AffChr(x+3,y,n);
    }

WinCadre(0,5,79,22,0);
ColWin(1,6,78,21,10*16+5);

Wait(0,0,0);

ChargeEcran();
}


void YouMad(char *s)
{
int x,l;
static char Buffer[70];
static int CadreLength=71;

struct Tmt T[5] = {
      {15,5,2,NULL,NULL},
      {45,5,3,NULL,NULL},
      { 2,2,0,"You are MAD!",NULL},
      { 1,1,4,NULL,&CadreLength},
      { 2,3,0,Buffer,NULL}
      };

struct TmtWin F = {
    3,10,76,17,
    "Error!"};

l=strlen(s);

x=(80-l)/2;     // 1-> 39, 2->39
if (x>25) x=25;

l=(40-x)*2;

CadreLength=l+1;

F.x1=x-2;
F.x2=x+l+1;

l=l+3;

T[0].x=(l/4)-5;
T[1].x=(3*l/4)-6;

strcpy(Buffer,s);

WinTraite(T,5,&F);

}

/*-------------------------------------------------------------*\
 *   Gestion de la barre de menu                               *
 * Renvoie 0 pour ESC                                          *
 * Sinon numero du titre;                                      *
 * xp: au depart, c'est le numero du titre                     *
 *     a l'arrivee ,c'est la position du titre                 *
\*-------------------------------------------------------------*/

int BarMenu(struct barmenu *bar,int nbr,int *poscur,int *xp,int *yp)
{
int c,i,j,n,x;
char let[32];
int car=0;

for (n=0;n<nbr;n++)
    let[n]=toupper(bar[n].titre[0]);

ColLin(0,0,80,1*16+7);
ChrLin(0,0,80,32);


x=0;
for(n=0;n<nbr;n++)
    x+=strlen(bar[n].titre);

i=(80-x)/nbr;
x=(80-(nbr-1)*i-x)/2;

c=*poscur;

do
{
if (c<0) c=nbr-1;
if (c>=nbr) c=0;

j=0;
for (n=0;n<nbr;n++)
    {
    if (n==c)
        {
        AffCol(x+j+n*i-1,0,7*16+4);
        AffCol(x+j+n*i,0,7*16+5);
        ColLin(x+j+n*i+1,0,strlen(bar[n].titre),7*16+4);
        *xp=x+j+n*i;
        }
        else
        {
        AffCol(x+j+n*i-1,0,1*16+7);
        AffCol(x+j+n*i,0,1*16+5);
        ColLin(x+j+n*i+1,0,strlen(bar[n].titre),1*16+7);
        }

    PrintAt(x+j+n*i,0,"%s",bar[n].titre);
    j+=strlen(bar[n].titre);
    }

if (*yp==0)
    break;

car=Wait(0,0,0);

switch(HI(car))
    {
    case 0x4B:
        c--;
        break;
    case 0x4D:
        c++;
        break;
    case 80:
        *yp=1;
        car=13;
        break;
    }
if (LO(car)!=0)
    for (n=0;n<nbr;n++)
        if (toupper(car)==let[n])
            c=n;
}
while ( (car!=13) & (car!=27) );

*poscur=c;

if (car==27)
    return 0;
    else
    return 1;
}

// 1: [RIGHT]   -1: [LEFT]
// 0: [ESC]      2: [ENTER]
int PannelMenu(struct barmenu *bar,int nbr,int *c,int *xp,int *yp)
{
int max,n,m,car,fin;
int i,col;
char couleur;
char let[32];

for (n=0;n<nbr;n++)
    {
    i=0;

    do
        {
        let[n]=toupper(bar[n].titre[i]);
        fin=1;
        for (m=0;m<n;m++)
            if (let[m]==let[n]) fin=0,i++;
        }
    while(fin==0);

    }

max=0;

for (n=0;n<nbr;n++)
    if (max<strlen(bar[n].titre))
        max=strlen(bar[n].titre);

SaveEcran();

if ((*xp)<1) (*xp)=1;

WinCadre(*xp-1,*yp-1,*xp+max,*yp+nbr,3);
ColWin(*xp,*yp,*xp+max-1,*yp+nbr-1,10*16+4);
ChrWin(*xp,*yp,*xp+max-1,*yp+nbr-1,32);

fin=0;

do
{
if ((*c)<0)   (*c)=nbr-1;
if ((*c)>=nbr) (*c)=0;

for (n=0;n<nbr;n++)
    {
    if (bar[n].fct==0)
        {
        ChrLin(*xp,(*yp)+n,max,196);
        ColLin(*xp,(*yp)+n,max,10*16+1);
        }
        else
        {
        PrintAt(*xp,(*yp)+n,"%s",bar[n].titre);
        col=1;
        if (n==*c)
            couleur=7*16+1;
            else
            couleur=10*16+4;

        for (i=0;i<strlen(bar[n].titre);i++)
            {
            if ( (col==1) & (toupper(bar[n].titre[i])==let[n]) )
                AffCol((*xp)+i,(*yp)+n,(couleur&240)+5),col=0;
                else
                AffCol((*xp)+i,(*yp)+n,couleur);
            }
        }
    }

car=Wait(0,0,0);

do
{
switch(HI(car))
    {
    case 0x48:  (*c)--; break;
    case 0x4B:  fin=-1; car=27;  break;
    case 0x4D:  fin=1;  car=27;  break;
    case 0x50:  (*c)++; break;
    }

if (LO(car)!=0)
    for (n=0;n<nbr;n++)
        if (toupper(car)==let[n])
            (*c)=n;
}
while (bar[*c].fct==0);

}
while ( (car!=13) & (car!=27) );

ChargeEcran();

if (car==27)
    return fin;
    else
    return 2;
}
