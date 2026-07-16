#include "ZE/FH/Config.h"


#include <algorithm>
#include <cassert>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>
#include <string_view>
#include <sys/mman.h>
#include <sys/stat.h>

#include "ZE/Core/Common/Conversion.hpp"

namespace ZE::FH
{

    /*
     * simple config
     * jaise key=value
     *
     */

    void IConfig::parseValue(const std::string_view &filename) {}

    Config::Config(const std::string &filepath)
    {
        int fd = open(filepath.c_str(), O_RDONLY);
        if (fd == -1)
        {
            // throw error at some future logging class
            std::cerr << "Failed to open configuration file\n";
            return;
        }

        struct stat fileInfo;
        if (fstat(fd, &fileInfo) == -1)
        {
            std::cerr << "Failed to get file info";
            return;
        }

        size_t fileSize = fileInfo.st_size;

        // file-> memory mapping ke liye
        void *map = mmap(nullptr, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

        const char *start = static_cast<char *>(map);
        const char *end = start + fileSize;

        while (start < end)
        {

            const char *nextLine = static_cast<const char *>(std::memchr(start, '\n', end - start));
            size_t lineLength = 0;
            if (nextLine != nullptr)
            {
                lineLength = nextLine - start;
            }
            else
            {
                lineLength = end - start;
            }

            const std::string_view sv = std::string_view(start, lineLength);
            Config::parseValue(std::move(sv));

            if (nextLine != nullptr)
            {
                start = nextLine + 1;
            }
            else
                break;
        }
    }

    void Config::parseValue(const std::string_view &value)
    {
        // regex -> seperate key=value logic
        int size = value.size();
        if (size == 0)
            return; // empty line ko ignore karo

        if (value[0] != '/')
        {
            // not a comment
            const char *sep = static_cast<const char *>(std::memchr(value.begin(), '=', value.size()));

            assert(sep != nullptr);
            const std::string_view key = std::string_view(value.data(), sep - value.data()); // 0 -> sep-1
            const std::string_view mapValue =
                    std::string_view(sep + 1, (value.data() + value.size()) - (sep + 1)); // sep+1 -> end

            std::cout << "Setting parsed " << key << "=" << mapValue << '\n';

            int intVal{0};
            if (ZE::Common::tryParseInt(mapValue, intVal))
            {
                Config::set(key, intVal);
                return;
            }

            std::vector<std::string> strArray;
            if (ZE::Common::tryParseArray(mapValue, strArray))
            {
                Config::set(key, std::move(strArray));
            }

            // normal string
            Config::set(key, mapValue.data());
        }
    }

    template<typename T>
    T Config::get(const std::string_view &key) const
    {
        return std::get<T>(this->settings.at(key.data()));
    }

    void Config::set(const std::string_view &key, const ConfigValue &value)
    {
        if (this->settings.find(key.data()) == this->settings.end())
        {
            this->settings[key.data()] = value;
        }
        else
        {
            std::cerr << "Duplicate key-value pair found, for key={"<< key << "},  discarding it\n";
        }
    }

} // namespace ZE::FH
