#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>//P2//P3
#include <SDL/SDL_mixer.h>//P4

int main (void)
{

SDL_Surface *screen = NULL; //P1
SDL_Surface *image = NULL;//P2
SDL_Surface *perso = NULL;//P3
SDL_Rect positionecran, positionperso;//p2//p3

SDL_Event  event;//P4
char pause;//P1
int done = 1;//P4

// initialiser SDL video 
        if (SDL_Init(SDL_INIT_VIDEO) != 0) //P1
        {//initialiser SDL video
		printf("Unable to initialize SDL: %s\n", SDL_GetError());//P1
		return -1;//P1
	}
// create a new window
	screen = SDL_SetVideoMode(1600, 400, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);//P1
	if (screen == NULL) //P1
        {
		printf("Unable to set video mode: %s\n", SDL_GetError());//P1
		return -1;//P1
	}


//image bitmap


image = SDL_LoadBMP("background.bmp");// P2// ou IMAG_Load
if(image==NULL)//P2
{  printf("Unable to load bitmap: %s",SDL_GetError());//P2
   return -1;}//P2
//Position Background
positionecran.x=0;//P2
positionecran.y=0;//P2
positionecran.w=image->w;//P2
positionecran.h=image->h;//P2

 perso = IMG_Load("detective.png");
	if (perso == NULL) {
		printf("Unable to load png: %s\n", SDL_GetError());
		return 1;
	}
SDL_SetColorKey(perso,SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(perso->format,255,255,255));//P3 (Arriére plan transparent pour le perso)
//Position Personnage

positionperso.x=380;//P2
positionperso.y=200;//P2
positionperso.w=perso->w;//P2
positionperso.h=perso->h;//P2

if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //API Mixer Initioalization//P5
   	{
      		printf("%s", Mix_GetError());
   	}
   	Mix_Music *music; //Construct Mix_Music pointer
   	music = Mix_LoadMUS("music.mp3"); //load the music
   	Mix_PlayMusic(music, 0); //play music

while (done){//P4
//Blit the image to the backbuffer
       SDL_BlitSurface(image, &positionecran, screen, NULL);//P2
       SDL_BlitSurface(perso, &positionecran, screen, &positionperso);//P3

       while (SDL_PollEvent(&event))//P4
	{
              switch(event.type)//P4
               {
      		   case SDL_QUIT://P4
 			done = 0;//P4
		   break;//P4

		   case SDL_KEYDOWN://P4
		   {
		      if(event.key.keysym.sym == SDLK_ESCAPE) done=0;//P4
		      if(event.key.keysym.sym == SDLK_RIGHT) positionperso.x+=10;//P4
		      if(event.key.keysym.sym == SDLK_LEFT) positionperso.x-=10;//P4
		      if(event.key.keysym.sym == SDLK_UP) positionperso.y-=10;//P4
		      if(event.key.keysym.sym == SDLK_DOWN) positionperso.y+=10;//P4
		   break;   //P4
		   }


	       }	

	}





       SDL_Flip(screen);//P2
    }



       SDL_FillRect(screen,0,SDL_MapRGB(screen->format, 255,255,0));//P1??
       //SDL_Flip(screen);//P1
       SDL_FreeSurface(image);//P2
       SDL_FreeSurface(perso);//P3
Mix_FreeMusic(music); // free music//P5
       //pause = getchar();//P1 P2 P3
       return 0;
}
