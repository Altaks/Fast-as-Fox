#ifndef MAPSECTION_H
#define MAPSECTION_H

#include <iostream>
#include <map>

class MapSection
{
private:
    /**
     * @brief coordinatesToTileId a map that contains the coordinates to the tiles
     */
    std::map<std::pair<int, int>, int> * coordinatesToTileId;

    /**
     * @brief sectionWidth the size of the section
     */
    int sectionWidth, sectionHeight;
public:
    /**
     * @brief MapSection a constructor
     * @param levelpath the path to the level file
     */
    MapSection(std::string levelpath);
    std::map<std::pair<int, int>, int> * getCoordinatesToTileId() const;
    int getSectionWidth() const;
    int getSectionHeight() const;
};

#endif // MAPSECTION_H
