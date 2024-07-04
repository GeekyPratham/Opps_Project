/*

Welcome To Super Market Billing System
*****************************************
1.Add Item.
2.Print Bill.
3.Exit.
4.Enter Choice

*/
#include <iostream> // for input output i.e cin,cout etc
#include <fstream> // for use of filehandling
#include <sstream> // for other datatypes i.e convert into string (conversion)  
#include <windows.h> // use for sleep()

using namespace std;

class Bill{
private:
    string Item;
    int Rate;
    int Quantity;

public:

    // constructor

    // 1. default constructor
    Bill(){
        Item = "empty";
        Rate = 0;
        Quantity = 0;
    }
    // 2. parameterized constructor
    Bill(string item,int r,int q){
        setItem(item);
        setRate(r);
        setQuantity(q);
    }
    
    // setter function
    void setItem(string item){
        Item = item;
    }
    void setRate(int rate){
        Rate = rate;
    }
    void setQuantity(int quant){
        if(quant > 0){
            Quantity = quant;
        }
        else Quantity = 0;
    }

    // Getter Funciton
    string getItem(){
        return Item;
    }
    int getRate(){
        return Rate;
    }
    int getQuantity(){
        return Quantity;
    }
};

void addItem(Bill b){
    bool close = false;
    while(!close){
        system("cls");
        int choice;
        cout<<"\t1.Add."<<endl; // press 1 then we can add
        cout<<"\t2.close."<<endl; // press key 2 to exit from add item 
        cout<<"\tEnter Choice: ";
        cin>>choice;

        if(choice == 1){
            string item;
            int rate,quant;

            cout<<"\tEnter Item Name : ";
            cin>>item;
            b.setItem(item);

            cout<<"\tEnter Rate Of Item : ";
            cin>>rate;
            b.setRate(rate);

            cout<<"\tEnter Quantity of Item : ";
            cin>>quant;
            b.setQuantity(quant);

            // save this data into file
            ofstream out("D:/BillFolder/Bill.txt",ios::app); // for sending data into file  we use ofstream out("filename")
            //"ios::app" iska use karne se phele wala item apne jagha pe rahega aur dusra item add ho jayega
            if(!out){
                cout<<"\tError : File Can't Open!"<<endl;
            }
            else{
                out<<"\t"<<b.getItem()<<" : "<<b.getRate()<<" : "<<b.getQuantity()<<endl;
            }
            out.close();
            cout<<"\tItem Added Successfully: "<<endl;
            Sleep(3000); // it is in milisecond. display for 3000ms ie 3sec 
        }

        else if(choice == 2){
            system("cls");
            close = true;
            cout<<"\tBack To Main Menu !"<<endl;
            Sleep(3000);
        }
    }
}

void PrintBill(){
    system("cls");

    int count = 0;

    bool close = false;
    while(!close){
        system("cls");
        int choice;
        cout<<"\t1.Add Bill."<<endl;
        cout<<"\t2.Close Session."<<endl;
        cout<<"\tEnter Choice: ";
        cin>>choice;

        if(choice == 1){
            string item;
            int quant;

            cout<<"\tEnter Item: ";
            cin>>item;
            // b.setItem(item);

            cout<<"\tEnter Quantity : ";
            cin>>quant;
            // b.setQuantity(quant);

            ifstream in("D:/BillFolder/Bill.txt");// ifstream is used to take input from the file and in is the nome of ifstream 
            ofstream out("D:/BillFolder/BillTemp.txt");


            string line; // variable used for taking input from input file
            bool found = false;
            
            while(getline(in,line)){ // take input from "in" in form of string variable line
                stringstream ss;
                ss<<line;
                // from file
                string itemName;
                int itemRate,itemQuant;

                char delimiter;// "  : " ka use ke lia hai

                ss>>itemName>>delimiter>>itemRate>>delimiter>>itemQuant;

                if(item == itemName){
                    found = true;
                    if(quant <= itemQuant){
                        int amount = itemRate*quant;
                        cout<<"\t Item | Rate | Quantity | Amount"<<endl;
                        cout<<"\t "<<itemName<<"\t "<<itemRate<<"\t "<<quant<<"\t "<<amount<<endl;

                        int newQuant = itemQuant - quant;
                        itemQuant = newQuant;
                        count += amount;

                        out<<"\t"<<itemName<<" : "<<itemRate<<" : "<<itemQuant<<endl<<endl;
                    }
                    else{
                        // not quantity is wrong
                        cout<<"\tSorry, "<<item<<" Ended!"<<endl;
                    }
                }
                else{
                    //not item found
                    out<<line<<endl;
                }
            }
            if(!found){
                cout<<"\tItem Not Available!"<<endl;
            }
            out.close();
            in.close();
            remove("D:/BillFolder/Bill.txt");
            rename("D:/BillFolder/BillTemp.txt","D:/BillFolder/Bill.txt");
        }

        else if (choice == 2){
            close = true;
            cout<<"\tCounting Total Bill"<<endl;
        }
        Sleep(3000);
    }
    system("cls");
    cout<<endl<<endl;

    cout<<"\t Total Bill ------------: "<<count<<endl<<endl;
    cout<<"\t Thanks for shopping"<<endl;
    Sleep(5000);

}

int main(){
    Bill b;// object of class Bill

    bool exit = false;
    while(!exit){
        system("cls"); // to hide previous output and display current input
        int val;

        cout<<"\tWelcome To Super Market Billing System"<<endl;
        cout<<"\t*****************************************"<<endl;
        cout<<"\t\t1.Add Item."<<endl;
        cout<<"\t\t2.Print Bill"<<endl;
        cout<<"\t\t3.Exit"<<endl;
        cout<<"\t\tEnter Choice"<<endl;

        cin>>val;

        if(val==1){
            system("cls");//"cls" means clear screen
            addItem(b);
            Sleep(3000);
        }
        else if(val == 2){
            
            PrintBill();
        }
        else if(val == 3){
            system("cls");
            exit = true;
            cout<<"\t Have a Nice Day! "<<endl;
            Sleep(3000);
        }

    }
}