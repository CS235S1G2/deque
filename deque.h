/***********************************************************************
* Header:
*    Deque
* Summary:
*
*    This will contain the class definition of:
*        Deque         : 
* Author
*    Nathan Bench, Jed Billman, Justin Chandler, Jeremy Chandler (Leonel Messi)
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
   // constructors & destructors
   Deque() : m_iBack(-1), m_iFront(0), m_max(0), m_data(NULL) {}
   
   Deque(int capacity) throw (const char *);   

   Deque(const Deque<T> & rhs) throw (const char *);
   
   Deque<T> & operator = (const Deque <T> & rhs);
   
   ~Deque()        { if (!empty()) delete [] m_data; }
   
   // standard container interfaces
   bool empty() const  { return size() == 0; }

   void clear() { m_iBack = -1; m_iFront = 0; }

   int capacity() const { return m_max;             }
   
   int size() const    { return m_iBack - m_iFront + 1;              }

   // deque specific interfaces
   void push_back(const T & t) throw (const char *);

   void push_front(const T & t) throw (const char *);

   void pop_back() throw (const char *);

   void pop_front() throw (const char *);

   T & front()     throw (const char *);
   T front() const throw (const char *);
   
   T & back()     throw (const char *);
   T back() const throw (const char *);
   
private:
   T * m_data;          // dynamically allocated array of T
   int m_iFront,
       m_iBack,
       m_max;      // how many items can I put on the Deque before full?
   
   // private methods -- cite: Brother Jones Discussion Board 04
   int iAbsoluteFromIRelative(int i) const
   {
      return (i >= 0) ? (i % m_max) : (m_max - ((-1 -i) % m_max) - 1);
   }
   
   int getIBack() const   { return iAbsoluteFromIRelative(m_iBack);  }
   int getIFront() const  { return iAbsoluteFromIRelative(m_iFront); }
   
   // increase capacity
   void resize(int newCap);
};

/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque <T> & rhs) throw (const char *)
{
   assert(rhs.m_max >= 0);

  
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
   m_iFront = 0;
   m_iBack = -1;  
   m_max = 0;
   
   int j = 0;
   // IF there is data to copy
   if (rhs.size() > 0)
   {      
      // copy over data
      for (int i = rhs.m_iBack; i < rhs.m_iBack; i++)
      {
         m_data[j++] = rhs.m_data[(i % rhs.capacity())];
	     m_iBack++;
      }
	  m_max = rhs.capacity();
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
   if (m_max == 0)
   {
	   m_iFront = 0;
	   m_iBack = -1;
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
   m_max = capacity;
   m_iBack = -1;
   m_iFront = 0;

   // initialize the container by calling the default constructor
   for (int i = 0; i < m_max; i++)
      m_data[i] = T();
}

/***************************************************
* DEQUE :: PUSH BACK
* Adds an item to the back of the deque
**************************************************/
template<class T>
void Deque<T>::push_back(const T & t) throw (const char *)
{
	if (size() == capacity())
	{
		resize(capacity() * 2);
	}
   
   m_iBack++;
	m_data[getIBack()] = t;
}

/***************************************************
* DEQUE :: PUSH FRONT
* Adds an item to the front of the deque
**************************************************/
template<class T>
inline void Deque<T>::push_front(const T & t) throw(const char *)
{
	if (size() == capacity())
	{
		resize(capacity() * 2);
	}

	m_iFront--;
	m_data[getIFront()] = t;
}

/***************************************************
* DEQUE :: POP BACK
* Removes an item from the back of the deque
**************************************************/
template<class T>
inline void Deque<T>::pop_back() throw(const char *)
{
	if (empty())
		throw "ERROR: attempting to pop from an empty deque";
	m_iBack--;
}

/***************************************************
* DEQUE :: POP FRONT
* Removes an item from the front of the deque
**************************************************/
template<class T>
void Deque<T>::pop_front() throw(const char *)
{
	if (empty())
		throw "ERROR: attempting to pop from an empty deque";
	m_iFront++;
}

/***************************************************
* DEQUE :: FRONT
* Returns the item currently at the front of the deque by reference
**************************************************/
template<class T>
T & Deque<T> :: front() throw(const char *)
{
   if (size() > 0)
      return m_data[getIFront()];
   else
      throw "ERROR: unable to access data from an empty deque"; 
}
/***************************************************
* DEQUE :: FRONT C
* Returns the item currently at the front of the deque by const value
**************************************************/
template<class T>
T Deque<T> :: front() const throw(const char *)
{
   if (size() > 0)
      return m_data[getIFront()];
   else
      throw "ERROR: unable to access data from an empty deque";     
}

/***************************************************
* DEQUE :: BACK
* Returns the item currently at the back of the deque by reference
**************************************************/
template<class T>
T & Deque<T> :: back()     throw (const char *)
{
   if (size() > 0)
      return m_data[getIBack()];
   else
      throw "ERROR: unable to access data from an empty deque";
}
   
/***************************************************
* DEQUE :: BACK C
* Returns the item currently at the back of the deque by const value
**************************************************/
template<class T>
T Deque<T> :: back() const throw (const char *)
{
   if (size() > 0)
      return m_data[getIBack()];
   else
      throw "ERROR: unable to access data from an empty deque";
}

/***************************************************
 * DEQUE :: =
 * Overload assignment operator
 **************************************************/
 template <class T>
 Deque<T> & Deque <T> :: operator = (const Deque <T> & rhs)
 {
    // resize array to the rhs
    if (m_max < rhs.size())
       resize(rhs.size());
    
    clear();

    // copy over data
    for (int i = rhs.m_iFront; i < rhs.m_iBack; i++)
    {
       push_back(rhs.m_data[iAbsoluteFromIRelative(i)]);
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
         temp[i] = m_data[(getIFront() + i) % m_max];
      }              

      m_iBack = size();
      m_iFront = 0;
      m_max = newCap;
      
      delete [] m_data;
      
      // in with the new
      m_data = temp;       

   }
   
   catch(std::bad_alloc)
   {
      throw "ERROR: Unable to allocate a new buffer for Deque";
   }
}

#endif // DEQUE_H
