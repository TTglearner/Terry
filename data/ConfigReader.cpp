
//

#include "ConfigReader.h"


ConfigReader::ConfigReader()
{
}

ConfigReader::~ConfigReader()
{
}

ConfigReader* ConfigReader::create(const std::string& szPath)
{
    ConfigReader* pRet = new ConfigReader();
    
    if(pRet && pRet->LoadToFile(szPath))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
    
}

std::string ConfigReader::GetValueString(const std::string& szkey,
                                         const std::string& szAttr)
{
    // 把 value 转为字符串
    auto& value = GetPrivateKey(szkey, szAttr);
    return value.asString();
}

int ConfigReader::GetValueI(const std::string& szkey,
                            const std::string& szAttr)
{
    // 把 value 转为整形
    auto& value = GetPrivateKey(szkey, szAttr);
    return value.asInt();
}

float ConfigReader::GetValueF(const std::string& szkey,
                              const std::string& szAttr)
{
    // 把 value 转为浮点型
    auto& value = GetPrivateKey(szkey, szAttr);
    return value.asFloat();
}

double ConfigReader::GetValueD(const std::string& szkey,
                               const std::string& szAttr)
{
    // 把 value 转为双精度型
    auto& value = GetPrivateKey(szkey, szAttr);
    return value.asDouble();
}

void ConfigReader::SetKeyValue(const std::string& szKey,
                               const std::string& szAttr, Value value)
{
}

// 加载文件
bool ConfigReader::LoadToFile(const std::string& path)
{
    CCLOG("Ready parse config-> %s", path.c_str());
    
    ssize_t dwFileSize = 0;
    
    // 获取到 app 下面的路径
    STRING szFullPath = FileUtils::getInstance()->fullPathForFilename(path);
    
    CCLOG("config full path = %s", szFullPath.c_str());
    
    // 获取文件中的数据
    BYTE* pFileData = FileUtils::getInstance()->getFileData(szFullPath.c_str(),
                                                            "r", &dwFileSize);
    

    
    
    // 如果数据不为null
    if(pFileData) // 多层
    {
        // 声明一个xml文件
        tinyxml2::XMLDocument hConfig;
        
        // 解析
        hConfig.Parse((const char*)pFileData);
        
        // 获取跟节点
        tinyxml2::XMLElement* pRootCfg = hConfig.FirstChildElement("Config");
        
        // 如果根节点存在
        if(pRootCfg)
        {
            seekAllNode(path, pRootCfg);
        }
        else
        {
            CCLOG("parse config -> %s failed!", path.c_str());
        }
        
        // 安全删除
        CC_SAFE_DELETE_ARRAY(pFileData);
        
        CCLOG("parse config -> %s success!", path.c_str());
    }
    
    
    
    
    return true;
}

// 获取私钥
const Value& ConfigReader::GetPrivateKey(const std::string& szKey,
                                         const std::string& szAttr)
{
    if(szAttr != "")
    {
        return m_ConfigContainer[szKey].asValueMap().at(szAttr);
    }
    else
    {
        return m_ConfigContainer[szKey];
    }
    
}

