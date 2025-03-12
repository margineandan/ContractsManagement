#include "service.h"
#include <fstream>

/**
 * @brief Retrieves all Disciplina objects from the repository.
 *
 * This function calls the `getAll()` method from the repository to get all the `Disciplina` objects stored.
 *
 * @return vector<Disciplina> - A vector containing all `Disciplina` objects.
 */
vector<Disciplina>& ServiceDisciplina::getAll() noexcept {
    return this->repoDisciplina.getAll();
}

/**
 * @brief Adds a new Disciplina object to the repository.
 *
 * This function validates the new `Disciplina`'s data and then adds it to the repository. It also records the action
 * for potential undo operations.
 *
 * @param denumire The name of the discipline.
 * @param ore The number of hours for the discipline.
 * @param tip The type of the discipline.
 * @param cadruDidactic The instructor's name.
 */
void ServiceDisciplina::addDisciplina(const std::string &denumire, const int &ore, const std::string &tip,
                                      const std::string &cadruDidactic) {
    this->validatorDisciplina.validDisciplina(denumire, ore, tip, cadruDidactic);
    Disciplina disciplina = Disciplina{denumire, ore, tip, cadruDidactic};
    this->repoDisciplina.add(disciplina);
    undoActions.push_back(std::make_unique<undoAdd>(repoDisciplina, disciplina));
}

/**
 * @brief Searches for a Disciplina object in the repository.
 *
 * This function validates the provided data and searches for the discipline using its name and type.
 * If found, the discipline is returned.
 *
 * @param denumire The name of the discipline.
 * @param tip The type of the discipline.
 * @return const Disciplina& - A reference to the found Disciplina object.
 * @throws ServiceException If the discipline cannot be found.
 */
const Disciplina& ServiceDisciplina::searchDisciplina(const std::string &denumire, const std::string &tip) {
    this->validatorDisciplina.validDisciplina(denumire, 1, tip, "");
    const Disciplina& disciplina = this->repoDisciplina.search(denumire, tip);
    return disciplina;
}

/**
 * @brief Modifies an existing Disciplina object in the repository.
 *
 * This function validates the new data, removes the old `Disciplina`, adds the modified `Disciplina`, and records the
 * action for potential undo operations.
 *
 * @param denumire The name of the discipline to modify.
 * @param ore The new number of hours for the discipline.
 * @param tip The new type for the discipline.
 * @param cadruDidactic The new instructor's name.
 */
void ServiceDisciplina::modifyDisciplina(const std::string &denumire, const int &ore, const std::string &tip,
                                         const std::string &cadruDidactic) {
    this->validatorDisciplina.validDisciplina(denumire, ore, tip, cadruDidactic);
    Disciplina disciplina = repoDisciplina.search(denumire, tip);
    repoDisciplina.remove(disciplina);
    Disciplina newDisciplina = Disciplina{denumire, ore, tip, cadruDidactic};
    repoDisciplina.add(newDisciplina);
    undoActions.push_back(std::make_unique<undoModify>(repoDisciplina, newDisciplina, disciplina));
}

/**
 * @brief Removes a Disciplina object from the repository.
 *
 * This function validates the data and removes the `Disciplina` object from the repository. The action is recorded for
 * potential undo operations.
 *
 * @param denumire The name of the discipline to remove.
 * @param tip The type of the discipline to remove.
 */
void ServiceDisciplina::removeDisciplina(const std::string &denumire, const std::string &tip) {
    this->validatorDisciplina.validDisciplina(denumire, 1, tip, "");
    Disciplina disciplina = this->repoDisciplina.search(denumire, tip);
    this->repoDisciplina.remove(disciplina);
    undoActions.push_back(std::make_unique<undoRemove>(repoDisciplina, disciplina));
}

/**
 * @brief A generic filter function for Disciplina objects.
 *
 * This function allows for filtering the `Disciplina` objects based on a user-defined function.
 *
 * @param fnc A function that determines if a `Disciplina` matches the filter criteria.
 * @return vector<Disciplina> - A vector of `Disciplina` objects that match the filter.
 */
vector<Disciplina> ServiceDisciplina::filter(const function<bool(const Disciplina &)> &fnc) {
    vector<Disciplina> result;
    auto discipline = this->getAll();
    std::copy_if(discipline.begin(), discipline.end(), std::back_inserter(result), fnc);
    return result;
}

/**
 * @brief Sorts the Disciplina objects based on a user-defined comparison function.
 *
 * This function sorts the `Disciplina` objects using a custom sorting function. It implements a basic sorting algorithm
 * to arrange the disciplines.
 *
 * @param sortFnc A comparison function used to sort the `Disciplina` objects.
 * @return vector<Disciplina> - A sorted vector of `Disciplina` objects.
 */
