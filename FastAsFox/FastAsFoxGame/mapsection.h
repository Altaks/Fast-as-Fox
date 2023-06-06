#ifndef MAPSECTION_H
#define MAPSECTION_H

#include <iostream>
#include <map>

class MapSection
{
private:
    std::map<std::pair<int, int>, int> * coordinatesToTileId;
    int sectionWidth, sectionHeight;
public:
    MapSection(std::string levelpath);
    std::map<std::pair<int, int>, int> * getCoordinatesToTileId() const;
    int getSectionWidth() const;
    int getSectionHeight() const;
};

#endif // MAPSECTION_H
