#ifndef __RANDOM_AGENT_H__
#define __RANDOM_AGENT_H__

#include <optional>

#include "utils.h"

class RandomAgent {
   public:
    std::pair<team, team> takeTurn(team whiteBitboards, team blackBitboards,
                                   bool turn);
};
#endif  // !__RANDOM_AGENT_H__
