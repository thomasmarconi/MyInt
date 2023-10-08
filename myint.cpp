//file for myInt class definitions -- Thomas Marconi
#include <iostream>
#include "myint.h"
#include <iomanip>
#include <cctype>
#include <cstring>

using namespace std;

// friend operator overloads---------------------------------------------------------- 
MyInt operator+ (const MyInt& x, const MyInt& y)       //addition
{
   MyInt z;                                                 //going to hold the final sum

   //if one of the numbers is zero
   if(x == 0)
      return y;
   if(y == 0)
      return x;

   //2 branches either x has more digits or (y has more digits or they're equal digits)
   if(x.currentSize>=y.currentSize)
   {
      z.currentSize = x.currentSize;
      z.Grow();
      for (unsigned int i = 0; i < z.currentSize; ++i)
         z.number[i] = 0;
      for (unsigned int i = 1; i < y.currentSize + 1; ++i) //add all of the y indeces
      {
         z.number[z.currentSize - i] = z.number[z.currentSize - i] + x.number[x.currentSize - i] + y.number[y.currentSize - i];
         if(z.number[z.currentSize - i] > 9)
         {
            z.number[z.currentSize - i - 1] = z.number[z.currentSize - i] / 10;
            z.number[z.currentSize - i] = z.number[z.currentSize - i] % 10;
         }
      }
      for (unsigned int i = x.currentSize - y.currentSize - 1; i >= 0; --i)  //add the remaining of the x indecese
      {
         if(x.currentSize - y.currentSize == 0)
            break;
         z.number[i + 1] = z.number[i + 1] + x.number[i];
         if(z.number[i+1] > 9)
         {
            z.number[i] = z.number[i+1] / 10;
            z.number[i+1] = z.number[i+1] % 10;
         }
         if(i==0)
            break;
      }
      if(z.number[0] == 0)
      {
         for (unsigned int i = 0; i < z.currentSize; ++i)
         {
            z.number[i] = z.number[i+1];
         }
         z.Shrink();
      }
   }
   else if(x.currentSize<y.currentSize)
   {
      z.currentSize = y.currentSize;
      z.Grow();
      for (unsigned int i = 0; i < z.currentSize; ++i)
         z.number[i] = 0;
      for (unsigned int i = 1; i < x.currentSize + 1; ++i) //add all of the y indeces
      {
         z.number[z.currentSize - i] = z.number[z.currentSize - i] + y.number[y.currentSize - i] + x.number[x.currentSize - i];
         if(z.number[z.currentSize - i] > 9)
         {
            z.number[z.currentSize - i - 1] = z.number[z.currentSize - i] / 10;
            z.number[z.currentSize - i] = z.number[z.currentSize - i] % 10;
         }
      }
      for (unsigned int i = y.currentSize - x.currentSize - 1; i >= 0; --i)  //add the remaining of the x indecese
      {
         if(y.currentSize - x.currentSize == 0)
            break;
         z.number[i + 1] = z.number[i + 1] + y.number[i];
         if(z.number[i+1] > 9)
         {
            z.number[i] = z.number[i+1] / 10;
            z.number[i+1] = z.number[i+1] % 10;
         }
         if(i==0)
            break;
      }
      if(z.number[0] == 0)
      {
         for (unsigned int i = 0; i < z.currentSize; ++i)
         {
            z.number[i] = z.number[i+1];
         }
         z.Shrink();
      }
   }

   return z;
}
MyInt operator* (const MyInt& x, const MyInt& y)       //multiplication
{
   MyInt z(0);
   MyInt t(0);
   
   if(x==0 || y ==0)
      return z;
   //2 cases -- x>y,x<=y

   if(x>y)//x is greater
   {
      unsigned int counter = 0;
      for (unsigned int i = y.currentSize - 1; i >= 0 ; --i)
      {  
         for (unsigned int j = x.currentSize -1; j >= 0; --j)
         {
            t.number[0] = t.number[0] + y.number[i] * x.number[j];
            if(j==0)
               break;
            t.Grow();
            for (unsigned int i = 1; i < t.currentSize; ++i) //shift everything right 1
            {
               t.number[t.currentSize - i] = t.number[t.currentSize - i - 1];
            }
            t.number[0] = 0;
            if(t.number[1]>9)
            {
               t.number[0] = t.number[1]/10;
               t.number[1] = t.number[1]%10;
            }
         }
         if(t.number[0] == 0) //clean up leading zero
         {
            for (unsigned int i = 0; i < t.currentSize; ++i)
            {
               t.number[i] = t.number[i+1];
            }
            t.Shrink();
         }
         z = z + t;                                  //add partial prod to prod
         t = 0;                                       //make t = 0 again
         counter++;
         for (unsigned int i = 0; i < counter; ++i)   //add zeros in for arithmetic
         {
            t.Grow();
            for (unsigned int j = t.currentSize - 1; j > 0; --j) //make t = 0 again
               t.number[j] = 0;
            t.number[0] = 0;
         }
         if(z.number[0] == 0) //clean up leading zero
         {
            for (unsigned int i = 0; i < z.currentSize; ++i)
            {
               z.number[i] = z.number[i+1];
            }
            z.Shrink();
         }
         if(i==0)
            break;
      }
   }
   if(x<=y)//y is greater or the number is being multiplied by itself
   {
      unsigned int counter = 0;
      for (unsigned int i = x.currentSize - 1; i >= 0 ; --i)
      {  
         for (unsigned int j = y.currentSize -1; j >= 0; --j)
         {
            t.number[0] = t.number[0] + x.number[i] * y.number[j];
            if(j==0)
               break;
            t.Grow();
            for (unsigned int i = 1; i < t.currentSize; ++i) //shift everything right 1
            {
               t.number[t.currentSize - i] = t.number[t.currentSize - i - 1];
            }
            t.number[0] = 0;
            if(t.number[1]>9)
            {
               t.number[0] = t.number[1]/10;
               t.number[1] = t.number[1]%10;
            }
         }
         if(t.number[0] == 0) //clean up leading zero
         {
            for (unsigned int i = 0; i < t.currentSize; ++i)
            {
               t.number[i] = t.number[i+1];
            }
            t.Shrink();
         }
         z = z + t;                                  //add partial prod to prod
         t = 0;                                       //make t = 0 again
         counter++;
         for (unsigned int i = 0; i < counter; ++i)   //add zeros in for arithmetic
         {
            t.Grow();
            for (unsigned int j = t.currentSize - 1; j > 0; --j) //make t = 0 again
               t.number[j] = 0;
            t.number[0] = 0;
         }
         if(z.number[0] == 0) //clean up leading zero
         {
            for (unsigned int i = 0; i < z.currentSize; ++i)
            {
               z.number[i] = z.number[i+1];
            }
            z.Shrink();
         }
         if(i==0)
            break;
      }
   }  
   return z;
}
MyInt operator- (const MyInt& x, const MyInt& y)       //subtraction
{
   MyInt z;                                                 //going to hold the final sum

   //if one of the numbers is zero
   if(x == 0)
      return y;
   if(y == 0)
      return x;
   if(x == y)
      return z;
   if(x<y)
      return z;

   if(x.currentSize>y.currentSize ||( x>y && x.currentSize==y.currentSize) )
   {
      unsigned int counter = 0;
      z.currentSize = x.currentSize;
      z.Grow();
      for (unsigned int i = 0; i < z.currentSize; ++i)
         z.number[i] = 0;
      for (unsigned int i = 1; i < y.currentSize + 1; ++i) //subtract all of the y indeces from the x indeces
      {
         z.number[z.currentSize - i] = z.number[z.currentSize - i] + x.number[x.currentSize - i] - y.number[y.currentSize - i];
         if(z.number[z.currentSize - i] < 0)
         {
            counter = 0;
            z.number[z.currentSize - i] = z.number[z.currentSize - i] + 10;
            if(x.number[x.currentSize - i - 1] > 0)
               x.number[x.currentSize - i - 1] = x.number[x.currentSize - i - 1] - 1;
            while(x.number[x.currentSize - i - 1 - counter] <= 0)
            {
               x.number[x.currentSize - i - 1 - counter] = 9;
               if(x.currentSize - i - 1 - counter < 0)
                  break;
               x.number[x.currentSize - i - 2 - counter] = x.number[x.currentSize - i - 2 - counter] - 1;
               counter++;
            }
         }
      }
      for (unsigned int i = x.currentSize - y.currentSize - 1; i >= 0; --i)  //add the remaining of the x indecese to z
      {
         if(x.currentSize - y.currentSize == 0)
            break;
         z.number[i + 1] = z.number[i + 1] + x.number[i];
         if(i==0)
            break;
      }
      while(z.number[0] == 0)
      {
         for (unsigned int j = 0; j < z.currentSize; ++j) //shift left 1
         {
            z.number[j] = z.number[j+1];
         }
         z.Shrink(); //shrink
      }
   }
   return z;
}
/*
MyInt operator/ (const MyInt& x, const MyInt& y)       //division
{

}
MyInt operator% (const MyInt& x, const MyInt& y)       //modulus
{

}*/
bool operator< (const MyInt& x, const MyInt& y)        //less than
{
   if(x.currentSize<y.currentSize)
      return true;
   else if(x.currentSize>y.currentSize)
      return false;
   else if(x.currentSize == y.currentSize)
   {
      for (int i = 0; i < x.currentSize; ++i)
      {
         if (x.number[i]<y.number[i])
            return true;
         if (x.number[i]>y.number[i])
            return false;
      }
   }
   return false;
}
bool operator> (const MyInt& x, const MyInt& y)        //greater than
{

   return(!(x<=y));
}
bool operator<= (const MyInt& x, const MyInt& y)       //less than or equal to
{

   return((x<y)||(x==y));
}
bool operator>= (const MyInt& x, const MyInt& y)       //greater than or equal to
{

   return(!(x<y));
}
bool operator== (const MyInt& x, const MyInt& y)       //comparison
{
   if(x.currentSize == y.currentSize)
   {
      for (int i = 0; i < x.currentSize; ++i)
      {
         if(x.number[i]!=y.number[i])
            return false;
      }
      return true;
   }
   else
      return false;
}
bool operator!= (const MyInt& x, const MyInt& y)       //not equal to
{

   return(!(x==y));
}
istream& operator>> (istream& s, MyInt& x)             //handles cin
{
   x = 0;
   char c;
   unsigned int store;
   while(isspace(s.peek()))
      s.ignore();
   while(isdigit(s.peek()))
   {
      c = s.get();
      store = x.C2I(c);
      x.number[x.currentSize - 1] = store;
      if(!isdigit(s.peek()))
         break;
      x.Grow();   //make bigger
   }
   return s;
}
ostream& operator<< (ostream& s, const MyInt& x)         //handles cout
{
   for (int i = 0; i < x.currentSize; ++i)
      s<<x.number[i];
   return s;
}

