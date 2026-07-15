#include "../../include/ZE/FH/Config.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <iterator>
#include <string>
#include <string_view>
#include <sys/mman.h>
#include <sys/stat.h>

namespace ZE::FH {

/*
 * simple config
 * jaise key=value
 *
 */
Config::Config(const std::string &filepath) {
  int fd = open(filepath.c_str(), O_RDONLY);
  if (fd == -1) {
    // throw error at some future logging class
    std::cerr << "Failed to open configuration file";
  }

  struct stat fileInfo;
  if (fstat(fd, &fileInfo) == -1) {
    std::cerr << "Failed to get file info";
  }

  size_t fileSize = fileInfo.st_size;

  // file-> memory mapping ke liye
  void *map =
      mmap(nullptr, fileSize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

  const char *start = static_cast<char *>(map);
  const char *end = start + fileSize;

  while (start < end) {

    const char *nextLine =
        static_cast<const char *>(std::memchr(start, '\n', end - start));
    size_t lineLength = 0;
    if (nextLine != nullptr) {
      lineLength = nextLine - start;
    } else {
      lineLength = end - start;
    }

    const std::string_view sv = std::string_view(start, lineLength);
    Config::parseValue(std::move(sv));

    if (nextLine != nullptr) {
      start = nextLine + 1;
    } else
      break;
  }
}

void Config::parseValue(const std::string_view &value) {
  // regex -> seperate key=value logic
  int size = value.size();
  if (size == 0)
    return;

  if (value[0] != '/') {
    // not a comment
    const char *sep = static_cast<const char *>(
        std::memchr(value.begin(), '=', value.size()));

    assert(sep != nullptr);
    const std::string_view key =
        std::string_view(value.data(), value.data() - sep - 1); // 0 -> sep-1
    const std::string_view mapValue = std::string_view(
        sep + 1, (value.data() + value.size()) - (1 + sep)); // sep+1 -> ed

    std::cout << "Setting parsed " << key << "=" << mapValue;
  }
}

  static inline ConfigValue Config::parseVariant(const std::string_view &val) {}

template <typename T> T Config::get(const std::string &key) const { 
  return std::get<T>(this->settings.at(key));
}
} // namespace ZE::FH
