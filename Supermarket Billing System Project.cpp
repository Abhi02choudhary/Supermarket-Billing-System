#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class shoping {
    private:
        int pcode;
        float price;
        float dis;
        string pname;
        
    public:
        void menu();
        void administrator();
        void buyer();
        void add();
        void edit();
        void res();  
        void list(); 
        void receipt();
};

void shoping::menu() {
    int choice;
    string email;
    string password;

    while(true) {
        cout << "\t\t\t\t__________________________________________________\n";
        cout << "\t\t\t\t                                                  \n";
        cout << "\t\t\t\t          Supermarket Main Menu                   \n";
        cout << "\t\t\t\t                                                  \n";
        cout << "\t\t\t\t__________________________________________________\n";
        cout << "\t\t\t\t                                                  \n";
        cout << "\t\t\t\t|  1) Administrator   |\n";
        cout << "\t\t\t\t|                     |\n";
        cout << "\t\t\t\t|  2) Buyer           |\n";
        cout << "\t\t\t\t|                     |\n";
        cout << "\t\t\t\t|  3) Exit            |\n";
        cout << "\t\t\t\t|                     |\n";
        cout << "\t\t\t\t Please select! ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\t\t\t Please Login \n";
                cout << "\t\t\t Enter Email: ";
                cin >> email;
                cout << "\t\t\t Password: ";
                cin >> password;

                if (email == "abhi@gmail.com" && password == "abhi@2005") {
                    administrator();
                } else {
                    cout << "Invalid email/password\n";
                }
                break;
            
            case 2:
                buyer();
                break;
            
            case 3:
                exit(0);

            default:
                cout << "Please select from the given options.\n";
                break;
        }
    }
}

void shoping::administrator() {
    int choice;
    while(true) {
        cout << "\n\n\n\t\t\t Administrator menu";
        cout << "\n\t\t\t|______1) Add the product _____|";
        cout << "\n\t\t\t|______2) Modify the product __|";
        cout << "\n\t\t\t|______3) Delete the product___|";
        cout << "\n\t\t\t|______4) Back to main menu____|\n";
        cout << "\n\n\t Please enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add();
                break;

            case 2:
                edit();
                break;

            case 3:
                res();  // Corrected from rem
                break;

            case 4:
                return;  // Return to menu

            default:
                cout << "Invalid choice!\n";
                break;
        }
    }
}

void shoping::buyer() {
    int choice;
    cout << "\t\t\t  1) Buy product\n";
    cout << "\t\t\t  2) Go back\n";
    cout << "\t\t\t Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:
            receipt();
            break;

        case 2:
            return;

        default:
            cout << "Invalid choice\n";
            break;
    }
}

void shoping::add() {
    fstream data;
    int c;
    int token = 0;
    float p;
    float d;
    string n;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Product code of the product: ";
    cin >> pcode;
    cout << "\n\n\t Name of the product: ";
    cin >> pname;
    cout << "\n\n\t Price of the product: ";
    cin >> price;
    cout << "\n\n\t Discount on the product: ";
    cin >> dis;

    data.open("database.txt", ios::in);

    if (!data) {
        data.open("database.txt", ios::app | ios::out);
        data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
        data.close();
    } else {
        data >> c >> n >> p >> d;

        while (!data.eof()) {
            if (c == pcode) {
                token++;
            }
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1) {
            cout << "\n\n\t Product already exists.\n";
        } else {
            data.open("database.txt", ios::app | ios::out);
            data << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            data.close();
            cout << "\n\n\t Record inserted!\n";
        }
    }
}

void shoping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p;
    float d;
    string n;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n File doesn't exist!\n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);

        data >> pcode >> pname >> price >> dis;
        while (!data.eof()) {
            if (pkey == pcode) {
                cout << "\n\t\t Product new code: ";
                cin >> c;
                cout << "\n\t\t Name of the product: ";
                cin >> n;
                cout << "\n\t\t Price: ";
                cin >> p;
                cout << "\n\t\t Discount: ";
                cin >> d;
                data1 << " " << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Record edited\n";
                token++;
            } else {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();

        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n Record not found, sorry!\n";
        }
    }
}

void shoping::res() {  // Corrected from rem
    fstream data, data1;
    int pkey;
    int token = 0;
    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product code: ";
    cin >> pkey;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File doesn't exist\n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof()) {
            if (pcode == pkey) {
                cout << "\n\n\t Product deleted successfully\n";
                token++;
            } else {
                data1 << " " << pcode << " " << pname << " " << price << " " << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
        data1.close();
        remove("database.txt");
        rename("database1.txt", "database.txt");

        if (token == 0) {
            cout << "\n\n Record not found\n";
        }
    }
}

void shoping::list() {  // Corrected from lsit
    fstream data;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database\n";
        return;
    }
    cout << "\n\n|_________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "|_________________________________\n";
    data >> pcode >> pname >> price >> dis;
    while (!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> dis;
    }
    data.close();
}

void shoping::receipt() {
    fstream data;

    int arrc[100];
    int arrq[100];
    char choice;
    int c = 0;
    float amount = 0;
    float dis = 0;
    float total = 0;

    cout << "\n\n\t\t\t\t RECEIPT ";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database\n";
        return;
    }

    data.close();
    list();
    cout << "\n Please place the order:\n";

    do {
        cout << "\n\nEnter Product code: ";
        cin >> arrc[c];
        cout << "\n\nEnter the product quantity: ";
        cin >> arrq[c];
        for (int i = 0; i < c; i++) {
            if (arrc[c] == arrc[i]) {
                cout << "\n\n Duplicate product code. Please try again!";
                return;
            }
        }
        c++;
        cout << "\n\n Do you want to buy another product? If yes, press y, else no: ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    cout << "\n\n\t\t\t___________________RECEIPT_________________\n";
    cout << "Product No\t Product Name\t Quantity\tPrice\tAmount\tAmount with discount\n";

    for (int i = 0; i < c; i++) {
        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> dis;
        while (!data.eof()) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                dis = amount - (amount * dis / 100);
                total += dis;
                cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t" << dis << "\n";
            }
            data >> pcode >> pname >> price >> dis;
        }
        data.close();
    }
    cout << "\n\n________________________________________";
    cout << "\n Total Amount: " << total << "\n";
}

int main() {
    shoping s;
    s.menu();
    return 0;
}

