/**
 * @author Dovhopolov Daniil
 */
#pragma once
#include <stack>
#include <filesystem>
#include <string_view>
#include <thread>
#include <iostream>
#include <mutex>
#include <atomic>
#include <system_error>

namespace task
{

    using path = std::filesystem::path;
    /**
     * @brief if you dont need print filePath after he find(if file is not found,nothing will be printed),comment #define SHOW_FILE_PATH in search.cpp.
     */
    class Finder
    {
        /// File path
        path filePath;
        bool isFind = false;
        std::mutex m;
        /// stack which store all pathes where file can be
        std::stack<path> pathes;
        /// name of file
        std::string_view name;
        /**
         * @brief Function which search file.End when pathes is empty or file isFind is true
         *
         */
        void exist() noexcept;
        /**
         * @brief Run exist func in many threads
         *
         */
        void find() noexcept;

    public:
        Finder(std::string_view name) noexcept;
        /**
         * @brief Get the Path file,if file is found return its path,else none.
         * if filePath is not empty,return filePath
         *
         * @return path
         */
        path GetPath() noexcept;
        /**
         * @brief Make filePath empty.After that can be used GetPath fuction to find new path of the file
         *
         */
        void ClearPath() noexcept;
    };
}
