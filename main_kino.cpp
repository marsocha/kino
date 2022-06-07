//Marcin Socha nr 418253
#include<iostream>
#include<cmath>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<vector>
#include<algorithm>
#include<cstdlib>
using namespace std;

const int MAX_OCENA = 10;
const int MIN_OCENA = 1;
const int MAX_ZAPROSZONYCH = 5;
const int MAX_LICZBA_MIEJSC = 10;
const int MIN_LICZBA_MIEJSC = 2;
const int MAX_LICZBA_SAL = 4;
const int SZANSA_OKAZJONALNEGO = 5; // prawd. to 1/SZANSA_OKAZJONALNEGO

class Miasto;
class Kino;
class Mieszkaniec;
class Sala;
class Widz;

class Film
{
protected:
    string tytul;
    int liczba_biletow;
    float ocena;
    int suma_ocen; //chcemy, aby srednia byla jak najbardziej dokladna,
    //wiec nie bedziemy liczyli sredniej na bierzaca
    //bo ostateczna srednia moze mocno odbiegac od prawdziwej
    int liczba_ocen;
public:
    Film() : tytul("---"), liczba_biletow(0), ocena(MIN_OCENA), suma_ocen(0), liczba_ocen(0){};
    Film(string t) : tytul(t), liczba_biletow(0), ocena(MIN_OCENA), suma_ocen(0), liczba_ocen(0) {};
    ~Film() = default;

    void wypisz_informacje() {
        cout << "Tytul: \"" << tytul << "\" ,ocena:" << get_ocena() << " ,liczba sprzedanych biletow:" << liczba_biletow << "\n";
    };
    void dodaj_ocene(int oc){
        suma_ocen += oc;
        liczba_ocen++;
    };
    void dodaj_bilety(int l){
        liczba_biletow += l;
    };
    float get_ocena() const {
        return ((liczba_ocen == 0) ? MIN_OCENA : (ceil (((float)suma_ocen / (float)liczba_ocen) * 100.0) / 100.0));
    };
    string get_tytul() {
        return tytul;
    };
    void set_tytul(string _tytul) {
        tytul = _tytul;
    };
};

class Mieszkaniec
{
protected:
    string imie;
    Miasto* m;
public:
    Mieszkaniec(string _imie, Miasto* miasto) : imie(_imie), m(miasto) {};
    Mieszkaniec(){};
    ~Mieszkaniec() = default;
    virtual bool czy_ide(int) = 0;
    virtual void co_dzisiaj() {};
    virtual void wypisz_informacje() {};
};
class Widz : public Mieszkaniec
{
protected:
    vector<string> historia_filmow;
    vector<int> historia_ocen;
public:
    Widz(){};
    ~Widz() = default;

    virtual int losuj_kino() = 0;
    virtual void ocen_film(int, int){};
    void wypisz_informacje() override {
        cout << "\n" << imie <<" zobaczyl " << historia_filmow.size() << " filmow i ocenil je nastepujaco: \n";
        for (int i = 0; i < historia_filmow.size(); ++i){
            cout << historia_filmow[i] << " na: " << historia_ocen[i] << "|";
        }
    };

};
class Kino
{
protected:
    string nazwa;
    string adres;
    bool multi; //true = multipleks, false = male kino
    Miasto* miasto;
public:
    Kino(){};
    ~Kino() = default;
    Kino(const Kino&){};
    Kino& operator=(const Kino& k){
        if(&k == this) return *this;
        nazwa = k.nazwa;
        adres = k.adres;
        multi = k.multi;
        miasto = k.miasto;
        return *this;
    };
    void set_nazwa(string _nazwa) {
        nazwa= _nazwa;
    };
    virtual void sprzedaj_bilet(int){};
    virtual void wypisz_informacje(){};
    virtual void wypisz_repertuar(int){};
    virtual void losuj_film(){};
    virtual bool czy_gramy_dzis_film_i_jest_miejsce(Film*, int) = 0;
    virtual vector<Sala*> get_sale_kinowe() = 0;
    virtual int get_liczba_sal() = 0;
    virtual void ile_miejsc_maja_sale() {};
    bool get_multi() const {
        return multi;
    };
    void wypisz_nazwe() {
        cout << nazwa << "\n";
    };
    string get_nazwa() {
        return nazwa;
    };
    virtual void dodaj_bilety_w_sali(int, int){};
    virtual string tytul_w_sali(int sala, int dzionek) = 0;

};

