
%.o: %.cc
	g++ -c -std=c++11  $< -o $@ -I.
server: server.o configdata.o util.o tcp_relay.o eventloop.o  dns_resolver.o
	g++ -std=c++11 *.o -l:libunivalue.a  -lpthread -I. -o $@
clean:
	rm -f *.o
	rm -f server 
