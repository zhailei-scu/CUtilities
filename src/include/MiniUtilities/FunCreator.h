#ifndef FUNCREATOR_H
#define FUNCREATOR_H 1

#define CLASSCREATOR(classname) [](){return new class classname();}
#define CLASSCREATOR_WITHNAME(classname,name) [](const std::string & name){return new class classname(std::string(name));}

#endif