//
//  IConfigReader.h
//  
//
//  Created by student on 16/8/17.
//
//

#ifndef IConfigReader_h
#define IConfigReader_h
#include "Define.h"

// 优点: 1.默认情况下，成员函数和成员变量，是公有的;
//      2.可以做内存对齐;

// struct 和 union 的区别:
//      1.struct的成员函数和成员变量，都有自己地址空间(有自己的内存区域)；
//      2.union所有的成员，公用一块地址空间;

struct IConfigReader
{
    // 通过键值，获取字符串
    virtual std::string GetValueString(const std::string& szkey,
                                       const std::string& szAttr = "") = 0;
    
    // 通过键值，获取int类型的值
    virtual int GetValueI(const std::string& szkey,
                          const std::string& szAttr = "") = 0;
    
    // 通过键值，获取float类型的值
    virtual float GetValueF(const std::string& szkey,
                            const std::string& szAttr = "") = 0;
    
    // 通过键值，获取double类型的值
    virtual double GetValueD(const std::string& szkey,
                             const std::string& szAttr = "") = 0;
    
    // 设置键值对
    virtual void SetKeyValue(const std::string& szKey,
                             const std::string& szAttr, Value value) = 0;
    

};

//union str
//{
//    
//};


#endif /* IConfigReader_h */
