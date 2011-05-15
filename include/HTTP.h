/*
Copyright (C) 2011 WebGame project.
*/

#ifndef CHTTP_H
#define CHTTP_H


enum Expecting
{
 BIG_OE_SMALL_LETERS = 1,
 NUMBERS,
 SPACEBAR_OR_TAB,
 OPEN_BRACKET,
 CLOSE_BRACKET,
 KOMA_DOT,
 BIG_OR_SMALL_LETERS_AND_NUMBERS,
 END_EOF,
 DOT
};

class cHTTP
{
    public:
        cHTTP() { Reset(); }
        ~cHTTP() { return; }

        void Reset();
        void LoadData( char * Data );
        void ProcessData();
        void LoadFromFile(char * FileName);
    protected:
    private:
    bool CmpString(char * Str1, char * Str2, unsigned int Str1Size);
    int ConvertTextToNumberInteger(char * Text, int size, int & LastCurNum); // size - размер текста без 0
    float ConvertTextToNumberFloat(char * Text, int size);
    char * GetNextTokenSkipSpacebar(char * Data, int & type,int & LastTokenSize, int & LastTokenStartReadPos, int & LastTokenStart);
    char * GetNextToken(int & type, char * ScriptData,int & LastTokenSize, int & LastTokenStartReadPos, int & LastTokenStart);
    int Token(char * Buffer, int  StartPos, int & type, int & LastTokenStartReadPos, int & LastTokenStart);


int LastTokenStart;
int LastTokenStartReadPos;
int LastTokenSize;
char * Data;
bool ErrorLoading;
};

#endif // CHTTP_H
