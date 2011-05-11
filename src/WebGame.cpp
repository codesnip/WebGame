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


void cWebGame::StartMainLoop()
{
    OutputDevice->Output("Starting main loop...\n");
    Sockets->MainLoop();
    OutputDevice->Output("Main loop ended...\n");
}



