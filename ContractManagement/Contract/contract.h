#pragma once
#include "../Domain/disciplina.h"
#include "../Repository/repository.h"
#include "../Utils/observer.h"
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using std::vector;

/**
 * @class contractStudii
 * @brief Manages a contract of disciplines, allowing additions, removals, and notifications to observers.
 */
class contractStudii: public Observable {
private:
    vector<Disciplina> contract;  ///< Vector storing the disciplines in the contract.
    RepoDisciplina& repoDisciplina;  ///< Reference to the discipline repository.

public:
    /**
     * @brief Constructor for contractStudii.
     * @param repoDisciplina Reference to the repository of disciplines.
     */
    explicit contractStudii(RepoDisciplina& repoDisciplina): repoDisciplina(repoDisciplina) {};

    /**
     * @brief Adds a discipline to the contract.
     * @param disciplina The discipline to be added.
     * @throws RepoException If the discipline already exists in the contract.
     */
    void adaugaDisciplinaContract(const Disciplina& disciplina);

    /**
     * @brief Adds a random selection of disciplines to the contract.
     * @param discipline A reference to the list of available disciplines.
     * @param numarDiscipline The number of disciplines to add randomly.
     */
    void adaugaRandom(vector<Disciplina>& discipline, int numarDiscipline);

    /**
     * @brief Retrieves all disciplines currently in the contract.
     * @return A constant reference to the vector of disciplines.
     */
    const vector<Disciplina>& getAllContract();

    /**
     * @brief Removes all disciplines from the contract.
     */
    void stergeContract();

    /**
     * @brief Removes a discipline from the contract by its name.
     * @param denumire The name of the discipline to remove.
     * @throws RepoException If the discipline is not found in the contract.
     */
    void stergeDisciplinaDinContract(const string& denumire);
};
