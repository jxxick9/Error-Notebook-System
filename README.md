# Error-Notebook-System
A student error-tracking notebook system built with Modern C++. Features strict Object-Oriented encapsulation, memory management via Smart Pointers, and individual data persistence for each student profile.

## Key Features

1. **User Authentication & Management**: Supports secure multi-student registration, login, and logout functionalities. 
2. **Comprehensive Error Item Tracking**: Allows students to add and delete recorded mistakes. Each entry contains descriptions, custom failure analysis, difficulty ratings (`EASY`, `MEDIUM`, `HARD`), error classifications (`CONCEPT`, `CALCULATION`, `CARELESS`), and subject routing (`MATH`, `PHYSICS`, `CHEMISTRY`).
3. **Advanced Querying & Metrics**: Enables real-time sorting by timestamps (newest/oldest first) and conditional data filtering via strong-typed enumerations.
4. **Isolated Data Persistence**: 
   - Global user registries are maintained inside `global_users.txt`.
   - Each individual's notebook is encapsulated and saved in a designated text format: `notebook_<username>.txt`.


## Project Structure

- `User.h` / `User.cpp`: Manages profile instantiation and encapsulates credential matching.
- `ErrorItem.h` / `ErrorItem.cpp`: Defines target error objects utilizing `enum class` schemas and timestamp tagging.
- `SystemManager.h` / `SystemManager.cpp`: Act as the core system orchestrator handling user business logic, collections, and backend I/O operations.
- `main.cpp`: Presents an interactive, English-based Command-Line App dashboard.


## Building and Running

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
./error_notebook
