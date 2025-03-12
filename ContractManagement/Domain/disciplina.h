#pragma once
#include <string>
#include <iostream>

using std::string;
using std::cout;

/**
 * Class representing a Disciplina (Discipline) object.
 */
class Disciplina {
private:
    string Denumire; /**< Name of the discipline. */
    int Ore{}; /**< Number of hours allocated to the discipline. */
    string Tip; /**< Type of discipline. */
    string Cadru; /**< Assigned teaching staff. */

public:
    /**
     * Default constructor for Disciplina object.
     *
     * @return NULL
     */
    Disciplina() = default;

    /**
     * Constructor for Disciplina object.
     *
     * @param Denumire (string) - Name of the discipline.
     * @param Ore (int) - Number of hours allocated to the discipline.
     * @param Tip (string) - Type of discipline.
     * @param Cadru (string) - Assigned teaching staff.
     *
     * @return NULL
     */
    Disciplina(const string& Denumire, const int& Ore, const string& Tip, const string& Cadru);

    /**
     * Copy constructor for Disciplina object.
     *
     * @param disciplina (Disciplina) - Discipline object to copy.
     *
     * @return NULL
     */
    Disciplina(const Disciplina& disciplina) = default;

    /**
     * Getter for Denumire (discipline name).
     *
     * @return string - Name of the discipline.
     */
    [[nodiscard]] string getDenumire() const;

    /**
     * Getter for Ore (hours allocated).
     *
     * @return int - Number of hours allocated to the discipline.
     */
    [[nodiscard]] int getOre() const;

    /**
     * Getter for Tip (type of discipline).
     *
     * @return string - Type of discipline.
     */
    [[nodiscard]] string getTip() const;

    /**
     * Getter for Cadru (assigned teaching staff).
     *
     * @return string - Assigned teaching staff.
     */
    [[nodiscard]] string getCadru() const;

    /**
     * Setter for Denumire (discipline name).
     *
     * @param newDenumire (string) - New name of the discipline.
     *
     * @return NULL
     */
    void setDenumire(const string& newDenumire);

    /**
     * Setter for Ore (hours allocated).
     *
     * @param newOre (int) - New number of hours allocated to the discipline.
     *
     * @return NULL
     */
    void setOre(const int& newOre);

    /**
     * Setter for Tip (type of discipline).
     *
     * @param newTip (string) - New type of discipline.
     *
     * @return NULL
     */
    void setTip(const string& newTip);

    /**
     * Setter for Cadru (assigned teaching staff).
     *
     * @param newCadru (string) - New assigned teaching staff.
     *
     * @return NULL
     */
    void setCadru(const string& newCadru);

    /**
     * Creates a copy of a given Disciplina object.
     *
     * @param disciplina (Disciplina) - The discipline object to copy.
     *
     * @return Disciplina - A new discipline object with the same attributes.
     */
    static Disciplina copyDisciplina(const Disciplina& disciplina);

    /**
     * Generates a string representation of the Disciplina object.
     *
     * @return string - Formatted string representation of the discipline object.
     */
    string displayDisciplina();
};