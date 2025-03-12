#include "ui.h"
#include <cstring>

void clearScreen() {
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
}

/**
 * Exit program.
 */
void Console::exitUI() {
    clearScreen();
    cout << "Program finalizat cu succes.\n";
    exit(EXIT_SUCCESS);
}

/**
 * Display existing Disciplina objects.
 */
void Console::displayUI(const vector<Disciplina> &discipline) {
    if (discipline.empty()) {
        cout << "Nu sunt discipline...\n";
        return;
    }

    cout << "DISCIPLINE DISPONIBILE\n\n";
    for (Disciplina disciplina: discipline)
        cout << disciplina.displayDisciplina() << endl;
}

/**
 * Add new Disciplina object.
 */
void Console::addUI() {
    cout << "ADAUGA DISCIPLINA\n\n";

    string denumire, ore, tip, cadruDidactic;
    cout << "Denumirea disciplinei: ";
    getline(cin >> std::ws, denumire);
    cout << "Ore pe saptamana: ";
    getline(cin >> std::ws, ore);
    cout << "Tipul disciplinei: ";
    getline(cin >> std::ws, tip);
    cout << "Cadrul didactic al disciplinei: ";
    getline(cin >> std::ws, cadruDidactic);

    try {
        int ora = stoi(ore);
        this->serviceDisciplina.addDisciplina(denumire, ora, tip, cadruDidactic);
        cout << "\nSUCCESS: disciplina adaugata cu succes!\n";
    } catch (const std::invalid_argument& err) {
        cout << "ERROR: 'ore' trebuie sa fie un numar intreg pozitiv...\n";
    } catch (UIException& exception) {
        cout << exception.getMessage();
    }
}

/**
 * Search Disciplina object.
 */
void Console::searchUI() {
    cout << "CAUTARE DISCIPLINA\n\n";

    string denumire, tip;
    cout << "Denumirea disciplinei: ";
    getline(cin >> std::ws, denumire);
    cout << "Tipul disciplinei: ";
    getline(cin >> std::ws, tip);

    try {
        Disciplina disciplina = this->serviceDisciplina.searchDisciplina(denumire, tip);
        cout << endl << disciplina.displayDisciplina() << endl;
    } catch (UIException& exception) {
        cout << exception.getMessage();
    }
}

/**
 * Modify existing Disciplina object.
 */
void Console::modifyUI() {
    cout << "MODIFICA DISCIPLINA\n\n";

    string denumire, ore, tip, cadruDidactic;
    cout << "Denumirea disciplinei: ";
    getline(cin >> std::ws, denumire);
    cout << "Ore pe saptamana: ";
    getline(cin >> std::ws, ore);
    cout << "Tipul disciplinei: ";
    getline(cin >> std::ws, tip);
    cout << "Cadrul didactic al disciplinei: ";
    getline(cin >> std::ws, cadruDidactic);

    try {
        int ora = stoi(ore);
        this->serviceDisciplina.modifyDisciplina(denumire, ora, tip, cadruDidactic);
        cout << "\nSUCCESS: disciplina modificata cu succes!\n";
    } catch (const std::invalid_argument& err) {
        cout << "ERROR: 'ore' trebuie sa fie un numar intreg pozitiv...\n";
    } catch (UIException& exception) {
        cout << exception.getMessage();
    }
}

/**
 * Remove existing Disciplina object.
 */
void Console::removeUI() {
    cout << "ELIMINA DISCIPLINA\n\n";

    string denumire, tip;
    cout << "Denumirea disciplinei: ";
    getline(cin >> std::ws, denumire);
    cout << "Tipul disciplinei: ";
    getline(cin >> std::ws, tip);

    try {
        this->serviceDisciplina.removeDisciplina(denumire, tip);
        cout << "\nSUCCESS: disciplina eliminata cu succes!\n";
    } catch (UIException& exception) {
        cout << exception.getMessage();
    }
}

/**
 * Run program function for Console object.
 */
void Console::run() {
    while (true) {
        cout << "MENIU DISCIPLINE\n\n";
        cout << "[0] Exit program\n";
        cout << "[1] Afisare discipline\n";
        cout << "[2] Adauga disciplina\n";
        cout << "[3] Cautare disciplina\n";
        cout << "[4] Modificare disciplina\n";
        cout << "[5] Stergere disciplina\n";

        string command;
        cout << "---------------------------------------------------------------------------------------------------" << endl;
        cout << "Choose option: ";
        cin >> command;

        try {
            int option = stoi(command);
            switch (option) {
                case 0:
                    exitUI();
                    break;
                case 1:
                    displayUI(serviceDisciplina.getAll());
                    break;
                case 2:
                    addUI();
                    break;
                case 3:
                    searchUI();
                    break;
                case 4:
                    modifyUI();
                    break;
                case 5:
                    removeUI();
                    break;
                default:
                    cout << "ERROR: comanda invalida...\n";
                    break;
            }
        } catch (const std::invalid_argument& err) {
            cout << "ERROR: comanda invalida...\n";
        } catch (const Exception& err) {
            cout << err.getMessage() << endl;
        }
    }
}
