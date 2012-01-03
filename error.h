#ifndef ERRORSOCK_H
#define ERRORSOCK_H

#include <iostream>
#include <string>

using namespace std;

class Error{
	public:
		Error();
		Error(string name);
		~Error();
};
#endif
