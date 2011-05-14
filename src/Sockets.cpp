#include "../include/Sockets.h"
#include "../include/OutputDevice.h"
#include "../include/ThreadSynhronization.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
//#include <sys/types.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>

cSockets::cSockets(cOutputDevice * OutputDevice)
{
    //ctor
Cliets = new cIntConnectedList(MAX_NUM_CLIENTS);
TempForAddingToEpoll.events = EPOLLIN | EPOLLET; // Задаем какие события будем улавливать с помощю epool от слушающего сокета
    cSockets::OutputDevice = OutputDevice;
    ListenerSocket = -1;
    CreateListeningSocket();
}

cSockets::~cSockets()
{
    //dtor
    delete Cliets;
}

void cSockets::CreateListeningSocket()
{

    OutputDevice->Output( "----Creating listener socket.----\n" );

    OutputDevice->Output( "1: Creating socket for listenig.\n" );
    if ( (ListenerSocket = socket(AF_INET, SOCK_STREAM, 0) ) == -1 ) { // Todo   close created socket
        OutputDevice->Output( "1: Error creating socket for listenig. Exiting.\n" );
        return;
    }
    OutputDevice->Output( "1: Socket for listening created. Socket no %d\n\n", ListenerSocket );

OutputDevice->Output("2: Setting socket to non blocking mode.\n");

  fcntl(ListenerSocket,F_SETFL,fcntl(ListenerSocket,F_GETFL,0) | O_NONBLOCK);
OutputDevice->Output("2: Setting socket to non blocking mode done.\n\n");

    OutputDevice->Output("3: Setting SO_REUSEADDR.\n");
    int yes=1;
    if ( setsockopt( ListenerSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int) ) == -1 ) {
        OutputDevice->Output("3: Can't set SO_REUSEADDR. Exiting.\n");
        CloseSocket(ListenerSocket);
        return;
    }
    OutputDevice->Output("3: SO_REUSEADDR set.\n\n");

    OutputDevice->Output("4: Binding.\n");
    sockaddr_in ServerAdress;
    ServerAdress.sin_family = AF_INET;
    ServerAdress.sin_addr.s_addr = INADDR_ANY;
    ServerAdress.sin_port = htons(SERVER_PORT);
    memset(&(ServerAdress.sin_zero), '\0', 8);
    if ( bind(ListenerSocket, (sockaddr *)&ServerAdress, sizeof(ServerAdress)) == -1 ) {
        OutputDevice->Output("4: Error binding. Exiting.\n");
        CloseSocket( ListenerSocket );
        return;
    }
    OutputDevice->Output("4: Binding done.\n\n");

    OutputDevice->Output( "5: Setting socket to listen.\n" );
    if (listen(ListenerSocket, MAX_NUM_CLIENTS) == -1) {
       OutputDevice->Output( "5: Error setting socket to listen. Exiting.\n" );
       CloseSocket( ListenerSocket );
       return;
    }
    OutputDevice->Output("5: Setting socket to listen done.\n\n");

    OutputDevice->Output( "6: Creating epoll.\n" );
    EpollDescriptor = epoll_create(MAX_NUM_CLIENTS);
    if(EpollDescriptor <= 0)
    {
        OutputDevice->Output( "6: Error creating epoll. Exiting.\n" );
        return;
    }
    OutputDevice->Output( "6: Epoll creation done. Epoll ID = %d\n\n", EpollDescriptor );

    OutputDevice->Output( "7: Adding listener to epoll.\n" );
    TempForAddingToEpoll.data.fd = ListenerSocket;
    if( epoll_ctl(EpollDescriptor, EPOLL_CTL_ADD, ListenerSocket, &TempForAddingToEpoll) < 0 )
    {
        OutputDevice->Output( "7: Error adding listener to epoll. Exiting.\n" );
        return;
    }
    OutputDevice->Output( "7: Adding listener to epoll done.\n\n" );

    OutputDevice->Output( "----Creating listener socket done.----\n\n" );
}


void cSockets::CloseSocket(int SocketNo)
{
    if( SocketNo == -1 ) return;

    if( SocketNo == ListenerSocket )
    {
        OutputDevice->Output("Closing socket no %d\(Listener socket\).\n", SocketNo);
    }else
    {
         OutputDevice->Output("Closing socket no %d.\n", SocketNo);
    }

    close( SocketNo );
}


 void cSockets::MainLoop()
 {
     int EpollEventsCount, i, Client;
     sockaddr_in IncomingClientAdress;
     socklen_t socklen;
     socklen = sizeof(struct sockaddr_in);
     while(1)
     {
        EpollEventsCount = epoll_wait(EpollDescriptor, ForAllEvents, MAX_NUM_CLIENTS, EPOLL_RUN_TIMEOUT);
        for(i = 0; i < EpollEventsCount ; i++)
        {
            if(ForAllEvents[i].data.fd == ListenerSocket)
            {
                // К нам подключился новый клиент
                Client = accept(ListenerSocket, (struct sockaddr *) &IncomingClientAdress, &socklen);
                fcntl(Client,F_SETFL,fcntl(Client,F_GETFL,0) | O_NONBLOCK);
                TempForAddingToEpoll.data.fd = Client;
                if ( epoll_ctl(EpollDescriptor, EPOLL_CTL_ADD, Client, &TempForAddingToEpoll) < 0 )
                {
                    OutputDevice->Output( "Error adding new client to epoll.\n" );
                }
                // Отправим приветствие клиенту
                {
                    char message[1024];
                    bzero(message, 1024);
                    sprintf(message, "Welcome to chat. Your ID is %d.\n", Client);
                    if( send(Client, message, 1024, 0) < 0) OutputDevice->Output( "Error sending welcome message to client.\n" );
                }

            }else
            {
                // Клиент прислал данные
                HandleDataFromClient(ForAllEvents[i].data.fd);
            }

        }
     }
 }

#define BUF_SIZE 1024
void cSockets::HandleDataFromClient( int ClientID )
{
    //Пришли данные от клиента
       int NumRecievedBytes;

       char buf[BUF_SIZE], message[BUF_SIZE];
       bzero(buf, BUF_SIZE);
       bzero(message, BUF_SIZE);

      NumRecievedBytes = recv(ClientID, buf, BUF_SIZE, 0);

      if ( NumRecievedBytes == 0 )
      {
          // Клиент закрыл соединение
            CloseSocket( ClientID );
      }else
      {
          // К нам пришли реальные данные от клиента


      }
}
