#ifndef __LIBLEVENSHTEIN__TRANSDUCER__STATE_TRANSITION_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__STATE_TRANSITION_H__

#include <cstddef>
#include <functional>
#include <vector>

#include "liblevenshtein/transducer/position.h"
#include "liblevenshtein/transducer/state.h"
#include "liblevenshtein/transducer/unsubsume.h"

namespace liblevenshtein {

    using PositionTransitionFn =
        std::function<std::vector<Position *>(std::size_t, Position *,
                                              std::vector<bool>&, std::size_t)>;
    using CompareFn = std::function<int(Position *, Position *)>;
    using MergeFn = std::function<void(State *, std::vector<Position *>)>;

    class StateTransition {
    public:
        StateTransition(PositionTransitionFn transition,
                        CompareFn compare,
                        MergeFn merge,
                        UnsubsumeFn unsubsume,
                        std::size_t max_distance,
                        std::size_t query_length);

        State * operator()(State *curr_state, std::vector<bool> &characteristic_vector);
    private:
        PositionTransitionFn transition;
        CompareFn compare;
        MergeFn merge;
        UnsubsumeFn unsubsume;
        std::size_t max_distance;
        std::size_t query_length;
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__STATE_TRANSITION_H__
