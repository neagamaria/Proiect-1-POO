#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;
ifstream in("fisier.in");

class Produs
{
    char *nume;
    float pret;
    int nr_bucati;
public:
    ///constructori initializare
    Produs(char*, float, int);
    Produs();
    Produs(bool);
    ///destructor
    ~Produs(){delete[] nume;}
    ///constructor copiere
    Produs(const Produs&);
    ///get si set
    float get_pret(){return pret;}
    int get_nr_bucati(){return nr_bucati;}
    void set_nr_bucati(int x){nr_bucati=x;}
    char* get_nume(){return nume;}
    ///operator de copiere
    Produs& operator=(Produs&);
    ///functie afisare
    void afis(){cout<<nume<<" "<<pret<<" "<<nr_bucati<<endl;}
    ///operator de afisare
    friend ostream &operator<<(ostream&, const Produs&);
    ///operator de citire
    friend istream &operator>>(istream &, Produs &);
    ///operator +
    Produs& operator+(float x);
    ///operatorul -- in forma prefixata
    Produs& operator--();
    ///operatorul -- in forma postfixata
    Produs& operator--(int);
    ///operator cast
    operator double();
    ///operator unar -
    Produs& operator-();
    ///operator - pt 2 obiecte
    Produs& operator-(Produs);
    ///operator +=
    Produs& operator+=(Produs);
    ///operator !
    bool operator!();
};
Produs::Produs():nr_bucati(0), pret(0){nume=new char(50);}
Produs::Produs(char* prod, float p, int nr){nume=new char(50); strcpy(nume, prod); pret=p; nr_bucati=nr;}
Produs::Produs(const Produs& p){nume=new char(50); strcpy(this->nume, p.nume); this->pret=p.pret; this->nr_bucati=p.nr_bucati;}
Produs::Produs (bool b)
{
    nume=new char(50);
    if(b==true)
    {
        cin.getline(nume, 50);
        cin>>nr_bucati>>pret;
    }
    else
    {
        in.getline(nume, 50);
        in>>nr_bucati>>pret;
    }
}
Produs& Produs::operator=(Produs& ob)
{
    if(this!=&ob)
    {
        this->nume=new char[strlen(ob.nume)+1];
        strcpy(this->nume, ob.nume);
        this->pret=ob.pret;
        this->nr_bucati=ob.nr_bucati;
    }
    return *this;
}

ostream &operator<<(ostream& out, const Produs &p)
{
    cout<<p.nume<<endl;
    cout<<p.nr_bucati<<" "<<p.pret<<endl;
    return out;
}
istream &operator>>(istream &in, Produs &p)
{
    cin.getline(p.nume, 50);
    cin>>p.nr_bucati>>p.pret;
    return in;
}

Produs& Produs::operator+(float x)
{
    this->pret+=x;
    return *this;
}

Produs& Produs::operator-(Produs p)
{
    this->pret-=p.pret;
    this->nr_bucati-=p.nr_bucati;
    return *this;
}
Produs& Produs::operator--()
{
    pret--;
    return *this;
}

Produs& Produs::operator--(int x)
{
    pret--;
    return *this;
}

Produs::operator double()
{
    return (double)pret;
}

Produs& Produs::operator-()
{
    pret=-pret;
    nr_bucati=-nr_bucati;
    return *this;
}

Produs& Produs::operator+=(Produs p)
{
    this->pret+=p.pret;
    this->nr_bucati+=p.nr_bucati;
    return *this;
}

bool Produs::operator!()
{
    if(pret==0 || nr_bucati==0)
        return 0;
    return 1;
}

class Comanda
{
    int id, nr_prod;
    char *magazin, *status;
    float suma_plata;
    Produs p[20];
public:
    ///constructori initializare
    Comanda();
    Comanda(int, char*);
    ///destructor
    ~Comanda(){delete[] magazin; delete[] status;}
    ///get si set
    char* get_status() {return status;}
    void set_status(char* s) {strcpy(status, s);}
    void set_suma_plata() {suma_plata=0;}
    int get_nr_prod() {return nr_prod;}
    Produs get_prod(int i) {return p[i];}
    ///operator afisare
    friend ostream &operator<<(ostream&, const Comanda&);
    ///operator de indexare
    Produs operator[](int i){return p[i];}

