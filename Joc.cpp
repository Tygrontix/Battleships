#include <iostream>
#include <thread>
#include <cstring>
#include <chrono>
#include <cstdlib>
using namespace std;

char mat1[11][11], mat2[11][11], mat_oponent[11][11];
int castigator = 0;

// ==============================================================================
// ||                                Structuri                                 ||
// ==============================================================================

struct Pozitie {
    int x, y;
};

Pozitie vapor[4];
int segmente_vapor_utilizate = 0;

// ==============================================================================
// ||                                 Design                                   ||
// ==============================================================================

void loading_screen() {
    cout << endl << "Inamicul isi pozitioneaza vapoarele...";
    this_thread::sleep_for(chrono::seconds(5));
}

void space() { // mizeria asta de functie hahahhaha :)))
    for(int i = 0; i<10 ; ++i)
        cout << endl;
}

// Potential, probabil nu va fi folosit.
/*void enunt() {
    cout << "Salut!" << endl << "1. Start Joc" << endl << "2. Iesi" << endl;
    int n;
    cin >> n;
    if(n==2)
        
}*/

// ==============================================================================
// ||                               Verificari                                 ||   
// ==============================================================================

/*
bool este_optiune_valida(int x, int y, char mat[11][11]) {
    if (!pozitie_valida(x, y)) 
        return false;

    if (segmente_vapor_utilizate == 0) {
        return are_loc_complet(x, y, mat);
    }

    if (segmente_vapor_utilizate == 1) {
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; ++i) {
            int nx = vapor[0].x + dx[i];
            int ny = vapor[0].y + dy[i];
            if (nx == x && ny == y && pozitie_valida(nx, ny)) {
                int rest = 3;
                for (int j = 1; j < 4; ++j) {
                    int fx = nx + dx[i] * j;
                    int fy = ny + dy[i] * j;
                    if (fx < 1 || fx > 10 || fy < 1 || fy > 10 || mat[fx][fy] != '.') {
                        rest = -1;
                        break;
                    }
                }
                if (rest != -1)
                    return true;
            }
        }
        return false;
    }

    int dx = vapor[1].x - vapor[0].x;
    int dy = vapor[1].y - vapor[0].y;

    int x_fata = vapor[segmente_vapor_utilizate - 1].x + dx;
    int y_fata = vapor[segmente_vapor_utilizate - 1].y + dy;

    int x_spate = vapor[0].x - dx;
    int y_spate = vapor[0].y - dy;

    bool valid_fata = (x == x_fata && y == y_fata && pozitie_valida(x_fata, y_fata));
    bool valid_spate = (x == x_spate && y == y_spate && pozitie_valida(x_spate, y_spate));

    return valid_fata || valid_spate;
}
*/

// !!!!!!!!!!! Incearca cu varianta de mai de sus

bool are_loc_complet(int x, int y, char matrice[11][11]) {
    bool ok = false;

    int px = x - segmente_vapor_utilizate, py = y - segmente_vapor_utilizate;

    for (int i = 1; i <= 4; ++i) {
        if((matrice[px][py+i] == '.') && (matrice[px+i][py] == '.') && (matrice[px][py-i] == '.') && (matrice[px-i][py] == '.'))
            ok = true;
    }
    cout << ok << "]";
    return ok;
}

bool pozitie_valida(int x, int y) {
    if(segmente_vapor_utilizate == 1)
    {
        bool k=0;
        if((x >= 1 && x <= 10 && y >= 1 && y <= 10 && mat1[x][y] == '.') || (x >= 1 && x <= 10 && y >= 1 && y <= 10 && mat1[x][y] == '.') || (x >= 1 && x <= 10 && y >= 1 && y <= 10 && mat1[x][y] == '.') ||(x >= 1 && x <= 10 && y+3 >= 1 && y <= 10 && mat1[x][y] == '.'))
           k=1;
        return k;
    }
    else
        return x >= 1 && x <= 10 && y >= 1 && y <= 10 && mat1[x][y] == '.';
}

