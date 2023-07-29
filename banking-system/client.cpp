//The client program reads requests from standard input and executes them.
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include "account.cpp"

void check_account_balance(int account_num, Account* accounts, std::string str) {
    if( *((int*)(accounts)) <= account_num) {
        std::cerr << "Invalid account number " << '\n';
		return;
    }

	if (str == "minimum") {
		std::cout << "minimum balance of account " << account_num << " : " <<  accounts[account_num + 1].get_min_balance() << std::endl;
	}

	else if (str == "current") {
    	std::cout << "current  balance of account: " << account_num << " : " << accounts[account_num + 1].get_balance() << std::endl;
	}

	else if (str == "max") {
    	std::cout << "Max balance of account: " << account_num << " : " << accounts[account_num + 1].get_max_balance() << std::endl;
	}
 }

 void freeze_account(int account_num, Account* accounts) {
    if (*((int*)(accounts)) <= account_num) {
        std::cerr << "Invalid account number " << '\n';
		return;
    }
	
    accounts[account_num + 1].set_frozen(true);
    std::cout << "Account " << account_num << " is frozen.\n";

 }

 void unfreeze_account(int account_num, Account* accounts) {
    if (*((int*)(accounts)) <= account_num) {
        std::cerr << "Invalid account number " << '\n';
        return;
    }

    accounts[account_num + 1].set_frozen(false);
    std::cout << "Account " << account_num << " is unfrozen.\n";

 }


