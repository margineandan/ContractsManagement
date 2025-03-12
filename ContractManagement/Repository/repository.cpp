#include "repository.h"
#include <string>
#include <algorithm>
#include <fstream>

/**
 * Check if Disciplina object exists in Repo.
 *
 * @param disciplina(Disciplina) - Disciplina object to search
 *
 * @return bool: True = Found / False = Not Found
 */
bool RepoDisciplina::exist(const Disciplina &disciplina) {
    try {
        RepoDisciplina::search(disciplina.getDenumire(), disciplina.getTip());
        return true;
    }
    catch (RepoException&) {
        return false;
    }
}

/**
* Getter for number of discipline in Repo.
*
* @return integer
*/
int RepoDisciplina::getSize() const {
    return (int)this->Catalog.size();
}

/**
 * Add Disciplina object to Repo.
 *
 * @param disciplina(Disciplina) - Disciplina object to add
 *
 * @throw RepoExec(RepoErr) - error message
 *
 * @return NULL
 */
void RepoDisciplina::add(const Disciplina &disciplina) {
    if (exist(disciplina)) {
        throw RepoException("ERROR: disciplina exista deja...\n");
    }

    this->Catalog.push_back(disciplina);
}

/**
 * Remove Disciplina object from Repo.
 *
 * @param disciplina(Disciplina) - Disciplina object to remove
 *
 * @throw RepoExec(RepoErr) - error message
 *
 * @return NULL
 */
void RepoDisciplina::remove(const Disciplina &disciplina) {
    exist(disciplina);

    int i = 0;
    while (i < this->Catalog.size()) {
        if (Catalog.at(i).getDenumire() == disciplina.getDenumire() && Catalog.at(i).getTip() == disciplina.getTip()) {
            Catalog.erase(Catalog.begin() + i);
            break;
        }
        i++;
    }
}

/**
 * Search Disciplina object in Repo.
 *
 * @param movie(Disciplina) - Disciplina object to search
 *
 * @throw RepoExec(RepoErr) - error message
 *
 * @return Disciplina
 */
const Disciplina& RepoDisciplina::search(const std::string &Denumire, const std::string &Tip) {
    for (const auto& disciplina: this->Catalog) {
        if (disciplina.getDenumire() == Denumire && disciplina.getTip() == Tip)
            return disciplina;
    }

    throw RepoException("ERROR: disciplina nu exista...\n");
}

/**
 * Update Disciplina object from Repo.
 *
 * @param newDisciplina(Disciplina) - Disciplina object to update
 *
 * @throw RepoExec(RepoErr) - error message
 *
 * @return NULL
 */
void RepoDisciplina::update(const Disciplina &newDisciplina) {
    for (auto& disciplina: this->Catalog) {
        if (disciplina.getDenumire() == newDisciplina.getDenumire() && disciplina.getTip() == newDisciplina.getTip()) {
            disciplina = newDisciplina;
            return ;
        }
    }

    throw RepoException("ERROR: disciplina nu exista...\n");
}

/**
 * Getter for all Disciplina object from Repo.
 *
 * @return vector<Disciplina>
 */
vector<Disciplina>& RepoDisciplina::getAll() {
    return this->Catalog;
}

/**
 * Function that loads from a file
 *
 * @return NULL
 */
void RepoFile::loadfromfile() {
    std::ifstream in(filename);
    if (!in.is_open()) throw RepoException("Eroare la deschiderea fisierului...");
    while(!in.eof()) {
        string denumire, tip, cadruDidactic;
        int ore;
        if (in.eof()) break;
        in >> denumire;
        if (in.eof()) break;
        in >> ore;
        if (in.eof()) break;
        in >> tip;
        if (in.eof()) break;
        in >> cadruDidactic;
        Disciplina disciplina{denumire, ore, tip, cadruDidactic};
        RepoDisciplina::add(disciplina);
    }
    in.close();
}

/**
 * Function that writes to a file
 *
 * @return NULL
 */
