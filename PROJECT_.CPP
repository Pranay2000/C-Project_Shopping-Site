#include<iostream>
#include<conio.h>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<process.h>
using namespace std;
struct eshop
{
    int category;
    char name[30];
    float price;
}item;
int shopcart=0;
int login()
{
     char log[30];
     cout<<endl;
     cout<<"Enter your Login ID : ";
     cin>>log;
     if(strcmp(log,"ABCD") == 0)
       return 1;
     else
       return 0;
}
int alogin()
{
     char log[30];
     cout<<endl;
     cout<<"Enter your Login ID : ";
     cin>>log;
     if(strcmp(log,"abcd") == 0)
       return 1;
     else
       return 0;
}
int pass()
{
     char c[30], c1;
     int check;
     cout<<"Enter Password : ";
     for(int i=0;;i++)
     {   c1=getch();
	 check = c1;
	 if(check == 13)
	 {
	     c[i] = '\0';
	     break;
	     }
	 c[i] =c1;
	 cout<<"*";
	 }
     if(strcmp(c,"1234") == 0)
       return 1;
     else
       return 0;
}
int apass()
{
    char c[30], c1;
    int check;
    cout<<"Enter Password : ";
    for(int i=0;;i++)
    {   c1=getch();
	check = c1;
	if(check == 13)
	{
	    c[i] = '\0';
	    break;
	    }
	c[i] =c1;
	cout<<"*";
	}
    if(strcmp(c,"12345") == 0)
      return 1;
    else
      return 0;
}
void Buyclothes()
{
      char cht,chb,chj,chd,chn;
      int ch, ch2,ch3,ch4,ch5,ch6;
      clrscr();
      cout<<"------******------It's time to shop------******------"<<endl;
      cout<<"                  1.Tops "<<endl;
      cout<<"                  2.Bottoms "<<endl;
      cout<<"                  3.Jumpsuits "<<endl;
      cout<<"                  4.Dresses "<<endl;
      cout<<"                  5.Nightsuits "<<endl;
      cout<<"                  6.Checkout "<<endl;
      cout<<" Enter Choice: ";
      cin>>ch;
      if(ch == 6)
      {
	  cout<<"Your total bill is: "<<shopcart<<endl;
	  cout<<"Press any key... ";
	  getch();
	  }
      else
      {
	  ifstream f1;
	  f1.open("itemlist.dat",ios::in|ios::binary);
	  cout<<"S.No. \t";
	  cout<<"Price \t";
	  cout<<"Category"<<endl;
	  int cnt=1;
	  f1.seekg(0,ios::beg);
	  while(f1.read((char*)&item,sizeof(item)))
	  {
		if(item.category==ch)
		{
		     cout<<cnt<<"\t";
		     cout<<item.price<<"\t";
		     cout<<item.name<<endl;
		     cnt++;
		     }
		}
	  f1.close();
	  cout<<cnt<<"\t"<<"Go back to menu"<<endl;
	  cnt++;
	  cout<<cnt<<"\t"<<"Checkout"<<endl;
	  cnt = cnt-2;
	  cout<<endl<<"Enter your choice: ";
	  cin>>ch2;
	  if(ch2==(cnt+1))
	  {
		Buyclothes();
	   }
	  else if(ch2==(cnt+2))
	  {
		cout<<"Your total bill is:  "<<shopcart ;
		cout<<endl <<endl;
		cout<<"Press any key... ";
		getch();
		}
	  else
	  {
	     ifstream f2;
	     f2.open("itemlist.dat",ios::in|ios::binary);
	     f2.seekg(0,ios::beg);
	     cnt=0;
	     while(f2.read((char*)&item,sizeof(item)))
	     {
		if(item.category==ch)
		{
		   cnt++;
		   if(ch2==cnt)
		   {
		     cout<<"Are you sure you want to buy this item(y/n): "<<endl;
		     cin>>cht;
		     if(cht=='y')
		     {
			cout<<"Your item has been successfully added to your shopping cart!"<<endl;
			cout<<"Press any key.. ";
			getch();
			shopcart=shopcart+item.price;
			}
		   break;
		   }
	       }
	   }
      f2.close();
      Buyclothes();
      }
   }
}


