#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
public:
    Account(int balance, int min_balance = 0, int max_balance = 1000000, bool is_frozen = false) : 
        balance{balance}, min_balance{min_balance}, max_balance{max_balance}, frozen(is_frozen) {}

  
    ~Account() {}

    int get_balance() const {
        return balance;
    }

    int get_min_balance() const {
        return min_balance;
    }

    int get_max_balance() const {
        return max_balance;
    }

    bool is_frozen() const {
        return frozen;
    }

    void set_balance(int balance) {
        this -> balance = balance;
    }

    void set_min_balance(int min_bal) {
        this -> min_balance = min_bal;
    }
 
    void set_max_balance(int max_bal) {
        this -> max_balance = max_bal;
    }

    void set_frozen(bool is_frozen) {
        frozen = is_frozen;
    }

private:
    int balance;
    int min_balance;
    int max_balance;
    bool frozen;
};

#endif

