#pragma clang diagnostic push
#pragma ide diagnostic ignored "hicpp-exception-baseclass"
#include "contract.h"
#include <algorithm>
#include <random>

using std::shuffle;

/**
 * Clears the contract by removing all disciplines.
 */
void contractStudii::stergeContract() {
    this->contract.clear();
    notify();
}

/**
 * Returns all disciplines currently in the contract.
 *
 * @return A constant reference to a vector containing all disciplines.
 */
const vector<Disciplina> &contractStudii::getAllContract() {
    return this->contract;
}

/**
 * Adds a random selection of disciplines to the contract.
 *
 * @param discipline A reference to the vector of available disciplines.
 * @param numarDiscipline The number of disciplines to be added randomly.
 */
void contractStudii::adaugaRandom(vector<Disciplina>& discipline, int numarDiscipline) {
    shuffle(discipline.begin(), discipline.end(), std::default_random_engine(std::random_device{}()));
    while(contract.size() < numarDiscipline && !discipline.empty()) {
        contract.push_back(discipline.back());
        discipline.pop_back();
    }
    notify();
}

/**
 * Adds a new discipline to the contract.
 *
 * @param disciplina The discipline to be added.
 * @throws RepoException If the discipline already exists in the contract.
 */
void contractStudii::adaugaDisciplinaContract(const Disciplina &disciplina) {
    for (auto& disc: this->getAllContract())
        if (disc.getDenumire() == disciplina.getDenumire())
            throw RepoException("ERROR: Disciplina exista deja...");

    this->contract.push_back(disciplina);
    notify();
}

/**
 * Removes a discipline from the contract by its name.
 *
 * @param denumire The name of the discipline to be removed.
 * @throws RepoException If the discipline is not found in the contract.
 */
void contractStudii::stergeDisciplinaDinContract(const string &denumire) {
    int i = 0;
    while (i < contract.size()) {
        if (contract.at(i).getDenumire() == denumire) {
            contract.erase(contract.begin() + i);
            notify();
            return;
        }
        i++;
    }

    throw RepoException("ERROR: Disciplina not found...");
}
