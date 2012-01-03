#include "image.h"

Image::Image(){
	this->img = NULL;
}

Image::Image(string name){
	this->setSurface(name);
}

Image::Image(SDL_Surface * name){
	this->setSurface(name);
}

Image::~Image(){
	SDL_FreeSurface(this->img);
}

SDL_Surface * Image::getSurface() const{
	return this->img;
}

int Image::getWidth() const{
	if(this->img != NULL)
		return this->img->w;
	else
		return 0;
}

int Image::getHeight() const{
	if(this->img != NULL)
		return this->img->h;
	else
		return 0;
}

void Image::setSurface(string name){
	SDL_Surface * oldimg = IMG_Load(name.c_str());
	
	if(oldimg == NULL){
		cout << "Error to load image : "<< SDL_GetError() << endl;
		return;
	}
	
	this->img = SDL_DisplayFormat(oldimg);
	
	if(this->img == NULL){
		cout << "Error to convert image : " << SDL_GetError() << endl;
		return;
	}
	
	SDL_FreeSurface(oldimg);
}

void Image::setSurface(SDL_Surface * name){
	this->img = name;
}

void Image::setTransparent(Uint8 R, Uint8 G, Uint8 B){
	Uint32 colorkey = SDL_MapRGB(this->img->format, R, G, B);
	SDL_SetColorKey(this->img, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);
}
