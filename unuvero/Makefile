all: magni_auth

magni_auth : magni_auth.o
	g++ -Wall -std=c++11 -O0 -g3 magni_auth.o -o magni_auth -rdynamic -Wl,-Bstatic -lboost_program_options -lboost_thread -lboost_date_time -lboost_regex -lboost_system -lboost_filesystem -lboost_chrono -Wl,-Bdynamic -lpthread -L /usr/local/lib -lcppnetlib-uri -lcppnetlib-client-connections -ljsoncpp -lssl -lcrypto -lrt 

magni_auth.o : magni_auth.cpp
	g++ -Wall -std=c++11 -O0 -g3 -DBOOST_NETWORK_ENABLE_HTTPS  -o magni_auth.o -c magni_auth.cpp
