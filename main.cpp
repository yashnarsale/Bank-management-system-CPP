#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class BankAccount {
    int accountNumber;
    string name, fatherName, adhaarNumber, phoneNumber, email;
    float amount;

    fstream file, file1;

public:
    int accountToBeManaged;

    void createAccount();
    void depositAmount();
    void withdrawAmount();
    void checkInfo();
    void deleteAccount();
    void updateAccount();

    void loginAccount(char choice) {
        cout << "Enter your account number: ";
        cin >> accountToBeManaged;

        bool accountExists = false;
        file.open("data.txt", ios::in);
        if (file.is_open()) {
            int accNoFromFile;
            while (file >> accNoFromFile >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount) {
                if (accNoFromFile == accountToBeManaged) {
                    accountExists = true;
                    break;
                }
            }
            file.close();
        }

        if (accountExists) {
            while (true) {
                system("cls");
                cout << "\n\n\n\t\t.......:::Our services:::......." << endl;
                cout << "\n\t\t:: press 1 to Deposit  Amount  :: ";
                cout << "\n\t\t:: press 2 to Withdraw Amount  ::";
                cout << "\n\t\t:: press 3 to Check    Info    ::";
                cout << "\n\t\t:: press 4 to Update    Info    ::";
                cout << "\n\t\t:: press 5 to Delete    Info    ::";
                cout << "\n\t\t:: press 0 to Exit     Menu    ::";
                cout << "\n\t\t:: ........................... ::" << endl;
                cout << "\t\t\t\t";
                cin >> choice;

                switch (choice) {
                    case '1':
                        depositAmount();
                        break;
                    case '2':
                        withdrawAmount();
                        break;
                    case '3':
                        checkInfo();
                        break;
                    case '4':
                        updateAccount();
                        break;
                    case '5':
                        deleteAccount();
                        break;
                    case '0':
                        return;
                    default:
                        cout << "Invalid Choice...!" << endl;
                        break;
                }
                system("pause");
            }
        } else {
            cout << "Account does not exist. Please create an account first." << endl;
        }
    }
};

void BankAccount::createAccount() {
    srand(time(0));
    accountNumber = rand() * rand() + rand() * rand();

    cout << "Enter your name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter your father's name: ";
    getline(cin, fatherName);

    cout << "Enter your Adhaar number: ";
    cin >> adhaarNumber;

    cout << "Enter your phone number: ";
    cin >> phoneNumber;

    cout << "Enter your email: ";
    cin >> email;

    cout << "Enter your initial account balance: ";
    cin >> amount;

    file.open("data.txt", ios::out | ios::app);
    file << accountNumber << "\t" << name << "\t" << fatherName << "\t" << adhaarNumber << "\t" << phoneNumber << "\t" << email << "\t" << amount << endl;
    file.close();

    cout << "Your account number is: " << accountNumber << endl;
    cout << "Please save it for future reference." << endl;
}