    ///alte functii
    //void adauga_produs(Produs);
    friend void adauga_produs(Produs, Comanda&); //transformare functie membra in functie prieten
    void sterge_produs(int);
    void afis_suma_plata(){strcpy(status, "Comanda procesata"); cout<<status<<". De plata: "<<suma_plata<<"lei\n";}
    void afis_produse();

};

Comanda::Comanda():suma_plata(0), nr_prod(0)
{
    magazin=new char[50];
    status=new char[50];
    strcpy(status,"");
    id=rand()%1000;
}

Comanda::Comanda(int nr, char* m):suma_plata(0), nr_prod(0)
{
    magazin=new char[50];
    status=new char[50];
    id=nr;
    strcpy(magazin, m);
    strcpy(status, "Adauga produse");
}
/*
void Comanda::adauga_produs(Produs prod)
{
    nr_prod++;
    p[nr_prod]=prod;
    suma_plata+=prod.get_pret()*prod.get_nr_bucati();
}
*/

void adauga_produs(Produs prod, Comanda& c)
{
    c.nr_prod++;
    c.p[c.nr_prod]=prod;
    c.suma_plata+=prod.get_pret()*prod.get_nr_bucati();
}

void Comanda::sterge_produs(int i)
{
    if (i==0 || i>nr_prod)
        cout<<"Produsul selectat nu exista in cos\n";
        else
        {
            Produs prod=p[i];
            suma_plata-=prod.get_pret()*prod.get_nr_bucati();

            cout<<"Produsul "<<prod.get_nume()<<" a fost sters din comanda\n";
            for(int j=i; j<nr_prod; j++)
                p[j]=p[j+1];
            nr_prod--;
        }
}


ostream &operator<<(ostream& out, const Comanda& c)
{
    cout<<"Comanda:"<<endl<<c.id<<" "<<c.magazin<<" "<<c.status<<" "<<c.suma_plata<<endl;
    return out;
}

void Comanda::afis_produse()
{
    cout<<"Produsele din comanda:\n";
    for(int i=1; i<=nr_prod; i++)
        cout<<i<<" "<<p[i]<<" ";
    cout<<'\n';
}

class Client
{
    char* nume_prenume, *adresa, *tel;
public:
    ///constructori initializare
    Client();
    Client(char*, char*, char*);
    ///destructor
    ~Client(){delete[] nume_prenume; delete[] adresa; delete[] tel;}
    ///operator afisare
    friend ostream &operator<<(ostream&, const Client&);
    ///operator citire
    friend istream &operator>>(istream &, Client &);
    ///alte functii
    void deschide_comanda(Comanda&);
    void finalizeaza_comanda(Comanda&);
    void editeaza_cont(char*, char*);

};

Client::Client(){nume_prenume=new char[50]; adresa=new char[50]; tel=new char[50];}
Client::Client(char* np, char* adr, char* t)
{
    nume_prenume=new char[50];
    adresa=new char[50];
    tel=new char[50];
    strcpy(nume_prenume, np); strcpy(adresa, adr); strcpy(tel, t);
}

void Client::deschide_comanda(Comanda& c){c.set_status("Comanda deschisa"); c.set_suma_plata(); cout<<c.get_status()<<endl;}
void Client::finalizeaza_comanda(Comanda& c)
{
    cout<<"Detalii livrare:\n"<<"Client\n"<<nume_prenume<<", "<<adresa<<", "<<tel<<endl;
    c.afis_suma_plata();

}
void Client::editeaza_cont(char *adresa, char *tel){strcpy(this->tel, tel); strcpy(this->adresa, adresa);}
ostream &operator<<(ostream& out, const Client& cl)
{
    cout<<"Client:"<<endl<<cl.nume_prenume<<" "<<cl.adresa<<" "<<cl.tel<<" "<<endl;
    return out;
}

