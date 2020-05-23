#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <SDL\SDL.h>
#include <SDL/SDL_ttf.h>
#include <fmod/fmod.h>
#include <math.h>
#include <time.h>
#include <SDL/SDL_mixer.h>
#include <dos.h>
#include "graphics.h"

#define LARGEUR 1440
#define HAUTEUR 900



typedef struct pixel
{
    int R,G,B;
} PIXEL;


void lire_image( PIXEL T[LARGEUR][HAUTEUR], char *NOM )
{
    int i, j, n, l, h;
    char p;
    FILE* fichier;
    fichier = NULL;
    fichier = fopen("allo.ppm", "r");
    if (fichier != NULL)
    {
        fscanf(fichier, "%c", &p);
        fscanf(fichier, "%d", &n);
        fscanf(fichier, "%d", &l);
        fscanf(fichier, "%d", &h);
        fscanf(fichier, "%d", &n);
        for( j = HAUTEUR -1; j >=0; j--)
        {
            for( i = 0; i < LARGEUR; i++)
            fscanf( fichier, "%d %d %d", &T[i][j].R, &T[i][j].G, &(T[i][j].B) );
        }
    }
    else printf("Pas de fichier");
    fclose(fichier);
}


void dessine_image( PIXEL T[LARGEUR][HAUTEUR])
{
    int j,i;
    POINT P,A3,B3;
	COULEUR C;
    for(j = 0; j< HAUTEUR; j++)
	{
		for (i = 0; i < LARGEUR; i++)
		{
    C = couleur_RGB(T[i][j].R,T[i][j].G,T[i][j].B);
    P.x = i;
    P.y = j;
    draw_pixel(P, C);
		}
	}
}


void affpol(PIXEL T[LARGEUR][HAUTEUR])
{
    POINT A3,B3;
    A3.x=380; A3.y=0.524*900+30;
    B3.x=750; B3.y=0.524*900+30;
    aff_pol("Jouer",60,A3,red);
    aff_pol("Quitter",60,B3,red);
}


void suivant_ecran(PIXEL T[LARGEUR][HAUTEUR]) /*permet de quitter ou de lancer le jeu*/
{
    int i=0;
    POINT E,F,G,I;
    while(i==0)
    {
        E=wait_clic();

            if (0.575*1100+(1440-1100)/2 < E.x && E.x< 0.75*1100+(1440-1100)/2 && 0.44*900 < E.y && E.y < 0.55*900)
            {
                exit(0);
            }
            if (0.25*1100+(1440-1100)/2 < E.x && E.x< 0.425*1100+(1440-1100)/2 && 0.44*900 < E.y && E.y < 0.55*900)
            {
                F.x=0; F.y=0;
                G.x=1440; G.y=900;
                draw_fill_rectangle(F,G,black);
                I.x=0;  I.y=900;
                affiche_auto_off();
                affiche_image("VraiGuitare.bmp",I,1440,900);
                affiche_all();
                i=1;
            }
    }
}


int demarrage1(int vitesse)
{
    int difficulty; int chiffre; vitesse=0;
    printf("Les touches pour jouer sont C V B N\n");
    while(vitesse==0)
    {
    printf("Difficulty ? (facile1/moyen2/difficile3/extreme4) : ");
    scanf("%d",&chiffre);
    if(chiffre==1){vitesse=1;} if(chiffre==2){vitesse=2;} if(chiffre==3){vitesse=3;} if(chiffre==4){vitesse=4;}
    }

    return vitesse;
}

int demarrage2(int TIME)
{
    printf("Temps ? (secondes) : ");
    scanf("%d",&TIME);
    return TIME;
}


