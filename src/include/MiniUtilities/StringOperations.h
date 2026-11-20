/*----------------------------------------------------------------------*
*--- Description:
*--- Author : Lei Zhai
*--- Location: Institute of Energy, Hefei Comprehensive National 
*--- Science Center. No. 80, Sanguocheng Road, Luyang District, 
*--- Hefei City, Anhui Province, People's Republic of China.
*--- Email : zhaileiytp@163.com or zhailei@ie.ah.cn
*--- data: From 2026/11 to --
*----------------------------------------------------------------------*/
#ifndef STRINGOPERATIONS_H
#define STRINGOPERATIONS_H

#include <vector>
#include <map>
#include <string>

class StringOperation{
 public:
  static void split_notIncludeFlag(const char* Str,char split,std::vector<std::string> & result);
  static void split_includeFlag(const char* Str,char split,std::vector<std::string> & result);
  static void EraseHeadAndTail(std::string & line,char theFlag);
  static void EraseStr(std::string & line,const std::string & str);
  static bool StringToBool(const char* str);
  static bool StringToBool(const std::string & str);

  static void getAllNumsInString(const std::string str,std::vector<std::string> & result,bool hasNegative);
  static void getAllNumsInString(const char* str,std::vector<std::string> & result,bool hasNegative);

  static int extractAppendNum_Int(const std::string & line, const std::string & targetStr);
  static float extractAppendNum_Float(const std::string & line, const std::string & targetStr);

private:
  static std::vector<std::string> extractAppendNum_Sub(const std::string & line, const std::string & targetStr);
};

#endif