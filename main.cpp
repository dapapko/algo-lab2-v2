#include <iostream>
#include "StackMachine.h"
using T = int;

int main(int argc, char *argv[]) {
    char notation = *argv[1];
    string s;
    vector<string> v;
    cout << "Enter expression: ";
    while ((cin.peek() != '\n') && (cin.peek() != EOF)) {
        cin >> s;
        v.push_back(s);
    }
    try {
        Binnum<T> result;
        auto* machine = new StackMachine<T>(v);
        if (notation == 'i') machine->infixToRPN();
        result = machine->evaluate();

        cout << "Result: " << result << endl;
        cout << "Result (bin): ";
        result.prt_bin();
        cout << endl;
    } catch (std::exception &e) {
        cout << "Smth is wrong with your expression" << endl;
    }
}
