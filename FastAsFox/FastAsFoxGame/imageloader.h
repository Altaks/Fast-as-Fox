#ifndef IMAGELOADER_H
#define IMAGELOADER_H

#include <QGraphicsDropShadowEffect>
#include <QKeyEvent>
#include <QFontDatabase>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QMovie>
#include <QApplication>
#include <QThreadPool>
#include <QTimer>
#include <iostream>
#include <QPushButton>
#include <QAudioOutput>
#include <QFile>
#include <constants.h>
#include <QElapsedTimer>

/**
 * @class ImageLoader
 * @brief Loads and processes images for menu items.
 *
 * The ImageLoader class loads images for menu items and applies processing
 * based on the number of levels unlocked. It emits a signal when the image is ready.
 */
class ImageLoader : public QObject, public QRunnable
{
    Q_OBJECT

public:
    ImageLoader(int index, int numberOfLevelsUnlocked, QObject* parent = nullptr);

signals:
    /**
     * @brief Signal emitted when the image is ready.
     * @param index The index of the image.
     * @param image The processed image.
     */
    void imageReady(int index, QPixmap pixmap);

protected:
    void run() override;

private:
    int m_index;
    int m_numberOfLevelsUnlocked;
};


#endif // IMAGELOADER_H
