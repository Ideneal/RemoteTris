#include "model.h"

Model::Model(){
	//init grid to 0
	vector<int> lol(3,0); // tre volte 0
	for(int i=0; i<3; i++)
		this->grid.push_back(lol);
}

Model::~Model(){
}

vector< vector<int> > Model::getGrid() const{
	return this->grid;
}

int Model::getPosition(unsigned int x, unsigned int y) const{
	if(x>2 || y>2)
		return -1; //error
	return this->grid[x][y];
}

bool Model::isFree(unsigned int x, unsigned int y) const{
	if(x>2 || y>2)
		return false; //error
	return (this->grid[x][y] == 0);
}

void Model::setPosition(unsigned int x, unsigned int y, unsigned int value){
	if(x>2 || y>2 || value<1 || value>2)
		return ;  //error
	if(this->grid[x][y] == 0)
		this->grid[x][y] = value;
}
