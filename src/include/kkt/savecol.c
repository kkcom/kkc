// Created by Dialog Box Constructor/RedBug

int res;

//--- Internal Variable ---

static char KKTmpX2=70;
static int KKTmpY2=2;
static int KKTmp4=70;

//--- User Field ---

static char KKField4[71];

struct TmtWin F = {-1,-1,74,8,"Save Color & Configuration setup"};

struct Tmt T[] = {
    {12, 5, 2,NULL,NULL},
    {49, 5, 3,NULL,NULL},
    { 1, 1, 9,&KKTmpX2,&KKTmpY2},
    { 3, 2, 0,"Filename to save:",NULL},
    { 2, 3, 1,KKField4,&KKTmp4}
   };

strcpy(KKField4,"");

res=WinTraite(T,5,&F,0);

strcpy(?,KKField4);
