# Project 23: Grain dryer — SPEC

Device type B, process sequencer. Key K1, second structure S2, report Q5.

This is the first version (HW2): the states and the events. The transition
table comes in week 5.

## States

The states are given by the project sheet.

| State   | Meaning                 | AUGER | BURNER     | FAN |
|---------|-------------------------|-------|------------|-----|
| IDLE    | empty (initial state)   | off   | off        | off |
| LOADING | auger filling the bin   | on    | off        | off |
| DRYING  | burner and fan on       | off   | on below 58.0 C, off at 60.0 C | on  |
| COOLING | fan on, burner off      | off   | off        | on  |
| UNLOAD  | unload auger running    | on    | off        | off |

## Events

The events the dryer reacts to. Each one comes from the switch register or
from a sensor reading.

| Event       | Source                         | Meaning                                         |
|-------------|--------------------------------|-------------------------------------------------|
| LOAD        | switch 0, press (0 to 1)       | command: start loading                          |
| UNLOAD_CMD  | switch 1, press (0 to 1)       | command: unload                                 |
| BIN_FULL    | switch 2, level                | the bin is full                                 |
| BIN_EMPTY   | switch 3, level                | the bin is empty                                |
| TEMP_LOW    | temperature below 58.0 C       | burner on (DRYING holds 60.0 C)                 |
| TEMP_HIGH   | temperature at or above 60.0 C | burner off                                      |
| DRY_DONE    | humidity below 30.0 %RH        | drying is finished: go to COOLING               |
| COOL_DONE   | temperature below 30.0 C       | cooling is finished                             |
| OVERTEMP    | temperature above 75.0 C       | rule 3: burner off, back to IDLE                |

Commands (LOAD, UNLOAD_CMD) that the dryer cannot accept in its current
state wait in the command queue (aux) until it can (rule 1).

## Open decisions (to settle before the transition table, week 5)

- Where the dryer goes when COOLING ends and no UNLOAD_CMD is waiting.
- When a queued UNLOAD_CMD is served if it arrives during DRYING.
- What LOAD does when the dryer is not in IDLE.
- BIN_FULL already on before LOAD.
- Humidity rising again during COOLING.
- Rule 3 outside DRYING, and IDLE ("empty") after rule 3 with a full bin.
- Which side of each threshold is which (for example, is 30.0 %RH "below 30"?).
- Where the press detection (previous switch value) lives: fsm.c or main.c.
