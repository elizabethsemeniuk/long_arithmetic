#include <iostream>
#include <vector>
using namespace std;

class BigNum {

public:
    vector<int> digits;
    int length;
    bool sign = true;

    BigNum(string input) {
        if (!isdigit(input[0]) && input[0] != '-') {
            cout << "Numbers cannot contain character" << input[0] << endl;
        }
        for (int i = 1; i < input.size(); i++){
            if (!isdigit(input[i]))
                cout << "Numbers cannot contain character" << input[i] << endl;
        }
        if (input[0] == '-') {
            sign = false;
            for (int i = input.size() - 1; i > 0; i--)
                digits.push_back(input[i] - '0');
            length = digits.size();
        } else {
            for (int i = input.size() - 1; i >= 0; i--)
                digits.push_back(input[i] - '0');
            length = digits.size();
        }
    }

    BigNum(BigNum const &a){
        sign = a.sign;
        digits = a.digits;
        length = a.length;
    }

    BigNum(){
        sign = true;
        length = 0;
        digits = vector<int>();
    }
};

BigNum abs(BigNum a){ // модуль числа
    BigNum b = BigNum(a);
    b.sign = true;
    return b;
}

void print(BigNum a){
    int i = a.length - 1;
    if (!a.sign)
        cout << '-';
    while (i >= 0){
        cout << a.digits[i];
        i--;
    }
    //cout << endl;
}

bool operator >(BigNum a, BigNum b){
    if (a.sign != b.sign){
        if (a.sign)
            return true;
        else
            return false;
    }
    else {
        if (a.sign){
            if (a.length > b.length)
                return true;
            else if (b.length > a.length)
                return false;
            else {
                for (int i = a.length - 1; i >= 0; i--){
                    if (a.digits[i] > b.digits[i])
                        return true;
                    else if (a.digits[i] < b.digits[i])
                        return  false;
                }
                return false;
            }
        }
    }
}

bool operator <(BigNum a, BigNum b){
    return b > a;
}

bool operator ==(BigNum a, BigNum b){
    return !(a > b || a < b);
}

BigNum operator +(BigNum a, BigNum b);

BigNum operator -(BigNum a, BigNum b) {
    BigNum c = BigNum();
        int debt = 0;
    if (a.sign == b.sign) {
        if (a.length > b.length) {
            for (int i = 0; i < a.length - b.length; i++) {
                b.digits.push_back(0);
                b.length++;
            }
        } else if (b.length > a.length) {
            for (int i = 0; i < b.length - a.length; i++) {
                a.digits.push_back(0);
                a.length++;
            }

        }
        if (abs(a) > abs(b)) {
            for (int i = 0; i < a.length; i++) {
                if (debt == 1) {
                    a.digits[i]--;
                    debt = 0;
                }
                if (a.digits[i] < b.digits[i]) {
                    debt = 1;
                    a.digits[i] += 10;
                }
                c.digits.push_back(a.digits[i] - b.digits[i]);
            }
            c.length = c.digits.size();
            for (int i = c.length - 1; i > 0; i--) {
                if (c.digits[i] == 0) {
                    c.digits.pop_back();
                    c.length--;
                }
                else
                    break;
            }
            c.sign = true;
        }
        if (abs(b) > abs(a)) {
            for (int i = 0; i < b.length; i++) {
                if (debt == 1) {
                    b.digits[i]--;
                    debt = 0;
                }
                if (b.digits[i] < a.digits[i]) {
                    debt = 1;
                    b.digits[i] += 10;
                }
                c.digits.push_back(b.digits[i] - a.digits[i]);
            }
            c.length = c.digits.size();
            for (int i = c.length - 1; i > 0; i--) {
                if (c.digits[i] == 0) {
                    c.digits.pop_back();
                    c.length--;
                }
                else
                    break;
            }
            c.sign = true;
        }
        if (abs(a) == abs(b)) {
            c = BigNum("0");
            c.sign = true;
        }
    }
    else {
        if (a.sign && !b.sign){
            c = abs(a) + abs(b);
            c.sign = true;
        }
        else{
            c = abs(b) + abs(a);
            c.sign = false;
        }

    }
    return c;
}

BigNum operator +(BigNum a, BigNum b){
    BigNum c = BigNum();
    int rest = 0;
    if (a.sign == b.sign) {
        if (a.length < b.length) {
            for (int i = 0; i < b.length - a.length; i++) {
                a.digits.push_back(0);
                a.length++;
            }
        }
        if (b.length < a.length) {
            for (int i = 0; i < a.length - b.length; i++) {
                b.digits.push_back(0);
                b.length++;
            }
        }
        for (int i = 0; i < a.length; i++) {
            int sum = (a.digits[i] + b.digits[i] + rest) % 10;
            rest = (a.digits[i] + b.digits[i] + rest) / 10;
            c.digits.push_back(sum);
        }
        c.sign = a.sign;
        c.length = a.length;
        if (rest > 0) {
            c.digits.push_back(rest);
            c.length++;
        }
    }
    else {
        if (a.sign){
            c = abs(a) - abs(b);
        }
        else {
            c = abs(b) - abs(a);
        }

    }
    return c;
}

int main() {
    BigNum a = BigNum("1");
    BigNum b = BigNum("-22");
    BigNum c = BigNum("1234567827483828383893828238989938389893389");

    a = BigNum("1");
    b = BigNum("-22");
    c = a - b;
    print(a);
    cout << " - ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;

    a = BigNum("-1");
    b = BigNum("22");
    c = a - b;
    print(a);
    cout << " - ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;

    a = BigNum("-1");
    b = BigNum("22");
    c = a + b;
    print(a);
    cout << " + ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;

    print(c);
    return 0;
}
