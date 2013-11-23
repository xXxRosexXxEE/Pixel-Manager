#include <SDL/SDL.h>
#include <iostream>
#include <math.h>

SDL_Surface *Screen = SDL_SetVideoMode(640,480,32, SDL_HWSURFACE | SDL_DOUBLEBUF);

bool Running = true;

Uint8 *keystate = SDL_GetKeyState(NULL);

float inc_dec_value = 0.0;
float first_value = 10;
float second_value = 20;
float third_value = 0;
int color_value = 0;

void PutPixel(int x, int y , int color, SDL_Surface *Surface) {
		unsigned int *framebuffer = static_cast<unsigned int*>(Surface->pixels);
		int offset = y * (Surface->pitch/sizeof(int));
		framebuffer[offset + x] = color;
}

struct Pixel_Manager {
		void TakeAwayResult_Drawn(int arg_one , int arg_two, int result_value, int color_value, SDL_Surface *Surface, int square_x_size, int square_y_size);
};

//the results of a take away equation becomes the blue drawn pixels 
void Pixel_Manager::TakeAwayResult_Drawn(int arg_one , int arg_two, int result_value, int color_value, SDL_Surface *Surface, int square_x_size, int square_y_size) {
		for(int x = 0; x<= square_x_size; x++){
				for(int y = 0; y<= square_y_size; y++) {
					result_value = arg_two - arg_one;
					if(result_value  <= y*x) {
						color_value=0xff0000;
						PutPixel(x,y, color_value, Surface); //std::cout << "red" << std::endl;
					} else {
						color_value=0x0000ff;
						PutPixel(x,y, color_value, Surface); //std::cout << "Blue" << std::endl;	
				    }		
				}
			}
		}

int main(int argc, char **)
{
	SDL_Event event;
	Pixel_Manager Pixel_Manager;

while(Running == true) {
	if(keystate[SDLK_UP])
		inc_dec_value+=1.0;
	if(!keystate[SDLK_UP])
		inc_dec_value+=0.0;
	
	if(keystate[SDLK_DOWN])
		inc_dec_value-=1.0;
	if(!keystate[SDLK_DOWN])
		inc_dec_value-=0.0;
		
		if(keystate[SDLK_END])
			return 0;
		
	SDL_FillRect(Screen,NULL,0x000000);
	
	Pixel_Manager.TakeAwayResult_Drawn(first_value,second_value,third_value,color_value,Screen,500,300);
	
	while(SDL_PollEvent(&event)) {
		switch(event.type)
		{
			case SDL_QUIT:
			return 0;
			break;
		}
	}	SDL_Flip(Screen);
  }
}


