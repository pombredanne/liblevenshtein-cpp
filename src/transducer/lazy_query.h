#ifndef __LIBLEVENSHTEIN__TRANSDUCER__LAZY_QUERY_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__LAZY_QUERY_H__

#include <cstddef>
#include <functional>
#include <queue>
#include <string>
#include <utility>
#include <vector>

#include "../collection/dawg_node.h"
#include "state.h"
#include "intersection.h"


namespace liblevenshtein {

    using TransitionFn = std::function<State *(State *, std::vector<bool> &)>;
    using DistanceFn = std::function<std::size_t(State *,std::size_t)>;

    template <class Result>
    class LazyQuery {
    public:
        LazyQuery(const std::string &term,
                  std::size_t max_distance,
                  DawgNode *root,
                  State *initial_state,
                  TransitionFn transition,
                  DistanceFn min_distance);

        LazyQuery() = default;

        LazyQuery &operator++();
        const Result& operator*() const;
        bool operator!=(const LazyQuery &other) const;

    private:
        std::queue<Intersection *> _pending;
        std::queue<std::pair<char, DawgNode *>> _edges;

        bool _is_complete = false;
        Intersection *_intersection = nullptr;
        Result _candidate;

        std::string _term;
        std::size_t _max_distance;
        TransitionFn transition;
        DistanceFn min_distance;

        std::size_t _a;
        std::size_t _k;
        std::size_t _i;

        void advance();

        void update_candidate(std::string &term, std::size_t distance);

        std::vector<bool> characteristic_vector(char x,
                                                std::string &term,
                                                std::size_t k,
                                                std::size_t i);
    };

    template class LazyQuery<std::string>;
    template class LazyQuery<std::pair<std::string, std::size_t>>;

    template <class Result>
    class LazyIterator {
    public:
        LazyIterator(const std::string &term,
                     std::size_t max_distance,
                     DawgNode *root,
                     State *initial_state,
                     TransitionFn transition,
                     DistanceFn min_distance);

        LazyQuery<Result> begin();
        LazyQuery<Result> end();

      private:
        std::string _term;
        std::size_t _max_distance;
        DawgNode* _root;
        State* _initial_state;
        TransitionFn transition;
        DistanceFn min_distance;
    };

    template class LazyIterator<std::string>;
    template class LazyIterator<std::pair<std::string, std::size_t>>;

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__LAZY_QUERY_H__
