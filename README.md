# Error Notebook System

A robust, localized Error Notebook System designed for students to track, analyze, and review their academic mistakes. Built with modern C++ Object-Oriented Programming (OOP) principles, this application features multi-user authentication, localized file persistence, and advanced data filtering.

## AI-Assisted Architecture & Independent Development Statement

This project was developed using a modern **AI-assisted engineering workflow**. The boilerplate object architecture and system skeleton were generated via AI prompting, while all **system debugging, toolchain environment troubleshooting, and core logical corrections were executed independently by the developer**.

During the integration phase, the developer identified and resolved two critical, game-breaking bottlenecks:
1. **Windows Toolchain & Path Resolution Fix**: Diagnosed and resolved a deep-seated CMake configuration failure caused by Windows directory path spaces (`YJ Chen`), fixing cache gridlocks by decoupling the build space from the user folder.
2. **State Persistence Logic Rectification**: Discovered a critical logic bug in `SystemManager::saveGlobalUsers()` where a boolean validation method was mistakenly utilized for file writes, causing passwords to be saved as `0`. Rectified the issue by engineering proper encapsulation getters in the `User` class.

---

## Core Architecture & Technical Highlights

*   **Modern C++ Memory Management**: Utilizes `std::shared_ptr` smart pointers extensively to manage `User` and `ErrorItem` lifecycles, completely mitigating potential Memory Leaks.
*   **Strongly-Typed Enumerations**: Employs `enum class` scopes for problem difficulties, error types, and subjects to prevent global namespace pollution and maintain strict type safety.
*   **Decoupled File Persistence**: Implements a dedicated file IO pipeline where each user's data is isolated into an individual `notebook_[username].txt` matrix, showcasing micro-data management principles.

---

## Project Blueprint

| File Name | Functional Description |
| :--- | :--- |
| `main.cpp` | System entry point, managing interactive console loop UI logic. |
| `SystemManager.h / .cpp` | User authentication core, notebook business logic, and file IO streams. |
| `User.h / .cpp` | Student account object encapsulation (username, password hash, real name). |
| `ErrorItem.h / .cpp` | Error entry structure containing type enums and Unix timestamp trackers. |
| `CMakeLists.txt` | Central CMake compilation configuration script. |

---

## Compilation & Execution Guide

To bypass command-line path parsing issues on Windows, it is highly recommended to place the repository in a space-free directory (e.g., `C:\ErrorNotebookSystem`):

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
.\error_notebook.exe
