#include "errors.h"

/**
 * Constructor for Exception object.
 *
 * @param err(string) - error message of Exception object
 *
 * @return NULL
 */
Exception::Exception(const std::string &err) {
    this->message = err;
}

/**
 * Getter for message of Exception object.
 *
 * @return string
 */
string Exception::getMessage() const {
    return ("\n" + this->message);
}