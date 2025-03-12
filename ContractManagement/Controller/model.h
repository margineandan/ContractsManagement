#pragma once

#include "../Domain/disciplina.h"
#include "../Service/service.h"

#include <QAbstractTableModel>
#include <QStandardItemModel>
#include <QBrush>
#include <Qt>
#include <utility>

/**
 * @class MyTableModel
 * @brief A custom model for displaying a list of disciplines in a QTableView.
 * This model represents the data of a list of `Disciplina` objects in a tabular format.
 */
class MyTableModel: public QAbstractTableModel {
private:
    vector<Disciplina> discipline;  ///< The vector of `Disciplina` objects to be displayed in the table.

public:
    /**
     * @brief Constructor that initializes the model with a list of disciplines.
     * @param discipline A vector of `Disciplina` objects to initialize the model.
     */
    explicit MyTableModel(vector<Disciplina> discipline): discipline(std::move(discipline)) {};

    /**
     * @brief Returns the number of rows in the model.
     * @param parent The parent index for the row count, default is an invalid index.
     * @return The number of rows in the model.
     */
    [[nodiscard]] int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return discipline.size();
    }

    /**
     * @brief Returns the number of columns in the model.
     * @param parent The parent index for the column count, default is an invalid index.
     * @return The number of columns in the model (4 in this case: Denumire, Ore, Tip, Cadru).
     */
    [[nodiscard]] int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 4;  ///< The table has 4 columns.
    }

    /**
     * @brief Returns the data for a specific cell in the table.
     * @param index The index of the cell (row and column).
     * @param role The role of the data (e.g., display role).
     * @return The data to display for the specified cell.
     */
    [[nodiscard]] QVariant data(const QModelIndex& index = QModelIndex(), int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            Disciplina disciplina = discipline[index.row()];

            if (index.column() == 0)
                return QString::fromStdString(disciplina.getDenumire());
            if (index.column() == 1)
                return QString::number(disciplina.getOre());
            if (index.column() == 2)
                return QString::fromStdString(disciplina.getTip());
            if (index.column() == 3)
                return QString::fromStdString(disciplina.getCadru());
        }

        return QVariant{};  ///< Return an empty QVariant if no data is available for the requested role.
    }

    /**
     * @brief Sets the data for the model with a new list of disciplines.
     * @param vectorDiscipline The new vector of `Disciplina` objects to be set.
     */
    void setDiscipline(vector<Disciplina> vectorDiscipline) {
        this->discipline = std::move(vectorDiscipline);

        // Notify the view that the data has changed and the layout needs to be updated.
        QModelIndex topLeft = createIndex(0, 0);
        QModelIndex bottomRight = createIndex(rowCount(), columnCount());

        emit layoutChanged();
        emit dataChanged(topLeft, bottomRight);
    }
};
