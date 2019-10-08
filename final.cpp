#include<conio.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<time.h>	
#include<dos.h>	
#include<iomanip>
#include<graphics.h>
#include"MMSystem.h"
using namespace std;
void gotoxy (int x, int y);
void date_times();
class date;
COORD coord = {0, 0};

class record
{
public:
char id[5],name[15],age[5],sex[5],contact[15],time[10],discription[100];
}rec[20],found[20];
int no;
char st_no[5],rt_name[20];
int aday,amonth,ayear,ahour,amin,asec;
char *date_time ();

void gotoxy (int x, int y)	//defining/initializing to predefined objects
{
    coord.X = x;
    coord.Y = y; // X and Y coordinates
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

class date
{ 
void date_times()
	{
		SYSTEMTIME t;		//pre defined in time.h header
 		GetLocalTime(&t);
		aday=t.wDay,amonth=t.wMonth,ayear=t.wYear,ahour=t.wHour,amin=t.wMinute,asec=t.wSecond;
		
	}
};
void frame()
{
	int i,j=79;
	for(i = 0;i<80,j>=0;i++,j--)
	{
		gotoxy(i,3);
		Sleep(10);
		cout<<"_";
		gotoxy(j,20);
		Sleep(10);
		cout<<"_";
	}
	gotoxy(56,2);
	char s[20];
	strcpy(s,date_time());
	cout<<s;		//every frame has date on the right top 
	
}
void frame_fix()	//instead of flow line fixing the frame
{
	int i,j=79;
	for(i = 0;i<80,j>=0;i++,j--)
	{
		gotoxy(i,3);
		cout<<"_";
		gotoxy(j,20);
		cout<<"_";
	}
	gotoxy(56,2);
	char s[20];
	strcpy(s,date_time());
	cout<<s;
}

char *date_time()
{
	time_t t;
	time(&t);
	char *loc=ctime(&t);
	return loc;	//returns local time and date
}
int owner_authen()
{
	char o_username[20],o_password[20];
	char o_user[20]="me1511",o_pass[20]="me1511";
	cout<<endl<<endl;
	cout.width(25);
	system("cls");
	cout<<"Enter Doctors User id and Password\n"<<"------------------------------------------------------------------------------------\n";
	cout<<endl<<"username: ";
	cin>>o_username;
	cout<<"password: ";
	cin>>o_password;
	cout<<"------------------------------------------------------------------------------------\n";
	if(strcmp(o_username, o_user)==0 && strcmp(o_password, o_pass)==0)
		return 1;
	else
		return 0;
}
void sortrecord()
{
int i,j;
record temp;
for(i=0;i<no-1;i++)
for(j=0;j<no-i-1;j++)
if(strcmp(rec[j].name,rec[j+1].name)>0)
{
temp=rec[j];
rec[j]=rec[j+1];
rec[j+1]=temp;
}
}
void indexfile()
{
fstream index ,index2 ,index3;
int i;
index .open("secindex.txt", ios :: out);
index2.open("record.txt", ios :: out);
index3.open("index.txt",ios::out);
for(i=0;i<no;i++)
{
 index3<<i<<"|"<<rec[i].id<<"\n";
 index<<rec[i].name<<"|"<<rec[i].id<<"|"<<i<<"\n";
 index2<<i<<"|"<<rec[i].name<<"|"<<rec[i].id<<"|"<<rec[i].age<<"|"<<rec[i].sex<<"|"<<rec[i].contact<<"|"<<rec[i].time<<"|"<<rec[i].discription<<"\n";
}
index.close();
index2.close();
index3.close();
}
void retrieve_record(char *index)
{
fstream file;
char id[5],name[15],age[5],sex[5],contact[15],time[10],discription[100],ind[5];
file.open("record.txt",ios::in);
for(int i=0;i<no;i++)
{
file.getline(ind,5,'|');
file.getline(name,15,'|');
file.getline(id,5,'|');
file.getline(age,5,'|');
file.getline(sex,5,'|');
file.getline(contact,15,'|');
file.getline(time,10,'|');
file.getline(discription,100,'\n');
if(strcmp(index,ind)==0)
{
cout<<"ID\tNAME\tAGE\tSEX\tCONTACT\tTIME\tDESCRIPTION\n";
cout<<id<<"\t"<<name<<"\t"<<age<<"\t"<<sex<<"\t"<<contact<<"\t"<<time<<"\t"<<discription<<"\n";
}
}
file.close();
}
void retrieve_details()
{
fstream file;
char id[5],name[15],age[5],sex[5],contact[15],time[10],discription[100],ind[5];
char chusn[20],index[20][20];
file.open("secindex.txt",ios::in);
int k=0;
int i = 0;
for(i=0;i<no;i++)
{
file.getline(name,15,'|');
file.getline(id,5,'|');
file.getline(ind,4,'\n');
if(strcmp(name,rt_name)==0)
{
strcpy(found[k].name,name);
strcpy(found[k].id,id);
strcpy(index[k],ind);
k++;
}
}
file.close();
if(k==1)
{
retrieve_record(index[0]);
return;
}
else
{
cout<<"choose the candidates id\n";
for(i=0;i<k;i++)
cout<<"ID:"<<found[i].id<<"\tNAME:"<<found[i].name<<endl;
}
cin>>chusn;
for(i=0;i<k;i++)
{
if(strcmp(chusn,found[i].id)==0)
{
retrieve_record(index[i]);
return;
}
}
cout<<"invalid entry\n";
return;
}

void delete_record(char *indx)
{
char id[5],name[15],age[5],sex[5],contact[15],time[10],discription[100],ind[5];
fstream file1,file2,file3;
char index[20][20];
file2.open("record.txt",ios::in);

int i = 0;
for(i=0;i<no;i++)
{
file2.getline(ind,4,'|');
file2.getline(name,15,'|');
file2.getline(id,5,'|');
file2.getline(age,5,'|');
file2.getline(sex,5,'|');
file2.getline(contact,15,'|');
file2.getline(time,10,'|');
file2.getline(discription,100,'\n');
strcpy(index[i],ind);
strcpy(rec[i].id,id);
strcpy(rec[i].name,name);
strcpy(rec[i].age,age);
strcpy(rec[i].sex,sex);
strcpy(rec[i].contact,contact);
strcpy(rec[i].time,time);
strcpy(rec[i].discription,discription);
}
int flag=-1;
for(i=0;i<no;i++)
{
if(strcmp(index[i],indx)==0)
flag=i;
}
if(flag==-1)
{
cout<<"error\n";
return;
}
if(flag==(no-1))
{
no--;
cout<<"record deleted\n";
return;
}
for(i=flag;i<no;i++)
{
rec[i]=rec[i+1];
}
no--;
cout<<"record deleted\n";
file2.close();
file1.open("secindex.txt",ios::in);
file2.open("record.txt",ios::in);
file3.open("index.txt",ios::in);
for(i=0;i<no;i++)
{
file3<<i<<"|"<<rec[i].id<<"\n";
file1<<rec[i].name<<"|"<<rec[i].id<<"|"<<i<<"\n";
file2<<i<<"|"<<rec[i].name<<"|"<<rec[i].id<<"|"<<rec[i].age<<"|"<<rec[i].sex<<"|"<<rec[i].contact<<"|"<<rec[i].time<<"|"<<rec[i].discription<<"\n";
}
file1.close();
file2.close();
file3.close();
}
void delete_index(char *nam)
{
fstream file;
char id[5],name[15],age[5],sex[5],contact[15],time[10],discription[100],ind[5];
char chusn[20],index[20][20];
int i,k=0;
file.open("secindex.txt",ios::in);
for(i=0;i<no;i++)
{
file.getline(name,15,'|');
file.getline(id,5,'|');
file.getline(ind,4,'\n');
if(strcmp(nam,name)==0)
{
strcpy(found[k].name,name);
strcpy(found[k].id,id);
strcpy(index[k],ind);
k++;
}
}
file.close();
if(k==1)
{
delete_record(index[0]);
return;
}
else
{
cout<<"\nchoose the candidates usn\n";
for(i=0;i<k;i++)
cout<<"ID:"<<found[i].id<<" NAME:"<<found[i].name<<endl;
}
cin>>chusn;
for(i=0;i<k;i++)
{
if(strcmp(chusn,found[i].id)==0)
{
delete_record(index[i]);
return;
}
}
cout<<"invalid entry\n";
return;
}
void retrieve_details1()
{
fstream file2;
char ind[5],id[5],name[15],age[5],sex[5],contact[15],time[10],discription[100];
file2.open("record.txt",ios::in);
for(int i=0;i<no;i++)
{
file2.getline(ind,5,'|');
file2.getline(id,5,'|');
file2.getline(name,15,'|');
file2.getline(age,5,'|');
file2.getline(sex,5,'|');
file2.getline(contact,15,'|');
file2.getline(time,10,'|');
file2.getline(discription,100,'\n');
if(strcmp(ind,st_no)==0)
{
cout<<"\n\t"<<"patient details :\n";
cout<<"ID\tNAME\tAGE\tSEX\tCONTACT\tTIME\tDESCRIPTION\n";
cout<<id<<"\t"<<name<<"\t"<<age<<"\t"<<sex<<"\t"<<contact<<"\t"<<time<<"\t"<<discription<<"\n";
}
}
file2.close();
}

int main()
{
fstream file1,file2,file3;
char rt_usn[20],st_name[20],st_usn[20];
char id[5],name[15],age[5],sex[5],contact[15],time[10],discription[100],ind[5];
int i,flag,flag1,choice;
int user;
system("cls");
system("COLOR 6F");

cout<<"------------------------------------------------------------------------------------\n";
gotoxy(33,1);
cout<<"1.Doctor\n";
gotoxy(33,4);
cout<<"2.Patient\n";
cout<<"------------------------------------------------------------------------------------\n";
gotoxy(33,10);
cout<<"Select User: "; 
cin>>user;
system("cls");
system("COLOR 2F");
//frame();
	switch(user)
	{
	case 1:int check;
                        check=owner_authen();
                        if(check == 1)
                        {
                        	system("cls");
                            system("COLOR 2F");
                            frame_fix();
                            cout<<"Welcome Doctor\n"<<"------------------------------------------------------------------------------------\n";
for(;;)
{
//gotoxy()
cout<<"\n CHOOSE AN OPTION\n";
cout<<" 1:ADD\n";
cout<<" 2:SEARCH\n";
cout<<" 3:DELETE\n";
cout<<" 4:DISPLAY\n";
cout<<" 5:EXIT\n";
cin>>choice;
switch(choice)
{

case 1:
system("cls");
system("COLOR 70");
frame_fix();
cout<<"\nenter the no of patients\n";
cin>>no;
for(i=0;i<no;i++)
{
cout<<"enter the name:";
cin>>rec[i].name;
cout<<"id:";
cin>>rec[i].id;
cout<<"age:";
cin>>rec[i].age;
cout<<"sex:";
cin>>rec[i].sex;
cout<<"contact:";
cin>>rec[i].contact;
cout<<"time:";
cin>>rec[i].time;
cout<<"discription:";
cin>>rec[i].discription;
}
sortrecord();
indexfile();
break;
case 2: 
system("cls");
system("COLOR 40");
frame();
int ch;
cout<<"\nSEARCH BY:";
cout<<" \n1:NAME";
cout<<"\n2:ID\n";
cin>>ch;
switch(ch)
{
case 1:	
system("cls");
system("COLOR 50");
frame_fix();
cout<<"\nenter the name of the record to be searched\n";
cin>>st_name;
file1.open("secindex.txt",ios::in);

if(!file1)
{
cout<<"file creation error\n";
exit(0);
}
flag1=0;
for(i=0;i<no;i++)
{
file1.getline(rt_name,20,'|');
file1.getline(st_usn,20,'|');
file1.getline(st_no,4,'\n');
if(strcmp(st_name,rt_name)==0)
{
retrieve_details();
flag1=1;
}
}
if(!flag1)
cout<<"record search failed \n";
file1.close();
break;
case 2:
system("cls");
system("COLOR 80");
frame_fix();
cout<<"\nenter the ID of the patient record to be searched\n";
cin>>st_usn;
file1.open("index.txt",ios::in);
if(!file1)
{
cout<<"error!\n";
exit(0);
}
flag1=0;
for(i=0;i<no;i++)
{
file1.getline(st_no,4,'|');
file1.getline(rt_usn,20,'\n');
if(strcmp(st_usn,rt_usn)==0)
{
retrieve_details1();
flag1=1;
}
}
if(!flag1)
{
cout<<"\nrecord search failed !!\n";
}
file1.close();
break;
}
break;

case 3:
system("cls");
system("COLOR 90");
frame_fix();
cout<<"\nenter the name of the record to be deleted\n";
cin>>st_name;
file1.open("secindex.txt",ios::in);
file3.open("index.txt",ios::in);
if(!file1||!file3)
{
cout<<"file creation error\n";
exit(0);
}
flag=0;
for(i=0;i<no;i++)
{
file1.getline(rt_name,20,'|');
file1.getline(st_usn,20,'|');
file1.getline(ind,4,'\n');

if((strcmp(st_name,rt_name)==0))
{
delete_index(rt_name);
flag=1;
break;
}
}
if(!flag)
cout<<"deletion failed \n";
file1.close();
file3.close();
break;
case 4: 
system("cls");
system("COLOR D0");
frame_fix();cout<<"\nNAME\tID\tAGE\tSEX\tCONTACT\tTIME\tDESCRIPTION\n";
for(i=0;i<no;i++)
{
cout<<rec[i].name<<"\t"<<rec[i].id<<"\t"<<rec[i].age<<"\t"<<rec[i].sex<<"\t"<<rec[i].contact<<"\t"<<rec[i].time<<"\t"<<rec[i].discription<<"\n";

}
break;
case 5: exit(0);
break;
default:cout<<"invalid choice\n";
exit(0);

//else
//cout<<endl<<"Invalid Username or Password!! Please try again...";
  }
}
		
	break;
	case 2: cout<<"Patient Record\n"<<"------------------------------------------------------------------------------------\n";
		while(1)
		{
			int ch;
		 cout<<"\nSEARCH BY:";
cout<<" \n1:NAME";
cout<<"\n2:ID\n";
cin>>ch;
switch(ch)
{
case 1:	
system("cls");
system("COLOR 50");
frame_fix();
cout<<"\nenter the name of the record to be searched\n";
cin>>st_name;
file1.open("secindex.txt",ios::in);

if(!file1)
{
cout<<"file creation error\n";
exit(0);
}
flag1=0;
for(i=0;i<no;i++)
{
file1.getline(rt_name,20,'|');
file1.getline(st_usn,20,'|');
file1.getline(st_no,4,'\n');
if(strcmp(st_name,rt_name)==0)
{
retrieve_details();
flag1=1;
}
}
if(!flag1)
cout<<"record search failed \n";
file1.close();
break;
case 2:
system("cls");
system("COLOR 80");
frame_fix();
cout<<"\nenter the ID of the patient record to be searched\n";
cin>>st_usn;
file1.open("index.txt",ios::in);
if(!file1)
{
cout<<"error!\n";
exit(0);
}
flag1=0;
for(i=0;i<no;i++)
{
file1.getline(st_no,4,'|');
file1.getline(rt_usn,20,'\n');
if(strcmp(st_usn,rt_usn)==0)
{
retrieve_details1();
flag1=1;
}
}
if(!flag1)
{
cout<<"\nrecord search failed !!\n";
}
file1.close();
break;
		}
	}

		break;
	default: exit(0);
break;
}
}
}

