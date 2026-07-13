## Phase 1: Structural Prototyping

* 目標： 建立清晰的物件導向（OOP）架構，用以處理使用者與錯誤項目。
* AI 協作： 引導 AI 生成 `User`、`ErrorItem` 及 `SystemManager` 的類別結構，並引入智慧指標（`std::shared_ptr`）與時間戳記工具（`std::chrono`），生成標準的標頭檔定義與程式碼骨架。



## Phase 2: Runtime Logic Debugging

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
