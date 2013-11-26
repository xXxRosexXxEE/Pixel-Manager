/*
	Pixel_Manager - SDL 1.2
	
	Messing around with pixel-manipulation
	
	C++
	
	Written by Rose Hughes
	
	COPYRIGHT 2012
*/

#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <math.h>

SDL_Surface *Screen = SDL_SetVideoMode(640,480,32,  SDL_OPENGL |SDL_HWSURFACE | SDL_DOUBLEBUF);

bool Running = true;

Uint8 *keystate = SDL_GetKeyState(NULL);

float inc_dec_value = 0.0;
float first_value = 10;
float second_value = 20;
float third_value = 0;
int color_value = 0;
float x_fire_start = 0;
float y_fire_start = 0;
float x_fire_end = 0;
float y_fire_end = 0;


//Classic Put-Pixel Function
void PutPixel(int x, int y , int color, SDL_Surface *Surface) {
		unsigned int *framebuffer = static_cast<unsigned int*>(Surface->pixels);
		int offset = y * (Surface->pitch/sizeof(int));
		framebuffer[offset + x] = color;
}

struct Pixel_Manager {
		void TakeAwayResult_Drawn(int arg_one , int arg_two, int result_value, int color_value, SDL_Surface *Surface, int square_x_size, int square_y_size);
		
		void Fire_Spawn(int start_x, int start_y , int start_time, int life, int color , int fade_amount, SDL_Surface *Surface);
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

void Pixel_Manager::Fire_Spawn(int start_x, int start_y , int start_time, int life, int color , int fade_amount, SDL_Surface *Surface)
{
		int tick = SDL_GetTicks();

		unsigned int *framebuffer = static_cast<unsigned int*>(Surface->pixels);

		int offset = start_y * (Surface->pitch/sizeof(int));
		
		framebuffer[offset + start_x] = color;
	
}

class OpenGL_Manager
{
		public:
			void Start_OpenGL(bool Switch);
			void Render_OpenGL(bool Switch);
			void Load_OBJ(bool Switch);
			void Close_OpenGL(bool Switch);
};

void OpenGL_Manager::Start_OpenGL(bool Switch)
{
		glClearColor(0,0,0,1.0);
		glViewport(0,0,640,480);
		
		float DIFFUSE_LIGHT[]  = {  1.0f, 1.0f,  1.0f, 1.0f };
		float AMBIENT_LIGHT[]  = {  0.3f, 0.3f,  0.3f, 1.0f };
		float light_pos[]      = { -2.0f, 2.0f, 10.0f, 0.0f };
		
		glLightfv( GL_LIGHT0, GL_AMBIENT , AMBIENT_LIGHT);
		glLightfv( GL_LIGHT0, GL_DIFFUSE , DIFFUSE_LIGHT);
		glLightfv( GL_LIGHT0, GL_POSITION, light_pos);
		glEnable ( GL_LIGHT0 );
		glEnable ( GL_LIGHTING );
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45,640.0/480.0,1.0,500.0);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glColor3f(255,0,0);
		glTranslatef(0,0,-4);
};

void OpenGL_Manager::Render_OpenGL(bool Switch)
{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLUquadricObj* Sphere;
		Sphere=gluNewQuadric();
		gluQuadricNormals(Sphere, GLU_SMOOTH);
		gluSphere(Sphere,1,20,20);
		//gluDeleteQuadric(Sphere);
	
	std::cout << inc_dec_value << std::endl;

};

int main(int argc, char **argv)
{
	SDL_Event event;
	OpenGL_Manager OpenGL_Manager;
	
	OpenGL_Manager.Start_OpenGL(true);
	
while(Running == true) {
	
	OpenGL_Manager.Render_OpenGL(true);
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
	//Pixel_Manager.TakeAwayResult_Drawn(first_value,second_value,third_value,color_value,Screen,500,300);
	
	/*
	if(x_fire_start <= Screen->w && y_fire_start <= Screen->h)
		 x_fire_start+=1, y_fire_start+=1;
	else {
		x_fire_start=100, y_fire_start=100;	
	};
	
	Pixel_Manager.Fire_Spawn(x_fire_start,y_fire_start/2, 1000 , 100.0, 0xff0000 , 0.0, Screen);
	*/
	
	while(SDL_PollEvent(&event)) {
		switch(event.type)
		{
			case SDL_QUIT:
			return 0;
			break;
		}
	}	
		SDL_GL_SwapBuffers();
  }
}


