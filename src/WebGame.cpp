/*
Copyright (C) 2011 WebGame project.
*/

#include "../include/ThreadSynhronization.h"
#include "../include/WebGame.h"
#include "../include/Sockets.h"


void cWebGame::Init()
{
    //
    ServerIsRunning = true;
    ThreadSynhronization = new cThreadSynhronization;
    OutputDevice = new cOutputDevice( ThreadSynhronization );
    OutputDevice->Output( "Starting server...\n" );
    Sockets = new cSockets( OutputDevice );

}

void cWebGame::Destruct()
{
    //
    ServerIsRunning = false;
    delete Sockets;
    delete ThreadSynhronization;
    delete OutputDevice; // should be last
}


void cWebGame::StartMainLoop()
{
    OutputDevice->Output("Starting main loop...\n");
    Sockets->MainLoop();
    OutputDevice->Output("Main loop ended...\n");
}