void transfer(int account_num1, int account_num2, int amount, Account* accounts) {

    if (*((int*)accounts) <= account_num1 || *((int*)accounts) <= account_num2) {
		std::cerr << "Invalid account number " << '\n';
        return;
    }

	else if (accounts[account_num1 + 1].is_frozen() || accounts[account_num2 + 1].is_frozen()) {
        std::cout << "Cannot transfer funds from/to a frozen account.\n";
    }

    else if (accounts[account_num1 + 1].get_balance() >= amount) {

		if (accounts[account_num2 + 1].get_balance() + amount <= accounts[account_num2 + 1].get_max_balance()) {
            accounts[account_num1 + 1].set_balance(accounts[account_num1 + 1].get_balance() - amount);
            accounts[account_num2 + 1].set_balance(accounts[account_num2 + 1].get_balance() + amount);
            std::cout << "Transfer of " << amount << " from account " << account_num1
                     << " to account " << account_num2 << " successful.\n";
		}

		else {
			std::cout << "Transfer has been unseccessfull as it is limited maximum balance" << std::endl;
		}
    }

	else {

		std::cout << "Transfer of " << amount << " from account " << account_num1
                        << " to account " << account_num2 << " is unsuccessful, account has not enough money.\n";

	}

 }

 void withdraw_all_accounts(int amount, Account* accounts) {

    for (int i = 0; i < *((int*)accounts); ++i) {
		if (accounts[i + 1].is_frozen()) {
            continue;
        }

		else if(accounts[i + 1].get_balance() + amount <= accounts[i + 1].get_max_balance()) {
			accounts[i + 1].set_balance(accounts[i + 1].get_balance() + amount);
		}
		 
    } 

	std::cout << "All accounts except frozen ones are withdrawed successfully" << std::endl;

 }


  void deposite_all_accounts(int amount, Account* accounts) {
 
    for (int i = 0; i < *((int*)accounts); ++i) {
		if (accounts[i + 1].is_frozen()) {
        	continue;
        }

		else if(accounts[i + 1].get_balance() - amount >= accounts[i + 1].get_min_balance()) {
        	accounts[i + 1].set_balance(accounts[i + 1].get_balance() - amount);
 		}          

    }

	std::cout << "All accounts except frozen ones are deposited" << std::endl;
  
   }

	
   void set_min_max_balance(int account_num, Account* accounts, int min_bal, int max_bal) {
		if (*((int*)(accounts)) <= account_num) {
 	    	std::cerr << "Invalid account number " << '\n';
          	return;
      	}

		if (accounts[account_num + 1].get_balance() < min_bal || accounts[account_num + 1].get_balance() > max_bal) {
			std::cout << "Can not set, as account has more/ less balance that max/min balance" << std::endl; 
		}

		else {
			accounts[account_num + 1].set_max_balance(max_bal);
			accounts[account_num + 1].set_min_balance(min_bal);
			std::cout << "min/max balance has seted" << std::endl;
		}
	}


  void run(Account* accounts) {
	while (true) {
		std::string command;
		std::getline(std::cin, command);

		if (command == "check current balance of account") {
			std::cout << "please, enter account number: " << std::endl;
			int account_num;
			std::cin >> account_num;
			std::cin.ignore();
			std::string cur = "current";
			check_account_balance(account_num, accounts, cur);
		}

		else if (command == "check minimum balance of account") {
			std::cout << "please, enter account number: " << std::endl;
			int account_num;
			std::cin >> account_num;
			std::cin.ignore();
			std::string min = "minimum";
			check_account_balance(account_num, accounts, min);
		}

		else if (command == "check maximum balance of account") {
			std::cout << "please, enter account number: " << std::endl;
			int account_num;
			std::cin >> account_num;
			std::cin.ignore();
			std::string max = "max";
			check_account_balance(account_num, accounts, max);
		}

		else if (command == "freeze account") {
			std::cout << "please, enter account number you want to freeze: " << std::endl;
			int account_num;
			std::cin >> account_num;
			std::cin.ignore();
			freeze_account(account_num, accounts);
		}

		else if (command == "unfreeze account") {
			std::cout << "please, enter account number you want to unfreeze: " << std::endl;
			int account_num;
			std::cin >> account_num;
			std::cin.ignore();
			unfreeze_account(account_num, accounts);
		}

		else if (command == "transfer") {
			std::cout << "please, input account number from which transfer will be" << std::endl;
			int acc1;
			std::cin >> acc1;
			std::cin.ignore();
			std::cout << "please, input account number to whom transfer will be" << std::endl;
			int acc2;
			std::cin >> acc2;
			std::cin.ignore();
			std::cout << "please, input amount of money" << std::endl;
			int amount;
			std::cin >> amount;
			std::cin.ignore();
			transfer(acc1, acc2, amount, accounts);

		}

		else if (command == "withdraw all accounts") {
			std::cout << "please, input amount of money" << std::endl;
			int amount;
			std::cin >> amount;
			std::cin.ignore();
			withdraw_all_accounts(amount, accounts);
		}

		else if (command == "deposite all accounts") {
			std::cout << "please, input amount of money" << std::endl;
			int amount;
			std::cin >> amount;
			std::cin.ignore();
			deposite_all_accounts(amount, accounts);
		}
		
		else if (command == "set min and max balance") {
			std::cout << "please, enter the number of account" << std::endl;
			int account_num;
			std::cin >> account_num;
			std::cin.ignore();
			std::cout << "please, input min balance to change" << std::endl;
			int min_bal;
			std::cin>> min_bal;
			std::cin.ignore();
			std::cout << "please, input max balance to change" << std::endl;
            int max_bal;
            std::cin>> max_bal;
			std::cin.ignore();
			set_min_max_balance(account_num, accounts, min_bal, max_bal);
		}

	   	else if (command == "quit") {
			return;
		}

		else {
			std::cerr << "Invalid command: please try again " <<  std::endl;      
		}
	  }
  }

int main(int argc, char** argv) {
    key_t key = ftok(".", 'B');

    if (key == -1) {
    	perror("ftok");
    	return 1;
    }

    // Get the shared memory segment ID
	int shmid = shmget(key, 0, 0);
	if (shmid == -1) {
    	perror("shmget");
    	return 1;
	}

	//attach
	Account* accounts = (Account*)shmat(shmid, nullptr, 0);
	std::cout << "Here is the operations that you can do: " << std::endl;
    std::cout << ">check current balance of account" << '\n' << ">check minimum balance of account" << '\n' << ">check maximum balance of account" << '\n' << ">freeze account" << '\n' << ">unfreeze account" << '\n' << ">transfer" << '\n' << ">withdraw all accounts" << '\n' << ">deposite all accounts" << '\n' << ">set min and max balance" << '\n' << ">quit" << std::endl;

	run(accounts);
}

