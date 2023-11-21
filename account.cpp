/*
Name: account.cpp
Purpose: Creates Account objects that can deposit, withdrawal, and transfer money, as well as displaying the account details.
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Account
{
    /*
    Parent class that has an account number, holder, and balance.
    Functionalities include displaying account details, depositing, and withdrawing money.
    Account can overload << operator, which is accessed inplicitly.
    */

    protected:
        string accountNumber;
        string accountHolder;
        double accountBalance;

    public:
        Account(string number, string holder, double balance) // constructor
            : accountNumber(number), accountHolder(holder), accountBalance(balance){}

        string getNumber()
        {
            /*
            Helper function that returns the account number.
            */
            return accountNumber;
        }

        string getHolder()
        {
            /*
            Helper function that returns the account holder.
            */
            return accountHolder;
        }

        double getBalance()
        {
            /*
            Helper function that returns the account balance.
            */
            return accountBalance;
        }

        virtual string getAccountType() const
        {
            /*
            Helper function that returns the account type.
            */
            return "Generic";
        }

        void displayDetails()
        {
            /*
            Function that displays the details of the account using the overloading << operator.
            */
            cout << *this;
        }

        void deposit(double amount)
        {
            /*
            Function that deposits money into account.
            */
            accountBalance += amount;
        }

        bool withdrawal(double amount)
        {
            /*
            Function that withdrawals money from account while ensuring sufficient funds. Returns a bool.
            */
            if (amount > 0 && amount <= accountBalance)
            {
                accountBalance -= amount; // money is withdrawn if funds are sufficient
                return true;
            }

            else
            {
                cout << "Account has insufficient funds." << endl;
                return false;
            }
        }

        friend ostream &operator<<(ostream& COUT, Account& acc)
        {
            /*
            Operator << overloading. Displays account details.
            */
            COUT << "Account Details for " << acc.getAccountType() << " Account (ID: " << acc.accountNumber << "):" << endl;
            COUT << "   Holder: " << acc.accountHolder << endl;
            COUT << "   Balance: $" << fixed << setprecision(2) << acc.accountBalance << endl;
            return COUT;
        }
};


class SavingsAccount: public Account
{
    /*
    Child class of Account.
    SavingsAccount has an interest rate in addition to derived variables from Account.
    Specified functionalities include displaying account details, and withdrawing money.
    SavingsAccount can overload + operator, to transfer money.
    */
    private:
        double interestRate;

    public:
        SavingsAccount(string number, string holder, double balance, double interest) // constructor
            : Account(number, holder, balance), interestRate(interest * 100){}

        double accountMinimum = 100; // set minimum balance

        string getAccountType() const override
        {
            /*
            Helper function that returns the account type. Overrides Account method.
            */
            return "Savings";
        }

        double getInterestRate()
        {
            /*
            Helper function that returns the interest rate.
            */
            return interestRate;
        }

        void displayDetails()
        {
            /*
            Helper function that displays account details using operator << overloading from Account.
            */
            cout << *this;
            cout << "   Interest Rate: " << fixed << setprecision(2) << interestRate << "%" << endl << endl;
        }

        bool withdrawal(double amount)
        {
             /*
            Helper function that withdrawals from account while ensuring sufficient funds (minimum balance). Returns bool.
            */
            if (amount > 0 && accountBalance - amount >= accountMinimum)
            {
                accountBalance -= amount; // money is withdrawn if funds are sufficient
                return true;
            }
            else
            {
                cout << "Savings had insufficient Funds. Minimum balance is $" << accountMinimum << "." << endl;
                return false;
            }
        }

        SavingsAccount operator+(Account &other)
        {
             /*
            Operator + overloading that transfers money between accounts.
            Money is transfered into calling object. Calling object is returned.
            */
            double transfer = 300; // set transfer amount

            // Transaction is performed if the other account has sufficient funds.
            if (other.withdrawal(transfer))
            {
                accountBalance += 300;
                return (*this);
            }

            else
            {
                return (*this);
            }
        }
};

class CurrentAccount : public Account
{
    /*
    Child class of Account.
    CurrentAccount has an overdraft limit in addition to derived variables from Account.
    Specified functionalities include displaying account details, and withdrawing money.
    CurrentAccount can overload + operator, to transfer money.
    */
    protected:
        double overdraftLimit;

    public:
        CurrentAccount(string number, string holder, double balance, double limit)
            : Account(number, holder, balance), overdraftLimit(limit){}

        string getAccountType() const override
        {
            /*
            Helper function that returns the account type. Overrides Account method.
            */
            return "Current";
        }

        void displayDetails()
        {
             /*
            Helper function that displays account details using operator << overloading from Account.
            */
            cout << *this;
            cout << "   Overdraft Limit: $" << fixed << setprecision(2) << overdraftLimit << endl << endl;
        }
        
        bool withdrawal(double amount){
            /*
            Helper function that withdrawals from account while ensuring sufficient funds (overdrafting limit). Returns bool.
            */
            if (amount > 0 && accountBalance - amount >= -overdraftLimit)
            {
                accountBalance -= amount; // money is withdrawn if funds are sufficient
                return true;
            }
            
            else
            {
                cout << "Current has insufficient funds. Overdrafting limit is " << overdraftLimit << "." << endl;
                return false;
            }
        }

        CurrentAccount operator+(Account &other)
        {
            /*
            Operator + overloading that transfers money between accounts.
            Money is transfered into calling object. Calling object is returned.
            */
            double transfer = 300; // set transfer amount
            // Transaction is performed if the other account has sufficient funds.
            if (other.withdrawal(transfer))
            {
                accountBalance += 300;
                return (*this);
            }

            else
            {
                return (*this);
            }
        }
};  

int main()
{
    SavingsAccount savings("S123", "John Doe", 1000, 0.02);
    CurrentAccount current("C456", "Jane Doe", 2000, 500);

    savings.displayDetails();
    current.displayDetails();

    savings.deposit(500);
    current.withdrawal(1000);

    cout << "Account Details after deposit and withdrawal:" << endl;
    savings.displayDetails();
    current.displayDetails();

    current = current + savings;

    cout << "Account Details after transfer:" << endl;
    savings.displayDetails();
    current.displayDetails();

    return 0;
}