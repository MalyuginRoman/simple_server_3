all:
	g++ -std=c++17 server.c -o server
	g++ -std=c++17 client.c -o client
	g++ -std=c++17 test_server.cpp -lcppunit -o test_server
test:
	chmod +x server
	./server
	./client
	./test_server
clean:
	$(RM) server client test_server
