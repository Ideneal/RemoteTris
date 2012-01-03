#include "control.h"

Control::Control(){
}

Control::~Control(){
}

bool Control::controlWin(Model * mod) const{
	vector< vector<int> > lol = mod->getGrid();
	return (   (lol[0][0] == lol[0][1] && lol[0][1] == lol[0][2] && lol[0][0] != 0) ||
		   (lol[1][0] == lol[1][1] && lol[1][1] == lol[1][2] && lol[1][0] != 0) ||
		   (lol[2][0] == lol[2][1] && lol[2][1] == lol[2][2] && lol[2][0] != 0) ||
		   (lol[0][0] == lol[1][0] && lol[1][0] == lol[2][0] && lol[0][0] != 0) ||
		   (lol[0][1] == lol[1][1] && lol[1][1] == lol[2][1] && lol[0][1] != 0) ||
		   (lol[0][2] == lol[1][2] && lol[1][2] == lol[2][2] && lol[0][2] != 0) ||
		   (lol[0][0] == lol[1][1] && lol[1][1] == lol[2][2] && lol[1][1] != 0) ||
		   (lol[0][2] == lol[1][1] && lol[1][1] == lol[2][0] && lol[1][1] != 0) );
}

bool Control::isFinish(Model * mod) const{
	bool end=true;
	if(!this->controlWin(mod))
		for(int i=0; i<3 && end; i++)
			for(int j=0; j<3 && end; j++)
				if(mod->isFree(i,j)) end=false;
	return end;
}

int Control::winner(Model * mod) const{
	if(!this->isFinish(mod))
		return -1; //error
	if(!this->controlWin(mod))
		return 0; //pareggio
		
	vector< vector<int> > lol = mod->getGrid();
	
	for(int i=0; i<3; i++)
		if( (lol[i][0] == lol[i][1] && lol[i][1] == lol[i][2] && lol[i][0] != 0) )
			return lol[i][0];
	for(int i=0; i<3; i++)
		if( (lol[0][i] == lol[1][i] && lol[1][i] == lol[2][i] && lol[0][i] != 0) )
			return lol[0][i];
	if( (lol[0][0] == lol[1][1] && lol[1][1] == lol[2][2] && lol[1][1] != 0) ||
	    (lol[0][2] == lol[1][1] && lol[1][1] == lol[2][0] && lol[1][1] != 0)   )
	    		return lol[1][1];
}
