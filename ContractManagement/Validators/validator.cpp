#include "validator.h"

/**
 * @brief Validates the `denumire` string for correctness.
 *
 * A valid `denumire` should only contain alphanumeric characters and spaces.
 * If any other character is found, the function returns `false`.
 *
 * @param denumire A string representing the name to be validated.
 * @return `true` if the name is valid (only alphanumeric characters and spaces), `false` otherwise.
 */
bool validDenumire(const string& denumire) {
    for (const auto& chr: denumire) {
        if (chr != ' ' && !isalnum(chr))
            return false;
    }

    return true;
}

/**
 * @brief Validates the `nume` string for correctness.
 *
 * A valid `nume` should only contain alphabetic characters and spaces.
 * If any other character is found, the function returns `false`.
 *
 * @param nume A string representing the name to be validated.
 * @return `true` if the name is valid (only alphabetic characters and spaces), `false` otherwise.
 */
bool validNume(const string& nume) {
    for (const auto& chr: nume) {
        if (chr != ' ' && !isalpha(chr))
            return false;
    }

    return true;
}

/**
 * @brief Validates if the `ore` (hours) value is greater than zero.
 *
 * The function returns `true` if the number of hours is greater than zero, and `false` otherwise.
 *
 * @param ore An integer representing the number of hours to be validated.
 * @return `true` if the number of hours is greater than zero, `false` otherwise.
 */
bool validOre(const int& ore) {
    return (ore > 0);
}

/**
 * @brief Validates the properties of a `Disciplina` object.
 *
 * This function checks the validity of the following attributes of a `Disciplina` object:
 * - `denumire`: The name must contain only alphanumeric characters and spaces.
 * - `ore`: The number of hours must be greater than zero.
 * - `tip`: The type must contain only alphabetic characters and spaces.
 * - `cadruDidactic`: The instructor's name must contain only alphabetic characters and spaces.
 *
 * If any validation fails, an exception is thrown with the corresponding error messages.
 *
 * @param denumire The name of the discipline.
 * @param ore The number of hours for the discipline.
 * @param tip The type of the discipline.
 * @param cadruDidactic The name of the instructor.
 * @throws ValidException If any validation fails, throws an exception with error messages.
 */
void Validator::validDisciplina(const std::string &denumire, const int &ore, const std::string &tip,
                                const std::string &cadruDidactic) {
    string errors;

    // Validate the discipline name.
    if (!validDenumire(denumire))
        errors.append("ERROR: denumire invalida...\n");

    // Validate the number of hours.
    if(!validOre(ore))
        errors.append("ERROR: ora invalida...\n");

    // Validate the discipline type.
    if (!validNume(tip))
        errors.append("ERROR: tip invalid...\n");

    // Validate the instructor's name.
    if (!validNume(cadruDidactic))
        errors.append("ERROR: cadru didactic invalid...\n");

    // If any validation failed, throw an exception with the error messages.
    if (!errors.empty())
        throw ValidException(errors);
}
