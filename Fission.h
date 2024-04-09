#ifndef _FISSION_H_
#define _FISSION_H_
#include <xtensor/xtensor.hpp>
#include <string>
#include <stdlib.h>
#include <iterator>

namespace Fission {
  using Coords = std::vector<std::tuple<int, int, int>>;

  constexpr int neutronReach(4);
  constexpr double modPower(1.0), modHeat(2.0);

  enum {
    // Cooler
    Water, Redstone, Quartz, Gold, Glowstone,
    Lapis, Diamond, Helium, Enderium, Cryotheum,
    Iron, Emerald, Copper, Tin, Magnesium, Active,
    // Other
    Cell = Active * 2, Moderator, Air
  };

  enum {
    GoalPower,
    GoalBreeder,
    GoalEfficiency
  };

  struct Settings {
    int sizeX, sizeY, sizeZ;
    double fuelBasePower, fuelBaseHeat;
    int limit[Air];
    double coolingRates[Cell];
    bool ensureActiveCoolerAccessible;
    bool ensureHeatNeutral;
    int goal;
    bool symX, symY, symZ;



    static Settings create(int sizeX, int sizeY, int sizeZ, double fuelBasePower, double fuelBaseHeat, int limit[Air], double coolingRates[Cell], 
        bool ensureActiveCoolerAccessible, bool ensureHeatNeutral, int goal, bool symX, bool symY, bool symZ)        
    {
        Settings s = {};
        s.sizeX = sizeX;
        s.sizeY = sizeY;
        s.sizeZ = sizeZ;
        s.fuelBasePower = fuelBasePower;
        s.fuelBaseHeat = fuelBaseHeat;
        memcpy(s.limit, limit, sizeof(int) * Air);
        memcpy(s.coolingRates, coolingRates, sizeof(double) * Cell);
        s.ensureActiveCoolerAccessible = ensureActiveCoolerAccessible;
        s.ensureHeatNeutral = ensureHeatNeutral;
        s.goal = goal;
        s.symX = symX;
        s.symY = symY;
        s.symZ = symZ;

        return s;
    }
  };

  struct Evaluation {
    // Raw
    Coords invalidTiles;
    double powerMult, heatMult, cooling;
    int breed;
    // Computed
    double heat, netHeat, dutyCycle, avgMult, power, avgPower, avgBreed, efficiency;

    void compute(const Settings &settings);
  };

  class Evaluator {
    const Settings &settings;
    xt::xtensor<int, 3> mults, rules;
    xt::xtensor<bool, 3> isActive, isModeratorInLine, visited;
    const xt::xtensor<int, 3> *state;
    int compatibleTile;

    int getTileSafe(int x, int y, int z) const;
    int getMultSafe(int x, int y, int z) const;
    bool countMult(int x, int y, int z, int dx, int dy, int dz);
    int countMult(int x, int y, int z);
    bool isActiveSafe(int tile, int x, int y, int z) const;
    int countActiveNeighbors(int tile, int x, int y, int z) const;
    bool isTileSafe(int tile, int x, int y, int z) const;
    int countNeighbors(int tile, int x, int y, int z) const;
    int countCasingNeighbors(int x, int y, int z) const;
    bool checkAccessibility(int compatibleTile, int x, int y, int z);
    bool checkAccessibility(int x, int y, int z);
  public:
    Evaluator(const Settings &settings);
    void run(const xt::xtensor<int, 3> &state, Evaluation &result);
  };
}

#endif
