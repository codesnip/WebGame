#ifndef WEBGAME_H
#define WEBGAME_H


class cWebGame
{
    public:
        cWebGame()   { Init(); }
        ~cWebGame()  { Destruct(); }
    protected:
        void Init();
        void Destruct();
        void MainLoop();
    private:
};

#endif // WEBGAME_H
