#ifndef __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__
#define __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__

#include <functional>
#include <initializer_list>
#include <vector>

#include "position.h"
#include "state_iterator.h"


namespace liblevenshtein {

    using Comparator = std::function<int(Position *, Position *)>;

    class StateIterator;

    class State {
    public:
        State() = default;
        State(std::initializer_list<Position *> positions);
        State(std::vector<Position *>& positions); // for testing
        ~State();

        State* head(Position *head);
        Position* head() const;
        State* add(Position *head);
        State* insert_after(Position *curr, Position *next);
        State* remove(Position *prev, Position *curr);
        State* sort(Comparator compare);

        StateIterator begin();
        StateIterator end();

    private:
        Position* _head = nullptr;

        Position *merge_sort(Comparator compare, Position *lhs_head);
        Position *merge(Comparator compare, Position *lhs_head,
                        Position *rhs_head);
        Position *find_middle(Position *head);
    };

} // namespace liblevenshtein


#endif // __LIBLEVENSHTEIN__TRANSDUCER__STATE_H__
