#ifndef TAPE_H
#define TAPE_H

#include <type_traits>

template <typename... Types>
struct tape_fragment {};

template <typename T1, typename T2, typename T3>
struct tape {};
// Valid tape tape<tape_fragment<Types1...>, T, tape_fragment<Types2...>>

// template <typename... Types1, typename T, typename... Types2>
// struct tape<tape_fragment<Types1...>, T, tape_fragment<Types2...>> {

// };

struct blank {};

struct new_tape : std::type_identity<tape<tape_fragment<>, blank, tape_fragment<>>> {};

using new_tape_t = typename new_tape::type;

template <typename T>
struct header_read {};

template <typename... Types1, typename T, typename... Types2>
struct header_read<tape<tape_fragment<Types1...>, T, tape_fragment<Types2...>>> : std::type_identity<T> {};

template <typename T>
using header_read_t = typename header_read<T>::type;

static_assert(std::is_same_v<header_read_t<new_tape_t>, blank>);

template <typename T1, typename T2>
struct header_write {};

template <typename New, typename... Types1, typename T, typename... Types2>
struct header_write<New, tape<tape_fragment<Types1...>, T, tape_fragment<Types2...>>> : std::type_identity<tape<tape_fragment<Types1...>, New, tape_fragment<Types2...>>> {};

template <typename New, typename Tape>
using header_write_t = typename header_write<New, Tape>::type;

using test_tape = new_tape_t;
using written_test_tape = header_write_t<int, test_tape>;
static_assert(std::is_same_v<written_test_tape, tape<tape_fragment<>, int, tape_fragment<>>>);

template <typename T>
struct header_stay : std::type_identity<T> {};

template <typename T>
using header_stay_t = typename header_stay<T>::type;

static_assert(std::is_same_v<written_test_tape, header_stay_t<written_test_tape>>);

#endif