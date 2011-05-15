/*
Copyright (C) 2011 WebGame project.
*/

#ifndef CINTCONNECTEDLIST_H
#define CINTCONNECTEDLIST_H
#define ITERATOR_END -2147483648
struct IntOneElement
{
    unsigned int PreviousVal;
    unsigned int NextVal;
};

class cIntConnectedList
{
    public:
        cIntConnectedList( unsigned int NumMemoryToReserve );
        ~cIntConnectedList();
        void Add( int ValueToAdd );
        void Remove( int ValueToRemove );
        void PrintAll();
        void ResetIterator();
        int GetNextValue();
        inline  int GetNumElements(){ return NumElements; }
    protected:

    private:
        unsigned int NumElements;
        unsigned int FirstValue;
        unsigned int LastValue;
        unsigned int IteratorValueToReturn;

        IntOneElement * Data;
};

#endif // CINTCONNECTEDLIST_H
