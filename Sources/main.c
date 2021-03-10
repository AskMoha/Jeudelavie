#include <stdio.h>
#include <SDL.h>

void fractale(SDL_Surface *fenetre, SDL_Surface *pixel, SDL_Surface *localisation,
                  TTF_Font *police, double x, double y, double zoom, int N)
{
    int i, j, n;
    double Zna, Znb, copie, Zmodule2, a, b;
    char coordonnees[256]={0};
    SDL_Color couleur={255, 255, 255};
    SDL_Rect position;

    for ( i=-fenetre->w/2; i<fenetre->w/2; i++ )
    {
        position.x=i+fenetre->w/2;
        a=4*i/((double)fenetre->w*zoom)+x;

        for ( j=-fenetre->h/2; j<fenetre->h/2; j++ )
        {
            n=Zna=Znb=0;
            position.y=j+fenetre->h/2;
            b=4*j/((double)fenetre->h*zoom)+y;

            if ( ( -5<i && i<5 && j==0 ) || ( -5<j && j<5 && i==0 ) )
                SDL_FillRect(pixel, NULL, SDL_MapRGB(pixel->format, 255, 255, 255));
            else
            {
                do
                {
                    n++;

                    copie=Zna;
                    Zna=Zna*Zna-Znb*Znb+a;
                    Znb=2*copie*Znb+b;

                    Zmodule2=Zna*Zna+Znb*Znb;
                }
                while ( n<N && Zmodule2<=4 );

                if ( n==N )
                    SDL_FillRect(pixel, NULL, SDL_MapRGB(pixel->format, 0, 0, 0));
                else
                    SDL_FillRect(pixel, NULL, SDL_MapRGB(pixel->format, 64*n/N, 255*n/N, 0));
            }

            SDL_BlitSurface(pixel, NULL, fenetre, &position);
        }
    }

    position.x=10;
    position.y=10;

    sprintf(coordonnees, "(%.4f; %.4f)", x, -y);
    localisation=TTF_RenderText_Solid(police, coordonnees, couleur);
    SDL_BlitSurface(localisation, NULL, fenetre, &position);

    SDL_Flip(fenetre);
    return;
}

int main(int argc, char** argv)
{
    int fin=0, N=30;
    double zoom=1, x=0, y=0;
    SDL_Event event;
    TTF_Font *police;
    SDL_Surface *fenetre, *pixel, *localisation;

    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_WM_SetCaption("Fractale de Mandelbrot", 0);

    fenetre=SDL_SetVideoMode(640, 640, 32, SDL_HWSURFACE|SDL_DOUBLEBUF);
    pixel=SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
    police=TTF_OpenFont("lucon.ttf", 10);

    fractale(fenetre, pixel, localisation, police, x, y, zoom, N);

    while (!fin)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                fin=1;
                break;
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        fin=1;
                        break;
                    case SDLK_KP5:
                        fractale(fenetre, pixel, localisation, police, x, y, zoom, N+=30);
                        break;
                    case SDLK_KP_PLUS:
                        fractale(fenetre, pixel, localisation, police, x, y, zoom+=zoom/2, N);
                        break;
                    case SDLK_KP_MINUS:
                        if ( zoom-zoom/3>=1 )
                            fractale(fenetre, pixel, localisation, police, x, y, zoom-=zoom/3, N);
                        break;
                    case SDLK_RIGHT:
                        fractale(fenetre, pixel, localisation, police, x+=0.4/zoom, y, zoom, N);
                        break;
                    case SDLK_LEFT:
                        fractale(fenetre, pixel, localisation, police, x-=0.4/zoom, y, zoom, N);
                        break;
                    case SDLK_UP:
                        fractale(fenetre, pixel, localisation, police, x, y-=0.4/zoom, zoom, N);
                        break;
                    case SDLK_DOWN:
                        fractale(fenetre, pixel, localisation, police, x, y+=0.4/zoom, zoom, N);
                        break;
                    default:
                        break;
                }
            }
        }
    }

    SDL_FreeSurface(pixel);
    TTF_CloseFont(police);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
