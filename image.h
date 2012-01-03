#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

using namespace std;

class Image{
	private:
		SDL_Surface * img;
	public:
		Image();
		Image(string);
		Image(SDL_Surface *);
		~Image();
		
		SDL_Surface * getSurface() const;
		int getWidth() const;
		int getHeight() const;
		
		void setSurface(string);
		void setSurface(SDL_Surface *);
		void setTransparent(Uint8 R, Uint8 G, Uint8 B);
};
#endif
