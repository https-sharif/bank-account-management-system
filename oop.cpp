// Coded by Sharif Islam
// 24 September 2023
#include<iostream>
#include<string>
#include<vector>
using namespace std;
class BankAccount{
    private:
        string Number,Name;
        double Balance;
    public:
        BankAccount(string number,string name,double balance){
            Number=number;
            Name=name;
            Balance=balance;
        }
        int CheckBalance(string number){
            if(number==Number){
                cout<<"Your balance is "<<Balance<<endl;
                return 1;
            }
            return 0;
        }
        int Deposit(string number){
            if(number==Number){
                double balance;
                cout<<"Enter the amount you want to deposit: ";
                cin>>balance;
                if(balance<0){
                    cout<<"Invalid balance. Please enter a positive amount."<<endl;
                }
                else{
                    Balance+=balance;
                    cout<<"Your balance is now "<<Balance<<endl;
                }
                return 1;
            }
            return 0;
        }
        int Withdraw(string number){
            if(number==Number){
                double balance;
                cout<<"Enter the amount you want to withdraw: ";
                cin>>balance;
                if(balance<=Balance&&balance>0){
                    Balance-=balance;
                    cout<<"Your balance is now "<<Balance<<endl;
                }
                else if(balance<0){
                    cout<<"Invalid withdrawal amount. Please enter a positive amount to withdraw."<<endl;
                }
                else{
                    cout<<"You have insufficient balance to withdraw "<<balance<<". Your current balance is "<<Balance<<endl;
                }
                return 1;
            }
            return 0;
        }

};
int main(){
    int n;
    cout<<"Enter how many bank account: ";
    cin>>n;
    vector<BankAccount> a;
    for(int i=0;i<n;i++){
        string number,name;
        double balance;
        cout<<i+1<<". Enter your bank account number, name and your balance: ";
        cin>>number>>name>>balance;
        BankAccount b(number,name,balance);
        a.push_back(b);
    }
    int x=1;
    while(x!=4){
        cout<<"1. Check Balance"<<endl;
        cout<<"2. Deposit Money"<<endl;
        cout<<"3. Withdraw Money"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>x;
        if(x==1){
            cout<<"Enter your bank number: ";
            string s;
            cin>>s;
            int y=0;
            for(int i=0;i<n;i++){
                y=a[i].CheckBalance(s);
                if(y){
                    break;
                }
            }
            if(!y){
                cout<<"No such bank account number ("<<s<<") exists."<<endl;
            }
        }
        else if(x==2){
            cout<<"Enter your bank number: ";
            string s;
            cin>>s;
            int y=0;
            for(int i=0;i<n;i++){
                y=a[i].Deposit(s);
                if(y){
                    break;
                }
            }
            if(!y){
                cout<<"No such bank account number ("<<s<<") exists."<<endl;
            }
        }
        else if(x==3){
            cout<<"Enter your bank number: ";
            string s;
            cin>>s;
            int y=0;
            for(int i=0;i<n;i++){
                y=a[i].Withdraw(s);
                if(y){
                    break;
                }
            }
            if(!y){
                cout<<"No such bank account number ("<<s<<") exists."<<endl;
            }
        }
        else if(x==4){
            cout<<"Program exited successfully"<<endl;
            return 0;
        }
        else{
            cout<<"Invalid inputs. Try again."<<endl;
        }
    }
}