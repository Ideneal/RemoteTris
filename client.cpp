//Tris Client

#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "model.h"
#include "control.h"
#include "view.h"
#include "image.h"
#include "socket.h"

using namespace std;

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 670
#define SCREEN_DEPTH 32

void show(Model * grid, View * Screen, Image * bg, Image * px, Image * po, int turn, TTF_Font * font){
	Screen->drawImage(bg);
	vector< vector<int> > gr = grid->getGrid();
	for(int x=0; x<3; x++){
		for(int y=0; y<3; y++){
			switch(grid->getPosition(x,y)){
				case X:
					Screen->drawImage(px, x * 200, y * 200);
					break;
				case O:
					Screen->drawImage(po, x * 200, y * 200);
					break;
				case 0:
					break;
			}
		}
	}
	string result = "Player O : ";
	if(turn % 2 != 0)
		result += "e' il mio turno";
	else
		result += "attendi...";
	
	Screen->putstring(result.c_str(), font, 10, 630, 0xff, 0x00, 0x00);
}

int main(int argc, char * argv[]){
	if(argc != 3){
		cout << "Usage: "<< argv[0] <<" <host> <port>"<<endl;
		exit(1);
	}
	
	//inizializzazione grafica
	View * Screen = new View(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_DEPTH);
	Image * black = new Image("black.bmp");
	Image * background = new Image("background.bmp");
	Image * playerX = new Image("playerx.bmp");
	Image * playerO = new Image("playero.bmp");
	playerX->setTransparent(0, 0, 0);
	playerO->setTransparent(0, 0, 0);
	SDL_Event * event = new SDL_Event();
	TTF_Init();
	TTF_Font * font = TTF_OpenFont("Bandal.ttf", 28);
	if(font == NULL){
		cout << "Impossibile caricare il font : "<<SDL_GetError()<<endl;
		exit(1);
	}
	
	
	bool click = false;
	bool end = false;
	int port = atoi(argv[2]);
	string host(argv[1]);
	string rcv;
	Socket * srv = new Socket(host, port);
	int turn = 0, x, y;
	Model * grid = new Model();
	Control * ctrl = new Control();
	
	cout << "waiting..."<<endl;
	srv->Connect();
	cout << "connessione accettata"<<endl;
	
	string trn;
	if( (trn = srv->Recv()) == "")
		end = true;
	turn = atoi(trn.c_str());
	
	while(!ctrl->isFinish(grid) && !end){
		show(grid, Screen, background, playerX, playerO,turn, font);
		
		//se è il turno del client
		if(turn % 2 != 0){
			
			while(SDL_PollEvent(event) && !click){
     				if(event->type == SDL_QUIT)
     					end = true;
     				if(event->type == SDL_MOUSEBUTTONDOWN){
     					if(event->button.button == SDL_BUTTON_LEFT){
     						x = event->button.x;
     						y = event->button.y;
     						
     						if(x < 200)	x=0;
     						else if(x<400)	x=1;
     						else		x=2;
     						
     						if(y < 200)	y=0;
     						else if(y<400)	y=1;
     						else		y=2;
     						
     						
     						if(grid->isFree(x,y)){
							grid->setPosition(x,y,O);
							turn++;
							stringstream ss(stringstream::in | stringstream::out);
							ss << x << y << "\n";
							string lol = ss.str();
							srv->Send(lol);
							click = true;
						}
     					}
     				}
     			}
			
		}else{
			if( (rcv = srv->Recv()) == "" )
				end = true;
			else{
				turn++;
				click = false;
			}
			
			int tmp = atoi(&rcv[0]);
			y = tmp % 10;
			tmp /= 10;
			x = tmp % 10;
			
			grid->setPosition(x,y,X);
		}
	}
	
	show(grid, Screen, background, playerX, playerO,turn, font);
	string result;
	if(end){
		cout << "Connection interrupt"<<endl;
		exit(1);
	}
	if(ctrl->winner(grid) < 0){
		cout << "error: winner"<<endl;
		exit(1);
	}
	if(ctrl->winner(grid) == 0)
		result = "Partita Patta";
	if(ctrl->winner(grid) == X)
		result = "Il player X e' il vincitore :D";
	if(ctrl->winner(grid) == O)
		result = "Il player O e' il vincitore :D";
	
	Screen->drawImage(black, 0, 0);
	Screen->putstring(result.c_str(), font, 150, 330, 0xff, 0x00, 0x00);
	
	click = false;
	while(!click){
		while(SDL_PollEvent(event)){
     			switch (event->type){
     				case SDL_QUIT :
     				case SDL_MOUSEBUTTONDOWN :
     				case SDL_KEYDOWN :
     					click = true;
     					break;
     			}
     		}
     	}
	
	srv->Close();
	delete event;
	delete playerO;
	delete playerX;
	delete background;
	delete black;
	delete Screen;
	delete srv;
	delete ctrl;
	delete grid;
	return 0;
}
