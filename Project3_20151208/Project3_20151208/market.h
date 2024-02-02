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

using namespace std;

/************************ Make "Market" class to store items information. ************************/
class Market
{
public:
    string m_item;
    string m_amount;
    string m_price;

public:
    void ReadItemInfo(string _a1, string _a2, string _a3)
    {
        m_item = _a1;
        m_amount = _a2;
        m_price = _a3;
    }

    /********************************* Quantity check function **************************************/
    string* QuantityCheck()
    {
        bool IsEnough = false;
        string itemquantity;

        while (!IsEnough)
        {
            cout << "How much do you want to buy? ";
            cin >> itemquantity;

            int input_amount = stoi(itemquantity); 
            int original_amount = stoi(m_amount); 


            if (original_amount < input_amount)
            {
                cout << "Insufficient Quantity..." << endl;
                cout << "We have " << m_amount << "." << endl;
            }
            else
            {
                IsEnough = true;
            }
        }

        string* ps = new string();
        *ps = itemquantity;
        
        return ps;
    }

};

