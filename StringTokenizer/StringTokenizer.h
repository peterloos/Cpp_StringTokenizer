class StringTokenizer
{
// output operator
friend ostream& operator<< (ostream&, StringTokenizer&);

private:
    // private member data
    char*   m_str;      // string to tokenize
    char*   m_delim;    // string of delimiters
    int     m_pos;      // current position during tokenization
    Token*  m_tokens;   // list of tokens

public:
    // c'tors / d'tor
    StringTokenizer ();
    StringTokenizer (char*);
    StringTokenizer (char*, char*);
    StringTokenizer (const StringTokenizer&);
    virtual ~StringTokenizer ();

    // setter
    void SetString (char*);
    void SetDelimiters (char*);

    // public methods
    int Count ();
    void Tokenize ();

    // enumeration
    void Reset ();
    bool HasMoreTokens () const;
    char* NextToken ();
    Token NextTokenEx ();
    void SkipToken ();

public:
    // public operators
    Token operator[] (int);

private:
    // private helper functions
    bool IsDelim (char) const;

public:
    // public operators
    StringTokenizer& operator= (const StringTokenizer&);
};
