// zadacha 4.3 rimskie.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;


string toNumeral(unsigned long Number, bool Thousands)
{
    string units[] =
    { "один","два","три","четыре","пять","шесть", "семь","восемь","девять" };
    string tens[] =
    { "десять","двадцать","тридцать","сорок","пятьдесят","шестьдесят",
     "семьдесят", "восемьдесят","девяносто" };
    string hundreds[] =
    { "сто","двести","триста","четыреста","пятьсот","шестьсот","семьсот",
     "восемьсот","девятьсот" };
    string secondten[] =
    { "одиннадцать","двенадцать","тринадцать","четырнадцать","пятнадцать",
     "шестнадцать","семнадцать","восемнадцать","девятнадцать" };
    string Women[2] = { "одна","две" };
    string result("");                                // пустая строка-результат
    typedef unsigned char byte;
    byte digits[3] = { 0 };                 // - цифры числа
    unsigned long n = Number;
    digits[0] = n % 10;               //--младшая цифра
    digits[1] = (n / 10) % 10;            //--средняя цифра+
    digits[2] = n / 100;                  //--старшая цифра
    if (digits[2] > 0) result += (hundreds[digits[2] - 1] + " ");
    if (digits[1] > 0)
    {
        if ((digits[1] == 1) && (digits[0] != 0))
        {
            result += (secondten[digits[0] - 1] + " "); return result;
        }
        else result += (tens[digits[1] - 1] + " ");
    }
    if (digits[0] > 0)
    {
        if (((digits[0] > 2) && (digits[1] != 1)) || (!Thousands))
            result += (units[digits[0] - 1] + " ");
        else result += (Women[digits[0] - 1] + " ");
    }
    return result;
}

string Numeral(unsigned int Number)
{
    string what_[3][3] = { {"миллион", "миллиона", "миллионов" },
             {"тысяча",  "тысячи",   "тысяч"     },
            };
    unsigned int t = Number;
    unsigned int treads[3];     //--вычисление троек числа
    treads[0] = t % 1000; treads[1] = t / 1000 % 1000; treads[2] = t / 1000000;
    string result = "";
    if (treads[2] > 0) {
        result += toNumeral(treads[2], false);
        if (treads[2] / 10 % 10 == 1) result += what_[0][2];                    //-1-
        else
            switch (treads[2] % 10)
            {
            case 0: case 5: case 6: case 7: case 8: case 9:
                result += what_[0][2]; break;
            case 2: case 3: case 4: result += what_[0][1]; break;
            case 1:                  result += what_[0][0]; break;
            }
        result += ' ';
    }
    if (treads[1] > 0) {
        result += toNumeral(treads[1], true);
        if (treads[1] / 10 % 10 == 1) result += what_[1][2];                      //-2-
        else switch (treads[1] % 10)
        {
        case 0: case 5: case 6:
        case 7: case 8: case 9: result += what_[1][2]; break;
        case 2: case 3: case 4: result += what_[1][1];break;
        case 1:                  result += what_[1][0];break;
        }
        result += ' ';
    }
    result += toNumeral(treads[0], false);
    






    return result;
}