class Miasto
{
protected:
    int liczba_mieszkancow;
    int liczba_multipleksow;
    int liczba_malych_kin;
    int dzien; //ktory jest dzien
    int liczba_dni; //ile trwa symulacja
    int liczba_filmow;
    string nazwa;
    vector <Film*> filmy;
    vector <Mieszkaniec*> mieszkancy; //lista mieszkancow
    vector <Kino*> kina;
    vector <Film*> filmy_dnia;
    Film* dziejszy_max;
public:
    Miasto(){};
    Miasto(int lmi, int lmu, int lmk, int d, int ld, int lf ,string n) {
        liczba_mieszkancow = lmi;
        liczba_multipleksow = lmu;
        liczba_malych_kin = lmk;
        dzien = d;
        liczba_dni = ld;
        liczba_filmow = lf;
        nazwa = n;
    };
    ~Miasto() {};
    Miasto(const Miasto &mias){
        liczba_mieszkancow = mias.liczba_mieszkancow;
        liczba_filmow = mias.liczba_filmow;
        liczba_multipleksow = mias.liczba_multipleksow;
        liczba_malych_kin = mias.liczba_malych_kin;
        dzien = mias.dzien;
        liczba_dni = mias.liczba_dni;
        nazwa = mias.nazwa;
        filmy = mias.filmy;
        mieszkancy = mias.mieszkancy;
        kina = mias.kina;
        filmy_dnia = mias.filmy;
        dziejszy_max = mias.dziejszy_max;
    };
    Miasto& operator=(const Miasto& mias){
        if(&mias == this) return *this;
        liczba_mieszkancow = mias.liczba_mieszkancow;
        liczba_filmow = mias.liczba_filmow;
        liczba_multipleksow = mias.liczba_multipleksow;
        liczba_malych_kin = mias.liczba_malych_kin;
        dzien = mias.dzien;
        liczba_dni = mias.liczba_dni;
        nazwa = mias.nazwa;
        filmy = mias.filmy;
        mieszkancy = mias.mieszkancy;
        kina = mias.kina;
        filmy_dnia = mias.filmy;
        dziejszy_max = mias.dziejszy_max;
        return *this;
    };

