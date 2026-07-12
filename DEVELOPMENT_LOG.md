## Phase 1: Structural Prototyping
*   **Objective:** Set up a clean OOP structure to handle users and error entries.
*   **AI Collaboration:** Prompted AI to generate class schemas for `User`, `ErrorItem`, and `SystemManager` incorporating smart pointers (`std::shared_ptr`) and `std::chrono` for timestamping.
*   **Outcome:** Successfully generated standard header definitions and code skeletons.

---

## Phase 2: Environment & Toolchain Debugging (Independent)
*   **Issue Encountered:** `CMake Error: The source directory "C:/Users/YJ Chen" does not appear to contain CMakeLists.txt.`
*   **Root Cause Analysis:** The Windows user directory contains a space (`YJ Chen`). When calling `cmake ..`, the PowerShell command-line arguments split at the space character, breaking the relative path parsing and causing CMake to look for a non-existent directory.
*   **Resolution Strategy:** 
    1. Isolated the build environment entirely from the localized OneDrive/User tree.
    2. Relocated the project workspace to a strict, space-free absolute directory tree (`C:\ErrorNotebookSystem`).
    3. Flushed the corrupted master caches (`Remove-Item C:\Users\CMakeCache.txt`).
    4. Regenerated clean Makefiles seamlessly.

---

## Phase 3: Runtime Logic Debugging (Independent)
*   **Issue Encountered:** Newly registered accounts successfully logged out but immediately threw `[!] Login failed` upon attempting to log back in during the same or a fresh session.
*   **Root Cause Analysis:** Inspected `SystemManager.cpp` and identified a fatal logic flaw in `saveGlobalUsers()`:
    ```cpp
    outfile << u->getUsername() << " " << u->authenticate(u->getUsername()) << "\n";
    ```
    The code mistakenly invoked the boolean validation function `authenticate()` during data serialization. Because it passed the username string into a password validator, it consistently evaluated to `false`, overwriting the student's password with `0` in the text registry.
*   **Resolution Strategy:**
    1. Refactored `User.h` to include an explicit constant encapsulation getter: `std::string getPasswordHash() const`.
    2. Rewrote the serialization engine inside `SystemManager::saveGlobalUsers()` to properly dump raw hashes instead of boolean flags.
    3. Purged the corrupted database file, recompiled using `mingw32-make`, and successfully ran end-to-end integration tests.
