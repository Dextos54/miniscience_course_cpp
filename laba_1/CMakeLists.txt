cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_FLAGS "-std=c++11 -g")

project(gmshdemo)
add_executable(sampleCube sampleCube.cpp)
add_executable(sampleCircle sampleCircle.cpp)
add_executable(sampleCylinder sampleCylinder.cpp)
add_executable(sample1 sample1.cpp)
add_executable(sample2 sample2.cpp)

# --- Подключаем gmsh, тут придется перебирать варианты 

# - если вам повезло, то сработает простой путь
#include_directories(${GMSH_INCLUDE_DIR})

# - если у вас Ubuntu, то возможно, что приехал немного кривой gmsh из репозитория
# - при этом достаточно указать системные пути, куда система положила нужные файлы
# - закомментируйте строку 14 и раскомментируйте эти шесть:
add_library(gmsh SHARED IMPORTED)
set_target_properties(gmsh PROPERTIES
    IMPORTED_LOCATION "/usr/lib/x86_64-linux-gnu/libgmsh.so"
    INTERFACE_INCLUDE_DIRECTORIES "/usr/include"
)
set(GMSH_LIBRARIES gmsh)

# - если предыдущий вариант не сработал, собирайте gmsh из исходников
# - после этого в предыдущем варианте заменяйте системные пути на те, что вы сделали сами

# --- Закончили с gmsh, остальное править не обязательно (не поможет)

# Укажем библиотеки для линковки
target_link_libraries(sampleCube ${GMSH_LIBRARIES})
target_link_libraries(sampleCircle ${GMSH_LIBRARIES})
target_link_libraries(sampleCylinder ${GMSH_LIBRARIES})
target_link_libraries(sample1 ${GMSH_LIBRARIES})
target_link_libraries(sample2 ${GMSH_LIBRARIES})
