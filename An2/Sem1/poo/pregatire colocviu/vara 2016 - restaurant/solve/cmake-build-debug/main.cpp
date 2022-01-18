//
// Created by Mihai on 13/01/2022.
//

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
/* Licu Mihai-George Grupa 262
Compilator: Clion MinGW
Tutore de laborator: Marius Miculta-Campeanu */


class Data
{
    int an;
    int luna;
    int zi;
public:
    Data(int an, int luna, int zi);

    friend std::ostream &operator<<(std::ostream &os, const Data &data);

    bool operator<(const Data &rhs) const;

    bool operator>(const Data &rhs) const;

    bool operator<=(const Data &rhs) const;

    bool operator>=(const Data &rhs) const;

};

std::ostream &operator<<(std::ostream &os, const Data &data) {
    os << "an: " << data.an << " luna: " << data.luna << " zi: " << data.zi;
    return os;
}

bool Data::operator<(const Data &rhs) const {
    if (an < rhs.an)
        return true;
    if (rhs.an < an)
        return false;
    if (luna < rhs.luna)
        return true;
    if (rhs.luna < luna)
        return false;
    return zi < rhs.zi;
}

bool Data::operator>(const Data &rhs) const {
    return rhs < *this;
}

bool Data::operator<=(const Data &rhs) const {
    return !(rhs < *this);
}

bool Data::operator>=(const Data &rhs) const {
    return !(*this < rhs);
}

Data::Data(int an, int luna, int zi) : an(an), luna(luna), zi(zi) {}


class Produs
{
    std::string denProd;
    float pretProd;
public:
    Produs(const std::string &denProd, float pretProd);
    ~Produs() = default;
    float getPretProd() const;

    friend std::ostream &operator<<(std::ostream &os, const Produs &produs);
};

float Produs::getPretProd() const {
    return pretProd;
}

Produs::Produs(const std::string &denProd, float pretProd) : denProd(denProd), pretProd(pretProd) {}

std::ostream &operator<<(std::ostream &os, const Produs &produs) {
    os << "denProd: " << produs.denProd << " pretProd: " << produs.pretProd;
    return os;
}

enum class Gen {M, F};
std::ostream &operator<<(std::ostream &os, const Gen &gen)
{
    switch(gen){

        case Gen::M:
            os<< "M";
            break;
        case Gen::F:
            os<<"F";
            break;
    }
    return os;
}

class Comanda
{
protected:
    int num;
    Produs prod;
    int nrPortii;
    Data data;

public:
    virtual std::shared_ptr<Comanda> clone() const = 0;
    virtual ~Comanda() = default;
    virtual float pretComanda();
    Comanda(int num, const Produs &prod, int nrPortii, const Data &data);
    virtual void afis(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Comanda &comanda);
    Comanda &operator+(int const num);
    Comanda &operator++();
    int getNrPortii() const;
};

Comanda::Comanda(int num, const Produs &prod, int nrPortii, const Data &data) : num(num), prod(prod), nrPortii(nrPortii),
                                                                                data(data) {}

float Comanda::pretComanda() {
    return prod.getPretProd() * nrPortii;
}

std::ostream &operator<<(std::ostream &os, const Comanda &comanda) {
    comanda.afis(os);
    return os;
}

void Comanda::afis(std::ostream &os) const{
    const auto &comanda = *this;
    os << "num: " << comanda.num << "\nprod: " << comanda.prod << " nrPortii: " << comanda.nrPortii << "\ndata: "
       << comanda.data<<"\n";

}

int Comanda::getNrPortii() const {
    return nrPortii;
}

Comanda &Comanda::operator+(const int num) { nrPortii += num;
    return *this;}

Comanda &Comanda::operator++() {
    nrPortii++;
}

class ComandaNormala : public Comanda
{

public:
    ComandaNormala(int num, const Produs &prod, int nrPortii, const Data &data);

    std::shared_ptr<Comanda> clone() const override;
};

std::shared_ptr<Comanda> ComandaNormala::clone() const {
    return std::make_shared<ComandaNormala>(*this);
}

ComandaNormala::ComandaNormala(int num, const Produs &prod, int nrPortii, const Data &data) : Comanda(num, prod,
                                                                                                      nrPortii, data) {}

class ComandaSpec: virtual public Comanda
{
protected:
    std::string obsClient;
    float pretSupl;
public:
    void afis(std::ostream &os) const override;

    ComandaSpec(int num, const Produs &prod, int nrPortii, const Data &data, const std::string &obsClient,
                float pretSupl);

    float pretComanda() override;

    std::shared_ptr<Comanda> clone() const override;
};

void ComandaSpec::afis(std::ostream &os) const {
    Comanda::afis(os);
    os << "\nObservatii client: " << obsClient<<" Pret Supplimentar: "<<pretSupl<<"\n";
}

std::shared_ptr<Comanda> ComandaSpec::clone() const {
    return std::make_shared<ComandaSpec>(*this);
}

ComandaSpec::ComandaSpec(int num, const Produs &prod, int nrPortii, const Data &data, const std::string &obsClient,
                         float pretSupl) : Comanda(num, prod, nrPortii, data), obsClient(obsClient),
                                           pretSupl(pretSupl) {}

