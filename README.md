# Error Notebook System

一個專為學生設計、具備強大在地化功能的錯題本系統，用於追蹤、分析與複習學業上的錯誤。本系統採用現代 C++ 物件導向程式設計（OOP）原則開發，具備多用戶身分驗證、在地化檔案持久化儲存以及進階數據篩選功能。

## AI 輔助架構與獨立開發聲明

本專案採用 AI 輔助進行開發。基礎的物件架構與系統骨架是由 AI 提示詞生成，而所有的系統除錯（Debugging）、工具鏈環境排障，以及核心邏輯修正，皆由開發者獨立執行完成。


## 核心架構與技術亮點

* 現代 C++ 記憶體管理：廣泛使用 `std::shared_ptr` 智慧指標來管理 `User` 與 `ErrorItem` 的生命週期，完全杜絕了潛在的記憶體洩漏。
* 強型態列舉：針對題目難度、錯誤類型與學科採用了具備作用域的 `enum class`，以防止全域命名空間污染並維持嚴格的型態安全。
* 解耦的檔案持久化：實作了專用的檔案 IO 管線，將每位使用者的資料獨立隔離到各自的 `notebook_[username].txt` 矩陣中，展現了微型數據管理的原則。

## 專案藍圖

| 檔案名稱 | 功能說明 |
| --- | --- |
| `main.cpp` | 系統入口點，負責管理互動式主控台（Console）的迴圈 UI 邏輯。 |
| `SystemManager.h / .cpp` | 使用者身分驗證核心、錯題本業務邏輯，以及檔案 IO 流。 |
| `User.h / .cpp` | 學生帳號物件封裝（包含使用者名稱、密碼雜湊值、真實姓名）。 |
| `ErrorItem.h / .cpp` | 錯題項目的結構，包含類型列舉與 Unix 時間戳記追蹤器。 |
| `CMakeLists.txt` | 中央 CMake 編譯組態指令碼。 |

## 編譯與執行指南

為了避免 Windows 系統上的命令列路徑解析問題，建議將此專案儲存於不含空格的目錄中（例如：`C:\ErrorNotebookSystem`）：

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
.\error_notebook.exe

```