istream &operator>>(istream &in, Client &cl)
{
    cin.getline(cl.nume_prenume, 50);
    cin.getline(cl.adresa, 50);
    cin.getline(cl.tel, 50);
    return in;
}

int main()
{
///.....

    Client cnt;
    cout<<"Introdu datele de client (Nume, Adresa, Telefon, fiecare pe cate un rand):\n";
    cin>>cnt; //supraincarcare operator citire
    Comanda c; //constructor initializare fara param.

    cout<<"1.Schimba date cont client\n2.Incepe cumparaturile\n";
    int x;
    cin>>x;
    cin.get();
    if(x==1)
    {
        char tel[50], adr[50];
        cout<<"Noua adresa:\n";
        cin.getline(adr, 50);
        cout<<"Noul telefon:\n";
        cin.getline(tel, 50);
        cnt.editeaza_cont(adr, tel);
    }

    cout<<cnt<<"\nSe deschide comanda:"; //supraincarcare operator afisare
    cnt.deschide_comanda(c);
    int nr;
    cout<<"Introdu numarul de produse";
    cin>>nr;
    cin.get();
    for(int i=1; i<=nr; i++)
    {
        cout<<"Adauga produsul "<<i<<" (Nume, Numar bucati, Pretul, fiecare pe cate o linie):\n";
        char n[50];
        int bucati;
        float pret;
        cin.getline(n, 50);
        cin>>bucati>>pret;
        cin.get();
        Produs p(n, bucati, pret); //constr. init. cu param.
        //c.adauga_produs(p);
        adauga_produs(p, c);
    }

    c.afis_produse();
    cout<<"Alege urmatoarul pas:\n"<<"1.Elimina un produs.\n"<<"2.Adauga de 2 ori un produs din comanda.\n";
    cout<<"3.Finalizeaza comanda\n";
    cin>>x;
    switch(x)
    {
    case 1:
        cout<<"Alege nr produsului de eliminat:\n";
        int nr;
        cin>>nr;
        c.sterge_produs(nr);
        //c.afis_produse();
        for(int i=1; i<=c.get_nr_prod(); i++)
            cout<<c[1]<<" "; //operator de indexare
        break;
    case 2:
        cout<<"Alege nr produsului de adaugat:\n";
        cin>>nr;
        Produs p2=c.get_prod(nr);//operator de atribuire
        Produs p3(p2); //constructor de copiere
        cout<<p2<<'\n'<<p3<<'\n';
        //c.adauga_produs(p3);
        adauga_produs(p3, c);
        break;
    }
    cout<<"Finalizare comanda\n";
    cnt.finalizeaza_comanda(c);

///.....

    cout<<"Alte operatii:\n";
    cout<<"Se creeaza un produs\n";
    Produs p4("paine", 3, 3);
    cout<<p4;
    double d=(double)p4;
    cout<<"Conversie float (produs.pret) to double "<<d<<'\n';
    cout<<"Operator de decrementare unar(forma prefixata si postfixata)\n"<<--p4<<" "<<p4--<<'\n';
    cout<<"Operator +\n"<<p4+2;

    cout<<"Operatii suplimentare:\n";
    Produs p5;
    cin>>p5;
    int y=p5;
    cout<<y<<endl;
    cout<<p5<<" "<<-p5;
    -p5;
    Produs p6(false); //constructor cu parametru bool
    cout<<p6<<'\n';
    Comanda c2;
    adauga_produs(p6, c2); //apelare functie transformata din functie membra in functie prieten
    Produs v[3];
    v[0]=p5;
    v[1]=v[2]=p5-p6;
    if(v[0]!=v[2])
        v[0]+=v[2];
    else if(!v[1])
        cout<<v[1]<<" nu e zero\n";
    for(int i=0; i<3; i++)
        cout<<v[i]<<" ";
    cout<<'\n';
    return 0;
}
