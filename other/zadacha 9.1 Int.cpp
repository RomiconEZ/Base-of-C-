

#include <cmath>
#include <iostream>


 long double func_y( long double  x)
{
    return (exp(x) * sin(x) * (pow(x, 2) + log(pow(sin(x), 4) + pow(cos(x), 4)))) / pow(x,3);
}

 long double RRect_Solve(long double a, long double b,long double dx)
{
    if (a > b)
    {
        return 0;
    }
     long double x = a;
    long double S = 0.0;
    /*while (x+dx <= b)*/for(int i=0;i<1000;++i)
    {
        
       /* S = S+ (dx * (func_y(x + dx)));*/
        S = S + func_y(x + dx);
        x = dx + x;
        
    }
    S = S * dx;
    return S;
}
long double lRect_Solve( long double a, long double b,  long double dx)
{
    if (a > b)
    {
        return 0;
    }
    long double x = a;
    long double S = 0.0;
    /*while (x <= b)*/for (int i = 0;i < 1000;++i)
    {
        S = S + func_y(x);
        x =x+ dx;
    }
    S = S * dx;
    return S;
}

long double Trap_Solve(long double a, long double b, long double dx)
{
    if (a > b)
    {
        return 0;
    }
     long double x = a;
    long double S = 0.0;
    /*while (x + dx <b)*/for (int i = 0;i < 1000;++i)
    {
        S = S+(func_y(x) + func_y(x + dx)) / 2.;
        x += dx;
    }
    S = S * dx;
    return S;
}
long double Monte_Solve(long double a,long double b, long double dx)
{
    if (a > b)
    {
        return 0;
    }
    long double x = a;
    long double max = abs(func_y(x));
    for (int i = 0;i < 1000;++i)
    {
        x += dx;
        if (abs(func_y(x)) > max) { max = abs(func_y(x)); }
        
    }
    long double ot = 0., npt = 0.;
    long double nott = 0.;
    long double s;
    long double dy;
    x = a;
    for (int i = 0;i < 1000;++i)
    {
        dy = 0.;
        while (dy <= max)
        {
            if (dy <= abs(func_y(x))) { if (func_y(x) > 0) { ++npt; } else { ++nott ; }++ot; }
            else { ++ot; }
            dy += max/100;
        }
        x += dx;
    }
    s = (npt / ot)*((b-a)*max)- (nott / ot) * ((b - a) * max);
    return s;
}

int main()
{
     long double ll, rl;
    std::cin >> ll >> rl;
    long double dr = (rl - ll)/ 1000.;
    long double S = RRect_Solve(ll, rl, dr);
    std::cout << "== rightRect ==" << std::endl << S << std::endl;
    
    S = lRect_Solve(ll, rl, dr);
    std::cout <<"== leftRect =="<< std::endl<< S << std::endl;


    S = Trap_Solve(ll, rl, dr);
    std::cout <<"== Trap ==" << std::endl << S << std::endl;

    S = Monte_Solve(ll, rl, dr);
    std::cout << "== Monte-Carlo ==" << std::endl << S << std::endl;
    
   /* for (int i = 0;i < 50;++i) {
        cout << func_y(i)<<"   ";
    }*/
    
    return 0;
}
