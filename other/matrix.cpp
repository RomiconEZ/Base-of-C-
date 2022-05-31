
#include <iostream>

class matrix {
    int r;
    int c;
    int** M;
public:
    matrix(int _r = 1,int _c = 1)
    {
        r = _r;
        c = _c;
        M = new int* [r];
        for (int i = 0; i < r; ++i) M[i] = new int[c];
    }
    ~matrix() { for (int i = 0; i < r; ++i) delete[] M[i]; delete[] M; }

    matrix(matrix& X) 
    {
        this->r = X.r;
        this->c = X.c;

        M = new int* [r];
        for (int i = 0; i < r; ++i) M[i] = new int[c];

        for (int i = 0;i < X.r;++i)
        {
            for (int k = 0; k < X.c; ++k) M[i][k] = X.M[i][k];
          
        }
        }
    matrix(matrix& X, int a) {
        this->r = X.r;
        this->c = X.c;

        M = new int* [r];
        for (int i = 0; i < r; ++i) M[i] = new int[c];

        for (int i = 0;i < X.r;++i)
        {
            for (int k = 0; k < X.c; ++k) M[i][k] = X.M[i][k]+a;

        }
    }


    friend std::ostream& operator << (std::ostream &out, const matrix &X); 
    friend std::istream& operator >> (std::istream &in, matrix& X);
   
};
std::istream& operator >> (std::istream& in, matrix& X)
{
    int a;
    int r=0;
        int c=0;
        for (int i = 0; i < (X.r * X.c);++i) {
            in >> a; 
            if (c >= X.c) { c = 0; ++r; };
            X.M[r][c] = a;
            ++c;
        
        }
            return in;
        
}
std::ostream& operator << (std::ostream& out, const matrix& X)
{
    for (int i=0;i<X.r;++i)
    {
        for (int k = 0; k < X.c; ++k) out << X.M[i][k]<< "  ";
        out << std::endl;
    }
    return out;
}

int main()
{
    matrix A(2, 3);
    std::cin >> A;
    std::cout << A << std::endl;
    matrix B(A);
    std::cout << B << std::endl;
    matrix C(A,10);
    std::cout << C << std::endl; 
        return 0;
}
