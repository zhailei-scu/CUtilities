/*----------------------------------------------------------------------*
*--- Description:
*--- Author : Lei Zhai
*--- Location: Institute of Energy, Hefei Comprehensive National 
*--- Science Center. No. 80, Sanguocheng Road, Luyang District, 
*--- Hefei City, Anhui Province, People's Republic of China.
*--- Email : zhaileiytp@163.com or zhailei@ie.ah.cn
*--- data: From 2021/11 to --
*----------------------------------------------------------------------*/
#include "StringOperations.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

using namespace std;

void StringOperation::getAllNumsInString(const char* Str,vector<string> & result,bool hasNegative){
  string temp(Str);
  int startPos = 0;
  int endPos = 0;
  bool finded = false;
  vector<string>().swap(result);
  result.clear();
  
  for(string::iterator it = temp.begin(); it != temp.end();it++){
    if(*it >= '0' && *it <= '9'){
      finded = true;
    }else if('.' == *it){
        if((it+1) != temp.end() && *(it+1) >= '0' && *(it+1) <= '9'){                                                       // .x
            finded = true;
        }else if(true==finded){                                                                                             // x.
            finded = true;
        }
    }else if('e' == *it || 'E' == *it){
        if((it+1) != temp.end() && ((*(it+1) >= '0' && *(it+1) <= '9') || ('-' == *(it+1) || '+' == *(it+1)))){             // ex 
            finded = true;
        }else if(true==finded){                                                                                             // xe or x.e 
            finded = true;
        }
    }else if('-' == *it && (hasNegative || (it != temp.begin() && ('e' == *(it-1) || 'E' == *(it-1))))){
        if((it+1) != temp.end()){
            if(*(it+1) >= '0' && *(it+1) <= '9'){                                                                           // -x
                finded = true;
            }else if((it+2) != temp.end() &&
                     '.' == *(it+1) &&
                     *(it+2) >= '0' && *(it+2) <= '9'){                                                                     // -.x
                finded = true;
            }
        }
    }else if('+' == *it){
        if((it+1) != temp.end()){
            if(*(it+1) >= '0' && *(it+1) <= '9'){                                                                           // -x
                finded = true;
            }else if((it+2) != temp.end() &&
                     '.' == *(it+1) &&
                     *(it+2) >= '0' && *(it+2) <= '9'){                                                                     // +.x
                finded = true;
            }
        }
    }else{
      finded = false;
    }

    if((!finded) && (startPos<endPos)){
      result.push_back(temp.substr(startPos,endPos-startPos));
      startPos = endPos;
    }

    endPos++;

    if(!finded){
      startPos = endPos;
    }
    
  }

  if(startPos<endPos){
    result.push_back(temp.substr(startPos,endPos-startPos));
  }
   
}


void StringOperation::getAllNumsInString(const string str,vector<string> & result,bool hasNegative){
  getAllNumsInString(str.c_str(),result,hasNegative);
}

void StringOperation::split_notIncludeFlag(const char* Str,char split,vector<string> & result){
  stringstream ss;
  string temp;
  ss << Str;

  vector<string>().swap(result);
  std::string().swap(temp);
  
  while(getline(ss,temp,split)){
    if("" != temp && " " != temp){
       result.push_back(temp);
       string().swap(temp);
    }
  }
   
}

void StringOperation::split_includeFlag(const char* Str,char split,vector<string> & result){
  string ss_Str(Str);
  string temp;

  vector<string>().swap(result);
  string().swap(temp);

  string::iterator it = ss_Str.begin();
  
  unsigned int posBefore = 0;
  unsigned int pos = 0;
  while(it != ss_Str.end()){
    
    if(*it == split){
      
      if(pos>posBefore){
	    temp = ss_Str.substr(posBefore,pos-posBefore);
	    result.push_back(temp);
      }

      posBefore=pos;
      temp = ss_Str.substr(pos,1);
      result.push_back(temp);
      posBefore = pos + 1;
    }

    pos++;

    it++;
    
  }

  if(posBefore<ss_Str.size()){
    temp = ss_Str.substr(posBefore,pos-posBefore);
    result.push_back(temp);
  }

}


void StringOperation::EraseHeadAndTail(std::string & line,char theFlag){
  line.erase(0,line.find_first_not_of(theFlag));
  line.erase(line.find_last_not_of(theFlag)+1);
}

void StringOperation::EraseStr(std::string & line,const std::string & str){
    std::regex patten(str,std::regex_constants::icase);
    line = std::regex_replace(line,patten,std::string("$1$3"));
}

bool StringOperation::StringToBool(const char* str){
  std::string tempStr = str;
  bool result = false;
  
  transform(tempStr.begin(),tempStr.end(),tempStr.begin(),::tolower);

  if("true" == tempStr){
    result = true;
  }else if("false" == tempStr){
    result = false;
  }else{
    std::cout<<"Error: Unknown string to bool: "<<str<<std::endl;
    exit(-1);
  }

  return result;
}

bool StringOperation::StringToBool(const string & str){
  return StringToBool(str.c_str());
}

std::vector<std::string> StringOperation::extractAppendNum_Sub(const std::string & line, const std::string & targetStr){
    std::vector<std::string> splitedNum;

    std::string substr = line.substr(line.find(targetStr) + targetStr.length(),line.length());

    if(!substr.empty()){
        StringOperation::getAllNumsInString(substr,splitedNum,false);
    }else{
        std::cerr<<"There are none matched expand number after str "<<targetStr<<std::endl;
        std::cerr<<"In the line: "<<line<<std::endl;
        exit(-1);
    }

    return splitedNum;
}

int StringOperation::extractAppendNum_Int(const std::string & line, const std::string & targetStr){
    std::vector<std::string> splitedNum = extractAppendNum_Sub(line,targetStr);
    int result = 0;
    std::stringstream ss;

    ss.str("");
    ss.clear();
    ss<<splitedNum[0];
    ss>>result;

    return result;
}

float StringOperation::extractAppendNum_Float(const std::string & line, const std::string & targetStr){
    std::vector<std::string> splitedNum = extractAppendNum_Sub(line,targetStr);
    float result = 0.0e0;
    std::stringstream ss;

    ss.str("");
    ss.clear();
    ss<<splitedNum[0];
    ss>>result;

    return result;
}