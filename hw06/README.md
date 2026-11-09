# HW6: The device loop

`replay` reads a scenario file and plays it back through the iom361 hardware
model, one tick per second. Each tick it sets the "world" (sensor and switches),
reads the sensor and switches through iom361's registers, toggles LED k for
every switch k that was just pressed, and prints one trace line in UTC:

    2026-10-06 08:00:02 temp=21.5 rh=40.0 switches=0x1 pressed=0x1 leds=0x1

## Build

    make            # builds ./replay with no warnings
    make clean      # removes the .o files, replay, and tests/test_hw06

## Run

    ./replay scenarios/switches.txt

## Test

    make test

This builds and runs the unit tests (`tests/test_hw06`), then runs
`./regress.sh`, which replays every file in `scenarios/` and compares the
output with `expected/<name>.trace` using `diff`. Each test prints PASS or
FAIL, and any failure gives a nonzero exit status.

| Scenario | What it tests |
|---|---|
| `scenarios/switches.txt` | a press, a hold, a release, a second press, and two switches pressed at once |
| `scenarios/sensor.txt` | 91.0 C reading back as 91.0, a negative temperature, values holding between lines, and the date changing at midnight |

## Files

| File | What it does |
|---|---|
| `sensor.h`, `sensor.c` | `reading_t` and `sensor_read`: reads TEMP_REG and HUMID_REG, keeps bits 19..0, converts, rounds to 0.1 |
| `panel.h`, `panel.c` | `panel_pressed`, `panel_released`, and `panel_led` / `panel_toggle` by read-modify-write |
| `scenario.h`, `scenario.c` | loads a scenario file (at most 1000 lines, no malloc) and gives the line in force at a tick |
| `main.c` | the replay loop and the trace |
| `iom361_r4.h`, `iom361_r4.c` | the hardware model, unchanged |
| `tests/test_hw06.c` | unit tests |
| `regress.sh`, `scenarios/`, `expected/` | regression tests |

## Design decisions

- `scenario_load` returns 0 on success, the number of the first wrong line,
  or -1 if the file cannot be opened. A file with no start line or no data
  lines returns the line after the last one, so it is never mistaken for success.
- The first data line must have tick 0, so that a line is in force at every tick.
- `before` starts at 0, so a switch that is already on at tick 0 counts as a press.