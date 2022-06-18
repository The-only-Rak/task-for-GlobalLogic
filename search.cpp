
#include "search.hpp"
#define SHOW_FILE_PATH
void task::Finder::exist() noexcept
{
    uint8_t tts = 1;
    ///we ignore all errors which can be thow
    std::error_code ec;
    while (true)
    {
        m.lock();
        if (!(isFind != true && pathes.size() > 0))
        {
            m.unlock();
            ///if pathes size is 0 its means that no pathes available.First time we wait.After that if new pathes was not add,the task was solve.  
            if (tts == 0 || isFind == true)
                break;
            else
            {
                using namespace std::chrono_literals;
                std::this_thread::yield();
                --tts;
                continue;
            }
        }

        std::filesystem::directory_iterator it;
        try
        {
            it = std::filesystem::directory_iterator(pathes.top(), std::filesystem::directory_options::skip_permission_denied);
        }
        catch(const std::exception& e)
        {
        }
        pathes.pop();
        m.unlock();
        for (const auto &i : it)
            if (!i.is_symlink(ec) && i.is_directory(ec))
            {
                m.lock();
                pathes.push(i.path());
                m.unlock();
            }
            else if (i.is_regular_file(ec))
            {
                m.lock();
                if (i.path().filename() == name)
                {
                    isFind = true;
                    filePath = i.path();
                    #ifdef SHOW_FILE_PATH
                    std::cout << filePath<<std::endl;
                    #endif
                }
                m.unlock();
            }
    }
}
void task::Finder::find() noexcept
{
    std::jthread th1(&Finder::exist, this);
    std::jthread th2(&Finder::exist, this);
    std::jthread th3(&Finder::exist, this);
    std::jthread th4(&Finder::exist, this);
    std::jthread th5(&Finder::exist, this);
    std::jthread th6(&Finder::exist, this);
    std::jthread th7(&Finder::exist, this);
    exist();
}
task::Finder::Finder(const std::string_view name) noexcept : name(name) 
{
    ///root path
    pathes.push(std::filesystem::current_path().root_name() / std::filesystem::current_path().root_directory());
}
task::path task::Finder::GetPath() noexcept
{
    if (filePath.empty())
        find();
    if (filePath.empty())
        filePath = "None";
    return filePath;
}
void task::Finder::ClearPath() noexcept
{
    if (!filePath.empty())
        filePath = path();
}
task::path task::find(const std::string_view a)
{   
    path res;
    bool exit = false;
    std::error_code ec;
    std::mutex m;
    std::filesystem::recursive_directory_iterator it(std::filesystem::current_path().root_name() / std::filesystem::current_path().root_directory(),std::filesystem::directory_options::skip_permission_denied);
    auto daemon = [&m,&it,&ec,&a,&exit,&res]()
    {
        while(true)
        {
            m.lock();
            if(std::filesystem::end(it) == it || exit == true)
            {
                m.unlock();
                break;
            }
                const auto b = *it;
                try
                {
                it++;
                }
                catch(std::exception& x)
                {}
            m.unlock();
            if(!b.is_symlink() && b.is_regular_file(ec) == true && b.path().filename() == a)
            {
                exit = true;
                #ifdef SHOW_FILE_PATH
                std::cout<<b.path()<<std::endl;
                #endif
                res = b.path();
            }
        }
        
    };
    std::jthread th1(daemon);
    std::jthread th2(daemon);
    std::jthread th3(daemon);
    std::jthread th4(daemon);
    std::jthread th5(daemon);
    std::jthread th6(daemon);
    std::jthread th7(daemon);
    daemon();
    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    th6.join();
    th7.join();
    return res;

}