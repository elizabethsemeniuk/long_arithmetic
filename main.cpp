#include <iostream>
#include <vector>
using namespace std;

class BigNum {

public:
    vector<int> digits;
    int length;
    bool sign = true;

    BigNum(string input) {
        if (input[0] == '-') {
            sign = false;
            for (int i = input.size() - 1; i > 0; i--)
                digits.push_back(input[i] - '0');
            length = digits.size();
            cout << "Number is negative" << endl;
        } else {
            for (int i = input.size() - 1; i >= 0; i--)
                digits.push_back(input[i] - '0');
            length = digits.size();
            cout << "Number is positive" << endl;
        }


    }
};

    void print(BigNum a){
        int i = a.length - 1;
        if (!a.sign)
            cout << '-';
        while (i >= 0){
            cout << a.digits[i];
            i--;
        }
        cout << endl;
    }



int main() {
    BigNum a = BigNum("12345678");
    BigNum b = BigNum("-123456787316761227");
    BigNum c = BigNum("1234567827483828383893828238989938389893389");
    string s1;
    cin >> s1;
    print(BigNum(s1));
    return 0;
}
