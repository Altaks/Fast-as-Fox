#ifndef MAPSECTION_H
#define MAPSECTION_H

#include <iostream>
#include <map>

/**
 * @brief The MapSection class represents a section of the game map.
 *
 * A MapSection is a portion of the game map that contains tiles.
 */
class MapSection
{
private:
    std::map<std::pair<int, int>, int> coordinatesToTileId; /**< The mapping of coordinates to tile IDs. */
    int sectionWidth; /**< The width of the section. */
    int sectionHeight; /**< The height of the section. */

public:
    /**
     * @brief Constructs a MapSection object with the specified level path.
     * @param levelpath The path to the level file.
     */
    MapSection(std::string levelpath);

    /**
     * @brief Returns the mapping of coordinates to tile IDs.
     * @return The mapping of coordinates to tile IDs.
     */
    std::map<std::pair<int, int>, int> getCoordinatesToTileId() const;

    /**
     * @brief Returns the width of the section.
     * @return The width of the section.
     */
    int getSectionWidth() const;

    /**
     * @brief Returns the height of the section.
     * @return The height of the section.
     */
    int getSectionHeight() const;
};

#endif // MAPSECTION_H
