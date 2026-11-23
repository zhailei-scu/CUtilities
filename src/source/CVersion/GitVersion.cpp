/*----------------------------------------------------------------------*
*--- Description:
*--- Author : Lei Zhai
*--- Location: Institute of Energy, Hefei Comprehensive National 
*--- Science Center. No. 80, Sanguocheng Road, Luyang District, 
*--- Hefei City, Anhui Province, People's Republic of China.
*--- Email : zhaileiytp@163.com or zhailei@ie.ah.cn
*--- data: From 2021/11 to --
*----------------------------------------------------------------------*/
#include "GitVersion.h"
#include <string>

std::string GetVersion(){
    std::string result;
    
    result.clear();
    result = "Version Information: ";
    result.append("Branch_");
    result.append(GIT_BRANCH);
    result.append("_Tag_");
    result.append(GIT_TAG);
    result.append("_CommitID_");
    result.append(GIT_COMMITID);

    return result;
}