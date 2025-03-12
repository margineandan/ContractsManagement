#pragma once

#include "../Repository/repository.h"
#include "../Validators/validator.h"
#include "../Contract/contract.h"
#include "../Utils/undo.h"
#include <unordered_map>
#include <functional>
#include <memory>

using std::function;
using std::vector;
using std::unordered_map;

typedef int(*Sort)(const Disciplina&, const Disciplina&);

/**
 * @class ServiceDisciplina
 * @brief Service class responsible for managing the business logic related to disciplines.
 *
 * This class serves as an intermediary between the user interface (or controller) and the data repository. It encapsulates
 * various operations such as adding, modifying, searching, removing disciplines, and managing contracts. Additionally, it
 * supports sorting, filtering, and undo operations.
 */
class ServiceDisciplina {
private:
    RepoAbstract& repoDisciplina;  ///< The repository used to store and manage disciplines.
    Validator& validatorDisciplina;  ///< Validator used for validating discipline data.
    contractStudii& contractCurent;  ///< The current study contract.

    vector<std::unique_ptr<ActiuneUndo>> undoActions;  ///< A collection of undo actions to support the undo functionality.

    /**
     * @brief Filters disciplines based on a user-defined predicate.
     * @param fnc The function that defines the filter criterion.
     * @return A vector of disciplines that match the filter condition.
     */
    vector<Disciplina> filter(const function<bool(const Disciplina&)>& fnc);

public:
    /**
     * @brief Constructor for the ServiceDisciplina class.
     * @param repoDisciplina The repository object for storing and managing disciplines.
     * @param validatorDisciplina The validator object for validating discipline data.
     * @param contractStudii The contract object for managing the study contract.
     */
    explicit ServiceDisciplina(RepoAbstract& repoDisciplina, Validator& validatorDisciplina, contractStudii& contractStudii):
            repoDisciplina(repoDisciplina), validatorDisciplina(validatorDisciplina), contractCurent(contractStudii) {}

    /**
     * @brief Retrieves all the disciplines in the repository.
     * @return A vector containing all disciplines.
     */
    vector<Disciplina>& getAll() noexcept;

    /**
     * @brief Adds a new discipline to the repository.
     * @param denumire The name of the discipline.
     * @param ore The number of hours for the discipline.
     * @param tip The type of the discipline.
     * @param cadruDidactic The name of the instructor for the discipline.
     */
    void addDisciplina(const string& denumire, const int& ore, const string& tip, const string& cadruDidactic);

    /**
     * @brief Searches for a discipline in the repository by name and type.
     * @param denumire The name of the discipline.
     * @param tip The type of the discipline.
     * @return A reference to the found discipline.
     * @throws ServiceException If the discipline is not found.
     */
    const Disciplina& searchDisciplina(const string& denumire, const string& tip);

    /**
     * @brief Modifies an existing discipline in the repository.
     * @param denumire The name of the discipline to modify.
     * @param ore The new number of hours for the discipline.
     * @param tip The new type of the discipline.
     * @param cadruDidactic The new instructor for the discipline.
     */
    void modifyDisciplina(const string& denumire, const int& ore, const string& tip, const string& cadruDidactic);

    /**
     * @brief Removes a discipline from the repository.
     * @param denumire The name of the discipline to remove.
     * @param tip The type of the discipline to remove.
     */
    void removeDisciplina(const string& denumire, const string& tip);

    /**
     * @brief Filters disciplines based on the number of hours.
     * @param ore The number of hours to filter by.
     * @return A vector containing the disciplines that match the filtering criterion.
     */
    vector<Disciplina> filterDisciplinaOre(const int& ore);

    /**
     * @brief Sorts the disciplines based on the provided sorting function.
     * @param sortFnc The sorting function to use for ordering the disciplines.
     * @return A vector of sorted disciplines.
     */
    vector<Disciplina> sortDiscipline(Sort sortFnc);

    /**
     * @brief Adds a contract to the current study contract.
     * @param denumire The name of the discipline.
     * @param destinatie The destination or related details of the contract.
     */
    void addContract(const string& denumire, const string& destinatie);

    /**
     * @brief Adds a number of random disciplines to the contract.
     * @param numarDiscipline The number of disciplines to add randomly.
     * @return The number of disciplines added.
     */
    int addRandom(int numarDiscipline);

    /**
     * @brief Retrieves all disciplines associated with the current contract.
     * @return A vector of disciplines in the contract.
     */
    const vector<Disciplina>& getAllContract();

    /**
     * @brief Removes the current contract.
     */
    void removeContract();

    /**
     * @brief Exports the current contract data to a file.
     * @param filename The name of the file where the contract data will be exported.
     */
    void exportContract(const string& filename);

    /**
     * @brief Generates a report on disciplines.
     * @return A map containing the disciplines and their respective counts.
     */
    unordered_map<string, int> raportDiscipline();

    /**
     * @brief Undoes the last action performed.
     */
    void undo();

    /**
     * @brief Retrieves the current study contract.
     * @return A reference to the current contract.
     */
    contractStudii& getContract() {
        return contractCurent;
    }
};

/**
 * @class ServiceException
 * @brief Exception class for errors that occur during service operations.
 *
 * This class extends the base `Exception` class and is used to handle errors specific to the service layer
 * of the application, such as invalid data or failed operations.
 */
class ServiceException: public Exception {
public:
    /**
     * @brief Constructor for the ServiceException class.
     * @param err The error message to be thrown.
     */
    explicit ServiceException(const string& err) : Exception(err) {}
};
