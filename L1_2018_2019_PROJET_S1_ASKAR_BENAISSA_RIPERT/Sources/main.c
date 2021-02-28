#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sdl.h>                                // pour définir la taille de la matrice
void init_matrice(int m[10][10])              //fonction d'affichage de la matrice
{
    int x,y;                                    //on initialise x y
    for(x=0; x < 10; x++)                      //on lance une boucle qui servira a faire chaque ligne
    {
        for(y=0; y < 10; y++)                  //on lance une boucle qui servira a faire chaque colonne
        {
            m[x][y]=rand()%2;                   //on remplit le tableau aleatoirement de 1 et de 0
        }
    }
    getchar();                                  //on attend une entrée de l'utilisateur pour continuer le programme
}
void aff_matrice(int m[10][10])               //sert a afficher une matrice, on prend comme donnée en entrée un tableau
{
    int b,c;                                    //on initialise x y
    SDL_Window *window = NULL;    /* On fait toutes nos initialisations ici */
    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              640, 480, SDL_WINDOW_SHOWN);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit;
    }
    SDL_Surface * screen = SDL_GetWindowSurface(window);
    int blanc = SDL_MapRGB(screen->format, 255, 250, 250);
    int noir = SDL_MapRGB(screen->format, 0, 0, 0);
    SDL_Rect rects[10][10];
    size_t j = 0;
    size_t i=0;
    for(b=0,i=0; b<=10,i <10; b++, i++)// pk ya un warning
    {
        for(c=0,j=0; c<=10,j<10; c++,j++)// la aussi
        {
            rects[i][j].w = 640/10;// 'cest bon
            rects[i][j].h = 480/10;//c'est bon
            rects[i][j].x =c*640/10;
            rects[i][j].y =b*480/10;

            if(m[b][c]==0)
            {
                SDL_FillRect(screen, &rects[b][c], blanc);
            }
            else
            {
                SDL_FillRect(screen, &rects[b][c], noir);
            }
        }
    }
    for(b=0; b< 10; b++)
    {
        for(c=0; c < 10; c++)
        {
            if(m[b][c]==0)
            {
                printf("%d ",m[b][c]);
            }
            else
            {
                printf("%d ",m[b][c]);
            }              //on affiche a l'ecran la valeur contenue dans la case
        }
        printf("\n");                           //on saute une ligne quand on arrive au bout d'une ligne(y=max-1)
    }
    SDL_UpdateWindowSurface(window);
    getchar();// vous pouvez remplacer par un sdl_delay mais vous aurez pas le temps de comparer avec ce qui est imprimé dans la console
Quit:
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
}
int somme(int m[10][10],int x,int y)
{
    int s;                                      // on intialise s qui sert a calculer la somme des valeurs des cases autour d'une case
    if(y==0)                                    //on procede par cas, si on est sur un bord on ne prend pas certaines valeurs poru eviter de sortir du tableau
    {
        if(x==0)
            return m[x+1][y]+m[x][y+1]+m[x+1][y+1];    //si on est en haut a gauche
        if(x==10-1)
            return m[x-1][y]+m[x-1][y+1]+m[x][y+1];// en bas a gauche
        return s=m[x-1][y]+m[x+1][y]+m[x-1][y+1]+m[x][y+1]+m[x+1][y+1];//si on est entre
    }
    if(y==10-1) //si on est tout a droite
    {
        if(x==0)
            return m[x+1][y]+m[x][y-1]+m[x+1][y-1];//en haut à droite
        if(x==10-1)
            return m[x-1][y]+m[x-1][y-1]+m[x][y-1];//en bas à droite
        return s=m[x-1][y]+m[x+1][y]+m[x-1][y-1]+m[x][y-1]+m[x+1][y-1];// si on est entre
    }
    {
        if(x==0)
            return m[x][y-1]+m[x+1][y-1]+m[x+1][y]+m[x][y+1]+m[x+1][y+1];//cas ou on ou est tt en haut
        if(x==10-1)
            return m[x-1][y-1]+m[x][y-1]+m[x-1][y]+m[x-1][y+1]+m[x][y+1];// cas ou on est tt en bas
        return m[x-1][y-1]+m[x][y-1]+m[x+1][y-1]+m[x-1][y]+m[x+1][y]+m[x-1][y+1]+m[x][y+1]+m[x+1][y+1];// cas general
    }
}

void pas(int m[10][10],int m2[10][10])// on met en entre les deux matrices
{
    int x,y,s;//  on initialise x y s
    for(x=0; x < 10; x++)
    {
        for(y=0; y < 10; y++)
        {
            s=somme(m,x,y);
            m2[x][y]=s==3||(s==2&&m[x][y]);//ici a l'aide de la somme on applique les regles, si elle est morte et entourée de 3 cellule vivante sa nouvelle valeur sera 1, ou si elle était vivante et entourée de deux cases vivante elle continue de vivre sinon elle meurt
        }
    }
}

void menu()
{
    int choix,i;
    int m[10][10], m2[10][10];
    printf("Bienvenue sur le jeu de la vie, tapez \n1:Acces au jeu\n2:Acces au regles\n");
    scanf("%d",&choix);
    switch(choix)
    {
    case(1):
        init_matrice(m);// on met des cases aleatoire qu'une seule fois
        for(i=0; i<100; i++)//ensuite on applique les regles a ces cases
        {
            aff_matrice(m);//on affiche la premiere matrice
            pas(m,m2);//on applique les regles et on met les nouvelles valeurs dans la seconde matrice
            //getchar();//on attends une nouvelle entrée de l'utilisateur
            aff_matrice(m2);//on affiche la deuxieme matrice
            pas(m2,m);//on applique les regles et on met les nouvelles valeures dans la matrice 1
            // getchar();// on attends une nouvelle entrée de l'utilisateur
        }
        break;//pour le switch
    case(2):
        printf("\n");
        printf("\nRegles de vie :\n1:Si une case vide est entouree de trois cases vivantes, alors elle sera vivante a la prochaine iteration. \n2:Si une case vivante est entourEe de deux ou trois cellules, alors elle sera vivante a la prochaine iteration. \n\nRegle de mort :\n1:Si une case vide est entouree de trois cases vivantes, alors elle sera vivante a la prochaine iteration.\n2:Si une case vivante est entouree de plus de trois cases vivantes, alors elle mourra de surpopulation a la prochaine iteration. \n \n");
        menu();//on retourne au menu après avoir affiché les regles
        break;
    }
}
int main(int argc,char *argv[])
{
    srand(time(NULL));// on lance le timer pour avoir des valeurs differente pour l'aleatoire
    menu();//on lance le menu
    return 0;
}