void iwrite()
{
    char rep='y';
    ofstream f1;
    f1.open("itemlist.dat",ios::app|ios::binary);
    do
    {
	cout<<"-----------------------------------------------"<<endl;
	cout<<"                  1.Tops "<<endl;
	cout<<"                  2.Bottoms "<<endl;
	cout<<"                  3.Jumpsuits "<<endl;
	cout<<"                  4.Dresses "<<endl;
	cout<<"                  5.Nightsuits "<<endl;
	cout<<"-----------------------------------------------"<<endl;
	cout<<"Enter category: ";
	cin>>item.category;
	cout<<"Enter item name: ";
	gets(item.name);
	cout<<"Enter price: ";
	cin>>item.price;
	f1.write((char*)&item,sizeof(item));
	cout<<"Item successfully added !! "<<endl<<endl;
	cout<<"Do you wish to add more? (y/n) ";
	cin>>rep;
     }while(rep=='y');
     getch();
   f1.close();
}

void iread()
{   clrscr();
    ifstream f1;
    f1.open("itemlist.dat",ios::in|ios::binary);
    f1.seekg(0,ios::beg);
    cout<<"Category: \t";
    cout<<"Price: \t";
    cout<<"Item Name: "<<endl<<endl;
    while(f1.read((char*)&item,sizeof(item)))
    {
	cout<<item.category<<"\t";
	cout<<item.price<<"\t";
	cout<<item.name<<endl;
	}
    getch();
    f1.close();
}
void idelete()
{   clrscr();
    cout<<"\nDeletion of item! "<<endl;
    char reply='n';
    ifstream f1;
    ofstream f2;
    f1.open("itemlist.dat",ios::in|ios::app|ios::binary);
    f2.open("temp.dat",ios::in|ios::out|ios::binary);
    f1.seekg(0,ios::beg);
    f2.seekp(0,ios::beg);
    while(f1.read((char*)&item,sizeof(item)))
    {
	cout<<"Category: "<<item.category<<"\t";
	cout<<"Price: "<<item.price<<"\t";
	cout<<"Item name: "<<item.name<<endl;
	cout<<endl<<"Do you wish to delete this record? (y/n) ";
	cin>>reply;
	if(reply == 'n')
	{
	     f2.write((char*)&item,sizeof(item));
	     }
	}
    f1.close();
    f2.close();
    remove("itemlist.dat");
    rename("temp.dat","itemlist.dat");
}
void iseq_search()
{   clrscr();
    cout<<"                Searching item sequentially!"<<endl;
    char reply = 'n';
    ifstream f1;
    f1.open("itemlist.dat",ios::in|ios::binary);
    f1.seekg(0,ios::beg);
    while(f1.read((char*)&item,sizeof(item)) && reply!='y')
    {
	cout<<"Category: "<<item.category<<"\t";
	cout<<"Price: "<<item.price<<"\t";
	cout<<"Item name: "<<item.name<<endl;
	cout<<endl<<"Is this the record you were searching for? (y/n) ";
	cin>>reply;
	cout<<endl;
	}
    if(reply == 'y')
      cout<<endl<<"Record found !";
    else
      cout<<endl<<"Record not found !";
    getch();
    f1.close();
}
void rand_search(int rec_no)
{
    ifstream f1;
    f1.open("itemlist.dat",ios::in|ios::binary);
    f1.seekg((rec_no-1)*sizeof(item));
    f1.read((char*)&item,sizeof(item));
    cout<<"Category: "<<item.category<<"\t";
    cout<<"Price: "<<item.price<<"\t";
    cout<<"Item name: "<<item.name<<endl;
    cout<<endl<<"Record found!"<<endl;
    getch();
    f1.close();
}
void iseq_modify()
{   clrscr();
    cout<<"              Modifying item list sequentially! "<<endl;
    char reply = 'n';
    ifstream f1;
    ofstream f2;
    f1.open("itemlist.dat",ios::in|ios::binary);
    f2.open("temp.dat",ios::out|ios::binary);
    f1.seekg(0,ios::beg);
    f2.seekp(0,ios::beg);
    while(f1.read((char*)&item,sizeof(item)))
    {
	cout<<"Category: "<<item.category<<"\t";
	cout<<"Price: "<<item.price<<"\t";
	cout<<"Item name: "<<item.name<<endl;
	cout<<endl<<"Is this the record you wish to modify? (y/n) ";
	cin>>reply;
	cout<<endl;
	if(reply == 'y')
	{
	     cout<<endl<<"Enter new details: "<<endl<<endl;
	     cout<<"Enter category: ";
	     cin>>item.category;
	     cout<<"Enter item name: ";
	     gets(item.name);
	     cout<<"Enter price: ";
	     cin>>item.price;
	     cout<<"Record Modified!";
	     f2.write((char*)&item,sizeof(item));
	     }
	else
	   f2.write((char*)&item,sizeof(item));
	}
    getch();
    f1.close();
    f2.close();
    remove("itemlist.dat");
    rename("temp.dat","itemlist.dat");
}
void rand_modify(int rec_no)
{
    fstream f1;
    f1.open("itemlist.dat",ios::in|ios::out|ios::binary);
    f1.seekg(0,ios::beg);
    f1.seekp(0,ios::beg);
    f1.seekg((rec_no-1)*sizeof(item));
    f1.read((char*)&item,sizeof(item));
    cout<<endl<<"This is the record to be modified:  ";
    cout<<endl<<endl;
    cout<<"Category: "<<item.category<<endl;
    cout<<"Item name: "<<item.name<<endl;
    cout<<"Price: "<<item.price<<endl;
    cout<<endl<<"Enter new details: "<<endl<<endl;
    cout<<"Enter category: ";
    cin>>item.category;
    cout<<"Enter item name: ";
    gets(item.name);
    cout<<"Enter price: ";
    cin>>item.price;
    f1.seekp((rec_no-1)*sizeof(item));
    f1.write((char*)&item,sizeof(item));
    f1.close();
    getch();
    cout<<" Record Modified! ";
}
void admin_menu()
{   clrscr();
    int choice;
    cout<<"=====================*ADMIN MENU*===================="<<endl;
    cout<<"                    1. Add items"<<endl;
    cout<<"	            2. Delete items"<<endl;
    cout<<"	            3. Search items(sequentially)"<<endl;
    cout<<"	            4. Search items(randomly)"<<endl;
    cout<<"	            5. Modify items(sequentially)"<<endl;
    cout<<"	            6. Modify items(randomly)"<<endl;
    cout<<"                 7. Display items "<<endl;
    cout<<"                 8. Exit "<<endl;
    cout<<"====================================================="<<endl;
    cout<<"Enter choice: ";
    cin>>choice;
    if(choice==8)
    {
	cout<<"Exiting...  ";
	getch();
	exit(0);
	}
    else if(choice==7)
    {
	iread();
	getch();
	}
    else if(choice==1)
    {
	iwrite();
	iread();
	}
    else if(choice==2)
    {
       idelete();
       }
    else if(choice == 3)
    {
	iseq_search();
	}
    else if(choice == 4)
    {   clrscr();
	cout<<"             Searching item randomly!";
	int rec_no;
	cout<<"Enter the record to be searched: ";
	cin>>rec_no;
	rand_search(rec_no);
	}
    else if(choice == 5)
    {
	iseq_modify();
	}
    else if(choice == 6)
    {   clrscr();
	cout<<"            Modifying item list randomly! ";
	int rec_no;
	cout<<endl<<"Enter the record no. to be modified: ";
	cin>>rec_no;
	rand_modify(rec_no);
	}
    admin_menu();
}
void main()
{   clrscr();
    int ch,ch1,choice;
    int check,check1;
    cout<<"------*****------MAIN MENU------*****------";
    cout<<endl;
    cout<<"                1. Customer Login "<<endl;
    cout<<"                2. Admin Login "<<endl;
    cout<<"-------------------------------------------"<<endl<<endl;
    cout<<"Enter choice: ";
    cin>>ch;
    if(ch==1)
    {  clrscr();
       check=login();
       check1=pass();
       if(check==1&&check1==1)
       {
	   cout<<endl<<endl<<"Login Successful!!!";
	   cout<<endl<<"Press any key... ";
	   getch();
	   clrscr();
	   cout<<endl<<endl;
	   cout<<"------******------Welcome to Clothesforyou.com------******------";
	   cout<<endl;
	   cout<<"                  1. Buy Clothes " <<endl;
	   cout<<"                  2. Logout  "<<endl;
	   cout<<"Enter choice: ";
	   cin>>ch1;
	   if(ch1==1)
	   {
		Buyclothes();
		getch();
		}
	   if(ch1==2)
	   {
		cout<<"Logging Out... ";
		getch();
		exit(0);
		}
	   }
       else
       {
	   cout<<endl<<endl;
	   cout<<"Incorrect Login ID or Password !! ";
	   cout<<endl<<"Press any key... ";
	   getch();
	   }
	}
    if(ch==2)
    {  clrscr();
       check=alogin();
       check1=apass();
       if(check==1&&check1==1)
       {
	   cout<<endl<<endl<<"Login Successful!!!";
	   cout<<endl<<"Press any key... ";
	   getch();
	   admin_menu();
	   }
       else
       {
	   cout<<endl<<endl;
	   cout<<"Incorrect Login ID or Password !! ";
	   cout<<endl<<"Press any key... ";
	   getch();
	   }
      }
}
