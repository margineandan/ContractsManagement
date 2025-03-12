#pragma once

#include "../Domain/disciplina.h"
#include "../Repository/repository.h"
#include "../Service/service.h"
#include "../Exceptions/errors.h"

#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::string;
using std::endl;

/**
 * Console class for user interaction.
 */
class Console {
private:
    ServiceDisciplina& serviceDisciplina;

    /**
     * Exits the program.
     */
    static void exitUI();

    /**
     * Displays all existing Disciplina objects.
     *
     * @param discipline (vector<Disciplina>) - List of disciplines to display.
     */
    void displayUI(const vector<Disciplina> &discipline);

    /**
     * Adds a new Disciplina object.
     */
    void addUI();

    /**
     * Removes an existing Disciplina object.
     */
    void removeUI();

    /**
     * Searches for a Disciplina object.
     */
    void searchUI();

    /**
     * Modifies an existing Disciplina object.
     */
    void modifyUI();

    /**
     * Filters Disciplina objects based on criteria.
     */
    void filterUI();

    /**
     * Sorts Disciplina objects.
     */
    void sortUI();

    /**
     * Adds a Disciplina object to the contract.
     */
    void addContractUI();

    /**
     * Adds random Disciplina objects to the contract.
     */
    void addRandomUI();

    /**
     * Removes all Disciplina objects from the contract.
     */
    void removeContractUI();

    /**
     * Exports Disciplina objects to a file.
     */
    void exportUI();

    /**
     * Opens the contract management menu.
     */
    void meniuContract();

    /**
     * Generates a report on Disciplina objects.
     */
    void raportUI();

    /**
     * Performs an undo operation.
     */
    void undoUI();

public:
    /**
     * Constructor for Console class.
     *
     * @param serviceDisciplina (ServiceDisciplina&) - Reference to service layer.
     */
    explicit Console(ServiceDisciplina& serviceDisciplina): serviceDisciplina{serviceDisciplina} {}

    /**
     * Runs the main program loop.
     */
    void run();
};

/**
 * UIException class for handling UI-related errors.
 */
class UIException: public Exception{
public:
    /**
     * Constructor for UIException class.
     *
     * @param err (string) - Error message.
     */
    explicit UIException(const string& err) : Exception(err) {}
};
