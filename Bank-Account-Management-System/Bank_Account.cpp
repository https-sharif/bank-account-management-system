// Coded by Sharif Islam
// 24 September 2023
// Updated on 1 August 2024

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <limits>
#include <tuple>

using namespace std;

class BankAccount
{
private:
    string Number, Name;
    long long Balance;
    vector<tuple<string,int,string> > transactions;
    int Pin;

public:

    BankAccount() : Number(""), Name(""), Balance(0), Pin(0) {}
    BankAccount(string number, string name, long long balance, int pin) : Number(number) , Name(name) , Balance(balance), Pin(pin){};

    void CheckBalance()
    {
        cout << "Dear " << Name << ", Your balance is $" << Balance << endl;
        cout<<endl;
    }

    void Deposit()
    {
        long long balance;
        cout << "Enter the amount you want to deposit: $";
        cin >> balance;
        if (balance < 0)
        {
            cout << "Invalid balance. Please enter a positive amount." << endl;
        }
        else
        {
            transactions.push_back({"Deposit", balance,""});
            Balance += balance;
            cout << "Dear " << Name << ", Your balance is now $" << Balance << endl;
        }
        cout<<endl;
    }

    void Withdraw()
    {
        long long balance;
        cout << "Enter the amount you want to withdraw: $";
        cin >> balance;
        if (balance <= Balance && balance > 0)
        {
            transactions.push_back({"Withdrawal", balance,""});
            Balance -= balance;
            cout << "Dear " << Name << ", Your balance is now $" << Balance << endl;
        }
        else if (balance < 0)
        {
            cout << "Invalid withdrawal amount. Please enter a positive amount to withdraw." << endl;
        }
        else
        {
            cout << "Dear " << Name << ", You have insufficient balance to withdraw $" << balance << ". Your current balance is $" << Balance << endl;
        }
        cout<<endl;
    }

    void printTransactions(){
        int line = 1;
        cout<<"Type of transaction \t Amount \t\t Sender/Recipient"<<endl;
        for(auto &[status,amount,from] : transactions){
            cout << line << ". " << status << " : \t\t" << amount << "\t\t " << from << endl;
            line++;
        }
        cout<<endl;
    }

    bool transferMoney(BankAccount &account,int amount){
        if(amount<=Balance){
            Balance -= amount;
            transactions.push_back({"Transfer Money",amount,account.getName()});
            return true;
        }
        else{
            return false;
        }
    }

    void receiveMoney(BankAccount &account, int amount){
        Balance += amount;
        transactions.push_back({"Received Money", amount ,account.getName()});
    }

    string getNumber()
    {
        return Number;
    }

    long long getBalance(){
        return Balance;
    }
    string getName(){
        return Name;
    }
    int getPin(){
        return Pin;
    }
    void setName(string name){
        Name = name;
    }
    void setPin(int pin){
        Pin = pin;
    }
};

bool validatePin(int pin1,int pin2){
    if(pin1 < 1000 || pin1 >9999 || pin2 < 1000 || pin2 > 9999){
        cout << "Invalid pin! Pin need to a 4-digit number" << endl;
        return false;
    }
    if(pin1 != pin2){
        cout << "The confirmation pin did not match. Try again." << endl;
        return false;
    }
    return true;
}

