#include "CityTowerManager.h"
#include <algorithm>
#include <cmath>
#include <climits> // Incluir este encabezado para usar INT_MAX
#include <stdexcept>

CityTowerManager::CityTowerManager(const std::vector<int>& cities, const std::vector<int>& towers)
    : cities(cities), towers(towers) {}

int CityTowerManager::findMinR() {
    try {
        int max_min_distance = 0;
        for (int city : cities) {
            int min_distance = closestTower(city);
            max_min_distance = std::max(max_min_distance, min_distance);
        }
        return max_min_distance;
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al calcular la distancia minima: " + std::string(e.what()));
    }
}

int CityTowerManager::closestTower(int city) {
    try {
        auto it = std::lower_bound(towers.begin(), towers.end(), city);
        int dist1 = (it == towers.end()) ? INT_MAX : std::abs(*it - city);
        int dist2 = (it == towers.begin()) ? INT_MAX : std::abs(*(it - 1) - city);
        return std::min(dist1, dist2);
    } catch (const std::exception& e) {
        throw std::runtime_error("Error al encontrar la torre mas cercana: " + std::string(e.what()));
    }
}
