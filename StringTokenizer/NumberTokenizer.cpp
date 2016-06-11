#include <iostream>
using namespace std;

#include "Token.h"
#include "StringTokenizer.h"
#include "NumberTokenizer.h"

// c'tors and d'tor
NumberTokenizer::NumberTokenizer ()
    : StringTokenizer ("", "0123456789")
{
}

NumberTokenizer::NumberTokenizer (char* s)
    : StringTokenizer (s, "0123456789")
{
}
