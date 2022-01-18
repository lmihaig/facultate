//
// Created by Mihai on 13/01/2022.
//

/* Licu Mihai-George Grupa 262
Compilator: Clion MinGW
Tutore de laborator: Marius Miculta-Campeanu */
#include <iostream>
#include <memory>
#include <algorithm>

class eroare_aplicatie : public std::runtime_error
{
public:
    explicit eroare_aplicatie(const std::string &arg) : runtime_error(arg) {}
};

class eroare_produs : public eroare_aplicatie
{
public:
    explicit eroare_produs(const std::string &arg) : eroare_aplicatie(arg) {}
};

class Data
{
    int an;
    int luna;
    int zi;

public:
    bool operator<(const Data &rhs) const;
    bool operator>(const Data &rhs) const;
    bool operator<=(const Data &rhs) const;
    bool operator>=(const Data &rhs) const;

    int getZi() const;
    int getLuna() const;
    int getAn() const;

    friend std::ostream &operator<<(std::ostream &os, const Data &data);

    Data(int zi, int luna, int an);
};

Data::Data(int zi, int luna, int an) : zi(zi), luna(luna), an(an) {}

int Data::getZi() const
{
    return zi;
}

int Data::getLuna() const
{
    return luna;
}

int Data::getAn() const
{
    return an;
}

std::ostream &operator<<(std::ostream &os, const Data &data)
{
    os << "zi: " << data.zi << " luna: " << data.luna << " an: " << data.an;
    return os;
}

