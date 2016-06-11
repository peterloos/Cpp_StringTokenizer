#include <iostream>
using namespace std;
#include <string>

#include "Token.h"
#include "StringTokenizer.h"

// c'tors and d'tor
Token::Token ()
{
    m_tok = (char*) 0;
}

Token::Token (char* tok)
{
    // allocate memory and copy argument
    int len = strlen(tok);
    m_tok = new char[len + 1];
    strcpy_s (m_tok, len + 1, tok);
}

Token::Token (char* tok, int len)
{
    // allocate memory and copy argument
    m_tok = new char[len + 1];
    strncpy_s (m_tok, len + 1, tok, len);
}

Token::Token (const Token& t)
{
    // allocate memory and copy argument
    if (t.m_tok != (char *) 0)
    {
        int len = strlen(t.m_tok);
        m_tok = new char[len + 1];
        strcpy_s (m_tok, len + 1, t.m_tok);
    }
    else
        m_tok = (char*) 0;
}

Token::~Token ()
{
    delete[] m_tok;
}

// comparison operator
bool Token::operator== (const Token& t)
{
    if (strcmp(m_tok, t.m_tok) != 0)
        return false;

    return true;
}

// assignment operator
Token& Token::operator= (const Token& t)
{
    // prevent self-assignment
    if (this == &t)
        return *this;

    // delete old token
    delete[] m_tok;

    // copy token
    if (t.m_tok != (char *) 0)
    {
        int len = strlen(t.m_tok);
        m_tok = new char[len + 1];
        strcpy_s (m_tok, len + 1, t.m_tok);
    }
    else
        m_tok = (char*) 0;

    return *this;
}

// output operator
ostream& operator<< (ostream& os, const Token& t)
{
    if (t.m_tok != (char *) 0)
        os << t.m_tok;
    return os;
}