int main()
{
    setlocale(0, "");
    char v[15];
    int c[7] = { 1, 5, 10, 50, 100, 500, 1000 };
    char b[7] = { 'I','V','X','L','C','D','M' };
    char x;
    int s = 0;
    int i = 1;
    std::cin >> x;
    v[0] = x;
    while (x != 'O') {
        std::cin >> x;
        v[i] = x;
        ++i;
    }
    int n1 = -1;
    int n2 = -1;

    for (int i = 0;v[i] != 'O';++i)
    {
        if (v[i] == 'M') { n1 = i;break; }


        if (n1 == -1) {
            for (int i = 0;v[i] != 'O';++i) {
                if (v[i] == 'D') { n1 = i;break; }
            }
        }
        if (n1 == -1) {
            for (int i = 0;v[i] != 'O';++i) {
                if (v[i] == 'C') { n1 = i;break; }
            }
        }
        if (n1 == -1) {
            for (int i = 0;v[i] != 'O';++i) {
                if (v[i] == 'L') { n1 = i;break; }
            }
        }
        if (n1 == -1) {
            for (int i = 0;v[i] != 'O';++i) {
                if (v[i] == 'X') { n1 = i;break; }
            }
        }if (n1 == -1) {
            for (int i = 0;v[i] != 'O';++i) {
                if (v[i] == 'V') { n1 = i;break; }
            }
        }if (n1 == -1) {
            for (int i = 0;v[i] != 'O';++i) {
                if (v[i] == 'I') { n1 = i;break; }
            }
        }

        if (v[i + 1] == 'O') { n2 = i; };

    }






    int ind = 1;
    int nomp=0;
    int nomp1=0;
    for (int i = n1 + 1;v[i + 1] != 'O';++i) {
        if (v[i] == 'M') { nomp = 6; }
        else {
            if (v[i] == 'D') { nomp = 5; }
            else {
                if (v[i] == 'C') { nomp = 4; }
                else {
                    if (v[i] == 'L') { nomp = 3; }
                    else {
                        if (v[i] == 'X') { nomp = 2; }
                        else {
                            if (v[i] == 'V') { nomp = 1; }
                            else {
                                if (v[i] == 'I') { nomp = 0; }
                            }
                        }
                    }
                }
            }
        }
        if (v[i + 1] == 'M') { nomp1 = 6; }
        else {
            if (v[i + 1] == 'D') { nomp1 = 5; }
            else {
                if (v[i + 1] == 'C') { nomp1 = 4; }
                else {
                    if (v[i + 1] == 'L') { nomp1 = 3; }
                    else {
                        if (v[i + 1] == 'X') { nomp1 = 2; }
                        else {
                            if (v[i + 1] == 'V') { nomp1 = 1; }
                            else {
                                if (v[i + 1] == 'I') { nomp1 = 0; }
                            }
                        }
                    }
                }
            }
        }
        if (nomp < nomp1) { ind = 0; }
    }

    int prov = 1;
    for (int i = 0;i < n1;++i) { if (v[0] != v[i]) { prov = 0; } }

    if ((n1 > 0) && (n2 != n1)) { prov = 0; }








    int pred = 0;

    int sprov = 0;
    int eprov=0;
    for (int i = n1 + 1;i <= n2;++i)
    {
        if (v[i] == 'M') { sprov = sprov + 1000; if (pred < 1000) { sprov = sprov - 2 * pred; };pred = 1000;
        }
        else {
            if (v[i] == 'D') { sprov = sprov + 500;if (pred < 500) { sprov = sprov - 2 * pred; };pred = 500;
            }
            else {
                if (v[i] == 'C') { sprov = sprov + 100;if (pred < 100) { sprov = sprov - 2 * pred; };pred = 100;
                }
                else {
                    if (v[i] == 'L') { sprov = sprov + 50; if (pred < 50) { sprov = sprov - 2 * pred; };pred = 50;
                    }
                    else {
                        if (v[i] == 'X') { sprov = sprov + 10;if (pred < 10) { sprov = sprov - 2 * pred; };pred = 10;
                        }
                        else {
                            if (v[i] == 'V') { sprov = sprov + 5; if (pred < 5) { sprov = sprov - 2 * pred; };pred = 5;
                            }
                            else {
                                if (v[i] == 'I') { sprov = sprov + 1; if (pred < 1) { sprov = sprov - 2 * pred; };pred = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (v[n1] == 'M') { eprov = 1000; }
    else {
        if (v[n1] == 'D') { eprov = 500; }
        else {
            if (v[n1] == 'C') { eprov = 100; }
            else {
                if (v[n1] == 'L') { eprov = 50; }
                else {
                    if (v[n1] == 'X') { eprov = 10; }
                    else {
                        if (v[n1] == 'V') { eprov = 5; }
                        else {
                            if (v[n1] == 'I') { eprov = 1; }
                        }
                    }
                }
            }
        }
    }
        if (eprov<=sprov) { prov = 0; }













        pred = 0;

    if (((n1 > 1)&&(prov == 0)) || ((n1 >= 0) && (n2 - n1 > 0)&&(prov == 0)) || ((ind == 0)&&(prov == 0))) { std::cout << "neverno vvedeno"; }
    else {
        if (n1 == 0) {
            for (int i = 0;v[i] != 'O';++i)
            {
                if (v[i] == 'M') { s = s + 1000; if (pred < 1000) { s = s - 2 * pred; };pred = 1000; }
                else {
                    if (v[i] == 'D') { s = s + 500; if (pred < 500) { s = s - 2 * pred; };pred = 500;
                    }
                    else {
                        if (v[i] == 'C') { s = s + 100; if (pred < 100) { s = s - 2 * pred; };pred = 100;
                        }
                        else {
                            if (v[i] == 'L') { s = s + 50; if (pred < 50) { s = s - 2 * pred; };pred = 50;
                            }
                            else {
                                if (v[i] == 'X') { s = s + 10; if (pred < 10) { s = s - 2 * pred; };pred = 10;
                                }
                                else {
                                    if (v[i] == 'V') { s = s + 5; if (pred < 5) { s = s - 2 * pred; };pred = 5;
                                    }
                                    else {
                                        if (v[i] == 'I') { s = s + 1; if (pred < 1) { s = s - 2 * pred; };pred = 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        if (n1 == 1) {
            for (int i = 1;v[i] != 'O';++i)
            {
                if (v[i] == 'M') { s = s + 1000; }
                else {
                    if (v[i] == 'D') { s = s + 500; }
                    else {
                        if (v[i] == 'C') { s = s + 100; }
                        else {
                            if (v[i] == 'L') { s = s + 50; }
                            else {
                                if (v[i] == 'X') { s = s + 10; }
                                else {
                                    if (v[i] == 'V') { s = s + 5; }
                                    else {
                                        if (v[i] == 'I') { s = s + 1; }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            if (v[0] == 'M') { s = s - 1000; }
            if (v[0] == 'D') { s = s - 500; }
            if (v[0] == 'C') { s = s - 100; }
            if (v[0] == 'L') { s = s - 50; }
            if (v[0] == 'X') { s = s - 10; }
            if (v[0] == 'V') { s = s - 5; }
            if (v[0] == 'I') { s = s - 1; }
        }
        if (n1 > 1) { std::cout << "neverno vvedeno";
        }
        /*
            if (v[n1] == 'M') { s = s + 1000; }
            if (v[n1] == 'D') { s = s + 500; }
            if (v[n1] == 'C') { s = s + 100; }
            if (v[n1] == 'L') { s = s + 50; }
            if (v[n1] == 'X') { s = s + 10; }
            if (v[n1] == 'V') { s = s + 5; }
            if (v[n1] == 'I') { s = s + 1; }
 
            for (int i = 0;i < n1;++i) {
                if (v[i] == 'M') { s = s - 1000; }
                else {
                    if (v[i] == 'D') { s = s - 500; }
                    else {
                        if (v[i] == 'C') { s = s - 100; }
                        else {
                            if (v[i] == 'L') { s = s - 50; }
                            else {
                                if (v[i] == 'X') { s = s - 10; }
                                else {
                                    if (v[i] == 'V') { s = s - 5; }
                                    else {
                                        if (v[i] == 'I') { s = s - 1; }
                                    }
                                }
                            }
                        }
                    }
                }
            }   
                
        }*/
    std::cout << s <<"  "<< Numeral(s);
}
    return 0;
}