#include <iostream>
#include <string>
#include <iomanip>

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
            cout << *this;
            //cout << "Account Details for " << getAccountType() << " Account (ID: " << getNumber() << "):" << endl;
            //cout << "   Holder: " << getHolder() << endl;
            //cout << "   Balance: $" << getBalance() << endl;
        }

        void deposit(double amount){
            accountBalance += amount;
        }

        bool withdrawal(double amount){
            if (amount > 0 && amount <= accountBalance){
                accountBalance -= amount;
                return true;
            }

            else {
                cout << "Account has insufficient funds." << endl;
                return false;
            }
        }

        friend ostream &operator<<(ostream& COUT, Accounts& acc) {
            COUT << "Account Details for " << acc.getAccountType() << " Account (ID: " << acc.accountNumber << "):" << endl;
            COUT << "   Holder: " << acc.accountHolder << endl;
            COUT << "   Balance: $" << fixed << setprecision(2) << acc.accountBalance << endl;
            return COUT;
        }
};


class SavingsAccount: public Accounts{
    private:
        double interestRate;

    public:
        SavingsAccount(string number, string holder, double balance, double interest)
            : Accounts(number, holder, balance), interestRate(interest * 100){}

        double accountMinimum = 100;

        string getAccountType() const override{
            return "Savings";
        }

        double getInterestRate() {
            return interestRate;
        }

        void displayDetails(){
            cout << *this;
            cout << "   Interest Rate: " << fixed << setprecision(2) << interestRate << "%" << endl << endl;
        }

        bool withdrawal(double amount){
            if (amount > 0 && accountBalance - amount >= accountMinimum){
                accountBalance -= amount;
                return true;
            }
            else{
                cout << "Savings had insufficient Funds. Minimum balance is $" << accountMinimum << "." << endl;
                return false;
            }
        }

        SavingsAccount operator+(Accounts &other){
            double transfer = 300;
            if (other.withdrawal(transfer)){
                accountBalance += 300;
                return (*this);
            }

            else{
                return (*this);
            }
        }
};

class CurrentAccount : public Accounts{
    protected:
        double overdraftLimit;

    public:
        CurrentAccount(string number, string holder, double balance, double limit)
            : Accounts(number, holder, balance), overdraftLimit(limit){}

        string getAccountType() const override{
            return "Current";
        }

        void displayDetails(){
            cout << *this;
            cout << "   Overdraft Limit: $" << fixed << setprecision(2) << overdraftLimit << endl << endl;
        }
        
        bool withdrawal(double amount){
            if (amount > 0 && accountBalance - amount >= -overdraftLimit){
                accountBalance -= amount;
                return true;
            }
            else{
                cout << "Current has insufficient funds. Overdrafting limit is " << overdraftLimit << "." << endl;
                return false;
            }
        }

        CurrentAccount operator+(Accounts &other){
            double transfer = 300;
            if (other.withdrawal(transfer)){
                accountBalance += 300;
                return (*this);
            }

            else{
                return (*this);
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

    savings = savings + current;

    cout << "Account Details after transfer:" << endl;
    savings.displayDetails();
    current.displayDetails();

    return 0;
}