int MUSIQUE()
{
    SDL_Event event;
    int continuer = 1;

    FMOD_SYSTEM *system;
    FMOD_SOUND *musique;
    FMOD_RESULT resultat;
    FMOD_System_Create(&system);
    FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    resultat = FMOD_System_CreateSound(system, "Zeze.mp3", FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    FMOD_CHANNEL *channel;
    FMOD_System_GetChannel(system, 0, &channel);

    if (resultat != FMOD_OK)
    {
        printf("Impossible de lire le fichier mp3\n");
        exit(EXIT_FAILURE);
    }

    FMOD_System_PlaySound(system, 0, musique, 0, NULL);
    FMOD_Channel_SetVolume(channel, 0.2);

    /*while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_p) //Si on appuie sur P
            {
                FMOD_CHANNELGROUP *canal;
                FMOD_BOOL etat;
                FMOD_System_GetMasterChannelGroup(system, &canal);
                FMOD_ChannelGroup_GetPaused(canal, &etat);

                if (etat) // Si la chanson est en pause
                    FMOD_ChannelGroup_SetPaused(canal, 0); // On enlève la pause
                else // Sinon, elle est en cours de lecture
                    FMOD_ChannelGroup_SetPaused(canal, 1); // On active la pause
            }
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                continuer = 0;
                break;
            }
            break;
        }
    }*/
}


int TableauRemplir(SDL_Rect TABLOY[100],SDL_Rect TABLOB[100],SDL_Rect TABLOG[100],SDL_Rect TABLOR[100])
{
    int i,j;
    TABLOY[0].y=-20; TABLOY[0].x=579;
    TABLOB[0].y=-20; TABLOB[0].x=653;
    TABLOG[0].y=-20; TABLOG[0].x=725;
    TABLOR[0].y=-20; TABLOR[0].x=798;
    for(i=0;i<80;i++)
    {
        TABLOY[i+1].y=TABLOY[i].y+10;
        TABLOY[i].x=579;
        TABLOB[i+1].y=TABLOB[i].y+10;
        TABLOB[i].x=653;
        TABLOG[i+1].y=TABLOG[i].y+10;
        TABLOG[i].x=725;
        TABLOR[i+1].y=TABLOR[i].y+10;
        TABLOR[i].x=798;
    }
}




int THEGAME(SDL_Rect TABLOG[100],SDL_Rect TABLOR[100],SDL_Rect TABLOY[100],SDL_Rect TABLOB[100],SDL_Surface *ecran, PIXEL T[LARGEUR][HAUTEUR], int difficulty, int score, int TIME)
{
    SDL_Surface *guitare=NULL;
    guitare=SDL_LoadBMP("guitare.bmp");

    SDL_Surface *boutonyellow=NULL;
    boutonyellow=SDL_LoadBMP("YELLOW.bmp");
    SDL_SetColorKey(boutonyellow, SDL_SRCCOLORKEY, SDL_MapRGB(boutonyellow->format, 255,255,255));

    SDL_Surface *boutonblue=NULL;
    boutonblue=SDL_LoadBMP("BLUE.bmp");
    SDL_SetColorKey(boutonblue, SDL_SRCCOLORKEY, SDL_MapRGB(boutonblue->format, 255,255,255));

    SDL_Surface *boutongreen=NULL;
    boutongreen=SDL_LoadBMP("GREEN.bmp");
    SDL_SetColorKey(boutongreen, SDL_SRCCOLORKEY, SDL_MapRGB(boutongreen->format, 255,255,255));

    SDL_Surface *boutonred=NULL;
    boutonred=SDL_LoadBMP("RED.bmp");
    SDL_SetColorKey(boutonred, SDL_SRCCOLORKEY, SDL_MapRGB(boutonred->format, 255,255,255));


int time=1000; int vitesse; int delay; int attente; score=0;
int partie=0;int i=0; int j=0; int k=0; int l=0; int z,w;
if(difficulty==1){vitesse=700;delay=10;} if(difficulty==2){vitesse=600;delay=5;} if(difficulty==3){vitesse=450;delay=0;} if(difficulty==4){vitesse=300; delay=0;}
int y1,y1i,y2,y2i,y3,y3i,y4,y4i,y5,y5i,b1,b1i,b2,b2i,b3,b3i,b4,b4i,b5,b5i,g1,g1i,g2,g2i,g3,g3i,g4,g4i,g5,g5i,r1,r1i,r2,r2i,r3,r3i,r4,r4i,r5,r5i;
POINT I; I.x=0; I.y=0; POINT K; POINT Y1,Y2,Y3,Y4,Y5,B1,B2,B3,B4,B5,G1,G2,G3,G4,G5,R1,R2,R3,R4,R5;
Y1.x=579; Y1.y=890; Y2.x=579; Y2.y=890; Y3.x=579; Y3.y=890; Y4.x=579; Y4.y=890; Y5.x=579; Y5.y=890;
B1.x=653; B1.y=890; B2.x=653; B2.y=890; B3.x=653; B3.y=890; B4.x=653; B4.y=890; B5.x=653; B5.y=890;
G1.x=725; G1.y=890; G2.x=725; G2.y=890; G3.x=725; G3.y=890; G4.x=725; G4.y=890; G5.x=725; G5.y=890;
R1.x=798; R1.y=890; R2.x=798; R2.y=890; R3.x=798; R3.y=890; R4.x=798; R4.y=890; R5.x=798; R5.y=890;
y1=0;y1i=0;y2=0;y2i=0;y3=0;y3i=0;y4=0;y4i=0;y5=0;y5i=0;b1=0;b1i=0;b2=0;b2i=0;b3=0;b3i=0;b4=0;b4i=0;b5=0;b5i=0;
g1=0;g1i=0;g2=0;g2i=0;g3=0;g3i=0;g4=0;g4i=0;g5=0;g5i=0;r1=0;r1i=0;r2=0;r2i=0;r3=0;r3i=0;r4=0;r4i=0;r5=0;r5i=0;
POINT Z; Z.x=300; Z.y=300;
int timingY,timingB,timingG,timingR; int Yz=0, Bz=0,Gz=0,Rz=0; int touchedelayYp,touchedelayBp,touchedelayGp,touchedelayRp,Yp,Bp,Gp,Rp;
char Score[1000]; char Temps[1000];

clock_t t;
t = clock();
double t1; int currenttime;


    while(partie==0)
    {
        t1 = clock() - t;
        currenttime = ((double)t1)/CLOCKS_PER_SEC;


        if(t1>time)
        {
            time=time+vitesse;
            w=alea_int(8)+1;
            if(w>3)
            {
                z=alea_int(4)+1;
                if(z==1){
                    if(y1==0){y1=1;}
                    else if(y1==1 && y2==0){y2=1;}
                    else if(y2==1 && y3==0){y3=1;}
                    else if(y3==1 && y4==0){y4=1;}
                    else if(y4==1 && y5==0){y5=1;}
                    }
                if(z==2){
                    if(b1==0){b1=1;}
                    else if(b1==1 && b2==0){b2=1;}
                    else if(b2==1 && b3==0){b3=1;}
                    else if(b3==1 && b4==0){b4=1;}
                    else if(b4==1 && b5==0){b5=1;}
                    }
                if(z==3){
                    if(g1==0){g1=1;}
                    else if(g1==1 && g2==0){g2=1;}
                    else if(g2==1 && g3==0){g3=1;}
                    else if(g3==1 && g4==0){g4=1;}
                    else if(g4==1 && g5==0){g5=1;}
                    }
                if(z==4){
                    if(r1==0){r1=1;}
                    else if(r1==1 && r2==0){r2=1;}
                    else if(r2==1 && r3==0){r3=1;}
                    else if(r3==1 && r4==0){r4=1;}
                    else if(r4==1 && r5==0){r5=1;}
                    }
            }

            if(w==3)
            {
                if(y1==0){y1=1;}
                    else if(y1==1 && y2==0){y2=1;}
                    else if(y2==1 && y3==0){y3=1;}
                    else if(y3==1 && y4==0){y4=1;}
                    else if(y4==1 && y5==0){y5=1;}
                if(b1==0){b1=1;}
                    else if(b1==1 && b2==0){b2=1;}
                    else if(b2==1 && b3==0){b3=1;}
                    else if(b3==1 && b4==0){b4=1;}
                    else if(b4==1 && b5==0){b5=1;}
                if(g1==0){g1=1;}
                    else if(g1==1 && g2==0){g2=1;}
                    else if(g2==1 && g3==0){g3=1;}
                    else if(g3==1 && g4==0){g4=1;}
                    else if(g4==1 && g5==0){g5=1;}
                if(r1==0){r1=1;}
                    else if(r1==1 && r2==0){r2=1;}
                    else if(r2==1 && r3==0){r3=1;}
                    else if(r3==1 && r4==0){r4=1;}
                    else if(r4==1 && r5==0){r5=1;}
            }

            if(w<3)
            {
                z=alea_int(6)+1;
                if(z==1){
                    if(y1==0){y1=1;}
                    else if(y1==1 && y2==0){y2=1;}
                    else if(y2==1 && y3==0){y3=1;}
                    else if(y3==1 && y4==0){y4=1;}
                    else if(y4==1 && y5==0){y5=1;}
                    if(b1==0){b1=1;}
                    else if(b1==1 && b2==0){b2=1;}
                    else if(b2==1 && b3==0){b3=1;}
                    else if(b3==1 && b4==0){b4=1;}
                    else if(b4==1 && b5==0){b5=1;}
                }
                if(z==2){
                    if(y1==0){y1=1;}
                    else if(y1==1 && y2==0){y2=1;}
                    else if(y2==1 && y3==0){y3=1;}
                    else if(y3==1 && y4==0){y4=1;}
                    else if(y4==1 && y5==0){y5=1;}
                    if(g1==0){g1=1;}
                    else if(g1==1 && g2==0){g2=1;}
                    else if(g2==1 && g3==0){g3=1;}
                    else if(g3==1 && g4==0){g4=1;}
                    else if(g4==1 && g5==0){g5=1;}
                }
                if(z==3){
                    if(y1==0){y1=1;}
                    else if(y1==1 && y2==0){y2=1;}
                    else if(y2==1 && y3==0){y3=1;}
                    else if(y3==1 && y4==0){y4=1;}
                    else if(y4==1 && y5==0){y5=1;}
                    if(r1==0){r1=1;}
                    else if(r1==1 && r2==0){r2=1;}
                    else if(r2==1 && r3==0){r3=1;}
                    else if(r3==1 && r4==0){r4=1;}
                    else if(r4==1 && r5==0){r5=1;}
                }
                if(z==4){
                    if(b1==0){b1=1;}
                    else if(b1==1 && b2==0){b2=1;}
                    else if(b2==1 && b3==0){b3=1;}
                    else if(b3==1 && b4==0){b4=1;}
                    else if(b4==1 && b5==0){b5=1;}
                    if(g1==0){g1=1;}
                    else if(g1==1 && g2==0){g2=1;}
                    else if(g2==1 && g3==0){g3=1;}
                    else if(g3==1 && g4==0){g4=1;}
                    else if(g4==1 && g5==0){g5=1;}
                }
                if(z==5){
                    if(b1==0){b1=1;}
                    else if(b1==1 && b2==0){b2=1;}
                    else if(b2==1 && b3==0){b3=1;}
                    else if(b3==1 && b4==0){b4=1;}
                    else if(b4==1 && b5==0){b5=1;}
                    if(r1==0){r1=1;}
                    else if(r1==1 && r2==0){r2=1;}
                    else if(r2==1 && r3==0){r3=1;}
                    else if(r3==1 && r4==0){r4=1;}
                    else if(r4==1 && r5==0){r5=1;}
                }
                if(z==6){
                    if(g1==0){g1=1;}
                    else if(g1==1 && g2==0){g2=1;}
                    else if(g2==1 && g3==0){g3=1;}
                    else if(g3==1 && g4==0){g4=1;}
                    else if(g4==1 && g5==0){g5=1;}
                    if(r1==0){r1=1;}
                    else if(r1==1 && r2==0){r2=1;}
                    else if(r2==1 && r3==0){r3=1;}
                    else if(r3==1 && r4==0){r4=1;}
                    else if(r4==1 && r5==0){r5=1;}
                }
            }

        }


        affiche_auto_off();
        SDL_BlitSurface(guitare,NULL,ecran,&I);


        if(y1==1)
        {
            TABLOY[y1i+1].y=TABLOY[y1i].y+10;
            SDL_BlitSurface(boutonyellow, NULL, ecran, &TABLOY[y1i]);
            y1i++; Y1.y=Y1.y-10;
            if(y1i==80){y1i=0; y1=0; Y1.y=890; Yp=0; touchedelayYp=t1+100;}
        }
        if(y2==1)
        {
            TABLOY[y2i+1].y=TABLOY[y2i].y+10;
            SDL_BlitSurface(boutonyellow, NULL, ecran, &TABLOY[y2i]);
            y2i++; Y2.y=Y2.y-10;
            if(y2i==80){y2i=0; y2=0; Y2.y=890; Yp=0; touchedelayYp=t1+100;}
        }
        if(y3==1)
        {
            TABLOY[y3i+1].y=TABLOY[y3i].y+10;
            SDL_BlitSurface(boutonyellow, NULL, ecran, &TABLOY[y3i]);
            y3i++; Y3.y=Y3.y-10;
            if(y3i==80){y3i=0; y3=0; Y3.y=890; Yp=0; touchedelayYp=t1+100;}
        }
        if(y4==1)
        {
            TABLOY[y4i+1].y=TABLOY[y4i].y+10;
            SDL_BlitSurface(boutonyellow, NULL, ecran, &TABLOY[y4i]);
            y4i++; Y4.y=Y4.y-10;
            if(y4i==80){y4i=0; y4=0; Y4.y=890; Yp=0; touchedelayYp=t1+100;}
        }
        if(y5==1)
        {
            TABLOY[y5i+1].y=TABLOY[y5i].y+10;
            SDL_BlitSurface(boutonyellow, NULL, ecran, &TABLOY[y5i]);
            y5i++; Y5.y=Y5.y-10;
            if(y5i==80){y5i=0; y5=0; Y5.y=890; Yp=0; touchedelayYp=t1+100;}
        }

        if(b1==1)
        {
            TABLOB[b1i+1].y=TABLOB[b1i].y+10;
            SDL_BlitSurface(boutonblue, NULL, ecran, &TABLOB[b1i]);
            b1i++; B1.y=B1.y-10;
            if(b1i==80){b1i=0; b1=0; B1.y=890; Bp=0; touchedelayBp=t1+100;}
        }
        if(b2==1)
        {
            TABLOB[b2i+1].y=TABLOB[b2i].y+10;
            SDL_BlitSurface(boutonblue, NULL, ecran, &TABLOB[b2i]);
            b2i++; B2.y=B2.y-10;
            if(b2i==80){b2i=0; b2=0; B2.y=890; Bp=0; touchedelayBp=t1+100;}
        }
        if(b3==1)
        {
            TABLOB[b3i+1].y=TABLOB[b3i].y+10;
            SDL_BlitSurface(boutonblue, NULL, ecran, &TABLOB[b3i]);
            b3i++; B3.y=B3.y-10;
            if(b3i==80){b3i=0; b3=0; B3.y=890; Bp=0; touchedelayBp=t1+100;}
        }
        if(b4==1)
        {
            TABLOB[b4i+1].y=TABLOB[b4i].y+10;
            SDL_BlitSurface(boutonblue, NULL, ecran, &TABLOB[b4i]);
            b4i++; B4.y=B4.y-10;
            if(b4i==80){b4i=0; b4=0; B4.y=890; Bp=0; touchedelayBp=t1+100;}
        }
        if(b5==1)
        {
            TABLOB[b5i+1].y=TABLOB[b5i].y+10;
            SDL_BlitSurface(boutonblue, NULL, ecran, &TABLOB[b5i]);
            b5i++; B5.y=B5.y-10;
            if(b5i==80){b5i=0; b5=0; B5.y=890; Bp=0; touchedelayBp=t1+100;}
        }

        if(g1==1)
        {
            TABLOG[g1i+1].y=TABLOG[g1i].y+10;
            SDL_BlitSurface(boutongreen, NULL, ecran, &TABLOG[g1i]);
            g1i++; G1.y=G1.y-10;
            if(g1i==80){g1i=0; g1=0; G1.y=890; Gp=0; touchedelayGp=t1+100;}
        }
        if(g2==1)
        {
            TABLOG[g2i+1].y=TABLOG[g2i].y+10;
            SDL_BlitSurface(boutongreen, NULL, ecran, &TABLOG[g2i]);
            g2i++; G2.y=G2.y-10;
            if(g2i==80){g2i=0; g2=0; G2.y=890; Gp=0; touchedelayGp=t1+100;}
        }
        if(g3==1)
        {
            TABLOG[g3i+1].y=TABLOG[g3i].y+10;
            SDL_BlitSurface(boutongreen, NULL, ecran, &TABLOG[g3i]);
            g3i++; G3.y=G3.y-10;
            if(g3i==80){g3i=0; g3=0; G3.y=890; Gp=0; touchedelayGp=t1+100;}
        }
        if(g4==1)
        {
            TABLOG[g4i+1].y=TABLOG[g4i].y+10;
            SDL_BlitSurface(boutongreen, NULL, ecran, &TABLOG[g4i]);
            g4i++; G4.y=G4.y-10;
            if(g4i==80){g4i=0; g4=0; G4.y=890; Gp=0; touchedelayGp=t1+100;}
        }
        if(g5==1)
        {
            TABLOG[g5i+1].y=TABLOG[g5i].y+10;
            SDL_BlitSurface(boutongreen, NULL, ecran, &TABLOG[g5i]);
            g5i++; G5.y=G5.y-10;
            if(g5i==80){g5i=0; g5=0; G5.y=890; Gp=0; touchedelayGp=t1+100;}
        }

        if(r1==1)
        {
            TABLOR[r1i+1].y=TABLOR[r1i].y+10;
            SDL_BlitSurface(boutonred, NULL, ecran, &TABLOR[r1i]);
            r1i++; R1.y=R1.y-10;
            if(r1i==80){r1i=0; r1=0; R1.y=890; Rp=0; touchedelayRp=t1+100;}
        }
        if(r2==1)
        {
            TABLOR[r2i+1].y=TABLOR[r2i].y+10;
            SDL_BlitSurface(boutonred, NULL, ecran, &TABLOR[r2i]);
            r2i++; R2.y=R2.y-10;
            if(r2i==80){r2i=0; r2=0; R2.y=890; Rp=0; touchedelayRp=t1+100;}
        }
        if(r3==1)
        {
            TABLOR[r3i+1].y=TABLOR[r3i].y+10;
            SDL_BlitSurface(boutonred, NULL, ecran, &TABLOR[r3i]);
            r3i++; R3.y=R3.y-10;
            if(r3i==80){r3i=0; r3=0; R3.y=890; Rp=0; touchedelayRp=t1+100;}
        }
        if(r4==1)
        {
            TABLOR[r4i+1].y=TABLOR[r4i].y+10;
            SDL_BlitSurface(boutonred, NULL, ecran, &TABLOR[r4i]);
            r4i++; R4.y=R4.y-10;
            if(r4i==80){r4i=0; r4=0; R4.y=890; Rp=0; touchedelayRp=t1+100;}
        }
        if(r5==1)
        {
            TABLOR[r5i+1].y=TABLOR[r5i].y+10;
            SDL_BlitSurface(boutonred, NULL, ecran, &TABLOR[r5i]);
            r5i++; R5.y=R5.y-10;
            if(r5i==80){r5i=0; r5=0; R5.y=890; Rp=0; touchedelayRp=t1+100;}
        }



    attente=t1+20;

    while(t1<attente)
    {

        t1 = clock() - t;
        K=get_arrow();

//Point fort et faible de votre parcoursup

        if(K.x<0 && Yz==0)
        {
            if((Y1.y<=150 || Y2.y<=150 || Y3.y<=150 || Y4.y<=150 || Y5.y<=150) || Yp==0){timingY=t1+300; Yz=1; Yp=1; score++;}
            else {timingY=t1+300; Yz=1; score--;}
        }

        if(K.x>0 && Bz==0)
        {
            if((B1.y<=150 || B2.y<=150 || B3.y<=150 || B4.y<=150 || B5.y<=150) || Bp==0){timingB=t1+300; Bz=1; Bp=1; score++;}
            else {timingB=t1+300; Bz=1; score--;}
        }

        if(K.y<0 && Gz==0)
        {
            if((G1.y<=150 || G2.y<=150 || G3.y<=150 || G4.y<=150 || G5.y<=150) || Gp==0){timingG=t1+300; Gz=1; Gp=1; score++;}
            else {timingG=t1+300; Gz=1; score--;}
        }

        if(K.y>0 && Rz==0)
        {
            if((R1.y<=150 || R2.y<=150 || R3.y<=150 || R4.y<=150 || R5.y<=150) || Rp==0){timingR=t1+300; Rz=1; Rp=1; score++;}
            else {timingR=t1+300; Rz=1; score--;}
        }


    if(t1>touchedelayYp){Yp=1;}
    if(t1>touchedelayBp){Bp=1;}
    if(t1>touchedelayGp){Gp=1;}
    if(t1>touchedelayRp){Rp=1;}

    if(t1>timingY && Yz==1){Yz=0;}
    if(t1>timingB && Bz==1){Bz=0;}
    if(t1>timingG && Gz==1){Gz=0;}
    if(t1>timingR && Rz==1){Rz=0;}


}

        sprintf(Score,"%d",score);
        if(score<0){aff_pol(Score,100,Z,red);}
        if(score>=0){aff_pol(Score,100,Z,white);}
        if(score>5){aff_pol(Score,100,Z,yellow);}
        if(score>=10){score=10; aff_pol(Score,100,Z,lawngreen);}
        if(score<=-10){sprintf(Temps,"%d",currenttime); partie=1; Z.x=Z.x-100; Z.y=Z.y+200; aff_pol("Game over",80,Z,red); Z.y=Z.y+300; aff_pol(Temps,100,Z,lawngreen);}


    affiche_all();

    if(t1>TIME*1000){partie=1;}
    SDL_Delay(delay);

    }

}






int main(int argc,char*argv[])
{
    freopen("CON", "r",stdin);
    freopen("CON", "w", stdout);

    static PIXEL T[LARGEUR][HAUTEUR];
    SDL_Rect TABLOY[100]; SDL_Rect TABLOB[100]; SDL_Rect TABLOG[100]; SDL_Rect TABLOR[100];
    int score; int TIME; int vitesse;
    lire_image(T,"allo.ppm");
    vitesse=demarrage1(vitesse);
    TIME=demarrage2(TIME);

    init_graphics(LARGEUR,HAUTEUR);
    access_screen();
    affiche_auto_off();
        dessine_image(T);
        affpol(T);
    affiche_all();
    suivant_ecran(T);
    TableauRemplir(TABLOY,TABLOB,TABLOG,TABLOR);
    MUSIQUE();
    THEGAME(TABLOG,TABLOR,TABLOY,TABLOB,SDL_screen,T,vitesse,score,TIME);

    wait_escape();
    return 0;
}
