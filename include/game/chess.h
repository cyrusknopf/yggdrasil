#include <array>
#include <cstdint>

class Chess {
public:
  std::array<uint64_t, 12> bitboards;

  void initGame();
};
