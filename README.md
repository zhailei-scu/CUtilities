[![GitHub Pages](https://img.shields.io/badge/github_pages-gray.svg?logo=github)](https://github.com/zhailei-scu/CUtilities/deployments/github-pages)
![Benchmark Dashboard](https://img.shields.io/badge/Benchmark-Undefine-logoColor=white
)
[![Requires C++ Standard 17+](https://img.shields.io/badge/C++-17+-blue.svg?&logoColor=white)](https://isocpp.org/)
[![Requires CMake 3.0.0+](https://img.shields.io/badge/Cmake-3.0.0+-blue.svg?logo=cmake&logoColor=white)](https://cmake.org/)
![License](https://img.shields.io/badge/license-MIT-blue)

CUtilities is a project including some basic C/C++ functions that is common for development.</br>

> **NOTE**
>     Currently, we recommand you use CMake to build your project and use CUtilities.

-  Author: Lei Zhai.</br>

Data: From 2026/11/14 to now.</rb>

- Location: Institute of Energy, Hefei Comprehensive National Science Center. No. 80, Sanguocheng Road, Luyang District, Hefei City, Anhui Province, People's Republic of China.</br>

- Email: <zhaileiytp@163.com>  or  <zhailei@ie.ah.cn>  </br>

License: MIT License (There are no limitation for anyone to use/modify/sale of this code, be happy to use this code).


Here, we can use CUtilities by two ways:

- 1 Embedment the CUtilities to your CMake project (without installation).

- 2 Mannual link the library after install CUtilities


# 1. Embedment the CUtilities to your CMake project (without installation) 

## 1.1 Download the Shared code to your project
```shell
cd $YourProjectPath
git remote add CUtilities-github https://github.com/zhailei-scu/CUtilities.git
git subtree add --prefix=CUtilities CUtilities-github master
```

Sure, you can also update the CUtilities in your project:
```shell
git subtree pull --prefix=CUtilities CUtilities-github master
```

## 1.2 Configure your project to use CUtilities
In your cmake project, use:
```cmake
add_subdirectory(${PROJECT_SOURCE_DIR}/CUtilities)
```
in your main CMakeLists.txt to introuce CUtilities.

After the add_library or add_executable, you can use:
```cmake
target_link_libraries(targetName CUtilities::CUtilities)
```
to build your library or exe and add CUtilities support.


# 2. Mannual link the library after install CUtilities(Need install)
```shell
cd $AnyPathYouWantToInstall
git clone https://github.com/zhailei-scu/CUtilities.git
mkdir CUtilities_build
cd CUtilities_build/
cmake -S CUtilities_build/ -DCMAKE_INSTALL_PREFIX=CUtilities_install
make j8 && make install
```

Then, like use any other CMake package, you can use `find_package` to load and verify in your CMakeLists.txt:
```cmake
find_package(CUtilities CONFIG REQUIRED)
```

After the add_library or add_executable, you can use:
```cmake
target_link_libraries(targetName CUtilities::CUtilities)
```
to build your library or exe and add CUtilities support.

# 3 Contribute CUtilities change to the repo
If you agree, you can contribute your changes of CUtilities to repo with a new branch $nameOfBranch$, we would be happy to consider your merge request carefully.
```shell
git add .
git commit -m "xxxxxx"
git push -u github master         # The main project
git subtree push --prefix=CUtilities/ CUtilities-github nameOfBranch
```