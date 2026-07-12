#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <iomanip>
#include "SystemManager.h"
#include "ErrorItem.h"
using namespace std;

void printDivider() {
    cout << "------------------------------------------------------------------\n";
}

string difficultyToString(ErrorItem::Difficulty diff) {
    switch (diff) {
        case ErrorItem::Difficulty::EASY: return "Easy";
        case ErrorItem::Difficulty::MEDIUM: return "Medium";
        case ErrorItem::Difficulty::HARD: return "Hard";
        default: return "Unknown";
    }
}

string errorTypeToString(ErrorItem::ErrorType type) {
    switch (type) {
        case ErrorItem::ErrorType::CONCEPT: return "Concept";
        case ErrorItem::ErrorType::CALCULATION: return "Calculation";
        case ErrorItem::ErrorType::CARELESS: return "Careless";
        default: return "Unknown";
    }
}

string subjectToString(ErrorItem::Subject sub) {
    switch (sub) {
        case ErrorItem::Subject::MATH: return "Math";
        case ErrorItem::Subject::PHYSICS: return "Physics";
        case ErrorItem::Subject::CHEMISTRY: return "Chemistry";
        default: return "Unknown";
    }
}

void displayErrorTable(const vector<shared_ptr<ErrorItem>>& items) {
    if (items.empty()) {
        cout << "\n[!] No error items found.\n";
        return;
    }

    printDivider();
    cout << left << setw(5) << "ID" 
         << setw(12) << "Subject" 
         << setw(10) << "Difficulty" 
         << setw(15) << "Type" 
         << "Description\n";
    printDivider();

    for (const auto& item : items) {
        cout << left << setw(5) << item->getId()
             << setw(12) << subjectToString(item->getSubject())
             << setw(10) << difficultyToString(item->getDifficulty())
             << setw(15) << errorTypeToString(item->getErrorType())
             << (item->getDescription().length() > 30 ? item->getDescription().substr(0, 27) + "..." : item->getDescription()) 
             << "\n"
             << "     -> Reason: " << item->getWrongReason() << "\n";
    }
    printDivider();
}

