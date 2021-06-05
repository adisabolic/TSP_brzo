#ifndef TSP_TURA_H
#define TSP_TURA_H

#include <iostream>
#include <vector>
using namespace std;

struct Grad
{
    int indeks;
    double latitude;
    double longitude;
    Grad(int indeks, double latitude, double longitude):indeks(indeks), latitude(latitude), longitude(longitude) {}
};

class TSP_Tura
{
    public:
    struct Cvor {
        int id;
        Cvor *susjed1, *susjed2;
        Cvor(int id, Cvor* s1 = nullptr, Cvor* s2 = nullptr): id(id), susjed1(s1), susjed2(s2) {}
    };

    Cvor *korijen; // prvi grad
    int n; // broj gradova
    vector<vector<int>> udaljenosti; // matrica udaljenosti
    vector<Cvor*> cvorovi; // niz cvorova grafa
    void zamijeni_susjede(Cvor*, Cvor*, Cvor*); // susjed prvog cvora koji je jednak drugom cvoru postavi na treci

public:
    TSP_Tura(int, vector<vector<int>>&, bool); // broj_gradova, matrica udaljenosti, bool da li pocetnu turu napraviti random ili 0->1->...->n-1->0
    TSP_Tura(vector<int>&, vector<vector<int>>&); // pocetna tura, matrica udaljenosti

    vector<int> vrati_vektor_ture(); // vraca vektor trenutne ture

    bool _2opt_uslov(pair<int, int>, pair<int, int>); // provjerava da li se isplati zamijeniti grane i->i+1 i j->j+1 sa i->j i i+1->j+1
    bool _3opt_uslov(pair<int, int>, pair<int, int>, pair<int, int>, int); // provjerava da li se isplati zamijeniti tri grane, zadnji parametar je vrsta 3opt zamjene
    void zamijeni_grane(pair<int, int>, pair<int, int>); // za 2opt - mijenja grane i->i+1 i j->j+1 sa i->j i i+1->j+1
    void zamijeni_grane(pair<int, int>, pair<int, int>, pair<int, int>, int); // 3opt - mijenja 3 grane (3opt), zadnji parametar je vrsta 3opt zamjene
    void _2opt();
    void _3opt();
    int duzinaTure();
};

#endif // TSP_TURA_H
