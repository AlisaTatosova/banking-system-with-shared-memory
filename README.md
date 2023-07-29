# banking-system-with-shared-memory

**The bank is stored in shared memory, work with the bank should not violate the integrity of the data.**
A transparent bank keeps N accounts with numbers from 0 to N-1. Each account has:
* current balance -- signed integer (balance can be negative)
* minimum possible balance -- signed integer
* maximum possible balance -- signed integerr
* is the account frozen, that is, is it allowed to change the current balance

The initializer program creates a new bank with N (command line argument) unfrozen accounts with zero balance, zero minimum balance, and some positive maximum possible balance.

The deinitializer program destroys the existing bank.

The client program reads requests from standard input and executes them. The request is one line from the input stream. So the bank is absolutely transparent, any client can perform any valid operations on any accounts.

Requests are of the following form:
* display the current/minimum/maximum account balance with the given number A
* freeze/unfreeze an account with a given number A
* transfer amount X from account A to account B, X > 0
* credit to all accounts / write off from all accounts X units
* set the given minimum/maximum possible balance X for the account with the given number A
If it is impossible to perform operations (for example, the account is frozen, the operation will lead to an overrun of the allowable credit limit, incorrect account number, incorrect data entry, etc.), the program politely displays a message about this and reads the next request. If the transaction is successful, display a message about it.

The Makefile must contain the following targets, with their dependencies correctly described:
*for building each object module (.o)
*for release builds (without including debug information)
*for debug build and running tests with valgrind (memcheck, helgrind), checking the correctness of the result
*for assembly to measure coverage on a test set
