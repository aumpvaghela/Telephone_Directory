#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
class Directory
{
	private:
		char name[50],address[50];
		int areacode;
		long long phone_no;
		
	public:
		void New_Record()
		{
			cout<<endl<<"Enter your name : ";cin>>name;
			cout<<endl<<"Enter your residential address : ";cin>>address;
			cout<<endl<<"Enter your Area-code : ";cin>>areacode;
			cout<<endl<<"Enter your phone no. : ";cin>>phone_no;	 
		}
		void display_all_records()
		{
			cout<<endl<<name<<setw(15)<<address<<setw(15)<<areacode<<setw(15)<<phone_no<<endl;
		}
		long long get_p()
		{
			return phone_no;
		}
		void update_phone(long long p)
		{
			phone_no=p;
		}
		int get_areacode()
		{
			return areacode;
		}
};

Directory d;
fstream f;

void write()
{
	f.open("TELEPHONE.dat",ios::binary|ios::app);
	d.New_Record();
	f.write((char*)&d,sizeof(d));
	f.close();
}
void read()
{
	cout<<endl<<"NAME"<<setw(15)<<"ADDRESS"<<setw(15)<<"AREA-CODE"<<setw(15)<<"PHONE NO."<<endl<<endl;
	f.open("TELEPHONE.dat",ios::binary|ios::in);
	while(f.read((char*)&d,sizeof(d)))
	{
		d.display_all_records();
	}	
	f.close();
}

void SEARCH_RECORD()
{
	int flag=0;
	long long phone_no;
	cout<<endl<<" Enter phone no. of person you want record of : ";
	cin>>phone_no;
	
	f.open("TELEPHONE.dat",ios::binary|ios::in);
	if(!f)
	{
		cout<<"File Error";return;
	}
	else
	{
		while(f)
		{
			if(f.read((char*)&d,sizeof(d)))
			{
				if(d.get_p()==phone_no)
				{
					cout<<endl<<" Record Found "<<endl;
					d.display_all_records();					
					flag=1;
					break;
				}
			}
		}
		if(flag==0)
		{
			cout<<endl<<"No Data Found";
		}
		f.close();
	}
}

void UPDATE_RECORD()
{
	int flag=0;
	long long p,phone_no;
	f.open("TELEPHONE.dat",ios::binary|ios::in|ios::out);
	if(!f)
	{
		cout<<"\n File Not Found ";return;
	}
	else
	{
		cout<<"\nEnter phone no : ";cin>>phone_no;
		while(f)
		{
			
			
			if(f.read((char*)&d,sizeof(d)))
			{
				int ps=f.tellg();
				if(d.get_p()==phone_no)
				{
					flag=1;
					cout<<"\nEnter new phone no. : ";
					cin>>p;
					d.update_phone(p);
					d.display_all_records();
					
					f.seekp(ps-sizeof(d));
					f.write((char*)&d,sizeof(d));
					
					break;
				}
			}
		}
		if(flag==0)
		{
			cout<<"\n\t No Data Found ";
		}
		f.close();
		cout<<"\nSuccessful ";
	}
}

void DELETE_RECORD()
{
	long long phone_no;
	fstream file;
	cout<<"\nEnter phone  you want to delete record of : ";cin>>phone_no;
	f.open("TELEPHONE.dat",ios::binary|ios::in);
	file.open("new.dat",ios::binary|ios::app);
	while(f)
		{
			if(f.read((char*)&d,sizeof(d)))
			{
				if(d.get_p()!=phone_no)
				{
					file.write((char*)&d,sizeof(d));
				}
			}
		}
	f.close();
	file.close();
	remove("TELEPHONE.dat");
	rename("new.dat","TELEPHONE.dat");
}

void COPYABC()
{
	fstream file;
	f.open("TELEPHONE.dat",ios::binary|ios::in);
	file.open("TELEBACK.dat",ios::binary|ios::app);
		while(f)
		{
			if(f.read((char*)&d,sizeof(d)))
			{
				if(d.get_areacode()==123)
				{
					file.write((char*)&d,sizeof(d));
				}
			}
		}
	f.close();
	file.close();
}

int main()
{
	int ch;
	cout<<endl<<"..WELCOME TO TELEPHONE EXCHANGE...";
	while(1)
	{
		
		cout<<endl<<endl<<"*******Menu********";
		cout<<endl<<endl<<"1. TO ADD RECORD";
		cout<<endl<<"2. TO DISPLAY ALL RECORD";
		cout<<endl<<"3. TO SEARCH PARTICULAR RECORD";
		cout<<endl<<"4. TO UPDATE PHONE_NO.";
		cout<<endl<<"5. TO DELETE PARTICULAR RECORD";
		cout<<endl<<"6. TO COPY RECORD OF AREACODE 123";
		cout<<endl<<"7. TO EXIT "<<endl;
		cout<<"********************"<<endl;
		cout<<endl<<"Enter your option";
		cin>>ch;
		
			switch(ch)
			{
				case 1:write();break;
				case 2:read();break;
				case 3:SEARCH_RECORD();break;
				case 4:UPDATE_RECORD();break;
				case 5:DELETE_RECORD();break;	
				case 6:COPYABC();break;
				case 7:
					exit(0);
					break;	
			}
		}
}


