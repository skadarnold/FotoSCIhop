/*	FotoSCIhop - Sierra SCI1.1/SCI32 games translator
 *  Copyright (C) Enrico Rolfi 'Endroz', 2004-2021.
 *
 *  generic list class
 *
 */

#include "stdafx.h"

#include "list.h"


template <class T>
bool List<T>::changeItem(const unsigned short which, const T *it)
{
   if (which<_last)
   {
      _item[which]=*it;
      return true;
   }   
   return false;
}

template <class T>
bool List<T>::insertItem(unsigned short loc, const T *it)
{
   if (it && (_last<_size))
   {
      //delete &_item[_last];
      for (unsigned short j=_last++; j>loc; j--)
          _item[j]=_item[j-1];

      _item[loc]=*it;  

      return true;
   }
   return false; 
}