vector<Disciplina> ServiceDisciplina::sortDiscipline(Sort sortFnc) {
    vector<Disciplina> discipline = repoDisciplina.getAll();
    vector<Disciplina> sorted;
    for (const auto & i : discipline)
        sorted.push_back(Disciplina(i));

    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        for (int i = 0; i < sorted.size() - 1; i++) {
            if (sortFnc(sorted.at(i), sorted.at(i + 1)) > 0) {
                Disciplina auxiliar = sorted.at(i);
                sorted.at(i) = sorted.at(i + 1);
                sorted.at(i + 1) = auxiliar;
                isSorted = false;
            }
        }
    }
    return sorted;
}

/**
 * @brief Filters Disciplina objects by the number of hours.
 *
 * This function filters the disciplines based on the number of hours.
 *
 * @param ore The maximum number of hours to filter disciplines by.
 * @return vector<Disciplina> - A vector of filtered `Disciplina` objects.
 */
vector<Disciplina> ServiceDisciplina::filterDisciplinaOre(const int &ore) {
    return filter([ore](const Disciplina& disciplina) { return disciplina.getOre() <= ore; });
}

/**
 * @brief Adds a discipline to the current contract.
 *
 * This function adds a `Disciplina` object to the current study contract by searching the discipline by its name and type.
 *
 * @param denumire The name of the discipline.
 * @param tip The type of the discipline.
 */
void ServiceDisciplina::addContract(const std::string &denumire, const std::string &tip) {
    const auto& disciplina = this->repoDisciplina.search(denumire, tip);
    contractCurent.adaugaDisciplinaContract(disciplina);
}

/**
 * @brief Adds a random number of disciplines to the current contract.
 *
 * This function adds a specified number of random disciplines to the current contract.
 *
 * @param numarDiscipline The number of random disciplines to add.
 * @return int - The number of disciplines in the contract after addition.
 */
int ServiceDisciplina::addRandom(int numarDiscipline) {
    contractCurent.adaugaRandom(this->getAll(), numarDiscipline);
    return contractCurent.getAllContract().size();
}

/**
 * @brief Retrieves all the disciplines in the current contract.
 *
 * @return const vector<Disciplina>& - A reference to the vector containing all disciplines in the current contract.
 */
const vector<Disciplina> &ServiceDisciplina::getAllContract() {
    return contractCurent.getAllContract();
}

/**
 * @brief Removes the current study contract.
 *
 * This function removes the entire contract, clearing all disciplines associated with it.
 */
void ServiceDisciplina::removeContract() {
    contractCurent.stergeContract();
}

/**
 * @brief Exports the current study contract to a file.
 *
 * This function exports the disciplines in the current contract to a file. It supports both CSV and HTML formats.
 *
 * @param filename The name of the file to export the contract data to.
 * @throws ServiceException If the file format is invalid or an error occurs during the file export.
 */
void ServiceDisciplina::exportContract(const string &filename) {
    if (filename.find(".csv") == std::string::npos && filename.find(".html") == std::string::npos)
        throw ServiceException("ERROR: Fisierul nu este valid... ");
    else {
        std::ofstream fout(filename);

        if (filename.find(".html") != std::string::npos) {
            fout << "<html>";
            fout << "<style> table, th, td {border:1px solid black} body{background-color: #E6E6FA;} </style>";
            fout << "<body>";
            fout << "<h1> DISCIPLINE </h1>";
            fout << "<table><tr><th>Denumire</th> <th>Ore</th> <th>Tip</th> <th>Cadru</th></tr>";
            for (auto &o: this->getAllContract()) {
                fout << "<tr><td>" << o.getDenumire() << "<td>" << o.getOre() << "</td><td>" << o.getTip()
                     << "</td><td>" << o.getCadru() << "</td></tr>";
            }
            fout << "</table></body>";
            fout << "<html>";
        } else {
            for (auto &o: this->getAllContract()) {
                fout << o.getDenumire() << ";" << o.getOre() << ";" << o.getTip()
                     << ";" << o.getCadru() << std::endl;
            }
        }
        fout.close();
    }
}

/**
 * @brief Generates a report for disciplines based on the instructor's name.
 *
 * This function creates a report that counts the number of disciplines for each instructor.
 *
 * @return unordered_map<string, int> - A map where the keys are the instructor names and the values are the counts of disciplines.
 */
unordered_map<string, int> ServiceDisciplina::raportDiscipline() {
    unordered_map<string, int> map;
    vector<Disciplina> discipline = this->getAll();
    for (const auto& disciplina: discipline) {
        if (map.find(disciplina.getCadru()) != map.end())
            map[disciplina.getCadru()]++;
        else
            map[disciplina.getCadru()] = 1;
    }

    return map;
}

/**
 * @brief Undoes the last operation.
 *
 * This function performs the undo operation for the last executed action. If no actions are available for undo,
 * an exception is thrown.
 *
 * @throws ServiceException If there are no actions available for undo.
 */
void ServiceDisciplina::undo() {
    if (undoActions.empty())
        throw ServiceException("ERROR: Nu se mai poate face undo...");
    undoActions.back()->doUndo();
    undoActions.pop_back();
}
