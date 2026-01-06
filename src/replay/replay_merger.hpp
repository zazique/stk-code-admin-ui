#ifndef REPLAY_MERGER_HPP
#define REPLAY_MERGER_HPP

#include <string>
#include <vector>

class ReplayMerger
{
public:
    static bool merge(int id1, int id2);
private:
    static std::string getNextMergedFilename();
};

#endif
