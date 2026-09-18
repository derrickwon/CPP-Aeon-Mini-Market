#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include<cctype>
using namespace std;

int c=0,loginpass=0;
float tax_price,total=0;

//structure
struct items
{
	string name;
	int stock;
	float price;
};
struct User {
	char userID[50];
	char password[50];
};
//function prototype
bool ValidUserID(const char* userID);
bool ValidPassword(const char* password);
bool userExists(const char* userID);
void registerUser();
bool loginUser();
void saveUser(const User & user);
int login();
float calculate(int,float);
void Output(int);
void payment();

main()
{
	loginpass=login();
	if(loginpass==1)
	{
		
		
		//structure table
		items canned[4];
		items vegetable[4];
		items fruits[4];
		
		//read file
		ifstream read;
		read.open("items.txt");
		if(read.fail())
			cout<<"File cannot be located!\n";
		else
		{
			while(c<4)
			{
				getline(read,canned[c].name);
				read>>canned[c].stock;
				read>>canned[c].price;
				read.ignore();
				getline(read,vegetable[c].name);
				read>>vegetable[c].stock;
				read>>vegetable[c].price;
				read.ignore();
				getline(read,fruits[c].name);
				read>>fruits[c].stock;
				read>>fruits[c].price;
				read.ignore();
				c++;
			}
	
		}
		//write added item to file
		ofstream write;
		write.open("cart.txt");
		
		//declaration
		int option=1,select_option=0,quantity=0	,counter=0,counter_for_list=0;
		float tax,subtotal;
		
		//user interface start
		cout<<"-------------------------------------------------\n\n";
		cout<<"\tWelcome To AEON Mini Market\n";
		
		
		while(option!=0)
		{
			cout<<"\n-------------------------------------------------";
			cout<<"\nWhat would you like to buy?\n";
			cout<<"\n1 - canned food\n\n2 - vegetable\n\n3 - fruits\n\n0 - checkout\n\n(Enter other any number to exit)";
			cout<<"\n-------------------------------------------------\n";
			cout<<"\noption: ";
			cin>>option;
			cout<<"\n-------------------------------------------------\n";
	
			//user input
			switch(option)
			
			{	
				case 0://checkout
					{
						if(counter>0)
						{
							Output(counter);
							payment();
							break;
						}
						else
						{
							cout<<"\nPlease add item to cart before checkout!!!\n\n";
							option=1;
							break;
						}
						
	
					}
				case 1://canned food
					counter_for_list=0;//to reset avaliable option in list
					cout<<"-------------------------------------------------\n";
					cout<<"No. item\t\tprice\t\tstock\n";
					cout<<"-------------------------------------------------\n";
					for(int i=0;i<4;i++)
					{
						cout<<endl<<i+1<<" - "<<canned[i].name<<"  RM"<<canned[i].price<<"\t\t"<<canned[i].stock<<endl;
						counter_for_list+=1;//to set avaliable option based on loop
					}
					cout<<"\n0 - back\n";
					cout<<"-------------------------------------------------\n";
					do{
						cout<<"\nEnter (No.) item you would like to purchase: ";
						cin>>select_option;
						
					}while(select_option<0||select_option>counter_for_list);
					if (select_option==0)
					{
						break;
					}
					do	{
							cout<<"\nEnter quantity you would like to purchase: ";
							cin>>quantity;
							if(quantity>canned[select_option-1].stock)
							{
								cout<<"\nUnfortunately, we have only "<<canned[select_option-1].stock<<" stock left.\n";
							}
							else if(quantity>=1&&quantity<=canned[select_option-1].stock)
							{
								cout<<"\nItem added to cart sucessfully!\n";
								canned[select_option-1].stock -= quantity;
								counter+=1;
								//calculation
								subtotal = calculate(quantity,canned[select_option-1].price);
								//writing into receipt
								write<<canned[select_option-1].name<<endl<<quantity<<endl<<subtotal<<endl; 
								break;	
							}
							else if(quantity==0)
							{
								break;
							}
							else
							{
								cout<<"\nInvalid input.\n";
							}
						}while(quantity <0 || quantity>canned[select_option-1].stock);
				break;
				
				case 2://vegetable
					counter_for_list=0;//to reset avaliable option in list
					cout<<"-------------------------------------------------\n";
					cout<<"No. item\t\tprice\t\tstock\n";
					cout<<"-------------------------------------------------\n";
					for(int i=0;i<4;i++)
					{
						cout<<endl<<i+1<<" - "<<vegetable[i].name<<"  RM"<<vegetable[i].price<<"\t\t"<<vegetable[i].stock<<endl;
						counter_for_list+=1;
					}
					cout<<"\n0 - back\n";
					cout<<"-------------------------------------------------\n";
					do{
						cout<<"\nEnter (No.) item you would like to purchase: ";
						cin>>select_option;
						
					}while(select_option<0||select_option>counter_for_list);
					if (select_option==0)
					{
						break;
					}
					do	{
							cout<<"\nEnter quantity you would like to purchase: ";
							cin>>quantity;
							if(quantity>vegetable[select_option-1].stock)
							{
								cout<<"\nUnfortunately, we have only "<<vegetable[select_option-1].stock<<" stock left.\n";
							}
							else if(quantity>=1&&quantity<=vegetable[select_option-1].stock)
							{
								cout<<"\nItem added to cart sucessfully!\n";
								vegetable[select_option-1].stock -= quantity;
								counter+=1;
								//calculation
								subtotal = calculate(quantity,vegetable[select_option-1].price);
								write<<vegetable[select_option-1].name<<endl<<quantity<<endl<<subtotal<<endl; 
								break;
							}
							else if(quantity==0)
							{
								break;
							}
							else
							{
								cout<<"\nInvalid input.\n";
							}
						}while(quantity <0 || quantity>vegetable[select_option-1].stock);
				break;
		
				case 3://fruits
					counter_for_list=0;//to reset avaliable option in list
					cout<<"-------------------------------------------------\n";
					cout<<"No. item\t\tprice\t\tstock\n";
					cout<<"-------------------------------------------------\n";
					for(int i=0;i<4;i++)
					{
						cout<<endl<<i+1<<" - "<<fruits[i].name<<"  RM"<<fruits[i].price<<"\t\t"<<fruits[i].stock<<endl;
						counter_for_list+=1;
					}
					cout<<"\n0 - back\n";
					cout<<"-------------------------------------------------\n";
					do{
						cout<<"\nEnter (No.) item you would like to purchase: ";
						cin>>select_option;
						
					}while(select_option<0||select_option>counter_for_list);
					if (select_option==0)
					{
						break;
					}
					do	{
							cout<<"\nEnter quantity you would like to purchase: ";
							cin>>quantity;
							if(quantity>fruits[select_option-1].stock)
							{
								cout<<"\nUnfortunately, we have only "<<fruits[select_option-1].stock<<" stock left.\n";
							}
							else if(quantity>=1&&quantity<=fruits[select_option-1].stock)
							{
								cout<<"\nItem added to cart sucessfully!\n";
								fruits[select_option-1].stock -= quantity;
								counter+=1;
								//calculation
								subtotal = calculate(quantity,fruits[select_option-1].price);
								write<<fruits[select_option-1].name<<endl<<quantity<<endl<<subtotal<<endl; 
								break;	
							}
							else if(quantity==0)
							{
								break;
							}
							else
							{
								cout<<"\nInvalid input.\n";
							}
						}while(quantity <0 || quantity>vegetable[select_option-1].stock);
				break;
				
				default://exit
						cout<<"have a nice day!";
						cout<<"\n-------------------------------------------------\n";
						return 0;
	
	
		
			}
			
		}
		read.close();
		write.close();
	
	}
	else
	{
		return 0;
	}
}//main program end

