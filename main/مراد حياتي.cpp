#include<iostream>
#include<string.h> // ضرورية لعمل strcmp و strcpy
using namespace std;

int count_wallet = 0;

struct open_wallet {
    int wallet_no;
    char wallet_name[30];
    char password[15];
    open_wallet *link;
} *h = NULL, *t = NULL, *n, *p;

struct customer_account {
    int wallet_no;
    int cust_no;
    char cust_name[30];
    char ident_no[15];
    char password[15];
    customer_account *link;
} *h1 = NULL, *t1 = NULL, *n1, *p1;

struct deposit {
    int deposit_no;
    int wallet_no;
    int cust_no;
    float amount;
    deposit *link;
} *h2 = NULL, *t2 = NULL, *n2, *p2;

struct transform {
    int trans_no;
    int wallet_in;
    int cust_in;
    int wallet_out;
    int cust_out;
    float amount;
    transform *link;
} *h3 = NULL, *t3 = NULL, *n3, *p3;

// القوائم
void main_menu() {
    cout << "\n1_ ADD NEW WALLET" << endl;
    cout << "2_ WALLET MANAGER" << endl;
    cout << "3_ CUSTOMER SERVICES" << endl;
    cout << "4_ SHOW ALL WALLETS" << endl;
    cout << "5_ EXIT" << endl;
}

void manager_menu() {
    cout << "\n1_ OPEN ACCOUNT FOR CUSTOMER" << endl;
    cout << "2_ DEPOSIT AMOUNT" << endl;
    cout << "3_ EXIT" << endl;
}

void customer_menu() {
    cout << "\n1_ CHECK BALANCE" << endl;
    cout << "2_ TRANSFORM MONEY (Not implemented)" << endl;
    cout << "3_ CHANGE PASSWORD" << endl;
    cout << "4_ EXIT" << endl;
}

void add_wallet() {
    char w_name[30];
    cout << "\nENTER WALLET NAME: "; cin >> w_name;
    p = h;
    while (p != NULL) {
        if (strcmp(p->wallet_name, w_name) == 0) {
            cout << "\nTHIS NAME ALREADY EXISTS!" << endl;
            return;
        }
        p = p->link;
    }
    count_wallet++;
    n = new open_wallet;
    n->wallet_no = count_wallet;
    strcpy(n->wallet_name, w_name);
    cout << "ENTER PASSWORD: "; cin >> n->password;
    n->link = NULL;
    if (h == NULL) { h = n; t = n; }
    else { t->link = n; t = n; }
    cout << "Wallet Created Successfully! ID: " << n->wallet_no << endl;
}

// دالة محسنة للتحقق من المدير وإرجاع رقم المحفظة
int check_wallet_manager(char mgr_name[], char ps[]) {
    p = h;
    while (p != NULL) {
        if (strcmp(p->wallet_name, mgr_name) == 0 && strcmp(p->password, ps) == 0)
            return p->wallet_no;
        p = p->link;
    }
    return -1;
}

void add_customer(int w_no) {
    int counter = 1;
    p1 = h1;
    while (p1 != NULL) {
        if (p1->wallet_no == w_no) counter++; // تصحيح = إلى ==
        p1 = p1->link;
    }
    n1 = new customer_account;
    n1->cust_no = counter;
    n1->wallet_no = w_no;
    cout << "ENTER NAME OF CUSTOMER: "; cin >> n1->cust_name;
    cout << "ENTER IDENTITY NO: "; cin >> n1->ident_no;
    cout << "ENTER PASSWORD: "; cin >> n1->password;
    n1->link = NULL;
    if (h1 == NULL) { h1 = n1; t1 = n1; }
    else { t1->link = n1; t1 = n1; }
    cout << "Customer Added! Account No: " << n1->cust_no << endl;
}

bool check_cust_no(int w_no, int cst_no) {
    p1 = h1;
    while (p1 != NULL) {
        if (p1->wallet_no == w_no && p1->cust_no == cst_no) return true;
        p1 = p1->link;
    }
    return false;
}

