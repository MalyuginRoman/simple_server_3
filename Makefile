all:
	g++ -std=c++17 server.c -o server
	g++ -std=c++17 client.c -lcppunit -o client
test:
	chmod +x server
	./client
clean:
	$(RM) server client
