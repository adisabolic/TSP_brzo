#ifndef TSP_TURA_CPP
#define TSP_TURA_CPP

#include "TSP_Tura.h"
#include <algorithm>

TSP_Tura::TSP_Tura(int n, vector<vector<int>>& mat_udaljenosti, bool random): n(n), udaljenosti(mat_udaljenosti) {

    vector <int> tura(n);
    cvorovi = vector<Cvor*>(n, nullptr);

    for(int i = 0; i < n; i++)
        tura[i] =  i;
    if(random)
        random_shuffle(tura.begin(),tura.end());

    korijen = new Cvor(tura[0]);
    Cvor* trenutni = korijen;
    cvorovi[tura[0]] = korijen;
    for(int i = 1 ; i < n ; i++) {
        Cvor* novi = new Cvor(tura[i], trenutni);
        cvorovi[tura[i]] = novi;
        trenutni->susjed2 = novi;
        trenutni = novi;
    }
    korijen->susjed1 = trenutni;
    trenutni->susjed2 = korijen;
}

TSP_Tura::TSP_Tura(vector<int> &tura, vector<vector<int>>& mat_udaljenosti): n(tura.size()), udaljenosti(mat_udaljenosti) {

    korijen = new Cvor(tura[0]);
    cvorovi = vector<Cvor*>(n, nullptr);
    cvorovi[tura[0]] = korijen;

    Cvor* trenutni = korijen;
    for(int i = 1 ; i < n ; i++) {
        Cvor* novi = new Cvor(tura[i], trenutni);
        cvorovi[tura[i]] = novi;

        trenutni->susjed2 = novi;
        trenutni = novi;
    }
    korijen->susjed1 = trenutni;
    trenutni->susjed2 = korijen;
}

vector<int> TSP_Tura::vrati_vektor_ture() {

    vector<int> tura(n);
    int i = 0;

    Cvor* trenutni = korijen;
    vector<int> posjecen(n, false);

    while(true) {
        tura[i] = trenutni->id;
        i++;
        posjecen[trenutni->id] = true;
        if(trenutni->susjed2 && !posjecen[trenutni->susjed2->id])
            trenutni = trenutni->susjed2;
        else if(trenutni->susjed1 && !posjecen[trenutni->susjed1->id])
            trenutni = trenutni->susjed1;
        else
            break;
    }

    return tura;
}

bool TSP_Tura::_2opt_uslov(pair<int, int> i, pair<int, int> j) {

    Cvor* cvor1(cvorovi[i.first]), *cvor1_iduci(cvorovi[i.second]);
    Cvor* cvor2(cvorovi[j.first]), *cvor2_iduci(cvorovi[j.second]);

    if(i.first == j.first || cvor1 == cvor2->susjed1 || cvor1 == cvor2->susjed2)
        return false;

    return udaljenosti[cvor1->id][cvor1_iduci->id] + udaljenosti[cvor2->id][cvor2_iduci->id]
            > (udaljenosti[cvor1->id][cvor2->id] + udaljenosti[cvor2_iduci->id][cvor1_iduci->id]);
}

void TSP_Tura::zamijeni_susjede(Cvor* cvor, Cvor* stari, Cvor* novi) {
    if(cvor->susjed1 == stari)
        cvor->susjed1 = novi;
    else if(cvor->susjed2 == stari)
        cvor->susjed2 = novi;
}

void TSP_Tura::zamijeni_grane(pair<int, int> i, pair<int, int> j) {

    Cvor* cvor1(cvorovi[i.first]), *cvor1_iduci(cvorovi[i.second]);
    Cvor* cvor2(cvorovi[j.first]), *cvor2_iduci(cvorovi[j.second]);

    if(i.first == j.first || cvor1 == cvor2->susjed1 || cvor1 == cvor2->susjed2)
        return;

    zamijeni_susjede(cvor1, cvor1_iduci, cvor2);
    zamijeni_susjede(cvor2, cvor2_iduci, cvor1);
    zamijeni_susjede(cvor1_iduci, cvor1, cvor2_iduci);
    zamijeni_susjede(cvor2_iduci, cvor2, cvor1_iduci);
}

