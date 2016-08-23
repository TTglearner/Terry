
//

#include "ConfigCenter.h"

ConfigCenter::ConfigCenter()
{}

ConfigCenter::~ConfigCenter()
{
}

// 通过名称获取，对应的容器
ValueMap* ConfigCenter::GetValueMap(const std::string& pFileName)
{
    // 如果容器内， 有此文件， 获取到返回
    if(m_ConfigMap.find(pFileName) != m_ConfigMap.end())
    {
        return &m_ConfigMap[pFileName].asValueMap();
    }
    else if(!FileUtils::getInstance()->isFileExist(pFileName))
    {
        // 如果app下面没有，返回nullptr
        return nullptr;
    }
    else
    {
        // 首次加载， 文件路径添加到容器内
        auto valueMap = FileUtils::getInstance()->getValueMapFromFile(pFileName);
        
        m_ConfigMap[pFileName] = valueMap;
        
        return &m_ConfigMap[pFileName].asValueMap();
    }
    

}

// 通过名称获取，对应的阅读器
IConfigReader* ConfigCenter::getConfigReaderByName(const std::string& szPath)
{
    // 如果阅读器容器内， 没有此阅读器，创建并添加到容器内
    if(!m_ConfigReaderMap.at(szPath))
    {
        m_ConfigReaderMap.insert(szPath, ConfigReader::create(szPath));
    }
    
    return m_ConfigReaderMap.at(szPath);
}

// 获取
const std::string ConfigCenter::GetDescHint(const std::string& szKey)
{
    auto pConfigReader = getConfigReaderByName("DescHint02.xml");
    
    return pConfigReader->GetValueString(szKey);
}






