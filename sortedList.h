#ifndef SORTEDLIST_H
# define SORTEDLIST_H
#include <string>
#include <iostream>
#include <cstdio>
#include <assert.h>
#include <stdexcept>

namespace mtm
{
template <class T>
class SortedList
{
   class Node
   {
   T data;
   Node* next=NULL;
   friend class SortedList;

   public:
   Node();//constructor
   Node(const T& data);//constructor
   ~Node() = default;//distructor
   Node(Node& node);//copy constructor
   T& operator*();
   };
 Node* head; 

 public:
  class const_iterator
  {    
  const SortedList<T>* list;
  int index;
  const_iterator(const SortedList<T>* list, int index);

  public:
  const_iterator(const const_iterator& it); //copy constructor
  ~const_iterator()=default;//distructor
  const T& operator*() const;
  const_iterator& operator++();//returns reference iterator and "out of range" if gets to null  
  const_iterator operator++(int);//returns iterator and "out of range" if gets to null  
  bool operator==(const const_iterator& it) const;
  bool operator!=(const const_iterator& it) const;
  const_iterator& operator=(const const_iterator&) = default;
  friend class SortedList<T>;
  };

    SortedList();//constructor
    ~SortedList();//distructor
    SortedList(const SortedList& list);//copy constructor
    void insert(const T& data);//insert new data to sorted list
    int length()const;//returns the length of the list
    template <typename Predicate>
    SortedList<T> filter(Predicate pred);// returns sorted list that answers the condition
    template<class Operation>
    SortedList<T> apply(Operation operation);//returns sorted list that with the needed change 
    const_iterator begin() const;
    const_iterator end() const;
    void remove(const const_iterator& it);// removes data from the list
    SortedList<T>& operator=(const SortedList& list);
    bool operator==(const SortedList& list);
    bool operator!=(const SortedList& list);
    static void empty(SortedList& list);//clears the data inside the sorted list
      //copy the data inside the sorted list to other list
    static void copyAndAllocate( SortedList& list_original ,const SortedList& list_to_copy);
   
};

  template <class T>
  SortedList<T>::Node::Node():
  next(nullptr){}
  template <class T>
  SortedList<T>::Node::Node(const T& data_to_insert):
  data(data_to_insert),next(nullptr)
  {}
  template <class T>
  SortedList<T>::Node::Node(SortedList<T>::Node &other):
  data(other.data),next(other.next)
  {}
 
  template <class T>
  T& SortedList<T>::Node::operator*()
  {
    return this->data;
  }  

 template <class T>
 SortedList<T>::SortedList():
 head(nullptr)
 { }

  template <class T>
 SortedList<T>::~SortedList()
 {
    empty(*this);
 }
  template <class T>
 SortedList<T>::SortedList(const SortedList<T>& list):
 head(nullptr)
 {
     copyAndAllocate(*this,list);
 }

 template <class T>
 void SortedList<T>::insert(const T& data)
 {
     SortedList<T>::Node* new_node= new SortedList<T>::Node(data) ;
     if(this->head==NULL)
     {
         this->head=new_node;
         return;
     }
     SortedList<T>::Node * ptr_back=this->head;
     SortedList<T>::Node * ptr_front=ptr_back->next;
    if(**new_node<**ptr_back)
    {
        new_node->next=ptr_back;
        this->head=new_node;
        return;
    }
    while(ptr_front!=NULL && **ptr_front<**new_node)
    { 
        ptr_front=ptr_front->next;
        ptr_back=ptr_back->next;
    }
    if(ptr_front==NULL)
    {
        ptr_back->next=new_node;
        return;
    }
    ptr_back->next=new_node;
    new_node->next=ptr_front;
 }

  template <class T>
 int SortedList<T>::length()const
 {
     SortedList<T>::Node * ptr=this->head;
     int counter=0;
     while (ptr!=NULL)
     {
         ptr=ptr->next;
         counter++;
     }
   return counter;   
 }


