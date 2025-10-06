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


template <>
struct next_state<state::start, blank> : std::type_identity<state::accept> {};

template <>
struct chosen_symbol<state::start, blank> : std::type_identity<blank> {};


template <typename State, typename TapeContent>
using next_state_t = typename next_state<State, TapeContent>::type;

template <typename State, typename TapeContent>
using chosen_symbol_t = typename chosen_symbol<State, TapeContent>::type;

template <typename State, typename Tape>
struct machine {};

template <typename T>
struct advance {};

template <typename State, typename Tape>
struct advance<machine<State, Tape>> : std::type_identity<machine<
    next_state_t<State, header_read_t<Tape>>,
    void
>> {};


using machine_instance = machine<state::start, new_tape_t>;

#endif