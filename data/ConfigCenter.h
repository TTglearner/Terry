
//

#ifndef ConfigCenter_h
#define ConfigCenter_h

#include "IConfigCenter.h"
#include "ConfigReader.h"

class ConfigCenter: public IConfigCenter
{
public:
    ConfigCenter();
    ~ConfigCenter();

    
    // IConfigCenter
public:
    // 通过名称获取，对应的容器
    virtual ValueMap* GetValueMap(const std::string& pFileName);
    
    // 通过名称获取，对应的阅读器
    virtual IConfigReader* getConfigReaderByName(const std::string& szPath);
    
    const std::string GetDescHint(const std::string& szKey);
    
private:
    // 存储 configReader
    Map<std::string, ConfigReader*> m_ConfigReaderMap;
   
    // 存储文件名称
    ValueMap m_ConfigMap;
};


#endif
