/*--------------------------------------------------------------------*\
|- Association header - player                                        -|
\*--------------------------------------------------------------------*/
#include <dos.h>
#include <process.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <conio.h>

#include <time.h>

#include "kk.h"
#include "win.h"

static struct
    {
    char *Filename;
    char *Titre;
    char *Meneur;
    signed short ext;
    short NoDir;
    char type;  /* 7 6 5 4 3 2 1 0
                   � � � � � � � ���� Unpacker
                   � � � � � � ������ Packer
                   ������������������ 0
                 */
    char os;    /* 7 6 5 4 3 2 1 0
                   � � � � � � � ���� Windows
                   ������������������ 0
                 */
    char info;
    char dir[128];
    } app[50];


static int nbr;        // nombre d'application
static int nbrdir; //
static int prem,max;


static int d,lfin;

static char di;
static int pos=0;

static char a;
static char chaine[132];
static char col[132];

static FILE *fic;
static char key[8];

static char Filename[256];
static char Titre[256];
static char Meneur[256];


/*--------------------------------------------------------------------*\
|-                                                                    -|
|- Code de retour:                                                    -|
|- 0: perfect                                                         -|
|- 1: error                                                           -|
|- 2: no player for this file                                         -|
|- 3: Arret ESCape                                                    -|
|-                                                                    -|
|- kefaire: 0 lancer application + fichier                            -|
|-          1 lancer application toute seule                          -|
|-          2 mettre l'application dans le buffer *name               -|
|-                                                                    -|
\*--------------------------------------------------------------------*/

