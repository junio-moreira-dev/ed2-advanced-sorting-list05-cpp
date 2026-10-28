cmake_minimum_required(VERSION 4.2)
project(ed2_advanced_sorting_list05_cpp)

set(CMAKE_CXX_STANDARD 20)

#add_executable(ed2_advanced_sorting_list05_cpp main.cpp
#        src/Exer02_MergeSortTrace.cpp
#        src/Exer03_QuickSortStructComparison.cpp
#        src/Exer01_TwoPointersMerge.cpp
#        src/Exer04_QuickSortSwapsLomutoVsHoare.cpp
#        src/Exer05_QuickSortMedianOfThree.cpp)

# Executável principal padrão (se for utilizar o main.cpp)
add_executable(ed2_advanced_sorting_list05_cpp main.cpp)

# Executáveis individuais para cada exercício da Lista 05
add_executable(Exer01_TwoPointersMerge src/Exer01_TwoPointersMerge.cpp)
add_executable(Exer02_MergeSortTrace src/Exer02_MergeSortTrace.cpp)
add_executable(Exer03_QuickSortStructComparison src/Exer03_QuickSortStructComparison.cpp)
add_executable(Exer04_QuickSortSwapsLomutoVsHoare src/Exer04_QuickSortSwapsLomutoVsHoare.cpp)
add_executable(Exer05_QuickSortMedianOfThree src/Exer05_QuickSortMedianOfThree.cpp)