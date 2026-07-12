#ifndef ERROR_ITEM_H
#define ERROR_ITEM_H

#include <string>
#include <chrono>

using namespace std;

class ErrorItem {
public:

    enum class Difficulty { EASY, MEDIUM, HARD };
    enum class ErrorType  { CONCEPT, CALCULATION, CARELESS };
    enum class Subject    { MATH, PHYSICS, CHEMISTRY };

  
    ErrorItem(int id, const string& desc, const string& reason, 
              Difficulty diff, ErrorType type, Subject sub, long long ts);


    int getId() const { return id; }
    string getDescription() const { return description; }
    string getWrongReason() const { return wrongReason; }
    Difficulty getDifficulty() const { return difficulty; }
    ErrorType getErrorType() const { return errorType; }
    Subject getSubject() const { return subject; }
    long long getTimestamp() const { return timestamp; }


    void updateWrongReason(const string& newReason);
    void updateDifficulty(Difficulty newDiff);

private:
    int id;
    string description;
    string wrongReason;
    Difficulty difficulty;
    ErrorType errorType;
    Subject subject;
    long long timestamp; 
};

#endif // ERROR_ITEM_H
