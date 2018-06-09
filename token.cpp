#include<map>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>
#include<list>
#include "token.h"
#include <cctype>
#include <vector>
void microsyntax::_Skip()
{
	
	while (std::isspace(_flow[index]))
	{
		if (_flow[index] == '\n')nowline++;
		++index;
	}
}


bool microsyntax::_Match(const std::string target)
{
	for (int i = index, j = 0; i < _flow.size(); )
	{
		if (_flow[i] == target[j])
		{
			++i; ++j;
		}
		else
		{
			return false;
		}
		if (j == target.size())
		{
			index = i;
			break;
		}
	}
	return true;
}

bool microsyntax::_IsSymbol()
{
	for (auto &p : _Symbollist)
	{
		if (_Match(p.first))
		{
			Word newword;
			newword.type = p.second;
			newword.str = p.first;
			newword.line = nowline;
			Words.push_back(newword);
			return true;
		}
	}
	return false;
}

bool microsyntax::_IsNumber()
{
	if (_flow[index] >= '0' &&_flow[index] <= '9')
	{
		index_now = index;
		std::string tmp = "";
		tmp += _flow[index];
		for (int i = index + 1; i < _flow.size(); )
		{
			if (_flow[i] >= '0' &&_flow[i] <= '9')
			{
				tmp += _flow[i];
				++i;
			}
			else
			{
				index = i;
				Word newword;
				newword.type = Type::Number;
				newword.str = tmp;
				newword.line = nowline;
				Words.push_back(newword);
				return true;
			}
		}
	}
	else
		return false;
}
bool microsyntax::_IsWord()
{
	if ((_flow[index] >= 'A' && _flow[index] <= 'Z') || (_flow[index] >= 'a' && _flow[index] <= 'z') || (_flow[index] == '_'))
	{
		index_now = index;
		std::string tmp = "";
		tmp += _flow[index];
		for (int i = index + 1; i < _flow.size();)
		{
			if ((_flow[i] >= 'A' && _flow[i] <= 'Z') || (_flow[i] >= 'a' && _flow[i] <= 'z') || (_flow[i] == '_')\
				|| (_flow[i] >= '0' &&_flow[i] <= '9'))
			{
				tmp += _flow[i];
				++i;
				//next letter
			}
			else
			{
				index = i;
				break;
			}
		}
		//	std::cout<<tmp<<std::endl;
		// This word is a keyword or an indentifier
		for (auto &p : _Keywordlist)
		{
			if (p.first == tmp)//is a key word
			{
				Word newword;
				newword.str = p.first;
				newword.type = p.second;
				newword.line = nowline;
				Words.push_back(newword);
				return true;
			}
		}
		//This is an identifier
		Word newword;
		newword.type = Type::Indentifier;
		newword.str = tmp;
		newword.line = nowline;
		Words.push_back(newword);
		return true;
	}
	else
	{
		return false;
	}
}

Type microsyntax::_NextWord()
{
	//skip spcaes
	_Skip();
	//Is end
	if (_flow[index] == '\0')
	{
		Word newword;
		newword.type = Type::Endmark;
		newword.str = "EOF";
		newword.line = nowline;
		Words.push_back(newword);
		return Type::Endmark;
	}

	if (_IsSymbol()) return Type::Leftbrac;//is symbol?
	else if (_IsNumber()) return Type::Number;
	else if (_IsWord()) return Type::Indentifier;
	//failed
	else
	{
		std::cout << "At index of " << index << "\n near" << _flow[index] << _flow[index + 1] << _flow[index + 2] << std::endl;
		throw ErrorReporter("Unknown microsyntax");
		return Type::unkown;
	}
}

bool microsyntax::Analysis()
{
	Type rety = Type::Assain;
	while (rety != Type::Endmark)
	{
		try
		{
			rety = _NextWord();
		}
		catch (ErrorReporter &msg)
		{
			std::cout<<"Line"<<nowline<<": " << msg.Report() << std::endl;
			return false;
		}
		//	std::cout << static_cast<int>(rety) <<"\n";
		// if(rety == Type::Endmark) break;

	}
	return true;
}

void microsyntax::PrintAns()
{
	for (auto &p : Words)
	{
		//std::cout << typetable[static_cast<int>(p.type)] << ", " << p.str <<"    "<<p.line<< std::endl;
		std::cout<< p.str << "\t\t" << typetable[static_cast<int>(p.type)] << std::endl;
	}

}
