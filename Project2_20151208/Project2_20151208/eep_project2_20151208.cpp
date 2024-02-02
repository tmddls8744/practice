/**************************************** Bank Account *********************************************
 * EEP Project 2
 * Name: ¹Ú½ÂÀÎ
 * Student Number: 20151208
****************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <cctype>
#include <sstream>
#include <string>

using namespace std;

/************************ Make "Client" class to store customer information. ************************/
class Client
{

public:
    string name;
    string birth_date;
    string passwd;
    string account;
    string balance;

public:
    void ReadInfo(string _a1, string _a2, string _a3, string _a4, string _a5)
    {
        
        name = _a1;
        birth_date = _a2;
        passwd = _a3;
        account = _a4;
        balance = _a5;

    }

    void DepositBalance(string _input)
    {
        unsigned int _bal = stoi(balance);
        unsigned int _mon = stoi(_input);
        _bal += _mon;
        balance = to_string(_bal);
    }

    int WithdrawBalance(string _input) //normal: return 0 ,abnormal: return -1
    {
        unsigned int _bal = stoi(balance);
        unsigned int _mon = stoi(_input);

        if (_bal < _mon) //(abnormal: return -1)
        {
            return -1;
        }
        else
        {
            _bal = _bal - _mon;
            balance = to_string(_bal);

            return 0;
        }

    }



};

// This function is useful when reading files based on blanks.
void Split(string result[5], string str)
{
    string word = "";
    int count = 0;
    for (auto x : str)
    {
        if (x == ' ')
        {
            result[count] = word;
            word = "";
            count++;
        }
        else
        {
            word = word + x;
        }
    }
}

#define ARR_SIZE 20
int save_size = 0;

