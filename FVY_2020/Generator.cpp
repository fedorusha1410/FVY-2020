#include "stdafx.h"
#include <string>
#include "Generator.h"

using namespace std;
#define BEGIN ".586\n"\
".model flat, stdcall\n"\
"includelib libucrt.lib\n"\
"includelib kernel32.lib\n"\
"includelib \"..\\Debug\\MyLib.lib\"\n"\
"ExitProcess PROTO:DWORD \n"\
".stack 4096\n"

#define END "call system_pause"\
				"\npush 0"\
				"\ncall ExitProcess"\
				"\nSOMETHINGWRONG:"\
				"\npush offset null_division"\
				"\ncall outstrline\n"\
				"call system_pause"\
				"\npush -1"\
				"\ncall ExitProcess"\
				"\nEXIT_OVERFLOW:"\
				"\npush offset overflow"\
				"\ncall outstrline\n"\
				"call system_pause"\
				"\npush -2"\
				"\ncall ExitProcess"\
				"\nmain ENDP\nend main"


#define EXTERN "\n outnum PROTO : DWORD\n"\
"\n outstr PROTO : DWORD\n"\
"\n outstrline PROTO : DWORD\n"\
"\n outnumline PROTO : DWORD\n"\
"\n system_pause PROTO \n"\
"\n lenght PROTO  : DWORD\n"\
"\n power PROTO : DWORD, : DWORD\n"


#define ITENTRY(x)  lex.idtable.table[lex.lextable.table[x].idxTI]
#define LEXEMA(x)   lex.lextable.table[x].lexema
namespace Gener
{

