# ⏱️ Digital Clock & Timer Suite (C)

A comprehensive, flicker-free, cross-platform command-line time management suite written in pure C. It features a real-time clock, countdown timer, drift-free stopwatch, and an alarm system with native audio alerts.

## Features

- **Real-Time Clock**: Displays current system time and date with live updates.
- **Countdown Timer**: Set custom hours, minutes, and seconds to count down to zero.
- **Drift-Free Stopwatch**: Uses system time (`time.h`) for mathematically precise elapsed time tracking, preventing cumulative `sleep()` drift.
- **Alarm System**: Set a specific 24-hour time to trigger a native audio alert.
- **Cross-Platform**: Seamlessly compiles and runs on Windows, Linux, and macOS using conditional compilation (`#ifdef _WIN32`).
- **Flicker-Free Rendering**: Utilizes ANSI escape sequences for clean, efficient terminal screen clearing.
- **Graceful Exit Handling**: Catches `Ctrl+C` signals to safely return to the main menu instead of abruptly crashing.
- **Zero External Dependencies**: Relies solely on the C Standard Library and native OS APIs.

## Build and Run

### Prerequisites
- A C compiler (GCC, Clang, or MSVC).

### Linux / macOS
```bash
# Clone the repository
git clone https://github.com/abdullahaljehan-me/digital-clock-timer-c.git
cd digital-clock-timer-c

# Compile
gcc -o timer digital_clock_timer.c

# Run
./timer
