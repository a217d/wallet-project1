#include <iostream>
#include <string.h>
#include <Windows.h>
using namespace std;

// ===================== الهيكلية =====================
struct open_wallet {
    char wallet_no[20];
    char wallet_name[20];
    char password[20];
    open_wallet* link;
};

struct customer_acc {
    char wallet_no[20];
    char cust_no[20];
    char cust_name[20];
    char ldent_no[20];
    char password[20];
    float balance = 0;
    customer_acc* link;
};

struct deposit {
    int deposit_no;
    char wallet_no[20];
    char cust_no[20];
    float amount;
    deposit* link;
};

struct transfer {
    int trans_no;
    char cust_in[20];
    char wallet_out[20];
    char wallet_in[20];
    char cust_out[20];
    float amount;
    transfer* link;
};

struct system_wallet {
    open_wallet* wh;
    open_wallet* wt;
    customer_acc* ch;
    customer_acc* ct;
    deposit* dh;
    deposit* dt;
    transfer* th;
    transfer* tt;

    int wallet_id;
    int cust_id;
    int dep_no;
    int trans_id;
};

// ===================== التهيئة =====================
void init(system_wallet& s) {
    s.wh = s.wt = NULL;
    s.ch = s.ct = NULL;
    s.dh = s.dt = NULL;
    s.th = s.tt = NULL;

    s.wallet_id = 3130;
    s.cust_id = 313;
    s.dep_no = 70;
    s.trans_id = 100;
}

// ===================== القوائم =====================
void show_menu() {
    cout << "\n***** MAIN MENU *****\n";
    cout << "1- ADD NEW WALLET\n";
    cout << "2- WALLET MANAGEMENT\n";
    cout << "3- CUSTOMER SERVICES\n";
    cout << "4- SHOW WALLETS\n";
    cout << "5- EXIT\n";
}

void show_wallet_manager_menu() {
    cout << "\n*** WALLET MANAGEMENT MENU ***\n";
    cout << "1- OPEN CUSTOMER ACCOUNT\n";
    cout << "2- DEPOSIT\n";
    cout << "3- EXIT\n";
}

void show_customer_menu() {
    cout << "\n*** CUSTOMER SERVICE MENU ***\n";
    cout << "1- TRANSFER MONEY\n";
    cout << "2- CHANGE PASSWORD\n";
    cout << "3- EXIT\n";
}

// ===================== العمليات =====================

// البحث عن المحفظة بالاسم
open_wallet* find_wallet_by_name(system_wallet& s, const char wallet_name[]) {
    open_wallet* temp = s.wh;
    while (temp != NULL) {
        if (strcmp(temp->wallet_name, wallet_name) == 0)
            return temp;
        temp = temp->link;
    }
    return NULL;
}

// البحث عن المحفظة برقمها في نظام معين
open_wallet* find_wallet_by_no(system_wallet& s, const char wallet_no[]) {
    open_wallet* temp = s.wh;
    while (temp != NULL) {
        if (strcmp(temp->wallet_no, wallet_no) == 0)
            return temp;
        temp = temp->link;
    }
    return NULL;
}

// إنشاء محفظة جديدة
void add_wallet(system_wallet& s) {
    char temp_name[20];
    cout << "Enter wallet name: ";
    cin >> temp_name;

    if (find_wallet_by_name(s, temp_name) != NULL) {
        cout << "This wallet name already exists.\n";
        return;
    }

    open_wallet* wn = new open_wallet;
    sprintf(wn->wallet_no, "%d", ++s.wallet_id);
    strcpy(wn->wallet_name, temp_name);

    cout << "Enter wallet password: ";
    cin >> wn->password;

    wn->link = NULL;
    if (s.wh == NULL) s.wh = s.wt = wn;
    else {
        s.wt->link = wn;
        s.wt = wn;
    }

    cout << "Wallet created successfully!\n";
    cout << "Wallet Number: " << wn->wallet_no << endl;
    cout << "Wallet Name  : " << wn->wallet_name << endl;
}

