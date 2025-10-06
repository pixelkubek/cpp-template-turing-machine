#ifndef MACHINE_H
#define MACHINE_H

#include "tape.h"


namespace state {
    struct start {};
    struct accept {};
    struct reject {};
};

template <typename State, typename TapeContent>
struct next_state {};

template <typename State, typename TapeContent>
struct chosen_symbol {};

template <typename State, typename TapeContent>
struct chosen_direction {};

template <typename State, typename TapeContent>
using next_state_t = typename next_state<State, TapeContent>::type;

template <typename State, typename TapeContent>
using chosen_symbol_t = typename chosen_symbol<State, TapeContent>::type;

template <typename State, typename TapeContent>
using chosen_direction_t = typename chosen_direction<State, TapeContent>::type;

template <typename State, typename Tape>
struct machine {};

template <typename T>
struct advance {};

template <typename State, typename Tape>
struct advance<machine<State, Tape>> : std::type_identity<machine<
    next_state_t<State, header_read_t<Tape>>,
    move_header_t<
        chosen_direction_t<
            State,
            header_read_t<Tape>
        >,
        header_write_t<
            chosen_symbol_t<State, header_read_t<Tape>>,
            Tape
        >
    >
>> {};

template <typename T>
using advance_t = typename advance<T>::type;

using machine_instance = machine<state::start, new_blank_tape_t>;

template <typename T>
struct compute {};

template <typename State, typename Tape>
struct compute<machine<State, Tape>> : std::conditional_t<
    std::is_same_v<State, state::accept>,
    std::true_type,
    std::conditional_t<
        std::is_same_v<State, state::reject>,
        std::false_type,
        compute<advance_t<machine<State, Tape>>>
    >
> {};

#endif