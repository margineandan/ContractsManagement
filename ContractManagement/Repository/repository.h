#pragma once

#include "../Domain/disciplina.h"
#include "../Exceptions/errors.h"

#include <utility>
#include <vector>
#include <string>
#include <unordered_map>
#include <random>

using std::string;
using std::vector;
using std::unordered_map;

class RepoAbstract {
public:
    RepoAbstract() = default;

    RepoAbstract(const RepoAbstract& disciplina) = delete;

    virtual void add(const Disciplina& disciplina) = 0;

    virtual void remove(const Disciplina& disciplina) = 0;

    virtual const Disciplina& search(const string& Denumire, const string& Tip) = 0;

    virtual vector<Disciplina>& getAll() = 0;

    virtual void update(const Disciplina& newDisciplina) = 0;
};

class RepoDisciplina : public RepoAbstract {
private:
    vector<Disciplina> Catalog;

    bool exist(const Disciplina& disciplina);

public:
    RepoDisciplina() = default;

    RepoDisciplina(const Disciplina& disciplina) = delete;

    int getSize() const;

    void add(const Disciplina& disciplina) override;

    void remove(const Disciplina& disciplina) override;

    void update(const Disciplina& newDisciplina);

    const Disciplina& search(const string& Denumire, const string& Tip) override;

    vector<Disciplina>& getAll() override;
};

class RepoFile : public RepoDisciplina{
private:
    string filename;

    void loadfromfile();

    void writetofile();

public:
    explicit RepoFile(string filename): RepoDisciplina(), filename{filename} {
        loadfromfile();
    }

    void add(const Disciplina& disciplina) override {
        RepoDisciplina::add(disciplina);
        writetofile();
    }

    void remove(const Disciplina& disciplina) override {
        RepoDisciplina::remove(disciplina);
        writetofile();
    }
};

class RepoLab: public RepoAbstract {
private:
    unordered_map<int, Disciplina> discipline;
    double probabilitate;

    // functie ce returneaza probabilitatea
    void randomProbability() const;

    bool exist(const Disciplina& disciplina);

public:
    RepoLab() {
        std::mt19937 generator(std::random_device{}());
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        probabilitate = dist(generator);
    }

    void setProbabilitate(double probabilitate);

    //RepoLab(const Disciplina& alt) = delete;

    void add(const Disciplina& disciplina) override;

    void remove(const Disciplina& disciplina) override;

    const Disciplina& search(const string& Denumire, const string& Tip) override;

    vector<Disciplina>& getAll() override;

    virtual void update(const Disciplina& newDisciplina) override;
};

class RepoException: public Exception{
public:
    explicit RepoException(const string& err) : Exception(err) {}
};