void BankAccount::depositAmount() {
    int amountToBeDeposited;

    cout << "Enter the amount to deposit: ";
    cin >> amountToBeDeposited;

    file.open("data.txt", ios::in);
    file1.open("data1.txt", ios::out | ios::app);

    file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;

    while (!file.eof()) {
        if (accountNumber == accountToBeManaged) {
            amount += amountToBeDeposited;
            file1 << accountNumber << "\t" << name << "\t" << fatherName << "\t" << adhaarNumber << "\t" << phoneNumber << "\t" << email << "\t" << amount << endl;
            cout << "Deposit successful. Your new balance is: " << amount << endl;
        } else {
            file1 << accountNumber << "\t" << name << "\t" << fatherName << "\t" << adhaarNumber << "\t" << phoneNumber << "\t" << email << "\t" << amount << endl;
        }
        file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt", "data.txt");
}

void BankAccount::withdrawAmount() {
    int amountToBeWithdrawn;

    cout << "Enter the amount to withdraw: ";
    cin >> amountToBeWithdrawn;

    file.open("data.txt", ios::in);
    file1.open("data1.txt", ios::out | ios::app);

    file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;

    while (!file.eof()) {
        if (accountNumber == accountToBeManaged) {
            if (amount >= amountToBeWithdrawn) {
                amount -= amountToBeWithdrawn;
                file1 << accountNumber << "\t" << name << "\t" << fatherName << "\t" << adhaarNumber << "\t" << phoneNumber << "\t" << email << "\t" << amount << endl;
                cout << "Withdrawal successful. Your new balance is: " << amount << endl;
            } else {
                cout << "Insufficient balance." << endl;
            }
        } else {
            file1 << accountNumber << "\t" << name << "\t" << fatherName << "\t" << adhaarNumber << "\t" << phoneNumber << "\t" << email << "\t" << amount << endl;
        }
        file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt", "data.txt");
}

void BankAccount::checkInfo() {
    file.open("data.txt", ios::in);

    if (!file) {
        cout << "File opening error!" << endl;
    } else {
        file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;

        while (!file.eof()) {
            if (accountNumber == accountToBeManaged) {
                system("cls");
                cout << "\n---------------------------" << endl;
                cout << "Account Number: " << accountNumber << endl;
                cout << "Name: " << name << endl;
                cout << "Father's Name: " << fatherName << endl;
                cout << "Adhaar Number: " << adhaarNumber << endl;
                cout << "Phone Number: " << phoneNumber << endl;
                cout << "Email: " << email << endl;
                cout << "Amount: " << amount << endl;
                cout << "---------------------------" << endl;
            }
            file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;
        }
    }

    file.close();
    system("pause");
}

void BankAccount::deleteAccount() {
    file.open("data.txt", ios::in);
    file1.open("data1.txt", ios::out | ios::app);

    file >> accountNumber>> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;

    while (!file.eof()) {
        if (accountNumber != accountToBeManaged) {
            file1 << accountNumber << "\t" << name << "\t" << fatherName << "\t" << adhaarNumber << "\t" << phoneNumber << "\t" << email << "\t" << amount << endl;
        }
        file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt", "data.txt");
    cout << "Account deleted successfully." << endl;
}

void BankAccount::updateAccount() {
    string newName, newFatherName, newAdhaarNumber, newPhoneNumber, newEmail;
    float newAmount;

    cout << "Enter new name: ";
    cin.ignore();
    getline(cin, newName);

    cout << "Enter new father's name: ";
    getline(cin, newFatherName);

    cout << "Enter new Adhaar number: ";
    cin >> newAdhaarNumber;

    cout << "Enter new phone number: ";
    cin >> newPhoneNumber;

    cout << "Enter new email: ";
    cin >> newEmail;

    cout << "Enter new amount: ";
    cin >> newAmount;

    file.open("data.txt", ios::in);
    file1.open("data1.txt", ios::out | ios::app);

    file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;

    while (!file.eof()) {
        if (accountNumber == accountToBeManaged) {
            file1 << accountNumber << "\t" << newName << "\t" << newFatherName << "\t" << newAdhaarNumber << "\t" << newPhoneNumber << "\t" << newEmail << "\t" << newAmount << endl;
            cout << "Account updated successfully." << endl;
        } else {
            file1 << accountNumber << "\t" << name << "\t" << fatherName << "\t" << adhaarNumber << "\t" << phoneNumber << "\t" << email << "\t" << amount << endl;
        }
        file >> accountNumber >> name >> fatherName >> adhaarNumber >> phoneNumber >> email >> amount;
    }

    file.close();
    file1.close();
    remove("data.txt");
    rename("data1.txt", "data.txt");
}

int main() {
    BankAccount accountManager;
    char choice;

    do {
        system("cls");
        cout << "\n\n\n\t\t***********************" << endl;
        cout << "\t\t....:::Yash Bank:::...." << endl;
        cout << "\t\t***********************" << endl;
        cout << "\n\t\t:: press 1 to Login  Account :: ";
        cout << "\n\t\t:: press 2 to Create Account ::";
        cout << "\n\t\t:: press 0 to Exit           ::";
        cout << "\n\t\t:: ......................... ::\n\t\t\t\t";
        cin >> choice;

        switch (choice) {
            case '1':
                accountManager.loginAccount(choice);
                break;
            case '2':
                accountManager.createAccount();
                break;
            case '0':
                cout << "\nThank you for using Yash Bank!\n";
                exit(0);
                break;
            default:
                cout << "\n Invalid choice...! ";
                break;
        }
    } while (choice != '0');

    return 0;
}