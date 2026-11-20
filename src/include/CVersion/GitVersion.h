/*----------------------------------------------------------------------*
*--- Description:
*--- Author : Lei Zhai
*--- Location: Institute of Energy, Hefei Comprehensive National 
*--- Science Center. No. 80, Sanguocheng Road, Luyang District, 
*--- Hefei City, Anhui Province, People's Republic of China.
*--- Email : zhaileiytp@163.com or zhailei@ie.ah.cn
*--- data: From 2026/11 to --
*----------------------------------------------------------------------*/
#ifndef GITVERSION_H
#define GITVERSION_H 1

#ifndef GIT_BRANCH
#define GIT_BRANCH "unknown"
#endif

#ifndef GIT_TAG
#define GIT_TAG "unknown"
#endif

#ifndef GIT_COMMITID
#define GIT_COMMITID "unknown"
#endif

#include <string>

std::string GetVersion();

#endif