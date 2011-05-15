/*
Copyright (C) 2011 Tech1 Game Engine.
*/

#include <stdio.h>
#ifndef _FILEIO_
#define _FILEIO_

#define ERROR_OPEN_FILE 4294967295

class cFile
{
private:
	FILE *file;
public:
	char * FileToWorkWith;
	cFile();
	~cFile();
	void OpenFile(char * FileName, char * mode); // mode = "w" - Для записи в начало. "a" добавить   . mode = "r" - Для чтения     "r+b"  для чтения и записи
	void ReadFile(char * Data, unsigned int NumDataToRead);
    unsigned int GetFileSizez(char * FileName);
	void PutDataToFile (char * Data, int Count);
	void LoadFile(char * FileName, char ** DataToStore);
	void CloseFile();
};


#endif
