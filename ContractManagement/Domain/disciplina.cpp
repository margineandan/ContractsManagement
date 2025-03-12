#include "disciplina.h"

/**
 * Constructor for Movie object.
 *
 * @param Denumire(string)
 * @param Ore(int)
 * @param Tip(string)
 * @param Cadru(string)
 *
 * @return NULL
 */
Disciplina::Disciplina(const string& Denumire, const int& Ore, const string& Tip, const string& Cadru) {
    this->Denumire = Denumire;
    this->Ore = Ore;
    this->Tip = Tip;
    this->Cadru = Cadru;
}

/**
 * Getter for Denumire for Disciplina object.
 *
 * @return string
 */
string Disciplina::getDenumire() const {
    return this->Denumire;
}

/**
 * Getter for Ore for Disciplina object.
 *
 * @return int
 */
int Disciplina::getOre() const {
    return this->Ore;
}

/**
 * Getter for Tip for Disciplina object.
 *
 * @return string
 */
string Disciplina::getTip() const {
    return this->Tip;
}

/**
 * Getter for Cadrufor Disciplina object.
 *
 * @return string
 */
string Disciplina::getCadru() const {
    return this->Cadru;
}

/**
 * Setter for Denumire of Denumire object.
 *
 * @param newDenumire(string) - new title of Denumire object
 *
 * @return NULL
 */
void Disciplina::setDenumire(const std::string &newDenumire) {
    this->Denumire = newDenumire;
}

/**
 * Setter for Ore of Denumire object.
 *
 * @param newOre(int) - new title of Denumire object
 *
 * @return NULL
 */
void Disciplina::setOre(const int &newOre) {
    this->Ore = newOre;
}

/**
 * Setter for Tip of Denumire object.
 *
 * @param newTip(string) - new title of Denumire object
 *
 * @return NULL
 */
void Disciplina::setTip(const std::string &newTip) {
    this->Tip = newTip;
}

/**
 * Setter for Cadru of Denumire object.
 *
 * @param newCadru(string) - new title of Denumire object
 *
 * @return NULL
 */
void Disciplina::setCadru(const std::string &newCadru) {
    this->Cadru = newCadru;
}

/**
 * Copy Disciplina object.
 *
 * @return Movie
 */
Disciplina Disciplina::copyDisciplina(const Disciplina &disciplina) {
    return Disciplina{disciplina.getDenumire(), disciplina.getOre(), disciplina.getTip(), disciplina.getCadru()};
}

/**
 * String representation of Disciplina object.
 *
 * @return string
 */
string Disciplina::displayDisciplina() {
    string displayMessage = "<DENUMIRE> " + this->Denumire + " <ORE> " + std::to_string(this->Ore) +
            " <TIP> "  + this->Tip + " <CADRU DIDACTIC> " + this->Cadru;

    return displayMessage;
}