bool este_optiune_valida(int x, int y, char mat[11][11]) {
    if (!pozitie_valida(x, y)) 
        return false;

    if (segmente_vapor_utilizate == 0) {
        if (are_loc_complet(x, y, mat))
            return true;
    }

    if (segmente_vapor_utilizate == 1) {
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        for (int i = 0; i < 4; ++i) {
            int nx = vapor[0].x + dx[i];
            int ny = vapor[0].y + dy[i];
            if (nx == x && ny == y)
                return true;
        }
        return false;
    }

    int dx = vapor[1].x - vapor[0].x;
    int dy = vapor[1].y - vapor[0].y;

    int x_fata = vapor[segmente_vapor_utilizate - 1].x + dx;
    int y_fata = vapor[segmente_vapor_utilizate - 1].y + dy;

    int x_spate = vapor[0].x - dx;
    int y_spate = vapor[0].y - dy;

    return (x == x_fata && y == y_fata) || (x == x_spate && y == y_spate);
}

// ==============================================================================
// ||                                Afisari                                   ||
// ==============================================================================

void afisare_matrice(char mat[11][11]) {
    space();
    cout << endl << "> Harta ta <" << endl << endl << "X | ";
    for(char litera = 'A'; litera < 'A' + 10; ++litera)
        cout << litera << " ";
    cout << endl << "- + - - - - - - - - - -";

    for(int i = 1; i <= 10; ++i) {
        if(i < 10) 
            cout << endl << i << " | ";
        else       
            cout << endl << i << "| ";

        for(int j = 1; j <= 10; ++j)
            cout << mat[i][j] << " ";
    }
    cout << endl;
}

void afisare_matrice_inamic(char mat[11][11], char mat_inamic[11][11]) {
    space();
    cout << endl << "> Harta ta <                   " << "> Harta Inamic <" << endl << endl << "X | ";

    for(char litera = 'A'; litera < 'A' + 10; ++litera)
        cout << litera << " ";
    cout << "  ||   X | ";

    for(char litera = 'A'; litera < 'A' + 10; ++litera)
        cout << litera << " ";

    cout << endl << "- + - - - - - - - - - -   ||   - + - - - - - - - - - -";

    int j;

    for(int i = 1; i <= 10; ++i) {
        if(i < 10) 
            cout << endl << i << " | ";
        else       
            cout << endl << i << "| ";

        for(j = 1; j <= 10; ++j)
            cout << mat[i][j] << " ";

        cout << "  ||   ";
        if(i < 10) 
            cout << i << " | ";
        else       
            cout << i << "| ";

        for(j = 1; j <= 10; ++j)
            cout << mat_inamic[i][j] << " ";  // 4 d 3 d 2 d 1 d
    }
    cout << endl;
}

void afisare_optiuni(int lungime_vapor) {
    if (lungime_vapor >= 4) 
        return;

    cout << endl << "Pozitii valide pentru plasarea vaporului:" << endl;

    for (int i = 1; i <= 10; ++i) {
        for (int j = 1; j <= 10; ++j) {
            if (este_optiune_valida(i, j, mat1)) {
                cout << "- (" << i << ", " << char('A' + j - 1) << ")" << endl;
            }
        }
    }
}

// versiune veche pentru afisarea matricei 2.
/*
void afisare_matrice_inamic(char mat[11][11]) {
    cout << endl << "> Harta Inamic <" << endl << endl << "X | ";
    for(char litera = 'A'; litera < 'A' + 10; ++litera)
        cout << litera << " ";
    cout << endl << "- + - - - - - - - - - -";

    for(int i = 1; i <= 10; ++i) {
        if(i < 10) 
            cout << endl << i << " | ";
        else       
            cout << endl << i << "| ";

        for(int j = 1; j <= 10; ++j)
            cout << mat[i][j] << " ";
    }
    cout << endl;
}
*/

