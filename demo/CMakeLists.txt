find_package(PkgConfig REQUIRED)

add_executable(demo_axpy           demo_axpy.cpp)
add_executable(demo_isFixed        demo_isFixed.cpp)
add_executable(demo_enumerateTuple demo_enumerateTuple.cpp)

target_include_directories(demo_axpy           PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(demo_isFixed        PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(demo_enumerateTuple PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(demo_axpy           PRIVATE BIC)
target_link_libraries(demo_isFixed        PRIVATE BIC)
target_link_libraries(demo_enumerateTuple PRIVATE BIC)