// Main file
int main()
{
    unsigned int _selnum = 0; 
    string _InputNum; 
    unsigned int _num = 0; 
    unsigned int _num2 = 0; 
    //Client* _selcli = new Client;
    save_size = 0;
    Client clients[ARR_SIZE];


    // Case1: Input variables.
    string nameIP;
    string birthIP;
    string passwdIP;
    string randaccount;
    string balanceIP;

    // Case2: Input variables.
    string nameIP2;
    string deposit_withdraw;

    // Case 3: Check the details of existing account.
    string nameIP3;

    // Used when writing a file.
    stringstream ss;
    string end_check;

    // random seed.
    srand(time(NULL));


    // Read file.
    ifstream myfile("bank_account.txt"); 
    string buffer;


    getline(myfile, buffer);

    while (myfile.peek() != EOF)
    {
        string ss[5];
        // Remove the first line.
        getline(myfile, buffer);
        // Split columns based on space.
        Split(ss, buffer);
        //Save file info in 'Clients' class.
        clients[save_size].ReadInfo(ss[0], ss[1], ss[2], ss[3], ss[4]);
        save_size++;
    }

    // First screen output
    cout << "1. Create new account." << endl;
    cout << "2. For transactions." << endl;
    cout << "3. Check the details of existing account." << endl;
    cout << "4. View customer's list." << endl;
    cout << "5. Exit." << endl;
    /************ Consider the exceptional case and write the part that receives the input. ************/

    while (1)
    {
        bool _flag = false;
        cout << "Choose the option (1~5): ";
        cin >> _InputNum;

        for (int i = 0; i < _InputNum.size(); ++i)
        {
            if (_InputNum[i] >= 58 || _InputNum[i] <= 47) 
            {
                _flag = true;
                break; 
            }
        }

        if (!_flag) 
        {
            _num = stoi(_InputNum); 
            if (1 <= _num && _num <= 5) break; 
        }

    }

    char ch[1];
    int opCheck;
    opCheck = _num; 

    ofstream bankfile("bank_account.txt"); 
    string line1;


    switch (opCheck)
    {
    case 1:
    {
        cout << "Name: ";
        cin >> nameIP;
        cout << "Birth date (yymmdd): ";
        cin >> birthIP;
        cout << "Passwd (4 digits): ";
        cin >> passwdIP;
        cout << "The amount you want to deposit first (-2,147,483,648 ~ 2,147,483,647): ";
        cin >> balanceIP;
        /****************************** OPTION 1: Create new account ******************************/

        // rand account
        unsigned int _randaccount = rand() % 1000000 + 100000; 
        bool _wflag = false; 
        while (1)
        {
            for (int i = 0; i < save_size; i++) 
            {
                int _acc = stoi(clients[i].account);
                if (_randaccount == _acc) _wflag = true; 
            }

            if (!_wflag) break; 
            else { 
                _randaccount = rand() % 1000000 + 100000;
                _wflag = false; 
            }

        }
        randaccount = to_string(_randaccount);

        // balance
        int cnt = 0;
        for (int i = 0; i < balanceIP.size(); i++)
        {
            if (balanceIP[i] != 48) break;
            else if (balanceIP[i] == 48) cnt++;
        }
        balanceIP.erase(0, cnt);

        clients[save_size].ReadInfo(nameIP, birthIP, passwdIP, randaccount, balanceIP);
        save_size++;

        break;
    }

    case 2:
    {
        cout << "What your name? ";
        cin >> nameIP2;
        // cout << "1. Deposit   2. Withdraw: ";
        // cin >> deposit_withdraw;
         /******************************* OPTION 2: For transactions *******************************/

        bool _flag3 = false;

        while (1)
        {
            bool _flag = false;
            bool _flag2 = false;

            cout << "1. Deposit   2. Withdraw: ";
            cin >> deposit_withdraw;

            for (int i = 0; i < deposit_withdraw.size(); ++i) 
            {
                if (deposit_withdraw[i] >= 58 || deposit_withdraw[i] <= 47) 
                {
                    _flag = true;
                    break; 
                }
            }

            if (!_flag) 
            {
                _num2 = stoi(deposit_withdraw); 
                if (_num2 == 1 || _num2 == 2)
                {
                    
                    for (int i = 0; i < save_size; ++i)
                    {
                        if (clients[i].name == nameIP2)
                        {
                            _flag2 = true;
                            _selnum = i;
                            break;
                        }

                    }

                    if (_flag2 == true) break; 
                    else if (_flag2 == false)
                    {
                        cout << "Our bank does not have your account..." << endl;
                        _flag3 = true;
                        break;
                    }
                }
            }
        }

        if (_num2 == 1 && !_flag3) //Deposit
        {
            string InputMoney;
            cout << "Your name is " << clients[_selnum].name << endl;
            cout << "Your balance is " << clients[_selnum].balance << endl;
            cout << "How much would you like to deposit?: ";
            cin >> InputMoney;

            clients[_selnum].DepositBalance(InputMoney);

            cout << "Your balance after transaction is " << clients[_selnum].balance << endl;
        }
        else if (_num2 == 2 && !_flag3) //Withdraw
        {
            string InputMoney;

            cout << "Your name is " << clients[_selnum].name << endl;

            while (1)
            {
                cout << "Your balance is " << clients[_selnum].balance << endl;
                cout << "How much would you like to withdraw?: ";
                cin >> InputMoney;

                int ret = clients[_selnum].WithdrawBalance(InputMoney);

                if (ret == 0)
                {
                    cout << "Your balance after transaction is " << clients[_selnum].balance << endl;
                    break;
                }
                else if (ret == -1)
                {
                    cout << "Insufficient Balance..." << endl;
                }
            }

        }


        break;
    }
    case 3:
        cout << "What your name? ";
        cin >> nameIP3;
        /******************************* OPTION 3: Check the details of existing account. *******************************/

        //while (1)
        {
            bool _flag = false;
            for (int i = 0; i < save_size; i++)
            {
                if (clients[i].name == nameIP3)
                {
                    _flag = true;
                    _selnum = i;
                    break;
                }
            }

            if (_flag == true) 
            {
                string InputPasswd;
                int _passwdcount = 0;
                cout << "Your name is " << clients[_selnum].name << endl;

                for (;;)
                {
                    if (_passwdcount >= 5) 
                    {
                        cout << "You have entered wrong password 5 times, shut down the system.... " << endl;
                        break;
                    }

                    cout << "Enter your password (4 digits): ";
                    cin >> InputPasswd;

                    if (clients[_selnum].passwd == InputPasswd)
                    {
                        cout << "Your account number is " << clients[_selnum].account << endl;
                        cout << "Your balance is " << clients[_selnum].balance << endl;
                        break;
                    }
                    else
                    {
                        _passwdcount++;
                    }

                }

            }
            else
            {
                cout << "Our bank does not have your account..." << endl;
              
            }
        }

        break;
    case 4:
        /************************************** OPTION 4: View customer's list. **************************************/

        for (int i = 0; i < save_size; i++)
        {
            cout << clients[i].name << endl;
        }


        break;
    case 5:
        break;
    }



    if (bankfile.is_open())
    {
        bankfile << "NAME" << " " << "BIRTH_DATE" << " " << "PASSWD" << " " << "ACCOUNT" << " " << "BALANCE" << " " << "\n";
        for (int write = 0; write < save_size; write++)
        {
            bankfile << clients[write].name << " " << clients[write].birth_date << " " << clients[write].passwd << " " << clients[write].account << " " << clients[write].balance << " " << "\n";
            end_check = clients[write].name;
            if (end_check.length() == 0)
            {
                break;
            }
        }
    }

    myfile.close();
    bankfile.close();

    return 0;
}