#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>
using namespace std;



struct Stack {
    char �ymbol;
    Stack* next;
};

struct StackDigit {
    int data;
    StackDigit* next;
};

int priorityPolishReversed(char a) {
    switch (a) {
    case '*': case '/': return 3;
    case '-': case '+': return 2;
    case '(': return 1;
    case ')': return 0;
    }

}

int priorityPolish(char a) {
    switch (a) {
    case '*': return 6;
    case '/': return 7;
    case '-': case '+': return 4;
    case '(': return 0;
    case ')': return 1;
    }

}

Stack* push(Stack* stack, char item)
{
    Stack* newStack = new Stack;
    newStack->�ymbol = item;
    newStack->next = stack;
    return newStack;
}

StackDigit* pushDigit(StackDigit* stack, int item)
{
    StackDigit* newStack = new StackDigit;
    newStack->data = item;
    newStack->next = stack;
    return newStack;
}

Stack* pop(Stack* stack, char& item)
{
    Stack* newStack = stack;
    item = stack->�ymbol;
    stack = stack->next;
    delete newStack;
    return stack;
}

StackDigit* popDigit(StackDigit* stack, int& item)
{
    StackDigit* newStack = stack;
    item = stack->data;
    stack = stack->next;
    delete newStack;
    return stack;
}

int stackSize(Stack* stack) {
    int size = 0;
    Stack* temp = stack;
    while (temp != NULL) {
        size++;
        temp = temp->next;
    }
    return size;
}


bool isValidInput(string formula) {
    int countOpen = 0;
    int countClosed = 0;
    for (int i = 0; i < formula.length(); i++) {
        if (formula[i] == ' ') {
            return false;
        }
        if (i > 0 && (formula[i] == '+' || formula[i] == '-' || formula[i] == '*' || formula[i] == '/') &&
            (formula[i - 1] == '+' || formula[i - 1] == '-' || formula[i - 1] == '*' || formula[i - 1] == '/')) {
            return false;
        }
        if (formula[i] == '(')
            countOpen++;
        if (formula[i] == ')')
            countClosed++;
    }
    return (countOpen == countClosed);
}


string getNumberFromString(string formula, int& index) {
    string output = "";

    for (index; index < formula.length(); index++) {
        char cymbol = formula[index];

        if (isdigit(cymbol)) output += cymbol;
        else {
            index--;
            break;
        }
    }
    return output;
}


void reverseString(string formula) {
    string output = "";
    for (int i = formula.length() - 1; i >= 0; i--) output += formula[i];
    formula = output;
}


string getNumberFromReversedString(string formula, int index) {
    string output = "";

    for (index; index >= 0; index--) {
        char cymbol = formula[index];

        if (isdigit(cymbol)) output += cymbol;
        else {
            index++;
            break;
        }
    }
    //reverseString(output);
    return output;
}


string convertToReversedPolish(string formula) {

    Stack* stack, * newStack = NULL;
    char a;
    string polishReversed;
    string number;

    for (int k = 0; k < formula.length(); k++)
    {
        if (isdigit(formula[k]))
        {
            number = getNumberFromString(formula, k);
            polishReversed += number;
            polishReversed += " ";

        }

        if (isalpha(formula[k]))
        {
            cout << "������� �� ������ ��������� ����.";
            break;
        }

        if (formula[k] == '(')
            newStack = push(newStack, formula[k]);

        if (formula[k] == ')')
        {
            while ((newStack->�ymbol) != '(')
            {
                newStack = pop(newStack, a);
                if (!newStack)
                    a = '\0';
                polishReversed += a;
                polishReversed += " ";
            }
            stack = newStack;
            newStack = newStack->next;
            delete stack;
        }

        if (formula[k] == '+' || formula[k] == '-' || formula[k] == '*' || formula[k] == '/')
        {
            while (newStack != NULL && priorityPolishReversed(newStack->�ymbol) >= priorityPolishReversed(formula[k]))
            {
                newStack = pop(newStack, a);
                polishReversed += a;
                polishReversed += " ";
            }
            newStack = push(newStack, formula[k]);
        }
    }

    while (newStack != NULL)
    {
        newStack = pop(newStack, a);

        polishReversed += a;
        polishReversed += " ";
    }

    return polishReversed;
}


string convertToPolish(string formula) {
    Stack* stack, * newStack = NULL;
    char a;
    string polish;
    string number;
    //cout << formula.length();

    for (int k = formula.length() - 1; k >= 0; k--) {
        if (isdigit(formula[k])) {
            number = getNumberFromReversedString(formula, k);
            polish += number;
            polish += " ";
        }

        if (isalpha(formula[k])) {
            cout << "������� �� ������ ��������� ����." << endl;
            break;
        }

        if (formula[k] == ')')
            newStack = push(newStack, formula[k]);

        if (formula[k] == '(') {
            while ((newStack->�ymbol) != ')') {
                newStack = pop(newStack, a);
                if (!newStack)
                    a = '\0';
                polish += a;
                polish += " ";
            }
            Stack* stack = newStack;
            newStack = newStack->next;
            delete stack;
        }

        if (formula[k] == '+' || formula[k] == '-' || formula[k] == '*' || formula[k] == '/') {
            while (newStack != NULL && priorityPolish(newStack->�ymbol) > priorityPolish(formula[k])) {
                newStack = pop(newStack, a);
                polish += a;
                polish += " ";
            }
            newStack = push(newStack, formula[k]);
        }
    }

    while (newStack != NULL) {
        newStack = pop(newStack, a);
        polish += a;
        polish += " ";
    }

    return polish;
}


