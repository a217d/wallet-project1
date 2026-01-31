#include <iostream>
#include <cstring>
#include <Windows.h>
using namespace std;

// سجلات المحفظة والعملاء والإيداع والتحويل
struct open_wallet {
    char wallet_no[20];
    char wallet_name[20];
    char password[20];
    open_wallet* link;
} *wh = NULL, *wt = NULL, *wp;

struct customer_acc {
    char wallet_no[20];
    char cust_no[20];
    char cust_name[20];
    char ident_no[20];
    char password[20];
    float balance = 0;
    customer_acc* link;
} *ch = NULL, *ct = NULL, *cp;

struct deposit {
    int deposit_no;
    char wallet_no[20];
    char cust_no[20];
    float amount;
    deposit* link;
} *dh = NULL, *dt = NULL, *dn;

struct transfer {
    int trans_no;
    char cust_in[20];
    char wallet_out[20];
    char wallet_in[20];
    char cust_out[20];
    float amount;
    transfer* link;
} *th = NULL, *tt = NULL, *tn;

// عرض القوائم
void show_menu() {
    cout << "\n*****MAIN MENU*****\n";
    cout << "1- ADD NEW WALLET\n";
    cout << "2- WALLET MANAGER\n";
    cout << "3- CUSTOMER SERVICES\n";
    cout << "4- SHOW WALLETS\n";
    cout << "5- EXIT\n";
}

void show_manager_menu() {
    cout << "\n***MANAGER MENU***\n";
    cout << "1- OPEN CUSTOMER ACCOUNT\n";
    cout << "2- DEPOSIT FOR CUSTOMER\n";
    cout << "3- EXIT\n";
}

void show_customer_menu() {
    cout << "\n***CUSTOMER SERVICE MENU***\n";
    cout << "1- TRANSFER MONEY\n";
    cout << "2- CHANGE PASSWORD\n";
    cout << "3- EXIT\n";
}

// البحث عن محفظة بالاسم
open_wallet* find_wallet_by_name(const char wallet_name[]) {
    open_wallet* temp = wh;
    while (temp) {
        if (strcmp(temp->wallet_name, wallet_name) == 0)
            return temp;
        temp = temp->link;
    }
    return NULL;
}

// إضافة محفظة جديدة
void add_wallet() {
    char name[20];
    cout << "Enter wallet name: ";
    cin >> name;

    if (find_wallet_by_name(name)) {
        cout << "This wallet name already exists.\n";
        return;
    }

    open_wallet* n = new open_wallet;
    static int wallet_id = 3130;
    sprintf(n->wallet_no, "%d", ++wallet_id);
    strcpy(n->wallet_name, name);

    cout << "Enter wallet password: ";
    cin >> n->password;
    n->link = NULL;

    if (!wh) wh = wt = n;
    else { wt->link = n; wt = n; }

    cout << "Wallet created successfully!\n";
    cout << "Wallet No: " << n->wallet_no << "  Name: " << n->wallet_name << endl;
}

// مدير المحفظة
void wallet_manager() {
    char wallet_no[20], password[20];
    int choice;

    cout << "Enter wallet number: ";
    cin >> wallet_no;
    cout << "Enter wallet password: ";
    cin >> password;

    wp = wh;
    while (wp) {
        if (strcmp(wp->wallet_no, wallet_no) == 0 && strcmp(wp->password, password) == 0) {
            do {
                show_manager_menu();
                cout << "Enter choice: ";
                cin >> choice;

                switch (choice) {
                case 1: { // فتح حساب عميل
                    customer_acc* n = new customer_acc;
                    strcpy(n->wallet_no, wp->wallet_no);

                    static int cust_id = 313;
                    sprintf(n->cust_no, "%d", ++cust_id);

                    cout << "Customer name: "; cin >> n->cust_name;
                    cout << "ID number: "; cin >> n->ident_no;
                    cout << "Set password: "; cin >> n->password;

                    do {
                        cout << "Opening balance (>2000): ";
                        cin >> n->balance;
                    } while (n->balance < 2000);

                    n->link = NULL;
                    if (!ch) ch = ct = n;
                    else { ct->link = n; ct = n; }

                    cout << "Customer account created!\nID: " << n->cust_no << " Balance: " << n->balance << endl;
                    break;
                }
                case 2: { // إيداع
                    char cust_no[20]; float amount;
                    cout << "Enter customer account number: ";
                    cin >> cust_no;

                    cp = ch;
                    while (cp) {
                        if (strcmp(cp->wallet_no, wp->wallet_no) == 0 && strcmp(cp->cust_no, cust_no) == 0) break;
                        cp = cp->link;
                    }
                    if (!cp) { cout << "Customer not found.\n"; break; }

                    do {
                        cout << "Enter deposit amount: "; cin >> amount;
                        if (amount <= 0) cout << "Amount must be positive.\n";
                    } while (amount <= 0);

                    dn = new deposit;
                    static int dep_id = 70;
                    dn->deposit_no = ++dep_id;
                    strcpy(dn->wallet_no, cp->wallet_no);
                    strcpy(dn->cust_no, cp->cust_no);
                    dn->amount = amount;
                    dn->link = NULL;

                    if (!dh) dh = dt = dn;
                    else { dt->link = dn; dt = dn; }

                    cp->balance += amount;
                    cout << "Deposit successful. New balance: " << cp->balance << endl;
                    break;
                }
                case 3: cout << "Exiting manager menu...\n"; break;
                default: cout << "Invalid choice.\n";
                }
            } while (choice != 3);
            return;
        }
        wp = wp->link;
    }
    cout << "Wallet not found or wrong password.\n";
}

