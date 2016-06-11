#include <iostream>
using namespace std;

#include "Token.h"
#include "StringTokenizer.h"

// c'tors and d'tor
StringTokenizer::StringTokenizer ()
{
    m_str = (char*) 0;
    m_delim = (char*) 0;

    SetString ("");
    SetDelimiters (" ");

    m_pos = 0;
    m_tokens = (Token*) 0;
}

StringTokenizer::StringTokenizer (char* s)
{
    m_str = (char*) 0;
    m_delim = (char*) 0;

    SetString (s);
    SetDelimiters (" ");

    m_pos = 0;
    m_tokens = (Token*) 0;
}

StringTokenizer::StringTokenizer (char* s, char* d)
{
    m_str = (char*) 0;
    m_delim = (char*) 0;

    SetString (s);
    SetDelimiters (d);

    m_pos = 0;
    m_tokens = (Token*) 0;
}

StringTokenizer::StringTokenizer (const StringTokenizer& st)
{
    m_str = (char*) 0;
    m_delim = (char*) 0;

    SetString (st.m_str);
    SetDelimiters (st.m_delim);

    m_pos = 0;
    m_tokens = (Token*) 0;
}

StringTokenizer::~StringTokenizer ()
{
    delete[] m_str;
    delete[] m_delim;
    delete[] m_tokens;
}

// setter
void StringTokenizer::SetString (char* s)
{
    // release formerly allocated string
    delete[] m_str;

    // allocate memory and copy argument
    int len = (int) strlen (s);
    m_str = new char[len + 1];
    strcpy_s (m_str, len + 1, s);
}

void StringTokenizer::SetDelimiters (char* d)
{
    // release formerly allocated delimiter string
    delete[] m_delim;

    // allocate memory and copy argument
    int len = (int) strlen (d);
    m_delim = new char[len + 1];
    strcpy_s (m_delim, len + 1, d);
}

// public methods
int StringTokenizer::Count ()
{
    int count = 0;

    int ofs = 0;
    while (m_str[ofs] != '\0')
    {
        if (IsDelim (m_str[ofs]))
        {
            ofs ++;
            continue;
        }
        else
        {
            // begin of next token found
            count ++;

            // search end of token
            while (m_str[ofs] != '\0')
            {
                if (! IsDelim (m_str[ofs]))
                    ofs ++;
                else
                    break;
            }
        }
    }

    return count;
}

void StringTokenizer::Tokenize ()
{
    Reset ();
    int count = Count();
    m_tokens = new Token[count];

    for (int i = 0; i < count; i ++)
        m_tokens[i] = NextToken();
}

// enumeration
void StringTokenizer::Reset ()
{
    m_pos = 0;
}

bool StringTokenizer::HasMoreTokens () const
{
    int ofs = m_pos;
    while (m_str[ofs] != '\0')
    {
        if (IsDelim (m_str[ofs]))
        {
            ofs ++;
            continue;
        }

        // there is at least one token in the string
        return true;
    }

    // no more chars found (except delimiters)
    return false;
}

char* StringTokenizer::NextToken ()
{
    // skip to begin of next token
    while (m_str[m_pos] != '\0')
    {
        if (IsDelim (m_str[m_pos]))
            m_pos ++;
        else
            break;
    }

    // end of string reached?
    if (m_str[m_pos]  == '\0')
        return (char*) 0;  // no more token available

    // search end of token
    int begin = m_pos;
    while (m_str[m_pos] != '\0')
    {
        if (! IsDelim (m_str[m_pos]))
            m_pos ++;
        else
            break;
    }

    // copy token into temporary buffer
    char* tok = new char [m_pos - begin + 1];
    for (int i = begin; i < m_pos; i ++)
        tok[i - begin] = m_str[i];
    tok [m_pos - begin] = '\0';

    return tok;
}

Token StringTokenizer::NextTokenEx ()
{
    // skip to begin of next token
    while (m_str[m_pos] != '\0')
    {
        if (IsDelim (m_str[m_pos]))
            m_pos ++;
        else
            break;
    }

    // end of string reached?
    if (m_str[m_pos] == '\0')
        return Token();  // no more token available

    // search end of token
    int begin = m_pos;
    while (m_str[m_pos] != '\0')
    {
        if (! IsDelim (m_str[m_pos]))
            m_pos ++;
        else
            break;
    }
    
    // create token
    Token tok (m_str + begin, m_pos - begin);
    return tok;
}

void StringTokenizer::SkipToken ()
{
	if (HasMoreTokens ())
		NextToken ();
}

// public operators
StringTokenizer& StringTokenizer::operator= (const StringTokenizer& st)
{
    // prevent self-assignment
    if (this == &st)
        return *this;

    // release left side
    delete[] m_str;
    delete[] m_delim;
    delete[] m_tokens;

    m_str = (char*) 0;
    m_delim = (char*) 0;

    SetString (st.m_str);
    SetDelimiters (st.m_delim);

    m_pos = 0;
    m_tokens = (Token*) 0;

    return *this;
}

Token StringTokenizer::operator[] (int i)
{
    return m_tokens[i];
}

// private helper function isDelim
bool StringTokenizer::IsDelim (char c) const
{
    for (int i = 0; m_delim[i] != '\0'; i ++)
        if (m_delim[i] == c)
            return true;

    return false;
}

// output
ostream& operator<< (ostream& os, StringTokenizer& t)
{
    os << "[";
    t.Reset ();
    bool first = true;
    while (t.HasMoreTokens ())
    {
        Token tok = t.NextToken ();
        if (first)
        {
            os << tok;
            first = false;
        }
        else
            os << "," << tok;
    }
    os << "]";

    return os;
}
