class Token
{
friend ostream& operator<< (ostream&, const Token&);

private:
    // private member data
    char* m_tok;   // token

public:
    // c'tors / d'tor
    Token ();
    Token (char*);
    Token (char*, int len);
    Token (const Token&);
    ~Token ();

public:
    // operators
    Token& operator= (const Token&);
    bool operator== (const Token&);
};