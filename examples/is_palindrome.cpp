#include "../macros.h"

// Recognise even-length palindromes over the alphabet {A, B}

ADD_TAPE_SYMBOL(A);
ADD_TAPE_SYMBOL(B);

ADD_STATE(GO_RIGHT_A);
ADD_STATE(GO_RIGHT_B);

ADD_STATE(FOUND_END_A);
ADD_STATE(FOUND_END_B);

ADD_STATE(OVER_LAST_A);
ADD_STATE(OVER_LAST_B);

ADD_STATE(GO_LEFT);
ADD_STATE(FOUND_BEGIN);

ADD_TRANSITION(start, blank, accept, blank, stay);
ADD_TRANSITION(start, A, GO_RIGHT_A, blank, go_right);
ADD_TRANSITION(start, B, GO_RIGHT_B, blank, go_right);

ADD_TRANSITION(GO_RIGHT_A, A, GO_RIGHT_A, A, go_right);
ADD_TRANSITION(GO_RIGHT_A, B, GO_RIGHT_A, B, go_right);

ADD_TRANSITION(GO_RIGHT_B, A, GO_RIGHT_B, A, go_right);
ADD_TRANSITION(GO_RIGHT_B, B, GO_RIGHT_B, B, go_right);

ADD_TRANSITION(GO_RIGHT_A, blank, FOUND_END_A, blank, go_left);
ADD_TRANSITION(GO_RIGHT_B, blank, FOUND_END_B, blank, go_left);

ADD_TRANSITION(FOUND_END_A, A, GO_LEFT, blank, go_left);
ADD_TRANSITION(FOUND_END_B, B, GO_LEFT, blank, go_left);

ADD_TRANSITION(GO_LEFT, A, GO_LEFT, A, go_left);
ADD_TRANSITION(GO_LEFT, B, GO_LEFT, B, go_left);

ADD_TRANSITION(GO_LEFT, blank, start, blank, go_right);

ADD_TRANSITION(accept, blank, accept, blank, stay);

RUN_EMPTY();
RUN_WITH_TAPE(A, A);
RUN_WITH_TAPE(A, B, B, A);
RUN_WITH_TAPE(A, B, B, A, A, B, B, A);

RUN_WITH_TAPE(A, B, B, B);
RUN_WITH_TAPE(A, B);
RUN_WITH_TAPE(A, B, A, B);
RUN_WITH_TAPE(A, B, A);
