/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  generic list class 
 *     
 */
  
#ifndef LIST_H
#define LIST_H                   

template <class T>
class List {
private:
	unsigned short _size;
    unsigned short _last;
          
	T *_item;

public:
    List(void) : _size(0), _item(0), _last(0) { }

	List(const unsigned short size) : _size(size), _last(0), _item(new T[_size]) { }

	~List() { if (_item) delete [] _item; }
    
	unsigned short getSize() const { return _size; }
    unsigned short getLast() const { return _last; }
	T *getItem(unsigned short which) const;
	bool addItem(const T *it);
    bool changeItem(const unsigned short which, const T *it);
    bool insertItem(unsigned short loc, const T *it);
};

 


template <class T>
bool List<T>::addItem(const T *it)
{
   if (it && (_last<_size))
   {
      //delete &_item[_last];        
      _item[_last++]=*it;
      return true;
   }
   return false;
}

template <class T>  
T *List<T>::getItem(unsigned short which) const 
{
   if (which<_last)
      return &_item[which];
   return 0;  
}
#endif 