//login function definition
int login()
{
	int log;
	
	do{
		cout<<"-------------------------------------------------\n\n";
		cout<<"\tWelcome To AEON Mini Market\n";
		cout<<"\n-------------------------------------------------";
		cout<<"\n--==== User Authentication ====--\n";
		cout<<"1. Register\n";
		cout<<"2. Login\n";
		cout << "3. Exit\n";
		cout<<" Choose option (1-3): ";
		cin>>log;
		
		switch (log)
		{
			case 1:
				registerUser();
				break;
				
			case 2:
				if(loginUser())
				{
					cout<<"Login successful!\n";
					return 1;
				}

				else{
					cout<<"Invalid credentials!\n";
				}
				break;
			
			case 3:
				cout<<"-------- Thank You!! --------\n";
				break;
				
			default:
				cout<<"Invalid Option Chosen! ! ! Please Try Again.\n";
				
		}
		
	}while (log != 3);
	
	return 0;
}
bool ValidUserID(const char* userID){
	if(strlen(userID) < 5) return false;
	
	int i;
	for(i=0; userID[i]; i++){
		if(!isalnum(userID[i])) return false;
	}
	return true;
}

bool ValidPassword(const char* password){
	if(strlen(password) < 8) return false;
	
	bool hasUpper =false, hasLower =false, hasDigit =false;
	int i;
	for(i=0; password[i]; i++){
		if (isupper(password[i])) hasUpper = true;
		if (islower(password[i])) hasLower = true;
		if (isdigit(password[i])) hasDigit = true;
	}
	return hasUpper && hasLower && hasDigit;
}

