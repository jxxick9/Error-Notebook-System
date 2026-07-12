#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

class User {
public:
    // 建構子
    User(const string& uname, const string& pwdHash, const string& name);

    // Getters
    string getUsername() const { return username; }
    string getStudentName() const { return studentName; }

    // 驗證密碼（封裝核心：外部程式無法得知 passwordHash，只能透過此介面比對）
    bool authenticate(const string& inputPassword) const;

    std::string getPasswordHash() const { return passwordHash; }

private:
    string username;     // 登入帳號（同時作為個人檔案命名的依據）
    string passwordHash; // 密碼雜湊值（或明文，實務上建議用 Hash 隱蔽）
    string studentName;   // 學生真實姓名
};

#endif // USER_H
