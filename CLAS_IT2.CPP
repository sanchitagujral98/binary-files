// binary file handling using classes

#include<conio.h>
#include<fstream.h>
#include<stdio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

class item
{
 int icode;
 char name[20];
 float price;
 int stock;

 public : item()
	  { icode=0;
	    strcpy(name," ");
	    price=0.0;
	    stock=0;
	  }

	  void getdata()
	  {
	   cout<<"\n Enter Item Code : "<<'\n';
	   cin>>icode;
	   cout<<"Enter Item Name : "<<'\n';
	   gets(name);
	   cout<<"Enter Item Price : "<<'\n';
	   cin>>price;
	   cout<<"Enter Item Stock : "<<'\n';
	   cin>>stock;
	  }
	  void showdata()
	  {
		cout<<"Item Code  : "<<icode<<'\t';
		cout<<"Item Name  : "<<name<<'\t';
		cout<<"Item Price : "<<price<<'\n';
		cout<<"Item Stock : "<<stock<<'\n';
	  }
		int geticode()
	  {
		return icode;
	  }

	  char* getname()
	  {
		return name;
	  }

	  int getprice()
	  {
		return price;
	  }

	  int getstock()
	  {
		return stock;
	  }
	  void setprice()
	  {cin>>price;}
	  void setstock()
	  {cin>>stock;}
};

void create()
{
	ofstream mf;
	mf.open("abc.dat",ios::binary);
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
		it.getdata();
		mf.write((char*)& it,sizeof(item));
		cout<<"want to continue?";
		cin>>ch;
	}
	while(ch=='Y' || ch=='y');
	mf.close();
}
void display_file()
{
   clrscr();
   cout<<"--------Item Details---------"<<'\n';
   ifstream mf("abc.dat",ios::binary);
   if(!mf)
   {
	cout<<"stream not created";
	getch();
	exit(0);
   }

  item it;
  mf.read((char *)& it, sizeof(item));
  while(mf)
  {
	it.showdata();
	mf.read((char *) & it, sizeof(item));
  }
  mf.close();
}


void stock_detail()
{
	clrscr();
	cout<<"-----Items with Stock more than 100-----"<<'\n';
	ifstream mf;
	mf.open("abc.dat",ios::binary);
	item it;
	if(!mf)
	{
		cout<<"Stream not Created";
		getch();
		exit(0);
	}
	mf.read((char *) &it,sizeof(item));
	while(mf)
	{
		if( it.getstock() >100)
		{ it.showdata();}
		mf.read((char *) &it,sizeof(item));
	}
	mf.close();
}

void price_stock()
{
	clrscr();
	cout<<"----Items with stock<100 and Prize>1000----"<<'\n';
	ifstream  mf;
	item it;
	mf.open("abc.dat",ios::binary);
	if(!mf)
	{
		cout<<"Stream Not Created";
		getch();
		exit(0);
	}
	mf.read((char *) &it,sizeof(item));
	while(mf)
	{
		if( it.getstock() <100 && it.getprice() >1000)
		{   it.showdata();}
		mf.read((char *) &it,sizeof(item));
	}
	mf.close();
}

void search1_rec()
{
	clrscr();
	cout<<"----Search by Item Code---"<<'/n';
	int num; item it;
	ifstream mf;
	mf.open("abc.dat",ios::binary);
	if(!mf)
	{
		cout<<"Stream Not Created";
		getch();
		exit(0);
	}
	cout<<"---Search By Item Code--"<<'\n';
	cout<<"Enter Item Code : ";
	cin>>num;
	mf.read((char *) &it,sizeof(item));
	while( mf && num!=it.geticode())
	mf.read((char*) &it,sizeof(item));
	if(num== it.geticode())
	{
		it.showdata();
	}
	else
	cout<<"Not Found";
	mf.close();
}
void search2_rec()
{
	clrscr();
	cout<<"----Search by Name(all)----"<<'\n';
	ifstream mf; char sname[20]; item it;
	mf.open("abc.dat",ios::binary);
	if(!mf)
	{
		cout<<"Stream Not Created";
		getch();
		exit(0);
	}
	cout<<"Enter the Name to be Searched : "<<'\n';
	gets(sname);
	mf.read((char *) &it,sizeof(item));
	while(mf)
	{
		if(strcmpi(it.getname(),sname)==0)
		{     it.showdata();}
		mf.read((char *) &it,sizeof(item));
	}
	mf.close();
}
void add_rec()
{
	clrscr();
	display_file();
	cout<<"----Addition of Item----"<<'\n';
	ofstream mf("abc.dat",ios::binary|ios::app);
	char ch;
	if(!mf)
	{
		cout<<"Stream Not Created";
		getch();
		exit(0);
	}
	item it;
	do
	{
		it.getdata();
		mf.write((char *) &it,sizeof(item));
		cout<<"Want to continue? "<<'\n';
		cin>>ch;
	}
	while(ch=='Y' || ch=='y');
	mf.close();
}

void delete_rec()
{
	clrscr();
	display_file();
	cout<<"----Deletion of a Record----"<<'\n';
	ifstream oldfile;
	item it;
	oldfile.open("abc.dat",ios::binary);
	if(!oldfile)
	{
		cout<<"Stream Not Created";
		getch();
		exit(0);
	}
	ofstream newfile;
	newfile.open("item.dat",ios::binary);
	int num; cout<<"Enter Item Code of item to be deleted : ";
	cin>>num;
	int f=0;
	oldfile.read((char *) &it,sizeof(item));
	while(oldfile)
	{
		if(it.geticode()!=num)
		newfile.write((char *) &it,sizeof(item));
		else f=1;
		oldfile.read((char *) &it,sizeof(item));
	}
	oldfile.close();
	newfile.close();
	remove("abc.dat");
	rename("item.dat","abc.dat");
	if(f==1)
	cout<<"Deleted";
	else cout<<"Not found";
	display_file();
}

void update_price()
{
	clrscr();
	display_file();
	fstream mf;
	long pos;
	mf.open("abc.dat",ios::binary|ios::in|ios::out);
	if(!mf)
	{
		cout<<"no stream created"<<'\n';
		exit(0);
	}
	item it;int num;
	cout<<"enter existing item code : "<<'\n';
	cin>>num;
	mf.read((char *) &it,sizeof(item));
	while(mf && num!=it.geticode())
	mf.read((char *) &it,sizeof(item));
	if(it.geticode()==num)
	{
		long pos=mf.tellg();
		pos-=sizeof(item);
		mf.seekg(pos,ios::beg);
		cout<<"Item Name : "<<it.getname()<<'\n';
		cout<<"Enter New Prize : ";
		it.setprice();
		cout<<"Enter New Stock : ";
		it.setstock();
		mf.write((char *) &it,sizeof(item));
	}
	else cout<<"Not found";
	mf.close();
}

void main()
{
	int a;
	char m;
	item it;
	do
	{ 	clrscr();
		cout<<"create a file-----------------------------0"<<'\n';
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
		cin>>a;
		switch(a)
		{ case 0:
			{
				clrscr();
				create();
				cout<<"\n File Created "<<'\n';
				display_file();
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
  }
  cout<<"Want to Continue? "<<'\n';
  cin>>m;}
  while(m=='Y' || m== 'y');
  getch();
}