
//

#ifndef ConfigReader_h
#define ConfigReader_h

#include "Define.h"
#include "IConfigReader.h"
#include "external/tinyxml2/tinyxml2.h"

class ConfigReader: public Ref, public IConfigReader
{
public:
    ConfigReader();
    ~ConfigReader();
    
    
    // 创建函数
public:
    static ConfigReader* create(const std::string& szPath);
    bool init(){return true;};
    
    // IConfigReader
    std::string GetValueString(const std::string& szkey,
                               const std::string& szAttr = "");
    
    int GetValueI(const std::string& szkey,
                  const std::string& szAttr = "");
    
    float GetValueF(const std::string& szkey,
                    const std::string& szAttr = "");
    
    double GetValueD(const std::string& szkey,
                     const std::string& szAttr = "");
    
    void SetKeyValue(const std::string& szKey,
                     const std::string& szAttr, Value value);
    
    
    
protected:
    // 加载文件
    bool LoadToFile(const std::string& path);
    // 获取私钥
    const Value& GetPrivateKey(const std::string& szKey,
                               const std::string& szAttr = nullptr);
    
    // 多层
    void seekAllNode(const std::string& path, tinyxml2::XMLElement* root);
    
    void getAttr(const std::string& path,
                 const char* szKey,
                 const tinyxml2::XMLAttribute* szAttr);
    
    // 单层
    void seekSingleLineNode(BYTE* pFileData, const std::string& path);
    
protected:
    ValueMap m_ConfigContainer;
    
    
};


#endif
