#include <bits/stdc++.h>
#include <math.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/stat.h>
using namespace std;

class FIO
{
    #define BUFF_LEN (1<<21)
    char *p;
    char out[BUFF_LEN];
    int nOut ;
public :
    FIO()
    {
        struct stat rstat;
        this->p = NULL ;
        
        if ( fstat(0, &rstat) == 0 && rstat.st_size > 0 )
            this->p = (char*)mmap(0, rstat.st_size, PROT_READ, MAP_SHARED, 0, 0) ;
        
        if ( this->p == MAP_FAILED ) this->p = NULL ;
        nOut = 0;
    }
    ~FIO() {
        this->write_flush();
    }
    void skip() { while ( this->p && *this->p && *this->p <= ' ' ) this->p++; }
    bool Char(char &c)  { if ( !this->p || *this->p <= 0 ) return false ; c = *this->p++; return true ; }
    bool line(char *s, int &len, const int maxLen)
    {
        char c = 0 ;
        this->skip();
        
        for ( len = 0 ; this->Char(c) && c > 0 && c != '\n' && len < maxLen ; len++ )
            *s++ = c ;
        *s = 0x00;
        return c || len > 0;
    }
    template<typename T> bool Int(T &n)
    {
        char c ;
        bool flag = true ;
        n = 0 ;
        this->skip();
        if ( ! this->Char(c) )  return false ;
        if ( c == '-' )
        {
            flag = false;
            if ( ! this->Char(c) ) return false ;
        }

        while ( c > ' ' )
        {
            n = n * 10 + c - 48 ;
            if ( ! this->Char(c) ) break;
        }
        if ( !flag ) n = -n;
        return true ;
    }
    template<typename T> bool Int(T &a, T &b) { return this->Int(a) && this->Int(b); }
    template<typename T> bool Int(T &a, T &b, T &c) { return this->Int(a, b) && this->Int(c); }
    template<typename T> bool Int(T &a, T &b, T &c, T &d) { return this->Int(a, b) && this->Int(c, d); }

    void write_flush(){
        if ( this->nOut > 0 )
        {
            fwrite(this->out, 1, this->nOut, stdout);
            this->nOut = 0;
        }
    }
    void write_Char(char c) { 
        if ( this->nOut >= BUFF_LEN )
            this->write_flush();
        this->out[ this->nOut ++ ] = c ;
    }
    template<typename T> void write_Int(T a) 
    {
        if ( a < 0 ) 
        {
            this->write_Char('-');
            a *= -1;
        }
        char buff[30];
        int nBuff = 0;
        for ( int i = 0 ; a > 0 ; a /= 10 )
            buff[nBuff++] = '0' + (a%10);
        while ( nBuff > 0 )
            write_Char(buff[--nBuff]);
    }
};

#define MAX_N (1000000)
int ans[MAX_N + 1]={0,};
int D[MAX_N + 1]={0,};
int S[MAX_N + 1]={0,};

void process()
{
    FIO fin ;    
    int N ;
    int i ;
    int nSp = -1;
    int nAns = 0;
    fin.Int(N);

    for ( i = 0 ; i < N ; i ++ )
    {
        fin.Int(D[i]);
        while ( nSp >= 0 && D[ S[nSp] ] < D[i])
            ans[ S[nSp--] ] = D[ i ];
        S[++nSp] = i;
    }
    for ( i = 0 ; i < N ; i ++ )
    {
        fin.write_Int(ans[ i ] > 0 ? ans[ i ] : -1);
        fin.write_Char(' ');
    }
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


