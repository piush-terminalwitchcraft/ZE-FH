#include <string_view>
#include <vector>
#include <charconv>

namespace ZE::Common { 

         
    inline bool tryParseInt(std::string_view& sv, int& out) {
        auto res = std::from_chars(sv.data(), sv.data() + sv.size(), out);
        return res.ec == std::errc() && res.ptr == sv.data() + sv.size();
    }

    inline bool tryParseArray(std::string_view& sv, std::vector<std::string>& out) {
        if (sv.find(',') == std::string_view::npos) return false;
        
        size_t start = 0;
        size_t end = sv.find(',');
        while (end != std::string_view::npos) {
            out.emplace_back(sv.substr(start, end - start));
            start = end + 1;
            end = sv.find(',', start);
        }
        out.emplace_back(sv.substr(start));
        return true;
    }
}
