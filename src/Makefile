
%.o: %.cc
	g++ -c -std=c++11  $< -o $@
server: server.o configdata.o util.o 
	g++ -std=c++11 *.o -l:libunivalue.a