int FicIdf(char *dest,char *name,int numero,int kefaire)
{
char ok,fin=0;
int j,i,n,m;

int car,nbrappl;

car=numero;

fic=fopen(KKFics->FicIdfFile,"rb");

if (fic==NULL)
    {
	PUTSERR("IDFEXT.RB missing");
	return 1;
	}

fread(key,1,8,fic);
if (memcmp(key,"RedBLEXU",8))
    {
	PUTSERR("File IDFEXT.RB is bad");
	return 1;
	}
di=fgetc(fic);

fread(&nbr,1,2,fic);

nbrappl=0;

for (j=0;j<nbr;j++)
	{
    char n;

    fread(&n,1,1,fic);
    Filename[n]=0;
    fread(Filename,n,1,fic);

    fread(&n,1,1,fic);
    Titre[n]=0;
    fread(Titre,n,1,fic);

    fread(&n,1,1,fic);
    Meneur[n]=0;
    fread(Meneur,n,1,fic);

    fread(&(app[nbrappl].ext),2,1,fic);              // Numero de format

    fread(&(app[nbrappl].NoDir),2,1,fic);            // Numero directory

    fread(&(app[nbrappl].type),1,1,fic);                  // Numero type

    fread(&(app[nbrappl].os),1,1,fic);        // Numero operating system

    fread(&(app[nbrappl].info),1,1,fic);       // Information sur player



    if ( (app[nbrappl].ext==numero) &
          (  (app[nbrappl].os==0) |
            ((app[nbrappl].os==1) & (KKCfg->_Win95==1)) )
         )
        {
        app[nbrappl].Filename=GetMem(strlen(Filename)+1);
        strcpy(app[nbrappl].Filename,Filename);
        app[nbrappl].Titre=GetMem(strlen(Titre)+1);
        strcpy(app[nbrappl].Titre,Titre);
        app[nbrappl].Meneur=GetMem(strlen(Meneur)+1);
        strcpy(app[nbrappl].Meneur,Meneur);
        nbrappl++;
        }
	}

fread(&nbrdir,1,2,fic);

for(n=0;n<nbrdir;n++)
    {
	fread(col,1,128,fic);
    for (i=0;i<nbrappl;i++)
        {
        if (n==app[i].NoDir-1)
            strcpy(app[i].dir,col);
		}
	}

fclose(fic);

if (nbrappl==0)
    {
	PUTSERR("No player for this file !");
    fin=2;
	}

if ( (nbrappl!=1) & (fin==0) )
    {
    int xx;

    SaveScreen();

    Bar(" Help CrMenu ----  ----  ----  ----  ----  ----  ----  ---- ");

    m=((Cfg->TailleY)-nbrappl)/2;

    if (m<2) m=2;
    max=nbrappl;
    if (max>Cfg->TailleY-3) max=Cfg->TailleY-3;

    xx=(Cfg->TailleX-56)/2;

    Cadre(xx,m-1,xx+55,m+max,0,Cfg->col[46],Cfg->col[47]);
    Window(xx+1,m,xx+54,m+max-1,Cfg->col[28]);

    PrintTo(24,1," Who? ");
    
    pos=0;
	nbr=nbrappl;

    d=1;
    lfin=52;

    prem=0;

	do	{
        if (pos<0) pos=0;
        if (pos>nbrappl-1) pos=nbrappl-1;

        while (pos-prem<0) prem--;
        while (pos-prem>=max) prem++;

        PrintAt(0,0,"%*s by %-*s",Cfg->TailleX/2-1,app[pos].Titre,
                                       Cfg->TailleX/2-3,app[pos].Meneur);

        for(n=0;n<max;n++)
            PrintTo(2,n,"%-49s",app[n+prem].Titre);

        for (n=d;n<=lfin;n++)
            {
            col[n]=GetRCol(n,pos-prem);
            AffRCol(n,pos-prem,Cfg->col[30]);     // 7
            }

        car=Wait(0,0,0);

        for (n=d;n<=lfin;n++)
            AffRCol(n,pos-prem,col[n]);

        if (car==0)
            {
            int button;

            button=MouseButton();

            if ((button&1)==1)     //--- gauche ------------------------
                {
                int y;

                y=MouseRPosY();

                if (y>=max)
                    car=80*256;
                    else
                    if (y<0)
                        car=72*256;
                        else
                        pos=prem+y;
                }

            if ((button&2)==2)     //--- droite ------------------------
                car=27;

            if ((button&4)==4)
                car=13;
            }


        if (LO(car)==0)
            {
            switch(HI(car))
                {
                case 72:
                    pos--;
                    break;
                case 80:
                    pos++;
                    break;
                case 0x47:
                    pos=0;
                    break;
                case 0x4F:
                    pos=nbr-1;
                    break;
                case 0x51:
                    pos+=5;
                    break;
                case 0x49:
                    pos-=5;
                    break;
                case 0x86:
                    WinMesg("Info. on dir",app[pos].dir,0);     // F12
                    break;
                case 0x3B:    //--- F1 ---------------------------------
                    HelpTopic("FicIdf");
                    break;
                case 0x3C:    //--- F2 ---------------------------------
                    ok=1;
                    strcpy(Filename,app[pos].Filename);
                    for(n=0;n<strlen(Filename);n++)
                        if (Filename[n]=='!') ok=0;
                    if (ok==1)
                        strcat(Filename," !:!\\!.!");
                    MenuCreat(app[pos].Titre,Filename,app[pos].dir);
                    break;
                }
			}
        }
    while ( (car!=27) & (car!=13) &
                  (HI(car)!=0x8D) & (HI(car)!=0x4B) & (HI(car)!=0x4D) );

    LoadScreen();

    if (LO(car)==27) fin=3;
    n=pos;
	}
	else
    {
	n=0;
    car=13;
    }

if (fin==0)
    {
    strcpy(chaine,app[n].dir);
    strcat(chaine,app[n].Filename);

    if (car!=13) kefaire=1;

    strcpy(dest,"");

    switch(kefaire)
        {
        case 0:
            FicIdfDev(dest,chaine,name);
//            sprintf(dest,"#%s %s",chaine,name);
            break;
        case 1:
            sprintf(dest,"#%s",chaine);
            break;
        case 2:
            strcpy(name,chaine);
            break;
        }
    }

for (j=0;j<nbrappl;j++)
	{
    free(app[nbrappl].Filename);
    free(app[nbrappl].Titre);
    free(app[nbrappl].Meneur);
    }

return fin;
}

/*--------------------------------------------------------------------*\
|- Code de retour:                                                    -|
|- 0: perfect                                                         -|
|- 1: error                                                           -|
|- 2: no player for this file                                         -|
\*--------------------------------------------------------------------*/

