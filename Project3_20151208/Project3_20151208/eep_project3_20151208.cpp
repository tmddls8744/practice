/******************************************* Market ************************************************
 * EEP Project 3
 * Name: ¹Ú½ÂÀÎ
 * Student Number: 20151208
****************************************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <cctype>
#include <sstream>
#include <string>

// Functions' header files.
#include "market.h"

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

Client clients[ARR_SIZE]; 
Market Items[ARR_SIZE]; 
int clients_size = 0; 
int items_size = 0; 
int select_itemnum = 0; 

void Payment(string* _num);



int main()
{
    // random seed
    srand(time(NULL));

    // Read file.
    int i = 0;
    ifstream myfile("bank_account.txt");
    string buffer;

    if (myfile.is_open())
    {
        getline(myfile, buffer);
        while (myfile.peek() != EOF)
        {
            //cout << i << "th line read" << endl;
            string ss[5];
            // Remove column line.
            getline(myfile, buffer);
            // Split columns based on space.
            Split(ss, buffer);
            // Save file info in 'Clients' class.
            clients[i].ReadInfo(ss[0], ss[1], ss[2], ss[3], ss[4]);
            //clients[i].ReadInfo(ss[0], stoi(ss[1]), stoi(ss[2]), stoi(ss[3]), stoi(ss[4]));
            i++;
        }
    }
    myfile.close();

    
    clients_size = i;
    buffer.clear(); 


    ifstream marketfile("items.txt");
    
    cout << "Welcome to the market!" << endl;
    i = 0;
    getline(marketfile, buffer);
    while (marketfile.peek() != EOF)
    {
        /************* Read the items.txt file, save it in the class, and display all of items, items' information **************/

                      
        string items[5];
        getline(marketfile, buffer);
        Split(items, buffer);
        Items[i].ReadItemInfo(items[0], items[1], items[2]);
        cout << items[0] << " " << items[1] << " " << items[2] << endl;
        i++;
    }
    marketfile.close();
    cout << endl;


    
    items_size = i;
    bool IsExistItem = false; 
    string itemname;

    cout << "What do you want to buy? ";
    cin >> itemname;

    for (int i = 0; i < items_size; i++)
    {
        if (itemname == Items[i].m_item) 
        {
            cout << "We have " << Items[i].m_amount << " " << Items[i].m_item;

            //if amount is more than 2,
            if (stoi(Items[i].m_amount) > 1) {
                cout << "s." << endl;
            }
            //if amount = 1,
            else {
                cout << "." << endl;
            }

            cout << "This is " << Items[i].m_price << " KRW each" << endl << endl;

            select_itemnum = i; 
            IsExistItem = true;

            break;
        }
    }

    if (false == IsExistItem) 
    {
        cout << "Our market does not have this item....";
        return 0;
    }
    
    ofstream bankfile("bank_account.txt");

    string* retun_num = Items[select_itemnum].QuantityCheck(); 
    


    /****************************************** Payment ******************************************/

    Payment(retun_num);

    string end_check;

    // Rewrite the bank_account.txt file.
    if (bankfile.is_open())
    {
        bankfile << "NAME" << " " << "BIRTH_DATE" << " " << "PASSWD" << " " << "ACCOUNT" << " " << "BALANCE" << " " << "\n";
        for (int write = 0; write < clients_size; write++)
        {
            bankfile << clients[write].name << " " << clients[write].birth_date << " " << clients[write].passwd << " " << clients[write].account << " " << clients[write].balance << " " << "\n";
            end_check = clients[write].name;
            if (end_check.length() == 0)
            {
                break;
            }
            /*
            dummyname1 = *(first_c + (write * bank_size));
            if (dummyname1.length() == 0)
            {
                break;
            }
            bankfile << *(first_c + (write * bank_size)) << " " << *(first_c + (write * bank_size) + 1) << " " << *(first_c + (write * bank_size) + 2) << " " << *(first_c + (write * bank_size) + 3) << " " << *(first_c + (write * bank_size) + 4) << " " << "\n";
            */
        }
    }

    // Rewrite the items.txt file.
    ofstream salefile("items.txt");
    if (salefile.is_open())
    {
        salefile << "ITEM" << " " << "AMOUNT" << " " << "PRICE" << "\n";
        for (int write = 0; write < items_size; write++)
        {
            salefile << Items[write].m_item << " " << Items[write].m_amount << " " << Items[write].m_price << " " << "\n";
            end_check = Items[write].m_item;
            if (end_check.length() == 0)
            {
                break;
            }

            /*
            dummyname2 = *(first_i + (write * market_size));
            if (dummyname2.length() == 0)
            {
                break;
            }
            salefile << *(first_i + (write * market_size)) << " " << *(first_i + (write * market_size) + 1) << " " << *(first_i + (write * market_size) + 2) << " " << "\n";
            */
        }
    }
    bankfile.close();
    salefile.close();

    
    delete(retun_num);


    return 0;
}

/**************************************** Payment function ********************************************/
void Payment(string* _num)
{
    bool IsExistClient = false; 
    int inputnum = stoi(*_num); 
    string inputname;

    cout << "You can buy them!" << endl << endl;
    cout << "What your name? ";
    cin >> inputname;



    for (int i = 0; i < clients_size; i++) 
    {
        if (clients[i].name == inputname) 
        {
            IsExistClient = true;
            int itemprice = stoi(Items[select_itemnum].m_price);
            int balance = stoi(clients[i].balance);
            int totalprice = itemprice * inputnum;
            int itemamount = stoi(Items[select_itemnum].m_amount); 

            cout << endl;


            if (balance >= totalprice)
            {
                cout << "The total amount is " << totalprice << " KRW." << endl;
                cout << "Your balance is " << balance << " KRW." << endl;
                cout << endl;
                cout << "I will pay " << totalprice << " KRW." << endl;
                cout << endl;
                cout << "Your account balance is " << balance - totalprice << "." << endl;
                cout << "The number of reamining " << Items[select_itemnum].m_item << " is " << itemamount - inputnum << "." << endl;


                clients[i].balance = to_string(balance - totalprice); 
                Items[select_itemnum].m_amount = to_string(itemamount - inputnum); 
            }
            else //If you run out of money.
            {
                cout << "The total amount is " << totalprice << " KRW." << endl;
                cout << "Your balance is " << balance << " KRW." << endl;
                cout << endl;
                cout << "Insufficient balance..." << endl;
                return;
            }

        }
    }

    //If there is no account information in the bank.txt file.
    if (false == IsExistClient)  
    {
        cout << "Your credit is uncertain...." << endl;
        return;
    }


}