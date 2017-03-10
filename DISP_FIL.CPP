//binary file handling using structures 

#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
struct item
{
	int icode;
	char name[20];
	float price;
	int stock;
};
void create()
{
	ofstream mf;
	mf.open("abc.dat");
	if(!mf)
	{
		cout<<"Stream not created";
		exit(0);
	}
	item it;
	char ch;
	do
	{
		clrscr();
		cout<<"\n Enter Item Code : "<<'\n';
		cin>>it.icode;
		cout<<"Enter Item Name : "<<'\n';
		gets(it.name);
		cout<<"Enter Item Price : "<<'\n';
		cin>>it.price;
		cout<<"Enter Item Stock : "<<'\n';
		cin>>it.stock;
		mf.write((char*)& it,sizeof(item));
		cout<<"want to continue?";
		cin>>ch;
	}
	while(ch=='Y' || ch=='y');
	mf.close();
}
void display_rec(item it)
{
	clrscr();
	cout<<"code "<<it.icode<<'\n';
	cout<<"name "<<it.name<<'\n';
	cout<<"stock "<<it.stock<<'\n';
	cout<<"price "<<it.price<<'\n';
}
void display_file()
{
	clrscr();
	ifstream mf("abc.dat",ios::binary);
	if(!mf)
	{cout<<"stream not created";
	 return;
	}
	item it;
	//	mf.read((char*)&it,sizeof(item));

	mf.read((char*)&it,sizeof(item));
	while (mf)
	{
		display_rec(it);
		mf.read((char*)&it,sizeof(item));
	}
}

void stock_detail()
{
	clrscr();
	ifstream mf;
	mf.open("abc.dat",ios::binary|ios::in);
	item it;
	if(!mf)
	cout<<"stream not created";
	mf.read((char*)&it,sizeof(item));
	while (mf)
	{
		if(it.stock>=100)
		display_rec(it);
		mf.read((char*)&it,sizeof(item));
	}
	mf.close();
}
void price_stock()
{
	clrscr();
	ifstream mf;
	mf.open("abc.dat",ios::binary|ios::in);
	item it;
	if(!mf)
	{
	cout<<"stream not created";
	return;
	}
	mf.read((char*)&it,sizeof(item));
	while (mf)
	{
		if(it.stock<100 && it.price>1000)
			display_rec(it);
		mf.read((char*)&it,sizeof(item));
	}
	mf.close();
}
void search1_rec()
{
	clrscr();
	ifstream mf;
	mf.open("abc.dat",ios::binary);
	int num;
	cout<<"enter the item code to be searched- ";
	cin>>num;
	if(!mf)
	{
	cout<<"stream not created";
	return;
	}
	item it;
	mf.read((char*)&it,sizeof(item));
	while (mf)
	{
		if(it.icode==num)
		display_rec(it);
		mf.read((char*)&it,sizeof(item));
	}
	mf.close();
}
void search2_rec()
{
	clrscr();
	ifstream mf;
	mf.open("abc.dat",ios::binary);
	char n[20];
	cout<<"enter the item name to be searched- ";
	gets (n);
	if(!mf)
	{
	cout<<"stream not created";
	return;
	}
	item it;
	mf.read((char*)&it,sizeof(item));
	while (mf)
	{       cout<<"item name-"<<it.name<<'\n';
		if(strcmpi (it.name,n)==0)
		display_rec(it);
		mf.read((char*)&it,sizeof(item));
	}
	mf.close();
}
void add_rec()
{
	clrscr();
	ofstream mf;
	mf.open("abc.dat",ios::binary|ios::app);
	if(!mf)
	{
		cout<<"stream not created";
		exit (0);
	}
	item it;
	cout<<"enter the code of new item-";
	cin>>it.icode;
	cout<<"enter the name of new item-";
	cin>>it.name;
	cout<<"enter the stock of the new item-";
	cin>>it.stock;
	cout<<"enter the price of the new item-";
	cin>>it.price;
	mf.write((char*)&it,sizeof(item));
	display_rec(it);
	mf.close();
}
void delete_rec()
{
	clrscr();
	ifstream oldfile;
	oldfile.open("abc.dat",ios::binary|ios::in);
	if(!oldfile)
	{
	cout<<"file not created";
	return;
	}
	ofstream newfile;
	newfile.open("item.dat",ios::binary|ios::out);
	int num;
	item it;
	int flag=0;
	cout<<"enter the code of item to be deleted-";
	cin>>num;
	oldfile.read((char*)&it,sizeof(item));
	while(oldfile)
	{
		if(it.icode!=num)
			newfile.write((char*)&it,sizeof(item));
		else flag=1;
		oldfile.read((char*)&it,sizeof(item));
	}
	oldfile.close();
	newfile.close();
	remove("abc.dat");
	rename("item.dat","abc.dat");
	if(flag==1)
	cout<<"record deleted"<<'\n';
	else
	cout<<"record not found"<<'\n';
}
void update_price()
{
	clrscr();
	fstream mf;
	mf.open("abc.dat",ios::binary|ios::in|ios::out);
	if(!mf)
	{
		cout<<"stream not created";
		return;
	}
	item it;
	int num,new_price;
	int f=0;
	cout<<"enter the item code of the item to be updated-";
	cin>>num;
	cout<<"enter the new price";
	cin>>new_price;
	mf.read((char*)&it,sizeof(item));
	while (mf)
	{

	if(it.icode==num)
	{       cout<<"inside"<<'\n';
		f=1;
		it.price=new_price;
		mf.seekg(-sizeof(item),ios::cur);
		mf.write((char*)&it,sizeof(item));
		display_rec(it);
	}
	mf.read((char*)&it,sizeof(item));
       //	display_rec(it);
	}
	if(f==0)
		cout<<"record not found"<<'\n';
	mf.close();
}

void main()
{
clrscr();
int n;
item it;
	do{
	cout<<'\n';
	cout<<"create a file.........0"<<'\n';
	cout<<"display the item list and details.........1"<<'\n';
	cout<<"details of items having stock above 100...2"<<'\n';
	cout<<"details of items having price above 1000 and stock less than 100....3"<<'\n';
	cout<<"search an item's details..............4"<<'\n';
	cout<<"search and displaying all records.....5"<<'\n';
	cout<<"add a new record into existing file...6"<<'\n';
	cout<<"delete a record from existing file....7"<<'\n';
	cout<<"update the price of an item...........8"<<'\n';
	cout<<"delete File...........................9"<<'\n';
	cout<<"Exit..................10"<<'\n';
	cout<<"enter your choice";
	cin>>n;
	switch(n)
	{
		case 0:{
				create();
				break;
			}
		case 1:{
				display_file();
				break;
			}
		case 2:{
				stock_detail();
				break;
			}
		case 3:{
				price_stock();
				break;
			}
		case 4:{
				search1_rec();
				break;
			}
		case 5:{
				search2_rec();
				break;
			}
		case 6:{
				add_rec();
				break;
			}
		case 7:{
				delete_rec();
				break;
			}
		case 8:{
				update_price();
				break;
			}
		case 9:{        remove("abc.dat");
				break;
			}
		case 10:{
				exit(0);
				break;
			}
		default:cout<<"wrong input";
	}
//	cout<<"want to continue Y/N";
  //	cin>>ans;
	  }
	while(n!=10);
  getch();
}
