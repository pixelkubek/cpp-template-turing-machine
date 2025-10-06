#include "../macros.h"

ADD_TAPE_SYMBOL(unit);

ADD_STATE(zero);
ADD_STATE(one);
ADD_STATE(two);

ADD_TRANSITION(start, blank, accept, blank, stay);
ADD_TRANSITION(start, unit, one, blank, go_right);
ADD_TRANSITION(one, unit, two, blank, go_right);
ADD_TRANSITION(two, unit, zero, blank, go_right);
ADD_TRANSITION(zero, unit, one, blank, go_right);
ADD_TRANSITION(zero, blank, accept, blank, stay);
ADD_TRANSITION(accept, blank, accept, blank, stay);

RUN_EMPTY();
RUN_WITH_TAPE(unit, unit, unit);
RUN_WITH_TAPE(unit, unit, unit, unit, unit, unit);

// RUN_WITH_TAPE(unit, unit, unit, unit, unit);
// RUN_WITH_TAPE(unit);