/*----------------------------------------------------------------------*
*--- Description:
*--- Author : Lei Zhai
*--- Location: Institute of Energy, Hefei Comprehensive National 
*--- Science Center. No. 80, Sanguocheng Road, Luyang District, 
*--- Hefei City, Anhui Province, People's Republic of China.
*--- Email : zhaileiytp@163.com or zhailei@ie.ah.cn
*--- data: From 2021/11 to --
*----------------------------------------------------------------------*/
#ifndef STLFUNC_H
#define STLFUNC_H
#include <iostream>
#include <map>
#include <vector>

#define ISSIGNED_TYPE(type) (((type)-1) < 0)

#define FINDER(typename1,typename2,value) \
              [&](const typename std::pair<typename1,typename2> &item) \
              { \
                  return item.second == value; \
              }

/*
template<typename T1,typename T2>
class Finder{
 public:
  Finder(const T1 & value_first, const T2 & value_second):value_first(value_first),value_second(value_second){}

  bool operator()(const typename std::map<T1,T2>::value_type & item){
    return item.second == value_second; // the "==" had been overrided
  }

 private:
  const T1 & value_first;
  const T2 & value_second;
};
*/

template <typename T1,typename T2>
class SortFuncs{
  public:
   static bool sortFunc(const std::pair<T1,T2> & s1, const std::pair<T1,T2> & s2);
};

template <typename T1,typename T2>
bool SortFuncs<T1,T2>::sortFunc(const std::pair<T1,T2> & s1, 
                                const std::pair<T1,T2> & s2){
    return s1.second > s2.second; // the 
}

template <typename T1,typename T2>
class Maps{
 public:
  static const T2 & findAndWarn(const std::map<T1,T2> &,const T1 & );
};

template <typename T1,typename T2>
const T2 & Maps<T1,T2>::findAndWarn(const std::map<T1,T2> & theMap,const T1 & key){

  if(theMap.count(key) <= 0){
    std::cerr<<"Error: the key was not finded: "<<key<<std::endl;
    exit(-1);
  }

  return theMap.find(key)->second;
}
#endif
