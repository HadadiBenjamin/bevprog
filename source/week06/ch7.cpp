/*
	The first working version of Stroustrup's calculator.
	Written by Renátó Besenczi based on the book BS, "Programming: Principles and Practice using C++, Second Edition"
	See chapter 6 and chapter 7 of book: https://stroustrup.com/programming.html
	© 2020 Renátó Besenczi, according to CC0. Questions: renato.besenczi@gmail.com
	Input from cin; output to cout. Input comes from cin through the Token_stream called ts.
	Grammar:
	
	Calculation:
		Statement
		Print
		Quit
		Calculation Statement
	Print:
		=
	Quit:
		x or exit
	Statement:
		Declaration
		Expression
	Declaration:
		"let" Name "=" Expression
	Name:
		string literal
	Expression:
		Term
		Expression + Term
		Expression – Term
	Term:
		Primary
		Term * Primary
		Term / Primary
		Term % Primary
	Primary:
		Number
		( Expression )
		– Primary
		+ Primary
	Number:
		floating-point-literal

*/

#include "std_lib_facilities.h" //Include usual header

// Some symbolic constants for clarity
constexpr char number = '8';
constexpr char quit = 'x';
constexpr char print = '=';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char result = '=';
constexpr char open = '(';
constexpr char close = ')';
constexpr char comma = ',';
constexpr char sum = '+';
constexpr char dot = '.';
constexpr char subtr = '-';
constexpr char multpl = '*';
constexpr char divis = '/';
constexpr char mod = '%';
const string declkey = "let"; //constexpr string since C++20 only
const string declkey1 = "pow";
const string declkey2 = "sqrt";
const string declkeyx = "exit";
constexpr char power = 'p';
constexpr char square = '@';

//function declarations
double expression();
double primary();
double term();
double declaration();
double statement();
double pows();
double sqrts();
// Variable ///////////////////////
class Variable {
public:
	string name;
	double value;
};

vector<Variable> var_table;

bool is_declared(string var)
{
	for (const auto& v : var_table)
		if (v.name == var) return true;
	return false;
}

double define_name (string var, double val)
{
	if (is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable{var,val});
	return val;
}

double get_value(string s)
{
	for(const auto& v : var_table)
		if (v.name == s) return v.value;
	error("get: undefined variable", s);
	return -1;
}




// Variable end ///////////////////////

// Token ///////////////////////
class Token {
public:
	char kind;
	double value;
	string name;
	Token(): kind(0) {}
	Token(char ch): kind(ch), value(0) {}
	Token(char ch, double val): kind(ch), value(val) {}
	Token(char ch, string n): kind(ch), name(n) {}
};
// Token end ///////////////////////

// Token_stream ///////////////////////
class Token_stream {
public:
	Token_stream();
	void putback(Token t);
	Token get();
	void ignore(char c);
private:
	bool full;
	Token buffer;
};

Token_stream::Token_stream() :full(false), buffer(0) {}

void Token_stream::putback(Token t)
{
	if (full) error("putback() into full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;

	switch (ch)
	{
		case print:
		case quit:
		case open:
		case close:
		case comma:
		case sum:
		case subtr:
		case multpl:
		case divis:
		case mod:
			return Token(ch);
		case dot:
		case '0': case '1': case '2': case '3': case '4':
    	case '5': case '6': case '7': case '8': case '9':
    	{
    		cin.putback (ch);
    		double val;
    		cin >> val;
    		return Token(number, val);
    	}
    	
    	default: 
    	{
    		if (isalpha(ch))
    		{
    			string s;
    			s += ch;
    			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
    			cin.putback(ch);
    			if (s == declkey) return Token{let};	
    			if (s == declkeyx) return Token{quit};
    			else if (s == declkey1) return Token{power}; 
    			else if (s == declkey2) return Token{square}; 
    			else if (is_declared(s))
    				return Token(number, get_value(s));
    			return Token{name,s};
    		}
    		error("Bad token");
    	}
    	return 0;
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}

	full = false;

	char ch = 0;
	while (cin>>ch)
		if (ch==c) return;
}
// Token_stream end ///////////////////////
Token_stream ts;

void clean_up_mess()
{
	ts.ignore(print);
}

// Logically separate calculate() from the usual "boiler plate" of main 
void calculate()
{
	while (cin)
	try {
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << endl;
	}
	catch (exception& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

void help() {
	cout << "\nYou are allowed to use +,-,*,/,%,sqrt(), and pow()\n\n";
	cout << "Once you are done entering an expression, enter a '=' to execute the expression. Quit= 'exit' or 'x'.\n";
	cout << "pow() is used in the following syntax: pow(<number to be raised>,<number to raise it to>)\n\n";

}

int main() 
try { 

	help();
			
	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);
	
	calculate();

	return 0;

} catch (exception& e){
	cerr << e.what() << endl;
	return 1;
} catch (...) {
	cerr << "exception\n";
	return 2;
}

//Functions mapping grammar rules //////////////////////////
double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
		case open:
		{
			double d = expression();
			t = ts.get();
			if (t.kind != close) error("')' expected");
			return d;
		}
		case number:
			return t.value;
		case subtr:
			return - primary();
		case sum:
			return primary();
		case power: return pows();
		case square: return sqrts();	
		default:
			error("primary expected");
	}
	return -1;
}

double term()
{
	double left = primary();
	Token t = ts.get();
	while(true)
	{
		switch (t.kind)
		{
			case multpl:
				left *= primary();
				t = ts.get();
				break;
			case divis:
			{
				double d = primary();
				if (d == 0) error("divide by zero");
				left /= d;
				t = ts.get();
				break;
			}
			case mod:
			{
				double d = primary();
				if (d == 0) error("%: divide by zero");
				left = fmod (left, d);
				t = ts.get();
				break;
				/* //or you can use narrow cast check
				int i1 = narrow_cast<int>(left);
				int i2 = narrow_cast<int>(primary());
				if (i2 == 0) error ("%: Zero oszto");
				left = i1 % i2;
				t = ts.get();
				break;
				*/
			}
			default:
				ts.putback(t);
				return left;
		}
	}
}

double expression()
{
	double left = term();
	Token t = ts.get();
	while (true)
	{
		switch(t.kind)
		{
			case sum:
				left += term();
				t = ts.get();
				break;
			case subtr:
				left -= term();
				t = ts.get();
				break;
			default:
				ts.putback(t);
				return left;
		}
	}
}

double declaration()
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	define_name(var_name, d);
	return d;
}

double statement()
{
	Token t = ts.get();
	switch(t.kind)
	{
		case let:
			return declaration();
		default:
			ts.putback(t);
			return expression();
	}
}
double sqrts() {
	Token t = ts.get();
	        if (t.kind != open) error("'(' expected");
	        double d=expression();
	        if (d<0) error("value is negative");
	Token t2 = ts.get();
	        if (t2.kind != close) error("')' expected");
	        return sqrt(d);
		}
double pows() {
	Token t = ts.get();
	        if (t.kind != open) error("'(' expected");
	        double d=expression();
	Token t2 = ts.get();
	        if (t2.kind !=comma) error("',' expected");
	        int i=narrow_cast<int>(expression());
	Token t3 = ts.get();
	        if (t3.kind != close) error("')' expected");
	        return pow(d,i);
		}
void set_value(string s, double d)
{
	for (auto& v : var_table)
		if(v.name == s){
			v.value = d;
			return;
		}
	error("set: undefined variable", s);
}
//Functions mapping grammar rules end //////////////////////////

// Program end!