    void zakoncz_symulacje() {
        cout << "Symulacja zakonczona. Oto podsumowanie: \n";
        cout << "Pula filmow: \n";
        for (int i = 0; i < liczba_filmow; ++i)
        {
            filmy[i]->wypisz_informacje();
        }
        cout << " \n Statystyki kin: \n";
        for (int i = 0; i < liczba_malych_kin + liczba_multipleksow; ++i)
        {
            kina[i]->wypisz_informacje();
        }
        cout << " \n Statystyki widzow: \n";
        for (int i = 0; i < liczba_mieszkancow; ++i)
        {
            mieszkancy[i]->wypisz_informacje();
        }
        cout << " \n Repertuary kin: \n";
        for (int i = 0; i < liczba_malych_kin + liczba_multipleksow; ++i)
        {
            kina[i]->wypisz_repertuar(liczba_dni);
        }

    };
    void wypisz_nazwe() {
        cout << nazwa << "\n";
    };
    void dodaj_do_dziejszych(int indeks) {
        if (find(filmy_dnia.begin(), filmy_dnia.end(), filmy[indeks]) == filmy_dnia.end()) {
            filmy_dnia.push_back(filmy[indeks]);
            if(filmy[indeks]->get_ocena() > dziejszy_max->get_ocena()) {
                dziejszy_max = filmy[indeks];
            }
        }
    };
    void kolejny_dzien() {
        if (dzien < liczba_dni) {

            filmy_dnia.erase(filmy_dnia.begin(), filmy_dnia.end());

            for (int i = 0; i < liczba_malych_kin + liczba_multipleksow; ++i)
            {
                kina[i]->losuj_film();
            }
            if (dzien == 0) {
                dziejszy_max = filmy[0];
            }
            for (int i = 0; i < liczba_mieszkancow; i++) {
                mieszkancy[i]->co_dzisiaj();
            }
        } else {
            zakoncz_symulacje();
        }
        dzien++;
    };
    Film* get_dzisiejszy_max(){
        return dziejszy_max;
    };
    vector<Film*> get_filmy() {
        return filmy;
    };
    vector<Mieszkaniec*> get_mieszkancy() {
        return mieszkancy;
    };
    int get_liczba_filmow () const{
        return liczba_filmow;
    };
    vector<Kino*> get_kina() {
        return kina;
    };
    int get_liczba_kin() const {
        return liczba_multipleksow + liczba_malych_kin;
    };
    int get_dzien() const {
        return dzien;
    };
    int get_liczba_dni() const {
        return liczba_dni;
    };
    void set_dane(string* dane, int ile_kin, int ile_filmow) {
        for (int i = 0; i < ile_kin + ile_filmow; i++) {
            if (i < ile_kin) {
                kina[i]->set_nazwa(dane[i]);
            } else {
                if (i < ile_kin + ile_filmow) {
                    filmy[i]->set_tytul(dane[i]);
                }
            }
        }
    };
    void dodaj_kino(Kino* k) {
        kina.push_back(k);
    };
    void dodaj_mieszkanca(Mieszkaniec* m) {
        mieszkancy.push_back(m);
    };
    void dodaj_film(Film* f) {
        filmy.push_back(f);
    };
    void ile_sal_maja_kina() {
        for (int i = 0; i< liczba_malych_kin + liczba_multipleksow; i++) {
            cout << "Kino "<< kina[i]->get_nazwa() << " posiada sal " << kina[i]->get_liczba_sal() << "\n";
            cout << "Ktore maja liczbe miejsc kolejno:";
            kina[i]->ile_miejsc_maja_sale();
            cout << "\n";
        };
    };
    void wypisz_filmy() {
        for (int i = 0; i < liczba_filmow; ++i) {
            cout << "Film nr " << i <<": " << filmy[i]->get_tytul() << "\n";
        }
    };
    void set_dzien(int dzionek) {
        dzien = dzionek;
    };
    void dodaj_bilety_w_sali(int kin, int sal, int ile_zapro) {
        kina[kin]->dodaj_bilety_w_sali(sal, ile_zapro);
    };
    void ocena_filmu(int kin, int sal, int ocena){
        for (int i = 0; i < liczba_filmow; ++i) {
            if (kina[kin]->tytul_w_sali(sal, dzien) == filmy[i]->get_tytul()) {
                filmy[i]->dodaj_ocene(ocena);
                filmy[i]->dodaj_bilety(1);
            }
        }
    };
};

class Sala
{
protected:
    int liczba_miejsc;
    int liczba_wolnych_miejsc;
    string* historia_filmow;
    Film* historia_filmow_pra;
    int* historia_biletow;
    Miasto* miasto;

public:
    Sala(){};

    Sala(Miasto* m){
        liczba_miejsc = rand() % (MAX_LICZBA_MIEJSC - MIN_LICZBA_MIEJSC) + MIN_LICZBA_MIEJSC + 1;
        liczba_wolnych_miejsc = liczba_miejsc;
        historia_filmow = new string[m->get_liczba_dni()];
        historia_biletow = new int[m->get_liczba_dni()];
        for (int i = 0; i < m->get_liczba_dni(); ++i) {
            historia_filmow[i] = "---";
            historia_biletow[i] = 0;
        }
        historia_filmow_pra = new Film[m->get_liczba_dni()];
        miasto = m;
    };
    ~Sala(){
        delete[] historia_filmow;
        delete[] historia_biletow;
        delete[] historia_filmow_pra;
    };
    Sala(const Sala& s){
        liczba_miejsc = s.liczba_miejsc;
        liczba_wolnych_miejsc = s.liczba_wolnych_miejsc;
        miasto = s.miasto;
        historia_filmow = new string[miasto->get_liczba_dni()];
        historia_biletow = new int[miasto->get_liczba_dni()];
        historia_filmow_pra = new Film[miasto->get_liczba_dni()];
    };
    Sala& operator=(const Sala& s){
        if (&s == this) return *this;
        liczba_miejsc = s.liczba_miejsc;
        liczba_wolnych_miejsc = s.liczba_wolnych_miejsc;
        miasto = s.miasto;
        delete[] historia_filmow;
        historia_filmow = new string[miasto->get_liczba_dni()];
        delete[] historia_biletow;
        historia_biletow = new int[miasto->get_liczba_dni()];
        historia_filmow_pra = new Film[miasto->get_liczba_dni()];
        return *this;
    };
    Film* wybierz_film(){
        int tmp = rand() % miasto->get_liczba_filmow();
        miasto->dodaj_do_dziejszych(tmp);
        historia_filmow[miasto->get_dzien()] = miasto->get_filmy()[tmp]->get_tytul();
        return (miasto->get_filmy()[tmp]);
    };
    void dodaj_bilety(int b) {
        historia_biletow[miasto->get_dzien()] += b;
        liczba_wolnych_miejsc -= b;
    };
    bool czy_dodac_bilety(int b) const {
        return (liczba_wolnych_miejsc >= b);
    };
    void zeruj_sale() {
        liczba_wolnych_miejsc = liczba_miejsc;
        wybierz_film();
    };
    string get_film(int dz) {
        return historia_filmow[dz];
    };
    Film* get_film_pra(int dz) {
        return &historia_filmow_pra[dz];
    };
    int get_liczba_wolnych_miejsc() const {
        return liczba_wolnych_miejsc;
    };
    int get_liczba_miejsc() const {
        return liczba_miejsc;
    };
    int* get_historia_biletow() {
        return historia_biletow;
    };
};



