#include "std_lib_facilities.h"


int main(){


cout<<"Please enter tour first name:\n";

string first_name;

cin >> first_name;

cout<<"Dear, "<<first_name<<"\n";

cout<<"How are you? I am fine. I miss you."<<"\n";

string friend_name;

cin >> friend_name;

cout<<"Have you seen "<<friend_name<<" lately?"<<"\n";

char friend_sex;

cin>>friend_sex;

if (friend_sex=='m') {cout<<"If you see "<<friend_name<<" please ask him to call me.\n";} else if(friend_sex=='f'){cout<<"If you see "<<friend_name<<" please ask her to call me.\n";}

int age=0;

cin>>age;

if ((age>0) && (age<110)) {cout<<"I hear you just had a birthday and you are "<<age<<" years old.\n";} else {simple_error("You're kidding!");}

if (age<12) {cout<<"Next year yoy will be age+1.\n";}

if (age==17) {cout<<"Next year yoy will be able to vote.\n";}

if (age>70) {cout<<"I hope you your enjoying retirement.\n";}

cout<<"Yours sincerely,\n\n\n";
	return 0;
}
