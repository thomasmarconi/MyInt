// starter file for MyInt class header -- Thomas Marconi
#include<iostream>
using namespace std;
class MyInt
{
   // operator overloads
   friend MyInt operator+ (const MyInt& x, const MyInt& y);       //addition
   friend MyInt operator* (const MyInt& x, const MyInt& y);       //multiplication
   //friend MyInt operator/ (const MyInt& x, const MyInt& y);       //division
   //friend MyInt operator% (const MyInt& x, const MyInt& y);       //modulus
   friend MyInt operator- (const MyInt& x, const MyInt& y);       //subtraction
   friend bool operator< (const MyInt& x, const MyInt& y);        //less than
   friend bool operator> (const MyInt& x, const MyInt& y);        //greater than
   friend bool operator<= (const MyInt& x, const MyInt& y);       //less than or equal to
   friend bool operator>= (const MyInt& x, const MyInt& y);       //greater than or equal to
   friend bool operator== (const MyInt& x, const MyInt& y);       //comparison
   friend bool operator!= (const MyInt& x, const MyInt& y);       //not equal to
   friend istream& operator>> (istream& s, MyInt& x);   //handles cin
   friend ostream& operator<< (ostream& s, const MyInt& x);   //handles cout

public:
   MyInt(int n = 0);		                  // first constructor -- int param
   MyInt(char string[]);                  // second constructor -- char param
   MyInt(const MyInt &m);                 // deep copy
   ~MyInt();                              // destructor
   MyInt& operator=(const MyInt &m);       // assignment operator -- deep assignment
   MyInt& operator++();                   //pre-fix increment
   MyInt operator++(int);                 //post-fix increment
   int C2I(char c);
   char I2C(int x);

private:
   // member data (suggested:  use a dynamic array to store the digits)
   unsigned int currentSize;                     //holds the size of the array
   int* number;                                  //dynamically allocated array of digits           
   void Grow();                                  //grows the array when the number is too big for the current array
   void Shrink();
};