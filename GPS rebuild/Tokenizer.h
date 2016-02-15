/***************************************************************************//*
NOTES:

Found online here: 
http://cboard.cprogramming.com/cplusplus-programming/51507-tokenizing-cplusplus-string.html
written by user Prelude
																			  
This MUST be included with source code in order to work properly. Handles 
strings delimited by any number of characters and creates tokens that may be 
accessed sequentially by calling the function Tokenizer.next()

																			  
***************************************************************************//**/
#include <sstream>
#include <vector>

using namespace std;

#ifndef _TOKENIZER_H_
#define _TOKENIZER_H_

class Tokenizer {
public:
	explicit Tokenizer(const string& s, char delim = ' ');
	explicit Tokenizer(const string& s, const string& delim);
public:
	string next() //call to get next token
	{ 
		return !done() ? *current++ : string(); 
	}
	bool done() const 
	{ 
		return current == tokens.end(); 
	}
private:
	vector<string>           tokens;
	vector<string>::iterator current;
};



/*
Constructor for single character delimited tokens
*/
Tokenizer::Tokenizer(const string& s, char delim)
{
	istringstream grabber(s);
	string        token;

	while (getline(grabber, token, delim)) {
		if (!token.empty())
			tokens.push_back(token);
	}
	current = tokens.begin();
}
/*
Constructor for multiple character delimited tokens
*/
Tokenizer::Tokenizer(const string& s, const string& delim)
{
	string            token;
	string::size_type front = 0;
	string::size_type back = 0;

	while (true)
	{
		if (back == string::npos)
			break;
		front = s.find_first_not_of(delim, front);
		if (front == string::npos)
			break;
		back = s.find_first_of(delim, front);
		token = s.substr(front, back - front);
		tokens.push_back(token);
		front = back + delim.length();
	}
	current = tokens.begin();
}
#endif