class Male_kino : public Kino
{
protected:
    vector<Sala*> sala_kinowa;
public:
    Male_kino(string _nazwa, string _adres, Miasto* m){
        nazwa = _nazwa;
        adres = _adres;
        miasto = m;
        multi = false;
        sala_kinowa.push_back(new Sala(m));
    };
    ~Male_kino() {};
    Male_kino(const Male_kino& s){
        nazwa = s.nazwa;
        adres = s.adres;
        miasto = s.miasto;
        multi = s.multi;
        sala_kinowa.push_back(s.sala_kinowa[0]);
    };
    Male_kino& operator=(const Male_kino& s){
        if (&s == this) return *this;
        nazwa = s.nazwa;
        adres = s.adres;
        miasto = s.miasto;
        multi = s.multi;
        sala_kinowa.push_back(s.sala_kinowa[0]);
        return *this;
    };

    void ile_miejsc_maja_sale() override {
        cout << sala_kinowa[0]->get_liczba_miejsc() << "\n";
    };

    void wypisz_informacje() override {
        cout << "Male kino \"" << nazwa <<"\", adres:" << adres <<"\n";
        cout << "to Male Kino, ktorego sala ma " << sala_kinowa[0]->get_liczba_miejsc() << " miejsc. ";
        cout << "Sala ta sprzedawala kolejno: ";
        for (int i = 0; i < miasto->get_liczba_dni(); ++i) {
            cout << sala_kinowa[0]->get_historia_biletow()[i] << "|";
        }
        cout << "biletow. \n";
    };
    void wypisz_repertuar(int _liczba_dni) override {
        cout << "Kino " << nazwa << ": \n";
        for (int i = 0; i < _liczba_dni ; ++i)
        {
            cout << "dzien nr " << i + 1 << ": " << sala_kinowa[0]->get_film(i) << "\n";
        }
    };
    void sprzedaj_bilet(int liczba_b) override {
        sala_kinowa[0]->dodaj_bilety(liczba_b);
    };
    void losuj_film() override {
        sala_kinowa[0]->zeruj_sale();
        sala_kinowa[0]->wybierz_film();
    };
    bool czy_gramy_dzis_film_i_jest_miejsce(Film* f, int dz) override {
        return (sala_kinowa[0]->get_film(dz) == f->get_tytul() && sala_kinowa[0]->get_liczba_wolnych_miejsc());
    };
    int get_liczba_sal() override {
        return 1;
    };
    vector<Sala*> get_sale_kinowe() override {
        return sala_kinowa;
    };

    void dodaj_bilety_w_sali(int sal, int ile_zapro) override {
        if(sala_kinowa[0]->czy_dodac_bilety(ile_zapro)) {
            sala_kinowa[0]->dodaj_bilety(ile_zapro);
        }
    };
    string tytul_w_sali(int sala, int dzionek) override {
        return sala_kinowa[0]->get_film(dzionek);
    };
};

