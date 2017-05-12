/***********************************************************************
 * Header:
 *    NOW SERVING
 * Summary:
 *    This will contain just the prototype for nowServing(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Nathan Bench, Jed Billman, Justin Chandler, Jeremy Chandler (Leonel Messi)
 ************************************************************************/

#ifndef NOW_SERVING_H
#define NOW_SERVING_H

//#include "deque.h"     // for DEQUE
#include <deque>

// the interactive nowServing program
void nowServing();

/************************************************
 * STUDENT
 * name, class, minutes
 ***********************************************/
class Student
{
   private:
      std::string name;
      std::string className;
      int minutes;
      bool isEmergency;
      
   public:
      // default constructor
      Student(): name(""), className(""), minutes(0), isEmergency(false) {}
      
      // non-default constructor
      Student(std::string & className, std::string & name, int & minutes, bool & emergency);
      
      // assignment operator
      Student & operator = (const Student & rhs);
      
      // getters
      std::string getName()                  { return name;                 }
      std::string getClass()                 { return className;            }
      int getMinutes()                       { return minutes;              }
      bool isEmergent()                      { return isEmergency;          }
      
      // setters
      void setName(std::string name)         { this->name = name;           }
      void setClass(std::string className)   { this->className = className; }
      void setMinutes(int minutes)           { this->minutes = minutes;     }
      void setEmergency(bool emergency)      { isEmergency = emergency;      }
      
      void subMin()                          { minutes--;                   }
      
      void display();
};

#endif // NOW_SERVING_H

