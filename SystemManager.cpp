#include <vector>
#include <string>
#include <memory>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "SystemManager.h"
using namespace std;

SystemManager::SystemManager(){
    loadGlobalUsers();
}

SystemManager::~SystemManager(){
    if (currentUser) {
        saveStudentNotebook(currentUser->getUsername());
    }
    saveGlobalUsers();
}

bool SystemManager::registerUser(const string& uname, const string& pwd, const string& name){
    for (const auto& u : globalUsers) {
        if (u->getUsername() == uname) return false;
    }
    globalUsers.push_back(make_shared<User>(uname, pwd, name));
    saveGlobalUsers();
    return true;
}

bool SystemManager::login(const string& uname, const string& pwd){
    for (const auto& u : globalUsers) {
        if (u->getUsername() == uname && u->authenticate(pwd)) {
            if (currentUser) {
                saveStudentNotebook(currentUser->getUsername());
            }
            currentUser = u;
            loadStudentNotebook(uname);
            return true;
        }
    }
    return false;
}

void SystemManager::logout(){
    if (currentUser) {
        saveStudentNotebook(currentUser->getUsername());
        currentUser = nullptr;
        currentNotebook.clear();
    }
}

void SystemManager::addErrorNotebookItem(const string& desc, const string& reason,
    ErrorItem::Difficulty diff, ErrorItem::ErrorType type, ErrorItem::Subject sub){
    if (!currentUser) return;
    
    int newId = 1;
    if (!currentNotebook.empty()) {
        int maxId = 0;
        for (const auto& item : currentNotebook) {
            if (item->getId() > maxId) maxId = item->getId();
        }
        newId = maxId + 1;
    }
    
    long long ts = chrono::duration_cast<chrono::seconds>(
        chrono::system_clock::now().time_since_epoch()).count();
        
    currentNotebook.push_back(make_shared<ErrorItem>(newId, desc, reason, diff, type, sub, ts));
    saveStudentNotebook(currentUser->getUsername());
}

void SystemManager::deleteErrorNotebookItem(int itemId){
    if (!currentUser) return;
    auto it = remove_if(currentNotebook.begin(), currentNotebook.end(),
        [itemId](const shared_ptr<ErrorItem>& item) { return item->getId() == itemId; });
    if (it != currentNotebook.end()) {
        currentNotebook.erase(it, currentNotebook.end());
        saveStudentNotebook(currentUser->getUsername());
    }
}

vector<shared_ptr<ErrorItem>> SystemManager::getErrorsSortedByTime(bool ascending) const{
    vector<shared_ptr<ErrorItem>> sortedList = currentNotebook;
    sort(sortedList.begin(), sortedList.end(), [ascending](const shared_ptr<ErrorItem>& a, const shared_ptr<ErrorItem>& b) {
        return ascending ? (a->getTimestamp() < b->getTimestamp()) : (a->getTimestamp() > b->getTimestamp());
    });
    return sortedList;
}

vector<shared_ptr<ErrorItem>> SystemManager::filterByDifficulty(ErrorItem::Difficulty diff) const{
    vector<shared_ptr<ErrorItem>> filteredList;
    for (const auto& item : currentNotebook) {
        if (item->getDifficulty() == diff) filteredList.push_back(item);
    }
    return filteredList;
}

vector<shared_ptr<ErrorItem>> SystemManager::filterByErrorType(ErrorItem::ErrorType type) const{
    vector<shared_ptr<ErrorItem>> filteredList;
    for (const auto& item : currentNotebook) {
        if (item->getErrorType() == type) filteredList.push_back(item);
    }
    return filteredList;
}

string SystemManager::getStudentFileName(const string& uname) const {
    return "notebook_" + uname + ".txt";
}

bool SystemManager::loadGlobalUsers(){
    globalUsers.clear();
    ifstream infile("global_users.txt");
    if (!infile.is_open()) return false;
    string uname, pwdHash, name;
    while (infile >> uname >> pwdHash) {
        infile.ignore();
        getline(infile, name);
        if (!uname.empty() && !pwdHash.empty() && !name.empty()) {
            globalUsers.push_back(make_shared<User>(uname, pwdHash, name));
        }
    }
    infile.close();
    return true;
}
    
bool SystemManager::saveGlobalUsers(){
    ofstream outfile("global_users.txt");
    if (!outfile.is_open()) return false;
    for (const auto& u : globalUsers) {
        outfile << u->getUsername() << " " << u->getPasswordHash() << "\n" << u->getStudentName() << "\n";
    }
    outfile.close();
    return true;
}

bool SystemManager::loadStudentNotebook(const string& uname) {
    currentNotebook.clear();
    ifstream infile(getStudentFileName(uname));
    if (!infile.is_open()) return false;
    string line;
    while (getline(infile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        int id, diffVal, typeVal, subVal;
        long long ts;
        string desc, reason;
        
        ss >> id >> diffVal >> typeVal >> subVal >> ts;
        ss.ignore();
        getline(ss, desc, '|');
        getline(ss, reason);
        
        currentNotebook.push_back(make_shared<ErrorItem>(
            id, desc, reason, 
            static_cast<ErrorItem::Difficulty>(diffVal),
            static_cast<ErrorItem::ErrorType>(typeVal),
            static_cast<ErrorItem::Subject>(subVal),
            ts
        ));
    }
    infile.close();
    return true;
}

bool SystemManager::saveStudentNotebook(const string& uname) {
    ofstream outfile(getStudentFileName(uname));
    if (!outfile.is_open()) return false;
    for (const auto& item : currentNotebook) {
        outfile << item->getId() << " "
                << static_cast<int>(item->getDifficulty()) << " "
                << static_cast<int>(item->getErrorType()) << " "
                << static_cast<int>(item->getSubject()) << " "
                << item->getTimestamp() << " "
                << item->getDescription() << "|"
                << item->getWrongReason() << "\n";
    }
    outfile.close();
    return true;
}
