# CPP-TEMPLATE-TURING-MACHINE
This project allows running an arbitrary deterministic Turing machine, using only C++'s types and templates.
All the logic is handled by template specializations, thus proving that C++ templates are Turing-complete.
The machine, tape, machine states, tape symbols are just types.
The machine is programed by providing template specializations for specific types.

# Defining a Turing machine
In order to define a Turing machine, helper macros are provided in `macros.h`.

```CPP
ADD_STATE(state_name);
```
This macro allows to add a new state to the machine. Note that `start`, `accept` and `reject` states are already provided and shouldn't be user-defined.

```CPP
ADD_TAPE_SYMBOL(symbol_name);
```
Add a symbol which can be stored in the tape. Note that the `blank` symbol is already provided.

```CPP
ADD_TRANSITION(from_state, from_symbol, to_state, to_symbol, to_direction);
```
Add a transition to the machine, when the machine is in the state `from_state` and the tape symbol under the header is `from_symbol`, write `to_symbol` under the header, change state to `to_state` and move in `to_direction`, which should be one of the following: `stay`, `go_left`, `go_right`.

```CPP
RUN_WITH_TAPE(...);
RUN_EMPTY();
```
Set the initial tape content, or a blank tape respectively.
In the first function, provide the initial tape contents with comma separated tape symbols (at least one).

# Running a Turing machine
To run the Turing machine run the following command
```BASH
g++ -std=c++20 -c <source_file_name>
```

If the program compiles, the machine accepts the tape contents, if it fails to compile it rejects it.
Note that the compilation may never terminate, as the simulated machine is subject to the halting problem.