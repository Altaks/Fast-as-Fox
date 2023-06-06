#include "mapsection.h"

#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

std::map<std::pair<int, int>, int> MapSection::getCoordinatesToTileId() const
{
    return coordinatesToTileId;
}

int MapSection::getSectionWidth() const
{
    return sectionWidth;
}

int MapSection::getSectionHeight() const
{
    return sectionHeight;
}

MapSection::MapSection(std::string levelpath)
{
    QFile jsonFile(QString::fromStdString(levelpath));

    if(!jsonFile.exists()){
        throw std::ios_base::failure("Level file doesn't exists : " + levelpath);
    }

    if(!jsonFile.open(QIODevice::ReadOnly)){
        throw std::ios_base::failure("Couldn't read ");
    }

    QByteArray data = jsonFile.readAll();
    QJsonDocument jsonDocument(QJsonDocument::fromJson(data));

    QJsonArray levelData = jsonDocument["layers"].toArray()[0].toObject()["data"].toArray();

    // acquire layer data to load it
    this->coordinatesToTileId = std::map<std::pair<int, int>, int>();

    int dataWidth = jsonDocument["layers"].toArray()[0].toObject()["width"].toInt();
    int dataHeight = jsonDocument["layers"].toArray()[0].toObject()["height"].toInt();

    this->sectionHeight = dataHeight;
    this->sectionWidth = dataWidth;

    for(int currentX = 0; currentX < dataWidth; currentX++){
        for(int currentY = 0; currentY < dataHeight; currentY++){

            // get tile id into the array
            int tileId = levelData.at(currentY * dataWidth + currentX).toInt();

            // determine game accurate coordinates
            int gameCoordX = currentX;
            int gameCoordY = dataHeight - 1 - currentY;

            // add the tile to the section
            coordinatesToTileId.emplace(std::pair<int, int>(gameCoordX, gameCoordY), tileId);
        }
    }

    jsonFile.close();
}
