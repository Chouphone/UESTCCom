#ifndef  PHASER_H
#define PHASER_H


#include "token.h"
#include <iostream>
#include <vector>
#include <string>

enum class vKind //two kinds: 0/V 1/P
{
	Variable,
	Parameter
};

enum class vType //only Interger here
{
	Integer
};

struct Var //varible table base descriptions
{
	std::string name;
	std::string proc;
	vKind kind;
	vType type;
	int vLevel;
	int posInTable;
};

struct Proc //process table base descriptions
{
	std::string name;
	vType type;
	int level;
	int varBegin, varEnd; 
};



class Phaser
{
public:
	bool Analysis();
	Phaser(const std::list <Word> &p)//initialize after microsyntax
		: Tokens(p)
	{
		varTable.clear();
		procTable.clear();
		tit = Tokens.begin();
		_nowline = 1;
		_nowlevel = 0;
		_nowprcname = "program";
	}
	void err(const std::string &msg);//error report!
	void PrintVar()
	{
		for(auto &p : varTable)
		{
			std::cout<<"-----------------------------\n";
			std::cout<<"name:"<<p.name<<std::endl;
			std::cout<<"proc:"<<p.proc<<std::endl;
			std::cout<<"kind:"<<static_cast<int>(p.kind)<<std::endl;
			std::cout<<"type:"<<"integer"<<std::endl;
			std::cout<<"level:"<<p.vLevel<<std::endl;
			std::cout<<"pos:"<<p.posInTable<<std::endl;
			std::cout<<"-----------------------------\n\n";
	
		}
	}
	void PrintProc()
	{
		for(auto &p : procTable)
		{
			std::cout<<"-----------------------------\n";
			std::cout<<"name:"<<p.name<<std::endl;
			//std::cout<<"proc:"<<p.proc<<std::endl;
			//std::cout<<"kind:"<<static_cast<int>(p.kind)<<std::endl;
			std::cout<<"type:"<<"integer"<<std::endl;
			std::cout<<"var begin pos:"<<p.varBegin<<std::endl;
			std::cout<<"var end pos:"<<p.varEnd<<std::endl;
			std::cout<<"-----------------------------\n\n";
	
		}	
	}
private:
	std::vector<Var> varTable;
	std::vector<Proc> procTable;
	bool _Match(Type a);//check if tit->type == a
	void _Next();//Next Token
	
	bool _IfDefVar(const std::string &a);
	bool _IfDefProc(const std::string &a);


	std::list <Word> Tokens;
	std::list <Word>::iterator tit;
	void _Program(const std::string &pname = "", const std::string &proc = "");
	void _SubProgram(const std::string &pname = "", const std::string &proc = "");
	void _Defs(const std::string &pname = "", const std::string &proc = "");
	void _Def(const std::string &pname = "", const std::string &proc = "");
	void _VarDef(const std::string &pname="", const std::string &proc="");
	void _ProcDef();
	
	void _Excs();
	void _Exc();

	void _arith();
	void _term();
	void _factor();
	void _condition();
	int _nowline;
	int _nowlevel;
	std::string _nowprcname;
};

#endif // ! PHASER_H
