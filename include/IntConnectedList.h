#ifndef CINTCONNECTEDLIST_H
#define CINTCONNECTEDLIST_H

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
    protected:

    private:
        unsigned int NumElements;
        unsigned int FirstValue;
        unsigned int LastValue;

        IntOneElement * Data;
};

#endif // CINTCONNECTEDLIST_H
