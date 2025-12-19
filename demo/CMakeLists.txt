find_package(PkgConfig REQUIRED)

# List of compiler flags
set(BIC_DEMO_COMPILE_WARNINGS
    -fopenmp-simd
    -Wundef
    -Wvarargs
    -Wall
    -Wextra
    -Winit-self
    -Wpedantic
    -Werror
    -Wconversion
    -Wuninitialized
    -Wmissing-declarations
    -Wrange-loop-construct
    -Wsign-conversion
    -Wshadow
    -Wnon-virtual-dtor
    -Wold-style-cast
    -Wcast-align
    -Woverloaded-virtual
    -Wnull-dereference
    -Wformat=2
    -flax-vector-conversions
    -pedantic
    -pedantic-errors
	-Wno-error=array-bounds
	-Wdouble-promotion
)

add_executable(demo_axpy           demo_axpy.cpp)
add_executable(demo_isFixed        demo_isFixed.cpp)
add_executable(demo_enumerateTuple demo_enumerateTuple.cpp)
add_executable(demo_Array          demo_Array.cpp)

target_include_directories(demo_axpy           PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(demo_isFixed        PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(demo_enumerateTuple PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(demo_Array          PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(demo_axpy           PRIVATE BIC)
target_link_libraries(demo_isFixed        PRIVATE BIC)
target_link_libraries(demo_enumerateTuple PRIVATE BIC)
target_link_libraries(demo_Array          PRIVATE BIC)

target_compile_options(demo_axpy           PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${BIC_DEMO_COMPILE_WARNINGS}>)
target_compile_options(demo_isFixed        PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${BIC_DEMO_COMPILE_WARNINGS}>)
target_compile_options(demo_enumerateTuple PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${BIC_DEMO_COMPILE_WARNINGS}>)
target_compile_options(demo_Array          PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${BIC_DEMO_COMPILE_WARNINGS}>)
