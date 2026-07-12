#include <string>
#include <chrono>
#include "ErrorItem.h"
using namespace std;

ErrorItem::ErrorItem(int id, const string& desc, const string& reason, 
    Difficulty diff, ErrorType type, Subject sub, long long ts)
    : id(id), description(desc), wrongReason(reason), 
      difficulty(diff), errorType(type), subject(sub), timestamp(ts) {
}

void ErrorItem::updateWrongReason(const string& newReason){
    wrongReason = newReason;
}

void ErrorItem::updateDifficulty(Difficulty newDiff){
    difficulty = newDiff;
}
