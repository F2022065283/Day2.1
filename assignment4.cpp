#include <iostream>
using namespace std;

class Account
{
protected:
    string firstname, lastname;
    double currentBalance;

public:
    Account(string firstname, string lastname, double currentBalance)
{
    this->firstname=firstname;
    this->lastname=lastname;
    this->currentBalance=currentBalance;
}
    virtual string getAcctType()
    {
        return "Account";
    }

    virtual double debitTransaction(double debitamount)
    {
        currentBalance -= debitamount;
        return currentBalance;
    }

    virtual double creditTransaction(double creditamount)
    {
        currentBalance += creditamount;
        return currentBalance;
    }

    void print()
    {
      
        cout << firstname << "," << lastname << "\t" << getAcctType() << "\t" << currentBalance << endl;
    }
};

class CheckingAccount : public Account
{
private:
    void chargeFee()
    {
        currentBalance -= 10;
    }

public:
    CheckingAccount(string firstname, string lastname, double currentBalance): Account(firstname, lastname, currentBalance)
         {

         }

    string getAcctType() 
    {
        return "Checking Account";
    }

    double debitTransaction(double debitamount) 
    {
        chargeFee();
         return Account::debitTransaction(debitamount);
    }

    double creditTransaction(double creditamount) 
    
    {
        chargeFee();
         return Account::creditTransaction(creditamount);
    }
};

class SavingsAccount : public Account
{
private:
int t;
    void payInterest()
    {
        currentBalance -= currentBalance * 0.2;
    }

public:
    SavingsAccount(string firstname, string lastname, double currentBalance)
        : Account(firstname, lastname, currentBalance) {
            t=0;
        }

    string getAcctType()
    {
        return "Savings Account";
    }

    double debitTransaction(double debitamount) 
    {
        if(t<2)
        {
            t++;
            cout<<"max limit reached\n";
        payInterest();
         return Account::debitTransaction(debitamount);
        }
        else
        {
            
            cout<<"max limit reached\n";

            return currentBalance;
        }
         
    }

    double creditTransaction(double creditamount) 
    {
        payInterest();
         return Account::creditTransaction(creditamount);
    }
};

int main()
{
    // Example usage
    Account* account1 = new CheckingAccount("Saud", "Yaseen", 200.00);
    Account* account2 = new SavingsAccount("Hunain", "Shahid", 1000.00);

    account1->creditTransaction(500.0);
    account2->debitTransaction(100.0);
    account2->debitTransaction(100.0);
    account2->debitTransaction(100.0);
      //cout << "Account Holder Name \t Account Type \t Account balance\n";
    account1->print();
    account2->print();

    delete account1;
    delete account2;

    return 0;
}
