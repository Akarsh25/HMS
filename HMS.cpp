//C++ program to implement working of hospital management system
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include <ctime>
#define ROOMS 100 //Maximum number of wards available=100
using namespace std;
int count=0,j;
int ward[ROOMS];
int month[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int leap(int y,int m)
{ 
  if(m==2&&(y%4==0&&y%100!=0||y%400==0))
     return 1;
  else 
     return 0;
}
class date
{
  public: int year;
          int month;
          int day;
 public:
          void curdate();
       
}; 

/*curdate()-Member function of date class.
  Retrieves and stores current date.*/
void date::curdate()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  year= 1900 + ltm->tm_year;
  month= 1 + ltm->tm_mon;
  day=ltm->tm_mday;
}

/*patient class which contains details of patients like name,age etc.
  Common to both in-patients and out-patients.*/
class patient 
{
   protected: char firstname[30];
              char lastname[30];
               date dob,doa;
              
              int age;
              string address;
              string bloodgrp;
              char phno[10];
              char sex;
              int treat;
              string doc;
              int pid;          
  public:     string status;
              friend ostream &operator <<(ostream &stream,patient p);
              friend istream &operator >>(istream &stream,patient &p);
              int calage(date);
             
};

istream &operator <<(istream &stream,patient &p)
{ 
   cout<<"Enter patient name: ";
   stream>>p.firstname>>" ">>p.lastname;
   //pid=count++;
   //cout<<"Patient id is: "<<"HMS"<<pid<<endl;
   int a;
   /*label1: 
   cout<<"\nEnter valid date of birth in ddmmyyyy format: ";
   cin>>p->d1.d>>p->d1.m>>p->d1.y;
   if(p->d1.d<0||p->d1.d>(month[p->d1.m]+leap(p->d1.y,p->d1.m))||p->d1.m<0||p->d1.m>12||p->d1.y<1910||p->d1.y>2014)
     goto label1;
   stream>>p->d1.d>>p->d1.m>>p->d1.y;
   date obj2;      //obj2 is an object of date class
   obj2.curdate(); //invokes curdate() & obj2 now contains the current system date
   p->doa.d=obj2.day;
   p->doa.m=obj2.month;
   p->doa.y=obj2.year;
   stream>>p->doa.d>>p->doa.m>>p->doa.y;*/
   label2:
   cout<<"\nEnter gender[1.Male\t2.Female\t3.Other]: ";
   cin>>a;
   if(a==1)
   stream>>p.sex='M';
   else if(a==2)
   stream>>p.sex='F';
   else if(a==3)
   stream>>p.sex='O';
   else
   goto label2; 
   label3:
   cout<<"\nEnter patient blood group: 1.A+\t2.A-\t3.B+\t4.B-\t5.O+\t6.O-\t7.AB+\t8.AB-:\n ";
   cin>>a;
   switch(a)
  {
   case 1: p.bloodgrp="A+";break;
   case 2: p.bloodgrp="A-";break;
   case 3: p.bloodgrp="B+";break;
   case 4: p.bloodgrp="B-";break;
   case 5: p.bloodgrp="O+";break;
   case 6: p.bloodgrp="O-";break;
   case 7: p.bloodgrp="AB+";break;
   case 8: p.bloodgrp="AB-";break;
   default: {cout<<"Enter valid option\n";
            goto label2;
            break;}
   }
    stream>>p.bloodgrp;
   cout<<"\nEnter patient phone no.: ";
   stream>>p.phno;
   cin.ignore();
   cout<<"\nEnter patient address: ";
   getline(cin,address);
   stream>>p.address;
   cout<<"\nEnter name of doctor assigned: ";
   getline(cin,doc);
   stream>>p.doc;
   return stream;
}

/*showdata()-Member function of patient class.
  Displays details of all patients stored in patient.txt*/
 ostream &operator <<(ostream &stream,patient p)
{
  stream<<"\nPatient Name\t: "<<firstname<<" "<<lastname;
  stream<<"\nPatient I.D\t: "<<pid;
  stream<<"\nPatient Age\t: "<<age;
  stream<<"\nPatient Gender\t: "<<sex;
  stream<<"\nBlood Group\t: "<<bloodgrp;
  stream<<"\nPatient Phone\t: "<<phno;
  stream<<"\nPatient Address\t: "<<address;
  stream<<"\nDoctor Assigned\t: "<<doc;
  stream<<"\n\n";
  return stream;
}


/*calage()-Member function of patient class.
  Calculates and returns current age of patient in years
int patient::calage(date today)
{
 age=((today.year)-(d1.y));
 cout<<"Age in years:"<<age;  
 return age;
}
*/
/*inpatient class contains details exclusive only to in-patients,
  like ward number,date of admission etc*/
class inpatient:protected patient
{
                int wardno;
               
     public: 
                int wardcheck();
		void getinfo1();
		
};

/*getinfo1()-member function of inpatient class.
  Accepts details of In-patients such as date of admission
  and assigns an available ward to the patient.*/
void inpatient::getinfo1()
{
   wardno=wardcheck();  
   if(wardno!=-1)		
     cout<<"Ward assigned is: "<<wardno;
   else
  { 
   cout<<"Sorry! all wards are full\n";
   exit(0);
   }
} 

/*wardcheck()-member function of inpatient class.
  This function checks for the next available ward number and returns
  the number to getinfo1().*/
int inpatient::wardcheck()
{
int i;
for(i=0;i<ROOMS;i++)
{
if(ward[i]==0)
{
ward[i]=1;
return (i+1);
}
}
return -1;
}


int main()
{
 for(j=0;j<ROOMS;j++)
   ward[j]=0;
 int choice;
 int status;
 cout<<"*****HOSPITAL MANAGEMENT SYSTEM*****\n\n"<<endl;
 cout<<"MENU:\n1.Enter patient information\n"<<
               "2.Display patient information\n"<<
               "3.Edit patient information\n"<<
               "4.Discharge & Invoice details\n"<<endl;
 patient obj; //obj is an object of patient class
 inpatient obj1; //obj1 is an object of inpatient class
 cout<<"Enter choice:";
 cin>>choice;
 switch(choice)
{
  case 1: {
           label4:   
           cout<<"Enter choice: 1.Inpatient or 2.Outpatient\n";
           cin>>status;
           fstream f;
           f.open("patient",ios::in|ios::out|ios::app);
           if(status==1)
          { 
             cin>>obj1;
	     f<<obj1;
           }
           else if(status==2)
          {   
		cin>>obj;
		f<<obj;
	  }
           else 
               {goto label4;}
           break;
          }
  case 2:{  
          fstream f;
          f.open("patient",ios::in|ios::out|ios::app); 
          f.seekg(0,ios::beg);
          char c;
          while(f.get(c))
         {
          cout<<c;
         }
		f.clear();
          break;
         }
case 3:   date obj2;
          obj2.curdate();
 }
}
