
#include <string>
#include <string_view>
#include <unordered_map>
#include <variant>
#include <vector>
namespace ZE::FH {

  using ConfigValue = std::variant<int, std::string, std::vector<std::string>>;

  class IConfig 
  {
    private:
      virtual void parseValue(const std::string_view& filename);

    public:
      virtual ~IConfig() = default;
    
  };

  class Config : public IConfig
  {
    private:
      std::unordered_map<std::string, ConfigValue> settings;

      void parseValue(const std::string_view& data) override;

    public:

      explicit Config(const std::string& filepath) ;

      template<typename T>
      T get(const std::string& key) const;

      template<typename T>
      T set(const std::string& key, const ConfigValue& value);
       
  };
  
}
