//
//  main.cpp
//  BigInt 3.0.1
//
//  Created by Арсений on 13.02.2021.
//  Copyright © 2021 Арсений. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>


const int if_nine = 9;


/*!
 * FIXME
 *
 * TODO
 *
 * @note с минусом лучше сравнить по модулю , а не по размеру
 * возможен вариант с сравненнием первого числа ( обдумать )
 */
/// Дополнительные внешние функции

//!void createMas(std::vector <unsigned int>& high, std::vector <unsigned int>& low, std::vector <unsigned int>& answer );



class BigInteger {
public:
    // А где конструктор копирования?
    // Конструктор, Присваивание, toString
    BigInteger();
    BigInteger(const long long& value);// Простые объекты (малого веса) по типу value можно передавать напрямую, копированием, что чуть упрощает работу
    BigInteger(const std::string& value);
    BigInteger& operator=(const long long& value);
    std::string toString() const;// Эм, а почему каст объявлен среди конструкторов??
    BigInteger& operator=(const BigInteger& value);


    // Унарные операторы
    BigInteger& operator++();
    const BigInteger operator++(int);// Он должен возвращать обычную копию, не const
    BigInteger& operator--();
    const BigInteger operator--(int);// Аналогично
    const BigInteger operator-();// Аналогично


    // Булевы операторы
    bool operator == (const BigInteger& value);
    bool operator != (const BigInteger& value);
    bool operator > (const BigInteger& value);
    bool operator < (const BigInteger& value);
    bool operator >= (const BigInteger& value);
    bool operator <= (const BigInteger& value);
    explicit operator bool() const;


    // Арифмитические операции 1.0
    BigInteger& operator+=(const BigInteger& value);
    BigInteger& operator-=(const BigInteger& value);
    BigInteger& operator*=(const BigInteger& value);
    BigInteger& operator/=(const BigInteger& value);
    BigInteger& operator%=(const BigInteger& value);


