#ifndef CSOCKETS_H
#define CSOCKETS_H
#include "../include/OutputDevice.h"

#define SERVER_PORT 8080

class cSockets
{
    public:
       cSockets(cOutputDevice * OutputDevice);
        ~cSockets();
        void CreateListeningSocket();
    protected:

    private:
    cOutputDevice * OutputDevice;
    int ListenerSocket;
    void CloseSocket(int SocketNo);
};

#endif // CSOCKETS_H
