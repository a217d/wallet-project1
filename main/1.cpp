#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;

/* ===== السجلات ===== */

struct Customer {
    char cust_no[20];
    char name[20];
    char id_no[20];
    char password[20];
};

struct Wallet {
    char wallet_no[20];
    char wallet_name[20];
    char password[20];
    int type; // 1 = Pocket , 2 = Mobile
    Customer* customer; // عميل واحد فقط
    Wallet* link;
};

struct Deposit {
    int dep_no;
    char wallet_no[20];
    char cust_no[20];
    float amount;
    Deposit* link;
};

struct Transfer {
    int trans_no;
    char from_wallet[20];
    char to_wallet[20];
    float amount;
    Transfer* link;
};

/* ===== رؤوس القوائم ===== */
Wallet* headWallet = NULL;
Deposit* headDeposit = NULL;
Transfer* headTransfer = NULL;

int walletCount = 0;
int depCount = 0;
int transCount = 0;

/* ===== القوائم ===== */

void mainMenu() {
    cout << "\n--- MAIN MENU ---\n";
    cout << "1- Add New Wallet\n";
    cout << "2- Wallet Management\n";
    cout << "3- Exit\n";
}

void managerMenu() {
    cout << "\n1- Open Customer Account\n";
    cout << "2- Deposit Money\n";
    cout << "3- Transfer Money\n";
    cout << "4- Exit\n";
}

/* ===== إنشاء محفظة ===== */

void addWallet() {
    Wallet* w = new Wallet;

    walletCount++;
    sprintf(w->wallet_no, "W%d", walletCount);

    cout << "Wallet Number: " << w->wallet_no << endl;
    cout << "Enter wallet name: ";
    cin >> w->wallet_name;
    cout << "Enter password: ";
    cin >> w->password;

    cout << "Wallet Type (1-Pocket , 2-Mobile): ";
    cin >> w->type;

    w->customer = NULL;
    w->link = headWallet;
    headWallet = w;

    cout << "Wallet created successfully.\n";
    Sleep(1000);
}

/* ===== البحث عن محفظة ===== */

Wallet* findWallet(char no[], char pass[]) {
    Wallet* p = headWallet;
    while (p != NULL) {
        if (strcmp(p->wallet_no, no) == 0 &&
            strcmp(p->password, pass) == 0)
            return p;
        p = p->link;
    }
    return NULL;
}

/* ===== فتح حساب عميل ===== */

void openCustomer(Wallet* w) {
    if (w->customer != NULL) {
        cout << "This wallet already has a customer.\n";
        return;
    }

    w->customer = new Customer;
    strcpy(w->customer->cust_no, "C001");

    cout << "Enter customer name: ";
    cin >> w->customer->name;
    cout << "Enter ID number: ";
    cin >> w->customer->id_no;
    cout << "Set customer password: ";
    cin >> w->customer->password;

    cout << "Customer account opened successfully.\n";
}

/* ===== إيداع ===== */

void depositMoney(Wallet* w) {
    if (w->customer == NULL) {
        cout << "No customer found.\n";
        return;
    }

    Deposit* d = new Deposit;
    depCount++;
    d->dep_no = depCount;
    strcpy(d->wallet_no, w->wallet_no);
    strcpy(d->cust_no, w->customer->cust_no);

    cout << "Enter amount: ";
    cin >> d->amount;

    d->link = headDeposit;
    headDeposit = d;

    cout << "Deposit recorded successfully.\n";
}

/* ===== تحويل ===== */

void transferMoney(Wallet* from) {
    char toWalletNo[20];
    Wallet* to;

    cout << "Enter destination wallet number: ";
    cin >> toWalletNo;

    to = headWallet;
    while (to != NULL && strcmp(to->wallet_no, toWalletNo) != 0)
        to = to->link;

    if (to == NULL) {
        cout << "Wallet not found.\n";
        return;
    }

    // شرط النوع
    if (from->type == to->type) {
        cout << "Transfer allowed only between Pocket and Mobile.\n";
        return;
    }

    Transfer* t = new Transfer;
    transCount++;
    t->trans_no = transCount;

    strcpy(t->from_wallet, from->wallet_no);
    strcpy(t->to_wallet, to->wallet_no);

    cout << "Enter amount: ";
    cin >> t->amount;

    t->link = headTransfer;
    headTransfer = t;

    cout << "Transfer recorded successfully.\n";
}

/* ===== main ===== */

int main() {
    int choice;

    do {
        mainMenu();
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            addWallet();
        }

        else if (choice == 2) {
            char no[20], pass[20];
            cout << "Enter wallet number: ";
            cin >> no;
            cout << "Enter password: ";
            cin >> pass;

            Wallet* w = findWallet(no, pass);
            if (w == NULL) {
                cout << "Invalid wallet.\n";
                continue;
            }

            int ch;
            do {
                managerMenu();
                cout << "Choice: ";
                cin >> ch;

                if (ch == 1) openCustomer(w);
                else if (ch == 2) depositMoney(w);
                else if (ch == 3) transferMoney(w);

            } while (ch != 4);
        }

    } while (choice != 3);

    return 0;
}