bool userExists(const char* userID){
	User user;
	ifstream file("users.data", ios::binary);
	
	while(file.read((char*)&user, sizeof(User))){
		if(strcmp(user.userID, userID) == 0){
			file.close();
			return true;
		}
	}
	file.close();
	return false;
}


void saveUser(const User& user){
 	ofstream file("users.data", ios::binary | ios::app);
 	file.write((char*)&user, sizeof(User));
 	file.close();
}
 

void registerUser(){
	User newUser;
	
	cout<<"\n**** User Registration ****\n";
	
	do{
		cout<<"Enter User ID: ";
		cin>>newUser.userID;
		
		if (!ValidUserID(newUser.userID)){
			cout<<"Invalid User ID! Use minimum 5 alphanumeric characters!\n";
			continue;
		}
		
		if(userExists(newUser.userID)){
			cout<<"This User already exists in this system!\n";
			continue;
		}
		break;
	}while(true);
	
	do{
		cout<<"Enter Password (must have Uppercase, Lowercase, and Digit): ";
		cin>>newUser.password;
		
		if(!ValidPassword(newUser.password)){
			cout<<"Invalid Password!! Password must contain at least 8 characters, including uppercase, lowercase, and digit.\n";
			continue;
		}
		break;
	}while(true);
	
	saveUser(newUser);
	cout<<"Registration is successful!!\n";
}

bool loginUser(){
	User inputUser;
	User storedUser;
	bool found = false;
	
	
	cout<<"\n*** User Login ***\n";
	cout<<"Enter Your User ID: ";
	cin>>inputUser.userID;
	cout<<"Enter Your Password: ";
	cin>>inputUser.password;
	
	ifstream file("users.data", ios::binary);
	
	while(file.read((char*)&storedUser, sizeof(User))){
		if(strcmp(storedUser.userID, inputUser.userID) == 0 &&
		strcmp(storedUser.password, inputUser.password) == 0){
			found = true;
			break;
		}
	}
	
	file.close();
	return found;
}
//calculate function definition
float calculate(int quan,float price)
{
	float tax,subtotal;
	subtotal=quan*price;
	tax = subtotal * 0.06;
	tax_price +=tax;
	total +=subtotal;
	return subtotal;
}

//output function definition
void Output(int count)
{

			//output receipt
			string item_name[100];
			float price[100];
			int cart_quantity[100], i , c=0;
							
			//declare file pointer for reading
			ifstream cart;
			cart.open("cart.txt");
			//to check if file exist in folder
			if(cart.fail())
				cout<<"File cannot be located!";
			else
			{
				while(!cart.eof())
				{
					getline(cart,item_name[c]);
					cart>>cart_quantity[c];
					cart>>price[c];
					cart.ignore();
					c++;
				}
			}
			cout<<"\nItem\t\t\tQuantity\tPrice\n";
			cout<<"-------------------------------------------------\n";
			for(i=0;i<c-1;i++)//c without -1 will display additional 1 random value at the end.
			{
				cout<<fixed<<setprecision(2);
				cout<<endl<<item_name[i]<<"\t";
				cout<<"x"<<cart_quantity[i]<<"\t";
				cout<<"\tRM"<<price[i]<<endl;
			}
			cout<<"-------------------------------------------------\n";
			cout<<"Sub-total"<<"\t\t\t\tRM"<<total<<endl;
			cout<<"6% Tax"<<"\t\t\t\t\tRM"<<tax_price<<endl;
			cout<<"Grand Total"<<"\t\t\t\tRM"<<total+tax_price<<endl;
			cout<<"-------------------------------------------------\n";
			cart.close();
}

//payment function definition
void payment()
{
	int method;
	cout<<"How would you like to pay?(1 - Cash / 2 - Card / 0 - cancel)\n";
	cout<<"Pay option: ";
	cin>>method;
	switch(method)
	{
		case 1:
			{
				cout<<"\nPayment accepted!";
				break;
			}
		case 2:
			{
				cout<<"\nPayment accepted!";
				break;
			}
		default:
			{
				break;
			}
	}
	cout<<"\nThank you!";
	
}
