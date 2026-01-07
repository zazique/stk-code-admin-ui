#include "replay/replay_merger.hpp"
#include "replay/replay_play.hpp"
#include "io/file_manager.hpp"
#include "utils/log.hpp"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

bool ReplayMerger::merge(int id1, int id2)
{
	const ReplayPlay::ReplayData& rd1 = ReplayPlay::get()->getReplayData(id1);
    const ReplayPlay::ReplayData& rd2 = ReplayPlay::get()->getReplayData(id2);
	if (rd1.m_track_name != rd2.m_track_name || rd1.m_laps != rd2.m_laps) {
		Log::error("ReplayMerger", "Incompatible replays! Track or Laps mismatch.");
		return false;
	}
    std::string path1 = file_manager->getReplayDir() + ReplayPlay::get()->getReplayData(id1).m_filename;
    std::string path2 = file_manager->getReplayDir() + ReplayPlay::get()->getReplayData(id2).m_filename;

    std::ifstream file1(path1);
    std::ifstream file2(path2);

    if (!file1.is_open() || !file2.is_open()) return false;

    std::string outPath = file_manager->getReplayDir() + getNextMergedFilename();
    std::ofstream outFile(outPath);

    std::vector<std::string> kart_lines_from_2;
    std::string line;
    std::stringstream all_data_from_2;
    bool found_first_size = false;

    while (std::getline(file2, line)) {
        if (line.find("kart:") == 0 || line.find("kart_color:") == 0) {
            kart_lines_from_2.push_back(line);
            continue;
        }

        if (!found_first_size && line.find("size:") == 0) {
            found_first_size = true;
        }

        if (found_first_size) {
            all_data_from_2 << line << "\n";
        }
    }
	
	srand(time(NULL));
    uint64_t new_uid = ((uint64_t)rand() << 32) | rand();
	
    file1.clear();
    file1.seekg(0);
    while (std::getline(file1, line)) {
		if (line.find("replay_uid:") == 0) {
            outFile << "replay_uid: " << new_uid << "\n";
            continue;
        }
		
        if (line.find("kart_list_end") == 0) {
            for (const auto& kl : kart_lines_from_2) {
                outFile << kl << "\n";
            }
        }
        outFile << line << "\n";
    }

    outFile << all_data_from_2.str();

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
