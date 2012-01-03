#include "socket.h"

Socket::Socket() throw(){
	this->newsock = -1;
	
	this->host.sin_family = AF_INET;
	this->host.sin_port = htons(1234); //default port
	this->host.sin_addr.s_addr = INADDR_ANY;
	
	if( (this->sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
		throw Error("socket");
}

Socket::Socket(int port) throw(){
	this->newsock = -1;
	
	this->host.sin_family = AF_INET;
	this->host.sin_port = htons(port);
	this->host.sin_addr.s_addr = INADDR_ANY;
	
	if( (this->sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
		throw Error("socket");
}

Socket::Socket(string & nhost, int port) throw(){
	this->newsock = -1;
	
	this->host.sin_family = AF_INET;
	this->host.sin_port = htons(port);
	this->host.sin_addr.s_addr = inet_addr( (this->getHostByName(nhost)).c_str() );
	
	if( (this->sock = socket(PF_INET, SOCK_STREAM, 0)) < 0 )
		throw Error("socket");
}

Socket::~Socket(){
	this->Close();
}

string Socket::getHostByName(string & nhost) throw(){
	struct hostent * hp = gethostbyname( nhost.c_str() );
	struct in_addr * addr;
	
	if(hp == NULL)
		throw Error("get host by name");
	
	addr = (struct in_addr *) (hp->h_addr);
	
	//string address = * inet_ntoa(* addr);
	return string( inet_ntoa(* addr) );
}

void Socket::Bind() throw(){
	if( bind(this->sock, (struct sockaddr *) &this->host, sizeof( struct sockaddr ) ) < 0 )
		throw Error("bind");
}

void Socket::Listen(int maxcon) throw(){
	if( listen(this->sock, maxcon) < 0 )
		throw Error("listen");
}

void Socket::Accept() throw(){
	socklen_t len = sizeof(struct sockaddr);
	if( this->newsock < 0 )
		if( (this->newsock = accept(this->sock, (struct sockaddr *)&this->client, &len ) ) < 0 )
			throw Error("accept");
}

void Socket::Connect() throw(){
	if( connect(this->sock, (struct sockaddr *)&this->host, sizeof(struct sockaddr)) < 0 )
		throw Error("connect");
}

void Socket::Send(string & msg) throw(){
	if(this->newsock < 0){
		if(send(this->sock, msg.c_str(), msg.length(), 0) < 0)
			throw Error("send");
	}else{
		if(send(this->newsock, msg.c_str(), msg.length(), 0) < 0)
			throw Error("send");
	}
}

string Socket::Recv() throw(){
	
	int length;
	char buf;
	string msg;
	if(this->newsock < 0){
	
		if ( (length = recv(this->sock, &buf, 1, 0) ) < 0)
			throw Error("recv");
		while(length > 0 && buf != '\n'){
			msg += buf;
			length = recv(this->sock, &buf, 1, 0);
		}
	}else{
		length = recv(this->newsock, &buf, 1, 0);
		while(length > 0 && buf != '\n'){
			msg += buf;
			length = recv(this->newsock, &buf, 1, 0);
		}
	}
	
	return msg;
}

void Socket::Close(){
	if(this->newsock > 0)
		close(this->newsock);
	close(this->sock);
}
