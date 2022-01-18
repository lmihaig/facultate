/*
Colocviu POO 2021
Licu Mihai-George Grupa 262
Compilator: MinGW (Clion cpp20)
Tutore de laborator: Marius Miculta-Campeanu
 */

#include <iostream>
#include <memory>
#include <algorithm>
#include <vector>
#include <string>

class eroare_aplicatie : public std::runtime_error
{
public:
    explicit eroare_aplicatie(const std::string &arg) : runtime_error(arg) {}
};

class eroare_data : public eroare_aplicatie
{
public:
    explicit eroare_data(const std::string &arg) : eroare_aplicatie(arg) {}
};

class eroare_plimbari : public eroare_aplicatie
{
public:
    explicit eroare_plimbari(const std::string &arg) : eroare_aplicatie(arg) {}
};

class Data
{
    int an;
    int luna;
    int zi;

public:
    Data(int an, int luna, int zi);

    bool operator<(const Data &rhs) const;

    bool operator>(const Data &rhs) const;

    bool operator==(const Data &rhs) const;

    bool operator!=(const Data &rhs) const;

    bool operator<=(const Data &rhs) const;

    bool operator>=(const Data &rhs) const;
    int getDataDif(Data const &datafinal) const;
    friend std::ostream &operator<<(std::ostream &os, const Data &data);
};

Data::Data(int an, int luna, int zi) : an(an), luna(luna), zi(zi) {}

