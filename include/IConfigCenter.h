
//

#ifndef IConfigCenter_h
#define IConfigCenter_h

#include "Define.h"

#include "IConfigReader.h"

struct IConfigCenter
{
    // 通过名称获取，对应的容器
    virtual ValueMap* GetValueMap(const std::string& pFileName) = 0;
    
    // 通过名称获取，对应的阅读器
    virtual IConfigReader* getConfigReaderByName(const std::string& szPath) = 0;
    
    // 获取DescHint.xml 里面的内容
    virtual const std::string GetDescHint(const std::string& szKey) = 0;
};

#endif
