#ifndef CTHREADSYNHRONIZATION_H
#define CTHREADSYNHRONIZATION_H
#include <pthread.h>

class cThreadSynhronization
{
    public:
        cThreadSynhronization();
        ~cThreadSynhronization();

       void EnterCriticalSection();
       void LeaveCriticalSection();
    protected:
    pthread_mutex_t mutex;
    private:
};

#endif // CTHREADSYNHRONIZATION_H