float ComandaSpec::pretComanda() {
    return Comanda::pretComanda() + pretSupl*nrPortii;
}

class ComandaOnline : virtual public Comanda
{
protected:
    std::string adresaLivrare;
    int comLivrare;
public:
    ComandaOnline(int num, const Produs &prod, int nrPortii, const Data &data, const std::string &adresaLivrare,
                  int comLivrare);

    std::shared_ptr<Comanda> clone() const override;

    float pretComanda() override;

    void afis(std::ostream &os) const override;
};

std::shared_ptr<Comanda> ComandaOnline::clone() const {
    return std::make_shared<ComandaOnline>(*this);
}

ComandaOnline::ComandaOnline(int num, const Produs &prod, int nrPortii, const Data &data,
                             const std::string &adresaLivrare, int comLivrare) : Comanda(num, prod, nrPortii, data), adresaLivrare(adresaLivrare),
                                                                                 comLivrare(comLivrare) {}

void ComandaOnline::afis(std::ostream &os) const {
    Comanda::afis(os);
    os << "\nLivrata la adresa:" <<adresaLivrare<<" Cu comisionul: "<<comLivrare<<"\n";
}

float ComandaOnline::pretComanda() {
    return Comanda::pretComanda() + Comanda::pretComanda()*(comLivrare/100);
}

class ComandaOnlineSpeciala : public ComandaSpec, public ComandaOnline
{
public:
    ComandaOnlineSpeciala(int num, const Produs &prod, int nrPortii, const Data &data, const std::string &obsClient,
                          float pretSupl, int num1, const Produs &prod1, int nrPortii1, const Data &data1,
                          const std::string &adresaLivrare, int comLivrare);

    std::shared_ptr<Comanda> clone() const override;

    float pretComanda() override;

    void afis(std::ostream &os) const override;

};
ComandaOnlineSpeciala::ComandaOnlineSpeciala(int num, const Produs &prod, int nrPortii, const Data &data,
                                             const std::string &obsClient, float pretSupl, int num1,
                                             const Produs &prod1, int nrPortii1, const Data &data1,
                                             const std::string &adresaLivrare, int comLivrare) : Comanda(num, prod, nrPortii, data) ,
                                                                                                 ComandaOnline(num, prod, nrPortii, data, adresaLivrare, comLivrare),
                                                                                                 ComandaSpec(num, prod, nrPortii, data, obsClient, pretSupl)
                                             {}

std::shared_ptr<Comanda> ComandaOnlineSpeciala::clone() const {
    return std::make_shared<ComandaOnlineSpeciala>(*this);
}

void ComandaOnlineSpeciala::afis(std::ostream &os) const {
    ComandaSpec::afis(os);
    ComandaOnline::afis(os);
}

float ComandaOnlineSpeciala::pretComanda() {
    return ComandaSpec::pretComanda() + ComandaSpec::pretComanda()*(comLivrare/100);
}

class Ospatar
{
    std::string nume;
    std::vector<std::shared_ptr<Comanda>> comenzi;
    int nrComenzi = 0;
    Gen gen;
    int varsta;

public:
    Ospatar(const std::string &nume, Gen gen, int varsta);
    ~Ospatar() = default;

    void adaugaComanda(const Comanda &comanda);
    friend std::ostream &operator<<(std::ostream &os, const Ospatar &ospatar);

    bool operator<(const Ospatar &rhs) const;

    bool operator>(const Ospatar &rhs) const;

    bool operator<=(const Ospatar &rhs) const;

    bool operator>=(const Ospatar &rhs) const;

    bool operator==(const Ospatar &rhs) const;

    bool operator!=(const Ospatar &rhs) const;
};

Ospatar::Ospatar(const std::string &nume, Gen gen, int varsta) : nume(nume), gen(gen), varsta(varsta) {}

std::ostream &operator<<(std::ostream &os, const Ospatar &ospatar) {
    os << "nume: " << ospatar.nume  << " gen: " << ospatar.gen << " varsta: " << ospatar.varsta << " nrComenzi: " << ospatar.nrComenzi<<"\n";
    for(auto const &c: ospatar.comenzi)
        c->afis(os);
    return os;
}

bool Ospatar::operator<(const Ospatar &rhs) const {
    return nrComenzi < rhs.nrComenzi;
}

bool Ospatar::operator>(const Ospatar &rhs) const {
    return rhs < *this;
}

bool Ospatar::operator<=(const Ospatar &rhs) const {
    return !(rhs < *this);
}

bool Ospatar::operator>=(const Ospatar &rhs) const {
    return !(*this < rhs);
}

bool Ospatar::operator==(const Ospatar &rhs) const {
    return nrComenzi == rhs.nrComenzi;
}

bool Ospatar::operator!=(const Ospatar &rhs) const {
    return !(rhs == *this);
}

void Ospatar::adaugaComanda(const Comanda &comanda) {
    comenzi.push_back(comanda.clone());
    nrComenzi++;
}


int main()
{
    Ospatar a{"Marcel", Gen::M, 20};
    Ospatar b{"Ionela", Gen::F, 46};

    a.adaugaComanda(ComandaNormala(1, Produs("Cordon Bleu", 25), 2, Data(2020, 1, 12)));

    std::cout<<a;

    return 0;
}