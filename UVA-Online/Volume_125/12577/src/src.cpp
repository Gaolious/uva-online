#include <bits/stdc++.h>
#include <math.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/stat.h>
using namespace std;

class FIO
{
    char *p;
    char c ;
public :
    FIO()
    {
        struct stat rstat;
        this->p = NULL ;
        
        if ( fstat(0, &rstat) == 0 && rstat.st_size > 0 )
            this->p = (char*)mmap(0, rstat.st_size, PROT_READ, MAP_SHARED, 0, 0) ;
        
        if ( this->p == MAP_FAILED ) this->p = NULL ;
    }
    void skip() { while ( this->p && *this->p && *this->p <= ' ' ) this->p++; }
    bool Char(char &c)  { if ( !this->p || *this->p <= 0 ) return false ; this->c = *this->p++; c = this->c; return true ; }
    bool line(char *s, int &len, const int maxLen)
    {
        char c = 0 ;
        this->skip();
        
        for ( len = 0 ; this->Char(c) && c > 0 && c != '\n' && len < maxLen ; len++ )
            *s++ = c ;
        *s = 0x00;
        return c || len > 0;
    }
    bool word(char *s, int &len, const int maxLen)
    {
        char c = 0 ;
        this->skip();
        
        for ( len = 0 ; this->Char(c) && c > ' ' && len < maxLen ; len++ )
            *s++ = c ;
        *s = 0x00;
        return c || len > 0;
    }
    bool sign(bool s)
    {
        char c ;
        this->skip();
        if ( ! this->Char(c) )  return false ;
        if ( c == '+' || c == '-' )
        {
            s = c == '+' ;
            if ( ! this->Char(c) )  return false ;
        }
        return true ;
    }
    template<typename T> bool Int(T &n)
    {
        char c ;
        bool flag = true ;
        n = 0 ;
        if ( !this->sign(flag) ) return false ;
        c = this->c ;
        for ( c = this->c ; c > ' ' ; n = n * 10 + c - 48)
            if ( ! this->Char(c) ) break;
        if ( !flag ) n = -n;
        return true ;
    }
    template<typename T> bool Float(T &n)
    {
        
    }
    template<typename T> bool Int(T &a, T &b) { return this->Int(a) && this->Int(b); }
    template<typename T> bool Int(T &a, T &b, T &c) { return this->Int(a, b) && this->Int(c); }
    template<typename T> bool Int(T &a, T &b, T &c, T &d) { return this->Int(a, b) && this->Int(c, d); }
};

void process()
{
    FIO fin ;   
    int n ; 
    char S[1024];
    int i ;

    for ( i = 1 ; fin.line(S, n, sizeof(S)-1) && S[0] != '*' ; i ++)
        printf("Case %d: %s\n", i, S[0] == 'H' ? "Hajj-e-Akbar" : "Hajj-e-Asghar");
}

int main() 
{ 
#ifndef ONLINE_JUDGE 
    clock_t t = clock();
#else  
#endif 

    process(); 

#ifndef ONLINE_JUDGE 
    t = clock() - t;
    printf ("Estimated Time : %f seconds.\n",((float)t)/CLOCKS_PER_SEC);    
#else 
#endif 
    return 0; 
} 


