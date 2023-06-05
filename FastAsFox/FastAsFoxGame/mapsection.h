#ifndef MAPSECTION_H
#define MAPSECTION_H

#include <iostream>
#include <map>

class MapSection
{
private:
    std::map<std::pair<int, int>, int> coordinatesToTileId;
public:
    MapSection(std::string levelpath);
    std::map<std::pair<int, int>, int> getCoordinatesToTileId() const;
};

#endif // MAPSECTION_H
