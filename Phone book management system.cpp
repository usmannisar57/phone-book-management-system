#include<iostream>
#include<bits/stdc++.h>
//#include<iomanip.h>
#include<conio.h>
#include<windows.h>
#include<fstream>
#include<vector>
#include<dos.h>
using namespace std;
fstream f;
COORD coord= {0,0};
void gotoxy(int x,int y)
{
	coord.X=x;
	coord.Y=y;
	SetConsoleCursorPosition (GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
class node{
	public:
		string number;
		string name;
		string email;
		node* right;
		node* left;
		node()
		{
			this->name=name;
			this->email=email;
			this->number=number;
			this->left=NULL;
			this->right=NULL;
		}
			node(string number,string name,string email)
		{
			this->name=name;
			this->email=email;
			this->number=number;
			this->left=NULL;
			this->right=NULL;
		}
};
class bst{
	public:
		node* root;
		bst()
		{
			this->root=NULL;
		}
		node* insert(node* &root,string number,string name,string email)
		{
		
			
			if(root == NULL)
			{
				root=new node(number,name,email);
				return root;
			}
			if(name>root->name)
			{
				root->right=insert(root->right,number,name,email);
			}
			else
			{
				root->left=insert(root->left,number,name,email);
			}
		return root;	
		}
		void input(node* &root)
		{
			string number;
			string name;
			string email;
			cout<<"enter name"<<endl;
			getline(cin,name);
			fflush(stdin);
		    cout<<"enter number"<<endl;
			getline(cin,number);
			fflush(stdin);
			cout<<"enter email"<<endl;
			getline(cin,email);
         	fflush(stdin);
			f.open("phonebook.txt",ios::app);
			f<<name<<endl;
			f<<number<<endl;
			f<<email<<endl;
			f.close();
			insert(root,number,name,email);
		}
		void inorder(node* &root)//   LNR
	{
	    fstream a;
	    a.open("phonebook",ios::app);
		int i;
		if(root==NULL)
		{
			return;
		}
		
		inorder(root->left);
		cout<<root->number<<" "<<setw(12)<<root->name<<" "<<setw(12)<<root->email<<" "<<endl;
		inorder(root->right); 
	}
void search_in_file(string x){
	f.open("phonebook.txt",ios::in);
	string l;
//	int count=0;
	while(!f.eof()){
		getline(f,l);
		if(x==l){
			cout<<"\nname "<<l<<endl;
			getline(f,l);
			cout<<"\nemail "<<l<<endl;
			getline(f,l);
			cout<<"\nnumber "<<l<<endl;
		//	continue;
//			break;
		}	
	}
	f.close();
//	cout<<"data not present "<<endl;
}
node* searchbst(node* &root,string x)
{
	if(root==NULL)
	{
		return NULL;
	}
	if(root->name==x)
	{
		return root;
	}
	if(root->name>x)
	{
		return searchbst(root->left,x);
	}
	else
	{
		return searchbst(root->right,x);
	}
}
node* searchloop(node* &root,string x)
{
	node* temp=root;
	while(temp!=NULL)
	{
		if(temp->name==x)
		{
			cout<<"NAME: "<<temp->name<<endl;
			cout<<"NUMBER: "<<temp->number<<endl;
			cout<<"EMAIL"<<temp->email<<endl;
			return root;
		}
		if(temp->name>x)
		{
			temp=temp->left;
		}
		else{
			temp=temp->right;
		}
	}
	cout<<"not found";
	return NULL;
}
node* minimum(node* &root)
{
	node* temp=root;
	while(temp->left!=NULL)
	{
		temp=temp->left;
	}
	return temp;
}
node* deletebst(node* &root,string val)
{
	if(root==NULL)
	{
		return root;
	}
	if(root->name==val)
	{
		//0 child
		if(root->left==NULL&&root->right==NULL)
		{
			delete root;
			return NULL;
		}
		//1 child
		//left child
		if(root->left!=NULL&&root->right==NULL)
		{
			node* temp=root->left;
			delete root;
			return temp;
		}
		//right child
		if(root->left==NULL&&root->right!=NULL)
		{
			node* temp=root->right;
			delete root;
			return temp;
	    }
		//2 child
		if(root->left!=NULL&&root->right!=NULL)
		{
			string min;
			min=minimum(root->right)->name;
			root->name=min;
			root->right=deletebst(root->right,min);
			return root;
		}
	}
	if(root->name>val)
	{
		root->left=deletebst(root->left,val);
		return root;
	}
    else
	{
		root->right=deletebst(root->right,val);
		return root;
	}
}
void delete_in_file(){

	int line_number;
		
	cout<<"LINE: ";
	cin>>line_number;
	
	f.open("phonebook.txt");
	if(f.fail()){
		cout<<"error";
	}
	vector<string> lines;
	string line;
	while(getline(f,line))
		lines.push_back(line);
	f.close();
	
	if(line_number> lines.size()){
		cout<<"line "<<line_number;
		cout<<"not in the file "<<endl;
		cout<<"file has "<<lines.size();
		cout<<"lines "<<endl;
	}
	ofstream wf;
	wf.open("phonebook.txt");
	if(wf.fail()){
		cout<<"error opening file "<<endl;
	}
	line_number--;
	for(int i=0;i<lines.size();i++){
		if(i != line_number){
			wf<<lines[i]<<endl;
		}
	}
	wf.close();
}
void print_via_file(){
	int i=1;
	f.open("phonebook.txt");
	string line;
	while(!f.eof()){
		getline(f,line);
		if(line=="")
		{
			break;
		}
		
		cout<<"<"<<i<<"> NAME: "<<line<<endl;
		i++;
		getline(f,line);
		cout<<"<"<<i<<"> NUMBER: "<<line<<endl;
		i++;
		getline(f,line);
		cout<<"<"<<i<<"> EMAIL: "<<line<<endl;
		i++;

	}

	f.close();
}
};

void menu(bst b)
{
	char a;
	int x,y;
	char arr1[]= "PHONE BOOK";
	char arr2[]= "> Press A to add data";
	char arr3[]= "> Press B to delete currently added data";
	char arr4[]= "> Press C to search currently added  data";
	char arr5[]= "> Press D to print currently added data";
	char arr8[]= "> Press E to delete data from file";
	char arr9[]= "> Press F to search data from file";
	char arr10[]="> Press G to print all data from file";

	char arr6[]="> Press H to exit";
	
	char arr7[]="**********************************";
 // system("cls"); 
  system("COLOR B");

	
  gotoxy(60,1);
  for(x=0; arr7[x]!=0; x++) 
		   { cout<<arr7[x];
		    for(y=0; y<=9999999; y++) { } 
			}
 gotoxy(72, 2);
      for(x=0; arr1[x]!=0; x++) 
		   { cout<<arr1[x];
		    for(y=0; y<=9999999; y++) { } 
			}
  gotoxy(60, 3);
  for(x=0; arr7[x]!=0; x++) 
		   { cout<<arr7[x];
		    for(y=0; y<=9999999; y++) { } 
			}
			
   gotoxy(60, 14);
  
  for(x=0; arr2[x]!=0; x++) 
		   { cout<<arr2[x];
		    for(y=0; y<=9999999; y++) 
			{ } 
			}			
gotoxy(60, 15);
 for(x=0; arr3[x]!=0; x++) 
		   { cout<<arr3[x];
		    for(y=0; y<=9999999; y++) 
			{ } 
			}
gotoxy(60, 16);
 for(x=0; arr4[x]!=0; x++) 
		   { cout<<arr4[x];
		    for(y=0; y<=9999999; y++)
			 { } 
			}
gotoxy(60, 17);
 for(x=0; arr5[x]!=0; x++) 
		   { cout<<arr5[x];
		    for(y=0; y<=9999999; y++)
			 { } 
			}
gotoxy(60, 18);
 for(x=0; arr8[x]!=0; x++) 
		   { cout<<arr8[x];
		    for(y=0; y<=9999999; y++)
			 { } 
			}
gotoxy(60, 19);
 for(x=0; arr9[x]!=0; x++) 
		   { cout<<arr9[x];
		    for(y=0; y<=9999999; y++)
			 { } 
			}
gotoxy(60, 20);
 for(x=0; arr10[x]!=0; x++) 
		   { cout<<arr10[x];
		    for(y=0; y<=9999999; y++)
			 { } 
			}
gotoxy(60, 21);
 for(x=0; arr6[x]!=0; x++) 
		   { cout<<arr6[x];
		    for(y=0; y<=9999999; y++)
			 { } 
			}
//	gotoxy(60, 18);
	cout<<endl;
	cin>>a;
	fflush(stdin);
	system("CLS");
	string val;
   while(a!='h'&&a!='H')
	{
    
	
  switch(a)
  {
  
    case 'a':
    {
  	b.input(b.root);

	 system("CLS")	;
  	break;
	}
    case 'A':
    {
  	b.input(b.root);
	system("CLS")	;	
  	break;
	}
 	case 'b':
	{
	cout<<endl<<"Enter name that you want delete"<<endl;
    getline(cin,val);
    fflush(stdin);
	b.deletebst(b.root,val);	
//	 	system("CLS")	;
		 
	break;
	}
 	case 'B':
	{
	cout<<endl<<"Enter name that you want delete"<<endl;
	getline(cin,val);
    fflush(stdin);
	b.deletebst(b.root,val);
//	system("CLS");
		 	
	break;
	}
	case 'c':
	{
	cout<<endl<<"Enter name that you are searching for"<<endl;
	getline(cin,val);
    fflush(stdin);
	b.searchloop(b.root,val);
	sleep(3);
	system("CLS");
		 
	break;	
	}
	case 'C':
	{
	cout<<endl<<"Enter name that you are searching for"<<endl;
	getline(cin,val);
    fflush(stdin);
	b.searchloop(b.root,val);
	system("CLS");
	sleep(3);		 
	break;	
	}
	case 'd':
	{
	    cout<<endl<<"NUMBER"<<" "<<setw(12)<<"NAME"<<" "<<setw(12)<<"EMAIL"<<endl;
       	b.inorder(b.root);	
       	sleep(5);
       	 	system("CLS")	;
		 
		 break;	
	}
	case 'D':
	{
	    cout<<endl<<"NUMBER"<<" "<<setw(12)<<"NAME"<<" "<<setw(12)<<"EMAIL"<<endl;
       	b.inorder(b.root);	
       	sleep(5);
       	system("CLS")	;
		 break;	
	}
	case 'e':
	{
	b.print_via_file();
	b.delete_in_file();	
	 	system("CLS")	;
		 
	break;
	}
 	case 'E':
	{
	b.print_via_file();
	b.delete_in_file();
	system("CLS");
		 	
	break;
	}
		case 'f':
	{
	cout<<endl<<"Enter name that you are searching for"<<endl;
	getline(cin,val);
    fflush(stdin);
	b.search_in_file(val);
	sleep(5);
	system("CLS");
		 
	break;	
	}
	case 'F':
	{
	cout<<endl<<"Enter name that you are searching for"<<endl;
	getline(cin,val);
    fflush(stdin);
	b.search_in_file(val);
	sleep(5);		 
	system("CLS");
	break;	
	}
		case 'g':
	{
	
         b.print_via_file();
//         sleep(5);
 system("PAUSE");
       	 	system("CLS")	;
		 
		 break;	
	}
	case 'G':
	{
          b.print_via_file();	
//          sleep(5);
        system("PAUSE");
       	system("CLS")	;
		 break;	
	}
	default:
	{
		cout<<"Enter valid option";
		 	system("CLS")	;
		 
		break;
	}
//	system("CLS");
}
     gotoxy(60, 1);
     cout<<"**********************************";
     gotoxy(72, 2);	
	 cout<<"PHONE BOOK"	;
     gotoxy(60, 3);
	 cout<<"**********************************";	
     gotoxy(60, 14);	
    cout<< "> Press A if to add data";
     gotoxy(60, 15);
	cout<< "> Press B to delete currently added data";
	 gotoxy(60, 16);
	cout<<"> Press C  to search currently added data";
	 gotoxy(60, 17);
	cout<<"> Press D to print currently added data";
	 gotoxy(60, 18);
	cout<<"> Press E to delete data from file"<<endl;
	 gotoxy(60, 19);
	cout<<"> Press F  to search data from file"<<endl;
	 gotoxy(60, 20);
	cout<<"> Press G to print all data from file"<<endl;
	 gotoxy(60, 21);
	cout<<"> Press H to exit"<<endl;
	cout<<endl;
	cin>>a;
	system("CLS");
	fflush(stdin);
}
		
}

void login(bst b)
{	
//
	system("COLOR B");
	gotoxy(60,16);
	cout<<"Enter Password: "; //password set to 110
	string password;
	cin>>password;
	system("CLS");
	if(password=="110")
	{
		
		menu(b);
	//	fflush;
	}
	else
	{
		int count=3;
		while(count>0&&password!="110")
		{
			gotoxy(60,17);
			cout<<"Wrong Password!";
			gotoxy(60,18);
			cout<<"You Trying to Break In?";
			gotoxy(60,19);
			cout<<"You Get "<< count<<" More Tries:";
			count--;
		    cin>>password;
		    system("CLS");
			if(password=="110")
			{
				menu(b);
			}
			else
			{
			gotoxy(60,17);
			cout<<"Wrong Password!";
			gotoxy(60,18);
			cout<<"You Trying to Break In?";
			gotoxy(60,19);
			cout<<"You Get "<< count<<" More Tries:";
		    cin>>password;
			count--;
		    system("CLS");
			}
		}
	}
}	


int main()
{
	bst b;
	login(b);
	//password is 110

}
