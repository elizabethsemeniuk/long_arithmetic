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
            c.sign = false; //false??
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
            }
            a.length = b.length;
        }
        if (b.length < a.length) {
            for (int i = 0; i < a.length - b.length; i++) {
                b.digits.push_back(0);
            }
            b.length = a.length;
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

int search(BigNum x, BigNum  y){
    for (int i = 1; i <= 9; i++){
        BigNum a = y * i;
        BigNum b = y * (i + 1);
        bool p1 = a == x;
        bool p2 = a < x;
        bool p3 = b > x;
        if ((p1 || p2) && p3)
            return i;
    }

}

std::pair<BigNum, BigNum> pairDivMod(BigNum a, BigNum b){
    BigNum z = BigNum(0);
    BigNum result = BigNum(0);
    for (int i = a.length - 1; i >= 0; i--) {
        if(i >= a.length)
            continue;
        if(a < b)
            return  {result, a};
        z = z * 10 + a.digits[i];
        if (z.length < b.length || abs(z) < abs(b)) {
            result = result * 10;
            continue;
        }
        int midresult = search(z, b);
        BigNum current = b * midresult;
        z = z - current;
        for (int j = 0; j < i; j++){
            current = current * 10;
        }
        result = result * 10 + midresult;
    }
    return  {result, z};
}

BigNum operator /(BigNum a, BigNum b) {
    return pairDivMod(a, b).first;
}

void print(BigNum a){
    int i = a.length - 1;
    if (!a.sign)
        cout << '-';
    while (i >= 0){
        cout << a.digits[i];
        i--;
    }
}

BigNum pow (BigNum a, BigNum b){
    if (b == 0)
        return BigNum(1);
    if (b == 1)
        return a;
    BigNum c = pow(a, b/2);
    c = c * c;
    BigNum x = BigNum(2);
    if (pairDivMod(b, x).second == 0)
        return c;
    else
        return c * a;
}

BigNum subMod(BigNum a, BigNum b){
    BigNum c = a - b;
    string moduleStr;
    cout << "Enter module, please:" << endl;
    cin >> moduleStr;
    BigNum module = BigNum(moduleStr);
    return pairDivMod(c, module).second;
}

BigNum addMod(BigNum a, BigNum b){
    BigNum c = a + b;
    string moduleStr;
    cout << "Enter module, please:" << endl;
    cin >> moduleStr;
    BigNum module = BigNum(moduleStr);
    return pairDivMod(c, module).second;
}

BigNum multMod(BigNum a, BigNum b){
    BigNum c = a * b;
    string moduleStr;
    cout << "Enter module, please:" << endl;
    cin >> moduleStr;
    BigNum module = BigNum(moduleStr);
    return pairDivMod(c, module).second;
}

/*BigNum divMod(BigNum a, BigNum b){ // ПЕРЕПИСАТЬ
    BigNum c = a / b;
    string moduleStr;
    cout << "Enter module, please:" << endl;
    cin >> moduleStr;
    BigNum module = BigNum(moduleStr);
    return pairDivMod(c, module).second;
} */

BigNum powMod(BigNum a, BigNum b){
    BigNum c = pow(a, b);
    string moduleStr;
    cout << "Enter module, please:" << endl;
    cin >> moduleStr;
    BigNum module = BigNum(moduleStr);
    return pairDivMod(c, module).second;
}

BigNum binSearch(BigNum left, BigNum right, BigNum a){
    BigNum middle = (left + right) / BigNum(2);
    if ((middle * middle == a || middle * middle < a) && ((middle + 1)*(middle + 1)) > a)
        return  middle;
    if (middle * middle < a)
        return  binSearch(middle + 1, right, a);
    else
        return  binSearch(left, middle, a);
}

BigNum sqrt(BigNum a){
    BigNum middle = 1 + (a / 4);
    if (a == 0)
        return 0;
    if (a == 1)
        return 1;
    else
        return binSearch(BigNum(2), a / BigNum(2), a);
}

void ex_al_eu_in(BigNum r1, BigNum r2, BigNum x1, BigNum x2, BigNum y1, BigNum y2, BigNum &gcd, BigNum &a, BigNum &b) {
    BigNum r3 = r1 - r2 * (r1 / r2);
    BigNum x3 = x1 - x2 * (r1 / r2);
    BigNum y3 = y1 - y2 * (r1 / r2);
    if (!(r3 == BigNum(0)))
        ex_al_eu_in(r2, r3, x2, x3, y2, y3, gcd, a, b);
    else {
        gcd = r2;
        a = x2;
        b = y2;
    }
}

void ex_al_eu(BigNum r1, BigNum r2, BigNum &gcd, BigNum &a, BigNum &b) {
    ex_al_eu_in(r1 > r2 ? r1 : r2, r1 < r2 ? r1 : r2, BigNum(1), BigNum(0), BigNum(0), BigNum(1), gcd, r1 > r2 ? a : b, r1 < r2 ? a : b);
}

BigNum reverseByMod(BigNum a, BigNum b){
    BigNum c = b;
    BigNum gcd = BigNum(1);
    ex_al_eu(a,b,gcd,a,b);
    if(!a.sign)
        a = a + c;
    return a;
}

BigNum solve_system(vector<std::pair<BigNum, BigNum>> equations){ // num and mod
    cout << "Solving system of " << equations.size() << " equations:" << endl;
    for(auto equation : equations){
        cout << "x = ";
        print(equation.first);
        cout <<  " (mod ";
        print(equation.second);
        cout << ");" << endl;
    }
    BigNum all_mod = BigNum(1);
    BigNum result = BigNum(0);
    for (auto pr : equations){
        BigNum new_first = (pr.first - result);
        while (!new_first.sign){
            new_first = new_first + pr.second;
        }
        new_first = new_first * reverseByMod(all_mod, pr.second);
        new_first = pairDivMod(new_first, pr.second).second;
        result = result + new_first * all_mod; // 2 17
        all_mod = all_mod * pr.second; // 5 35
    }
    return result;
}

int main() {
    BigNum a = BigNum("6");
    BigNum b = BigNum("2");
    BigNum c = BigNum("1234567827483828383893828238989938389893389");

   // a = BigNum("4096");
    b = BigNum("123456798960569059");
    c =  sqrt(b);
   // print(a);
    cout << " sqrt ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;

    // solve_system(vector<std::pair<BigNum, BigNum>> equations)

    vector<std::pair<BigNum, BigNum>> test = {{BigNum(2), BigNum(5)},
                                              {BigNum(3), BigNum(7)},
                                              {BigNum(5), BigNum(11)}};
    c = solve_system(test);
    cout << "Result: ";
    print(c);
    cout << endl;

    vector<std::pair<BigNum, BigNum>> test4 = {{BigNum(5), BigNum(9)},
                                              {BigNum(7), BigNum(8)},
                                              {BigNum(3), BigNum(7)}};
    c = solve_system(test4);
    cout << "Result: ";
    print(c);
    cout << endl;
    vector<std::pair<BigNum, BigNum>> test1 = {{BigNum(1), BigNum(5)},
                                              {BigNum(2), BigNum(7)}};
    c = solve_system(test1);
    cout << "Result: ";
    print(c);
    cout << endl;

    vector<std::pair<BigNum, BigNum>> test2 = {{BigNum(0), BigNum(2)},
                                               {BigNum(0), BigNum(4)}};
    c = solve_system(test2);
    cout << "Result: ";
    print(c);
    cout << endl;

    a = BigNum(5);
    b = BigNum(13);
    c = reverseByMod(a, b);
    print(a);
    cout << "^(-1) (mod ";
    print(b);
    cout << ") = ";
    print(c);
    cout << endl;

    a = BigNum(5);
    b = BigNum(7);
    c = reverseByMod(a, b);
    print(a);
    cout << "^(-1) (mod ";
    print(b);
    cout << ") = ";
    print(c);
    cout << endl;

    a = BigNum(71);
    b = BigNum(91);
    c = reverseByMod(a, b);
    print(a);
    cout << "^(-1) (mod ";
    print(b);
    cout << ") = ";
    print(c);
    cout << endl;


    a = BigNum("12");
    b = BigNum("6");
    int f = 10;
    c = a / b;
    print(a);
    cout << " / ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;

    a = BigNum("3");
    b = BigNum("9");
    c = pow(a,b);
    print(a);
    cout << "^";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;

    a = BigNum("400");
    b = BigNum("9");
    c = a + b;
    print(a);
    cout << " + ";
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

    a = BigNum("4096");
    b = BigNum("4");
    c = a / b;
    print(a);
    cout << " / ";
    print(b);
    cout << " = ";
    print(c);
    cout << endl;


    return 0;
}
