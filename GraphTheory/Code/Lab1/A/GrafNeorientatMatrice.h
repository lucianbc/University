#ifndef PROBLEME_GRAFNEORIENTATMATRICE_H
#define PROBLEME_GRAFNEORIENTATMATRICE_H

#include <vector>
#include <string>

namespace GrafNeorientatMatrice
{
    std::vector<std::vector<int>> citeste(std::istream&);
    void afisare(std::vector<std::vector<int>>, std::ostream&);
}

#endif //PROBLEME_GRAFNEORIENTATMATRICE_H
