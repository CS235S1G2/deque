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
   Student holder;
   
   // instructions
   cout << "Every prompt is one minute.  The following input is accepted:\n";
   cout << "\t<class> <name> <#minutes>    : a normal help request\n";
   cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
   cout << "\tnone                         : no new request this minute\n";
   cout << "\tfinished                     : end simulation\n";

   // your code here
   do
   {
      // reset holder
      Student a;
      holder = a;
      
      // display minutes
      cout << "<" << minutes << "> ";

      // cite: Matt Burr Discussion Board 04 
      string className;
      string studentName;
      int serviceMinutes;
      bool isEmergent = false;
     
      cin >> className;
      if (className == "finished")
         break;
      if (className != "none")
      {
         /*** input to student ***/      
         if (className == "!!")
         {
            cin >> className >> studentName >> serviceMinutes;
            isEmergent = true;
         }
         else
         {
            cin >> studentName >> serviceMinutes;
         }
         // initialize new student
         Student s(className, studentName, serviceMinutes, isEmergent);
         holder = s;
      } // IF input != finished || none
      
         /********************/
         /*** Student flow ***/
         /********************/
         // IF no current student
         if (currentStudent.getMinutes() == 0)
         {
            // IF empty queue
            if (line.empty())
               currentStudent = holder;
            else
            {
               currentStudent = line.front();
               line.pop_front();
            }
         }
         // IF current student with time remaining
         else if (currentStudent.getMinutes() > 1)
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
         // IF emergency with 1 minute left
         else if (currentStudent.getMinutes() == 1 &&
                  holder.isEmergent())
         {
            currentStudent.display();
            currentStudent = holder;
            minutes++;
            continue;
         }

      
      /**********************/
      /*** Current Action ***/
      /**********************/
      // IF current student with time
      if (currentStudent.getMinutes() > 0)
      {
         currentStudent.display();
         currentStudent.subMin();
      } // IF currentStudent.minutes > 0

   minutes++;
   } while (input != "finished");
   // end
   cout << "End of simulation\n";
}

/************************************************
 * STUDENT :: STUDENT
 * non-default constructor
 ***********************************************/
Student :: Student(std::string & className, std::string & name, int & minutes, bool & emergency)
{
   this->className = className;
   this->name = name;
   this->minutes = minutes;
   isEmergency = emergency;
}

/************************************************
 * STUDENT :: DISPLAY
 * display the contents of the student object
 ***********************************************/
void Student :: display()
{
   cout << (isEmergency ?  "\tEmergency for " : "\tCurrently serving ")
        << name
        << " for class "
        << className
        << ". Time left: "
        << minutes
        << endl;
}

/************************************************
 * STUDENT :: ASSIGNMENT OPERATOR
 * Assigns Student lhs to Student rhs
 ***********************************************/
Student & Student :: operator = (const Student & rhs)
{
   className = rhs.className;
   name = rhs.name;
   minutes = rhs.minutes;
   isEmergency = rhs.isEmergency;
   
   return *this;
} 


