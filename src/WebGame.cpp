#include "../include/WebGame.h"
#include "../include/Sockets.h"



void cWebGame::Init()
{
    //
    ServerIsRunning = true;
    OutputDevice = new cOutputDevice;
    OutputDevice->Output( "Starting server...\n" );
    Sockets = new cSockets(OutputDevice);
}

void cWebGame::Destruct()
{
    //
    ServerIsRunning = false;
    delete Sockets;
    delete OutputDevice; // should be last
}

bool cWebGame::MainLoop()
{
    //



return true;
}


