/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Nathan Bench, Jed Billman, Jeremy Chandler, Justin Chandler
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>       // for STRING
#include <cstring>      // for c_str()
#include <cstdlib>
#include <cassert>      // for ASSERT
#include "nowServing.h" // for nowServing() prototype
#include <deque>
//#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{
   // initialize variables
   string input;
   int minutes = 0;
   deque <Student> line;
   Student currentStudent;
   //Student holder;
   
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   do
   {
      // minute
      cout << "<" << minutes << "> ";
      
      // get input
      cin.ignore();
      cin.clear();
      getline(cin, input);
      if (input != "finished")
      {
         /*** input to student ***/      
         // prep variables
         int index = 0;
         
         int dIndex = 0; 
         string data[3];
            // data[0] -- name
            // data[1] -- class name
            // data[2] -- number
         int number;
         bool isEmergent = false;
         
         // find emergent case
         if (input[0] == '!' && input[1] == '!' && input[2] == ' ')
         {
            isEmergent = true;
            // set index to new start
            index = 3;
         }
         
         // parse input to data[]
         for (index; index < input.size(); index++)
         {
            // IF space increase data's index
            if (input[index] == ' ')
            {
               dIndex++;
            }
            
            // copy char by char
            data[dIndex] += input[index];  
         }
         
         // convert data[2] to int
         number = atoi(data[2].c_str()); // cite: Jeffry Simpson on discussion board
         // handle non digit values
         if (number <= 0)
            number = 1;
         
         // initialize new student
         Student holder(data[0], data[1], number, isEmergent);
         
         
         /*** Student flow ***/
         if (line.empty())
         {
            //currentStudent(holder);
         }
         else
         {
            if (holder.isEmergent())
            {
               line.push_front(holder);
            }
            else
            {
               line.push_back(holder);
            }
         }
         
         /*** Current Action ***/
         // IF current student with time
         if (currentStudent.getMinutes() > 0)
         {
            // emergent
            if (currentStudent.isEmergent())
            {
               cout << "\tEmergency for "
                    << currentStudent.getName()
                    << "for class "
                    << currentStudent.getClass()
                    << ". Time left: "
                    << currentStudent.getMinutes()
                    << endl;
            }
            // non-emergent
            else
            {
               cout << "\tCurrently serving "
                    << currentStudent.getName()
                    << "for class "
                    << currentStudent.getClass()
                    << ". Time left: "
                    << currentStudent.getMinutes()
                    << endl;
            }
         } // IF currentStudent.minutes > 0
         
         minutes++;
      }
      

      
   } while (input != "finished");
   // end
   cout << "End of simulation\n";
}

/************************************************
 * STUDENT :: STUDENT
 * non-default constructor
 ***********************************************/
Student :: Student(std::string & name, std::string & className, int & minutes, bool & emergency)
{
   this->name = name;
   this->className = className;
   this->minutes = minutes;
   isEmergency = emergency;
} 