bool Data::operator<(const Data &rhs) const
{
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

bool Data::operator>(const Data &rhs) const
{
    return rhs < *this;
}

bool Data::operator<=(const Data &rhs) const
{
    return !(rhs < *this);
}

bool Data::operator>=(const Data &rhs) const
{
    return !(*this < rhs);
}

enum class UnitateMasura
{
    Bucata,
    Greutate,
    Volum
};
std::ostream &operator<<(std::ostream &os, const UnitateMasura &unitate)
{
    switch (unitate)
    {
    case UnitateMasura::Bucata:
        os << "Bucata";
        break;
    case UnitateMasura::Greutate:
        os << "Greutate";
        break;
    case UnitateMasura::Volum:
        os << "Volum";
        break;
    }
    return os;
}
class Produs
{
    UnitateMasura unitate;
    std::string nume;
    Data intrare;
    int cantitate;
    float pretUnitate;

public:
    virtual std::shared_ptr<Produs> clone() const = 0;
    virtual ~Produs() = default;
    virtual float pretlot();
    virtual void afis(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Produs &produs);

    Produs(UnitateMasura unitate, const std::string &nume, const Data &intrare, int cantitate, float pretUnitate);
};

float Produs::pretlot()
{
    return pretUnitate * cantitate;
}

std::ostream &operator<<(std::ostream &os, const Produs &produs)
{
    produs.afis(os);
    return os;
}

void Produs::afis(std::ostream &os) const
{
    const auto &produs = *this;
    os << "unitate: " << produs.unitate << " nume: " << produs.nume << " cantitate: " << produs.cantitate
       << " pretUnitate: " << produs.pretUnitate << ", intrat in magazin la: " << intrare;
}

Produs::Produs(UnitateMasura unitate, const std::string &nume, const Data &intrare, int cantitate, float pretUnitate)
    : unitate(unitate), nume(nume), intrare(intrare), cantitate(cantitate), pretUnitate(pretUnitate) {}

class ProdusSimplu : virtual public Produs
{
public:
    std::shared_ptr<Produs> clone() const override;

    ProdusSimplu(UnitateMasura unitate, const std::string &nume, const Data &intrare, int cantitate, float pretUnitate);
};

std::shared_ptr<Produs> ProdusSimplu::clone() const
{
    return std::make_shared<ProdusSimplu>(*this);
}

ProdusSimplu::ProdusSimplu(UnitateMasura unitate, const std::string &nume, const Data &intrare, int cantitate,
                           float pretUnitate) : Produs(unitate, nume, intrare, cantitate, pretUnitate) {}

class Produs_Perisabil : virtual public Produs
{
    Data valabilitate;

public:
    std::shared_ptr<Produs> clone() const override;

    void afis(std::ostream &os) const override;

    Produs_Perisabil(UnitateMasura unitate, const std::string &nume, const Data &intrare, int cantitate,
                     float pretUnitate, const Data &valabilitate);
};

std::shared_ptr<Produs> Produs_Perisabil::clone() const
{
    return std::make_shared<Produs_Perisabil>(*this);
}

void Produs_Perisabil::afis(std::ostream &os) const
{
    Produs::afis(os);
    os << "Expira la " << valabilitate << "\n";
}

Produs_Perisabil::Produs_Perisabil(UnitateMasura unitate, const std::string &nume, const Data &intrare, int cantitate,
                                   float pretUnitate, const Data &valabilitate) : Produs(unitate, nume, intrare,
                                                                                         cantitate, pretUnitate),
                                                                                  valabilitate(valabilitate)
{
    if (valabilitate < intrare)
        throw eroare_produs("expirat");
}

class Produs_Promotie : virtual public Produs
{
    float discount;

public:
    float pretlot() override;

    void afis(std::ostream &os) const override;

    Produs_Promotie(UnitateMasura unitate, const std::string &nume, const Data &intrare, int cantitate,
                    float pretUnitate, float discount);

    std::shared_ptr<Produs> clone() const override;
};

std::shared_ptr<Produs> Produs_Promotie::clone() const
{
    return std::make_shared<Produs_Promotie>(*this);
}

float Produs_Promotie::pretlot()
{
    return Produs::pretlot() * (1 - discount);
}

void Produs_Promotie::afis(std::ostream &os) const
{
    Produs::afis(os);
    os << "Discount: " << discount << "\n";
}

Produs_Promotie::Produs_Promotie(UnitateMasura unitate, const std::string &nume, const Data &intrare, int cantitate,
                                 float pretUnitate, float discount) : Produs(unitate, nume, intrare, cantitate,
                                                                             pretUnitate),
                                                                      discount(discount)
{
    if (discount < 0)
        throw eroare_produs("discount negativ");
}

class Produs_Promotie_Perisabil : public Produs_Perisabil, public Produs_Promotie
{
public:
    Produs_Promotie_Perisabil(UnitateMasura masura, std::string string, Data dataintrare, int cantitate, double pret,
                              double discount, Data dataexpirare);

    void afis(std::ostream &os) const override;

    std::shared_ptr<Produs> clone() const override;
};

std::shared_ptr<Produs> Produs_Promotie_Perisabil::clone() const
{
    return std::make_shared<Produs_Promotie_Perisabil>(*this);
}

void Produs_Promotie_Perisabil::afis(std::ostream &os) const
{
    Produs_Perisabil::afis(os);
    Produs_Promotie::afis(os);
}

Produs_Promotie_Perisabil::Produs_Promotie_Perisabil(UnitateMasura masura, std::string string, Data dataintrare,
                                                     int cantitate, double pret, double discount, Data dataexpirare) : Produs(masura, string, dataintrare, cantitate, pret),
                                                                                                                       Produs_Perisabil(masura, string, dataintrare, cantitate, pret, dataexpirare),
                                                                                                                       Produs_Promotie(masura, string, dataintrare, cantitate, pret, discount)
{
}

class Magazin
{
    std::vector<std::shared_ptr<Produs>> produse;
    std::string nume;

public:
    Magazin(const Magazin &m);
    Magazin &operator=(const Magazin &m);
    ~Magazin() = default;
    void adauga(const Produs &p);

    friend std::ostream &operator<<(std::ostream &os, const Magazin &magazin);

    Magazin(const std::string &nume);

    Magazin(const std::vector<std::shared_ptr<Produs>> &produse, const std::string &nume);
};

Magazin::Magazin(const Magazin &m)
{
    for (const auto &produs : m.produse)
    {
        produse.push_back(produs->clone());
    }
}

Magazin &Magazin::operator=(const Magazin &m)
{
    nume = m.nume;
    for (const auto &produs : m.produse)
    {
        produse.push_back(produs->clone());
    }
    return *this;
}

void Magazin::adauga(const Produs &p)
{
    produse.push_back(p.clone());
}

Magazin::Magazin(const std::string &nume) : nume(nume) {}

Magazin::Magazin(const std::vector<std::shared_ptr<Produs>> &produse, const std::string &nume) : produse(produse),
                                                                                                 nume(nume) {}

std::ostream &operator<<(std::ostream &os, const Magazin &magazin)
{
    os << "nume: " << magazin.nume << "\n";
    for (const auto &produs : magazin.produse)
        produs->afis(os);
    return os;
}

int main()
{
    Magazin m{"Mega-Image"};
    m.adauga(Produs_Promotie{UnitateMasura::Bucata, "Ceapa", Data{11, 1, 2022}, 50, 7.33, 0.2});
    m.adauga(Produs_Perisabil{UnitateMasura::Greutate, "Rosii", Data{5, 1, 2022}, 100, 3, Data{20, 1, 2022}});
    m.adauga(ProdusSimplu{UnitateMasura::Bucata, "Orez", Data{10, 1, 2022}, 200, 10});
    m.adauga(Produs_Promotie_Perisabil{UnitateMasura::Volum, "Pasta de dinti", Data{11, 1, 2022}, 300, 6.33, 0.2, Data{30, 2, 2023}});
    std::cout << m;
    return 0;
}