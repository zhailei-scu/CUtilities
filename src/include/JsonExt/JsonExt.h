/*----------------------------------------------------------------------*
*--- Description:
*--- Author : Lei Zhai
*--- Location: Institute of Energy, Hefei Comprehensive National 
*--- Science Center. No. 80, Sanguocheng Road, Luyang District, 
*--- Hefei City, Anhui Province, People's Republic of China.
*--- Email : zhaileiytp@163.com or zhailei@ie.ah.cn
*--- data: From 2026/11 to --
*----------------------------------------------------------------------*/
#ifndef JSONEXT_H
#define JSONEXT_H
#include <map>
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <iomanip>

class JsonExt;

class JsonFlags{
private:
    JsonFlags();
    virtual ~JsonFlags();
    JsonFlags(const JsonFlags &) = delete;
    const JsonFlags & operator =(const JsonFlags &) = delete;

public:
    static const JsonFlags & getInstance();

    std::string objectStartFlag = "{";
    std::string objectEndFlag = "}";
    std::string arrayStartFlag = "[";
    std::string arrayEndFlag = "]";
    std::string commaFlag = ",";
    std::string colonFlag = ":";
private:
    void clear();
};

class JsonBase{
public:
    JsonBase();
    ~JsonBase();
    JsonBase(const JsonBase &);
    const JsonBase & operator = (const JsonBase &);

public:

    friend JsonExt;

    std::map<std::string,std::string> *namedPairs = NULL;
    std::map<std::string,std::vector<std::string>> *namedLists = NULL;
    std::map<std::string,JsonBase*> *namedObjects = NULL;
    std::map<int,JsonBase*> *objectsArray = NULL;

public:
    void writeBackToIo(std::ostream & io) const;
    void print() const;
    void reset();
};

class JsonExt{
public:
    JsonExt();
    virtual ~JsonExt();
    JsonExt(const JsonExt &);
    const JsonExt & operator = (const JsonExt &);

public:
    JsonBase* getJsonInfo() const;
    void setJsonInfo(JsonBase*);
    void Extract(std::ifstream & ifs);
    void Extract(const std::string &);
    void WriteBackToFile(const std::string & outFile,const std::ios::openmode & theMode);
private:
    JsonBase *theJsonInfo = NULL;

private:
    void clear();
    void EraseUselesschars(std::string & s);
    void Extract(std::vector<std::string> & clearInfo);
    void Extract(JsonBase* treeRoot,std::vector<std::string> & clearInfo);
    void Extract(JsonBase* base,const std::vector<std::string> & clearInfo,int & pos,int & endPos);
    void Extract(std::map<std::string,std::vector<std::string>> *theList,
                 const std::vector<std::string> & clearInfo,
                 int & pos,
                 int & endPos);
    void SplitByFlag(std::vector<std::string> & clearInfo);
    void SplitByFlag(std::vector<std::string> & clearInfo,const char flag);
    void Check(const JsonBase* treeRoot);

private:
    friend JsonBase;
    static void Traverse(const JsonBase* treeRoot,
                         std::vector<std::string> & traverseInfo,
                         int blankNum=0);
};

#endif