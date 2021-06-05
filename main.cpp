#include <iostream>
#include "TSP_Tura.h"
#include <cmath>
#include <fstream>
using namespace std;

// Euklidska udaljenost
int udaljenost(double x1, double y1, double x2, double y2) {
    return round(sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)));
}

// vrati matricu udaljenosti gradova iz fajla
vector<vector<int>> ucitaj_fajl(string filename) {
    ifstream unos(filename);
    vector<Grad> gradovi;

    while(!unos.eof()) {
        int indeks;
        double latitude;
        double longitude;
        unos>>indeks;
        unos.get();
        unos>>latitude;
        unos.get();
        unos>>longitude;
        unos.get();
        gradovi.push_back(Grad(indeks,latitude,longitude));
    }
    unos.close();

    int n = gradovi.size();
    vector<vector<int>> udaljenosti(n, vector<int>(n));

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            udaljenosti[i][j] = udaljenost(gradovi[i].latitude,gradovi[i].longitude,gradovi[j].latitude,gradovi[j].longitude);

    return udaljenosti;
}

int main() {
    vector<vector<int>> u(ucitaj_fajl("./data/sahara.txt"));
    TSP_Tura tura(u.size(), u, false);

    vector<int> vracena = tura.vrati_vektor_ture();
    cout<<"Duzina pocetne ture: "<<tura.duzinaTure()<<endl;

    tura._2opt();
    vracena = tura.vrati_vektor_ture();
    cout<<"Duzina 2opt ture: "<<tura.duzinaTure()<<endl;

    tura._3opt();

    vracena = tura.vrati_vektor_ture();
    cout<<"Duzina 3opt ture: "<<tura.duzinaTure()<<endl;

    cout<<endl;
}
