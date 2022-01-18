#include <iostream>
#include <memory>
#include <algorithm>

class Jucarie
{
protected:
    inline static int totalJucarii = 0;
    std::string denumire;
    float dimensiune;
    std::string tip;

public:
    virtual std::shared_ptr<Jucarie> clone() const = 0;
    Jucarie(const std::string &denumire, float dimensiune, const std::string &tip);
    virtual ~Jucarie() = default;
    virtual void afis(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Jucarie &jucarie);
};

Jucarie::Jucarie(const std::string &denumire, float dimensiune, const std::string &tip) : denumire(denumire),
                                                                                          dimensiune(dimensiune), tip(tip) { totalJucarii++; }

std::ostream &operator<<(std::ostream &os, const Jucarie &jucarie)
{
    jucarie.afis(os);
    return os;
}

void Jucarie::afis(std::ostream &os) const
{
    const auto &jucarie = *this;
    os << "denumire: " << jucarie.denumire << " dimensiune: " << jucarie.dimensiune << " tip: " << jucarie.tip << "\n";
}

class JucarieClasica : public Jucarie
{
    inline static int totalJucariiClasice = 0;
    std::string material;
    std::string culoare;

public:
    JucarieClasica(const std::string &denumire, float dimensiune, const std::string &tip, const std::string &material,
                   const std::string &culoare);

    void afis(std::ostream &os) const override;

    std::shared_ptr<Jucarie> clone() const override;
};

JucarieClasica::JucarieClasica(const std::string &denumire, float dimensiune, const std::string &tip,
                               const std::string &material, const std::string &culoare) : Jucarie(denumire, dimensiune, tip), material(material),
                                                                                          culoare(culoare) { totalJucariiClasice++; }

std::shared_ptr<Jucarie> JucarieClasica::clone() const
{
    return std::make_shared<JucarieClasica>(*this);
}

void JucarieClasica::afis(std::ostream &os) const
{
    Jucarie::afis(os);
    os << "material: " << material << " culoare: " << culoare << "\n";
}

class JucarieEducativa : virtual public Jucarie
{
protected:
    inline static int totalJucariiEducative = 0;
    std::string abilitate;

public:
    JucarieEducativa(const std::string &denumire, float dimensiune, const std::string &tip,
                     const std::string &abilitate);

    std::shared_ptr<Jucarie> clone() const override;

    void afis(std::ostream &os) const override;
};

std::shared_ptr<Jucarie> JucarieEducativa::clone() const
{
    return std::make_shared<JucarieEducativa>(*this);
}

JucarieEducativa::JucarieEducativa(const std::string &denumire, float dimensiune, const std::string &tip,
                                   const std::string &abilitate) : Jucarie(denumire, dimensiune, tip), abilitate(abilitate) { totalJucariiEducative++; }

void JucarieEducativa::afis(std::ostream &os) const
{
    Jucarie::afis(os);
    os << "abilitatea dezvoltata: " << abilitate << "\n";
}

class JucarieElectronica : virtual public Jucarie
{
protected:
    inline static int totalJucariiElectronice = 0;
    int nrBaterii;

public:
    JucarieElectronica(const std::string &denumire, float dimensiune, const std::string &tip, int nrBaterii);

    std::shared_ptr<Jucarie> clone() const override;

    void afis(std::ostream &os) const override;
};

JucarieElectronica::JucarieElectronica(const std::string &denumire, float dimensiune, const std::string &tip,
                                       int nrBaterii) : Jucarie(denumire, dimensiune, tip), nrBaterii(nrBaterii) { totalJucariiElectronice++; }

std::shared_ptr<Jucarie> JucarieElectronica::clone() const
{
    return std::make_shared<JucarieElectronica>(*this);
}

void JucarieElectronica::afis(std::ostream &os) const
{
    Jucarie::afis(os);
    os << "numarul de baterii necesare: " << nrBaterii << "\n";
}

class JucarieModerna : public JucarieEducativa, public JucarieElectronica
{
    inline static int totalJucariiModerne = 0;
    std::string brand;
    std::string model;

public:
    JucarieModerna(const std::string &denumire, float dimensiune, const std::string &tip,
                   const std::string &brand, const std::string &model);

    std::shared_ptr<Jucarie> clone() const override;

    void afis(std::ostream &os) const override;
};

JucarieModerna::JucarieModerna(const std::string &denumire, float dimensiune, const std::string &tip,
                               const std::string &brand, const std::string &model) : Jucarie(denumire, dimensiune, tip),
                                                                                     JucarieEducativa(denumire, dimensiune, tip, "generala"),
                                                                                     JucarieElectronica(denumire, dimensiune, tip, 1),
                                                                                     brand(brand), model(model)
{
    totalJucariiModerne++;
    totalJucariiElectronice--;
    totalJucariiEducative--;
}

