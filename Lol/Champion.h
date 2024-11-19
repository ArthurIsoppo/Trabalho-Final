// Champion.h

#ifndef CHAMPION_H
#define CHAMPION_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Definição da struct Date
struct Date {
    int year;
    int month;
    int day;

    Date(int y, int m, int d) : year(y), month(m), day(d) {}
};

// Definição da classe Champion
class Champion {
public:
    string name;
    string role;
    double winrate;
    string classType;
    string mostMastery;
    Date launchDate;
    string build;

    // Construtor da classe Champion
    Champion(string n, string r, double w, string c, string m, Date d, string b)
        : name(n), role(r), winrate(w), classType(c), mostMastery(m), launchDate(d), build(b) {}

    // Função para imprimir os detalhes do campeão
    void printDetails();
};

// Declaração das funções auxiliares
vector<string> split(const string &s, char delimiter);
vector<Champion> readChampions(const string &filename);
void biggestWinRate(const vector<Champion>& champions);
void championBuild(const vector<Champion>& champions, const string &name);
void tableChamp (const vector<Champion>& champions);
void Patty(const vector<Champion>& champions);
void randomizer(const vector<Champion>& champions, const string& lane);

#endif
