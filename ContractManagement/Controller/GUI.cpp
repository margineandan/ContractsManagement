#include "GUI.h"

int sortDenumireGUI(const Disciplina& disciplina1, const Disciplina& disciplina2) {
    return disciplina1.getDenumire().compare(disciplina2.getDenumire());
}

int sortTipGUI(const Disciplina& disciplina1, const Disciplina& disciplina2) {
    return disciplina1.getTip().compare(disciplina2.getTip());
}

int sortOreGUI(const Disciplina& disciplina1, const Disciplina& disciplina2) {
    return disciplina1.getOre() > disciplina2.getOre();
}

void ContracteGUI::initializeGUI() {

    // MAIN
    auto lyMain = new QHBoxLayout;
    this->setLayout(lyMain);

    // LEFT SIDE
    auto leftSide = new QWidget;
    auto lyLeftSide = new QVBoxLayout;
    leftSide->setLayout(lyLeftSide);

    auto form = new QWidget;
    auto lyForm = new QFormLayout;
    form->setLayout(lyForm);

    editDenumire = new QLineEdit;
    editOre = new QLineEdit;
    editTip = new QLineEdit;
    editCadruDidactic = new QLineEdit;

    lyForm->addRow(labelDenumire, editDenumire);
    lyForm->addRow(labelOre, editOre);
    lyForm->addRow(labelTip, editTip);
    lyForm->addRow(labelCadruDidactic, editCadruDidactic);

    btnAddDisciplina = new QPushButton("Adauga disciplina");
    btnRemoveDisciplina = new QPushButton("Sterge disciplina");
    btnModifyDisciplina = new QPushButton("Modifica disciplina");

    auto buttons = new QWidget;
    auto lyButtons = new QHBoxLayout;
    buttons->setLayout(lyButtons);

    lyButtons->addWidget(btnAddDisciplina);
    lyButtons->addWidget(btnRemoveDisciplina);
    lyButtons->addWidget(btnModifyDisciplina);

    lyLeftSide->addWidget(form);
    lyLeftSide->addWidget(buttons);

    auto lyRadioBox = new QHBoxLayout;
    groupBox->setLayout(lyRadioBox);

    lyRadioBox->addWidget(radioSortDenumire);
    lyRadioBox->addWidget(radioSortOre);
    lyRadioBox->addWidget(radioSortTip);

    btnSortDiscipline = new QPushButton("Sorteaza discipline");
    lyRadioBox->addWidget(btnSortDiscipline);

    auto lyRadioBoxFilter = new QHBoxLayout;
    groupBoxFilter->setLayout(lyRadioBoxFilter);

    lyRadioBoxFilter->addWidget(radioFilterDenumire);
    lyRadioBoxFilter->addWidget(radioFilterOre);
    lyRadioBoxFilter->addWidget(radioFilterTip);

    btnFilterDiscipline = new QPushButton("Filtreaza discipline");
    lyRadioBoxFilter->addWidget(btnFilterDiscipline);

    lyLeftSide->addSpacing(50);
    lyLeftSide->addWidget(groupBox);
    lyLeftSide->addWidget(groupBoxFilter);

    btnreloadData = new QPushButton("Reload data");
    btnUndo = new QPushButton("Undo");
    lyLeftSide->addWidget(btnreloadData);
    lyLeftSide->addWidget(btnUndo);

    btnContracte = new QPushButton("Meniu Contracte");
    addContract = new QPushButton("Adauga in contract");
    removeContract = new QPushButton("Sterge contract");
    addRandom = new QPushButton("Adauga random in contract");
    exportContracte = new QPushButton("Exporta contracte");

    editDenumireContract = new QLineEdit;
    editTipContract = new QLineEdit;
    editNumarRandom = new QLineEdit;
    editExportContracte = new QLineEdit;

    listaContracte = new QListWidget;
    listaDiscipline = new QListWidget;

    // RIGHT SIDE
    auto rightSide = new QWidget;
    auto lyRightSide = new QVBoxLayout;
    rightSide->setLayout(lyRightSide);

//    int nrLinii = 15;
//    int nrColoane = 4;
//    tabelDiscipline = new QTableWidget{nrLinii, nrColoane};


    tabelDiscipline->setModel(model);


    QStringList tblHeaderList;
    tblHeaderList << "DENUMIRE" << "ORE" << "TIP" << "CADRU DIDACTIC";
//  tabelDiscipline->setHorizontalHeaderLabels(tblHeaderList);
    tabelDiscipline->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    tabelDiscipline->horizontalHeader()->setSectionsMovable(true);


    //lyRightSide->addWidget(listaDiscipline);
    lyRightSide->addWidget(tabelDiscipline);
    lyRightSide->addSpacing(50);
    lyRightSide->addWidget(btnContracte);
    lyMain->addWidget(leftSide);
    lyMain->addWidget(rightSide);
    lyMain->addLayout(dynamicButtons);
}

