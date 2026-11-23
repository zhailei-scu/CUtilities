/*----------------------------------------------------------------------*
*--- Description:
*--- Author : Lei Zhai
*--- Location: Institute of Energy, Hefei Comprehensive National 
*--- Science Center. No. 80, Sanguocheng Road, Luyang District, 
*--- Hefei City, Anhui Province, People's Republic of China.
*--- Email : zhaileiytp@163.com or zhailei@ie.ah.cn
*--- data: From 2021/11 to --
*----------------------------------------------------------------------*/
#ifndef FUNCREATOR_H
#define FUNCREATOR_H 1

#define CLASSCREATOR(classname) [](){return new class classname();}
#define CLASSCREATOR_WITHNAME(classname,name) [](const std::string & name){return new class classname(std::string(name));}

#endif