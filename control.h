#ifndef CONTROL_H
#define CONTROL_H


#include <vector>
#include "model.h"

using namespace std;

class Control{
	private:
		bool controlWin(Model *) const;
		
	public:
		Control();
		~Control();
		
		bool isFinish( Model * ) const;
		int winner(Model *) const;
};
#endif