void editDetails(BankAccount &account){
    int choice = 0;

    while(choice != 3){
        cout << "What information do you want to edit? " << endl;
        cout << "1. Name" << endl;
        cout << "2. Pin" << endl;
        cout << "3. Save Changes and Exit" << endl;

        cout << "Enter your choice: ";
        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number between 1 and 3." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your choice: ";
        }
        string newName;
        int oldPin,newPin,confirmationPin;
        int tries;
        switch (choice){
            case 1:
                cout << "Enter the new name: ";
                cin.ignore();
                getline(cin,newName);
                tries = 0;
                do{
                    cout << "Enter your pin to confirm your edit: ";
                    cin >> oldPin;
                    tries++;
                    if(oldPin == account.getPin()){
                        break;
                    }
                    else{
                        cout << "Wrong pin entered! Try again. " << endl;
                    }
                }while(tries<3);
                if(oldPin != account.getPin()){
                    cout << "You have entered your pin incorrectly 3 times. Try again later." << endl;
                    choice = 3;
                    break;
                }

                account.setName(newName);
                cout << "Your name has been updated successfully." << endl;
                cout << endl;
                break;
            case 2:
                tries = 0;
                do{
                    cout << "Enter your old pin: ";
                    cin >> oldPin;
                    tries++;
                    if(oldPin == account.getPin()){
                        break;
                    }
                    else{
                        cout << "Wrong pin entered! Try again. " << endl;
                    }
                }while(tries<3);
                if(oldPin != account.getPin()){
                    cout << "You have entered your old pin incorrectly 3 times. Try again later." << endl;
                    cout << endl;
                    choice = 3;
                    break;
                }

                do{
                    cout << "Enter your new pin: ";
                    cin >> newPin;
                    cout << "Enter your new pin again to confirm: ";
                    cin >> confirmationPin;
                }
                while(!validatePin(newPin,confirmationPin));
                
                account.setPin(newPin);
                cout << "Your pin has been updated successfully." << endl;

                break;
            case 3: 
                cout << "Your changes have been saved." << endl;
                return;
            default:
                cout << "Enter a valid number between 1 and 3. " << endl;
                break;
        }
    }
}

bool validBankAccountNumber(const string &number)
{
    if(number.size()<8 || number.size() > 14){
        cout << "Invalid bank account number. The bank account number should be between 8-digit and 14-digit. Try again!" << endl;
        return false;
    }
    for (auto c : number)
    {
        if (c < '0' || c > '9')
        {
            cout << "Invalid bank account number. The bank number should have only numbers. Try again!" << endl;
            return false;
        }
    }
    return true;
}

void handleAccount(unordered_map<string,BankAccount> &accounts,BankAccount &account)
{
    int choice = 0;
    while (choice != 7)
    {
        cout << "1. Check Balance" << endl;
        cout << "2. Deposit Money" << endl;
        cout << "3. Withdraw Money" << endl;
        cout << "4. Print Transactions" << endl;
        cout << "5. Transfer Money" << endl;
        cout << "6. Edit Account Information" << endl;
        cout << "7. Log out" << endl;
        cout<<endl;
        cout << "Enter your choice: ";

        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your choice: ";
        }
        string recipient;
        int amount;
        switch (choice)
        {
        case 1:
            account.CheckBalance();
            break;
        case 2:
            account.Deposit();
            break;
        case 3:
            account.Withdraw();
            break;
        case 4:
            account.printTransactions();
            break;
        case 5:
            do{
                cout << "Enter the recipient bank account number: ";
                cin>>recipient;
            }while(!validBankAccountNumber(recipient));
            if(account.getNumber() == recipient){
                cout<< "You cannot transfer money to your own account. Please select a different recipient." << endl;
                cout<<endl;
            }
            else if(accounts.find(recipient) == accounts.end()){
                cout << "The recipient does not exist in the bank records. Please check if you entered the information correctly." << endl;
            }
            else{
                do{
                    cout << "Enter the amount you want to transfer: ";
                    cin >> amount;
                    if(amount<=0){
                        cout << "Amount should be positive! Enter the amount you want to transfer: ";
                    }
                }while(amount<=0);

                if(account.transferMoney(accounts[recipient],amount)){
                    cout << "Transaction successful." << endl;
                    cout << "Your balance is now $" << account.getBalance() << endl;
                    accounts[recipient].receiveMoney(account,amount);
                    cout<<endl;
                }
                else{
                    cout << "Transaction failed. Insufficient amount in your account." << endl;
                    cout << "You have $" << account.getBalance() << endl;
                }
            }
            cout<<endl;
            break;
        case 6:
            editDetails(account);
            break;
        case 7:
            cout << "Logged out successfully." << endl;
            cout<<endl;
            return;
        default:
            cout << "Invalid inputs. Try again." << endl;
            cout<<endl;
            break;
        }
    }
}

