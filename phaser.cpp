#include "phaser.h"

bool Phaser::_Match(Type a)
{
	if (a == tit->type)
		return true;
	else
		return false;
}

void Phaser::_Next()
{
	if (tit != Tokens.end())
		tit++;
	_nowline = tit->line;
}

void Phaser::err(const std::string &msg)
{
	throw ErrorReporter(msg);
}
bool Phaser::_IfDefVar(const std::string &a)
{
	for (auto p : varTable)
	{
		if (p.name == a && p.vLevel <= _nowlevel) 
		{
			return true;
		}
	}

	//err("varible not define!\n");
	return false;
}

bool Phaser::_IfDefProc(const std::string &a)
{
	if (a == _nowprcname)
		return true;
	
	for (auto p : procTable)
	{
		if (p.name == a && p.level <= _nowlevel)
		{
			return true;
		}
	}

	//err("varible not define!\n");
	return false;
}

void Phaser::_Program(const std::string &pname, const std::string &proc)
{
	_SubProgram( pname, proc);
}

void Phaser::_SubProgram(const std::string &pname, const std::string &proc)
{
	if (_Match(Type::Begin))_Next();
	else err("Begin expected!\n");
	++_nowlevel;
	std::string upername = _nowprcname;
	_nowprcname = proc;
	_Defs(pname, proc);

	/*if (_Match(Type::endc))_Next();
	else 
	{
		std::cout<<tit->str<<std::endl;
		err("';' expected1!\n");
	}*/
	_Excs();

	if (_Match(Type::End))_Next();
	else 
        {
               std::cout<<tit->str<<std::endl;
               err("'End' expected!\n");
        }
	_nowprcname = upername;

	--_nowlevel;
}

void Phaser::_Defs(const std::string &pname, const std::string &proc)
{
	do {
		if (_Match(Type::Int))_Next();
		else err(("'Integer' expected\n"));

		_Def(pname, proc);

		if (_Match(Type::endc))_Next();
		else err(("';' expected2\n"));

	} while (_Match(Type::Int));
}

void Phaser::_Def(const std::string &pname, const std::string &proc)
{
	if (_Match(Type::Function))
	{
		_Next();
		_ProcDef();
	}
	else
	{
		_VarDef(pname, proc);
	}
	
}

void Phaser::_VarDef(const std::string &pname, const std::string &proc)
{
	std::string newvar="";
	if (_Match(Type::Indentifier)){
		newvar = tit->str;
		_Next();
	}
	else
	{
		err("variable needed!/n");
	}
	//NO redifine at the same level
	if (_IfDefVar(newvar))
		err("redefine variables\n");
	Var *newVar = new Var;
	newVar->name = newvar;
	newVar->proc = proc;
	if(pname == newvar) newVar->kind = vKind::Parameter;
	else newVar->kind = vKind::Variable;
	newVar->type = vType::Integer;
	newVar->vLevel = _nowlevel;
	newVar->posInTable = varTable.size();
	varTable.push_back(*newVar);

}

void Phaser::_ProcDef()
{
	std::string procname = "",paraname = "";
	if (_Match(Type::Indentifier)) {
		procname = tit->str;
		_Next();
	}//get function name

	if(_IfDefProc(procname))
		err("redefine functions\n");

	if (_Match(Type::Leftbrac))_Next();
	else err("'(' expected\n");

	if (_Match(Type::Indentifier)) { paraname = tit->str; _Next(); }
	else err("'parameter' expected\n");

	if (_Match(Type::Rightbrac))_Next();
	else err("')' expected\n");

	if (_Match(Type::endc))_Next();
	else err("';' expected3\n");

	int varbegin = varTable.size();
	_SubProgram(paraname,procname);
	int varend = varTable.size() - 1;

	Proc *prov = new Proc;
	prov->name = procname;
	prov->type = vType::Integer;
	prov->level = _nowlevel;
	prov->varBegin = varbegin;
	prov->varEnd = varend;

	procTable.push_back(*prov);

}

void Phaser::_Excs()
{
	do
	{
		_Exc();
		if (_Match(Type::End)) {  break; }

		if (_Match(Type::endc))_Next();
		else err(("';' expected4\n"));
	} while (1);
}

void Phaser::_Exc()
{
	if (_Match(Type::Read) || _Match(Type::Write))
	{
		_Next();
		if (_Match(Type::Leftbrac))_Next();
		else err("'(' expected\n");

		if (_Match(Type::Indentifier)) {
			if (!_IfDefVar(tit->str))
				err("Not defined reference!\n");
			_Next();
		}
		else err("'parameter' expected\n");
		
		if (_Match(Type::Rightbrac))_Next();
		else err("')' expected\n");
	}else
		if (_Match(Type::Indentifier))
		{
			_Next();
			if (_Match(Type::Assain))_Next();
			else err(":= needed!\n");

			_arith();
		}
		else if (_Match(Type::If))
		{
			_Next();
			
			_condition();

			if (_Match(Type::Then))_Next();
			else err("Then expected!\n");

			_Exc();

			if (_Match(Type::Else))_Next();
			else err("Else expected!\n");
			_Exc();
			
		}
}

void Phaser::_arith()
{
	_term();
	while (_Match(Type::Minus) || _Match(Type::Plus))
	{
		_Next();
		_term();
	}
}

void Phaser::_term()
{
	_factor();
	while (_Match(Type::Times))
	{
		_Next();
		_factor();
	}
}

void Phaser::_factor()
{
	if (_Match(Type::Number))
	{
		_Next();
		return;
	}else
		if (_Match(Type::Indentifier))
		{
			std::string rt = tit->str;

			_Next();
			if (_Match(Type::Leftbrac))
			{
				if (!_IfDefProc(rt))
					err("Not defined reference!\n");

				_Next();
				_arith();
				if (_Match(Type::Rightbrac))_Next();
				else err("')' expected!\n");
			}
			else 
			{
				if (!_IfDefVar(rt))
					err("Not defined reference!\n");
				return;
			}
		}
}

void Phaser::_condition()
{
	_arith();

	if (_Match(Type::Larger) || _Match(Type::Largeeuqal) || \
		_Match(Type::Less) || _Match(Type::Lesseuqal) || \
		_Match(Type::Equal) || _Match(Type::Notequal))
	{
		_Next();
	}
	else
		err(">? expected!\n");

	_arith();
}

bool Phaser::Analysis()
{
	try { _Program(); }
	catch (ErrorReporter &msg)
	{
		std::cout << "Line" << _nowline << ": " << msg.Report() << std::endl;
		return false;
	}
	if (!_Match(Type::Endmark))
	{
		err("EOF expected!\n");
		return false;
	}
	return true;
}
