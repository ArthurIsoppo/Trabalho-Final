// Champion.cpp

#include "Champion.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <iomanip>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

// Split por delimitador, no caso a gente vai usar ;
vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Funcao que le o arquivo e cria os objetos Champion
vector<Champion> readChampions(const string &filename) {
    vector<Champion> champions;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        return champions;
    }

    //cout << "Arquivo aberto com sucesso: " << filename << endl;

    string line;
    getline(file, line);
    //cout << "Cabeçalho ignorado: " << line << endl;

    while (getline(file, line)) {
        //cout << "Lendo linha: " << line << endl;
        vector<string> fields = split(line, ';');

        if (fields.size() != 7) {
            cerr << "Erro ao ler linha: " << line << endl;
            continue;
        }

        string name = fields[0];
        string role = fields[1];
        double winrate = stod(fields[2].find(',') != string::npos ? fields[2].replace(fields[2].find(','), 1, ".") : fields[2]);
        string classType = fields[3];
        string mostMastery = fields[4];
        vector<string> dateFields = split(fields[5], '-');
        string build = fields[6];

        if (dateFields.size() != 3) {
            cerr << "Erro ao ler data: " << fields[5] << endl;
            continue;
        }

        Date launchDate(stoi(dateFields[0]), stoi(dateFields[1]), stoi(dateFields[2]));

        //cout << "Criando Champion: " << name << endl;
        Champion champion(name, role, winrate, classType, mostMastery, launchDate, build);
        champions.push_back(champion);
    }

    file.close();
    //cout << "Arquivo fechado: " << filename << endl;
    return champions;
}


// Teste
/*
void Champion::printDetails() {
    string formattedBuild = regex_replace(build, regex("/n"), "\n");

    cout << "Name: " << name << endl;
    cout << "Role: " << role << endl;
    cout << "Winrate: " << winrate << endl;
    cout << "Class: " << classType << endl;
    cout << "Most Mastery: " << mostMastery << endl;
    cout << "Launch Date: " << launchDate.year << "/" << launchDate.month << "/" << launchDate.day << endl;
    cout << "Build: " << endl << formattedBuild << endl;
}
*/

// Maior winrate
void biggestWinRate(const vector<Champion>& champions) {
    double enourmous = 0;
    string oPika;
    for (const Champion& champ : champions) {
        if (champ.winrate > enourmous) {
            enourmous = champ.winrate;
            oPika = champ.name;
        }
    }
    cout << "O campeao com o maior winrate eh: " << oPika << ", com: " << enourmous << "%" << " de winrate" << endl;
}

// funcao para deixar os "/n" funcionais
string formatBuild(const string &build) {
    return regex_replace(build, regex("/n"), "\n");
}

// Funcao que imprime a build
void championBuild(const vector<Champion>& champions, const string &name) {
    for (auto it = champions.cbegin(); it != champions.cend(); ++it) {
        if (it->name == name) {
            cout << "|Best Build for " << it->name << ':' << endl;
            cout << formatBuild(it->build) << endl;
            return;
        }
    }
}

// operator overloading para o "<<" funcionar com a struct date
ostream& operator<<(ostream& os, const Date& data) {
    os << data.day << '/' << data.month << '/' << data.year;
    return os;
}

//Tabelinha mto massa com a lista dos campeos
void tableChamp(const vector<Champion>& champions) {
    cout << left << setw(15) << "Name" 
              << setw(10) << "Winrate" 
              << "Launch Date\n";
    cout << "----------------------------------------\n";
    
    for (auto it = champions.cbegin(); it != champions.cend(); ++it) {
        cout << left << setw(15) << it->name 
                  << setw(10) << it->winrate 
                  << it->launchDate << "\n";
    }
}

void randomizer(const vector<Champion>& champions, const string& lane) {
vector<Champion> aux;

for (const Champion& champ : champions) {
    if(champ.role == lane) {
        aux.push_back(champ);
    }
}

if (aux.empty()) {
    cout << "Nenhum campeao para essa rota" << endl;
    return;
}

srand(time(0));

random_shuffle(aux.begin(), aux.end());

const Champion& theChosenOne = aux.front();

cout << "O campeao selecionado foi: " << theChosenOne.name << endl;
championBuild(aux, theChosenOne.name);
}

void Patty(const vector<Champion>& champions) {
    int option = 100;

    cout << "Como posso te ajudar?" << endl;
    cout << "(0) \"Desejo ver sua lista de campeoes\"" << endl;
    cout << "(1) \"Desejo saber a Build do campeao X\"" << endl;
    cout << "(2) \"Desejo saber qual o campeao com a maior Winrate\"" << endl;
    cout << "(3) \"Desejo um campeao aleatorio para eu jogar na lane X\"" << endl;
    cin >> option;

    if (option == 0) {
        tableChamp(champions);
    } else if (option == 1) {
        string championName;
        cout << "Certo! Poderia por favor me dizer o nome do campeao para eu executar a tarefa?" << endl;
        cin >> championName;
        cout << "Muito obrigada!" << endl;
        championBuild(champions, championName);
    } else if (option == 2) {
        biggestWinRate(champions);
    } else if (option == 3) {
                string lane;
        cout << "Certo! Poderia por favor me dizer a lane para eu executar a tarefa?" << endl;
        cin >> lane;
        cout << "Muito obrigada!" << endl;
        randomizer(champions, lane);
    } else {
        cout << "Nao seja bobao! Insira um numero valido" << endl;
        Patty(champions);
        return;
    }

    // Adicionando o separador
    cout << "-------------------------------------------" << endl;

    string soption;
    cout << "Deseja fazer mais alguma coisa? (y/n)" << endl;
    cin >> soption;

    if (soption == "y") {
        Patty(champions);
    } else {
        cout << "Obrigada por usar a assistente Patty! Até a próxima!" << endl;
    }
}

