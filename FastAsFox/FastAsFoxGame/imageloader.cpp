#include "imageloader.h"

/**
     * @brief Constructs an ImageLoader object.
     * @param index The index of the image.
     * @param numberOfLevelsUnlocked The number of levels unlocked.
     * @param parent The parent QObject.
     */
ImageLoader::ImageLoader(int index, int numberOfLevelsUnlocked, QObject* parent)
    : QObject(parent), m_index(index), m_numberOfLevelsUnlocked(numberOfLevelsUnlocked)
{
}
/**
     * @brief Starts the image loading and processing.
     *
     * This function loads the base image, applies grayscale conversion if the
     * index is greater than or equal to the number of levels unlocked, scales
     * the images to a fixed size, overlays a frame, and emits the imageReady signal.
     */
void ImageLoader::run()
{
    QPixmap baseImage(":/menu/sprites/menu/" + QString::number(m_index + 1) + ".jpg");

    if (m_index >= m_numberOfLevelsUnlocked) {
        QImage image = baseImage.toImage();
        image = image.convertToFormat(QImage::Format_Grayscale8);
        baseImage = QPixmap::fromImage(image);
    }

    baseImage = baseImage.scaled(QSize(200, 150), Qt::IgnoreAspectRatio);

    QPixmap overlayImage(":/menu/sprites/menu/framelevel.png");
    overlayImage = overlayImage.scaled(QSize(200, 150), Qt::IgnoreAspectRatio);

    QPainter painter(&baseImage);
    painter.drawPixmap(0, 0, overlayImage);
    painter.end();

    emit imageReady(m_index, baseImage);
}
