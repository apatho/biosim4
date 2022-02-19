#ifndef SIGNALS_H_INCLUDED
#define SIGNALS_H_INCLUDED

// Container for pheromones.

#include <vector>
#include <cstdint>
#include <cassert>
#include "basicTypes.h"

namespace BS {

// Usage: uint8_t magnitude = signals[layer][x][y];
// or             magnitude = signals.getMagnitude(layer, Coord);


constexpr unsigned SIGNAL_MIN = 0;
constexpr unsigned SIGNAL_MAX = UINT8_MAX;

enum SignalLayer {
    PHEROMONE = 0,
    FOOD = 1,
};

struct Signals {
    struct Column {
        Column(uint16_t numRows) : data { std::vector<uint8_t>(numRows, 0) } { }
        uint8_t& operator[](uint16_t rowNum) { assert(rowNum < data.size()); return data[rowNum]; }
        uint8_t operator[](uint16_t rowNum) const { assert(rowNum < data.size()); return data[rowNum]; }
        void zeroFill() { std::fill(data.begin(), data.end(), 0); }
    private:
        std::vector<uint8_t> data;
    };

    struct Layer {
        Layer(uint16_t numCols, uint16_t numRows) : data { std::vector<Column>(numCols, Column(numRows)) } { }
        Column& operator[](uint16_t colNum) { assert(colNum < data.size()); return data[colNum]; }
        const Column& operator[](uint16_t colNum) const { assert(colNum < data.size()); return data[colNum]; }
        void zeroFill() { for (Column &col : data) { col.zeroFill(); } }
    private:
        std::vector<Column> data;
    };

    void init(uint16_t layers, uint16_t sizeX, uint16_t sizeY);
    Layer& operator[](uint16_t layerNum) { return data[layerNum]; }
    const Layer& operator[](uint16_t layerNum) const { assert(layerNum < data.size()); return data[layerNum]; }
    uint8_t getMagnitude(uint16_t layerNum, Coord loc) const { assert(layerNum < data.size()); return (*this)[layerNum][loc.x][loc.y]; }
    void setMagnitude(uint16_t layerNum, Coord loc, uint8_t magnitude);
    void increment(uint16_t layerNum, Coord loc);
    void zeroFill() { for (Layer &layer : data) { layer.zeroFill(); } }
    void fade(unsigned layerNum);

private:
    std::vector<Layer> data;
};

} // end namespace BS

#endif // SIGNALS_H_INCLUDED