void showDashboard(SystemManager& manager) {
    while (true) {
        cout << "\n==================================================\n";
        cout << "   WELCOME BACK, " << manager.getCurrentUser()->getStudentName() << " !\n";
        cout << "==================================================\n";
        cout << "1. View All Error Items (Newest First)\n";
        cout << "2. View All Error Items (Oldest First)\n";
        cout << "3. Filter Errors by Difficulty\n";
        cout << "4. Filter Errors by Error Type\n";
        cout << "5. Add a New Error Item\n";
        cout << "6. Delete an Error Item\n";
        cout << "7. Logout\n";
        cout << "==================================================\n";
        cout << "Please choose an option (1-7): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[!] Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore(); // clear newline

        if (choice == 1) {
            auto items = manager.getErrorsSortedByTime(false); // Descending
            cout << "\n--- ALL ERROR ITEMS (NEWEST FIRST) ---\n";
            displayErrorTable(items);
        }
        else if (choice == 2) {
            auto items = manager.getErrorsSortedByTime(true); // Ascending
            cout << "\n--- ALL ERROR ITEMS (OLDEST FIRST) ---\n";
            displayErrorTable(items);
        }
        else if (choice == 3) {
            cout << "\nSelect Difficulty to Filter:\n";
            cout << "0. Easy\n1. Medium\n2. Hard\nChoice: ";
            int diffChoice;
            cin >> diffChoice;
            if (diffChoice >= 0 && diffChoice <= 2) {
                auto items = manager.filterByDifficulty(static_cast<ErrorItem::Difficulty>(diffChoice));
                cout << "\n--- FILTERED ERROR ITEMS ---\n";
                displayErrorTable(items);
            } else {
                cout << "\n[!] Invalid choice.\n";
            }
        }
        else if (choice == 4) {
            cout << "\nSelect Error Type to Filter:\n";
            cout << "0. Concept\n1. Calculation\n2. Careless\nChoice: ";
            int typeChoice;
            cin >> typeChoice;
            if (typeChoice >= 0 && typeChoice <= 2) {
                auto items = manager.filterByErrorType(static_cast<ErrorItem::ErrorType>(typeChoice));
                cout << "\n--- FILTERED ERROR ITEMS ---\n";
                displayErrorTable(items);
            } else {
                cout << "\n[!] Invalid choice.\n";
            }
        }
        else if (choice == 5) {
            string desc, reason;
            int diffChoice, typeChoice, subChoice;

            cout << "\nEnter Problem Description: ";
            getline(cin, desc);
            cout << "Enter Why You Got It Wrong (Reason): ";
            getline(cin, reason);

            cout << "Select Difficulty (0: Easy, 1: Medium, 2: Hard): ";
            cin >> diffChoice;
            cout << "Select Error Type (0: Concept, 1: Calculation, 2: Careless): ";
            cin >> typeChoice;
            cout << "Select Subject (0: Math, 1: Physics, 2: Chemistry): ";
            cin >> subChoice;

            if (diffChoice >= 0 && diffChoice <= 2 && typeChoice >= 0 && typeChoice <= 2 && subChoice >= 0 && subChoice <= 2) {
                manager.addErrorNotebookItem(
                    desc, reason,
                    static_cast<ErrorItem::Difficulty>(diffChoice),
                    static_cast<ErrorItem::ErrorType>(typeChoice),
                    static_cast<ErrorItem::Subject>(subChoice)
                );
                cout << "\n[+] Error item added successfully! Saved to your notebook.\n";
            } else {
                cout << "\n[!] Invalid options. Item creation aborted.\n";
            }
        }
        else if (choice == 6) {
            auto items = manager.getErrorsSortedByTime(false);
            displayErrorTable(items);
            if (items.empty()) continue;

            cout << "Enter the ID of the item you want to delete: ";
            int itemId;
            cin >> itemId;
            manager.deleteErrorNotebookItem(itemId);
            cout << "\n[-] Item deleted (if the ID existed).\n";
        }
        else if (choice == 7) {
            manager.logout();
            cout << "\n[<=] Logged out successfully. Goodbye!\n";
            break;
        }
        else {
            cout << "\n[!] Invalid option. Please select between 1 and 7.\n";
        }
    }
}

int main() {
    SystemManager manager;
    cout << "==================================================\n";
    cout << "        Welcome to Error Notebook App             \n";
    cout << "==================================================\n";

    while (true) {
        cout << "\n1. Login\n";
        cout << "2. Register New Account\n";
        cout << "3. Exit Application\n";
        cout << "--------------------------------------------------\n";
        cout << "Please select an option (1-3): ";

        int mainChoice;
        if (!(cin >> mainChoice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n[!] Invalid input. Please enter a number.\n";
            continue;
        }
        cin.ignore();

        if (mainChoice == 1) {
            string uname, pwd;
            cout << "\n--- USER LOGIN ---\n";
            cout << "Username: ";
            cin >> uname;
            cout << "Password: ";
            cin >> pwd;

            if (manager.login(uname, pwd)) {
                showDashboard(manager);
            } else {
                cout << "\n[!] Login failed. Wrong username or password.\n";
            }
        }
        else if (mainChoice == 2) {
            string uname, pwd, name;
            cout << "\n--- CREATE ACCOUNT ---\n";
            cout << "Choose a Username: ";
            cin >> uname;
            cout << "Choose a Password: ";
            cin >> pwd;
            cin.ignore(); // clear newline before getline
            cout << "Enter Your Real Name: ";
            getline(cin, name);

            if (manager.registerUser(uname, pwd, name)) {
                cout << "\n[+] Registration successful! You can log in now.\n";
            } else {
                cout << "\n[!] Registration failed. Username might already exist.\n";
            }
        }
        else if (mainChoice == 3) {
            cout << "\nThank you for using Error Notebook App. Exiting...\n";
            break;
        }
        else {
            cout << "\n[!] Invalid option. Please select 1, 2, or 3.\n";
        }
    }

    return 0;
}
