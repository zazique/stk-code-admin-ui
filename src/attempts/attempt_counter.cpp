#include "attempts/attempt_counter.hpp"
#include "io/xml_node.hpp"
#include "io/file_manager.hpp"
#include "config/user_config.hpp"
#include "utils/file_utils.hpp"
#include "utils/log.hpp"
#include <fstream>

AttemptCounter* AttemptCounter::get()
{
    static AttemptCounter instance;
    return &instance;
}

AttemptCounter::AttemptCounter()
{
    load();
}

void AttemptCounter::addAttempt(const std::string& track_id)
{
    if (track_id.empty()) return;
    m_stats[track_id]++;
    save();
}

int AttemptCounter::getAttempts(const std::string& track_id)
{
    auto it = m_stats.find(track_id);
    return (it != m_stats.end()) ? it->second : 0;
}

void AttemptCounter::load()
{
    std::string filepath = file_manager->getUserConfigFile("attempts.xml");
    
    const XMLNode *root = file_manager->createXMLTree(filepath);
    if (!root) return;

    m_stats.clear();
    for (unsigned int i = 0; i < root->getNumNodes(); i++)
    {
        const XMLNode* node = root->getNode(i);
        if (node->getName() == "track")
        {
            std::string id = "";
            int count = 0;
            node->get("id", &id);
            node->get("count", &count);
            if (!id.empty()) m_stats[id] = count;
        }
    }
    delete root;
}

void AttemptCounter::save()
{
    std::string filepath = file_manager->getUserConfigFile("attempts.xml");
    
    std::string temp_path = filepath + "new";
    std::ofstream configfile(FileUtils::getPortableWritingPath(temp_path).c_str());

    if (!configfile.is_open())
    {
        Log::error("AttemptCounter", "Failed to open %s for writing", temp_path.c_str());
        return;
    }

    configfile << "<?xml version=\"1.0\"?>\n";
    configfile << "<attempts version=\"1\">\n";
    
    for (auto const& pair : m_stats)
    {
        configfile << "    <track id=\"" << pair.first 
                   << "\" count=\"" << pair.second << "\" />\n";
    }

    configfile << "</attempts>\n";
    configfile.close();

    file_manager->removeFile(filepath);
    FileUtils::renameU8Path(temp_path, filepath);
}
