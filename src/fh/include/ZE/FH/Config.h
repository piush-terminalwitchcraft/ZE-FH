
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>
namespace ZE::FH
{

    using ConfigValue = std::variant<int, std::string, std::vector<std::string>>;

    class IConfig
    {
    private:
        virtual void parseValue(const std::string_view &filename);

    };

    class Config : public IConfig
    {
    private:
        std::unordered_map<std::string, ConfigValue> settings;

        void parseValue(const std::string_view &data) override;

    public:
        Config(const std::string &filepath);

        template<typename T>
        T get(const std::string_view &key) const;

        void set(const std::string_view &key, const ConfigValue &value);

        ~Config() = default;
    };

} // namespace ZE::FH
