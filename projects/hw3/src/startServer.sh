

# Compile and start server
gcc serverDecoder.c -lpthread -o serverDecoder
gcc ./layers/physical.c ./layers/data_link.c ./layers/application.c server.c -o server
./server
