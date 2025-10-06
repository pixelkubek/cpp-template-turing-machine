#include "machine.h"

#define add_state(state_name)                                                  \
    namespace state {                                                          \
        struct state_name {};                                                  \
    }
#define add_tape_symbol(symbol_name)                                           \
    namespace tape_symbol {                                                    \
        struct symbol_name {};                                                 \
    }

#define add_transition(from_state, from_symbol, to_state, to_symbol,           \
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


add_state(moved_right);
add_state(moved_back);
add_tape_symbol(sym);

add_transition(start, blank, moved_right, sym, go_right);
add_transition(moved_right, blank, moved_back, blank, go_left);
add_transition(moved_back, sym, accept, blank, stay);
add_transition(accept, blank, accept, blank, stay);

using my_machine = machine<state::start, new_blank_tape_t>;

static_assert(compute<my_machine>::value);