void RepoFile::writetofile() {
    std::ofstream out(filename);
    if (!out.is_open()) throw RepoException("Eroare la deschiderea fisierului...");
    for (const auto &disciplina: RepoDisciplina::getAll()) {
        out << disciplina.getDenumire();
        out << std::endl;
        out << disciplina.getOre();
        out << std::endl;
        out << disciplina.getTip();
        out << std::endl;
        out << disciplina.getCadru();
        out << std::endl;
    }
    out.close();
}

/**
 * Verifies if the probability set is less than a random number between 0 and 1.
 *
 * @return NULL
 */
void RepoLab::randomProbability() const {
    double random = ((double) rand() /  (RAND_MAX));
    if (random > probabilitate) {
        throw RepoException("ERROR: Nu se poate executa aceasta functie...");
    }
}

/**
 * Check if Disciplina object exists in Repo.
 *
 * @param disciplina(Disciplina) - Disciplina object to search
 *
 * @return bool: True = Found / False = Not Found
 */
bool RepoLab::exist(const Disciplina &disciplina) {
    randomProbability();
    for (const auto &dis: discipline)
        if (dis.second.getDenumire() == disciplina.getDenumire() && dis.second.getTip() == disciplina.getTip())
            return true;

    return false;
}

void RepoLab::setProbabilitate(double probabilitatea) {
    probabilitate = probabilitatea;
}

/**
 * Add Disciplina object to Repo.
 *
 * @param disciplina(Disciplina) - Disciplina object to add
 *
 * @throw RepoExec(RepoErr) - error message
 *
 * @return NULL
 */
void RepoLab::add(const Disciplina &disciplina) {
    randomProbability();
    if (exist(disciplina))
        throw RepoException("ERROR: Disciplina exista deja...");

    int i = int(discipline.size());
    discipline.insert(std::make_pair(i, disciplina));
}

/**
 * Remove Disciplina object from Repo.
 *
 * @param disciplina(Disciplina) - Disciplina object to remove
 *
 * @throw RepoExec(RepoErr) - error message
 *
 * @return NULL
 */
void RepoLab::remove(const Disciplina &disciplina) {
    randomProbability();
    int i = 0;
    while(i < discipline.size() && discipline.at(i).getDenumire() != disciplina.getDenumire() &&
          discipline.at(i).getTip() != disciplina.getTip())
        i++;

    if (i >= discipline.size())
        throw RepoException("ERROR: Disciplina nu exista...");

    for(int j = i; j < discipline.size() - 1; j++)
        discipline.at(j) = discipline.at(j + 1);
    discipline.erase((int)discipline.size() - 1);
}

/**
 * Search Disciplina object in Repo.
 *
 * @param movie(Disciplina) - Disciplina object to search
 *
 * @throw RepoExec(RepoErr) - error message
 *
 * @return Disciplina
 */
const Disciplina& RepoLab::search(const std::string &Denumire, const std::string &Tip) {
    randomProbability();
    auto iterator = std::find_if(discipline.begin(), discipline.end(), [=](const std::pair<int, Disciplina> disciplina) {
        return disciplina.second.getDenumire() == Denumire && disciplina.second.getTip() == Tip;
    });

    if (iterator == discipline.end())
        throw RepoException("ERROR: Disciplina nu exista...");

    return (*iterator).second;
}

/**
 * Update Disciplina object from Repo.
 *
 * @param newDisciplina(Disciplina) - Disciplina object to update
 *
 * @throw RepoExec(RepoErr) - error message
 *
 * @return NULL
 */
void RepoLab::update(const Disciplina &newDisciplina) {
}

/**
 * Getter for all Disciplina object from Repo.
 *
 * @return vector<Disciplina>
 */
vector<Disciplina> DISCIPLINE;
vector<Disciplina>& RepoLab::getAll() {
    DISCIPLINE.clear();
    for(const auto& disciplina: discipline)
        DISCIPLINE.push_back(disciplina.second);

    return DISCIPLINE;
}