class Multipleks : public Kino
{
protected:
    vector<Sala*> sale_kinowe;
    int liczba_sal;
public:
    Multipleks(string _nazwa, string _adres, Miasto *m) {
        nazwa = _nazwa;
        adres = _adres;
        miasto = m;
        multi = true;
        liczba_sal = rand() % (MAX_LICZBA_SAL - 1) + 2;
        for (int i = 0; i < liczba_sal; ++i) {
            sale_kinowe.push_back(new Sala(m));
        }
    };
    ~Multipleks(){
        //delete [] sale_kinowe;
    };
    Multipleks(const Multipleks& s){
        nazwa = s.nazwa;
        adres = s.adres;
        miasto = s.miasto;
        multi = s.multi;
        liczba_sal = s.liczba_sal;
        sale_kinowe = s.sale_kinowe;
    };
    Multipleks& operator=(const Multipleks& s){
        if (&s == this) return *this;
        nazwa = s.nazwa;
        adres = s.adres;
        miasto = s.miasto;
        multi = s.multi;
        liczba_sal = s.liczba_sal;
        sale_kinowe = s.sale_kinowe;
        return *this;
    };
    void ile_miejsc_maja_sale() override {
        for (int i = 0; i < liczba_sal; ++i) {
            cout << "Sala nr " << i + 1 << ": " << sale_kinowe[i]->get_liczba_miejsc() << ", ";
        }

    };

    void dodaj_bilety_w_sali(int sal, int ile_zapro) override {
        if(sale_kinowe[sal]->czy_dodac_bilety(ile_zapro)) {
            //cout << ile_zapro << "|";
            sale_kinowe[sal]->dodaj_bilety(ile_zapro);
        }
    };

    void wypisz_informacje() override {
        cout << "Multipleks \"" << nazwa <<"\", adres:" << adres <<" \n";
        cout << "to Multipleks, ktory ma " << liczba_sal;
        cout << " sal, a kazda po ";
        for (int i = 0; i < liczba_sal; ++i) {
            cout << sale_kinowe[i]->get_liczba_miejsc() << "|";
        }
        cout << " miejsc. ";
        cout << "Sale ta sprzedawaly kolejno: ";
        for (int i = 0; i < liczba_sal; ++i) {
            for (int j = 0; j < miasto->get_liczba_dni(); ++j) {
                cout << sale_kinowe[i]->get_historia_biletow()[j] << "|";
            }
        }
        cout << " biletow. \n";
    };

    vector<Sala*> get_sale_kinowe() override {
        return sale_kinowe;
    };
    int get_liczba_sal() override {
        return liczba_sal;
    };

    void wypisz_repertuar(int _liczba_dni) override {
        cout << "Kino " << nazwa << ": \n";
        for (int i = 0; i < liczba_sal; ++i)
        {
            cout << "Sala nr " << i + 1 << ": \n";
            for (int j = 0; j < _liczba_dni; ++j)
            {
                cout << "dzien nr " << j + 1 << ":" << sale_kinowe[i]->get_film(j) << "\n";
            }
        }

    };
    void sprzedaj_bilet(int liczba_b) override {
        for (int i = 0; i < liczba_sal; i++) {
            sale_kinowe[i]->dodaj_bilety(liczba_b);
        }
    };
    void losuj_film() override {
        for (int i = 0; i < liczba_sal; ++i)
        {
            sale_kinowe[i]->zeruj_sale();
            sale_kinowe[i]->wybierz_film();
        }
    };
    bool czy_gramy_dzis_film_i_jest_miejsce(Film* f, int dz) override {
        for (int i = 0; i < liczba_sal; ++i)
        {
            if (sale_kinowe[i]->get_film(dz) == f->get_tytul() && sale_kinowe[i]->get_liczba_wolnych_miejsc()) {

                return true;
            } ;
        }
        return false;
    };
    string tytul_w_sali(int sala, int dzionek) override {
        return sale_kinowe[sala]->get_film(dzionek);
    };
};

class Nieogladajacy : public Mieszkaniec
{
public:
    Nieogladajacy(){};
    ~Nieogladajacy() = default;
    Nieogladajacy(const Nieogladajacy& s) = default;
    Nieogladajacy& operator=(const Nieogladajacy& s) = default;

    bool czy_ide(int dz) override {
        return false;
    };
    void co_dzisiaj() override{

    };
    void wypisz_informacje() override {
        cout << "\n" << imie <<" nic nie ogladal \n";
    };
};

class Koneser : public Widz {

public:
    Koneser(){};
    Koneser(string _imie, Miasto* mias){
        imie = _imie;
        m = mias;
    };
    ~Koneser() = default;
    Koneser(const Koneser& s){
        imie = s.imie;
        m = s.m;
    };
    Koneser& operator=(const Koneser& s){
        if (&s == this) return *this;
        imie = s.imie;
        m = s.m;
        return *this;
    };
    bool czy_ide(int dz) override {
        return true;
    };

