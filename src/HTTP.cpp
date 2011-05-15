#include "../include/HTTP.h"

void cHTTP::Reset()
{
    //ctor
    LastTokenStart = 0;
    LastTokenStartReadPos = 0;
    LastTokenSize = 0;
    Data = 0;
    ErrorLoading = false;
}


void cHTTP::LoadData( char * Data )
{
    //
    Reset();
    cHTTP::Data = Data;
}


void cHTTP::ProcessData()
{
    //
    int type = 0;
    char * Token;
    Token = GetNextTokenSkipSpacebar( Data ,type, LastTokenSize, LastTokenStartReadPos, LastTokenStart );
}


int cHTTP::ConvertTextToNumberInteger(char * Text, int size, int & LastCurNum) // size - размер текста без 0
{
    size--;
    int i = 0;
    int j;
    int CurNum;
    int RetValue=0;
    LastCurNum = 10;
	while(i!=size+1)
	{
		CurNum = ((int)Text[size-i] - (int)'0');
		for(j=0; j!=i; j++)
			{
				CurNum	*=	10;
				if(i == size) LastCurNum *= 10;
			}
		RetValue +=  CurNum;
		i++;
	}
    return RetValue;
}


float cHTTP::ConvertTextToNumberFloat(char * Text, int size)
{
    float ReturnValue;
    int i=0;
    int BeforeDot;
    int AfterDot;
    int LastCurNum;
    while(Text[i]!='.')
	{
		i++;

	}
    if(Text[0]=='-')
	{
		i--;
		BeforeDot = ConvertTextToNumberInteger(Text+1, i, LastCurNum);
		AfterDot = ConvertTextToNumberInteger(Text+1 + (char)i+(char)1, size - i-2,LastCurNum);
		ReturnValue =-(((float)AfterDot / (float)LastCurNum)+BeforeDot);
	}else
	{
		BeforeDot = ConvertTextToNumberInteger(Text, i,LastCurNum);
		AfterDot = ConvertTextToNumberInteger(Text + (char)i+(char)1, size - i - 1,LastCurNum);
		//cout << "L:" << LastCurNum << endl;
		ReturnValue = ((float)AfterDot / (float)LastCurNum)+BeforeDot;
	}

    return ReturnValue;
}

char * cHTTP::GetNextTokenSkipSpacebar(char * Data, int & type,int & LastTokenSize, int & LastTokenStartReadPos, int & LastTokenStart)
{
	char * ReturnData;
	do
	{
		ReturnData = GetNextToken(type, Data, LastTokenSize, LastTokenStartReadPos, LastTokenStart);
		if(type == 0) return 0;
	}
	while((type == SPACEBAR_OR_TAB));

    return ReturnData;
}

char * cHTTP::GetNextToken(int & type, char * ScriptData,int & LastTokenSize, int & LastTokenStartReadPos, int & LastTokenStart)
{
    char * ReturnData = ScriptData;
    LastTokenSize = Token(ScriptData,LastTokenStartReadPos+LastTokenStart+LastTokenSize, type, LastTokenStartReadPos, LastTokenStart);
    ReturnData+= LastTokenStart+LastTokenStartReadPos;

    return ReturnData;
}


int cHTTP::Token(char * Buffer, int  StartPos, int & type, int & LastTokenStartReadPos, int & LastTokenStart)
{
	LastTokenStartReadPos = StartPos;
	LastTokenStart = 0;
	bool wasDot = false;
	int size = 0;
	int ToExpect = 0;
	char * Token = Buffer+StartPos;
	type = 0;
	while (*Token)
	{
		if(*Token == 0)
		{ type = ToExpect;
			return size;
			break;
		}
		if((*Token == 10)||(*Token == 13))
		{

			switch(ToExpect)
			{
				case BIG_OR_SMALL_LETERS_AND_NUMBERS:
				type = ToExpect;
				return size;
				break;

				case  NUMBERS:
				type = ToExpect;
				return size;
				break;

				case  SPACEBAR_OR_TAB:
				type = ToExpect;
				return size;
				break;
			}

 			Token++;
			LastTokenStart++;
			continue;
		}
			if(!((*Token >= 'A' && *Token <= 'Z')||(*Token >= 'a' && *Token <= 'z')||(*Token >= '0' && *Token <= '9')||(*Token == ' ')||(*Token == '	')||(*Token == ';')||(*Token == '}')||(*Token == '{')||(*Token == '.')||(*Token == '-')||(*Token == '_')||(*Token == ':')||(*Token == '/'))) 	// Проверяем  разрешенный ли это стмвол
			{
					type = ToExpect;
					LastTokenStart = (unsigned int)Token;
					return -1;
			}
		switch(ToExpect)
		{
			case BIG_OR_SMALL_LETERS_AND_NUMBERS:
				if((*Token >= 'A' && *Token <= 'Z')||(*Token >= 'a' && *Token <= 'z')||(*Token >= '0' && *Token <= '9')||(*Token == '_')||(*Token == ':')||(*Token == '/')||(*Token == '.'))
				{
					size++;
					Token++;
					  //Если это больщая буква
					continue;
				}
				type = ToExpect;
				return size;
			break;

			case  SPACEBAR_OR_TAB:
				if((*Token == ' ')||(*Token == '	'))
				{
					size++;
					Token++;
					  //Если это больщая буква
					continue;
				}
				type = ToExpect;
				return size;
			break;

			case  NUMBERS:
				if((*Token >= '0' && *Token <= '9') || (*Token == '.'))
				{
					if(*Token == '.')
					{
						if(wasDot)
						{
					type = 0;
					LastTokenStart = (unsigned int)Token;
					return -1; // в числе не может быть больше 1й точки
						}else
						{
							wasDot = true;
						}
					}

					size++;
					Token++;
					  //Если это больщая буква
					continue;
				}else
				{
					if(*Token == '-')
					{
						type = 0;
						LastTokenStart = (unsigned int)Token;
						return -1; // После минуса не число
					}

				}
				type = ToExpect;
				return size;
			break;

				//if(
		case 0: // Первая буква
			{
				if ((*Token >= 'A' && *Token <= 'Z')||(*Token >= 'a' && *Token <= 'z'))
				{
					 ToExpect = BIG_OR_SMALL_LETERS_AND_NUMBERS;
					 type = BIG_OR_SMALL_LETERS_AND_NUMBERS;
				}
				if ((*Token >= '0' && *Token <= '9')||(*Token == '-'))
				{
					 ToExpect = NUMBERS;
					 type =	NUMBERS;
				}

				if (*Token == ' ')
				{
					ToExpect = SPACEBAR_OR_TAB; // Пробел
					type = SPACEBAR_OR_TAB;
				}
				if (*Token == '	')
				{
					ToExpect = SPACEBAR_OR_TAB; // Табуляция
					type = SPACEBAR_OR_TAB;
				}
				if (*Token == '{')
				{	type = 	OPEN_BRACKET;
					return 1;
				}
				if (*Token == '}')
				{	type = 	CLOSE_BRACKET;
					return 1;
				}
				if (*Token == ';')
				{	type = 	KOMA_DOT;
					return 1;
				}
				if (*Token == '.')
				{
					type = DOT;
					LastTokenStart = (unsigned int)Token;
					return -1;  //Точка не может быть первым символом
				}
				size = 1;
				Token++;
				continue;
				break;
			}
		}
	}
    if(type)
    {
        type = ToExpect;
    }else
    {
        type = END_EOF;
    }
    return size;
}
