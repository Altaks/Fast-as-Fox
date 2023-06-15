#include "Hublot.h"

Hublot::Hublot(QGraphicsScene *scene)
    : QGraphicsPixmapItem(), scene(scene) {
    setupImage();
}
/**
 * @brief Updates the Hublot with a new image or clears it.
 *
 * This function updates the Hublot with a new image if the `show` parameter is true.
 * If `show` is false, the Hublot is cleared and set to an empty pixmap.
 *
 * @param show A boolean value indicating whether to show the image or clear the Hublot.
 */
void Hublot::updateHublot(bool show) {
    if(show) {
        setupImage();
    }
    else {
        this->setPixmap(QPixmap()); // Set to an empty pixmap
    }
}
/**
 * @brief Sets up the image for the Hublot.
 *
 * This function sets up the image for the Hublot by combining a hublot pixmap,
 * a babyfox pixmap, and a gray square. The resulting image is scaled and drawn
 * onto the Hublot.
 */
void Hublot::setupImage() {
    QPixmap hublotPixmap(":/userInterface/sprites/userInterface/hublot.png");

    // Reduce size of the hublot pixmap by 8
    int newWidth = hublotPixmap.width() / 8;
    int newHeight = hublotPixmap.height() / 8;
    QPixmap scaledHublotPixmap = hublotPixmap.scaled(newWidth, newHeight, Qt::KeepAspectRatio);

    QPixmap babyfoxPixmap(":/userInterface/sprites/userInterface/babyfox.png");
    QPixmap scaledBabyfoxPixmap = babyfoxPixmap.scaled(newWidth/2, newHeight/2, Qt::KeepAspectRatio);

    // Draw babyfox pixmap onto hublot pixmap
    QPainter painter(&scaledHublotPixmap);
    int babyfoxX = (scaledHublotPixmap.width() - scaledBabyfoxPixmap.width()) / 2;
    int babyfoxY = (scaledHublotPixmap.height() - scaledBabyfoxPixmap.height()) / 2;
    painter.drawPixmap(babyfoxX, babyfoxY, scaledBabyfoxPixmap);

    // Draw gray square on the bottom-right of the hublot pixmap
    squareSize = newWidth / 4; // Change as needed
    int squareX = scaledHublotPixmap.width() - squareSize;
    int squareY = scaledHublotPixmap.height() - squareSize;
    painter.setPen(Qt::NoPen); // Remove border
    painter.setBrush(QBrush(Qt::gray));
    painter.drawRect(squareX, squareY, squareSize, squareSize);

    painter.end();

    // Set pixmap to the QGraphicsPixmapItem
    setPixmap(scaledHublotPixmap);

    // Adding the QGraphicsPixmapItem to the scene
    scene->addItem(this);
    this->update();
}