StackDigit* peek(StackDigit* beg) {
    if (beg == NULL) return NULL;
    while (beg->next) beg = beg->next;
    return beg;
}

int fromPrefixToPostfix(string& formula) {
    StackDigit* stack = NULL;
    string postfix = "";
    int temp = 0;
    string number;

    for (int i = formula.length() - 1; i >= 0; i--) {
        char c = formula[i];
        if (isdigit(c)) {
            number = getNumberFromReversedString(formula, i);
            pushDigit(stack, stoi(number));
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            int op1 = 0;
            if (op1 == 0) op1 = temp;
            popDigit(stack, op1);
            int op2 = 0;
            if (op2 == 0) op2 = temp;
            popDigit(stack, op2);
            //temp = (op1 + " " + op2 + " " + c);

            pushDigit(stack, 0);
        }
    }
    popDigit(stack, temp);
    return temp;
}

int calculateInfixOperation(char operat, int first, int second) {
    if (!second) return first;
    if (!first) return second;
    switch (operat) {
    case '+':
        return first + second;
    case '-':
        return first - second;
    case '*':
        return first * second;
    case '/':
        return first / second;
    default:
        return 0;
    };
}

int calculatePostfix(string& formula) {

    if (formula.length() == 0) return 0;
    StackDigit* stack = NULL; // ���� ��� ���������
    string number;
    int result = 0;

    for (int i = 0; i < formula.length(); i++) {
        char c = formula[i];

        if (isdigit(c)) {
            number = getNumberFromString(formula, i);
            stack = pushDigit(stack, stoi(number));
        }

        if (c == '+' || c == '-' || c == '*' || c == '/') {
            int num2 = 0, num1 = 0;

            if (stack == NULL) {
                cout << "������������ ��������� ��� " << c << endl;
                return 0;
            }
            stack = popDigit(stack, num2);

            if (stack == NULL) {
                cout << "������������ ��������� ��� " << c << endl;
                return 0;
            }

            stack = popDigit(stack, num1);

            stack = pushDigit(stack, calculateInfixOperation(c, num1, num2));
        }
    }

    popDigit(stack, result);
    return result;
}

int main()
{
    setlocale(LC_ALL, "RU");
    string formula;
    int choose = 0;

    while (choose != -1)
    {

        cin.clear();
        cin.sync();
        cout << "�������� ��������:" << endl << endl
            << "1. ����������� �������������� ���������� ���������." << endl << endl
            << "2. ��������� �� ������������ ���������." << endl << endl
            << "3. ��������� �������. " << endl << endl
            << "4. ����� �� ���������."
            << endl << endl;

        cout << "�����: ";
        int input;
        cin >> input;
        cout << endl;

        if (cin.fail()) {
            cout << "������������ ����, ������� ����� ������� ��� �����������." << endl << endl;
            _getch();
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (input)
        {
        case 1: {
            cout << "������� ������� ��� ��������." << endl;
            cin >> formula;
            //getline(cin, formula);
            if (isValidInput(formula)) {
                cout << "1) ����� �������� �������� �������." << endl;
                cout << "2) ����� �������� �������." << endl;
                cout << "��� ����� (1/2): ";
                int choice;
                cin >> choice;
                switch (choice)
                {
                case 1: {
                    string reversedPolish = convertToReversedPolish(formula);
                    cout << "��������� � �������� �������� �������: " << reversedPolish << endl;
                    break;
                }
                case 2: {
                    string polish = convertToPolish(formula);
                    cout << "��������� � ������ �������� �������: ";
                    for (int i = polish.length() - 1; i >= 0; i--)
                    {
                        cout << polish[i];
                    }
                    cout << endl;
                    break;
                }
                default:
                    cout << "������������ ����, ������� ����� ������� ��� �����������.";
                    _getch();
                    break;
                }
            }
            else {
                cout << "����������� ������� �������.";
                break;

            }
            break;
        }
        case 2: {
            cout << "������� �������." << endl;
            cin >> formula;
            //getline(cin, formula);
            if (isValidInput(formula)) {
                cout << "��������� ���������" << endl;
            }
            else {
                cout << "������� �������� ������." << endl;
            }
            break;
        }
        case 3:
        {
            cout << "������� ������� ��� ��������." << endl;
            cin >> formula;
            if (isValidInput(formula)) {
                string reversedPolish = convertToReversedPolish(formula);
                cout << "���������: " << calculatePostfix(reversedPolish) << endl;
            }
            else {
                cout << "����������� ������� �������.";
                break;
            }
            break;
        }
        case 4: {
            choose = -1;
            break;
        }
        default: {
            cout << "������������ ����, ������� ����� ������� ��� �����������. " << endl << endl;
            _getch();
            break;
        }
        }
    }


    return 0;
}