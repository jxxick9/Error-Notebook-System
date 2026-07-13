## 簡介

一個結合自身家教經驗，專為家教學生設計的錯題本系統，用於追蹤、分析與複習學業上的錯誤。本系統採用現代 C++ 物件導向程式設計（OOP）原則開發，具備多用戶身分驗證、在地化檔案持久化儲存以及進階數據篩選功能。架構與技術亮點如下：
* 運用繼承（Inheritance）與多型（Polymorphism）建立基底使用者類別，衍生出「家教老師」與「學生/家長」雙端權限，並透過虛擬函式（Virtual Functions）實作統一卻分流的登入與操作介面。
* 實作現代 C++ 記憶體管理，使用 `std::shared_ptr` 智慧指標來管理 `User` 與 `ErrorItem` 的生命週期，完全杜絕了潛在的記憶體洩漏。
* 針對題目難度、錯誤類型與學科採用了具備作用域的 `enum class`，以防止全域命名空間污染並維持嚴格的型態安全。
* 實作了檔案專用的檔案 IO 管線，將每位使用者的資料獨立隔離到各自的 `notebook_[username].txt` 矩陣中，展現了微型數據管理的原則。


## 開發聲明

本專案採用 AI 輔助進行開發。基礎的物件架構與系統骨架是由 AI 提示詞生成，而所有的系統除錯（Debugging）、工具鏈環境排障，以及核心邏輯修正，皆由開發者獨立執行完成。


## 實作偵錯紀錄
* 遇到問題： 新註冊的帳號可以成功登出，但在同一個工作階段或新的工作階段中嘗試重新登入時，會跳出 `[!] Login failed`。
* 根本原因分析： 檢查 `SystemManager.cpp` 後，發現 `saveGlobalUsers()` 中存在邏輯缺陷：
```cpp
outfile << u->getUsername() << " " << u->authenticate(u->getUsername()) << "\n";

```
程式碼在進行資料序列化（存檔）時，誤呼叫了用於布林值驗證的 `authenticate()` 函式。由於它將使用者名稱字串帶入了密碼驗證器中，導致驗證結果恆為 `false`，進而在文字資料庫中將學生的密碼覆寫為 `0`。
* 解決策略：
1. 重構 `User.h`，加入一個明確的常數封裝 Getter 函式：`std::string getPasswordHash() const`。
2. 重寫 `SystemManager::saveGlobalUsers()` 內部的序列化引擎，以正確儲存原始的雜湊值。
3. 清除損壞的資料庫檔案，使用 `mingw32-make` 重新編譯，並成功通過端到端（end-to-end）的整合測試。



## 專案藍圖

| 檔案名稱 | 功能說明 |
| --- | --- |
| `main.cpp` | 系統入口點，負責管理互動式主控台（Console）的迴圈 UI 邏輯。 |
| `SystemManager.h / .cpp` | 使用者身分驗證核心、錯題本業務邏輯，以及檔案 IO 流。 |
| `User.h / .cpp` | 學生帳號物件封裝（包含使用者名稱、密碼雜湊值、真實姓名）。 |
| `ErrorItem.h / .cpp` | 錯題項目的結構，包含類型列舉與 Unix 時間戳記追蹤器。 |
| `CMakeLists.txt` | 中央 CMake 編譯組態指令碼。 |

## 編譯與執行

為了避免 Windows 系統上的命令列路徑解析問題，建議將此專案儲存於不含空格的目錄中（例如：`C:\ErrorNotebookSystem`）：

```bash
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
mingw32-make
.\error_notebook.exe

```