// 层次单一（结点单一排列）
void ConfigReader::seekSingleLineNode(BYTE* pFileData, const std::string& path)
{
        // 如果数据不为null
        if(pFileData) // 单层的
        {
            // 声明一个xml文件
            tinyxml2::XMLDocument hConfig;
    
            // 解析
            hConfig.Parse((const char*)pFileData);
    
            // 获取根节点
            tinyxml2::XMLElement* pRootCfg = hConfig.FirstChildElement("Config");
    
            // 如果根节点存在
            if(pRootCfg)
            {
                // 获取第二层
                tinyxml2::XMLElement* pChildCfg = pRootCfg->FirstChildElement();
    
                while(pChildCfg)
                {
                    // 获取键
                    const char* szKey = pChildCfg->Value();
                    // 获取第一个的属性
                    auto szAttr = pChildCfg->FirstAttribute();
    
                    if(szAttr == NULL)
                    {
                        pChildCfg = pChildCfg->NextSiblingElement();
                        continue;
                    }
    
                    if(szAttr->Next() == NULL)
                    {
                        m_ConfigContainer[szKey] = Value(szAttr->Value());
                        CCLOG("%s -> %s = %s", path.c_str(), szKey, szAttr->Value());
                    }
                    else
                    {
                        ValueMap _attrValueMap;
    
                        while(szAttr)
                        {
                            _attrValueMap[szAttr->Name()] = Value(szAttr->Value());
                            CCLOG("%s -> %s -> %s = %s", path.c_str(), szKey, szAttr->Name(), szAttr->Value());
                            szAttr = szAttr->Next();
                        }
    
                        m_ConfigContainer[szKey] = _attrValueMap;
                    }
    
                    pChildCfg = pChildCfg->NextSiblingElement();
                }
    
                CCLOG("parse config -> %s success!", path.c_str());
            }
            else
            {
                CCLOG("parse config -> %s failed!", path.c_str());
            }
            
            // 安全删除
            CC_SAFE_DELETE_ARRAY(pFileData);
        }
}

// 层次复杂（多层次）
void ConfigReader::seekAllNode(const std::string& path, tinyxml2::XMLElement* root)
{
    // 获取该结点的下一层（第一个结点）
    //tinyxml2::XMLElement* rootChild = root->FirstChildElement();
    
    // 如果当前节点（root）没有子节点 ，读取该节点属性后，跳转到下一个兄弟节点
    // 否则，进入该节点的第一个子节点
    if(root->FirstChildElement() == NULL)
    {
        
        
        // 获取键
        const char* szKey = root->Value();
        // 获取第一个属性
        auto szAttr = root->FirstAttribute();
        
         // 该结点没有属性
        if(szAttr == NULL)
        {
            // 跳转到下一个兄弟结点
            seekAllNode(path, root->NextSiblingElement());
        }
        
        // 获取 属性
        getAttr(path, szKey, szAttr);

        
        // 跳转到下一个兄弟结点
        if(root->NextSiblingElement() != NULL)
        {
            seekAllNode(path, root->NextSiblingElement());
        }
 
    }
    else
    {
        // 进入子节点
        seekAllNode(path, root->FirstChildElement());
        
        //读取父节点数据
        // 获取键
        const char* szKey = root->Value();
        // 获取第一个属性
        auto szAttr = root->FirstAttribute();
        
        // 该结点没有属性
        if(szAttr == NULL)
        {
            // 跳转到上一个节点
            //seekAllNode(path, root->PreviousSiblingElement());
        }
        else
        {
            getAttr(path, szKey, szAttr);

         }
        
        // 跳转到父节点的兄弟节点
        if(root->NextSiblingElement() != NULL)
        {
            seekAllNode(path, root->NextSiblingElement());
        }
        
    }
    
}


void ConfigReader::getAttr(const std::string& path,
                           const char* szKey,
                           const tinyxml2::XMLAttribute* szAttr)
{
    // 该结点只有一个属性
    if(szAttr->Next() == NULL)
    {
        // 将该结点的 属性的 键 和 值 ，存入到 map 容器中
        m_ConfigContainer[szKey] = Value(szAttr->Value());
        CCLOG("%s -> %s = %s", path.c_str(), szKey, szAttr->Value());
        
    }
    else // 该结点有多个属性， 为该节点生成一个 map 容器
    {
        ValueMap _attrValueMap;
        
        // 遍历这个结点的所有 属性,将 属性的 键 和 值 添加到 _attrValueMap容器中
        while(szAttr)
        {
            _attrValueMap[szAttr->Name()] = Value(szAttr->Value());
            CCLOG("%s -> %s -> %s = %s", path.c_str(), szKey, szAttr->Name(), szAttr->Value());
            szAttr = szAttr->Next();
        }
        
        // 将 这个结点的 map容器 按 键值 添加到 主 map容器中
        m_ConfigContainer[szKey] = _attrValueMap;
        
    }
}











