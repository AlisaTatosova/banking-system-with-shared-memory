CFLAGS = -Wall -Werror -DRELEASE
programms = target1 target2

all: $(programms) target3

target1: initializer.o
	g++ $(CFLAGS) initializer.o -o target1

target2: client.o
	g++ $(CFLAGS) client.o -o target2

target3: deinitializer.o
	g++ $(CFLAGS) deinitializer.o -o target3

init.o: initializer.cpp account.cpp
	g++ $(CFLAGS) -c initializer.cpp

client.o: client.cpp account.cpp
	g++ $(CFLAGS) -c client.cpp

deinit.o: deinitializer.cpp account.cpp
	g++ $(CFLAGS) -c deinitializer.cpp

clean: 
	rm -rf *.o main

