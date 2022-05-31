
#include <iostream>

class Game {
    char G[3][3];
public:
    Game() { for (int i = 0; i <= 2; ++i) { for (int k = 0; k <= 2; ++k) { G[i][k] = ' '; } } };

    void setS_x(int p, int v) { G[p][v] = 'X'; };
    void setS_o(int p, int v) { G[p][v] = 'O'; };

    void tablica() {
        std::cout << "  " << "0" << "   " << "1" << "   " << "2" << std::endl;
        for (int i = 0;i <= 2;++i) { std::cout << i << " " << G[i][0] << " | " << G[i][1] << " | " << G[i][2] << std::endl; }
    }

    void startGame()
    {
        bool win = 0;
        int hod = 0;
        int p = 0, v = 0;
        bool pk = 0;
        tablica();
        while ((win == 0) && (hod < 10))
        {
            tablica();
            std::cout << "Введите клетку" << std::endl;
            while (pk == 0)
            {
                std::cin >> p >> v;
                if ((G[p][v] != ' ')||(p>2)||(v>2)) {
                    std::cout << "Введите клетку корректно" << std::endl;
                }
                else { 
                    pk = 1; 
                    if ((hod % 2) == 1) { setS_x(p, v);/* G[p][v] = 'X';*/ }
                    if ((hod % 2) == 0) { setS_o(p, v);/* G[p][v] = 'O';*/ }
                }
            }
            

            if (hod >= 5) 
            {
                for (int i = 0; i <= 2; ++i) {
                    if ((G[i][0] == G[i][1])&&(G[i][1] == G[i][2])) {
                        win = 1;break;
                    }
                }
                for (int i = 0; i <= 2; ++i) {
                    if ((G[0][i] == G[1][i])&&(G[1][i] == G[2][i])) {
                        win = 1;break;
                    }
                }
                if ((G[0][0] == G[1][1])&&(G[1][1] == G[2][2]) || (G[0][2] == G[1][1])&&(G[1][1] == G[2][0])) {
                    win = 1;break;
                }
               
            }
            ++hod;
            pk = 0;
            if (win == 1)break;
        }
        tablica();
        if (win == 1) {
            if (((hod - 1) % 2) == 0) { std::cout << "O-player win!!!"; }
            else {
                std::cout << "X-player win!!!";
            }
        }
        else { std::cout << "Draw"; };
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    Game Gay;
    Gay.startGame();
    return 0;
}
