#ifndef ATTEMPT_COUNTER_HPP
#define ATTEMPT_COUNTER_HPP

#include <string>
#include <map>

class AttemptCounter {
private:
    std::map<std::string, int> m_stats;

public:
    AttemptCounter();
    void addAttempt(const std::string& track_id);
    int getAttempts(const std::string& track_id);
    static AttemptCounter* get();
    void load();
    void save();
};

extern AttemptCounter* attempt_counter;

#endif
