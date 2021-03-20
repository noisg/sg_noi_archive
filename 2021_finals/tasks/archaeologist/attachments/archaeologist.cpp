#include "archaeologist.h"
#include <utility>
#include <vector>

void archaeologist(int N, int K, int L, std::vector<int> map, int lightlevel, std::vector<int> paths) {
    // You should fill in this function
    
    // For example, set the light level of the current room
    set_light(0);
    
    // For example, take a corridor to an adjacent room
    std::pair<int, std::vector<int>> result = take_path(0);
    int new_room = result.first;
    std::vector<int> new_paths = result.second;
}