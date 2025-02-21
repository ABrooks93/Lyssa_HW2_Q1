#include <iostream>
using namespace std;

// 2.a struct created for Check.
struct Check {
    int CheckNum;
    string CheckMemo;
    double CheckAmount = -1; 

    friend ostream & operator<<(ostream &var, Check &c);

    bool operator>(const Check &c);

}; 

class CheckBook {
private:
    // 2.b private variables declared for CheckBook.
    int numOfChecks, checkBookSize;
    float balance, lastDeposit;
    Check* chkPtr

public:
    // 2.something getters and setters
    int getNumOfChecks() {
        return numOfChecks;
    }
    int getCheckBookSize() {
        return checkBookSize;
    }
    float getBalance() {
        return balance;
    }
    float getLastDeposit() {
        return lastDeposit;
    }
    void setNumOfChecks(int num) {
        numOfChecks = num;
    }
    void setCheckBookSize(int size) {
        checkBookSize = size;
    }
    void setBalance(float bal) {
        balance = bal;
    }
    void setLastDeposit(float deposit) {
        lastDeposit = deposit;
    }
    //2.something+1 default constructor
    CheckBook() {
        numOfChecks = 0;
        checkBookSize = 4;
        balance = 0;
        chkPtr = nullptr;
    }
    //2.8 constructor with parameters
    CheckBook(int num, int size, float bal) {
        numOfChecks = num;
        checkBookSize = size;
        balance = bal;
        chkPtr = nullptr;
    }
    //2.9 destructor
    ~CheckBook() {
        delete[] chkPtr;
    }
    //2.10 copy constructor
    CheckBook(const CheckBook &cb) {
        numOfChecks = cb.numOfChecks;
        checkBookSize = cb.checkBookSize;
        balance = cb.balance;
        chkPtr = new Check[checkBookSize];
        for (int i = 0; i < numOfChecks; i++) {
            chkPtr[i] = cb.chkPtr[i];
        }
    }

    //2.11 overloaded assignment operator declaration
    bool operator=(const Checkbook &cb);

    //2.12 void deposit function
    void deposit(float amount) {
        balance += amount;
        lastDeposit = amount;
    }

    //2.13 bool writeCheck( Check c_amount) function
    bool writeCheck(Check& c_amount) {
        if (c_amount.CheckAmount <= balance) {
            string memos[] = {"wedding", "baby shower", "pizza", "children hospital", "barber shop", "plumber", "hobbit", "trudo"};
            int numMemos = sizeof(memos) / sizeof(memos[0]);

            cout << "Enter check amount: ";
            cin >> c_amount.CheckAmount;

            if (c_amount.CheckAmount > balance) {
                cout << "Check amount exceeds remaining balance. Check not processed.\n";
                return false;
            }

            cin.ignore();
            cout << "Enter check memo (or press Enter for a random memo): ";
            string userMemo;
            getline(cin, userMemo);

            if (userMemo.empty()) {
                srand(time(0));
                int randomIndex = rand() % numMemos;
                c_amount.CheckMemo = memos[randomIndex];
            } else {
                c_amount.CheckMemo = userMemo;
            }

            c_amount.CheckNum = numOfChecks + 1;

            balance -= c_amount.CheckAmount;
            checks[numOfChecks] = c_amount; // Direct assignment to vector element
            numOfChecks++;

            //c Check if half the checkbook is full
            if (numOfChecks >= checkBookSize / 2) {
                // Double the checkbook size
                int newSize = checkBookSize * 2;
                checks.resize(newSize);  // resize automatically copies existing elements
                checkBookSize = newSize;

                cout << "WARNING: Checkbook is half full. A new checkbook has been ordered.\n";
            }

            cout << "Check written successfully.\n";
            return true;
        } else {
            cout << "Insufficient funds.\n";
            return false;
        }

        //d 
        void displayChecks() const {
            if (numOfChecks == 0) {
                cout << "No checks have been written yet.\n";
                return;
            }
    
            vector<Check> checksCopy = checks; // Create a copy so we don't reverse the original order
            checksCopy.resize(numOfChecks); // Only consider the checks that have been written.
    
            reverse(checksCopy.begin(), checksCopy.end()); // Reverse the order of the *copy*
    
            for (const auto& check : checksCopy) {
                cout << check << endl; // Use the overloaded << operator
            }
        }
    }

};

//2.11 overloaded assignment operator
bool CheckBook::operator=(const CheckBook &cb) {
    if (this == &cb) {
        return true;
    }
    delete[] chkPtr;
    numOfChecks = cb.numOfChecks;
    checkBookSize = cb.checkBookSize;
    balance = cb.balance;
    chkPtr = new Check[checkBookSize];
    for (int i = 0; i < numOfChecks; i++) {
        chkPtr[i] = cb.chkPtr[i];
    }
    return true;
}

ostream & operator<<(ostream &var, Check &c) {
    var<<c.CheckNum<<" "<<c.CheckMemo<<" "<<c.CheckAmount;
    return var;
}

// bool is returning true or false when check is compared to a float variable.
bool Check::operator>(Float &f) {
    return CheckAmount>f;
}

int main();
