#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "error.h"

#include <string>
#include <sstream>
#include <vector>

using namespace std;

class Socket{
	private:
		int sock, newsock;
		sockaddr_in host, client;
	public:
		Socket() throw();
		Socket(int port) throw();
		Socket(string & nhost, int port) throw();
		~Socket();
		
		string getHostByName(string & nhost) throw();
		
		void Bind() throw();
		void Listen(int maxcon) throw();
		void Accept() throw();
		
		void Connect() throw();
		
		void Send(string & msg) throw();
		string Recv() throw();
		
		void Close();
};
#endif
		
