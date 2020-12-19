#pragma once
#include "stdafx.h"
#define SEPSTREMP  "\n;------------------------------\n"
#define SEPSTR(x)  "\n;----------- " + string(x) + " ------------\n"





namespace Gener
{
	bool CodeGeneration(Lex::LEX& tables, Parm::PARM& parm, Log::LOG& log);
};