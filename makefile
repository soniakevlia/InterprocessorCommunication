all: conn_mmap host

conn_mmap: conn_mmap.cpp
	g++ -Wall -O3  conn_mmap.cpp -c -lpthread
host: host.cpp
	g++ -Wall -O3  host.cpp -o host -lpthread

clean:
	rm -f conn_mmap host