void add_deposit(int w_no, int cst_no) {
    int counter = 1;
    p2 = h2;
    while (p2 != NULL) {
        if (p2->wallet_no == w_no) counter++;
        p2 = p2->link;
    }
    n2 = new deposit;
    n2->deposit_no = counter;
    n2->wallet_no = w_no;
    n2->cust_no = cst_no;
    cout << "ENTER AMOUNT: "; cin >> n2->amount;
    n2->link = NULL;
    if (h2 == NULL) { h2 = n2; t2 = n2; }
    else { t2->link = n2; t2 = n2; }
}

void report_balance(int w_no, int cst_no) {
    float credit = 0, debit = 0;
    p2 = h2;
    while (p2 != NULL) {
        if (p2->wallet_no == w_no && p2->cust_no == cst_no) credit += p2->amount;
        p2 = p2->link;
    }
    // ملاحظة: هنا يجب إضافة منطق السحب أو التحويل لحساب debit
    cout << "\n-----------------------------" << endl;
    cout << "YOUR BALANCE IS: " << credit - debit << endl;
    cout << "-----------------------------" << endl;
}

int check_customer(char w_name[], int cst_no, char ps[]) {
    // أولاً البحث عن المحفظة
    int w_id = -1;
    p = h;
    while(p != NULL) {
        if(strcmp(p->wallet_name, w_name) == 0) { w_id = p->wallet_no; break; }
        p = p->link;
    }
    if (w_id == -1) return -1;

    // ثانياً البحث عن العميل داخل تلك المحفظة
    p1 = h1;
    while (p1 != NULL) {
        if (p1->wallet_no == w_id && p1->cust_no == cst_no && strcmp(p1->password, ps) == 0)
            return w_id;
        p1 = p1->link;
    }
    return -1;
}

void show_wallets() {
    p = h;
    cout << "\nLIST OF WALLETS:" << endl;
    while (p != NULL) {
        cout << "ID: " << p->wallet_no << " | Name: " << p->wallet_name << endl;
        p = p->link;
    }
}

int main() {
    int c, c2, c3, cst_no;
    char pass[15], w_name[30];
    do {
        main_menu();
        cout << "\nENTER YOUR CHOICE: "; cin >> c;
        switch (c) {
            case 1: add_wallet(); break;
            case 2: 
                cout << "ENTER WALLET NAME: "; cin >> w_name;
                cout << "ENTER PASSWORD: "; cin >> pass;
                int current_w;
                current_w = check_wallet_manager(w_name, pass);
                if (current_w != -1) {
                    do {
                        manager_menu();
                        cout << "ENTER CHOICE: "; cin >> c2;
                        if (c2 == 1) add_customer(current_w);
                        else if (c2 == 2) {
                            cout << "ENTER CUSTOMER NO: "; cin >> cst_no;
                            if (check_cust_no(current_w, cst_no)) add_deposit(current_w, cst_no);
                            else cout << "WRONG CUSTOMER NO!" << endl;
                        }
                    } while (c2 != 3);
                } else cout << "AUTH FAILED!" << endl;
                break;
            case 3:
                cout << "ENTER WALLET NAME: "; cin >> w_name;
                cout << "ENTER ACCOUNT NO: "; cin >> cst_no;
                cout << "ENTER PASSWORD: "; cin >> pass;
                int cust_w_id;
                cust_w_id = check_customer(w_name, cst_no, pass);
                if (cust_w_id != -1) {
                    do {
                        customer_menu();
                        cout << "ENTER CHOICE: "; cin >> c3;
                        if (c3 == 1) report_balance(cust_w_id, cst_no);
                    } while (c3 != 4);
                } else cout << "LOGIN FAILED!" << endl;
                break;
            case 4: show_wallets(); break;
        }
    } while (c != 5);
    return 0;
}