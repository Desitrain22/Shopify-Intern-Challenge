// ShopifyCRUD.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <string.h>
#include <fstream>
#include <map>
#include <ctime>
#include <string>

using namespace std;

class Item {

public:

    Item() {};
    Item(string itemName, long sku, int quantity) : itemName(itemName), sku(sku), quantity(quantity) {}
    
    void changeQuantity(int amount)
    {
        quantity += amount;
        quantity = max(quantity, 0);
        cout << (amount > 0 ? "added " : "removed ") << amount << " " << itemName << ".\n New total is: " << quantity << endl;
    }

    void modifyName(string newName)
    {
        itemName = newName;
        cout << "name changed to.\n" << itemName;
    }

    void changeSku(long newSKU)
    {
        sku = newSKU;
        cout << "SKU changed to " << sku << "\n";
    }

    void editDescription(string newDescription)
    {
        itemDescription = newDescription;
        cout << "Description updated.\n";
    }

    friend ostream& operator<<(ostream& os, const Item& item);
    
private:
    string itemName = "No Item Name Provided";
    long sku = 0;
    string itemDescription = "No Description Provided";
    int quantity = 0;

};

ostream& operator <<(ostream& outputStream, const Item& item)
{
    outputStream << item.itemName << ", " << to_string(item.sku) << ", " << item.itemDescription << ", " << to_string(item.quantity) << "\n";
    return outputStream;
}

void printToCSV(string fileName, map<string, Item*> &inventory)
{
    map<string, Item*>::iterator iterator;   
    
    ofstream newFile;
    newFile.open("Inventory_"+fileName+".csv");

    newFile << "Item name, SKU, Desc., Quantity" << "\n";

    for (iterator = inventory.begin(); iterator != inventory.end(); iterator++)
    {
        newFile << *(iterator->second);
    } 
    newFile.close();
}


int main(void)
{
    map<string, Item*> stuff;
    cout << "Welcome to the Inventory Management System\n";
    cout << "To create a new item, please enter 'create' followed by the item name, SKU, and quantity. Seperate these parameters with spaces as follows:\n";
    cout << "'create socks 123456 6'" << "\n\n";

    cout << "To add or subtract any amount of items, simply type'add' or 'remove',followed by the item name, followed by the amount. For instance:\n";
    cout << "'socks add 5'\t or \t'socks remove 2'" << endl << endl;

    cout << "To edit the sku or description, enter the item name, followed by 'sku' or 'desc.' followed by the updated version. For instance:\n";
    cout << "'socks sku 12234' \t 'socks desc. things to keep your feet warm, or your hands'" << endl << endl;

    cout << "To see a specific item, simply type view followed by the item name. Simply typing 'view all' with no item will show the full list. For instance:\n";
    cout << "'view socks'\twill show you the socks, whereas \t'viewAll'\t will show you the full inventory" << endl << endl;

    cout << "To delete an item, enter 'delete ' followed by the item name, such as 'delete socks'" << endl;
    cout << "The item will be fully removed from the inventory and will need to be re-created" << endl;
    

    cout << "To create a CSV, please enter 'CSV' followed by the version or name to give the CSV. For instance:\n";
    cout << "'CSV version_one'" << "creates a CSV named 'inventory_version_one.csv'" << endl;
    cout << "Do note that CSV names must be a single string with no spaces" << endl << endl;

    cout << "Finally, type exit to exit" << endl << endl;


    string toEdit;
    string command;

    string name;
    long sku;
    string desc;
    int quantity;

    while (true)
    {
        cin.clear();
        cin >> command;
        if (command == "create")
        {
            cin >> name >> sku >> quantity;
            stuff.insert(pair<string, Item*>(name, new Item(name, sku, quantity)));
            cout << "created " << * stuff[name] << endl;
        }

        else if (command == "CSV")
        {
            cin >> name;
            printToCSV(name, stuff);
            cout << "created inventory_" << "name"<< ".CSV" << endl;
        }

        else if (command == "view")
        {
            cin >> name;
            if (name == "all")
            {
                map<string, Item*>::iterator iterator;
                for (iterator = stuff.begin(); iterator != stuff.end(); iterator++)
                {
                    cout << *(iterator->second);
                }
            }
            else
            {
                if (!stuff.count(name))
                {
                    cout << "\n" << name << " Not in inventory!";
                }
                else
                {
                    cout << *stuff[name];
                }
            }
            cout << endl;
        }

        else if (command == "exit")
        {
            cout << "Goodbye! :DDD Please visit my website http://nealpatel.dev to find out more about me. I promise I don't bite!" << endl;
            break;
        }

        else if (command == "delete")
        {
            cin >> name;
            if (!stuff.count(name))
            {
                cout << "\n" << name << " Not in inventory!" << endl;
            }
            else
            {
                delete(stuff[name]);
                stuff.erase(name);
                cout << "Deleted " << name << " from Inventory.\n";
            }
        }

        else
        {
            if (!stuff.count(command))
            {
                cout << "invalid entry! Create the item first" << endl;
                cin.ignore(1000, '\n');
            }

            else
            {
                name = command;
                cin >> toEdit;
                if (toEdit == "add")
                {
                    cin >> quantity;
                    stuff[name]->changeQuantity(quantity);
                }

                else if (toEdit == "remove")
                {
                    cin >> quantity;
                    stuff[name]->changeQuantity(-1 * quantity);
                }

                else if (toEdit == "desc.")
                {
                    getline(cin, desc);
                    stuff[name]->editDescription(desc);
                }

                else if (toEdit == "sku")
                {
                    cin >> sku;
                    stuff[name]->changeSku(sku);
                }

                else
                {
                    cout << "invalid command for " << name;
                    cin.ignore(1000, '\n');
                }
            }
        }
    }
}
