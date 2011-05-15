/*
Copyright (C) 2011 WebGame project.
*/

#ifndef CSOCKETS_H
#define CSOCKETS_H
#include "../include/OutputDevice.h"
#include <stdlib.h>  //for timeval
#include "../include/ThreadSynhronization.h"

#include <sys/epoll.h>
#include "../include/IntConnectedList.h"




#define SERVER_PORT 8080
#define MAX_NUM_CLIENTS 10000
#define EPOLL_RUN_TIMEOUT -1

#define STR_NOONE_CONNECTED "Noone connected to server except you!"
#define STR_MESSAGE "Client #%d>> %s"
class cSockets
{
    public:
       cSockets(cOutputDevice * OutputDevice);
        ~cSockets();
        void CreateListeningSocket();
        void MainLoop();
    protected:

    private:

epoll_event TempForAddingToEpoll;
epoll_event ForAllEvents[MAX_NUM_CLIENTS];
int EpollDescriptor;

    cOutputDevice * OutputDevice;
    int ListenerSocket;
    void HandleDataFromClient( int ClientID );
    void CloseSocket(int SocketNo);
    cIntConnectedList * Clients;
};

#endif // CSOCKETS_H
