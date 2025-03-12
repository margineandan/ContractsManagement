#pragma once

#include "../Contract/contract.h"
#include <QWidget>
#include <QPainter>

/**
 * @class HistogramGUI
 * @brief A graphical user interface (GUI) class that visualizes contract data as a histogram.
 *
 * This class represents a histogram where each bar corresponds to a contract's data,
 * with the height of each bar being proportional to the number of hours (Ore) in the contract.
 * The class uses the Observer design pattern, updating the histogram whenever the underlying
 * contract data changes. The histogram is painted using the `QPainter` class on the widget.
 * Each bar is placed at a random location on the widget for visual representation.
 */
class HistogramGUI: public QWidget, public Observer {
private:
    contractStudii& contractStudii;

public:
    /**
     * @brief Constructor that initializes the histogram GUI and sets up the observer.
     *
     * The constructor registers this `HistogramGUI` object as an observer for the `contractStudii`
     * model, ensuring that the histogram is updated when the contract data changes.
     *
     * @param contractStudii A reference to the `contractStudii` model containing contract data.
     */
    explicit HistogramGUI(class contractStudii& contractStudii): contractStudii(contractStudii) {
        contractStudii.addObserver(this);
    };

    /**
     * @brief Called when the observed contract data changes.
     *
     * This method triggers a repaint of the widget to update the histogram display
     * with the latest contract data.
     */
    void update() override {
        repaint();
    }

    /**
     * @brief Paint event handler that renders the histogram on the widget.
     *
     * This method uses `QPainter` to draw a histogram on the widget, where each
     * rectangle (bar) corresponds to a contract. The height of each bar represents
     * the number of hours (`Ore`) associated with each contract, and the bars are
     * placed at random locations on the widget.
     *
     * @param ev The paint event that contains information about the paint request.
     */
    void paintEvent(QPaintEvent* ev) override {
        QPainter painter{this};
        srand(time(nullptr));

        for(const auto& contract: contractStudii.getAllContract()) {
            int coordX = rand() % 300;
            int coordY = rand() % 300;
            painter.drawRect(coordX, coordY, 60, contract.getOre() * 2);
        }
    }
};
