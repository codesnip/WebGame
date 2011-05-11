#include "../include/Sockets.h"
#include "../include/OutputDevice.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
//#include <sys/types.h>
#include <iostream>


cSockets::cSockets(cOutputDevice * OutputDevice)
{
    //ctor
   cSockets::OutputDevice = OutputDevice;
   ListenerSocket = -1;
   CreateListeningSocket();
}

cSockets::~cSockets()
{
    //dtor
}

void cSockets::CreateListeningSocket()
{
     OutputDevice->Output( "----Creating listener socket.----\n" );

    OutputDevice->Output( "1: Creating socket for listenig.\n" );
    if ( (ListenerSocket = socket(AF_INET, SOCK_STREAM, 0) ) == -1 ) { // Todo   close created socket
        OutputDevice->Output( "1: Error creating socket for listenig. Exiting.\n" );
        //return false;
    }
    OutputDevice->Output( "1: Socket for listening created. Socket no %d\n\n", ListenerSocket );

    OutputDevice->Output("2: Setting SO_REUSEADDR.\n");
    int yes=1;
    if ( setsockopt( ListenerSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int) ) == -1 ) {
        OutputDevice->Output("2: Can't set SO_REUSEADDR. Exiting.\n");
        CloseSocket(ListenerSocket);
       // return false;
    }
    OutputDevice->Output("2: SO_REUSEADDR set.\n\n");

    OutputDevice->Output("3: Binding.\n");
    sockaddr_in ServerAdress;
    ServerAdress.sin_family = AF_INET;
    ServerAdress.sin_addr.s_addr = INADDR_ANY;
    ServerAdress.sin_port = htons(SERVER_PORT);
    memset(&(ServerAdress.sin_zero), '\0', 8);
    if ( bind(ListenerSocket, (sockaddr *)&ServerAdress, sizeof(ServerAdress)) == -1 ) {
        OutputDevice->Output("3: Error binding. Exiting.\n");
        CloseSocket( ListenerSocket );
       // return false;
    }
    OutputDevice->Output("3: Binding done.\n\n");
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