	bool CodeGeneration(Lex::LEX& lex, Parm::PARM& parm, Log::LOG& log)
	{
		bool gen_ok;
		ofstream ofile(parm.out);
		ofile << BEGIN;
		ofile << EXTERN;
		ofile << ".const\n null_division BYTE 'ERROR: DIVISION BY ZERO', 0\n overflow BYTE 'ERROR: VARIABLE OVERFLOW', 0 \n";
		int conditionnum = 0, cyclenum = 0;
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idtype == IT::L)
			{
				ofile << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].iddatatype == IT::SYM)
				{
					ofile << " BYTE \'" << lex.idtable.table[i].value.symbol << "\', 0\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::STR)
				{
					ofile << " BYTE \'" << lex.idtable.table[i].value.vstr.str << "\', 0\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::UB)
				{
					ofile << " SDWORD " << lex.idtable.table[i].value.vbyte << endl;
				}
			}
		}
		ofile << ".data\n";
		for (int i = 0; i < lex.idtable.size; i++)
		{
			if (lex.idtable.table[i].idtype == IT::IDTYPE::V)
			{
				ofile << "\t" << lex.idtable.table[i].id;
				if (lex.idtable.table[i].iddatatype == IT::SYM)
				{
					ofile << " DWORD ?\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::STR)
				{
					ofile << " DWORD ?\n";
				}
				if (lex.idtable.table[i].iddatatype == IT::UB)
				{
					ofile << " SDWORD 0\n";
				}
			}
		}

		stack<string> stk;
		stack<IT::Entry> temp;
		string cyclecode = "", func_name = "";					// ��� ��������� �������
		bool flag_cycle = false,					// ������ �����?
			flag_main = false,
			flag_is = false,					// if
			flag_true = false,
			flag_false = false,
			flag_return = false;

		ofile << "\n.code\n\n";
		for (int i = 0; i < lex.lextable.size; i++)
		{
			switch (lex.lextable.table[i].lexema)
			{
			case LEX_FUNCTION:
			{
				i++;
				flag_return = false;
				ofile << (func_name = ITENTRY(i).id) << " PROC ";
				int j = i + 2;
				while (LEXEMA(j) != LEX_RIGHTTHESIS) // ���� ��������� �� ��������
				{
					if (lex.lextable.table[j].lexema == LEX_ID) // ��������
					{
						ofile << lex.idtable.table[lex.lextable.table[j].idxTI].id << " : ";
						if (ITENTRY(j).iddatatype == IT::IDDATATYPE::UB)
						{
							ofile << " SDWORD ";
						}
						else if (ITENTRY(j).iddatatype == IT::IDDATATYPE::SYM)
						{
							ofile << " DWORD ";
						}
						else
						{
							ofile << " DWORD ";
						}
					}
					if (LEXEMA(j) == LEX_COMMA)
					{
						ofile << ", ";
					}
					j++;
				}
				ofile << endl;
				break;
			}
			case LEX_MAIN:
			{
				flag_main = true;
				ofile << "main PROC\n";
				break;
			}
			case LEX_RETURN:
			{
				if (flag_main)
				{
					Log::WriteError(log.stream, Error::GetError(320, lex.lextable.table[i].sn, 0));
					ofile.close();
					return false;
				}
				if (LEXEMA(i + 1) != LEX_SEPARATOR)
				{
					if (LEXEMA(i + 1) != LEX_LEFTHESIS && (ITENTRY(i + 1).iddatatype == IT::IDDATATYPE::UB || ITENTRY(i + 1).idtype == IT::IDTYPE::P || ITENTRY(i + 1).idtype == IT::IDTYPE::V))
						ofile << "\tmov eax, " << ITENTRY(i + 1).id << "\n";
					else if (LEXEMA(i + 1) != LEX_LEFTHESIS)
						ofile << "\tmov eax,offset " << ITENTRY(i + 1).id << "\n";
					else if (LEXEMA(i + 2) != LEX_MINUS)
						ofile << "\tmov eax, " << ITENTRY(i + 2).id << "\n";
					else
					{
						ofile << "\tmov eax, 0\n";
						ofile << "\tmov ebx," << ITENTRY(i + 3).id;
						ofile << "\n\tsub eax, ebx\n";
					}
				}
				ofile << "\tret\n";
				if (!flag_return)
				{
					ofile << "\nSOMETHINGWRONG:"\
						"\npush offset null_division"\
						"\ncall outstrline\n"\
						"call system_pause"\
						"\npush -1"\
						"\ncall ExitProcess\n"\
						"\nEXIT_OVERFLOW:"\
						"\npush offset overflow"\
						"\ncall outstrline\n"\
						"call system_pause"\
						"\npush -2"\
						"\ncall ExitProcess\n";
					flag_return = true;
				}
				break;
			}
			case LEX_BRACELET:
			{
				if (flag_main)
					break;
				ofile << func_name + " ENDP\n";
				break;
			}
			case LEX_EQUAL:
			{
				int result_position = i - 1;
				while (lex.lextable.table[i].lexema != LEX_SEPARATOR)
				{

					switch (LEXEMA(i))
					{
					case LEX_STDFUNC:
					case LEX_LITERAL:
					{
						if (ITENTRY(i).iddatatype == IT::IDDATATYPE::UB)
						{
							ofile << "\tpush " << ITENTRY(i).id << endl;
							stk.push(lex.idtable.table[lex.lextable.table[i].idxTI].id);
							break;
						}
						else
						{
							ofile << "\tpush offset " << ITENTRY(i).id << endl;
							stk.push("offset" + (string)lex.idtable.table[lex.lextable.table[i].idxTI].id);
							break;
						}
					}
					case LEX_ID:
					{

						ofile << "\tpush " << ITENTRY(i).id << endl;
						stk.push(lex.idtable.table[lex.lextable.table[i].idxTI].id);
						break;
					}
					case LEX_SUBST:
					{
						for (int j = 1; j <= (LEXEMA(i + 1) - '0') + 1; j++)
						{
							ofile << "\tpop edx\n";

						}
						for (int j = 1; j <= lex.lextable.table[i + 1].lexema - '0'; j++)
						{
							ofile << "\tpush " << stk.top() << endl;
							stk.pop();
						}
						ofile << "\t\tcall " << ITENTRY(i - (lex.lextable.table[i + 1].lexema - '0') - 1).id << "\n\tpush eax\n";
						break;
					}
					case LEX_TILDA:
					{
						ofile << "\tmov eax, 0\n\tpop ebx\n";
						ofile << "\tsub eax, ebx\n\tpush eax\n";
						break;
					}
					case LEX_STAR:
					{
						ofile << "\tpop eax\n\tpop ebx\n";
						ofile << "\timul ebx\n\tjo EXIT_OVERFLOW\n\tpush eax\n";

						break;
					}

					case LEX_PLUS:
					{
						ofile << "\tpop eax\n\tpop ebx\n";
						ofile << "\tadd eax, ebx\n\tjo EXIT_OVERFLOW\n\tpush eax\n";
						break;
					}
					case LEX_MINUS:
					{
						if (LEXEMA(i - 2) == LEX_EQUAL)
						{
							ofile << "\tmov eax, 0\n\tpop ebx\n";
							ofile << "\tsub eax, ebx\n\tpush eax\n";
							break;
						}
						ofile << "\tpop ebx\n\tpop eax\n";
						ofile << "\tsub eax, ebx\n\tpush eax\n";
						break;
					}
					case LEX_DIRSLASH:
					{
						ofile << "\tpop ebx\n\tpop eax\n";
						ofile << "\tcmp ebx,0\n"\
							"\tje SOMETHINGWRONG\n";
						ofile << "\tcdq\n";
						ofile << "\tidiv ebx\n\tpush eax\n";
						break;
					}
					case LEX_PROCENT:
					{

						ofile << "\tpop ebx\n\tpop eax\n";
						ofile << "\tcmp ebx,0\n"\
							"\tje SOMETHINGWRONG\n";
						ofile << "\tcdq\n";
						ofile << "\tidiv ebx\n\tpush edx\n";
						break;
					}
					}
					i++;
				}
				ofile << "\tpop " << ITENTRY(result_position).id << "\n";
				ofile << endl;
				break;
			}
			case LEX_ID:
			{
				if (LEXEMA(i + 1) == LEX_LEFTHESIS && LEXEMA(i - 1) != LEX_FUNCTION
					&& lex.lextable.table[i].sn > lex.lextable.table[i - 1].sn)
				{
					for (int j = i + 1; LEXEMA(j) != LEX_RIGHTTHESIS; j++)
					{
						if (LEXEMA(j) == LEX_ID || LEXEMA(j) == LEX_LITERAL)
							temp.push(ITENTRY(j)); // // ��������� ���� � ������ �������	
					}
					while (!temp.empty())
					{
						if (temp.top().idtype == IT::IDTYPE::L && (temp.top().iddatatype == IT::IDDATATYPE::STR || temp.top().iddatatype == IT::IDDATATYPE::SYM))
							ofile << "\npush offset " << temp.top().id << "\n";
						else  ofile << "\npush " << temp.top().id << "\n";
						temp.pop();
					}
					ofile << "\ncall " << ITENTRY(i).id << "\n";
				}
				break;
			}
			/*case LEX_INCR:
			{
				ofile << "\tmov eax," << ITENTRY(i - 1).id << "\n";
				ofile << "\tmov ebx," << ITENTRY(i + 1).id << "\n";
				switch (ITENTRY(i).id[1])
				{
				case LEX_PLUS:
				{
					ofile << "\tadd eax, ebx\n\tjo EXIT_OVERFLOW\n";
					break;
				}
				case LEX_MINUS:
				{
					ofile << "\tsub eax, ebx\n\tjo EXIT_OVERFLOW\n";
					break;
				}
				case LEX_STAR:
				{
					ofile << "\timul ebx\n\tjo EXIT_OVERFLOW\n";
					break;
				}
				case LEX_DIRSLASH:
				{
					ofile << "\tcmp ebx,0\n"\
						"\tje SOMETHINGWRONG\n";
					ofile << "\tcdq\n";
					ofile << "\tidiv ebx\n";
					break;
				}
				}
				ofile << "\tmov " << ITENTRY(i - 1).id << " , eax\n";
				break;
			}*/
			case LEX_OUTLINE: // ������� ������ 
			{
				switch (ITENTRY(i + 1).iddatatype)
				{
				case IT::IDDATATYPE::UB:
					ofile << "\npush " << ITENTRY(i + 1).id << "\ncall outnumline\n";
					break;
				case IT::IDDATATYPE::SYM:
				case IT::IDDATATYPE::STR:
					if (ITENTRY(i + 1).idtype == IT::IDTYPE::L)
						ofile << "\npush offset " << ITENTRY(i + 1).id << "\ncall outstrline\n";
					else ofile << "\npush " << ITENTRY(i + 1).id << "\ncall outstrline\n";
					break;
				}
				break;
			}
			case LEX_OUTPUT: // �����
			{
				switch (ITENTRY(i + 1).iddatatype)
				{
				case IT::IDDATATYPE::UB:
					ofile << "\npush " << ITENTRY(i + 1).id << "\ncall outnum\n";
					break;
				case IT::IDDATATYPE::SYM:
				case IT::IDDATATYPE::STR:
					if (ITENTRY(i + 1).idtype == IT::IDTYPE::L)
						ofile << "\npush offset " << ITENTRY(i + 1).id << "\ncall outstr\n";
					else ofile << "\npush " << ITENTRY(i + 1).id << "\ncall outstr\n";
					break;
				}
				break;
			}
			case LEX_IF: // �������
			{
				conditionnum++;
				flag_is = true;
				char* right = nullptr, * wrong = nullptr;
				int j = i;
				while (LEXEMA(j) != LEX_SQ_RBRACELET)
				{
					if (LEXEMA(j) == LEX_THEN)
					{
						flag_true = true;
					}
					else if (LEXEMA(j) == LEX_ELSE)
					{
						flag_false = true;
					}
					j++;
				}
				if (LEXEMA(j + 1) == LEX_THEN || LEXEMA(j + 1) == LEX_ELSE)
				{
					flag_true = true;
					flag_false = true;
				}
				switch (LEXEMA(i + 2))
				{
				case LEX_MORE:
					right = (char*)"jg";  wrong = (char*)"jle";
					break;
				case LEX_LESS:
					right = (char*)"jl";  wrong = (char*)"jge";
					break;
				case LEX_EQUALS:
					right = (char*)"jz";  wrong = (char*)"jnz";
					break;
				case LEX_NOTEQUALS:
					right = (char*)"jnz";  wrong = (char*)"jz";
					break;
				}
				if (ITENTRY(i + 1).iddatatype == IT::IDDATATYPE::UB)
				{
					ofile << "\tmov edx, " << ITENTRY(i + 1).id << "\n\tcmp edx, " << ITENTRY(i + 3).id << "\n";


				}
				if (ITENTRY(i + 1).iddatatype == IT::IDDATATYPE::SYM || ITENTRY(i + 1).iddatatype == IT::IDDATATYPE::STR)
				{
					if (ITENTRY(i + 1).idtype == IT::IDTYPE::V || ITENTRY(i + 1).idtype == IT::IDTYPE::P)
						ofile << "\n\tmov esi, " << ITENTRY(i + 1).id;
					else
						ofile << "\n\tmov esi, offset " << ITENTRY(i + 1).id;

					if (ITENTRY(i + 3).idtype == IT::IDTYPE::V || ITENTRY(i + 3).idtype == IT::IDTYPE::P)
						ofile << "\n\tmov edi, " << ITENTRY(i + 3).id;
					else
						ofile << "\n\tmov edi, offset " << ITENTRY(i + 3).id;

					if (ITENTRY(i + 1).idtype == IT::IDTYPE::V || ITENTRY(i + 1).idtype == IT::IDTYPE::P)
						ofile << "\n\t push " << ITENTRY(i + 1).id;
					else
						ofile << "\n\t push offset " << ITENTRY(i + 1).id;

					ofile << "\n\t call lenght";
					ofile << "\n\t mov ebx,eax";

					if (ITENTRY(i + 1).idtype == IT::IDTYPE::V || ITENTRY(i + 3).idtype == IT::IDTYPE::P)
						ofile << "\n\t push " << ITENTRY(i + 3).id;
					else
						ofile << "\n\t push offset " << ITENTRY(i + 3).id;

					ofile << "\n\t call lenght";
					ofile << "\n\t cmp ebx,eax";
					if (flag_false)
						ofile << "\n\t" << wrong << " wrong" << conditionnum;
					else
						ofile << "\n\t jne next" << conditionnum;
					ofile << "\n\t mov ecx,eax";
					ofile << "\n\t repe cmpsb\n";
				}
				if (flag_true)
					ofile << "\t" << right << " right" << conditionnum << "\n";
				if (flag_false)
					ofile << "\t" << wrong << " wrong" << conditionnum << "\n";
				ofile << "\t" << "jmp next" << conditionnum << "\n";
				i += 2;
				break;
			}
			case LEX_THEN:
			{
				ofile << "right" << conditionnum << ":";
				break;
			}
			case LEX_ELSE:
			{
				ofile << "wrong" << conditionnum << ":";
				break;
			}
			case LEX_SQ_RBRACELET:
			{
				if (flag_cycle && !flag_is)
				{
					flag_cycle = false;
					ofile << cyclecode;
					ofile << "continue" << cyclenum << ":";
				}
				if (flag_is)
				{
					if (LEXEMA(i + 1) != LEX_THEN && LEXEMA(i + 1) != LEX_ELSE)
					{
						ofile << "\nnext" << conditionnum << ":";
						flag_is = false;
						flag_true = false;
						flag_false = false;
					}
					else
					{
						ofile << "\tjmp next" << conditionnum << "\n\n";
					}
				}
				break;
			}
			case LEX_WHILE:
			{
				flag_cycle = true;
				cyclecode.clear();
				cyclenum++;
				char* right = nullptr, * wrong = nullptr;
				switch (LEXEMA(i + 2))
				{
				case LEX_MORE:
					right = (char*)"jg";  wrong = (char*)"jle";
					break;
				case LEX_LESS:
					right = (char*)"jl";  wrong = (char*)"jge";
					break;
				case LEX_EQUALS:
					right = (char*)"jz";  wrong = (char*)"jnz";
					break;
				case LEX_NOTEQUALS:
					right = (char*)"jnz";  wrong = (char*)"jz";
					break;
				}
				if (ITENTRY(i + 1).iddatatype == IT::IDDATATYPE::UB)
				{
					cyclecode = "\tmov edx, " + (string)ITENTRY(i + 1).id + "\n\tcmp edx, " + (string)ITENTRY(i + 3).id + "\n";
				}
				if (ITENTRY(i + 1).iddatatype == IT::IDDATATYPE::SYM || ITENTRY(i + 1).iddatatype == IT::IDDATATYPE::STR)
				{
					if (ITENTRY(i + 1).idtype == IT::IDTYPE::V || ITENTRY(i + 1).idtype == IT::IDTYPE::P)
						cyclecode += "\tmov esi, " + (string)ITENTRY(i + 1).id;
					else
						cyclecode += "\tmov esi, offset" + (string)ITENTRY(i + 1).id;
					if (ITENTRY(i + 3).idtype == IT::IDTYPE::V || ITENTRY(i + 3).idtype == IT::IDTYPE::P)
						cyclecode += "\n\tmov edi, " + (string)ITENTRY(i + 3).id + "\n";
					else
						cyclecode += "\n\tmov edi, offset" + (string)ITENTRY(i + 3).id + "\n";

					if (ITENTRY(i + 1).idtype == IT::IDTYPE::V || ITENTRY(i + 1).idtype == IT::IDTYPE::P)
						cyclecode += "\n\t push " + (string)ITENTRY(i + 1).id;
					else
						cyclecode += "\n\t push offset" + (string)ITENTRY(i + 1).id;

					cyclecode += "\n\t call lenght";
					cyclecode += "\n\t mov ebx,eax";

					if (ITENTRY(i + 3).idtype == IT::IDTYPE::V || ITENTRY(i + 3).idtype == IT::IDTYPE::P)
						cyclecode += "\n\t push " + (string)ITENTRY(i + 3).id;
					else
						cyclecode += "\n\t push offset" + (string)ITENTRY(i + 3).id;
					cyclecode += "\n\t call lenght";
					cyclecode += "\n\t cmp ebx,eax";
					cyclecode += "\n\t" + (string)wrong + " continue" + std::to_string(cyclenum);
					cyclecode += "\n\t mov ecx,eax";
					cyclecode += "\n\t repe cmpsb\n";
				}
				cyclecode += "\t" + (string)right + " cycle" + std::to_string(cyclenum) + "\n";
				ofile << cyclecode;
				ofile << "\t" << "jmp continue" << cyclenum << "\n";
				i += 2;
				break;
			}
			case LEX_DO:
			{
				ofile << " cycle" << cyclenum << ":";
			}

			}
		}
		ofile << END;
		ofile.close();
		return true;
	};
}