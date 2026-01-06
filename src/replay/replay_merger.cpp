#include "replay/replay_merger.hpp"
#include "replay/replay_play.hpp"
#include "io/file_manager.hpp"
#include "utils/log.hpp"
#include <fstream>
#include <sstream>

bool ReplayMerger::merge(int id1, int id2)
{
    std::string path1 = file_manager->getReplayDir() + ReplayPlay::get()->getReplayData(id1).m_filename;
    std::string path2 = file_manager->getReplayDir() + ReplayPlay::get()->getReplayData(id2).m_filename;

    std::ifstream file1(path1);
    std::ifstream file2(path2);

    if (!file1.is_open() || !file2.is_open()) return false;

    std::string outPath = file_manager->getReplayDir() + getNextMergedFilename();
    std::ofstream outFile(outPath);

    std::vector<std::string> kart_lines_from_2;
    std::vector<std::string> data_lines_from_2;
    std::string line;

    bool collecting_data = false;
    while (std::getline(file2, line)) {
        if (line.find("kart:") == 0 || line.find("kart_color:") == 0) {
            kart_lines_from_2.push_back(line);
        }
        if (collecting_data) {
            if (!line.empty()) data_lines_from_2.push_back(line);
        }
        if (line.find("size:") == 0) {
            collecting_data = true;
            data_lines_from_2.push_back(line); 
        }
    }

    file1.clear();
    file1.seekg(0);
    while (std::getline(file1, line)) {
        if (line.find("kart_list_end") == 0) {
            for (const auto& kl : kart_lines_from_2) outFile << kl << "\n";
        }
        outFile << line << "\n";
    }

    for (const auto& dl : data_lines_from_2) {
        outFile << dl << "\n";
    }

    Log::info("ReplayMerger", "Successfully merged into %s", outPath.c_str());
    return true;
}

std::string ReplayMerger::getNextMergedFilename() {
    int index = 1;
    while (true) {
        std::string name = "merged" + std::to_string(index) + ".replay";
        if (!file_manager->fileExists(file_manager->getReplayDir() + name)) {
            return name;
        }
        index++;
    }
}