// تسجيل دخول العميل
bool customer_login(const char wallet_no[], const char cust_no[], const char password[],
                    open_wallet*& wallet, customer_acc*& customer) {
    wp = wh;
    while (wp) {
        if (strcmp(wp->wallet_no, wallet_no) == 0) {
            cp = ch;
            while (cp) {
                if (strcmp(cp->wallet_no, wp->wallet_no) == 0 &&
                    strcmp(cp->cust_no, cust_no) == 0 &&
                    strcmp(cp->password, password) == 0) {
                    wallet = wp; customer = cp; return true;
                }
                cp = cp->link;
            }
        }
        wp = wp->link;
    }
    return false;
}

// تغيير كلمة المرور
void change_password(customer_acc* customer) {
    char old_pass[20], new_pass[20];
    cout << "Enter old password: "; cin >> old_pass;
    if (strcmp(customer->password, old_pass) != 0) {
        cout << "Incorrect old password.\n"; return;
    }
    cout << "Enter new password: "; cin >> new_pass;
    strcpy(customer->password, new_pass);
    cout << "Password changed successfully.\n";
}

// خدمات العميل
void Customer_service() {
    char wallet_no[20], cust_no[20], password[20];
    int choice;
    open_wallet* current_wallet = NULL;
    customer_acc* current_customer = NULL;

    cout << "Enter your wallet number: "; cin >> wallet_no;
    cout << "Enter your customer account number: "; cin >> cust_no;
    cout << "Enter password: "; cin >> password;

    if (!customer_login(wallet_no, cust_no, password, current_wallet, current_customer)) {
        cout << "Wallet or customer not found.\n"; return;
    }

    do {
        show_customer_menu();
        cout << "Enter choice: "; cin >> choice;

        switch (choice) {
        case 1: { // تحويل
            char target_wallet[20], target_cust[20]; float amount;
            cout << "Enter target wallet number: "; cin >> target_wallet;
            cout << "Enter target customer number: "; cin >> target_cust;
            cout << "Enter amount: "; cin >> amount;

            if (amount <= 0 || amount > current_customer->balance) {
                cout << "Invalid amount.\n"; break;
            }

            // البحث عن العميل المستلم
            open_wallet* target_wp = wh; customer_acc* target_cp = ch;
            while (target_wp && strcmp(target_wp->wallet_no, target_wallet) != 0) target_wp = target_wp->link;
            while (target_cp && !(strcmp(target_cp->wallet_no, target_wallet) == 0 && strcmp(target_cp->cust_no, target_cust) == 0))
                target_cp = target_cp->link;

            if (!target_wp || !target_cp) { cout << "Recipient not found.\n"; break; }

            current_customer->balance -= amount;
            target_cp->balance += amount;

            // سجل التحويل
            tn = new transfer;
            static int trans_id = 100;
            tn->trans_no = ++trans_id;
            strcpy(tn->cust_out, current_customer->cust_no);
            strcpy(tn->cust_in, target_cp->cust_no);
            strcpy(tn->wallet_out, current_wallet->wallet_no);
            strcpy(tn->wallet_in, target_wp->wallet_no);
            tn->amount = amount;
            tn->link = NULL;
            if (!th) th = tt = tn; else { tt->link = tn; tt = tn; }

            cout << "Transfer successful. New balance: " << current_customer->balance << endl;
            break;
        }
        case 2: change_password(current_customer); break;
        case 3: cout << "Exiting customer service...\n"; break;
        default: cout << "Invalid choice.\n";
        }

    } while (choice != 3);
}

// عرض المحافظ
void show_wallets() {
    wp = wh; int x = 0;
    if (!wp) { cout << "No wallets.\n"; return; }
    while (wp) {
        cout << "\nWallet No: " << wp->wallet_no << "  Name: " << wp->wallet_name << endl;
        wp = wp->link; x++;
    }
}

int main() {
    int choice;
    do {
        show_menu();
        cout << "Enter your choice: "; cin >> choice;
        switch (choice) {
        case 1: add_wallet(); break;
        case 2: wallet_manager(); break;
        case 3: Customer_service(); break;
        case 4: show_wallets(); break;
        }
    } while (choice != 5);

    cout << "Exiting program. Goodbye!\n";
    return 0;
}