std::shared_ptr<Jucarie> JucarieModerna::clone() const
{
    return std::make_shared<JucarieModerna>(*this);
}

void JucarieModerna::afis(std::ostream &os) const
{
    Jucarie::afis(os);
    os << "numarul de baterii necesare:" << nrBaterii << " abilitatea dezvoltata: " << abilitate << "\n";
}

class eroare_aplicatie : public std::runtime_error
{
public:
    explicit eroare_aplicatie(const std::string &arg) : runtime_error(arg) {}
};

class eroare_faptebune : public eroare_aplicatie
{
public:
    explicit eroare_faptebune(const std::string &arg) : eroare_aplicatie(arg) {}
};

class Copil
{
protected:
    inline static int ID = 0;
    const int myID;
    std::string nume;
    std::string prenume;
    std::string adresa;
    int varsta;
    int nrFapteBune;
    std::vector<std::shared_ptr<Jucarie>> jucarii;

public:
    Copil(const std::string &nume, const std::string &prenume, const std::string &adresa, int varsta, int nrFapteBune, const int myID);
    virtual void adaugare(const Jucarie &j);
    virtual ~Copil() = default;
    virtual void afis(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os, const Copil &copil);
};

Copil::Copil(const std::string &nume, const std::string &prenume, const std::string &adresa, int varsta,
             int nrFapteBune, const int myID) : nume(nume), prenume(prenume), adresa(adresa), varsta(varsta), nrFapteBune(nrFapteBune), myID(ID++)
{
    if (nrFapteBune < 0)
        throw eroare_faptebune("Numarul de fapte bune trebuie sa fie pozitiv!");
}

void Copil::adaugare(const Jucarie &j)
{
    if (nrFapteBune <= jucarii.size())
        throw eroare_faptebune("Numarul de cadouri este maxim numarul de fapte bune!");
    jucarii.push_back(j.clone());
}

void Copil::afis(std::ostream &os) const
{
    const auto &copil = *this;
    os << "myID: " << copil.myID << " nume: " << copil.nume << " prenume: " << copil.prenume << " adresa: "
       << copil.adresa << " varsta: " << copil.varsta << " nrFapteBune: " << copil.nrFapteBune << "\n";
    os << "jucarii:\n";
    for (const auto &j : jucarii)
        j->afis(os);
    os << "\n";
}

std::ostream &operator<<(std::ostream &os, const Copil &copil)
{
    copil.afis(os);
    return os;
}

class CopilCuminte : public Copil
{
    int nrDulciuri;

public:
    CopilCuminte(const std::string &nume, const std::string &prenume, const std::string &adresa, int varsta,
                 int nrFapteBune, int nrDulciuri);

    void afis(std::ostream &os) const override;
};

CopilCuminte::CopilCuminte(const std::string &nume, const std::string &prenume, const std::string &adresa, int varsta,
                           int nrFapteBune, int nrDulciuri) : Copil(nume, prenume, adresa, varsta, nrFapteBune, ID), nrDulciuri(nrDulciuri)
{
    if (nrFapteBune < 10)
        throw eroare_faptebune("Faptele bune ale unui copil cuminte trebuie sa fie minim 10!");
}

void CopilCuminte::afis(std::ostream &os) const
{
    Copil::afis(os);
    os << "Numarul de dulciuri: " << nrDulciuri << "\n";
}

class CopilNeastamparat : public Copil
{
    int nrCarbuni;

public:
    void afis(std::ostream &os) const override
    {
        Copil::afis(os);
        os << "Numarul de carbuni: " << nrCarbuni << "\n";
    }

    CopilNeastamparat(const std::string &nume, const std::string &prenume, const std::string &adresa, int varsta,
                      int nrFapteBune, int nrCarbuni) : Copil(nume, prenume, adresa, varsta, nrFapteBune, ID), nrCarbuni(nrCarbuni) {}
};

int main()
{

    try
    {
        std::vector<Copil> copii;
        copii.push_back(CopilCuminte("Iancu", "Marcel-Tudor", "Strada Paparuda Nr 23", 14, 12, 231));
        copii[0].adaugare(JucarieEducativa("Sueprglue", 13, "de mancat", "nutritiva"));
        copii[0].adaugare(JucarieElectronica("aparat de ras in nas", 12, "grooming", 2));
        copii[0].adaugare(JucarieClasica("Bat", 20, "de bataie", "lemn", "maro"));

        copii.push_back(CopilNeastamparat("Ghita", "Marcel-Iancu", "Strada plopilor intre vii", 12, 2, 69));
        copii[1].adaugare(JucarieModerna("Fidgetspinner", 1, "De pus pe deget", "Gucci", "x6"));
        for (const auto &c : copii)
        {
            std::cout << c;
        }
    }
    catch (std::runtime_error &error)
    {
        std::cout << "Eroare cu copii " << error.what() << "\n";
    }
    return 0;
}
