#include<iostream>
#include<string.h>
#include <Windows.h>
using namespace std;
 const int r = 4;
 int *number; // مصفوفه لتخزين ارقام الحسابات
 int size = 3; // حجم المصفوفه
 int count = 0; // عداد لعدد المحافظ 
 
 struct customer_acc; // تعريف مبدئي
 
// سجل تصريح فتح المحفظه
struct open_wallet{
      char wallet_no[20];// رقم الحساب للمحفظه
      char wallet_name[20];// اسم المحفظه
      char password[20]; // كلمه مرور المحفظه
      customer_acc *customer;//  مؤشر للعملاء 
      open_wallet *link; // مؤشر للمحفظه التاليه
} *n, *h,*t,*p ;

 struct deposit;
 struct transfer;
// سجل فتح حساب للعميل 
struct customer_acc{
    char wallet_no[20];// رقم المحفظه
    char cust_no[20];// رقم العميل
    char cust_name[20];// اسم العميل
    char ldent_no[20];// رقم الهويه
    char password[20];
    deposit *deposits[20]; // قائمة الإيداعات
    int deposit_count = 0;  // عداد الإيداعات
    transfer *transfers[20]; // قائمه التحويلات
    int transfer_count = 0; // عداد التحويلات 
    float balance = 0; // الرصيد
    customer_acc *link; // مؤشر للحساب التالي 
};
// سجل الايداع
struct deposit{
    int deposit_no;// رقم الايداع
    char wallet_no[20];// رقم حساب المحفظه
    char cust_no[20];// رقم حساب العميل
    float amount;// مبلغ الايداع
    deposit *link; 
};
//   سجل التحويل
struct transfer{
    int trans_no;// رقم التحويل
    char cust_in[20];// رقم حساب العميل المحول له
    char wallet_out[20]; // رقم حساب المحفظه المحوله
    char wallet_in[20]; // رقم حساب المحفظه المحول منها
    char cust_out[20];// رقم حساب العميل المحول
    float amount;// مبلغ التحويل
    transfer *link;
};
void show_menu(){
	
    cout << "*****main menu*****" << endl;
    cout << "1-ADD NEW WALLET" << endl;
    cout << "2-WALLET MANGERMENT" << endl;
    cout << "3-CUSTOMERS SERVICES" << endl;
    cout << "4-Exit" << endl;
}
 
 void add_wallet(){
 	    if (count < size){
                n = new open_wallet;

            	 char wallett_id[20] = "3130"; // رقم حساب المحفظه 
            	 int num = atoi(wallett_id); // تحويل النص الى رقم 
            	 num += count ; // مقدار الزياده 
				 sprintf(wallett_id, "%d", num); // تحويل الرقم مرة ثانية إلى نص
            	 
               strcpy(n->wallet_no, wallett_id);
               cout << " wallet no is: " <<  n->wallet_no << endl;
		
				
                cout << "enter wallet name: ";
                  cin >> n->wallet_name;

                cout << "enter password: ";
                 cin >> n->password;
                 
                n->customer = NULL; // يعني ان المحفظه ليس لها حساب عميل بعد
                n->link = NULL;
                
                 // اضافه المحفظه الى القائمه
                if(h == NULL){
                      h = n;
                      t = n;
                }
                else{
                        t->link = n;// ربط المحفظه الجديده في اخر القائمه
                        t = n;
                } 
                cout << "Please wait...." << endl; // انتظار 
                Sleep(2500);
                cout << "The wallet has been added successfully." << endl; // القبول 
                
                count++;
               
            }
            else{
                //  عدم قبول محفظه جديده
                cout << "You have reached the maximum number of wallets." << endl;
             }
        

 }
 
 // مدير المحفظه 
 void show_manager_menu(){
 	 cout << endl;
 	 cout << "***manager_menu***" <<  endl;
 	 cout << "1- Opening a customer account" << endl;// فتح حساب عميل
 	 cout << "2- Depositing money for a client" << endl; //ايداع لعميل
 	 cout << "3- Exit" << endl ;
 }
 
   // مدير المحفظه 
 
 void wallet_manager(){
  	    char wallet_no[20];
        char password[20];
        int choices;

            cout << "Enter wallet_no: ";
            cin >> wallet_no;
            
             cout << "Enter your password: ";
                cin >> password;
                
              // البحث عن المحفظة
             p = h;
            while(p != NULL){
             if(strcmp(wallet_no, p->wallet_no) == 0 &&strcmp(password, p->password) == 0){
                        
                // المحفظة صحيحة → ندخل حلقة المدير
                do {
                     
                   show_manager_menu(); // عرض القائمة
                    cout << "Enter your choice: ";
                    cin >> choices;

                  if(choices > 0 && choices <= 3){
                  switch(choices){
                     case 1: // فتح حساب عميل
                        if(p->customer != NULL){
                            cout << "This wallet already has a customer account." << endl;
                            break;
                        }
                        
                        else{
                            p->customer = new customer_acc;// إنشاء حساب عميل جديد ديناميكيًا
                            strcpy(p->customer->wallet_no, p->wallet_no);

                            cout << "Wallet no is: " << p->wallet_no << endl; 
                            cout << "Enter the customer's name: ";
                            cin >> p->customer->cust_name;

                            cout << "Enter the ID number: ";
                            cin >> p->customer->ldent_no;
                            
                             // تعيين كلمة المرور الخاصة بالعميل
                            strcpy(p->customer->password, password);
                            
                            cout << "the password is: " << p->customer->password << endl;
                            
                               char cust_id[20] = "313"; // رقم حساب العميل 
            	               static int num = atoi(cust_id); // تحويل النص الى رقم 
            	               num += 2; // مقدار الزياده 
				               sprintf(cust_id, "%d", num); // تحويل الرقم مرة ثانية إلى نص
            	 
                               strcpy(p->customer->cust_no, cust_id);
                               
                               float opening_balance;
                               
							 do {
							    cout << "Enter opening balance (must be > 2000): ";
								cin >> opening_balance;
								
								if(opening_balance < 2000){
								cout << "Invalid amount! Please enter a positive value.\n";
							    }
							     
							  } while(opening_balance < 2000);
								
							  p->customer->balance = opening_balance;// تعيين الرصيد الافتتاحي
                            
                              cout << "Please wait...." << endl;
                              Sleep(1500);
                            
                             cout << "Customer account created successfully!" << endl;
                            
                             cout << "Customer ID: " << p->customer->cust_no << endl;
                             cout << "Customer password: " << p->customer->password << endl;
                             cout << "Opening balance: " << p->customer->balance << endl;

                            
                        }
                        break;

                    case 2: // إيداع
                         char wallet_no[20];
                         float deposit_amount;

                         cout << "Enter wallet_no:";
                          cin >> wallet_no;
                          
                           if(p->customer != NULL && strcmp(p->customer->wallet_no, wallet_no) == 0){

							    cout << "Current balance: " << p->customer->balance << endl;

							    
							   do {
								    cout << "Enter deposit amount: ";
								    cin >> deposit_amount;
								
								    if(deposit_amount <= 0) {
								        cout << "The amount is incorrect. Please enter a positive value.\n";
								    }
								
								} while(deposit_amount <= 0); // استمر طالما الرقم <= 0
								
							  // إنشاء سجل الإيداع الجديد ديناميكيًا
							    deposit* d = new deposit;
							    static int deposit_id = 70;   // رقم بداية الإيداع
							    deposit_id += 1;
							    d->deposit_no = deposit_id;
							
							    strcpy(d->wallet_no, p->customer->wallet_no);// نسخ رقم المحفظه
							    strcpy(d->cust_no, p->customer->cust_no);// نسخ رقم العميل
							    d->amount = deposit_amount;// تعيين مبلغ الإيداع
							   
							
							    // تحديث مصفوفة الإيداعات داخل العميل
							    p->customer->deposits[p->customer->deposit_count++] = d;// زيادة العداد
							
							    // تحديث الرصيد الحالي للعميل
							    p->customer->balance += deposit_amount;
							
							    cout << "Deposit number: " << d->deposit_no << endl;
							    cout << "Deposit successful! New balance: " << p->customer->balance << endl;
							    
							}
							
							else{
							    cout << "No customer account to deposit into." << endl;
							}
							
                             break;
                       
                        

                    case 3: // خروج من قائمة المدير
                        cout << "Exiting manager..." << endl;
                        break;

                    default:
                        cout << "Invalid choice. Try again." << endl;
                }
                
          }
         
            } while(choices != 3); // تبقى في القائمة حتى يختار الخروج

            break; // الخروج من البحث عن المحفظة بعد تنفيذ Manager
        }

        p = p->link; // الانتقال للمحفظة التالية
     }
    if(p == NULL){
        cout << "You don't have a wallet. Create a wallet first." << endl;
    }

       
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
    open_wallet*& wallet,// مؤشر للمحفظه الحاليه 
    customer_acc*& customer// مؤشر لحساب العميل الحالي
) {
    open_wallet* a = h;

    while (a != NULL) {
        if (strcmp(a->wallet_no, wallet_out) == 0 && a->customer != NULL && strcmp(a->password, password) == 0) {
            if (strcmp(a->customer->cust_no, cust_out) == 0) {
                wallet = a;// تعيين المحفظه الحاليه
                customer = a->customer; // تعيين حساب العميل الحالي
                return true;
            }
        }
        a = a->link;
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
       
     else{
    strcpy(customer->password, new_password);
    strcpy(wallet->password, new_password);

    cout << "Password changed successfully.\n";
    return true;
    }
 }


  void Customer() {

    char wallet_out[20];
    char cust_out[20];
    char password[20];
    int ch;

    //  مؤشرات Session
    open_wallet* current_wallet = NULL;
    customer_acc* current_customer = NULL;

    // ===== Login =====
    cout << "Enter your wallet number: ";
    cin >> wallet_out;

    cout << "Enter your customer account number: ";
    cin >> cust_out;

    cout << "Enter your password: ";
    cin >> password;

    if (!customer_login(wallet_out, cust_out, password,  current_wallet, current_customer)) {
        cout << "Wallet or customer not found.\n";
        return;
    }

    // ===== Customer Session =====
    do {
    	
        show_Customer();  // عرض المنيو بعد التحقق
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {

        // ===== Transfer =====
        case 1: {
            char target_wallet_no[20];
            char target_cust_no[20];
            float amount;
            bool confirm;

            // 1️⃣ إدخال رقم محفظة المستلم
            cout << "Enter target wallet number: ";
            cin >> target_wallet_no;
            
            // 1️⃣ إدخال رقم حساب المستلم
            cout << "Enter target  number: ";
            cin >> target_cust_no;

            // 2️⃣ البحث عن المحفظة المستقبلة ورقم الحساب
            open_wallet* receiver_wallet = h;
            while (receiver_wallet != NULL &&
                   strcmp(receiver_wallet->wallet_no, target_wallet_no) != 0) {
                   	
                receiver_wallet = receiver_wallet->link;
            }
            

           if (receiver_wallet == NULL ||
               receiver_wallet->customer == NULL ||
            strcmp(receiver_wallet->customer->cust_no, target_cust_no) != 0) {

            cout << "Receiver customer account not found.\n";
           break;
         }


            // 3️⃣ إدخال المبلغ
            cout << "Enter amount: ";
            cin >> amount;

            if (amount <= 0 || amount > current_customer->balance) {
                cout << "Invalid amount.\n";
                break;
            }

            // 4️⃣ رسالة التأكيد
            cout << "\nAre you sure you want to transfer " << amount
                 << " to wallet number " << receiver_wallet->wallet_no << endl <<
				 "And the username that was transferred to him is: " <<  receiver_wallet->customer->cust_name << endl;
            cout << "1- Yes\n0- No\n";
            cout << "Your choice: ";
            cin >> confirm;

            if (!confirm) {
                cout << "Transfer cancelled successfully.\n";
                break;
            }

            // 5️⃣ تنفيذ التحويل
            current_customer->balance -= amount;
            receiver_wallet->customer->balance += amount;

            // 6️⃣ إنشاء سجل التحويل وتخزينه في مصفوفة transfers
            transfer* tr = new transfer;
            static int trans_id = 100;
            tr->trans_no = ++trans_id;

            strcpy(tr->cust_out, current_customer->cust_no);// 
            strcpy(tr->cust_in, receiver_wallet->customer->cust_no);//
            strcpy(tr->wallet_out, current_wallet->wallet_no);//
            strcpy(tr->wallet_in, receiver_wallet->wallet_no);//
            tr->amount = amount;

            current_customer->transfers[current_customer->transfer_count++] = tr;
              Sleep(2500);
            // 7️⃣ عرض النتيجة
            cout << "\nTransfer completed successfully.\n";
            cout << "Transfer wallet number: " << tr->wallet_out << endl;
            cout << "Transferr account number: " << tr->cust_out << endl;
            cout << "The wallet number of the recipient: " << tr->wallet_in << endl;
            cout << "Account number to which the money is transferred: " << tr->cust_in << endl;
            cout << "Transfer number: " << trans_id << endl;
            cout << "Your new balance: " << current_customer->balance << endl;

            break;
        }

        // ===== Change Password =====
        case 2:
            changing_of_password(current_customer, current_wallet);
            break;

        case 3:
            cout << "Exiting customer service...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (ch != 3);
}



 
 int main(){
 	number = new int[size];
    h = NULL, t = NULL;
    int choice;
    do{
      show_menu();
       
      
      cout << "Enter your choice: ";
      cin >> choice;
      
     if(choice > 0 && choice < 4){
      switch(choice){
        case 1:// اضافه محفظه جديده
        	 add_wallet();
             
             break;

        case 2:  // مدير المحافظ
               wallet_manager();
		       break;

        case 3: // خدمات العملاء
             	Customer();
             	break;
      }
   }
   
  }while(choice != 4);
   
    // ===== تنظيف الذاكرة =====
   open_wallet* tempW;

  while (h != NULL) {
	    tempW = h;
	    h = h->link;
	
	    if (tempW->customer != NULL) {
	
	        // حذف الإيداعات
	        for (int i = 0; i < tempW->customer->deposit_count; i++) {
	            delete tempW->customer->deposits[i];
	        }
	
	        // حذف التحويلات
	        for (int i = 0; i < tempW->customer->transfer_count; i++) {
	            delete tempW->customer->transfers[i];
	        }
	
	        // حذف العميل نفسه
	        delete tempW->customer;
	    }
	
	    // حذف المحفظة
	    delete tempW;
    }

 // حذف المصفوفة
delete[] number;

   cout << "Exiting program. Goodbye!" << endl;

   return 0;
}
   
 

