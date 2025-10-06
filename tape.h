#ifndef TAPE_H
#define TAPE_H

#include <type_traits>

template <typename... Types>
struct tape_fragment {};

template <typename T1, typename T2, typename T3>
struct tape {};

namespace tape_symbol {
    struct blank {};
};

struct new_blank_tape : std::type_identity<tape<tape_fragment<>, tape_symbol::blank, tape_fragment<>>> {};

using new_blank_tape_t = typename new_blank_tape::type;

template <typename T>
struct header_read {};

template <typename... Types1, typename T, typename... Types2>
struct header_read<tape<tape_fragment<Types1...>, T, tape_fragment<Types2...>>> : std::type_identity<T> {};

template <typename T>
using header_read_t = typename header_read<T>::type;

template <typename T1, typename T2>
struct header_write {};

template <typename New, typename... Types1, typename T, typename... Types2>
struct header_write<New, tape<tape_fragment<Types1...>, T, tape_fragment<Types2...>>> : std::type_identity<tape<tape_fragment<Types1...>, New, tape_fragment<Types2...>>> {};

template <typename New, typename Tape>
using header_write_t = typename header_write<New, Tape>::type;

template <typename T>
struct header_stay : std::type_identity<T> {};

template <typename T>
using header_stay_t = typename header_stay<T>::type;

template <typename T>
struct header_right {};

template <typename... Types1, typename T>
struct header_right<tape<tape_fragment<Types1...>, T, tape_fragment<>>> : std::type_identity<tape<tape_fragment<T, Types1...>, tape_symbol::blank, tape_fragment<>>> {};

template <typename... Types1, typename T1, typename T2, typename... Types2>
struct header_right<tape<tape_fragment<Types1...>, T1, tape_fragment<T2, Types2...>>> : std::type_identity<tape<tape_fragment<T1, Types1...>, T2, tape_fragment<Types2...>>> {};

template <typename T>
using header_right_t = typename header_right<T>::type;

template <typename T>
struct header_left {};

template < typename T, typename... Types1>
struct header_left<tape<tape_fragment<>, T, tape_fragment<Types1...>>> : std::type_identity<tape<tape_fragment<>, tape_symbol::blank, tape_fragment<T, Types1...>>> {};

template <typename... Types1, typename T1, typename T2, typename... Types2>
struct header_left<tape<tape_fragment<T1, Types1...>, T2, tape_fragment<Types2...>>> : std::type_identity<tape<tape_fragment<Types1...>, T1, tape_fragment<T2, Types2...>>> {};

template <typename T>
using header_left_t = typename header_left<T>::type;

namespace direction {
    struct stay {};
    struct go_left {};
    struct go_right {};
};

template <typename Direction, typename Tape>
struct move_header : std::conditional_t<
    std::is_same_v<Direction, direction::stay>,
    header_stay<Tape>,
        std::conditional_t<
            std::is_same_v<Direction, direction::go_left>,
            header_left<Tape>,
            std::conditional_t<
                std::is_same_v<Direction, direction::go_right>,
                header_right<Tape>,
                std::enable_if<false>
            >
        >
> {};

template <typename Direction, typename Tape>
using move_header_t = typename move_header<Direction, Tape>::type;


template <typename... Types>
struct new_tape : std::type_identity<
    header_right_t<
        tape<tape_fragment<>, tape_symbol::blank, tape_fragment<Types...>>
    >
> {};

template <typename... Types>
using new_tape_t = typename new_tape<Types...>::type;

#endif