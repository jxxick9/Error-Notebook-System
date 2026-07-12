#include <string>
#include "User.h"
using namespace std;

User::User(const string& uname, const string& pwdHash, const string& name)
    : username(uname), passwordHash(pwdHash), studentName(name) {
}

bool User::authenticate(const string& inputPassword) const{
    return passwordHash == inputPassword;
}
