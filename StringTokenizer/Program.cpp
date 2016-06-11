#include <iostream>
using namespace std;

#include "Token.h"
#include "StringTokenizer.h"
#include "NumberTokenizer.h"

void Test01 ();
void Test02 ();
void Test03 ();
void Test04 ();
void Test05 ();
void Test06 ();
void Test07 ();
void Test08 ();
void Test09 ();
void Test10();
void Test11();

void main ()
{
    Test01();
    Test02();
    Test03();
    Test04();
    Test05();
    Test06();
    Test07();
    Test08();
    Test09();
	Test10();
	Test11();

	getchar();
}

void Test01 ()
{
    StringTokenizer st ("Dies ist ein Test");
    while (st.HasMoreTokens ())
    {
        char* tok = st.NextToken ();
        cout << "found '" << tok << '\'' << endl;
        delete[] tok;
    }
}

void Test02 ()
{
    StringTokenizer st ("!#!123!456#789#!#", "!#");
    while (st.HasMoreTokens ())
    {
        char* tok = st.NextToken ();
        cout << "found '" << tok << '\'' << endl;
        delete[] tok;
    }
}

void Test03 ()
{
    StringTokenizer st ("Dies ist ein Test");

    st.Tokenize();  // disassemble string into tokens

    for (int i = 0; i < st.Count(); i ++)
    {
        Token t = st[i];
        cout << i << ": " << t << endl;
    }
    cout << "# Tokens:   " << st.Count() << endl << endl;
}

void Test04 ()
{
    StringTokenizer st ("Dies ist ein anderer Test", "!#");
    st.Tokenize();

    for (int i = 0; i < st.Count(); i ++)
    {
        Token t = st[i];
        cout << i << ": " << t << endl;
    }
    cout << "# Tokens:   " << st.Count() << endl << endl;
}

void Test05 ()
{
    StringTokenizer st ("Dies!ist#auch#!#!#!ein!#!#!#Test", "!#");
    st.Tokenize();

    cout << "# Tokens: " << st.Count() << endl;
    for (int i = 0; i< st.Count(); i ++)
    {
        Token t = st[i];
        cout << i << ": " << t << endl;
    }
}

void Test06 ()
{
    // regular use of this tokenizer
    StringTokenizer st ("Dies ist ein Test");
    while (st.HasMoreTokens ())
    {
        char* tok = st.NextToken ();
        cout << "Found: " << tok << endl;
        delete tok;
    }

    // illegal use of tokenizer - no preceding call of 'HasMoreTokens'
    char* cp = st.NextToken ();
    if (cp == (char*) 0)
        cout << "NextToken failed!" << endl;

    // another test scanario
    st.SetString ("0Auch123dieses456ist789nur12ein34nichtssagender45Satz67zum8Testen9");
    st.SetDelimiters ("0123456789");
    cout << st << endl;

    // testing CountTokens method
    int num = st.Count ();
    cout << "# Tokens: " << num << endl;

    // yet another test scanario
    StringTokenizer st2 ("123!456#789", "!#");
    while (st2.HasMoreTokens ())
    {
        char * tok = st2.NextToken ();
        cout << "Found: " << tok << endl;
        delete tok;
    }

    // testing CountTokens method
    num = st2.Count ();
    cout << "# Tokens: " << num << endl;
}

void Test07 ()
{
    StringTokenizer st ("Dies ist ein Test");
    while (st.HasMoreTokens ())
    {
        Token tok = st.NextTokenEx ();
        cout << tok << endl;
    }
}

void Test08 ()
{
	// testing SkipToken
    StringTokenizer st ("Dies ist ein Test");

    Token tok = st.NextToken ();
    cout << "Found: " << tok << endl;

	st.SkipToken ();

    tok = st.NextToken ();
    cout << "Found: " << tok << endl;

	// st.SkipToken ();

	tok = st.NextToken ();
    cout << "Found: " << tok << endl;
}

void Test09 ()
{
    Token t;
    cout << t << endl;

    Token t1 ("123");
    Token t2 ("123");

    cout << (t1 == t2) << endl;
}

void Test10 ()
{
    // testing class NumberTokenizer
    NumberTokenizer nt = NumberTokenizer ("Auch123dieses456ist789nur12ein34nichtssagender45Satz67zum89Testen");
    cout << nt << endl;
}

void Test11 ()
{
    StringTokenizer st1 ("Dies ist ein Test");
    StringTokenizer st2 ("!#!123!456#789#!#", "!#");

    while (st2.HasMoreTokens ())
    {
        Token tok = st2.NextTokenEx ();
        cout << "Found " << tok << endl;
    }
    cout << endl;

    // testing operator '='
    cout << "testing operator '='" << endl;
    st2 = st1;
    while (st2.HasMoreTokens ())
    {
        Token tok = st2.NextTokenEx ();
        cout << "Found " << tok << endl;
    }
    cout << endl;

    cout << "testing copy-c'tor()" << endl;
    StringTokenizer st3 = st2;
    while (st3.HasMoreTokens ())
    {
        Token tok = st3.NextTokenEx ();
        cout << "Found " << tok << endl;
    }
}
