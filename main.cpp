
/*************************************************************************
** Author : Alyssa Brooks
** Program : hw2, q2
** Date Created : February 19, 2025
** Date Last Modified : February 20, 2025
** Usage : Checkbook
**
** Problem:
Defines Check and Checkbook 
Write Check Method 
Display Method 
*************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

using namespace std;

struct Check {
    int CheckNum;
    string CheckMemo;
    double CheckAmount = -1;

    friend ostream& operator<<(ostream& var, Check& c);

    bool operator>(const Check &c);

}; 

ostream & operator<<(ostream &var, Check &c) {
    var<<c.CheckNum<<" "<<c.CheckMemo<<" "<<c.CheckAmount;
    return var;
}

bool Check::operator>(const Check& c) {
    return CheckAmount > c.CheckAmount;
}

bool Check::operator>(float f) {
    return CheckAmount > f;
}

// CheckBook method implementations:

float CheckBook::getBalance() const { return balance; }
float CheckBook::getLastDeposit() const { return lastDeposit; }
int CheckBook::getNumOfChecks() const { return numOfChecks; }
int CheckBook::getCheckBookSize() const { return checkBookSize; }
void CheckBook::setBalance(float bal) { balance = bal; }
void CheckBook::setLastDeposit(float deposit) { lastDeposit = deposit; }
void CheckBook::setNumOfChecks(int num) { numOfChecks = num; }
void CheckBook::setCheckBookSize(int size) { checkBookSize = size; }

CheckBook::CheckBook() : balance(0.0), lastDeposit(0.0), numOfChecks(0), checkBookSize(4) {
    chkPtr = new Check[checkBookSize];
}

CheckBook::CheckBook(float bal) : balance(bal), lastDeposit(0.0), numOfChecks(0), checkBookSize(2) {
    chkPtr = new Check[checkBookSize];
}

CheckBook::~CheckBook() {
    delete[] chkPtr;
}

CheckBook::CheckBook(const CheckBook& cb) : balance(cb.balance), lastDeposit(cb.lastDeposit), numOfChecks(cb.numOfChecks), checkBookSize(cb.checkBookSize) {
    chkPtr = new Check[checkBookSize];
    for (int i = 0; i < numOfChecks; i++) {
        chkPtr[i] = cb.chkPtr[i];
    }
}

CheckBook& CheckBook::operator=(const CheckBook& cb) {
    if (this != &cb) {
        delete[] chkPtr;
        balance = cb.balance;
        lastDeposit = cb.lastDeposit;
        numOfChecks = cb.numOfChecks;
        checkBookSize = cb.checkBookSize;
        chkPtr = new Check[checkBookSize];
        for (int i = 0; i < numOfChecks; i++) {
            chkPtr[i] = cb.chkPtr[i];
        }
    }
    return *this;
}

void CheckBook::deposit(float amount) { balance += amount; lastDeposit = amount; }

bool CheckBook::writeCheck(Check& c_amount) {
    if (c_amount > balance) {  // Using overloaded > operator
        cout << "Insufficient funds.\n";
        return false;
    }

    string memos[] = {"wedding", "baby shower", "pizza", "children hospital", "barber shop", "plumber", "hobbit", "trudo"};
    int numMemos = sizeof(memos) / sizeof(memos[0]);

    cout << "Enter check amount: ";
    cin >> c_amount.CheckAmount;

    if (c_amount > balance) {
        cout << "Check amount exceeds remaining balance. Check not processed.\n";
        return false;
    }

    cin.ignore(); // Consume the newline character left by cin
    cout << "Enter check memo (or press Enter for a random memo): ";
    string userMemo;
    getline(cin, userMemo);

    if (userMemo.empty()) {
        int randomIndex = rand() % numMemos; // No srand() here! It's in main()
        c_amount.CheckMemo = memos[randomIndex];
        cout<< memos[randomIndex] << endl;
    } else {
        c_amount.CheckMemo = userMemo;
    }

    c_amount.CheckNum = numOfChecks + 1;

    balance -= c_amount.CheckAmount;
    chkPtr[numOfChecks] = c_amount;
    numOfChecks++;

    if (numOfChecks >= checkBookSize / 2) {
        int newSize = checkBookSize * 2;
        Check* temp = new Check[newSize];
        for (int i = 0; i < numOfChecks; i++) {
            temp[i] = chkPtr[i];
        }
        delete[] chkPtr;
        chkPtr = temp;
        checkBookSize = newSize;

        cout << "WARNING: Checkbook is half full. A new checkbook has been ordered.\n";
    }

    cout << "Check written successfully.\n";
    return true;
}

void CheckBook::displayChecks() const {
    if (numOfChecks == 0) {
        cout << "No checks have been written yet.\n";
        return;
    }

    for (int i = numOfChecks - 1; i >= 0; i--) {
        cout << chkPtr[i] << endl; // Using overloaded << operator
    }
}

void CheckBook::checkTest(CheckBook& cb, float initialBalance) {
    cb.setBalance(initialBalance);
    Check newCheck;
    int checkNum = 1;

    while (cb.getBalance() > 0) {
        newCheck.CheckAmount = rand() % 50 + 1;
        newCheck.CheckNum = checkNum++;
        if (!cb.writeCheck(newCheck)) {
            break;
        }
        cout << "Balance after check " << newCheck.CheckNum << ": $" << cb.getBalance() << endl;
    }

    cout << "\nAll checks written (or balance exhausted):\n";
    cb.displayChecks();
    cout << "Final checkbook size: " << cb.getCheckBookSize() << endl;
}

int main() {
    srand(time(0));

    float initialBalance = 5000.0;
    CheckBook myCheckBook(initialBalance); // Initialize with balance

    cout << "Starting check test with initial balance: $" << initialBalance << endl;
    myCheckBook.checkTest(myCheckBook, initialBalance);

    return 0;
}