void ContracteGUI::connectSignalSlots() {
    QObject::connect(btnAddDisciplina, &QPushButton::clicked, this, &ContracteGUI::GUIaddDisciplina);
    QObject::connect(btnRemoveDisciplina, &QPushButton::clicked, this, &ContracteGUI::GUIremoveDisciplina);
    QObject::connect(btnModifyDisciplina, &QPushButton::clicked, this, &ContracteGUI::GUImodifyDisciplina);

    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try {
            this->serviceGUI.undo();
            this->reloadList(this->serviceGUI.getAll());
            QMessageBox::information(this, "INFO", QString::fromStdString("Undo realizat cu succes."));
        } catch (Exception& exception) {
            QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(btnSortDiscipline, &QPushButton::clicked, [&]() {
        try {
            if (radioSortDenumire->isChecked())
                this->reloadList(serviceGUI.sortDiscipline(sortDenumireGUI));
            else if (radioSortOre->isChecked())
                this->reloadList(serviceGUI.sortDiscipline(sortOreGUI));
            else if (radioSortTip->isChecked())
                this->reloadList(serviceGUI.sortDiscipline(sortTipGUI));
        } catch (Exception& exception) {
            QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(btnFilterDiscipline, &QPushButton::clicked, [&]() {
        try {
            int ore = editOre->text().toInt();
            editOre->clear();
            this->reloadList(serviceGUI.filterDisciplinaOre(ore));
            QMessageBox::information(this, "INFO", QString::fromStdString("Filtrare realizata cu succes."));
        } catch (Exception& exception) {
            QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(btnreloadData, &QPushButton::clicked, [&]() {
       this->reloadList(serviceGUI.getAll());
        QMessageBox::information(this, "INFO", QString::fromStdString("Date recuperate cu succes."));
    });

    QObject::connect(btnContracte, &QPushButton::clicked, [&]() {
       auto fereastraContracte = new QWidget;
       auto lyFereastraContracte = new QVBoxLayout;
       fereastraContracte->setLayout(lyFereastraContracte);

        auto fereastraContracteMain = new QWidget;
        auto lyFereastraContracteMain = new QHBoxLayout;
        fereastraContracteMain->setLayout(lyFereastraContracteMain);

       auto button1 = new QWidget;
       auto lyButton1 = new QHBoxLayout;
       button1->setLayout(lyButton1);
       lyButton1->addWidget(addRandom);
       lyButton1->setAlignment(Qt::AlignHCenter);

        auto button2 = new QWidget;
        auto lyButton2 = new QHBoxLayout;
        button2->setLayout(lyButton2);
        lyButton2->addWidget(exportContracte);
        lyButton2->setAlignment(Qt::AlignHCenter);

        auto up1 = new QWidget;
        auto lyUp1 = new QFormLayout;
        up1->setLayout(lyUp1);
        lyUp1->addRow("Denumire disciplina: ", editDenumireContract);
        lyUp1->addRow("Tipul disciplinei: ", editTipContract);

       auto up = new QWidget;
       auto lyUp = new QHBoxLayout;
       up->setLayout(lyUp);
       lyUp->addWidget(addContract);
       lyUp->addWidget(removeContract);

       auto down = new QWidget;
       auto lyDown = new QFormLayout;
       down->setLayout(lyDown);
       lyDown->addRow(labelRandom, editNumarRandom);

        auto down1 = new QWidget;
        auto lyDown1 = new QFormLayout;
        down1->setLayout(lyDown1);
        lyDown1->addRow(labelExport, editExportContracte);

        auto butoaneNoi = new QWidget;
        auto lyButoaneNoi = new QHBoxLayout;
        butoaneNoi->setLayout(lyButoaneNoi);
        lyButoaneNoi->addWidget(butonReadOnlyGUI);
        lyButoaneNoi->addWidget(butonCrudGUI);

        lyFereastraContracte->addWidget(up1);
        lyFereastraContracte->addSpacing(-15);
        lyFereastraContracte->addWidget(up);
       lyFereastraContracte->addSpacing(30);
        lyFereastraContracte->addWidget(down);
        lyFereastraContracte->addSpacing(-15);
       lyFereastraContracte->addWidget(button1);
        lyFereastraContracte->addSpacing(30);
        lyFereastraContracte->addWidget(down1);
        lyFereastraContracte->addSpacing(-15);
       lyFereastraContracte->addWidget(button2);
        lyFereastraContracte->addSpacing(30);
        lyFereastraContracte->addWidget(butoaneNoi);

       lyFereastraContracteMain->addWidget(fereastraContracte);
       lyFereastraContracteMain->addWidget(listaContracte);

       fereastraContracteMain->show();
    });

    QObject::connect(addContract, &QPushButton::clicked, [&]() {
       try {
            string denumire = editDenumireContract->text().toStdString();
            string tip = editTipContract->text().toStdString();

            editDenumireContract->clear();
            editTipContract->clear();

            this->serviceGUI.addContract(denumire, tip);
            this->reloadContracte(this->serviceGUI.getAllContract());
            QMessageBox::information(this, "INFO", QString::fromStdString("Disciplina adaugata cu succes."));
       } catch (Exception& exception) {
           QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
       }
    });

    QObject::connect(removeContract, &QPushButton::clicked, [&]() {
        try {
            this->serviceGUI.removeContract();
            this->reloadContracte(serviceGUI.getAllContract());
            QMessageBox::information(this, "INFO", QString::fromStdString("Contract sters cu succes."));
        } catch (Exception& exception) {
            QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(addRandom, &QPushButton::clicked, [&]() {
        try {
            int nrDiscipline = editNumarRandom->text().toInt();
            editNumarRandom->clear();
            this->serviceGUI.addRandom(nrDiscipline);
            this->reloadList(this->serviceGUI.getAll());
            this->reloadContracte(serviceGUI.getAllContract());
            QMessageBox::information(this, "INFO", QString::fromStdString("Discipline random adaugate cu succes."));
        } catch (Exception& exception) {
            QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(exportContracte, &QPushButton::clicked, [&]() {
        try {
            string fisier = editExportContracte->text().toStdString();
            editExportContracte->clear();
            this->serviceGUI.exportContract(fisier);
            listaContracte->clear();
            this->serviceGUI.removeContract();
            this->reloadList(this->serviceGUI.getAll());
            this->reloadContracte(this->serviceGUI.getAllContract());
            QMessageBox::information(this, "INFO", QString::fromStdString("Contract exportat cu succes."));
        } catch (Exception& exception) {
            QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
        }
    });

    QObject::connect(butonCrudGUI, &QPushButton::clicked, [&]() {
        auto fereastraContract = new contractGUIList(serviceGUI.getContract());
        fereastraContract->show();
    });

    QObject::connect(butonReadOnlyGUI, &QPushButton::clicked, [&](){
        auto fereastraFiguri = new HistogramGUI(serviceGUI.getContract());
       fereastraFiguri->show();
    });

    QObject::connect(tabelDiscipline->selectionModel(), &QItemSelectionModel::selectionChanged, [&](){
        if (tabelDiscipline->selectionModel()->selectedIndexes().isEmpty()) {
            editDenumire->setText("");
            editOre->setText("");
            editTip->setText("");
            editCadruDidactic->setText("");
        }
        else {
            auto row = tabelDiscipline->selectionModel()->selectedIndexes().at(0).row();
            auto denumire = tabelDiscipline->model()->data(tabelDiscipline->model()->index(row, 0), Qt::DisplayRole).toString();
            auto ore = tabelDiscipline->model()->data(tabelDiscipline->model()->index(row, 1), Qt::DisplayRole).toString();
            auto tip = tabelDiscipline->model()->data(tabelDiscipline->model()->index(row, 2), Qt::DisplayRole).toString();
            auto cadru_didactic = tabelDiscipline->model()->data(tabelDiscipline->model()->index(row, 3), Qt::DisplayRole).toString();

            editDenumire->setText(denumire);
            editOre->setText(ore);
            editTip->setText(tip);
            editCadruDidactic->setText(cadru_didactic);
            reloadList(serviceGUI.getAll());
        }
    });
}

void ContracteGUI::reloadList(const vector<Disciplina>& discipline) {

    // LISTA
    listaDiscipline->clear();
    for(const auto& disciplina: discipline) {
        auto item1 = new QListWidgetItem(QString::fromStdString(
                disciplina.getDenumire() + " " + std::to_string(disciplina.getOre()) + " " + disciplina.getTip() + " " +
                disciplina.getCadru()));
        listaDiscipline->addItem(item1);
    }

    // TABEL
//    tabelDiscipline->clearContents();
//    tabelDiscipline->setRowCount(discipline.size());
//    int lineNumber = 0;
//    for(const auto& disciplina: discipline) {
//        tabelDiscipline->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(disciplina.getDenumire())));
//        tabelDiscipline->setItem(lineNumber, 1, new QTableWidgetItem(QString::number(disciplina.getOre())));
//        tabelDiscipline->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(disciplina.getTip())));
//        tabelDiscipline->setItem(lineNumber, 3, new QTableWidgetItem(QString::fromStdString(disciplina.getCadru())));
//        lineNumber++;
//    }

    model->setDiscipline(discipline);
    initDynamicButtons();
}

void ContracteGUI::reloadContracte(const vector<Disciplina>& contracte) {
    listaContracte->clear();
    for(const auto& contract: contracte) {
        auto item = new QListWidgetItem(QString::fromStdString(contract.getDenumire() + " " + std::to_string(contract.getOre()) + " " + contract.getTip() + " " + contract.getCadru()));
        listaContracte->addItem(item);
    }
}

void ContracteGUI::GUIaddDisciplina() {
    try {
        string denumire = editDenumire->text().toStdString();
        int ore = editOre->text().toInt();
        string tip = editTip->text().toStdString();
        string cadru = editCadruDidactic->text().toStdString();

        editDenumire->clear();
        editOre->clear();
        editTip->clear();
        editCadruDidactic->clear();

        this->serviceGUI.addDisciplina(denumire, ore, tip, cadru);
        this->reloadList(this->serviceGUI.getAll());

        QMessageBox::information(this, "INFO", QString::fromStdString("Disciplina adaugata cu succes."));
    } catch (Exception& exception) {
        QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
    }
}

void ContracteGUI::GUIremoveDisciplina() {
    try {
        string denumire = editDenumire->text().toStdString();
        string tip = editTip->text().toStdString();

        editDenumire->clear();
        editOre->clear();
        editTip->clear();
        editCadruDidactic->clear();

        this->serviceGUI.removeDisciplina(denumire, tip);
        this->reloadList(this->serviceGUI.getAll());

        QMessageBox::information(this, "INFO", QString::fromStdString("Disciplina stearsa cu succes."));
    } catch (Exception& exception) {
        QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
    }
}

void ContracteGUI::GUImodifyDisciplina() {
    try {
        string denumire = editDenumire->text().toStdString();
        int ore = editOre->text().toInt();
        string tip = editTip->text().toStdString();
        string cadru = editCadruDidactic->text().toStdString();

        editDenumire->clear();
        editOre->clear();
        editTip->clear();
        editCadruDidactic->clear();

        this->serviceGUI.modifyDisciplina(denumire, ore, tip, cadru);
        this->reloadList(this->serviceGUI.getAll());

        QMessageBox::information(this, "INFO", QString::fromStdString("Disciplina modificata cu succes."));
    } catch (Exception& exception) {
        QMessageBox::information(this, "ERROR", QString::fromStdString(exception.getMessage()));
    }
}