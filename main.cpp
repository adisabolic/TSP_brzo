#include <iostream>
#include "TSP_Tura.h"
using namespace std;

int main() {
    vector<int> t({0,4,2,8,1,3,6,7,5});
    vector<vector<int>> u(t.size(), vector<int>(t.size(), 1));

    /*for(int i = 0 ; i < u.size() ; i++) {
        for(int j = 0 ; j < u.size() ; j++) {
            cout<<u[i][j]<<" ";
        }
        cout<<endl;
    }*/

    TSP_Tura tura(t, u);

    //cout<<tura.cvorovi[0]->susjed2->id<<endl;
    //tura.zamijeni_grane({4,2}, {1,3}, {7,5}, 3);
    tura._3opt();

    vector <int> vracena = tura.vrati_vektor_ture();

    for(int i = 0 ; i < vracena.size() ; i++) {
        cout<<vracena[i]<<" ";
    }
}
