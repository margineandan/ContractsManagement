#pragma once
#include <string>

using std::string;

/**
 * Class definition for Exception object.
 *
 * @arg message(string) - error message of Exception object.
 */
class Exception {
private:
    string message;

public:
    /**
     * Constructor for Exception object.
     *
     * @param err(string): error message of Exception object.
     *
     * @return NULL
     */
    explicit Exception(const string& err);

    /**
     * Getter for message of Exception object.
     *
     * @return string
     */
    [[nodiscard]] string getMessage() const;
};