// إدارة المحفظة (مدير المحفظة) عبر اسم المحفظة وكلمة المرور
void wallet_manager(system_wallet& jeeb, system_wallet& jawali, system_wallet& kareemi) {
    char wallet_name[20], password[20];
    cout << "Enter wallet name: ";
    cin >> wallet_name;
    cout << "Enter wallet password: ";
    cin >> password;

    system_wallet* systems[3] = { &jeeb, &jawali, &kareemi };
    system_wallet* current = nullptr;
    open_wallet* wp = nullptr;

    for (int i = 0; i < 3; i++) {
        wp = systems[i]->wh;
        while (wp != NULL) {
            if (strcmp(wp->wallet_name, wallet_name) == 0 &&
                strcmp(wp->password, password) == 0) {
                current = systems[i];
                break;
            }
            wp = wp->link;
        }
        if (current != nullptr) break;
    }

    if (current == nullptr) {
        cout << "Wallet not found or wrong password.\n";
        return;
    }

    int choice;
    do {
        show_wallet_manager_menu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            customer_acc* cn = new customer_acc;
            strcpy(cn->wallet_no, wp->wallet_no);
            sprintf(cn->cust_no, "%d", ++current->cust_id);

            cout << "Customer name: ";
            cin >> cn->cust_name;
            cout << "ID number: ";
            cin >> cn->ldent_no;
            cout << "Set customer password: ";
            cin >> cn->password;

            do {
                cout << "Opening balance (>2000): ";
                cin >> cn->balance;
            } while (cn->balance < 2000);

            cn->link = NULL;
            if (current->ch == NULL) current->ch = current->ct = cn;
            else { current->ct->link = cn; current->ct = cn; }

            cout << "Customer account created successfully.\n";
            break;
        }

        case 2: {
            char cust_no[20];
            float amount;
            cout << "Enter customer account number: ";
            cin >> cust_no;

            customer_acc* cp = current->ch;
            while (cp != NULL) {
                if (strcmp(cp->wallet_no, wp->wallet_no) == 0 &&
                    strcmp(cp->cust_no, cust_no) == 0)
                    break;
                cp = cp->link;
            }
            if (cp == NULL) {
                cout << "Customer account not found.\n";
                break;
            }

            cout << "Enter deposit amount: ";
            cin >> amount;
            if (amount <= 0) {
                cout << "Amount must be positive.\n";
                break;
            }

            deposit* dn = new deposit;
            dn->deposit_no = ++current->dep_no;
            strcpy(dn->wallet_no, cp->wallet_no);
            strcpy(dn->cust_no, cp->cust_no);
            dn->amount = amount;
            dn->link = NULL;

            if (current->dh == NULL) current->dh = current->dt = dn;
            else { current->dt->link = dn; current->dt = dn; }

            cp->balance += amount;
            cout << "Deposit successful. New balance: " << cp->balance << endl;
            break;
        }

        case 3:
            cout << "Exiting wallet manager...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

// ===================== خدمة العميل =====================
bool customer_login(system_wallet& jeeb, system_wallet& jawali, system_wallet& kareemi,
                    const char wallet_no[], const char cust_no[], const char password[],
                    open_wallet*& wallet, customer_acc*& customer) {
    system_wallet* systems[3] = { &jeeb, &jawali, &kareemi };
    for (int i = 0; i < 3; i++) {
        open_wallet* wp = systems[i]->wh;
        while (wp != NULL) {
            if (strcmp(wp->wallet_no, wallet_no) == 0) {
                customer_acc* cp = systems[i]->ch;
                while (cp != NULL) {
                    if (strcmp(cp->wallet_no, wallet_no) == 0 &&
                        strcmp(cp->cust_no, cust_no) == 0 &&
                        strcmp(cp->password, password) == 0) {
                        wallet = wp;
                        customer = cp;
                        return true;
                    }
                    cp = cp->link;
                }
            }
            wp = wp->link;
        }
    }
    return false;
}

bool changing_of_password(customer_acc* customer) {
    char old_password[20], new_password[20];
    cout << "Enter old password: "; cin >> old_password;
    cout << "Enter new password: "; cin >> new_password;

    if (strcmp(customer->password, old_password) != 0) {
        cout << "Old password is incorrect.\n";
        return false;
    }

    strcpy(customer->password, new_password);
    cout << "Password changed successfully.\n";
    return true;
}

void customer_service(system_wallet& jeeb, system_wallet& jawali, system_wallet& kareemi) {
    char wallet_no[20], cust_no[20], password[20];
    cout << "Enter wallet number: "; cin >> wallet_no;
    cout << "Enter customer account number: "; cin >> cust_no;
    cout << "Enter account password: "; cin >> password;

    open_wallet* current_wallet = nullptr;
    customer_acc* current_customer = nullptr;

    if (!customer_login(jeeb, jawali, kareemi, wallet_no, cust_no, password, current_wallet, current_customer)) {
        cout << "Wallet or customer not found.\n";
        return;
    }

    int choice;
    do {
        show_customer_menu();
        cout << "Enter your choice: "; cin >> choice;
        switch (choice) {
        case 1: {
            char target_wallet_no[20], target_cust_no[20];
            float amount;
            cout << "Enter target wallet number: "; cin >> target_wallet_no;
            cout << "Enter target customer account number: "; cin >> target_cust_no;

            open_wallet* wp = nullptr;
            customer_acc* cp = nullptr;
            if (!customer_login(jeeb, jawali, kareemi, target_wallet_no, target_cust_no, "", wp, cp)) {
                cout << "Receiver not found.\n"; break;
            }

            cout << "Enter amount: "; cin >> amount;
            if (amount <= 0 || amount > current_customer->balance) {
                cout << "Invalid amount.\n"; break;
            }

            cout << "Confirm transfer? 1-Yes 0-No: "; int confirm; cin >> confirm;
            if (!confirm) { cout << "Transfer cancelled.\n"; break; }

            current_customer->balance -= amount;
            cp->balance += amount;

            // سجل التحويل
            transfer* tn = new transfer;
            tn->trans_no = ++(jeeb.trans_id); // مجرد ترقيم عام
            strcpy(tn->cust_out, current_customer->cust_no);
            strcpy(tn->cust_in, cp->cust_no);
            strcpy(tn->wallet_out, current_wallet->wallet_no);
            strcpy(tn->wallet_in, wp->wallet_no);
            tn->amount = amount;
            tn->link = nullptr;

            if (jeeb.th == nullptr) jeeb.th = jeeb.tt = tn;
            else { jeeb.tt->link = tn; jeeb.tt = tn; }

            cout << "Transfer completed. New balance: " << current_customer->balance << endl;
            break;
        }
        case 2: changing_of_password(current_customer); break;
        case 3: cout << "Exiting customer service...\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

// ===================== عرض المحافظ =====================
void show_wallets(system_wallet& s) {
    open_wallet* wp = s.wh;
    if (!wp) { cout << "No wallets.\n"; return; }
    while (wp) {
        cout << "Wallet Name : " << wp->wallet_name << ", Wallet No: " << wp->wallet_no << endl;
        wp = wp->link;
    }
}

// ===================== تنظيف الذاكرة =====================
void clear_system(system_wallet& s) {
    open_wallet* wtemp;
    while (s.wh) { wtemp = s.wh; s.wh = s.wh->link; delete wtemp; }
    customer_acc* ctemp;
    while (s.ch) { ctemp = s.ch; s.ch = s.ch->link; delete ctemp; }
    deposit* dtemp;
    while (s.dh) { dtemp = s.dh; s.dh = s.dh->link; delete dtemp; }
    transfer* ttemp;
    while (s.th) { ttemp = s.th; s.th = s.th->link; delete ttemp; }
}

// ===================== البرنامج الرئيسي =====================
int main() {
    system_wallet jeeb, jawali, kareemi;
    init(jeeb); init(jawali); init(kareemi);

    int choice;
    do {
        show_menu();
        cout << "Enter your choice: "; cin >> choice;
        switch (choice) {
        case 1: {
            int sys_choice; cout << "Choose system: 1-Jeeb 2-Jawali 3-Kareemi: "; cin >> sys_choice;
            system_wallet* current = nullptr;
            if (sys_choice == 1) current = &jeeb;
            else if (sys_choice == 2) current = &jawali;
            else if (sys_choice == 3) current = &kareemi;
            else { cout << "Invalid choice.\n"; break; }
            add_wallet(*current); break;
        }
        case 2: wallet_manager(jeeb, jawali, kareemi); break;
        case 3: customer_service(jeeb, jawali, kareemi); break;
        case 4:
            cout << "\n--- JEEB ---\n"; show_wallets(jeeb);
            cout << "\n--- JAWALI ---\n"; show_wallets(jawali);
            cout << "\n--- KAREEMI ---\n"; show_wallets(kareemi);
            break;
        case 5: cout << "Exiting program.\n"; break;
        default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    clear_system(jeeb);
    clear_system(jawali);
    clear_system(kareemi);
    return 0;
}
