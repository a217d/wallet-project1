#include<iostream>
#include<string.h>
#include <Windows.h>
using namespace std;
 const int r = 4;
 int *number; // مصفوفه لتخزين ارقام الحسابات
 int size = 3; // حجم المصفوفه
 int count = 0; // عداد لعدد المحافظ 
 
// سجل تصريح فتح المحفظه
struct open_wallet{
      char wallet_no[20];// رقم الحساب 
      char wallet_name[20];// اسم المحفظه
      char password[20]; // كلمه مرور المحفظه
      open_wallet *link; // مؤشر للمحفظه التاليه
} *wn, *wh,*wt,*wp;

// سجل فتح حساب للعميل 
struct customer_acc{
    char wallet_no[20];// رقم المحفظه
    char cust_no[20];// رقم العميل
    char cust_name[20];// اسم العميل
    char ldent_no[20];// رقم الهويه
    char password[20];
    float balance = 0; // الرصيد
    customer_acc *link; // مؤشر للحساب التالي 
} *cn, *ch ,*ct ,*cp;

// سجل الايداع
struct deposit{
    int deposit_no;// رقم الايداع
    char wallet_no[20];// رقم حساب المحفظه
    char cust_no[20];// رقم حساب العميل
    float amount; // مبلغ الايداع
    deposit *link; 
} *dn, *dh ,*dt,*dp;

//   سجل التحويل
struct transfer{
    int trans_no;// رقم التحويل
    char cust_in[20];// رقم حساب العميل المحول له
    char wallet_out[20]; // رقم حساب المحفظه المحوله
    char wallet_in[20]; // رقم حساب المحفظه المحول منها
    char cust_out[20];// رقم حساب العميل المحول
    float amount;// مبلغ التحويل
    transfer *link;
}*tn, *th = NULL,*tt = NULL,*tp;

void show_menu(){
	
    cout << "*****main menu*****" << endl;
    cout << "1-ADD NEW WALLET" << endl;
    cout << "2-WALLET MANGERMENT" << endl;
    cout << "3-CUSTOMERS SERVICES" << endl;
    cout << "4- SHOW WALLET" << endl;
    cout << "5-Exit" << endl;
}

     open_wallet* find_wallet_by_name(const char wallet_name[]) {
       open_wallet* temp = wh;
      while (temp != NULL) {
        if (strcmp(temp->wallet_name, wallet_name) == 0)
            return temp;
         temp = temp->link;
      }
      return NULL;
    }
    
