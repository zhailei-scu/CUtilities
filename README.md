[![GitHub Pages](https://img.shields.io/badge/github_pages-gray.svg?logo=github)](https://github.com/zhailei-scu/CUtilities/deployments/github-pages)
![Benchmark Dashboard](https://img.shields.io/badge/Benchmark-Undefine-logoColor=white
)
[![Requires C++ Standard 17+](https://img.shields.io/badge/C++-17+-blue.svg?&logoColor=white)](https://isocpp.org/)
[![Requires CMake 3.0.0+](https://img.shields.io/badge/Cmake-3.0.0+-blue.svg?logo=cmake&logoColor=white)](https://cmake.org/)
![License](https://img.shields.io/badge/license-MIT-blue)

CUtilities is a project including some basic C/C++ functions that is common for development..</br>

Author: Lei Zhai.</br>

Data: From 2026/11/14 to now.</rb>

- - Location: Institute of Energy, Hefei Comprehensive National Science Center. No. 80, Sanguocheng Road, Luyang District, Hefei City, Anhui Province, People's Republic of China.</br>

Email: <zhaileiytp@163.com>  or  <zhailei@ie.ah.cn>  </br>

License: MIT License (There are no limitation for anyone to use/modify/sale of this code, be happy to use this code).

# 1. Usage

## 1.1 Introduce the Shared code to your project
```shell
cd $YourProjectPath
git remote add CUtilities-github http://192.168.55.1:8011/Common/CUtilities.git
```

## 1.2 Push change of the Shared code to repo
```shell
git add .
git commit -m "xxxxxx"
git push -u local master         # The main project
git subtree push --prefix=CUtilities/ CUtilities-local master
```