std::ostream &operator<<(std::ostream &os, const Data &data)
{
    os << "an: " << data.an << " luna: " << data.luna << " zi: " << data.zi;
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

bool Data::operator==(const Data &rhs) const
{
    return an == rhs.an &&
           luna == rhs.luna &&
           zi == rhs.zi;
}

bool Data::operator!=(const Data &rhs) const
{
    return !(rhs == *this);
}

int Data::getDataDif(const Data &datafinal) const
{

    if (datafinal <= *this)
        throw eroare_data("Data de final mai mica decat cea de inceput!");
    int zile = 0;
    // fiecare an are 365 de zile si fiecare luna are exact 30 zile, n-am stiut altfel
    zile += (datafinal.an - an) * 365;
    zile += (datafinal.luna - luna) * 30;
    zile += (datafinal.zi - zi);
    return zile;
}

class Cazare
{
    const int codcur;
    int mese;
    bool cazatSingur;
    std::vector<std::string> alergeni;
    Data inceputCazare;
    Data finalCazare;
    std::string numePachet;

public:
    Cazare(const int codcur, int mese, bool cazatSingur,
           const Data &inceputCazare, const Data &finalCazare, const std::string &numePachet);
    virtual ~Cazare() = default;
    virtual std::shared_ptr<Cazare> clone() const = 0;
    virtual void afis(std::ostream &os) const;
    virtual float calcPret();
    friend std::ostream &operator<<(std::ostream &os, const Cazare &cazare);
    virtual void adaugaAlergeni(std::string alergen);
};

Cazare::Cazare(const int codcur, int mese, bool cazatSingur,
               const Data &inceputCazare, const Data &finalCazare, const std::string &numePachet) : codcur(codcur),
                                                                                                    mese(mese), cazatSingur(
                                                                                                                    cazatSingur),
                                                                                                    inceputCazare(inceputCazare), finalCazare(finalCazare),
                                                                                                    numePachet(
                                                                                                        numePachet) {}

std::ostream &operator<<(std::ostream &os, const Cazare &cazare)
{
    cazare.afis(os);
    return os;
}

void Cazare::afis(std::ostream &os) const
{
    const auto &cazare = *this;
    os << "codcur: " << cazare.codcur << " mese: " << cazare.mese << " cazatSingur: " << cazare.cazatSingur
       << " alergeni: "
       << "\n";
    for (const auto &al : alergeni)
        os << al;
    os << " inceputCazare: " << cazare.inceputCazare << " finalCazare: "
       << cazare.finalCazare << " numePachet: " << cazare.numePachet;
}

float Cazare::calcPret()
{
    int zile = inceputCazare.getDataDif(finalCazare);
    float pret = zile * 100;
    if (cazatSingur)
        pret += zile * 30;
    return pret;
}

void Cazare::adaugaAlergeni(std::string alergen)
{
    alergeni.push_back(alergen);
}

class CazareClasic : public Cazare
{
public:
    CazareClasic(const int codcur, int mese, bool cazatSingur, const Data &inceputCazare, const Data &finalCazare,
                 const std::string &numePachet);

    std::shared_ptr<Cazare> clone() const override;
};

CazareClasic::CazareClasic(const int codcur, int mese, bool cazatSingur, const Data &inceputCazare,
                           const Data &finalCazare, const std::string &numePachet) : Cazare(codcur, mese, cazatSingur, inceputCazare, finalCazare,
                                                                                            numePachet) {}

std::shared_ptr<Cazare> CazareClasic::clone() const
{
    return std::make_shared<CazareClasic>(*this);
}

class CazareSport : virtual public Cazare
{
    int plimbari;

public:
    CazareSport(const int codcur, int mese, bool cazatSingur, const Data &inceputCazare, const Data &finalCazare,
                const std::string &numePachet, int plimbari);

    void afis(std::ostream &os) const override;

    std::shared_ptr<Cazare> clone() const override;

    float calcPret() override;
};

CazareSport::CazareSport(const int codcur, int mese, bool cazatSingur, const Data &inceputCazare,
                         const Data &finalCazare, const std::string &numePachet, int plimbari) : Cazare(codcur, mese, cazatSingur, inceputCazare,
                                                                                                        finalCazare, numePachet),
                                                                                                 plimbari(plimbari)
{
    if (plimbari > 5)
        throw eroare_plimbari("Maxim 5 plimbari!");
}

float CazareSport::calcPret()
{
    return Cazare::calcPret() + plimbari * 30;
}

void CazareSport::afis(std::ostream &os) const
{
    Cazare::afis(os);
    os << "Numarul de plimbari: " << plimbari;
}

std::shared_ptr<Cazare> CazareSport::clone() const
{
    return std::make_shared<CazareSport>(*this);
}

class CazareConfort : virtual public Cazare
{
    std::vector<std::string> activitati;

public:
    CazareConfort(const int codcur, int mese, bool cazatSingur, const Data &inceputCazare, const Data &finalCazare,
                  const std::string &numePachet);

    void afis(std::ostream &os) const override;
    int getActivitati();
    std::shared_ptr<Cazare> clone() const override;

    float calcPret() override;

    virtual void adaugaActivitate(std::string activitate, bool vip = false);
};

CazareConfort::CazareConfort(const int codcur, int mese, bool cazatSingur, const Data &inceputCazare,
                             const Data &finalCazare, const std::string &numePachet) : Cazare(codcur, mese,
                                                                                              cazatSingur,
                                                                                              inceputCazare,
                                                                                              finalCazare,
                                                                                              numePachet)
{
}

void CazareConfort::adaugaActivitate(std::string activitate, bool vip)
{
    if (!vip)
    {
        if (activitati.size() >= 2)
            throw eroare_aplicatie("Maxim doua activitati in pachetul confort!");
    }
    activitati.push_back(activitate);
}

std::shared_ptr<Cazare> CazareConfort::clone() const
{
    return std::make_shared<CazareConfort>(*this);
}

float CazareConfort::calcPret()
{
    return Cazare::calcPret() + getActivitati() * 50;
}

void CazareConfort::afis(std::ostream &os) const
{
    Cazare::afis(os);
    for (const auto &act : activitati)
        os << act;
}

int CazareConfort::getActivitati()
{
    return activitati.size();
}

class CazareVIP : public CazareSport, public CazareConfort
{
    int minutePlimbare;

public:
    std::shared_ptr<Cazare> clone() const override;

    CazareVIP(const int codcur, int mese, bool cazatSingur, const Data &inceputCazare, const Data &finalCazare,
              const std::string &numePachet, int plimbari,
              int minutePlimbare);

    float calcPret() override;

    void adaugaActivitate(std::string activitate, bool vip = true) override;

    void afis(std::ostream &os) const override;
};

std::shared_ptr<Cazare> CazareVIP::clone() const
{
    return std::make_shared<CazareVIP>(*this);
}

void CazareVIP::afis(std::ostream &os) const
{
    CazareSport::afis(os);
    CazareConfort::afis(os);
    os << "minute de plimbat: " << minutePlimbare;
}

float CazareVIP::calcPret()
{
    return Cazare::calcPret() + 0.8 * minutePlimbare + 40 * getActivitati();
}

CazareVIP::CazareVIP(const int codcur, int mese, bool cazatSingur, const Data &inceputCazare, const Data &finalCazare,
                     const std::string &numePachet, int plimbari,
                     int minutePlimbare) : Cazare(codcur, mese, cazatSingur, inceputCazare, finalCazare, numePachet),
                                           CazareSport(codcur, mese, cazatSingur, inceputCazare, finalCazare, numePachet,
                                                       plimbari),
                                           CazareConfort(codcur, mese, cazatSingur, inceputCazare, finalCazare,
                                                         numePachet),
                                           minutePlimbare(minutePlimbare)
{
    if (minutePlimbare < 30)
        throw eroare_plimbari("Minim 30 de minute!");
}

void CazareVIP::adaugaActivitate(std::string activitate, bool vip)
{
    CazareConfort::adaugaActivitate(activitate, vip);
}

class Animal
{
    static inline int cod = 0;
    const int codanimal;
    std::string nume;
    int varsta;
    std::string rasa;

public:
    Animal(const std::string &nume, int varsta, const std::string &rasa);
    ~Animal() = default;
    static int getCod();
    std::shared_ptr<Animal> clone() const;
    friend std::ostream &operator<<(std::ostream &os, const Animal &animal);
    void afis(std::ostream &os) const;
};

Animal::Animal(const std::string &nume, int varsta, const std::string &rasa) : nume(nume), varsta(varsta),
                                                                               rasa(rasa), codanimal(cod++) {}

std::ostream &operator<<(std::ostream &os, const Animal &animal)
{
    animal.afis(os);
    return os;
}

int Animal::getCod()
{
    return cod;
}

std::shared_ptr<Animal> Animal::clone() const
{
    return std::make_shared<Animal>(*this);
}

void Animal::afis(std::ostream &os) const
{
    const auto &animal = *this;
    os << "nume: " << animal.nume << " varsta: " << animal.varsta << " rasa: " << animal.rasa << " cod: "
       << animal.codanimal;
}

class Client
{
    std::string nume;
    std::string nrTel;
    std::string adresa;
    std::string CNP;
    std::vector<std::pair<std::shared_ptr<Cazare>, std::shared_ptr<Animal>>> formular;

public:
    void adaugaFormular(const Cazare &cazare, const Animal &animal);
    Client(const std::string &nume, const std::string &nrTel, const std::string &adresa, const std::string &cnp);
    ~Client() = default;
    float getPretTotal();
    friend std::ostream &operator<<(std::ostream &os, const Client &client);
};

Client::Client(const std::string &nume, const std::string &nrTel, const std::string &adresa, const std::string &cnp) : nume(nume), nrTel(nrTel), adresa(adresa), CNP(cnp) {}

void Client::adaugaFormular(const Cazare &cazare, const Animal &animal)
{
    formular.push_back(std::make_pair(cazare.clone(), animal.clone()));
}

std::ostream &operator<<(std::ostream &os, const Client &client)
{
    os << "nume: " << client.nume << " nrTel: " << client.nrTel << " adresa: " << client.adresa << " CNP: "
       << client.CNP << "\n";
    os << "Formulare:\n";
    for (const auto &form : client.formular)
    {
        os << "Cazarea: ";
        form.first->afis(os);
        os << "\n";
        os << "Animalul: ";
        form.second->afis(os);
        os << "\n";
    }
    return os;
}

float Client::getPretTotal()
{
    float pretTotal = 0;
    for (const auto &form : formular)
    {
        pretTotal += form.first->calcPret();
    }
    return pretTotal;
}

int main()
{
    try
    {
        Client c1("Condrea Tudor", "0729571729", "Strada plopilor intre vii", "6220112015386");
        Animal a1("Miti", 2, "pisica portocalie");
        Animal a2("Rex", 4, "husky");
        CazareVIP cazare1(a1.getCod(), 5, 1, Data(2022, 1, 14), Data(2022, 1, 17), "pachet vip", 1, 30);
        cazare1.adaugaActivitate("uitat la televizor");
        cazare1.adaugaActivitate("spalat pe dinti");
        cazare1.adaugaAlergeni("pasta de dinti");
        CazareClasic cazare2(a2.getCod(), 8, 0, Data(2022, 1, 14), Data(2022, 1, 15), "pachet clasic");
        cazare2.adaugaAlergeni("nutella");
        c1.adaugaFormular(cazare1, a1);
        c1.adaugaFormular(cazare2, a2);
        std::cout << c1;
        std::cout << c1.getPretTotal();
    }
    catch (std::runtime_error &error)
    {
        std::cout << "Eroare cu cazarile " << error.what() << "\n";
    }
    return 0;
}
