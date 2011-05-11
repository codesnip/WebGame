#ifndef WEBGAME_H
#define WEBGAME_H
#include "../include/OutputDevice.h"
#include "../include/Sockets.h"

class cWebGame
{
    public:
        cWebGame()   { Init(); }
        ~cWebGame()  { Destruct(); }

        bool MainLoop();
        void CloseSocket(int SocketNo);

    protected:
        void Init();
        void Destruct();

        bool ServerIsRunning;

        cOutputDevice * OutputDevice;
        cSockets      * Sockets;
    private:
};

#endif // WEBGAME_H
