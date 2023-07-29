//deinitializer destroys bank
#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "account.cpp"

void deinitializer() {
    key_t key = ftok(".", 'B');
    if (key == -1) {
        perror("ftok");
        exit(1);
    }
    // Get the shared memory segment ID
    int shmid = shmget(key, 0, 0);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }
    // Detach shared memory segment
    shmdt((Account*)shmat(shmid, nullptr, 0));

    //delete
    if (shmctl(shmid, IPC_RMID, nullptr) == -1) {
        perror("shmctl");
        exit(1);
    }

    std::cout << "Bank destroyed" << std::endl;

}

int main() {
	deinitializer();
}
