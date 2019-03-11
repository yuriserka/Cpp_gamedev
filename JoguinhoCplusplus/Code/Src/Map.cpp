#include <time.h>
#include <fstream>

#include "../Include/Map.h"

void Map::loadMap(std::string path, int size_x, int size_y) {
    std::fstream map_file;
    map_file.open(path);

    if (!map_file.is_open()) {
        std::cout << "nao foi possivel abrir o arquivo: " << path << "\n";
        exit(EXIT_FAILURE);
    }

    for (int y = 0; y < size_y; ++y) {
        for (int x = 0; x < size_x; ++x) {
            char char_tileId;
            map_file.get(char_tileId);
            
            this->addTile(x * 32, y * 32, atoi(&char_tileId));

            map_file.ignore();
        }
    }

    map_file.close();
}