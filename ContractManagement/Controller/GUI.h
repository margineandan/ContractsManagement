#pragma once
#include "../Service/service.h"
#include "crudGUI.h"
#include "readonlyGUI.h"
#include "model.h"

#include <vector>
#include <string>
#include <QApplication>
#include <QWidget>
#include <QBoxLayout>
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QRadioButton>
#include <qlistwidget.h>
#include <QStringList>
#include <QTableView>
#include <QFont>
#include <QStandardItemModel>

using std::vector;
using std::string;

/**
 * @class ContracteGUI
 * @brief A graphical user interface (GUI) for managing and interacting with contract data and discipline information.
 *
 * This class provides a user interface for adding, removing, and modifying contract data and discipline information.
 * It allows for filtering, sorting, and displaying contract and discipline data in both table and list formats.
 * The interface interacts with the `ServiceDisciplina` service to perform actions on the data, such as CRUD operations
 * (Create, Read, Update, Delete) and filtering/sorting operations.
 */
class ContracteGUI: public QWidget {
private:
    ServiceDisciplina& serviceGUI;  ///< A reference to the ServiceDisciplina, which handles the data.

    // MAIN
    QLabel* labelDenumire = new QLabel{"Denumirea disciplinei:"};
    QLabel* labelOre = new QLabel{"Ore disciplina:"};
    QLabel* labelTip = new QLabel{"Tipul disciplinei"};
    QLabel* labelCadruDidactic = new QLabel{"Cadrul didactic al disciplinei:"};

    QLineEdit* editDenumire{};  ///< Input field for the discipline's name.
    QLineEdit* editOre{};  ///< Input field for the discipline's number of hours.
    QLineEdit* editTip{};  ///< Input field for the discipline's type.
    QLineEdit* editCadruDidactic{};  ///< Input field for the discipline's teacher.

    QPushButton* btnAddDisciplina{};  ///< Button to add a new discipline.
    QPushButton* btnRemoveDisciplina{};  ///< Button to remove a discipline.
    QPushButton* btnModifyDisciplina{};  ///< Button to modify an existing discipline.

    QGroupBox* groupBox = new QGroupBox("TIP SORTARE");  ///< Group box for sorting options.

    QRadioButton* radioSortDenumire = new QRadioButton(QString::fromStdString("Denumire"));  ///< Radio button for sorting by name.
    QRadioButton* radioSortOre = new QRadioButton(QString::fromStdString("Ore"));  ///< Radio button for sorting by hours.
    QRadioButton* radioSortTip = new QRadioButton(QString::fromStdString("Tip"));  ///< Radio button for sorting by type.
    QPushButton* btnSortDiscipline{};  ///< Button to sort the disciplines.

    QGroupBox* groupBoxFilter = new QGroupBox("TIP FILTRARE");  ///< Group box for filtering options.

    QRadioButton* radioFilterDenumire = new QRadioButton(QString::fromStdString("Denumire"));  ///< Radio button for filtering by name.
    QRadioButton* radioFilterOre = new QRadioButton(QString::fromStdString("Ore"));  ///< Radio button for filtering by hours.
    QRadioButton* radioFilterTip = new QRadioButton(QString::fromStdString("Tip"));  ///< Radio button for filtering by type.
    QPushButton* btnFilterDiscipline{};  ///< Button to filter the disciplines.

    QPushButton* btnreloadData{};  ///< Button to reload the discipline data.
    QPushButton* btnUndo{};  ///< Button to undo the last action.

    // TABEL
    MyTableModel* model = new MyTableModel(serviceGUI.getAll());  ///< Model for displaying the disciplines in a table format.
    QTableView* tabelDiscipline = new QTableView;  ///< Table view widget to display the disciplines.

    // LISTA
    QListWidget* listaDiscipline{};  ///< List widget to display the disciplines in a list format.
    QPushButton* btnContracte{};  ///< Button to navigate to the contract view.

    // CONTRACTE
    QPushButton* addContract{};  ///< Button to add a new contract.
    QPushButton* removeContract{};  ///< Button to remove an existing contract.
    QPushButton* addRandom{};  ///< Button to add random contracts.
    QPushButton* exportContracte{};  ///< Button to export contracts.

    QLineEdit* editDenumireContract{};  ///< Input field for the contract's name.
    QLineEdit* editTipContract{};  ///< Input field for the contract's type.
    QLineEdit* editNumarRandom{};  ///< Input field for the number of random contracts to add.
    QLineEdit* editExportContracte{};  ///< Input field for the file name to export contracts.

    QListWidget* listaContracte{};  ///< List widget to display the contracts.

    QLabel* labelRandom = new QLabel{"Numar discipline random de adaugat:"};  ///< Label for the number of random disciplines to add.
    QLabel* labelExport = new QLabel{"Numele fisierului pentru exportare:"};  ///< Label for the file name for export.

    QPushButton* butonCrudGUI = new QPushButton{"Contract Crud"};  ///< Button to navigate to the CRUD contract view.
    QPushButton* butonReadOnlyGUI = new QPushButton{"Contract Read Only"};  ///< Button to navigate to the read-only contract view.

    // BUTOANE DINAMICE
    QVBoxLayout* dynamicButtons = new QVBoxLayout;  ///< Layout for dynamically added buttons.

    /**
     * @brief Initializes the GUI components and arranges them within the layout.
     */
    void initializeGUI();

    /**
     * @brief Connects signals and slots to handle user interactions.
     */
    void connectSignalSlots();

    /**
     * @brief Reloads the list widget with updated discipline data.
     * @param discipline The updated vector of discipline data.
     */
    void reloadList(const vector<Disciplina>& discipline);

    /**
     * @brief Reloads the list widget with updated contract data.
     * @param contracte The updated vector of contract data.
     */
    void reloadContracte(const vector<Disciplina>& contracte);

    /**
     * @brief Initializes the dynamic buttons based on the discipline report.
     * Creates a button for each discipline type and connects it to display the count.
     */
    void initDynamicButtons() {
        QLayoutItem* item;
        while((item = dynamicButtons->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        unordered_map<string, int> discipline = serviceGUI.raportDiscipline();
        for(auto& materie: discipline) {
            auto btn = new QPushButton(QString::fromStdString(materie.first));
            dynamicButtons->addWidget(btn);
            QObject::connect(btn, &QPushButton::clicked, [materie](){
                QMessageBox::information(nullptr, "INFO", QString::number(materie.second));
            });
        }
    }

public:
    /**
     * @brief Constructor that initializes the ContracteGUI and connects it to the `ServiceDisciplina`.
     * @param serviceDisciplina A reference to the `ServiceDisciplina` service that provides the contract and discipline data.
     */
    explicit ContracteGUI(ServiceDisciplina& serviceDisciplina) : serviceGUI{serviceDisciplina} {
        initializeGUI();
        connectSignalSlots();
        reloadList(serviceGUI.getAll());
    }

    /**
     * @brief Adds a new discipline using data from the input fields.
     */
    void GUIaddDisciplina();

    /**
     * @brief Removes an existing discipline.
     */
    void GUIremoveDisciplina();

    /**
     * @brief Modifies an existing discipline using data from the input fields.
     */
    void GUImodifyDisciplina();
};
