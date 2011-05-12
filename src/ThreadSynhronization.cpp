#include "../include/ThreadSynhronization.h"

cThreadSynhronization::cThreadSynhronization()
{
    //ctor
    mutex = PTHREAD_MUTEX_INITIALIZER;
}

cThreadSynhronization::~cThreadSynhronization()
{
    //dtor
}

void cThreadSynhronization::EnterCriticalSection()
{
    pthread_mutex_lock( &mutex );
}

void cThreadSynhronization::LeaveCriticalSection()
{
    pthread_mutex_unlock( &mutex );
}
