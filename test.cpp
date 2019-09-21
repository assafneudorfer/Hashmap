int main(int argc, char **argv)
{
    std::vector<int> scorevec = {20,0,30,0,0,15,15,0,35};
    std::vector<int> resultvec;
    struct dirent *entry = nullptr;
    DIR *dp = nullptr;
    std::string data;
    std::string email;
    dp = opendir(argc > 1 ? argv[1] : "/");
    if (dp != nullptr)
    {
        while ((entry = readdir(dp)))
        {
            data = entry->d_name;
            entry = readdir(dp);
            email = entry->d_name;
            std::size_t pos2 = data.find("txt");
            std::size_t pos1 = email.find("txt");
            if(pos1 != std::string::npos && pos2 != std::string::npos)
            {
                resultvec.push_back(mainHelper(data,email,0));
            }




        }
        for (int i = 0; i < scorevec.size() ; ++i)
        {
            if(scorevec[i] != resultvec[i])
            {
                std::cerr<<"err"<<i<<std::endl;
            }
        }
    }

    closedir(dp);
    return 0;
