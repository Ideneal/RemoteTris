#ifndef MODEL_H
#define MODEL_H

#define		X	1
#define 	O	2

#include <vector>

using namespace std;

class Model{
	private:
		vector< vector<int> > grid;
		
		//bool end;
		//int winner;
	public:
		Model();
		~Model();
		
		vector< vector<int> > getGrid() const;
		int getPosition(unsigned int, unsigned int) const;
		bool isFree(unsigned int,unsigned int) const;
		
		void setPosition(unsigned int, unsigned int, unsigned int);
};
#endif
