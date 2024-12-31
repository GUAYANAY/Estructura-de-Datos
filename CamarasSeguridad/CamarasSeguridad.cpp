#include "CamarasSeguridad.h"
#include <algorithm>
#include <cmath>

using namespace std;

bool isCovered(int r, const vector<int>& locations, const vector<int>& cameras) {
    int j = 0;
    for (int i = 0; i < locations.size(); ++i) {
        while (j < cameras.size() && abs(cameras[j] - locations[i]) > r) {
            ++j;
        }
        if (j == cameras.size()) {
            return false;
        }
    }
    return true;
}

int CamarasSeguridad::calcularRangoMinimo(const vector<int>& locations, const vector<int>& cameras) {
    int left = 0, right = 1e9;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (isCovered(mid, locations, cameras)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}
