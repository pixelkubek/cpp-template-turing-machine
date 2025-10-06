#include "machine.h"

#define ADD_STATE(state_name)                                                  \
    namespace state {                                                          \
        struct state_name {};                                                  \
    }
#define ADD_TAPE_SYMBOL(symbol_name)                                           \
    namespace tape_symbol {                                                    \
        struct symbol_name {};                                                 \
    }

#define ADD_TRANSITION(from_state, from_symbol, to_state, to_symbol,           \
                       to_direction)                                           \
    template <>                                                                \
    struct next_state<state::from_state, tape_symbol::from_symbol>             \
        : std::type_identity<state::to_state> {};                              \
                                                                               \
    template <>                                                                \
    struct chosen_symbol<state::from_state, tape_symbol::from_symbol>          \
        : std::type_identity<tape_symbol::to_symbol> {};                       \
                                                                               \
    template <>                                                                \
    struct chosen_direction<state::from_state, tape_symbol::from_symbol>       \
        : std::type_identity<direction::to_direction> {}

#define RUN_WITH_TAPE(...)                                                     \
    using namespace tape_symbol;                                               \
    static_assert(                                                             \
        compute<machine<state::start, new_tape_t<__VA_ARGS__>>>::value)

#define RUN_EMPTY()                                                            \
    static_assert(compute<machine<state::start, new_blank_tape_t>>::value)

ADD_STATE(moved_right);
ADD_STATE(moved_back);
ADD_TAPE_SYMBOL(sym);

ADD_TRANSITION(start, blank, moved_right, sym, go_right);
ADD_TRANSITION(moved_right, blank, moved_back, blank, go_left);
ADD_TRANSITION(moved_back, sym, accept, blank, stay);
ADD_TRANSITION(accept, blank, accept, blank, stay);

RUN_EMPTY();