int PlayerIdf(char *name,int numero)
{
char fin=0;

int j,i,n;

int nbrappl;

a=numero;

fic=fopen(KKFics->FicIdfFile,"rb");

if (fic==NULL)
    {
	PUTSERR("IDFEXT.RB missing");
	return 1;
	}

fread(key,1,8,fic);
if (memcmp(key,"RedBLEXU",8))
    {
	PUTSERR("File IDFEXT.RB is bad");
	return 1;
	}
di=fgetc(fic);

fread(&nbr,1,2,fic);

nbrappl=0;

for (j=0;j<nbr;j++)
	{
    char n;

    fread(&n,1,1,fic);
    Filename[n]=0;
    fread(Filename,n,1,fic);

    fread(&n,1,1,fic);
    Titre[n]=0;
    fread(Titre,n,1,fic);

    fread(&n,1,1,fic);
    Meneur[n]=0;
    fread(Meneur,n,1,fic);

    fread(&(app[nbrappl].ext),2,1,fic);              // Numero de format

    fread(&(app[nbrappl].NoDir),2,1,fic);            // Numero directory

    fread(&(app[nbrappl].type),1,1,fic);                  // Numero type

    fread(&(app[nbrappl].os),1,1,fic);        // Numero operating system

    fread(&(app[nbrappl].info),1,1,fic);       // Information sur player

    if ( (app[nbrappl].ext==numero) &
          (  (app[nbrappl].os==0) |
            ((app[nbrappl].os==1) & (KKCfg->_Win95==1)) )
       )
        {
        app[nbrappl].Filename=GetMem(strlen(Filename)+1);
        strcpy(app[nbrappl].Filename,Filename);
        app[nbrappl].Titre=GetMem(strlen(Titre)+1);
        strcpy(app[nbrappl].Titre,Titre);
        app[nbrappl].Meneur=GetMem(strlen(Meneur)+1);
        strcpy(app[nbrappl].Meneur,Meneur);

        nbrappl++;
        }
	}

fread(&nbrdir,1,2,fic);

for(n=0;n<nbrdir;n++)
    {
	fread(col,1,128,fic);
    for (i=0;i<nbrappl;i++)
        {
        if (n==app[i].NoDir-1)
            strcpy(app[i].dir,col);
		}
	}

fclose(fic);

if (nbrappl==0)
    {
	PUTSERR("No player for this file !");
    fin=2;
	}
    else
    {
    i=0;
    for(n=0;n<nbrappl;n++)
        if (app[n].info==1)
            i=n;

    strcpy(name,app[i].dir);
    strcat(name,app[i].Filename);
    }

for (j=0;j<nbrappl;j++)
    {
    free(app[nbrappl].Filename);
    free(app[nbrappl].Titre);
    free(app[nbrappl].Meneur);
    }

return fin;
}


void FicIdfDev(char *dest,char *chaine,char *name)
{
char ok=1;
static char buf1[256],buf2[256];
char *drive,*rep,*file,*ext;
int m,n;

for(n=0;n<strlen(chaine);n++)
    {
    if (chaine[n]=='!') ok=0;
    }

if (ok==1)
    {
    FileinPath(name,buf1);
    sprintf(dest,"#%s %s",chaine,buf1);
    return;
    }


strcpy(buf1,name);

rep=file=ext=NULL;

drive=buf1;

for(n=0;n<strlen(name);n++)
    {
    if (buf1[n]==':')
        rep=buf1+n+1,buf1[n]=0;
    if (buf1[n]=='\\') m=n;
    }

file=buf1+m+1;
buf1[m]=0;

for(n=m;n<strlen(name);n++)
    {
    if (buf1[n]=='.')
        ext=buf1+n+1,buf1[n]=0;
    }

strcat(dest,name);

m=0;
ok=0;

for(n=0;n<strlen(chaine);n++)
    {
    if (chaine[n]!='!')
        {
        buf2[m]=chaine[n];
        m++;
        }
        else
        {
        switch(chaine[n+1])
            {
            case ':':
                strcpy(buf2+m,drive);
                m+=strlen(drive);
                break;
            case '\\':
                strcpy(buf2+m,rep);
                m+=strlen(rep);
                break;
            case '.':
                strcpy(buf2+m,file);
                m+=strlen(file);
                ok=1;
                break;
            default:
                if (ok==1)
                    {
                    strcpy(buf2+m,ext);
                    m+=strlen(ext);
                    }
                    else
                    {
                    strcpy(buf2+m,file);
                    m+=strlen(file);
                    ok=1;
                    }
                break;
            }
        }
    }
buf2[m]=0;

sprintf(dest,"#%s",buf2);

return;
}


