#include <xtensor/xnpy.hpp>
#include "FissionNet.h"

int main() {
  //Fission::Settings settings {
  //  7, 7, 7,
  //  168, 62.5
  //  {
  //    {1.75, -1, 60, 540, true},
  //    {1.75, -1, 75, 432, true},
  //    {1.75, -1, 51, 676, true},
  //    {1.80, -1, 30, 1620, true},
  //    {1.80, -1, 37, 1296, true},
  //    {1.80, -1, 25, 2028, true},
  //    {1.80, -1, 71, 288, true},
  //    {1.80, -1, 89, 230, true},
  //    {1.80, -1, 60, 360, true},
  //    {1.85, -1, 35, 864, true},
  //    {1.85, -1, 44, 690, true},
  //    {1.85, -1, 30, 1080, true}
  //  },
  //  {
  //    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  //    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
  //    -1, -1, -1, -1, -1, -1, -1, -1
  //  },
  //  {0, 0, 0},
  //  Fission::GoalOutput,
  //  false, false, true, true
  //};

  double coolVals[Fission::Cell] = { 60, 90, 90, 120, 130, 120, 150, 140, 120, 160, 80, 160, 80, 120, 110, 150, 3200, 3000, 4800, 4000, 2800, 7000, 6600, 5400, 6400, 2400, 3600, 2600, 3000, 3600 };
  int countLimits[Fission::Air] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1};
  auto settings = Fission::Settings::create(10, 10, 10, 84, 22.5, countLimits, coolVals, true, true, Fission::GoalPower, true, true, true);

  Fission::Opt opt(settings, true);
  while (true) {
    opt.stepInteractive();
    if (opt.needsRedrawBest()) {
        std::cout << "Max Power: " << opt.getBest().value.power << std::endl;
        std::cout << "Net Heat: " << opt.getBest().value.netHeat << std::endl;
        std::cout << "Efficiency: " << opt.getBest().value.efficiency*100 << "%" << std::endl;
        std::cout << "---------------------\n";
        xt::dump_npy("best.npy", opt.getBest().state);
    }
  }
}
