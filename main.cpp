/*
    Mouad Oulouali - LargeInt 331H Final Project
*/

#include "LargeInt.h"
#include <iostream>
using namespace std;

int main() 
{
  LargeInt num1;
  LargeInt num2;
  

  cout<<"\nEnter the first large integer : ";
  cin >> num1;

  cout<<"\nEnter the second large integer : ";
  cin >> num2;

  if ( num1 > num2 )
    cout <<"\n\nThe first large integer is grater";
  else if ( num1 == num2 )
    cout <<"\n\nThe two large integers are the same";
  else if ( num1 < num2 )
    cout <<"\n\nThe first large integer is smaller";

  cout<<"\n\n"<<num1 << " + " << num2 <<" = "<<  (num1+num2);
  
  cout<<"\n\n"<<num1 << " - " << num2 <<" = "<<  (num1-num2);

  cout<<"\n\n"<<num1 << " * " << num2 <<" = "<<  (num1*num2);

  cout<<"\n\n"<<num1 << " / " << num2 <<" = "<<  (num1/num2);

  cout<<"\n\n"<<num1 << " % " << num2 <<" = "<<  (num1%num2);

  return 0;
}
