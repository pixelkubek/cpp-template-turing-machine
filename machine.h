#ifndef MACHINE_H
#define MACHINE_H

#include "tape.h"


struct state {
    struct start {};
    struct accept {};
    struct reject {};
};

struct direction {
    struct stay {};
    struct go_left {};
    struct go_right {};
};

template <typename State, typename TapeContent>
struct next {};

template <typename New, typename Instruction>
struct instruction {};

template <typename New, typename Instruction>
using program = std::type_identity<instruction<New, Instruction>>;

template <>
struct next<state::start, blank> : program<state::accept, blank> {};

static_assert(next<state::start, blank>::type)


template <typename State, typename Tape>
struct machine {};

using machine_instance = machine<state::start, new_tape_t>;

#endif