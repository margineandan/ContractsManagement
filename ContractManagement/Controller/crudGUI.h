#pragma once

#include "../Contract/contract.h"
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
#include <QListWidget>
#include <QStringList>
#include <QFont>

/**
 * @class contractGUIList
 * @brief Graphical User Interface (GUI) for displaying the contract disciplines using a QListWidget.
 * Implements the Observer pattern to update the list when the contract changes.
 */
class contractGUIList: public QWidget, public Observer {
private:
    contractStudii& contractStudii;  ///< Reference to the contractStudii model.
    QListWidget* listaContracte = new QListWidget;  ///< List widget to display contract disciplines.
    QVBoxLayout* layout = new QVBoxLayout;  ///< Main layout for the widget.

    /**
     * @brief Initializes the GUI components.
     */
    void initializeGUI() {
        this->setLayout(layout);
        layout->addWidget(listaContracte);
    }

    /**
     * @brief Connects observer signals to update the UI when data changes.
     */
    void connectSignalSlots() {
        contractStudii.addObserver(this);
    }

    /**
     * @brief Reloads the list with updated discipline data.
     * @param discipline The vector of disciplines to display.
     */
    void reloadData(const vector<Disciplina>& discipline) {
        listaContracte->clear();
        for(const auto& disciplina: discipline) {
            auto item = new QListWidgetItem(QString::fromStdString(
                    disciplina.getDenumire() + " " +
                    std::to_string(disciplina.getOre()) + " " +
                    disciplina.getTip() + " " +
                    disciplina.getCadru()
            ));
            listaContracte->addItem(item);
        }
    }

public:
    /**
     * @brief Constructor that initializes the GUI and connects the observer.
     * @param contractStudii Reference to the contract model.
     */
    explicit contractGUIList(class contractStudii& contractStudii) : contractStudii(contractStudii) {
        initializeGUI();
        connectSignalSlots();
        reloadData(this->contractStudii.getAllContract());
    };

    /**
     * @brief Observer update method, called when the contract data changes.
     */
    void update() override {
        reloadData(contractStudii.getAllContract());
    }

    /**
     * @brief Destructor that removes the observer from the contract.
     */
    ~contractGUIList() override {
        contractStudii.removeObserver(this);
    }
};
