/*
Copyright (C) 2011 Tech1 Game Engine.
*/


#include <stdlib.h>
#include "../include/FileIO.h"

void cFile::CloseFile()
{
    fclose( file );
    FileToWorkWith = NULL;
}


void cFile::OpenFile(char * FileName, char * mode)
{
    FileToWorkWith = FileName;
    file = fopen( FileToWorkWith, mode );
}


void cFile::PutDataToFile (char * Data, int Count)
{
//fputs( Data, file );
    fwrite(Data, 1, Count, file);
}


void cFile::ReadFile(char * Data, unsigned int NumDataToRead)
{
    fread((void *)Data,NumDataToRead,1, file);
}


unsigned cFile::GetFileSizez(char * FileName)
{
    FILE *fin;
    fin = fopen(FileName, "rb");
    if(fin == 0) return ERROR_OPEN_FILE;
    unsigned int size;
    fseek(fin, 0, SEEK_END);
    size = ftell(fin);
    fseek(fin, 0, SEEK_SET);
    fclose( fin );
    return size;
}


void cFile::LoadFile(char * FileName, char ** DataToStore)
{
    //
    int FileSize = GetFileSizez(FileName);
    if(FileSize == ERROR_OPEN_FILE)
    {
        *DataToStore = (char *)ERROR_OPEN_FILE;
        return;
    }else if(FileSize == 0)
    {
        *DataToStore = 0;
        return;
    }
    OpenFile(FileName, "rb");
    *DataToStore = new char[FileSize+1];
    ReadFile(*DataToStore, FileSize);
    *DataToStore[FileSize]=0;
    CloseFile();
}


cFile::cFile()
{
    FileToWorkWith = NULL;
}


cFile::~cFile()
{
    if(FileToWorkWith)
    fclose( file );
}
