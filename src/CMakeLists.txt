add_subdirectory(utils)
add_subdirectory(gui)
add_subdirectory(core)
add_subdirectory(dataTypes)

add_executable(test main.cpp)
target_link_libraries(test PRIVATE 
    nm::prof
    nm::logger
    dirichlet::core
    nm::dtypes
)
# target_compile_options(test PUBLIC "-O3;-msse2;-mfpmath=sse;-ftree-vectorizer-verbose=5")