int main()
{
    unordered_map<string,BankAccount> accounts;
    int choice = 0;
    while (choice != 4)
    {
        cout << "1. Add an account" << endl;
        cout << "2. Log in to an account" << endl;
        cout << "3. Delete an account" << endl;
        cout << "4. Exit program" << endl;
        cout<<"Enter your choice: ";
        cout<<endl;
        while (!(cin >> choice))
        {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Enter your choice: ";
        }
        string number, name;
        long long balance;
        bool valid = true;
        int tries;
        switch (choice)
        {
            case 1:
                cout << "Enter your bank account number: ";
                cin >> number;
                while (!validBankAccountNumber(number) || accounts.find(number) != accounts.end())
                {
                    if (accounts.find(number) != accounts.end())
                    {
                        cout << "The accounts already exists in the bank records." << endl;
                    }
                    cout << "Enter your bank account number: ";
                    cin >> number;
                }
                cout<<endl;
                cin.ignore();
                cout << "Enter your full name: ";
                getline(cin, name);
                cout << "Enter your balance: ";

                while (true)
                {
                    cin >> balance;
                    if (cin.fail() || balance < 0)
                    {
                        cout << "Invalid input. Please enter a positive number." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    }
                    else
                    {
                        break;
                    }
                }
                int pin1,pin2;
                do{
                    cout << "Enter your pin: ";
                    cin >> pin1;
                    cout << "Enter your pin again to confirm: ";
                    cin >> pin2;
                }
                while(!validatePin(pin1,pin2));

                cout << "Name: " << name << endl;
                cout << "Account Number: " << number << endl;
                cout << "Balance: " << balance << endl;
                cout<<endl;
                cout << "Do you want to confirm this information? (Y/N): ";

                char confirmation;
                cin >> confirmation;

                if (confirmation == 'Y' || confirmation == 'y')
                {
                    BankAccount acc(number, name, balance, pin1);
                    accounts[number] = acc;
                }

                break;
            case 2:
                cout << "Enter your bank account number: ";
                cin >> number;

                if(accounts.find(number) != accounts.end()){
                    int pin;
                    tries = 0;
                    do{
                        cout << "Enter your pin to log in: ";
                        cin >> pin;
                        tries++;
                        if(pin == accounts[number].getPin()){
                            break;
                        }
                        else{
                            cout << "Wrong pin entered! Try again. " << endl;
                        }
                    }while(tries<3);

                    if(pin != accounts[number].getPin()){
                        cout << "You have entered your old pin incorrectly 3 times. Try again later." << endl;
                        cout << endl;
                        break;
                    }
                    handleAccount(accounts,accounts[number]);
                }
                else
                {
                    cout << "No such bank account number exists." << endl;
                    cout<<endl;
                }

                break;
            case 3:
                cout << "Enter your bank account number: ";
                cin >> number;
                if(accounts.find(number) != accounts.end()){
                    int pin;
                    tries = 0;
                    do{
                        cout << "Enter your pin to log in: ";
                        cin >> pin;
                        tries++;
                        if(pin == accounts[number].getPin()){
                            break;
                        }
                        else{
                            cout << "Wrong pin entered! Try again. " << endl;
                        }
                    }while(tries<3);

                    if(pin != accounts[number].getPin()){
                        cout << "You have entered your old pin incorrectly 3 times. Try again later." << endl;
                        cout << endl;
                        break;
                    }

                    cout << "Do you want to confirm deletion? (Y/N): ";

                    char confirmation;
                    cin >> confirmation;

                    if (confirmation == 'Y' || confirmation == 'y')
                    {
                        accounts.erase(number);
                    }

                }
                else
                {
                    cout << "No such bank account number exists." << endl;
                    cout<<endl;
                }
                break;
            case 4:
                cout << "Program exited successfully." << endl;
                cout<<endl;
                return 0;
            default: 
                cout << "Invalid choice! Please enter a number between 1 - 4." << endl;
                cout<<endl;
                break;
        }
        cout<<endl;
    }
    return 0;
}
