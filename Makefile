CC = g++
LIBRERIE = -lSDL -lSDL_image -lSDL_ttf

SERVER = server.cpp
BINS = server

CLIENT = client.cpp
BINC = client

compile: model.o error.o image.o control.o view.o socket.o
	$(CC) -c model.cpp error.cpp image.cpp control.cpp view.cpp socket.cpp
	
	@echo "inizio compilazione..."
	$(CC) -o $(BINC) $(CLIENT) $^ $(LIBRERIE)
	$(CC) -o $(BINS) $(SERVER) $^ $(LIBRERIE)

clean: model.o error.o image.o control.o view.o socket.o
	rm $^
