#include "route.h"

const std::vector<std::string> Route::route =
{
  "c1a0d",
  "c1a0a",
  "c1a0b",
  "c1a0e",
  "c1a0c",
  "c1a1",
  "c1a1a",
  "c1a1f",
  "c1a1b",
  "c1a1c",
  "c1a2",
  "c1a2a",
  "c1a2b",
  "c1a3",
  "c1a4",
  "c1a4k",
  "c1a4b",
  "c1a4f",
  "c1a4b",
  "c1a4i",
  "c1a4b",
  "c1a4i",
  "c1a4b",
  "c1a4d",
  "c1a4e",
  "c1a4d",
  "c1a4b",
  "c1a4i",
  "c1a4g",
  "c1a4j",
  "c2a1",
  "c2a2",
  "c2a2a",
  "c2a2b1",
  "c2a2c",
  "c2a2d",
  "c2a2e",
  "c2a2f",
  "c2a2g",
  "c2a2h",
  "c2a2g",
  "c2a3",
  "c2a3a",
  "c2a3b",
  "c2a3c",
  "c2a3d",
  "c2a3e",
  "c2a4",
  "c2a4a",
  "c2a4b",
  "c2a4c",
  "c2a4d",
  "c2a4e",
  "c2a4f",
  "c2a4e",
  "c2a4g",
  "c2a5",
  "c2a5w",
  "c2a5x",
  "c2a5a",
  "c2a5b",
  "c2a5c",
  "c2a5d",
  "c2a5e",
  "c2a5f",
  "c2a5g",
  "c3a1",
  "c3a1a",
  "c3a1b",
  "c3a2e",
  "c3a2",
  "c3a2a",
  "c3a2b",
  "c3a2c",
  "c3a2d",
  "c4a1",
  "c4a2",
  "c4a2a",
  "c4a2b",
  "c4a1a",
  "c4a1b",
  "c4a1c",
  "c4a1d",
  "c4a1e",
  "c4a1f",
  "c4a3",
};

bool Route::checkNextLevelInRoute(const std::string& level)
{
  if (nextLevelIndex >= 0 && nextLevelIndex < route.size() && level == route[nextLevelIndex])
  {
    nextLevelIndex++;
    return true;
  }

  return false;
}