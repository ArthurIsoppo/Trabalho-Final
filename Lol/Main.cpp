// Main.cpp

#include <iostream>
#include <vector>
#include "Champion.h"

using namespace std;

int main() {
//Parte do arquivo e objetos
    string filename = "champions_data.txt";
    vector<Champion> champions = readChampions(filename);

    if (champions.empty()) {
        cerr << "Nenhum campeão foi lido do arquivo." << endl;
        return 1;
    }

cout << "Bem vindo! Sou sua assistente pessoal de League of Legends!" << endl;
cout << "Me chamo Patty" << endl;

//Funcao das opcoes e acoes
Patty(champions);

    return 0;
}
