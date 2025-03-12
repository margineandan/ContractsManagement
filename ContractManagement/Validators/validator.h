#pragma once

#include "../Domain/disciplina.h"
#include "../Exceptions/errors.h"

#include <string>

using std::string;

/**
 * @class Validator
 * @brief A class responsible for validating the properties of a Disciplina object.
 *
 * The Validator class ensures that the `Disciplina` object has valid data before it is added or modified in the repository.
 */
class Validator {
public:
    /**
     * @brief Validates the properties of a Disciplina object.
     *
     * This method checks the validity of the following attributes of a Disciplina object:
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
    void validDisciplina(const string& denumire, const int& ore, const string& tip,
                         const string& cadruDidactic);
};

/**
 * @class ValidException
 * @brief A custom exception class for handling validation errors.
 *
 * This class is thrown when validation fails in the Validator class, providing error messages to inform the user about the specific issues.
 */
class ValidException: public Exception {
public:
    /**
     * @brief Constructor for the ValidException class.
     *
     * Initializes the exception with a specific error message.
     *
     * @param err The error message explaining the validation failure.
     */
    explicit ValidException(const string& err) : Exception(err) {}
};