    // Арифмитические операции 2.0
    // Абидно, так то += круче считается, а это так, приятный доп
    // А почему они friend? Поправь
    friend BigInteger operator+(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator-(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator*(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator/(const BigInteger& left, const BigInteger& right);
    friend BigInteger operator%(const BigInteger& left, const BigInteger& right);


    // Поток ввода и вывода
    friend  std::ostream& operator<<(std::ostream& out, const BigInteger& num);
    friend  std::istream& operator>>(std::istream& in, BigInteger& value);

    // Функция модуля
    void toABS() {
        if (sign == 0) {
            sign = 0;
        }
        else {
            sign = 1;
        }
    }

    // Узнать знак
    int getSign() {// if a<0 ... 
        return sign;
    }
private:
    std::vector <unsigned int> number;
    int sign = 0;
    // Дополнительные функции
    // Было бы круто получить побольше комментариев по поводу данных функций
    void createMas(const std::vector <unsigned int>& high, const std::vector <unsigned int>& low, std::vector <unsigned int>& answer);
    void createMas(const std::vector <unsigned int>& high, const std::vector <unsigned int>& low, std::vector <long long>& answer);
    void fix_sum(std::vector <unsigned int>& answer);
    void fix_sum(std::vector <long long>& answer);
    bool CheckMas(const std::vector <unsigned int>& first, const std::vector <unsigned int>& second);
    void Simple() { //особенно эта

    }
};

// Опционально-литеральный суффикс

//BigInteger operator ""_bi(const char* num) {
//  return BigInteger(std::string(num));
//}

// Дополнительные внешние функции


// Дополнительные внутренние функции


// Конструктор, Присваивание, toString
BigInteger::BigInteger() {
    sign=0;
    // Здесь было бы хорошо добавить один нулевой элемент, так как пустая инициализация это создание элемента = 0
}

BigInteger::BigInteger(const long long& value) {
    if (value == 0) {
        sign=0;
        number.push_back(value);
    }

    if (value < 0 ) {
        sign=-1;
        long long var_value = value;
        var_value=std::abs(var_value);
        while (var_value != 0) {
            number.push_back(var_value % 10);
            var_value/=10;
        }
        std::reverse(number.begin(), number.end());

    }

    if (value > 0) {
        sign=1;
        long long var_value = value;
        while (var_value != 0) {
            number.push_back(var_value % 10);
            var_value/=10;
        }
        std::reverse(number.begin(), number.end());
    }
}

BigInteger::BigInteger(const std::string& value) {
    size_t i=0;
    sign=1;

    if (value[0]=='-') {
        sign=-1;
        i=1;
    }

    if (value[0]=='0') {
        sign=0;
        number.push_back(value[i]-'0');// push_back (0)
        i=1;
    }

    for (; i<value.size(); ++i) {
        number.push_back(value[i]-'0');
    }

}
// Зачем копипаста? У тебя по факту есть конструктор из long long и оператор присваивания для BigInt,
// Откуда, через приведение типов, данная функция и заработает
BigInteger& BigInteger::operator=(const long long& value) {
    number.clear();
    if (value == 0) {
        sign=0;
        number.push_back(value);
    }

    if (value < 0 ) {
        sign=-1;
        long long var_value = value;
        var_value=std::abs(var_value);
        while (var_value != 0) {
            number.push_back(var_value % 10);
            var_value/=10;
        }
        std::reverse(number.begin(), number.end());
    }

    if (value > 0) {
        sign=1;
        long long var_value = value;
        while (var_value != 0) {
            number.push_back(var_value % 10);
            var_value/=10;
        }
        std::reverse(number.begin(), number.end());
    }
    return (*this);
}

std::string BigInteger::toString() const {
    std::string answer;
    if (sign==-1) answer.push_back('-');
    for (size_t i=0; i<number.size();++i) {
        answer.push_back((char)(number[i]+48));
    }
    return answer;
}

BigInteger& BigInteger::operator=(const BigInteger &value) {
    number=value.number;
    sign=value.sign;
    return (*this);
}
// Унарные операторы
BigInteger & BigInteger::operator--() {
    *this-=1;
    return *this;
}

const BigInteger BigInteger::operator--(int)  {
    BigInteger answer = *this;
    *this-=1;
    return answer;
}

BigInteger & BigInteger::operator++() {
    *this+=1;
    return *this;
}

const BigInteger BigInteger::operator++(int) {
    BigInteger answer = *this;
    *this+=1;
    return answer;
}

const BigInteger BigInteger::operator-() {
    BigInteger answer = *this;
    answer.sign *= -1;
    return answer;
}

// Булевы операторы
bool BigInteger::operator==(const BigInteger &value) {
    return ((value.number==this->number) && (value.sign==this->sign));
}

bool BigInteger::operator!=(const BigInteger &value) {
    return !((*this)==value);
}

bool BigInteger::operator>(const BigInteger &value) {
    if (this->sign != value.sign) return (this->sign > value.sign);
    if (value.sign == 0) return false;
    if (number.size() != value.number.size()) {
        if (this->sign > 0) return (number.size() > value.number.size());
        if (this->sign < 0) return  (number.size() < value.number.size());
    }
    else {
        for (size_t i = 0; i < number.size(); ++i) {
            if (number[i] != value.number[i]) {
                if (this->sign > 0) return (number[i] > value.number[i]);
                if (this->sign < 0) return  (number[i] < value.number[i]);
            }
        }
        return false;
    }
    return false;
}

bool BigInteger::operator>=(const BigInteger &value) {
    return ((*this)==value || (*this)>value);
}

bool BigInteger::operator<(const BigInteger &value) {
    return !((*this)>= value);
}

bool BigInteger::operator<=(const BigInteger &value) {
    return ((*this)==value || (*this)<value);
}

BigInteger::operator bool() const {
    return sign;
}


// Арифмитические операции 1.0
BigInteger & BigInteger::operator+=(const BigInteger &value) {

    if (value.sign == 0) {
        return (*this);
    }

    if (this->sign == 0) {

        if (value.sign==-1) {
            number=value.number;
            sign=-1;
            return (*this);
        }

        if (value.sign==1) {
            (*this)=value;
            return (*this);
        }
    }

    if (this->sign == value.sign) {
        if ((this->number).size() >= value.number.size()) {
            std::vector <unsigned int> answer;// создание временных массивов для += запрещено, в этом вся фишка, иначе нет смысла в его скорости
            createMas((*this).number,value.number,answer);
            fix_sum(answer);
            (*this).number=answer;
            return (*this);
        }

        else {
            std::vector <unsigned int> answer;
            createMas(value.number,(*this).number,answer);
            fix_sum(answer);
            (*this).number=answer;
            return (*this);
        }
    }

    else {
        BigInteger c_value=value;// Тут особенно
        c_value.sign=c_value.sign*(-1);
        (*this)-=c_value;
        return (*this);
    }
}

BigInteger & BigInteger::operator-=(const BigInteger &value) {
    if (value.sign == 0) {
        return (*this);
    }

    if ((*this).sign == 0) {
        (*this) = value;
        if (value.sign==-1) {
            sign=1;
            return (*this);
        }
        if (value.sign==1) {
            sign=-1;
            return (*this);
        }
    }

    if (value.sign == (*this).sign) {
        if (CheckMas(this->number,value.number)) {
            std::vector <long long> answer;
            createMas(this->number,value.number,answer);
            fix_sum(answer);
            number.clear();
            for (unsigned int i=0; i<answer.size();++i) {
                number.push_back(answer[i]);
            }
            if (sign==-1) sign=-1;
            else if (sign==1) sign=1;
            if (number[0]==0) sign=0;
            return (*this);
        }

        else {
            std::vector <long long> answer;
            createMas(value.number,this->number,answer);
            fix_sum(answer);
            number.clear();
            for (unsigned int i=0; i<answer.size();++i) {
                number.push_back(answer[i]);
            }
            sign=value.sign;
            if (sign==-1) sign=1;
            else if (sign==1) sign=-1;
            if (number[0]==0) sign=0;
            return (*this);
        }
    }

    else {
        BigInteger c_value = value;
        c_value.sign=c_value.sign*(-1);
        (*this)+=c_value;
        return (*this);
    }

}

BigInteger & BigInteger::operator*=(const BigInteger &value) {
    if (sign == 0) {
        return (*this);
    }

    if (value.sign == 0) {
        (*this)=0;
        return *this;
    }

    int new_sign = 1;
    if (value.sign != sign) {
        new_sign=-1;
    }

    BigInteger const_bufer = (*this);
    BigInteger answer = 0;
    //(*this)=0;
    size_t i = value.number.size();
    size_t j = 0;
    do {
        --i;
        BigInteger var_bufer = 0;
        for (unsigned int k = 0; k < value.number[i]; ++k) {
            var_bufer+=const_bufer;
        }

        if (var_bufer != 0) {
            for (unsigned  int k = 0; k < j; ++k) {
                var_bufer.number.push_back(0);
            }
        }

        ++j;
        answer+=var_bufer;
    } while (i!=0);
    //sign = new_sign;
    *this = answer;
    sign = new_sign;
    return *this;
}

BigInteger & BigInteger::operator/=(const BigInteger& value) {

    BigInteger copy_value = value;
    copy_value.sign=1;
    BigInteger copy_this = (*this);
    copy_this.sign=1;

    if (this->number == value.number) {
        BigInteger answer(1);
        *this = answer;
        return *this;
    }


    if (value.sign == 0) {
        //std::cout << "Серый,блять,ты конченый";
        return *this;
    }

    if (sign == 0) {
        return *this;
    }

    if (number.size() < value.number.size()) {
        *this = 0;
        return (*this);
    }

    if (copy_this < copy_value) {
        *this = 0;
        return *this;
    }

    std::vector <unsigned int> answer;
    BigInteger buffer = 0;
    size_t i = 0;
    //size_t j = 0;
    //bool check = true;

    do {

        if (buffer  - copy_value < 0) {
            answer.push_back(0);
            buffer=buffer*10 + number[i];
        }

        while (buffer - copy_value > -1) {
            answer[answer.size()-1]++;
            buffer-=copy_value;
        }

        ++i;
    } while (i != number.size());

    while (answer[0]==0) {
        answer.erase(answer.begin());
    }

    number = answer;
    if (sign == value.sign) sign = 1;
    else sign = -1;
    return *this;

}

BigInteger & BigInteger::operator%=(const BigInteger &value) {
    BigInteger this_copy = *this;
    this_copy /= value;
    *this = *this - value*this_copy;
    return *this;
}
// Арифмитические операции 2.0
// А для чего тогда friend?
BigInteger operator+(const BigInteger& left, const BigInteger& right) {
    BigInteger answer = left;
    return (answer+=right);
}

BigInteger operator-(const BigInteger& left, const BigInteger& right) {
    BigInteger answer = left;
    return (answer-=right);
}

BigInteger operator*(const BigInteger& left, const BigInteger& right) {
    BigInteger copy_left = left;
    copy_left*=right;
    return copy_left;
}

BigInteger operator/(const BigInteger& left, const BigInteger& right) {
    BigInteger copy_left = left;
    copy_left/=right;
    return copy_left;
}

BigInteger operator%(const BigInteger& left, const BigInteger& right) {
    BigInteger left_copy = left;
    left_copy%=right;
    return left_copy;
}
// Поток ввода и вывода
std::ostream& operator<<(std::ostream& out, const BigInteger& value) {
    out << value.toString();
    return out;
}
std::istream& operator>>(std::istream& in, BigInteger& value) {
    std::string str;
    in >> str;
    value = BigInteger(str);
    return in;
}

// Дополнительные функции

void BigInteger::createMas(const std::vector<unsigned int> &high, const std::vector<unsigned int> &low, std::vector<unsigned int> &answer) {
    size_t size_h = high.size();
    answer.push_back(0);
    for (size_t i=0; i < size_h; ++i) {
        answer.push_back(high[i]);
    }

    long long  lo = (long long)low.size()-1;
    long long  an = (long long)answer.size()-1;

    for (; an>0; --an) {
        if (lo>-1) answer[an]+=low[lo];
        lo--;
    }
}
// Даже боюсь спросить что они делают
void BigInteger::createMas(const std::vector<unsigned int> &high, const std::vector<unsigned int> &low, std::vector<long long> &answer) {

    for (size_t i=0; i < high.size(); ++i) {
        answer.push_back(high[i]);
    }

    long long lo = (long long)low.size() - 1;
    long long an = (long long)answer.size() - 1;

    for (; an>-1; --an) {
        if (lo > -1) {
            answer[an]-=low[lo];
        }
        lo--;
    }
}
// Создавать 2 функции с одинаковым названием и семантикой (описанием ввода) за исключением int/long и делать их совершенно разными оч плохо
// По крайне мере читаемости я тут явно не увидел
void BigInteger::fix_sum(std::vector<unsigned int>& answer) {
    long long j = (long long)answer.size() - 1;
    for (; j>0; --j) {
        if (answer[j] > 9) {
            answer[j-1]+=answer[j]/10;
            answer[j]=answer[j]%10;
        }
    }
    if (answer[0]==0) {
        answer.erase(answer.begin());
    }
}

void BigInteger::fix_sum(std::vector<long long>& answer) {
    long long j = (long long)answer.size()-1;
    for (;j>-1;--j) {
        if (answer[j] < 0) {
            answer[j]+=10;
            answer[j-1]-=1;
        }
    }

    while (answer[0]==0 && answer.size()>1) {
        answer.erase(answer.begin());
    }
}

bool BigInteger::CheckMas(const std::vector<unsigned int>& first, const std::vector<unsigned int>& second) {
    if (first.size() > second.size()) return true;
    if (first.size() < second.size()) return false;
    for (unsigned int i=0; i<first.size(); ++i) {
        if (first[i] != second[i]) return first[i]>second[i];
    }
    return false;
}



class Rational {
public:
    // Конструктор и оператор приведения
    Rational() {
        sign = 0;
        a = 0;
        b = 0;
    }
    Rational(const BigInteger& value);

    Rational(const long long& value);

    Rational(const long long& value1, const long long& value2);

    //Rational& operator=(const double& value);

    Rational& operator=(const long long& value);

    // Вывод
    friend  std::ostream& operator<<(std::ostream& out, const Rational& num);

    // Операторы сравнения
    bool operator==(const Rational& value);
    bool operator!=(const Rational& value);
    bool operator<(const Rational& value);
    bool operator>(const Rational& value);
    bool operator<=(const Rational& value);
    bool operator>=(const Rational& value);
    explicit operator bool() const;

    // Унарные операторы
    Rational& operator++();
    Rational operator++(int);
    Rational& operator--();
    Rational operator--(int);
    Rational operator-();

    // Арифмитические операции 1.0

    Rational& operator+=(const Rational& value);
    Rational& operator-=(const Rational& value);
    Rational& operator*=(const Rational& value);
    Rational& operator/=(const Rational& value);

    // Арифмитические операции 2.0
    // Friend нужно убрать, не нужон он тут
    friend Rational operator+(const Rational& left, const Rational& right);
    friend Rational operator-(const Rational& left, const Rational& right);
    friend Rational operator*(const Rational& left, const Rational& right);
    friend Rational operator/(const Rational& left, const Rational& right);

    // toString

    const std::string toString() const {
        if (sign == 0) return "0";
        std::string answer;
        if (sign == -1) answer+="-";
        answer+=a.toString();
        //answer+="/";
        BigInteger ONE = 1;
        BigInteger M_ONE = -1;
        if ( ONE == b || (M_ONE == b)) {
            return answer;
        }
        answer+="/";
        answer += b.toString();
        return answer;
    }

    const std::string asDecimal (size_t precision ) const;

    explicit operator double() const{
        double result = atof((*this).asDecimal(17).c_str());
        return result;
    }



private:
    BigInteger a;
    BigInteger b;
    int sign;

    void fix() {
        //if (b == 1) return;
        //if (b == -1) return;
        if (sign == 0) return;
        BigInteger copy_a = a;
        BigInteger copy_b = b;
        //std::cout << a << " ";
        //std::cout << b << " ";

        while (copy_a != 0 && copy_b != 0) {
            if (copy_a > copy_b) {
                copy_a%=copy_b;
            }
            else {
                copy_b%=copy_a;
            }
        }
        //std::cout << a << " " << b << '\n';
        if (copy_b != 0 ) {
            a/=copy_b;
            b/=copy_b;
        }

        if ( copy_a != 0 ) {
            a/=copy_a;
            b/=copy_a;
        }
    }
};


// Конструктор
Rational::Rational(const BigInteger& value) {
    a = value;
    sign = a.getSign();// if (a < 0) a*=-1
    a.toABS();
    b = 1;
}

Rational::Rational(const long long &value) {
    a = value;
    sign = a.getSign();// Аналогично
    a.toABS();
    b = 1;
}

Rational::Rational(const long long &value1, const long long &value2) {
    a=value1;
    b=value2;
    a.toABS();
    sign = a.getSign();
    fix();
}
/*
Rational & Rational::operator=(const double &value) {
    if (value != 1) {
        return *this;
    }
    else {
        return *this;
    }
}
*/
Rational& Rational::operator=(const long long &value) {
    if (value == 0) {
        sign = 0;
        // a=0;
        // b=1; Иначе при умножении на этот rational может случиться печаль
        //return *this;
    }

    if (value > 0) {
        sign = 1;
        b = 1;
        a = value;
        //return *this;
    }

    if (value < 0) {
        sign = -1;
        b = 1;
        a = -value;
        //return *this;
    }
    return *this;
}


// Операторы сравнения
bool Rational::operator==(const Rational &value) {
    //std::cerr << " " << *this << " TUT == " << value << " " ;
    if (sign == 0 && value.sign == 0 ) return true;
    Rational copy_value = value;// Это ещё что, зачем? У тебя должен быть гарант, что поступающий Rational уже пофикшен, иначе как его оператива держит то
    copy_value.fix();
    if (sign == copy_value.sign && a == copy_value.a && b == copy_value.b) {
        return true;
    }
    else {
        return false;
    }
}

bool Rational::operator!=(const Rational &value) {
    //std::cerr << " " << *this << " TUT != " << value << " " ;
    return !(*this == value);
}

bool Rational::operator<(const Rational &value) {
    //std::cerr << " " << *this << " TUT < " << value << " " ;
    BigInteger answer = a * value.b * (sign) - value.a * b * (value.sign);
    if (answer < 0) {
        return true;
    }
    else {
        return false;
    }
}

bool Rational::operator<=(const Rational &value) {
    //std::cerr << " " << *this << " TUT <= " << value << " " ;
    return (*this == value || *this < value);
}

bool Rational::operator>(const Rational &value) {
    //std::cerr << " " << *this << " TUT > " << value << " " ;
    return !(*this <= value);
}

bool Rational::operator>=(const Rational &value) {
    //std::cerr << " " << *this << " TUT >= " << value << " " ;
    return (*this == value || *this > value);
}

Rational::operator bool() const {
    return sign;
}


// Унарные операторы
Rational  Rational::operator-() {
    Rational answer = *this;
    answer.sign = answer.sign * (-1);
    return answer;
}

Rational & Rational::operator++() {
    *this+=1;
    return *this;
}

Rational  Rational::operator++(int) {
    Rational answer = *this;
    answer+=1;// Не правильно, должен изменяться не answer, a this, так как ты должен вернуть копию со старым значением
    return answer;
}

Rational & Rational::operator--() {
    *this-=1;
    return *this;
}

Rational  Rational::operator--(int) {
    Rational answer = *this;
    answer-=1;// Аналогично
    return answer;
}


// Арифтические операции 1.0
Rational & Rational::operator+=(const Rational &value) {
    if (sign == 0) {
        *this = value;
        return *this;
    }

    if (value.sign == 0) {
        return *this;
    }

    a = (sign)*a * value.b + (value.sign)*value.a * b ;
    b = b * value.b;
    sign = a.getSign();
    a.toABS();
    (*this).fix();
    return *this;
}

Rational & Rational::operator-=(const Rational &value) {
    Rational copy_value = value;// Это зачем? Во первых - и так создаст копию, а во вторых 2 копирования в -= не есть приемлемо
    *this+=(-copy_value);
    return *this;
}

Rational & Rational::operator*=(const Rational &value) {
    a = a * value.a;
    b = b * value.b;
    sign = sign * value.sign;
    fix();
    return *this;
}

Rational & Rational::operator/=(const Rational &value) {
    //std::cerr << "first " << *this << " second " << value << " " ;
    a = a * value.b;
    b = b * value.a;
    sign = sign * value.sign;
    fix();
    //std::cerr << " my answer " << *this;
    return *this;
}

// Арифмитические операции 2.0
Rational operator+(const Rational& left, const Rational& right) {
    Rational copy_left = left;
    return copy_left += right;
}

Rational operator-(const Rational& left, const Rational& right) {
    Rational copy_left = left;
    return copy_left -= right;
}

Rational operator*(const Rational& left, const Rational& right) {
    Rational copy_left = left;
    return copy_left *= right;
}

Rational operator/(const Rational& left, const Rational& right) {
    Rational copy_left = left;
    return copy_left/=right;
}


// вывод

std::ostream& operator<<(std::ostream& out, const Rational& value) {
    out << value.toString();
    return out;
}

// asDecimal
const std::string Rational::asDecimal(size_t precision) const  {
    std::cerr << *this << " " << precision << " ";
    std::string answer;
    if (sign == 0) {
        answer+="0";
        if (precision == 0) return answer;
        answer+=",";
        for (size_t i = 0; i < precision; ++i) {
            answer+="0";
        }
        return answer;
    }
    if (sign == -1) answer+="-";
    answer+=(a/b).toString();
    if (precision == 0) return answer;
    answer+=".";
    unsigned long long position = 0;
    int check=0;
    BigInteger buffer = (a % b);
    buffer*=10;
        while (buffer < b) {
            buffer *= 10;
            answer += "0";
            position += 1;
            if (position == precision) break;
        }
        while (true) {
            if (position == precision) break;
            if (buffer >= b) {
                answer += (buffer / b).toString();
                buffer %= b;
                position += 1;
                check=0;
            }
            else {
                buffer*=10;
                check+=1;

                if (buffer == 0) {
                    position+=1;
                    answer+="0";
                }

                else if (check > 1) {
                    answer+="0";
                    position+=1;
                }

            }
        }
    return answer;
}

void Test() {

    BigInteger A = 15;
    long long n = 15;
    for (long long i = 0; i < 10000; ++i) {
        A *= (-i);
        n *= (-i);
        if (A != n) {
            std::cout << "ERR" << '\n';
        }
    }
}

void TestDiv() {

    BigInteger A;
    BigInteger B;

    long long a;
    long long b;

    size_t j = 0;
    for (long long i = 0; i < 100000; ++i) {
        a = ((rand() << 15) | rand()) - ((rand() << 15) | rand()) * ((rand() << 15) | rand()) - ((rand() << 15) | rand());
        b = ((rand() << 15) | rand()) - ((rand() << 15) | rand());
        std::string s1 = std::to_string(a);
        std::string s2 = std::to_string(b);

        A = s1;
        B = s2;
        BigInteger C = a/b;
        if (C != (A/B)) {
            std::cout << "ERROR " << A << " " << B << "\n";
        }
        else
        {
            j++;
        }
    }

    std::cout << j << '\n';

}







