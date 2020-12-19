#pragma once
#include "stdafx.h"

#define IN_MAX_LEN_TEXT 1024*1024				//������������ ������ ��������� ���� = 1��
#define IN_CODE_ENDL '\n'						//������ ����� ������
#define FREE_SPACE ' '
#define SEPARATOR '|'
#define IN_CODE_QUOTE '\"'
#define IN_CODE_NULL  '\0'

#define MAX_LEN_BUFFER  2048
#define IN_CODE_TILDA	'~'
#define IN_CODE_NOT_DOUBLE_QUOTE '\''


//������� �������� ������� ����������, ������ = ��� (Windows -1251) �������
//�������� IN::F -  ����������� ������, IN::T - ����������� ������, IN::I - ������������ ( �� �������), E - ���������, L - ��������, S - ������
// ���� 0 <- �������� < 256 - �� �������� ������ ��������


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
		char word[MAX_LEN_BUFFER];	// �����
		int line;		// ������ � �������� ������
		static int size;// ���������� ����
	};
	struct IN
	{
		/*
		S - ( ) [ ] # < > ! & * + - = , ;
		P - ������, ���������
		N - ����� ������
		F - �����������
		T - �����������
		I - ������������
		Q - "
		QQ - ~
		COM - �����������
		*/
		enum { T = 1024, F = 2048, I = 4096, S, Q, P, N, QQ, K };
		int size = 0;
		int lines = 1;
		int ignor = 0;
		unsigned char* text = new unsigned char[IN_MAX_LEN_TEXT];		//Windows 1251
		int code[256] = IN_CODE_TABLE;				//������� �������� I,T,F ����� ��������
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