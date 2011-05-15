/*
Copyright (C) 2011 WebGame project.
*/

#include "../include/IntConnectedList.h"
#include <iostream>
cIntConnectedList::cIntConnectedList( unsigned int NumMemoryToReserve )
{
    //ctor
    Data = new IntOneElement[NumMemoryToReserve+1]; //+1
    NumElements = 0;
    FirstValue = ITERATOR_END;
    LastValue = ITERATOR_END;
    IteratorValueToReturn = ITERATOR_END;
}

cIntConnectedList::~cIntConnectedList()
{
    //dtor
    delete [] Data;
}

void cIntConnectedList::PrintAll()
{
   // int TempElement = FirstValue;
   // int i;
   // for( i=0 ; i!=NumElements ; i++ )
    //{
    //    std::cout << "Element no " << i << " value: " <<  TempElement << "\n";
    //    TempElement = Data[TempElement].NextVal;
   // }

    int TempElement;
    ResetIterator();
    int i = 0;
    for( TempElement = GetNextValue(); TempElement != ITERATOR_END ; TempElement = GetNextValue() )
    {
        std::cout << "Element no " << i << " value: " <<  TempElement << "\n";
        i++;
    }

}

void cIntConnectedList::Remove( int ValueToRemove )
{
    if( NumElements == 0)
    {
        return;
    }else if( NumElements == 1)
    {
        NumElements = 0;
        FirstValue  = ITERATOR_END;
        LastValue   = ITERATOR_END;
    }else
    {
        if( ValueToRemove == FirstValue )
        {
            FirstValue = Data[ValueToRemove].NextVal;
            NumElements--;
        }else if ( ValueToRemove == LastValue )
        {
            LastValue = Data[ValueToRemove].PreviousVal;
            Data[LastValue].NextVal = ITERATOR_END;
            NumElements--;
        }else
        {
            Data[Data[ValueToRemove].PreviousVal].NextVal = Data[ValueToRemove].NextVal;
            Data[Data[ValueToRemove].NextVal].PreviousVal = Data[ValueToRemove].PreviousVal;
            NumElements--;
        }
    }


}

void cIntConnectedList::Add( int ValueToAdd )
{
    if( NumElements == 0)
    {
        Data[ValueToAdd].PreviousVal = 0;
        Data[ValueToAdd].NextVal = 0;
        NumElements = 1;
        FirstValue = ValueToAdd;
        LastValue = ValueToAdd;
    }else
    {
        Data[LastValue].NextVal = ValueToAdd;
        Data[ValueToAdd].PreviousVal = LastValue;
        Data[ValueToAdd].NextVal = 0;
        LastValue = ValueToAdd;
        NumElements++;
    }

}

void cIntConnectedList::ResetIterator()
{
    IteratorValueToReturn = FirstValue;
}

int cIntConnectedList::GetNextValue()
{
    int ValueToReturn = IteratorValueToReturn;
    if( IteratorValueToReturn == LastValue || IteratorValueToReturn == ITERATOR_END )
    {
        IteratorValueToReturn = ITERATOR_END;
    }else
    {
       IteratorValueToReturn = Data[IteratorValueToReturn].NextVal;
    }
    return ValueToReturn;
}
