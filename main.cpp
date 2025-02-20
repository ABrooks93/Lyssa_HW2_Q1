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

ostream & operator<<(ostream &var, Check &c) {
    var<<c.CheckNum<<" "<<c.CheckMemo<<" "<<c.CheckAmount;
    return var;
}

// bool is returning true or false when check is compared to a float variable.
bool Check::operator>(Float &f) {
    return CheckAmount>f;
}

int main();
