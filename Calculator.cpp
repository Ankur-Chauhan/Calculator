// Calculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Calculator.h"

int&& getInput(){
    int num = 0;
    cin >> num;
    while (1){
        if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter correct input" << endl;
            cin >> num;
        }
        if (!cin.fail())
            break;
    }
    return std::move(num);
}

char& getChar(){
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    char num = '\0';
    cin >> num;
    while (!(num == '+' || num == '-' || num == '*' || num == '/' || num == '%' || num == 'u')){
        std::cout << "Invalid operator, please reenter" << std::endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> num;
    }
    return num;
}

int main(){
    char input; int argument;
    std::cout << "Calculator programme:\n";
    argument = getInput();
    Calculator<int> calculator(std::move(argument));
    while (1){
        input = getChar();
        if (input == 'x')
            break;
        if(input != 'u')
            argument = getInput();
        
        // 'x' to break
        switch (input)
        {
            case '+':
                calculator + argument;
                break;
            case '-':
                calculator - argument;
                break;
            case '*':
                calculator * argument;
                break;
            case '/':
                calculator / argument;
                break;
            case '%':
                calculator % argument;
                break;
            case 'u':
                calculator.undoValue();
                break;
            case 'p':
                calculator.undoPrint();
                break;
        }
        cout << calculator;
    }
}