//member functions-----------------------------------------------------------------

//constructors
MyInt::MyInt(int n)
{
   currentSize = 0;
   unsigned int numDigits = 0;
   //if <=0 set array equal to zero
   if(n<=0)
   {
      currentSize++;
      number = new int[currentSize];
      number[0]=0;
   }
   else  //if number is >0
   {
      int nCopy = n;
      while(nCopy!=0)
      {
         nCopy = nCopy / 10;
         ++currentSize;
         ++numDigits;
      }
      number = new int[currentSize];
      while(n!=0)
      {
         int lastDigit = n%10;
         n = n/10;
         number[numDigits-1]=lastDigit;
         numDigits--;
      }  
   }
}
MyInt::MyInt(char string[])                  // second constructor -- char param
{
   currentSize = 0;
   int numDigits = strlen(string);
   bool badString;
   if(strlen(string) == 0)          //if string is empty
   {
      currentSize++;
      number = new int[currentSize];
      number[0]=0;
   }
   for (int i = 0; i < strlen(string); ++i)  //checks if the string has a something other than a number in it
      {
         if(C2I(string[i])==-1)
         {
            badString = true;
            break;
         }
         else badString = false;
      }
   if(badString)                            //if string has characters other than 0-9
   {
      currentSize++;
      number = new int[currentSize];
      number[0]=0;
   }
   else
   {
      currentSize = strlen(string);
      number = new int[currentSize];
      for (int i = 0; i < strlen(string); ++i)  //if string is good
      {
         number[numDigits-1]=C2I(string[numDigits-1]);
         numDigits--;
      }
   } 
}
MyInt::~MyInt()
//destructor function for the MyInt Class -- deallocates the MyInt's list of digits
{

   delete [] number;
}
MyInt::MyInt(const MyInt &m)                 // deep copy
{
   currentSize = m.currentSize;
   number = new int[currentSize];
   for (int i = 0; i < currentSize; ++i)
      number[i]=m.number[i];
}
MyInt& MyInt::operator=(const MyInt &m)       
// assignment operator -- deep assignment
// does a similar task to that of the copy constructor
// but is not a new object, so must delete any existing allocation
// and must return the assigned value (i.e. this object, *this)
{
   if(this != &m)
   {
      delete [] number;
      currentSize = m.currentSize;
      number = new int[currentSize];
      for (int i = 0; i < currentSize; ++i)
         number[i]=m.number[i];
   }
   return *this;
}
MyInt& MyInt::operator++()                   //pre-fix increment
{
   Grow();//make array one slot bigger
   //shift everything right
   for (int i = currentSize - 1; i > 0; i--)
   {
      number[i] = number[i - 1];
   }
   number[currentSize - 1] = number[currentSize - 1] + 1;
   for (int i = currentSize - 1; i > 0; i--)
   {
      if(number[i]>9)
      {
         number[i] = number[i] % 10;
         number[i-1] = number[i-1] + 1;
      }
   }
   if(number[0]>9)
   {
      number[0] = number[0]-9;
      return *this;
   }
   for (int i = 0; i < currentSize - 1; ++i)
   {
      number[i] = number[i + 1];
   }
   Shrink();

   return *this;
}
MyInt MyInt::operator++(int)                 //post-fix increment
{
   MyInt temp = *this;
   Grow();//make array one slot bigger
   //shift everything right
   for (int i = currentSize - 1; i > 0; i--)
   {
      number[i] = number[i - 1];
   }
   number[currentSize - 1] = number[currentSize - 1] + 1;
   for (int i = currentSize - 1; i > 0; i--)
   {
      if(number[i]>9)
      {
         number[i] = number[i] % 10;
         number[i-1] = number[i-1] + 1;
      }
   }
   if(number[0]>9)
   {
      number[0] = number[0]-9;
      return temp;
   }
   for (int i = 0; i < currentSize - 1; ++i)
   {
      number[i] = number[i + 1];
   }
   Shrink();
   return temp;
}
void MyInt::Grow()                           //grows the array when the number is too big for the current array
{
   currentSize++;
   int* newPtr = new int[currentSize];
   for (int i = 0; i < currentSize; ++i)
      newPtr[i]=number[i];
   delete [] number;
   number = newPtr;
}
void MyInt::Shrink()                         //shrink array when too many slots are being used
{
   currentSize--;
   int* newPtr = new int[currentSize];
   for (int i = 0; i < currentSize; ++i)
      newPtr[i] = number[i];
   delete [] number;
   number = newPtr;
}

//conversion functions---------------------------------------------------------

int MyInt::C2I(char c)
// converts character into integer (returns -1 for error)
{
   if (c < '0' || c > '9') return -1;  // error
   return (c - '0');          // success
}

char MyInt::I2C(int x)
// converts single digit integer into character (returns '\0' for error)
{
   if (x < 0 || x > 9)     return '\0';   // error
   return (static_cast<char>(x) + '0');   // success
}