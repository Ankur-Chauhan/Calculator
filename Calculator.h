#pragma once
#include <iostream>
#include <stack>
using namespace std;

template<typename T>
struct previousOps {
    char        _operator;
    T           _operand;
    double      _value;
    previousOps(const T&, const char&, const double&);
};

template<typename T>
previousOps<T>::previousOps(const T& variable, const char& symbol, const double& value) {
    this->_operator = symbol;
    this->_operand = variable;
    this->_value = value;
}

template<typename T>
class Calculator {
    std::stack<previousOps<T>>       undo;
    double                           value;

public:
    Calculator(T&& argument) : value(std::move(argument)) {}
    ~Calculator() {}

    bool addState(const T& arg, const char& symbol, const double& previousValue);
    int  savedStates() { return undo.size(); }
    void undoValue();
    void undoPrint();

    void operator+(const T& argument);
    void operator-(const T& argument);
    void operator*(const T& argument);
    void operator/(const T& argument);
    void operator%(const T& argument);

    friend ostream& operator<<(ostream& cout, const Calculator& calculator) {
        cout << calculator.value << std::endl;
        return cout;
    }
};

template<typename T>
void Calculator<T>::operator+(const T& arg) {
    addState(arg, '+', this->value);
    this->value += arg;
}

template<typename T>
void Calculator<T>::operator-(const T& arg) {
    addState(arg, '-', this->value);
    this->value -= arg;
}

template<typename T>
void Calculator<T>::operator*(const T& arg) {
    addState(arg, '*', this->value);
    this->value *= arg;
}

template<typename T>
void Calculator<T>::operator/(const T& arg) {
    if (arg == 0)
    {
        std::cout << "Exception:Divide by 0" << std::endl;
        return;
    }
    addState(arg, '/', this->value);
    this->value = (double)this->value / arg;
    //return this->value;
}

template<typename T>
void Calculator<T>::operator%(const T& arg) {
    addState(arg, '%', this->value);
    this->value = (int)this->value % arg;
}

template<typename T>
bool Calculator<T>::addState(const T& arg, const char& symbol, const double& value) {
    //std::cout << "AddState:" << arg << "|" << symbol << "|" << value << std::endl;
    undo.push(previousOps<T>(arg, symbol, value));
    return true;
}

template<typename T>
void Calculator<T>::undoValue() {
    if (undo.size() == 0)
    {
        this->value = 0;
        return;
    }
    this->value = undo.top()._value;
    undo.pop();
}

template<typename T>
void Calculator<T>::undoPrint() {
    std::stack<previousOps<T>>  check = undo;
    while (!check.empty()) {
        std::cout << check.top()._operand << "|" << check.top()._operator << "|" << check.top()._value << std::endl;
        check.pop();
    }
}