    int losuj_kino() override {
        return -1;
    };

    void ocen_film(int kin, int sal) override {
        int ocenka = (rand() % (MAX_OCENA * 3 / 4 - MIN_OCENA) + MIN_OCENA + 1);
        m->ocena_filmu(kin, sal, ocenka);
        historia_ocen.push_back(ocenka);
        historia_filmow.push_back(m->get_kina()[kin]->get_sale_kinowe()[sal]->get_film(m->get_dzien()));
        //dzielenie całkowite, wiec maksymalnie da 3/4 MAX_OCENA
    };

    int znajdz_sale(int i, string tyt) {
        for(int j = 0; j < m->get_kina()[i]->get_liczba_sal(); ++j) {
            if (m->get_kina()[i]->get_sale_kinowe()[j]->get_film(m->get_dzien()) == tyt) {
                return j;
            }
        }
        return -1;
    };

    void kup_bilet(int kin, int sal) {
        m->dodaj_bilety_w_sali(kin, sal, 1);
    };

    void co_dzisiaj() override {
        for (int i = 0; i < m->get_liczba_kin(); ++i) {
            if (m->get_kina()[i]->czy_gramy_dzis_film_i_jest_miejsce(m->get_dzisiejszy_max(), m->get_dzien())) {
                int sala_k;
                sala_k = (znajdz_sale(i, m->get_dzisiejszy_max()->get_tytul()));
                //cout << m->get_kina()[i]->get_sale_kinowe()[sala_k]->get_film(m->get_dzien()) << "\n";
                kup_bilet(i, sala_k);
                ocen_film(i, sala_k);
            }
        }

    };
};

class Kinoman : public Widz {
protected:
    int pierwszy_dzien;
public:

    Kinoman() {
        pierwszy_dzien = rand() % 3;
    };
    Kinoman(string _imie, Miasto* mias){
        imie = _imie;
        m = mias;
        pierwszy_dzien = rand() % 3;
    };
    Kinoman(const Kinoman& s){
        imie = s.imie;
        m = s.m;
        pierwszy_dzien = s.pierwszy_dzien;
    };
    Kinoman& operator=(const Kinoman& s){
        if (&s == this) return *this;
        imie = s.imie;
        m = s.m;
        pierwszy_dzien = s.pierwszy_dzien;
        return *this;
    };
    ~Kinoman() = default;

    int ile_zaproszonych() {
        return rand() % MAX_ZAPROSZONYCH;
    };

    int losuj_kino() override {
        return rand() % m->get_liczba_kin();
    };


    bool czy_ide(int dz) override {
        return ((dz - pierwszy_dzien) % 3 == 0);
    };

    void ocen_film(int kin, int sal) override {
        int ocenka = (rand() % (MAX_OCENA - MIN_OCENA) / 2 + (MAX_OCENA - MIN_OCENA) / 2 + 1);
        m->ocena_filmu(kin, sal, ocenka);
        historia_ocen.push_back(ocenka);
        historia_filmow.push_back(m->get_kina()[kin]->get_sale_kinowe()[sal]->get_film(m->get_dzien()));
    };

    int losuj_sale(int kin, Miasto* m) {
        return (rand() % (m->get_kina()[kin]->get_liczba_sal()));
    };
    void ocena_znajomych(int kin, int sal) {
        int ocenka = (rand() % (MAX_OCENA - MIN_OCENA) + 1);
        m->ocena_filmu(kin, sal, ocenka);
    };


    void co_dzisiaj() override {
        if (czy_ide(m->get_dzien())) {
            int ile_zapro = ile_zaproszonych();
            int kin = losuj_kino();
            int sal = losuj_sale(kin, m);
            m->dodaj_bilety_w_sali(kin, sal, ile_zapro + 1);
            ocen_film(kin, sal);
            for(int i = 0; i < ile_zapro; ++i) {
                ocena_znajomych(kin, sal);
            }
        }
    };
};

class Okazjonalny : public Widz {
public:
    Okazjonalny(){};
    Okazjonalny(string _imie, Miasto* mias){
        imie = _imie; m = mias;
    };
    ~Okazjonalny() = default;
    Okazjonalny(const Okazjonalny& s){
        imie = s.imie;
        m = s.m;
    };
    Okazjonalny& operator=(const Okazjonalny& s){
        if (&s == this) return *this;
        imie = s.imie;
        m = s.m;
        return *this;
    };
    bool czy_ide(int dz) override {
        return !(rand() % SZANSA_OKAZJONALNEGO);
    };


