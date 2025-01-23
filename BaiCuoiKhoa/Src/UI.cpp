#include "UI.hpp"
#include <iostream>

using namespace std;

int UI::getUserChoice(const string& prompt){
    int choice;
    cout << prompt;
    cin >> choice;
    return choice;
}

void UI::showMessage(const string& message){
    cout << message << endl;
}

string UI::getInputString(const string& prompt){
    string input;
    cout << prompt;
    cin >> input;
    return input;
}


