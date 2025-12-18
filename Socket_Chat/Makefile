CLIENT_BIN = client
CLIENT_SRC = client.c

SERVER_BIN = server
SERVER_SRC = server.c

LIBS = utils.c

all: server client

server:
	gcc -g $(SERVER_SRC) $(LIBS) -o $(SERVER_BIN)

client: 
	gcc -g $(CLIENT_SRC) $(LIBS) -o $(CLIENT_BIN)

clean_client:
	rm -rf $(CLIENT_BIN)

clean_server:
	rm -rf $(SERVER_BIN)

fclean: clean_client clean_server

re: fclean all

