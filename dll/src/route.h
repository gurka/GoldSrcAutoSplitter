#ifndef ROUTE_H_
#define ROUTE_H_

#include <string>
#include <vector>

class Route
{
 public:
  bool checkNextLevelInRoute(const std::string& level);
  bool isDone() const { return nextLevelIndex == route.size(); }
  void reset() { nextLevelIndex = 0; }

 private:
  std::size_t nextLevelIndex = 0;

  static const std::vector<std::string> route;
};

#endif  // ROUTE_H_