void add_wallet() {

    char temp_name[20];
    
    cout << "Enter wallet name: ";
    cin >> temp_name;

    // التحقق من تكرار الاسم
    if (find_wallet_by_name(temp_name) != NULL) {
        cout << "This wallet name already exists.\n";
        return;
    }
    if(count >= size){
    	cout << "Wallet limit reached. Cannot add more wallets.\n";
    	return;
    }
    // إنشاء محفظة جديدة
     wn = new open_wallet;

    // توليد رقم محفظة فريد
    static int wallet_id = 3130;
    sprintf(wn->wallet_no, "%d", wallet_id+= 1);

    strcpy(wn->wallet_name, temp_name);

    cout << "Enter wallet password: ";
    cin >> wn->password;

    wn->link = NULL;

    // ربطها بالقائمة
    if (wh == NULL) {
        wh = wt = wn;
    }
    
     else {
        wt->link = wn;
        wt = wn;
    } 
    
     cout << "pleas waite..." << endl;
     Sleep(1500);
     
    count++;
    cout << "Wallet created successfully " << endl;
    cout << "Wallet Number: " << wn->wallet_no << endl;
    cout << "Wallet Name  : " << wn->wallet_name << endl;
}


 // مدير المحفظه 
 void show_manager_menu(){
 	 cout << endl;
 	 cout << "***manager_menu***" <<  endl;
 	 cout << "1- Opening a customer account" << endl;// فتح حساب عميل
 	 cout << "2- Depositing money for a client" << endl; //ايداع لعميل
     cout << "3-Delete deposits" << endl;
 	 cout << "4- Exit" << endl ;
 }
    
    bool Search_for_customer(const char wallet_no[], const char cust_name[]) {

    cp = ch;
    while (cp != NULL) {
        if (strcmp(cp->wallet_no, wallet_no) == 0 &&
            strcmp(cp->cust_name, cust_name) == 0) {
            return false; // الاسم موجود
        }
        cp = cp->link;
    }
    return true; // الاسم غير موجود
  }

   // مدير المحفظه 
 void wallet_manager() {

    char wallet_no[20];
    char password[20];
    int choice;

    cout << "Enter wallet number: ";
    cin >> wallet_no;

    cout << "Enter wallet password: ";
    cin >> password;

    // البحث عن المحفظة
    wp = wh;
    while (wp != NULL) {

        if (strcmp(wp->wallet_no, wallet_no) == 0 &&
            strcmp(wp->password, password) == 0) {

            do {
                show_manager_menu();
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice) {

                // فتح حساب عميل 
              case 1: {   // فتح حساب عميل جديد

                    cn = new customer_acc;

                    // ربط العميل بالمحفظة
                    strcpy(cn->wallet_no, wp->wallet_no);

                     // توليد رقم عميل فريد
                     static int cust_id = 313;
                    sprintf(cn->cust_no, "%d", ++cust_id);

                    cout << "Customer name: ";
                    cin >> cn->cust_name;

                    if (!Search_for_customer(wp->wallet_no, cn->cust_name)) {
                    cout << "This customer name already exists in this wallet.\n";
                   delete cn;
                  break;
                 }

                    cout << "ID number: ";
                    cin >> cn->ldent_no;

                    // كلمة مرور العميل (مبدئياً نفس المحفظة)
                    cout << "Set customer password: ";
                    cin >> cn->password;

                        // رصيد افتتاحي
                    do {
                        cout << "Opening balance (must be > 2000): ";
                         cin >> cn->balance;

                        } while (cn->balance < 2000);

                        // ربطه بقائمة العملاء
                        cn->link = NULL;

                        if (ch == NULL) {
                            ch = cn;
                            ct = cn;
                        }
                         else {
                            ct->link = cn;
                            ct = cn;
                        }

                        cout << "\nCustomer account created successfully!\n";
                        cout << "Customer ID: " << cn->cust_no << endl;
                        cout << "Wallet number: " << cn->wallet_no << endl;
                        cout << "Balance: " << cn->balance << endl;

                        break;
                    }


                // إيداع 
                case 2: {
                    char cust_no[20];
                    float amount;

                    cout << "Enter customer account number: ";
                    cin >> cust_no;

                    cp = ch;
                    while (cp != NULL) {
                        if (strcmp(cp->wallet_no, wp->wallet_no) == 0 &&
                            strcmp(cp->cust_no, cust_no) == 0) {
                            break;
                        }
                        cp = cp->link;
                    }

                    if (cp == NULL) {
                        cout << "Customer account not found.\n";
                        break;
                    }

                    do {
                        cout << "Enter deposit amount: ";
                        cin >> amount;

                        if(amount <= 0){
                            cout << "Amount must be positive.\n";
                         }
                    } while (amount <= 0);

                    dn = new deposit;
                    static int dep_no = 70;
                    dn->deposit_no = ++dep_no;

                    strcpy(dn->wallet_no, cp->wallet_no);
                    strcpy(dn->cust_no, cp->cust_no); 
                    dn->amount = amount;
                    dn->link = NULL;

                    if (dh == NULL) {
                        dh = dn;
                        dt = dn;
                    } 
                    else {
                        dt->link = dn;
                        dt = dn;
                    }

                    cp->balance += amount;

                    cout << "Deposit successful.\n";
                    cout << "New balance: " << cp->balance << endl;
                    cout << "your dep_no: " << dn->deposit_no << endl;
                    break;
                }

                case 3: {   // حذف إيداع

                int dep_no;
                cout << "Enter deposit number: ";
                cin >> dep_no;

                deposit *prev = NULL;
                dp = dh;

                while (dp != NULL && dp->deposit_no != dep_no) {
                    prev = dp;
                    dp = dp->link;
                }

                if (dp == NULL || strcmp(dp->wallet_no, wp->wallet_no) != 0) {
                    cout << "Deposit not found.\n";
                    break;
                }

                cp = ch;
                while (cp != NULL &&!(strcmp(cp->wallet_no, dp->wallet_no) == 0 &&
                        strcmp(cp->cust_no, dp->cust_no) == 0)) {
                    cp = cp->link;
                }

                if (cp == NULL) {
                    cout << "Cannot delete deposit.\n";
                    break;
                }

                cp->balance -= dp->amount;

                if (prev == NULL) 
                  dh = dp->link;
                else 
                 prev->link = dp->link;

                delete dp;

                cout << "Deposit deleted. New balance: " << cp->balance << endl;
                break;
            }

                case 4:
                    cout << "Exiting wallet manager...\n";
                    break;

                default:
                    cout << "Invalid choice.\n";
                }

            } while (choice != 4);

            return;
        }

        wp = wp->link;
    }

    cout << "Wallet not found or wrong password.\n";
}

   void show_Customer(){
   	 cout << endl;
   	 cout << "**Customer_service_menu**" << endl;
   	 cout << "1- TARNFORM MONEY" << endl;
   	 cout << "2- CHANGE PASSWORD" << endl;
   	 cout << "3- EXIT" << endl;
   }

    // البحث عن حساب العميل ورقم محفظته
  bool customer_login(
    const char wallet_out[],
    const char cust_out[],
    const char password[],
    open_wallet*& wallet,
    customer_acc*& customer
) {
    wp = wh;

    while (wp != NULL) {

        if (strcmp(wp->wallet_name, wallet_out) == 0 ) {

            cp = ch;
            while (cp != NULL) {

                if (strcmp(cp->wallet_no, wp->wallet_no) == 0 &&
                    strcmp(cp->cust_no, cust_out) == 0 && strcmp(cp->password, password) == 0) {

                    wallet = wp;// مؤشر للمحفظه الحاليه
                    customer = cp; // مؤشر لحساب العميل الحالي
                    return true;
                }
                cp = cp->link;
            }
        }
        wp = wp->link;
    }
    return false;
}
  
 bool changing_of_password(customer_acc* customer, open_wallet* wallet) {

    char old_password[20];
    char new_password[20];

    cout << "Enter old password: ";
    cin >> old_password;

    cout << "Enter new password: ";
    cin >> new_password;

    if (strcmp(customer->password, old_password) != 0) {
        cout << "Old password is incorrect.\n";
        return false;
    }

    strcpy(customer->password, new_password);
    
    cout << "Password changed successfully.\n";
    return true;
}

  void Customer() {

    char wallet_out[20];
    char cust_out[20];
    char password[20];
    int chh;

    open_wallet* current_wallet = NULL;
    customer_acc* current_customer = NULL;

    cout << "Enter your wallet name: ";
    cin >> wallet_out;

    cout << "Enter your customer account number: ";
    cin >> cust_out;

    cout << "Enter your account password: ";
    cin >> password;

    if (!customer_login(wallet_out, cust_out, password, current_wallet, current_customer)) {
        cout << "Wallet or customer not found.\n";
        return;
    }

    do {

        show_Customer();
        cout << "Enter your choice: ";
        cin >> chh;

            if(chh >= 1 && chh <= 3){
        switch (chh) {

        // TRANSFER 
        case 1: {

            char target_wallet_name[20];
            char target_cust_no[20];
            float amount;
            bool confirm;

            cout << "Enter target wallet name: ";
            cin >> target_wallet_name;

            cout << "Enter target  number: ";
            cin >> target_cust_no;

            // البحث عن محفظة المستلم
            wp = wh;
            while (wp != NULL && strcmp(wp->wallet_name, target_wallet_name) != 0) {
                wp = wp->link;
            }

            if (wp == NULL) {
                cout << "Receiver customer account not found.\n";
                break;
            }

            // البحث عن حساب المستلم
            cp = ch;
            while (cp != NULL &&
                   !(strcmp(cp->wallet_no, wp->wallet_no) == 0 && strcmp(cp->cust_no, target_cust_no) == 0)) {

                  cp = cp->link;
            }

            if (cp == NULL) {
                cout << "Receiver customer account not found.\n";
                break;
            }

            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0 || amount > current_customer->balance) {
                cout << "Invalid amount.\n";
                break;
            }

            cout << "\nAre you sure you want to transfer " << amount
                 << " to wallet number " << wp->wallet_no << endl
                 << "And the username that was transferred to him is: "
                 << cp->cust_name << endl;

            cout << "1- Yes\n0- No\n";
            cout << "Your choice: ";
            cin >> confirm;

            if (!confirm) {
                cout << "Transfer cancelled successfully.\n";
                break;
            }

            // تنفيذ التحويل
            current_customer->balance -= amount;
            cp->balance += amount;

            // إنشاء سجل التحويل
            tn = new transfer;
            static int trans_id = 100;
            tn->trans_no = ++trans_id;

            strcpy(tn->cust_out, current_customer->cust_no); // ترقم حساب العميل المحول
            strcpy(tn->cust_in, cp->cust_no);// ترقم حساب العميل المحول له
            strcpy(tn->wallet_out, current_wallet->wallet_name); // اسم محفظة المحول
            strcpy(tn->wallet_in, wp->wallet_name);// اسم محفظة المستلم
            tn->amount = amount;

            tn->link = NULL;

            if (th == NULL){
                th = tn;
                tt = tn;
             }

            else {
                tt->link = tn;
                tt = tn;
            }

            Sleep(2500);

            cout << "\nTransfer completed successfully.\n";
            cout << "Transfer wallet name: " << tn->wallet_out << endl;
            cout << "Transferr account number: " << tn->cust_out << endl;
            cout << "The wallet name of the recipient: " << tn->wallet_in << endl;
            cout << "Account number to which the money is transferred: " << tn->cust_in << endl;
            cout << "Transfer number: " << trans_id << endl;
            cout << "Your new balance: " << current_customer->balance << endl;

            break;
        }

        //  Change Password 
        case 2:
            changing_of_password(current_customer, current_wallet);
            break;

        case 3:
            cout << "Exiting customer service...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
     }

    } while (chh != 3);
}
 void show_wallets() {
    wp = wh;
    int x = 0;
    while (wp != NULL) {
    	 cout << "\n*** List of Wallets ***" << endl;
        cout << x + 1 << "-" << "Wallet Name: " << wp->wallet_name << endl;
        cout << x + 1  << "-" << "and Wallet Number: "<< wp->wallet_no << endl;
        wp = wp->link;
        x++;
    }
     if(wp == NULL  && x == 0){
        cout << "No wallets.\n";
     }

    }
 
 int main() {

    //  مصفوفة التحكم بعدد المحافظ 
    number = new int[size];

    // تهيئة مؤشرات المحافظ 
    wh = NULL;
    wt = NULL;

    // تهيئة مؤشرات حسابات العملاء
    ch = NULL;
    ct = NULL;

    // تهيئة مؤشرات الإيداعات 
    dh = NULL;
    dt = NULL;

    //  تهيئة مؤشرات التحويلات 
    th = NULL;
    tt = NULL;

    int choice;

    do {
        show_menu();

        cout << "Enter your choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 4) {
            switch (choice) {

            case 1:   // إضافة محفظة جديدة
                    add_wallet();
                break;

            case 2:   // مدير المحفظة
                wallet_manager();
                break;

            case 3:   // خدمات العملاء
                Customer();
                break;

                 case 4:   // اظهار المحافظ 
                 show_wallets();
                break;
            }
        }

    } while (choice != 5);

    // حذف المحافظ
    open_wallet* wtemp;
    while (wh != NULL) {
        wtemp = wh;
        wh = wh->link;
        delete wtemp;
    }

    // حذف حسابات العملاء
    customer_acc* ctemp;
    while (ch != NULL) {
        ctemp = ch;
        ch = ch->link;
        delete ctemp;
    }

    // حذف الإيداعات
    deposit* dtemp;
    while (dh != NULL) {
        dtemp = dh;
        dh = dh->link;
        delete dtemp;
    }

    // حذف التحويلات
    transfer* ttemp;
    while (th != NULL) {
        ttemp = th;
        th = th->link;
        delete ttemp;
    }

    // حذف مصفوفة عدد المحافظ
    delete[] number;

    cout << "Exiting program. Goodbye!" << endl;

    return 0;
}
