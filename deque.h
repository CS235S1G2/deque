/***********************************************************************
* Header:
*    Deque
* Summary:
*
*    This will contain the class definition of:
*        Deque         : 
* Author
*    Nathan Bench, Jed Billman, Justin Chandler (Messi), Jeremy Chandler
************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>
#include <new>
#include <iostream>

/************************************************
 * DEQUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Deque
{
public:
   // default constructor : empty and kinda useless
   Deque() : m_numPush(0), m_numPop(0), m_capacity(0), m_data(NULL) {}

   // copy constructor : copy it
   Deque(const Deque<T> & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Deque(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Deque()        { if (!empty()) delete [] m_data; }
   
   // is the container currently empty
   bool empty() const  
   {
      return size() == 0;
   }

   // remove all the items from the container
   void clear()        { m_numPush = m_numPop = 0;                 }

   // how many items can the stack currently contain?
   int capacity() const { return m_capacity;             }
   
   // how many items are currently in the container?
   int size() const    { return (m_numPush - m_numPop);              }   // cite: BYUI PDF page 83

   // add an item to the back of the deque
   void push(const T & t) throw (const char *);

   // Removes an item from the front of the deque
   void pop() throw (const char *);

   // Returns the item currently at the front of the deque
   T & front()     throw (const char *);
   //T front() const throw (const char *);
   
   // Returns the item currently at the front of the deque
   T & back()     throw (const char *);
   //T back() const throw (const char *);
   
   // assignment operator '='
   Deque<T> & operator = (const Deque <T> & rhs);
   
private:
   T * m_data;          // dynamically allocated array of T
   int m_numPush,       // cite: BYUI PDF page 82
       m_numPop,
       m_capacity;      // how many items can I put on the Deque before full?
   
   // private methods
   int iHead() const { return m_numPop % m_capacity; }           // cite: BYUI PDF page 82
   int iTail() const { return (m_numPush - 1) % m_capacity; }    // cite: BYUI PDF page 82
   // increase capacity
   void resize(int newCap);
};

/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
   assert(rhs.m_capacity >= 0);

  
      try
      {
         T * temp = new T[rhs.size()];
         
         // assign new data
         m_data = temp;
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate a new buffer for Deque";
      }
   
   // insure the indices are beginning at 0
   m_numPop = 0;
   m_numPush = 0;  
   m_capacity = 0;
   
   int j = 0;
   // IF there is data to copy
   if (rhs.size() > 0)
   {      
      // copy over data
      for (int i = rhs.m_numPop; i < rhs.m_numPush; i++)
      {
         m_data[j++] = rhs.m_data[(i % rhs.capacity())];
	     m_numPush++;
      }
	  m_capacity = rhs.capacity();
   }

}

/**********************************************
 * DEQUE : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Deque <T> :: Deque(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (m_capacity == 0)
   {
      m_numPop = m_numPush = 0;
      m_data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      m_data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

      
   // SET member variables
   m_capacity = capacity;
   m_numPush = m_numPop = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < m_capacity; i++)
      m_data[i] = T();
}

/***************************************************
* DEQUE :: PUSH
* Adds an item to the back of the deque
**************************************************/
template<class T>
void Deque<T>::push(const T & t) throw (const char *)
{
	if (size() == capacity())
	{
		resize(capacity() * 2);
	}
   
    m_numPush++;
	m_data[iTail()] = t;
}

/***************************************************
* DEQUE :: POP
* Removes an item from the front of the deque
**************************************************/
template<class T>
void Deque<T>::pop() throw(const char *)
{
	if (empty())
		throw "ERROR: attempting to pop from an empty deque";
	m_numPop++;
}

/***************************************************
* DEQUE :: FRONT
* Returns the item currently at the front of the deque by reference
**************************************************/
template<class T>
T & Deque<T> :: front() throw(const char *)
{
	// if empty
	if (empty())
		throw "ERROR: attempting to access an item in an empty deque";
	return m_data[iHead()];
}
/***************************************************
* DEQUE :: FRONT C
* Returns the item currently at the front of the deque by const value
**************************************************/
/*template<class T>
T Deque<T> :: front() const throw(const char *)
{
	// if empty
	if (empty())
		throw "ERROR: attempting to access an item in an empty deque";
	return m_data[iHead()];      
}*/

/***************************************************
* DEQUE :: BACK
* Returns the item currently at the back of the deque by reference
**************************************************/
template<class T>
T & Deque<T> :: back()     throw (const char *)
{
   if (empty())
		throw "ERROR: attempting to access an item in an empty deque";
	return m_data[iTail()]; 
}
   
/***************************************************
* DEQUE :: BACK C
* Returns the item currently at the back of the deque by const value
**************************************************/
/*template<class T>
T Deque<T> :: back() const throw (const char *)
{
   if (empty())
		throw "ERROR: attempting to access an item in an empty deque";
	return m_data[iTail()]; 
}*/

/***************************************************
 * DEQUE :: =
 * Overload assignment operator
 **************************************************/
 template <class T>
 Deque<T> & Deque <T> :: operator = (const Deque <T> & rhs)
 {
	 // don't copy yourself
	 if (this != &rhs)
	 {
		 // resize array to the rhs
		 if (m_capacity < rhs.size())
			 resize(rhs.size());

		 // insure the indices are beginning at 0

		 int j = 0;
		 // IF there is data to copy
		 m_numPush = 0;
		 m_numPop = 0;
		 if (rhs.size() > 0)
		 {
			 // copy over data
			 for (int i = rhs.m_numPop; i < rhs.m_numPush; i++)
			 {
				 m_data[j++] = rhs.m_data[(i % rhs.capacity())];
				 m_numPush++;
			 }
		 }
	 }
	 return *this;
 }
   
/***************************************************
* DEQUE :: RESIZE
* Allocate memory for m_data
**************************************************/
template<class T>
void Deque<T>::resize(int newCap)
{
   if (newCap == 0)
      newCap = 1;

   try
   {
      T *temp = new T[newCap];
      
      for (int i = 0; i < size(); i++)
      {
         temp[i] = m_data[(iHead() + i) % capacity()];
      }
	  m_numPush = size();
	  m_numPop = 0;
      m_capacity = newCap;
      
      // in with the new
      m_data = temp;       

   }
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Deque";
   }

}

#endif // DEQUE_H