 template <class T> 
bool SortedList<T>::operator==(const SortedList<T>& list1)
{
   if(this==&list1)
   {
       return true;
   }
   return false;
}

template <class T>
bool SortedList<T>::operator!=(const SortedList<T>& list)
{
    if(this==&list)
    {
        return false;
    }
    return true;
}

 template <class T>
 SortedList<T>& SortedList<T>:: operator=(const SortedList<T>& list)
 { 
    if(this==&list)
    {
        return *this;
    }
    empty(*this);
    copyAndAllocate(*this,list);
    return *this; 
 }

 template <class T>
 template <typename Predicate>
 SortedList<T> SortedList<T>::filter(Predicate pred)
 {
   SortedList<T> new_list;
   for(typename SortedList<T>::const_iterator it=this->begin();it!=this->end();++it)
   {
      if(pred(*it))
      {
          new_list.insert(*it);
      }
   }
   return new_list;
 }

 template<class T>
 void SortedList<T>::remove(const const_iterator& it)
 {
    if(it.list==NULL)
    {
        return;
    }
    SortedList<T>::Node *pointer=this->head; 
    if(it.index==0)
    {
        this->head=this->head->next;
        delete pointer;
        return;
        
    }
    SortedList<T>::Node *ptr_back=this->head;
    int counter=0;
    while(it.index!=counter)
    {
        ptr_back=pointer;
        pointer=pointer->next;
        counter++;
    }
    if(pointer->next==NULL)
    {
        ptr_back->next=NULL;
        delete pointer;
        return;
    }
    ptr_back->next=pointer->next;
    delete pointer;
 }

 template<class T>
typename SortedList<T>::const_iterator SortedList<T>::begin() const 
{
return const_iterator(this, 0);
}

template<class T>
typename SortedList<T>::const_iterator SortedList<T>::end() const 
{
 return const_iterator(this, this->length());
} 

template<class T> 
template<class Operation>
SortedList<T> SortedList<T>::apply(Operation operation)
{
    SortedList<T> list;
    for(SortedList<T> :: const_iterator it=begin();it!=end();++it)
    {
        T element=operation(*it);
        list.insert(element);

    }
    return list;
}

 template <class T>
 void SortedList<T>::empty(SortedList<T>& list)
 { 
    SortedList<T>::Node * ptr_temp;
    while (list.head!=NULL)
    {
        ptr_temp=list.head;
        list.head=list.head->next;
        delete ptr_temp;
    }
 }

template <class T>
 void SortedList<T>::copyAndAllocate( SortedList<T>& list_original ,const SortedList<T>& list_to_copy)
 {
     SortedList<T>::Node *ptr_to_copy=list_to_copy.head;
     list_original.head=NULL;
     while(ptr_to_copy!=NULL)
     {
         list_original.insert(**ptr_to_copy);
         ptr_to_copy=ptr_to_copy->next;
       
     }
 }
template <class T>
SortedList<T>::const_iterator::const_iterator(const SortedList<T>* list, int index):
list(list),index(index) 
{}

template <class T>
SortedList<T>::const_iterator::const_iterator(const const_iterator& it):
const_iterator(it.list,it.index)
{}

 template <class T>
 const T& SortedList<T>::const_iterator::operator*() const
 {
  //assert(index>=0 && index<list->length());
  SortedList<T>::Node* ptr=this->list->head;
  int counter=0;
  while(counter<this->index)
  {
    ptr=ptr->next;
    counter++;    
  }
  return **ptr;
 }

 template <class T>
 typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++()
 {
   if(this==nullptr)
   {
       throw std::out_of_range("out of range");
   }
   ++index;
   return *this;
 }

 template <class T>
 typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int)
 {
    if(this==nullptr)
   {
       throw std::out_of_range("out of range");
   } 
   const_iterator result = *this;
   ++*this;
   return result; 
 }

 template <class T>
 bool SortedList<T>::const_iterator::operator==(const SortedList<T>::const_iterator& it) const
 {
        
        return ((index == it.index) && list==it.list);
 }

 template <class T>
 bool SortedList<T>::const_iterator::operator!=(const SortedList<T>::const_iterator& it) const
 {
     if(*this==it)
     {
         return false;
     }
     return true;
 }
}
#endif