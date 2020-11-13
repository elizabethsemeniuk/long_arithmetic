#include <iostream>
#include <vector>
#include <string>
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

    void setBigNum(BigNum const &a){
        sign = a.sign;
        digits = a.digits;
        length = a.length;
    }

    BigNum(BigNum const &a){
       setBigNum(a);
    }

    BigNum(){
        sign = true;
        length = 0;
        digits = vector<int>();
    }

    BigNum(int i) {
        setBigNum(BigNum(std::to_string(i)));
    }
};
BigNum operator +(BigNum a, BigNum b);

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

BigNum operator *(BigNum a, BigNum b){

    BigNum c = BigNum();
    for (int i = 0; i < a.length + b.length; i++) {
        c.digits.push_back(0);
        c.length++;
    }

    int rest = 0;
    int result = 0;
    for (int j = 0; j < b.length; j++){
        for (int k = 0; k < a.length; k++){
            result = a.digits[k] * b.digits[j] + rest;
            c.digits[k + j] += result % 10;
            rest = result / 10;
        }
        if (rest > 0)
            c.digits[j + a.length] += rest;
        rest = 0;
    }
    rest = 0;
    for (int i = 0; i < c.digits.size(); i++){
        c.digits[i] += rest;
        rest = c.digits[i] / 10;
        c.digits[i] %= 10;

    }
    while (rest > 0){
        c.digits.push_back(rest % 10);
        rest /= 10;
        c.length++;
    }
    c.length = c.digits.size();
    int i = c.length - 1;
    while (i > 0 && c.digits[i] == 0) {
            c.digits.pop_back();
            c.length--;
            i--;
    }
    c.sign = a.sign == b.sign; // signs
    return c;
}

BigNum operator * (BigNum a, int b){
    BigNum c = BigNum(b);
    c = c * a;
    return c;
}

BigNum operator + (BigNum a, int b){
    BigNum c = BigNum(b);
    c = c + a;
    return c;
}

BigNum operator / (BigNum a, BigNum b){

}
/*BigNum search (BigNum left, BigNum right, BigNum x, BigNum  y){
    int middle = (left + right);
    if (left == right)
        return  left;
    else if (x < y)
        return 0;
    else if (middle * x < y && middle * x == y && (middle + 1) * x > y)
        return middle;
    else if (middle * x > y)
        return  search(left, middle, x, y);
    else
        return  search(middle, right, x, y);
}*/

BigNum pow (BigNum a, int n){
    if (n == 0)
        return BigNum(1);
    if (n == 1)
        return a;
    BigNum c = pow(a, n/2);
    c = c * c;
    if (n % 2 == 0)
        return c;
    else
        return c * a;
}

int main() {
    BigNum a = BigNum("6");
    BigNum b = BigNum("2");
    BigNum x = BigNum();
    BigNum c = BigNum("1234567827483828383893828238989938389893389");

    a = BigNum("12");
    b = BigNum("6");
    c = a / b;
    print(a);
    cout << " / ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;


    a = BigNum("64");
    b = BigNum("64");
    c = a * b;
    print(a);
    cout << " * ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;

    a = BigNum("-875");
    b = BigNum("875");
   // c = a + b;
    print(a);
    cout << " + ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;

    return 0;
}
