#include "../macros.h"

ADD_STATE(moved_right);
ADD_STATE(moved_back);
ADD_TAPE_SYMBOL(sym);

ADD_TRANSITION(start, blank, moved_right, sym, go_right);
ADD_TRANSITION(moved_right, blank, moved_back, blank, go_left);
ADD_TRANSITION(moved_back, sym, accept, blank, stay);
ADD_TRANSITION(accept, blank, accept, blank, stay);

ADD_TRANSITION(start, sym, reject, blank, stay);
ADD_TRANSITION(reject, blank, reject, blank, stay);

RUN_WITH_TAPE(blank);