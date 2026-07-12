#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include "User.h"
#include "ErrorItem.h"

using namespace std;

class SystemManager {
public:
    SystemManager();
    ~SystemManager();

    bool registerUser(const string& uname, const string& pwd, const string& name);
    bool login(const string& uname, const string& pwd);
    void logout();
    bool isCurrentLoggedIn() const { return currentUser != nullptr; }
    shared_ptr<User> getCurrentUser() const { return currentUser; }

    void addErrorNotebookItem(const string& desc, const string& reason,
                              ErrorItem::Difficulty diff, ErrorItem::ErrorType type, ErrorItem::Subject sub);
    void deleteErrorNotebookItem(int itemId);


    vector<shared_ptr<ErrorItem>> getErrorsSortedByTime(bool ascending = false) const;
    vector<shared_ptr<ErrorItem>> filterByDifficulty(ErrorItem::Difficulty diff) const;
    vector<shared_ptr<ErrorItem>> filterByErrorType(ErrorItem::ErrorType type) const;


    bool loadGlobalUsers(); 
    bool saveGlobalUsers();

private:
    vector<shared_ptr<User>> globalUsers;            // 系統所有註冊學生名單
    vector<shared_ptr<ErrorItem>> currentNotebook;   // 當前登入學生的錯題本
    shared_ptr<User> currentUser;                    // 目前登入的使用者指標 (未登入則為 nullptr)

    std::string getStudentFileName(const string& uname) const;
    bool loadStudentNotebook(const string& uname);
    bool saveStudentNotebook(const string& uname);
};

#endif // SYSTEM_MANAGER_H
