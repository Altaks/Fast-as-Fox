#ifndef MAPSECTION_H
#define MAPSECTION_H

#include <iostream>
#include <map>

class MapSection
{
private:
    /**
     * @brief coordinatesToTileId stores the coordinates of a tile, as well as its ID
     */
    std::map<std::pair<int, int>, int> * coordinatesToTileId;
    /**
     * @brief sectionWidth the width of the mapSection
     * @brief sectionHeight the height of the mapSection
     */
    int sectionWidth, sectionHeight;
public:
    /**
     * @brief MapSection the constructor for the mapSection class
     * @param levelpath the path to the file that contains the level
     */
    MapSection(std::string levelpath);
    /**
     * @brief getCoordinatesToTileId getter for coordinaeToTileId
     * @return  coordinaeToTileId
     */
    std::map<std::pair<int, int>, int> * getCoordinatesToTileId() const;
    /**
     * @brief getSectionWidth getter for sectionWidth
     * @return sectionWidth
     */
    int getSectionWidth() const;
    /**
     * @brief getSectionHeight getter for sectionHeight
     * @return sectionHeight
     */
    int getSectionHeight() const;
};

#endif // MAPSECTION_H
