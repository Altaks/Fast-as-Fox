#include "mapsection.h"

#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>

std::map<std::pair<int, int>, int> MapSection::getCoordinatesToTileId() const
{
    return coordinatesToTileId;
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
    coordinatesToTileId = std::map<std::pair<int, int>, int>();

    int dataWidth = jsonDocument["layers"].toArray()[0].toObject()["width"].toInt();
    int dataHeight = jsonDocument["layers"].toArray()[0].toObject()["height"].toInt();

    for(int currentX = 0; currentX < dataWidth; currentX++){
        for(int currentY = 0; currentY < dataHeight; currentY++){

            // get tile id into the array
            int tileId = levelData.at(currentY * dataHeight + currentX).toInt();

            // determine game accurate coordinates
            int gameCoordX = currentX;
            int gameCoordY = dataHeight - currentY;

            // add the tile to the section
            coordinatesToTileId.emplace(std::pair<int, int>(gameCoordX, gameCoordY), tileId);
        }
    }

    jsonFile.close();
}
