#ifndef CITYTOWERMANAGER_H
#define CITYTOWERMANAGER_H

#include <vector>

class CityTowerManager {
public:
    CityTowerManager(const std::vector<int>& cities, const std::vector<int>& towers);
    int findMinR();

private:
    std::vector<int> cities;
    std::vector<int> towers;
    int closestTower(int city);
};

#endif // CITYTOWERMANAGER_H
