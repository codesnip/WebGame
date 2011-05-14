#include "../include/IntConnectedList.h"

cIntConnectedList::cIntConnectedList( unsigned int NumMemoryToReserve )
{
    //ctor
    Data = new IntOneElement[NumMemoryToReserve];
    NumElements = 0;
    FirstValue = 0;
    LastValue = 0;
}

cIntConnectedList::~cIntConnectedList()
{
    //dtor
    delete [] Data;
}

void cIntConnectedList::Add( int ValueToAdd )
{
    if( NumElements == 0)
    {
            Data[ValueToAdd].PreviousVal = 0;
    Data[ValueToAdd].NextVal = 0;
    }

}
