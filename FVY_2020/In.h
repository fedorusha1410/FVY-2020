#pragma once
#include "stdafx.h"

#define IN_MAX_LEN_TEXT 1024*1024				//максимальный размер исходного кода = 1МБ
#define IN_CODE_ENDL '\n'						//символ коцна строки
#define FREE_SPACE ' '
#define SEPARATOR '|'
#define IN_CODE_QUOTE '\"'
#define IN_CODE_NULL  '\0'

#define MAX_LEN_BUFFER  2048
#define IN_CODE_TILDA	'~'
#define IN_CODE_NOT_DOUBLE_QUOTE '\''


//таблица проверки входной информации, индекс = код (Windows -1251) символа
//значение IN::F -  запрещенный симовл, IN::T - разрешенных символ, IN::I - игнорировать ( не вводить), E - выражения, L - литералы, S - пробел
// если 0 <- значение < 256 - то вводится данное значение


#define IN_CODE_TABLE {\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::P, IN::N, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::P, IN::S, IN::Q, IN::T,  IN::F, IN::S, IN::S, IN::F,   IN::S, IN::S, IN::S, IN::S,  IN::S, IN::S, IN::T, IN::S,\
	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::S, IN::S, IN::S, IN::T,\
	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::K, IN::S, IN::T, IN::T,\
	IN::F, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T,  IN::T, IN::T, IN::T, IN::T,   IN::T, IN::T, IN::T, IN::S,  IN::T, IN::S, IN::QQ, IN::T,\
	\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,\
	IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F,   IN::F, IN::F, IN::F, IN::F,  IN::F, IN::F, IN::F, IN::F \
}

namespace In
{
	struct InWord
	{
		char word[MAX_LEN_BUFFER];	// слово
		int line;		// строка в исходном тексте
		static int size;// количество слов
	};
	struct IN
	{
		/*
		S - ( ) [ ] # < > ! & * + - = , ;
		P - пробел, табуляция
		N - новая строка
		F - запрещённый
		T - разрешённый
		I - игнорируемый
		Q - "
		QQ - ~
		COM - комментарий
		*/
		enum { T = 1024, F = 2048, I = 4096, S, Q, P, N, QQ, K };
		int size = 0;
		int lines = 1;
		int ignor = 0;
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];		//Windows 1251
		int code[256] = IN_CODE_TABLE;				//таблица проверки I,T,F новое значение
		int positionArr;
		InWord* words;
	};

	struct Flags {
		bool flag_space = false;
		bool flag_expression = false;
		bool flag_literal = false;
		bool flag_separator = false;
		bool _literal = false;
	};

	IN getin(wchar_t infile[], std::ostream* stream);
	void addWord(InWord* words, char* word, int line);
	InWord* getWordsTable(std::ostream* stream, unsigned char* text, int* code, int textSize);
	void printTable(InWord* table);
}