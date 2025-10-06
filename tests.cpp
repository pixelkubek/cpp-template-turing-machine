#include "tape.h"
#include "machine.h"

// HEADER READ tests
static_assert(std::is_same_v<header_read_t<new_blank_tape_t>, tape_symbol::blank>);

// HEADER WRITE tests
using test_tape = new_blank_tape_t;
using written_test_tape = header_write_t<int, test_tape>;

static_assert(std::is_same_v<written_test_tape, tape<tape_fragment<>, int, tape_fragment<>>>);

// HEADER STAY tests
static_assert(std::is_same_v<written_test_tape, header_stay_t<written_test_tape>>);

// HEADER RIGHT tests
static_assert(std::is_same_v<header_right_t<tape<tape_fragment<int>, long, tape_fragment<double>>>, tape<tape_fragment<long, int>, double, tape_fragment<>>>);
static_assert(std::is_same_v<header_right_t<tape<tape_fragment<int>, long, tape_fragment<>>>, tape<tape_fragment<long, int>, tape_symbol::blank, tape_fragment<>>>);

// HEADER LEFT tests
static_assert(std::is_same_v<header_left_t<tape<tape_fragment<int>, long, tape_fragment<double>>>, tape<tape_fragment<>, int, tape_fragment<long, double>>>);
static_assert(std::is_same_v<header_left_t<tape<tape_fragment<int>, long, tape_fragment<>>>, tape<tape_fragment<>, int, tape_fragment<long>>>);

