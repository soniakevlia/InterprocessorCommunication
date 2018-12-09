mmap: conn_mmap host
mq: conn_mq host
pipe: conn_pipe host
seg: conn_seg host
shm: conn_shm host

conn_mmap: conn/conn_mmap.cpp
	g++ -Wall -O3  conn/conn_mmap.cpp -c -lpthread

conn_mq: conn/conn_mq.cpp
	g++ -Wall -O3  conn/conn_mq.cpp -c -lpthread

conn_pipe: conn/conn_pipe.cpp
	g++ -Wall -O3  conn/conn_pipe.cpp -c -lpthread

conn_seg: conn/conn_seg.cpp
	g++ -Wall -O3  conn/conn_seg.cpp -c -lpthread

conn_shm: conn/conn_shm.cpp
	g++ -Wall -O3  conn/conn_shm.cpp -c -lpthread

host: host.cpp
	g++ -Wall -O3  host.cpp -o host -lpthread

clean:
	rm -f conn_mmap host