// ==============================================================================
// ||                       Schimb intre tipuri de date                        ||
// ==============================================================================

int litera_in_coloana(char l) {
    if(l >= 'A' && l <= 'Z') 
        return l - 'A' + 1;
    if(l >= 'a' && l <= 'z') 
        return l - 'a' + 1;
    return -1;
}

// ==============================================================================
// ||                             Functionalitate                              ||
// ==============================================================================

void coordonate_input(int& a, int& b) {
    int l;
    char c;
    b=0;
    while(b==0) {
        cout << endl << "Introdu coordonate: ";
        cin >> l >> c;
        a = l;
        if(!strchr("abcdefghijABCDEFGHIJ", c)) {
            cout << "Trebuie sa introduci un numar si o litera!";
            continue;
        }
        b = litera_in_coloana(c);
    }
}

void plasare_vapor() {
    while (segmente_vapor_utilizate < 4) {
        int x, y;
        coordonate_input(x, y);

        if (!pozitie_valida(x, y)) {
            cout << "Pozitie invalida!" << endl;
            continue;
        }

        if (!este_optiune_valida(x, y, mat1)) {
            cout << "Pozitie invalida!" << endl;
            continue;
        }

        mat1[x][y] = 'o';

        if (segmente_vapor_utilizate == 0 || 
            (x == vapor[0].x - (vapor[1].x - vapor[0].x) && y == vapor[0].y - (vapor[1].y - vapor[0].y))) {
            for (int i = segmente_vapor_utilizate; i > 0; --i) {
                vapor[i] = vapor[i - 1];
            }
            vapor[0] = {x, y};
        } else {
            vapor[segmente_vapor_utilizate] = {x, y};
        }

        segmente_vapor_utilizate++;

        afisare_matrice(mat1);
        if (segmente_vapor_utilizate < 4)
            afisare_optiuni(segmente_vapor_utilizate);
    }
    segmente_vapor_utilizate=0;
}

void atac() {
    int x, y;
    afisare_matrice_inamic(mat1, mat2);
    coordonate_input(x,y);
    mat2[x][y] = 'x';

/*  if(x == ? && y == ?)
        mat2[x][y] = 'x';
    else
        mat2[x][y] = '~'; 
*/

    afisare_matrice_inamic(mat1, mat2);
}

void pozitionare_vapoare() {
    cout << "Sa inceapa jocul !" << endl;

    for(int i = 1; i <= 10; ++i)
        for(int j = 1; j <= 10; ++j)
        {
            mat1[i][j] = '.';
            mat2[i][j] = '.';
        }

    afisare_matrice(mat1);
    plasare_vapor();
    plasare_vapor();
}

// ==============================================================================
// ||                                Oponent                                   ||
// ==============================================================================

void coordonate_random(int &random_x, int &random_y) {
    srand(time(NULL));

    random_x = (rand() % 10 ) + 1;
    random_y = (rand() % 10 ) + 1;
}

void harta_oponent() {
    int x,y,directie;
    directie = ( rand() % 4 ) + 1;

    coordonate_random(x, y);
    mat_oponent[x][y] = 'o';
/*
    if(mat_oponent != '.')
        //aici ~~!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
}

// ==============================================================================
// ||                                   JOC                                    ||
// ==============================================================================

void joc() {
    pozitionare_vapoare();
    loading_screen();
    harta_oponent();
    while(castigator == 0) {
        atac();
    }
}

// Probleme de rezolvat:
// - La introducerea unei litere la inceput, ( d 5 ), intra in ciclare infinita.
// - Verifica daca o barca are sau nu loc, si evita afisarea optiunilor atunci cand barca nu poate fi completata. ( Problema intimpinata la plasarea celui de al 2 lea vapor )
// - Mai fa jocu nu ?

int main() {
    joc();
    return 0;
}