    void ocen_film(int kin, int sal) override {
        int ocenka = (rand() % (MAX_OCENA - MIN_OCENA) + MIN_OCENA + 1);
        m->ocena_filmu(kin, sal, ocenka);
        historia_ocen.push_back(ocenka);
        historia_filmow.push_back(m->get_kina()[kin]->get_sale_kinowe()[sal]->get_film(m->get_dzien()));
    };

    int losuj_sale(int kin) {
        return (rand() % (m->get_kina()[kin]->get_liczba_sal()));
    };
    int losuj_kino() override {
        return rand() % m->get_liczba_kin();
    };
    void co_dzisiaj() override {
        if (czy_ide(m->get_dzien())) {
            int k = losuj_kino();
            int sal = losuj_sale(k);
            ocen_film(k,sal);
            m->dodaj_bilety_w_sali(k, sal, 1);
        }
    };

};

class Symulacja {
private:
    Miasto m;
public:
    Symulacja(int lmi, int lmu, int lmk, int d, int ld, int lf ,string n) {
        m = Miasto(lmi, lmu, lmk, d, ld, lf ,n) ;
    };

    ~Symulacja() = default;
    Symulacja(const Symulacja& s){
        m = s.m;
    };
    Symulacja& operator=(const Symulacja& s){
        if (&s == this) return *this;
        m = s.m;
        return *this;
    };
    Miasto* get_miasto(){
        return &m;
    };
    void dodaj_kino(Kino* k){
        m.dodaj_kino(k);
    };
    void dodaj_mieszkanca(Mieszkaniec* mieszkaniec){
        m.dodaj_mieszkanca(mieszkaniec);
    };
    void dodaj_film(Film* f){
        m.dodaj_film(f);
    };
    void symuluj() {
        for (int i = 0; i < m.get_liczba_dni() + 1; i++) {
            m.kolejny_dzien();
        }
    };
};

int main() {
    //srand(time(NULL));
    srand(10);
    Symulacja sym(20,2,2,0,25,10,"Filmowo");
    sym.dodaj_mieszkanca(new Kinoman("Mirek", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Adam", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Stefan", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Marcin", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Julia", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Kasia", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Tomek", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Krzychu", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Ania", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Kinoman("Grazyna", sym.get_miasto()));
    //10 kinomanow
    sym.dodaj_mieszkanca(new Koneser("Ildefons", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Koneser("Gerwazy", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Koneser("Miroslaw", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Koneser("Katarzyna", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Koneser("Leszek", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Koneser("Jakub", sym.get_miasto()));
    //6 koneserow
    sym.dodaj_mieszkanca(new Okazjonalny("Okazjusz", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Okazjonalny("Esmeralda", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Okazjonalny("Sebastian", sym.get_miasto()));
    sym.dodaj_mieszkanca(new Okazjonalny("Patryk", sym.get_miasto()));
    // 4 okazjonalnych
    sym.dodaj_film(new Film("Umrzyj twardo"));
    sym.dodaj_film(new Film ("Klub walki"));
    sym.dodaj_film(new Film ("Milosc rzeczywiscie"));
    sym.dodaj_film(new Film ("Szrek"));
    sym.dodaj_film(new Film ("Ten Obcy: bardzo stromo"));
    sym.dodaj_film(new Film ("Biuro"));
    sym.dodaj_film(new Film ("Piraci z Wolinu"));
    sym.dodaj_film(new Film ("Terminal w Linuxie"));
    sym.dodaj_film(new Film ("Zielona osma mila"));
    sym.dodaj_film(new Film ("A to lotr jeden"));
    sym.dodaj_kino(new Multipleks("Sloncios", "ul. Tania 10", sym.get_miasto()));
    sym.dodaj_kino(new Multipleks("Wielekino", "ul. Klawiatur 4", sym.get_miasto()));
    sym.dodaj_kino(new Male_kino("Panorama", "ul. Wolna 33", sym.get_miasto()));
    sym.dodaj_kino(new Male_kino("Bilboteka", "ul. Zwykla 8", sym.get_miasto()));
    sym.symuluj();

    return 0;
}
