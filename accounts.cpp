#include <iostream>
#include <string>

using namespace std;

class Accounts{
    protected:
        string accountNumber;
        string accountHolder;
        double accountBalance;

    public:
        Accounts(string number, string holder, double balance)
            : accountNumber(number), accountHolder(holder), accountBalance(balance){}

        string getNumber(){
            return accountNumber;
        }

        string getHolder(){
            return accountHolder;
        }

        double getBalance(){
            return accountBalance;
        }

        virtual string getAccountType() const{
            return "Generic";
        }

        void displayDetails(){
            cout << "Account Details for " << getAccountType() << " Account (ID: " << getNumber() << "):" << endl;
            cout << "   Holder: " << getHolder() << endl;
            cout << "   Balance: $" << getBalance() << endl;
        }
        
        void deposit(double amount){
            accountBalance += amount;
        }

        void withdrawal(double amount){
            if (amount > 0 && amount <= accountBalance){
                accountBalance -= amount;
            }

            else {
                cout << "Insufficient funds." << endl;
            }
        }

        friend ostream& operator<<(ostream& os, const Accounts& acc) {
        os << "Account Details for " << acc.getAccountType() << " (ID: " << acc.accountNumber << "):" << endl;
        os << "   Holder: " << acc.accountHolder << endl;
        os << "   Balance: $" <<  acc.accountBalance << endl;
        return os;
        }
};


Accounts operator+(Accounts &toAccount, Accounts &fromAccount){
    double transferAmount = 300;
    fromAccount.withdrawal(transferAmount);
    toAccount.deposit(transferAmount);
    return toAccount;
}


class SavingsAccount: public Accounts{
    private:
        double interestRate;

    public:
        SavingsAccount(string number, string holder, double balance, double interest)
            : Accounts(number, holder, balance), interestRate(interest){}

        string getAccountType() const override{
            return "Saving";
        }

        void displayDetails(){
            Accounts::displayDetails();
            cout << "   Interest Rate: " << interestRate << "%" << endl << endl;
        }

        void withdrawal(double amount){
            double accountMinimum = 100;
            if (amount > 0 && accountBalance - amount >= accountMinimum){
                accountBalance -= amount;
            }
            else{
                cout << "Insufficient Funds. Minimum balance is $" << accountMinimum << "." << endl;
            }
        }
};

class CurrentAccount : public Accounts{
    private:
        double overdraftLimit;

    public:
        CurrentAccount(string number, string holder, double balance, double limit)
            : Accounts(number, holder, balance), overdraftLimit(limit){}

        string getAccountType() const override{
            return "Current";
        }

        void displayDetails(){
            Accounts::displayDetails();
            cout << "   Overdraft Limit: $" << overdraftLimit << endl << endl;
        }
        void withdrawal(double amount){
            if (amount > 0 && accountBalance - amount >= -overdraftLimit){
                accountBalance -= amount;
            }
            else{
                cout << "Insufficient funds. Overdrafting limit is " << overdraftLimit << "." << endl;
            }
        }
};  

int main(){
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdrawal(1000);

    cout << "Account Details after deposit and withdrawal:" << endl;
    savings.displayDetails();
    current.displayDetails();

    current + savings;

    cout << "Account Details after transfer:" << endl;
    savings.displayDetails();
    current.displayDetails();

    return 0;
}