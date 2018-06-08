#include<map>
#include<cstdlib>
#include<fstream>
#include<iostream>
#include<string>
#include<list>
#include<vector>
const std::string typetable[] = {"Int",
            "If", "For", "While", "Else", "Then",
            "Begin", "End", "Function",
            "Plus", "Minus", "Times", 
            "Assain", 
            "Equal",
            "Notequal",
            "Leftbrac", "Rightbrac",
            "Lesseuqal",
            "Indentifier", "Number", "Endmark" };
//std::map <std::string, int> Transtable;

enum class Type{
    //Keywords
    Int,
    If, For, While, Else, Then,
    Begin, End, Function,
    //Symbols
    Plus, Minus, Times, 
    Assain, 
    Equal,
    Notequal,
    Leftbrac, Rightbrac,
    Lesseuqal,
    //Indentifiers & numbers

    Indentifier, Number, Endmark, unkown
};

struct Word
{
    Type type;
    std::string str;
};

class ErrorReporter// used to report microsyntax error
{
public:
    ErrorReporter(const std::string &msg)
        : _msg(msg)
    {}

    const char* Report(){return _msg.c_str();}    
private:
    std::string _msg;
};

class microsyntax
{
public: 
    microsyntax(const std::string &flows)
        : _flow(flows), index(0), index_now(0), index_start(0)
    {
        Words.clear();
        _Symbollist.clear();
        _Symbollist.push_back(std::make_pair("+", Type::Plus));
        _Symbollist.push_back(std::make_pair("-", Type::Minus));
        _Symbollist.push_back(std::make_pair("*", Type::Times));
        _Symbollist.push_back(std::make_pair("=", Type::Assain));
        _Symbollist.push_back(std::make_pair("==", Type::Equal));
        _Symbollist.push_back(std::make_pair("!=", Type::Notequal));
        _Symbollist.push_back(std::make_pair("(", Type::Leftbrac));
        _Symbollist.push_back(std::make_pair(")", Type::Rightbrac));
        _Symbollist.push_back(std::make_pair("<=", Type::Lesseuqal));
        _Keywordlist.clear();
        _Keywordlist.push_back(std::make_pair("Int", Type::Int));
        _Keywordlist.push_back(std::make_pair("If", Type::If));
        _Keywordlist.push_back(std::make_pair("For", Type::For));
        _Keywordlist.push_back(std::make_pair("While", Type::While));
        _Keywordlist.push_back(std::make_pair("Else", Type::Else));
        _Keywordlist.push_back(std::make_pair("Then", Type::Then));
        _Keywordlist.push_back(std::make_pair("Begin", Type::Begin));
        _Keywordlist.push_back(std::make_pair("End", Type::End));
        _Keywordlist.push_back(std::make_pair("Function", Type::Function));
    }
    bool Analysis();
    void PrintAns();
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