bool TSP_Tura::_3opt_uslov(pair<int, int> i, pair<int, int> j, pair<int, int> k, int tip) {

    Cvor* cvor1(cvorovi[i.first]), *cvor1_iduci(cvorovi[i.second]);
    Cvor* cvor2(cvorovi[j.first]), *cvor2_iduci(cvorovi[j.second]);
    Cvor* cvor3(cvorovi[k.first]), *cvor3_iduci(cvorovi[k.second]);

    if(i.first == j.first || i.first == k.first || j.first == k.first)
        return false;

    int tezina(udaljenosti[cvor1->id][cvor1_iduci->id] + udaljenosti[cvor2->id][cvor2_iduci->id] + udaljenosti[cvor3->id][cvor3_iduci->id]);

    if (tip == 3) // 3.
        return tezina > udaljenosti[cvor1->id][cvor3->id] + udaljenosti[cvor1_iduci->id][cvor2_iduci->id] + udaljenosti[cvor2->id][cvor3_iduci->id];
    else if (tip == 2) // 4.
        return tezina > udaljenosti[cvor1->id][cvor2_iduci->id] + udaljenosti[cvor1_iduci->id][cvor3->id] + udaljenosti[cvor2->id][cvor3_iduci->id];
    else if (tip == 1) // 2.
        return tezina > udaljenosti[cvor1->id][cvor2->id] + udaljenosti[cvor1_iduci->id][cvor3->id] + udaljenosti[cvor2_iduci->id][cvor3_iduci->id];
    else if (tip == 0) // 1.
        return tezina > udaljenosti[cvor1->id][cvor2_iduci->id] + udaljenosti[cvor3->id][cvor2->id] + udaljenosti[cvor1_iduci->id][cvor3_iduci->id];

    return false;
}

void TSP_Tura::zamijeni_grane(pair<int, int> i, pair<int, int> j, pair<int, int> k, int tip) {

    Cvor* cvor1(cvorovi[i.first]), *cvor1_iduci(cvorovi[i.second]);
    Cvor* cvor2(cvorovi[j.first]), *cvor2_iduci(cvorovi[j.second]);
    Cvor* cvor3(cvorovi[k.first]), *cvor3_iduci(cvorovi[k.second]);

    if(i.first == j.first || i.first == k.first || j.first == k.first)
        return;

    if (tip == 3) // 3.
    {
        zamijeni_susjede(cvor1, cvor1_iduci, cvor3);
        zamijeni_susjede(cvor3, cvor3_iduci, cvor1);

        zamijeni_susjede(cvor2_iduci, cvor2, cvor1_iduci);
        zamijeni_susjede(cvor1_iduci, cvor1, cvor2_iduci);

        zamijeni_susjede(cvor2, cvor2_iduci, cvor3_iduci);
        zamijeni_susjede(cvor3_iduci, cvor3, cvor2);
    }
    else if (tip == 2) // 4.
    {
        zamijeni_susjede(cvor1, cvor1_iduci, cvor2_iduci);
        zamijeni_susjede(cvor2_iduci, cvor2, cvor1);

        zamijeni_susjede(cvor3, cvor3_iduci, cvor1_iduci);
        zamijeni_susjede(cvor1_iduci, cvor1, cvor3);

        zamijeni_susjede(cvor2, cvor2_iduci, cvor3_iduci);
        zamijeni_susjede(cvor3_iduci, cvor3, cvor2);
    }
    else if (tip == 1) // 2.
    {
        zamijeni_susjede(cvor1, cvor1_iduci, cvor2);
        zamijeni_susjede(cvor2, cvor2_iduci, cvor1);

        zamijeni_susjede(cvor1_iduci, cvor1, cvor3);
        zamijeni_susjede(cvor3, cvor3_iduci, cvor1_iduci);

        zamijeni_susjede(cvor2_iduci, cvor2, cvor3_iduci);
        zamijeni_susjede(cvor3_iduci, cvor3, cvor2_iduci);
    }
    else if (tip == 0) // 1.
    {
        zamijeni_susjede(cvor1, cvor1_iduci, cvor2_iduci);
        zamijeni_susjede(cvor2_iduci, cvor2, cvor1);

        zamijeni_susjede(cvor3, cvor3_iduci, cvor2);
        zamijeni_susjede(cvor2, cvor2_iduci, cvor3);

        zamijeni_susjede(cvor1_iduci, cvor1, cvor3_iduci);
        zamijeni_susjede(cvor3_iduci, cvor3, cvor1_iduci);
    }
}

#endif // TSP_TURA_CPP
