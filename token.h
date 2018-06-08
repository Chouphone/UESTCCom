#ifndef TOKEN_H
#define TOKEN_H


#include<map>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>
#include<list>
#include<vector>
const std::string typetable[] = { "Int",
"If", "For", "While", "Else", "Then",
"Begin", "End", "Function","Read", "Write" ,
"Plus", "Minus", "Times",
"Assain",
"Equal",
"Notequal",
"Leftbrac", "Rightbrac",
"Lesseuqal","Largeeuqal",
"Less", "Larger","endc","Endline",
"Indentifier", "Number", "Endmark" };
//std::map <std::string, int> Transtable;

enum class Type {
	//Keywords
	Int,
	If, For, While, Else, Then,
	Begin, End, Function, Read, Write,
	//Symbols
	Plus, Minus, Times,
	Assain,
	Equal,
	Notequal,
	Leftbrac, Rightbrac,
	Lesseuqal, Largeeuqal,
	Less, Larger, endc,Endline,
	//Indentifiers & numbers

	Indentifier, Number, Endmark, unkown
};

struct Word
{
	Type type;
	std::string str;

	int line;
};

class ErrorReporter// used to report microsyntax error
{
public:
	ErrorReporter(const std::string &msg)
		: _msg(msg)
	{}

	const char* Report() { return _msg.c_str(); }
private:
	std::string _msg;
};

class microsyntax
{
public:
	microsyntax(const std::string &flows)
		: _flow(flows), index(0), index_now(0), index_start(0), nowline(1)
	{
		Words.clear();
		_Symbollist.clear();
		_Symbollist.push_back(std::make_pair("+", Type::Plus));
		_Symbollist.push_back(std::make_pair("-", Type::Minus));
		_Symbollist.push_back(std::make_pair("*", Type::Times));
		_Symbollist.push_back(std::make_pair(":=", Type::Assain));
		_Symbollist.push_back(std::make_pair("=", Type::Equal));
		_Symbollist.push_back(std::make_pair("<>", Type::Notequal));
		_Symbollist.push_back(std::make_pair("(", Type::Leftbrac));
		_Symbollist.push_back(std::make_pair(")", Type::Rightbrac));
		_Symbollist.push_back(std::make_pair("<=", Type::Lesseuqal));
		_Symbollist.push_back(std::make_pair(">=", Type::Largeeuqal));
		_Symbollist.push_back(std::make_pair("<", Type::Less));
		_Symbollist.push_back(std::make_pair(">", Type::Larger));
		_Symbollist.push_back(std::make_pair(";", Type::endc));
		_Keywordlist.clear();
		_Keywordlist.push_back(std::make_pair("integer", Type::Int));
		_Keywordlist.push_back(std::make_pair("if", Type::If));
		_Keywordlist.push_back(std::make_pair("for", Type::For));
		_Keywordlist.push_back(std::make_pair("while", Type::While));
		_Keywordlist.push_back(std::make_pair("else", Type::Else));
		_Keywordlist.push_back(std::make_pair("then", Type::Then));
		_Keywordlist.push_back(std::make_pair("begin", Type::Begin));
		_Keywordlist.push_back(std::make_pair("end", Type::End));
		_Keywordlist.push_back(std::make_pair("read", Type::Read));
		_Keywordlist.push_back(std::make_pair("write", Type::Write));
		_Keywordlist.push_back(std::make_pair("function", Type::Function));
	}
	bool Analysis();
	void PrintAns();
	std::list <Word> GetWords() {
		return Words;
	}
	int nowline;
private:
	std::string _flow;
	int index;
	int index_now, index_start;
	std::list <Word> Words;
	std::vector <std::pair<std::string, Type> > _Symbollist;
	std::vector <std::pair<std::string, Type> > _Keywordlist;
	Type _NextWord();
	void _Skip();
	bool _Match(const std::string target);
	bool _IsSymbol();
	
	bool _IsNumber();
	bool _IsWord();
};
#endif // TOKEN_H