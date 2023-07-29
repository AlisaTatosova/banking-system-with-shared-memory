//the initializer creates a new bank wint N accounts
#include "account.cpp"
#include <sys/shm.h>
#include <iostream>

void initializer(int n) {

	key_t key = ftok(".", 'B');
    if (key == -1) {
    	perror("ftok");
        exit(1);
    }

    int shmid = shmget(key, n * sizeof(Account), IPC_CREAT | 0666);
    if (shmid == -1) {
    	std::cerr << "Failed to create shared memory segment." << std::endl;
        exit(1);;
    }

    // Attach shared memory segment to the process
    Account* accounts = (Account*)shmat(shmid, nullptr, 0);
    if (accounts == (void*)-1) {
    	std::cerr << "Failed to attach shared memory segment." << std::endl;
        exit(1);
    }
	
	*((int*)accounts) = n;
    for (int i = 1; i <= n; ++i) {
        accounts[i] = Account(0);
    }
		std::cout << "The bank is initialized with " << n << " accounts" << std::endl;
}

int main(int argc, char** argv) {
    int num = std::stoi(argv[1]);
    initializer(num);
}
