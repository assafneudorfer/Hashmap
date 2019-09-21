#include <iostream>
#include <fstream>
#include "HashMap.hpp"
#include <algorithm>


/**
 *
 * @param key
 * @param value
 * @param line
 */
void checkLine(std::string *key, int *value, std::string &line)
{
    std::size_t pos = line.find(',');
    *key = line.substr(0, pos);
    std::string str = line.substr(pos + 1);
    if (*key == line)
    {
        std::cerr << "Invalid input" << std::endl;
    }
    std::transform(key->begin(), key->end(), key->begin(), [](unsigned char c)
    { return std::tolower(c); });
    *value = std::stoi(str);
    if (!std::all_of(str.begin(), str.end(), ::isdigit))
    {
        std::cerr << "Invalid input" << std::endl;
        exit(EXIT_FAILURE);
    }


}
/**
 *
 * @param myfile
 * @return
 */
HashMap<std::string, int> *buildData(std::fstream &myfile)
{
    std::string line;
    auto map = new HashMap<std::string, int>();
    while (std::getline(myfile, line))
    {
        std::string key;
        int value;
        checkLine(&key, &value, line);
        map->insert(key, value);

    }
    return map;
}
/**
 *
 * @param line
 * @param key
 * @param value
 * @return
 */
int getScoreforLine(const std::string &line, const std::string &key, int value)
{
    int sum = 0;
    std::size_t pos = line.find(key);
    while (pos != std::string::npos)
    {
        sum += value;
        pos = line.find(key, pos + 1);
    }
    return sum;
}
/**
 *
 * @param myfile
 * @param hashMap
 * @return
 */
int getScore(std::fstream &myfile, HashMap<std::string, int> *hashMap)
{
    int score = 0;
    std::string line;
    while (std::getline(myfile, line))
    {
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c)
        { return std::tolower(c); });
        for (auto it = hashMap->begin(); it != hashMap->end(); ++it)
        {
            std::string key = it->first;
            int value = it->second;
            score += getScoreforLine(line, key, value);
        }

    }
    return score;
}
/**
 *
 * @param data_path
 * @param email_path
 * @param threshold
 */
void mainHelper(const std::string& data_path, const std::string& email_path, int threshold)
{
    int score;
    std::fstream data_file, email_file;
    data_file.open(data_path, std::ios::in);
    email_file.open(email_path, std::ios::in);
    if (!data_file.is_open() || !email_file.is_open())
    {
        exit(EXIT_FAILURE);
    }
    HashMap<std::string, int> *hashMap = buildData(data_file);
    score = getScore(email_file, hashMap);
    delete hashMap;
    data_file.close();
    email_file.close();

    if (score > threshold)
    {
        std::cout << "SPAM" << std::endl;
        return;
    }
    std::cout << "NOT_SPAM" << std::endl;

}

/**
 *
 * @param arg
 * @param argv
 * @return
 */
int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cerr << "Usage: SpamDetector <database path> <message path> <threshold>" << std::endl;
        exit(EXIT_FAILURE);
    }
    int threshold = std::stoi(argv[3]);
    mainHelper(argv[1], argv[2], threshold);


    return 0;

}