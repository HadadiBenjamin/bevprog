#include "std_lib_facilities.h"

int main(){

double a=1, b=0, min=0, max=0;/*
cout<<"Please enter 1 values!\n";

while (cin>>a) {

  if (a<b) {
	 cout<< "the larger value is: " << b<< "\n";
	cout<< "the smaller value is: " << a<< "\n";}

  else {if (a==b) {
	cout<< "the numbers are equal: "<<a<<"\n";}

        else 
	    {cout<< "the larger value is: " << a<< "\n";
	    cout<< "the smaller value is: " << b<< "\n";}}
if (a!=b) {
 if ((a-b<0.001) && (a-b>-0.001)) {
	cout<< "the numbers are almost equal \n";}}
 

if (max<a) {max=a; cout<<"the largest so far \n";}
if (b==0) {min=max;}
if (a<min) {min=a; cout<<"the smallest so far \n";}




 b=a;*/


const double m_cm = 100,in_cm = 2.54,ft_in = 12;
bool logikai_tarolo = true;
double small,large,vegertek=0.0;
string megyseg;
vector<double> ertekek;
double T;

while(cin>>a>>megyseg){
  cout<<a<<megyseg<<"\n";
  if (megyseg == "m"){
    a = a;
  }else if (megyseg == "cm"){
    a = a/m_cm;
  }else if (megyseg == "in"){
    a = in_cm*a/m_cm;
  }else if (megyseg == "ft"){
    a = ft_in*in_cm*a/m_cm;
  }else {
    cout<<"Illegal unit!\n";
  }
  ertekek.push_back(a);
  vegertek = vegertek + a;
  if(logikai_tarolo){
    small = a;
    large = a;
    logikai_tarolo= false;
  }else if (a<small) {
    cout<<"The smallest so far\n";
    small = a;
  }else if (a>large){
    cout<<"The large so far\n";
    large = a;
  }
}
cout<<"\n";
cout<<"Largest: "<<large<<"\n";
cout<<"Smallest: "<<small<<"\n";
cout<<"Sum of values: "<<vegertek<<"\n";

  /*for(int i=0;i<ertekek.size();i++){
    for (int j=0;j<ertekek.size()-1;j++){
      if (ertekek[j]>ertekek[j+1]){
        T = ertekek[j];
        ertekek[j] = ertekek[j+1];
        ertekek[j+1] = T;
 
      }
    }
  }*/
sort(ertekek);
cout<<"Ertekek: ";
 for (int i = 0;i<ertekek.size();i++){
   cout<<ertekek[i]<<" ";

 }
cout<<"\n";



	return 0;}

