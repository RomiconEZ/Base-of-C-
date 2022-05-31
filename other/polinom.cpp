#include <iostream>



int main()
{
    double a;
    double b;
    double c;
    double d;
    double x1;
    double x2;
    double x3;
    std::cin >> a >> b >> c;
    if ((a == 0) && (b == 0) && (c == 0)) { std::cout << "x = R"; }
    else {

        if ((a == 0) && (b == 0) && (c != 0) || ((b == 0) && (c > 0) && (a > 0))) { std::cout << "net korney"; }
        else {
            if ((c > 0) && (b == 0) && (a < 0)) { std::cout << "+/-" << sqrt(c / abs(a)); }
            else {
                if ((c == 0) && (b == 0) && (a != 0)) { std::cout << "x = 0"; }
                else {
                    if ((c < 0) && (b == 0) && (a > 0)) { std::cout << "x = " << ((-c) / a); }
                    else
                    {
                        if ((a == 0) && (b != 0) && (c != 0)) { std::cout << ((-c) / b); }
                        else {
                            if ((b == 0) && (c > 0) && (a != 0)) { std::cout << "x1 = 0" << "x2 = " << (-b) / a; }
                            else {
                                if ((b != 0) && (c == 0) && (a == 0)) { std::cout << "x = 0"; }
                                else {
                                    d = b * b - 4. * a * c;
                                    if (d > 0)
                                    {

                                        x1 = (-b - sqrt(d)) / (2. * a);
                                        x2 = (((-b) + sqrt(d)) / (2. * a));
                                        std::cout << x1 << ' ' << x2;
                                    }
                                    else
                                    {
                                        if (d == 0.)
                                        {
                                            x3 = -(b / (2. * a));
                                            std::cout << x3;
                                        }
                                        else { std::cout << "net korney"; }
                                    }
                                }



                            }
                        }
                    }
                }
            }
        }



        return 0;
    }
}


