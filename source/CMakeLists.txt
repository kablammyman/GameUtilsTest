project(GameUtilsTest)
include_directories($ENV{MY_GAME_UTILS} )
include_directories($ENV{MY_STRING_UTILS} )
message( $ENV{MY_STRING_UTILS} ) 

IF(WIN32)
include_directories(${CMAKE_SOURCE_DIR}/include) 
set(SDL2_32_LIB ${CMAKE_SOURCE_DIR}/lib/win/x86/SDL2.lib)
set(SDL2_64_LIB ${CMAKE_SOURCE_DIR}/lib/win/x64/SDL2.lib)
set(SDL2MAIN_32_LIB ${CMAKE_SOURCE_DIR}/lib/win/x86/SDL2main.lib)
set(SDL2MAIN_64_LIB ${CMAKE_SOURCE_DIR}/lib/win/x64/SDL2main.lib)
set(SDL2_TTF_32_LIB ${CMAKE_SOURCE_DIR}/lib/win/x86/SDL2_ttf.lib)
set(SDL2_TTF_64_LIB ${CMAKE_SOURCE_DIR}/lib/win/x64/SDL2_ttf.lib)
set(SDL2_IMAGE_32_LIB ${CMAKE_SOURCE_DIR}/lib/win/x86/SDL2_image.lib)
set(SDL2_IMAGE_64_LIB ${CMAKE_SOURCE_DIR}/lib/win/x64/SDL2_image.lib)

include_directories(${CMAKE_SOURCE_DIR}/include) 
set(SDL2_32_LIB ${CMAKE_SOURCE_DIR}/lib/win/x86/SDL2.lib)
set(SDL2_64_LIB ${CMAKE_SOURCE_DIR}/lib/win/x64/SDL2.lib)
set(SDL2MAIN_32_LIB ${CMAKE_SOURCE_DIR}/lib/win/x86/SDL2main.lib)
set(SDL2MAIN_64_LIB ${CMAKE_SOURCE_DIR}/lib/win/x64/SDL2main.lib)
set(SDL2_TTF_32_LIB ${CMAKE_SOURCE_DIR}/lib/win/x86/SDL2_ttf.lib)
set(SDL2_TTF_64_LIB ${CMAKE_SOURCE_DIR}/lib/win/x64/SDL2_ttf.lib)
set(SDL2_IMAGE_32_LIB ${CMAKE_SOURCE_DIR}/lib/win/x86/SDL2_image.lib)
set(SDL2_IMAGE_64_LIB ${CMAKE_SOURCE_DIR}/lib/win/x64/SDL2_image.lib)

set(MY_GAME_LIB_32_D $ENV{MY_X86_DEBUG_LIBS}/GameUtils.lib)
set(MY_GAME_LIB_64_D $ENV{MY_X64_DEBUG_LIBS}/GameUtils.lib)
set(MY_GAME_LIB_32_R $ENV{MY_X86_RELEASE_LIBS}/GameUtils.lib)
set(MY_GAME_LIB_64_R $ENV{MY_X64_RELEASE_LIBS}/GameUtils.lib)


set(MY_STRING_LIB_32_D $ENV{MY_X86_DEBUG_LIBS}/StringUtils.lib)
set(MY_STRING_LIB_64_D $ENV{MY_X64_DEBUG_LIBS}/StringUtils.lib)
set(MY_STRING_LIB_32_R $ENV{MY_X86_RELEASE_LIBS}/StringUtils.lib)
set(MY_STRING_LIB_64_R $ENV{MY_X64_RELEASE_LIBS}/StringUtils.lib)



ELSE()


find_package(SDL2 REQUIRED)

find_package(SDL2 REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
set(SDL2_64_LIB ${SDL2_LIBRARY})
set(SDL2MAIN_64_LIB ${SDL2_MAIN_LIBRARY} )

#set(SDL2_TTF_32_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x86/SDL2_ttf.a)
#set(SDL2_IMAGE_32_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x86/SDL2_image.a)

set(SDL2_TTF_64_LIB ${SDL2_TTF_LIBRARY})
set(SDL2_IMAGE_64_LIB ${SDL2_IMAGE_LIBRARY})

#notice the "lib" in front of my stuff
set(MY_GAME_LIB_32_D $ENV{MY_X86_DEBUG_LIBS}/libGameUtils.a)
set(MY_GAME_LIB_64_D $ENV{MY_X64_DEBUG_LIBS}/libGameUtils.a)
set(MY_GAME_LIB_32_R $ENV{MY_X86_RELEASE_LIBS}/libGameUtils.a)
set(MY_GAME_LIB_64_R $ENV{MY_X64_RELEASE_LIBS}/libGameUtils.a)


set(MY_STRING_LIB_32_D $ENV{MY_X86_DEBUG_LIBS}/libStringUtils.a)
set(MY_STRING_LIB_64_D $ENV{MY_X64_DEBUG_LIBS}/libStringUtils.a)
set(MY_STRING_LIB_32_R $ENV{MY_X86_RELEASE_LIBS}/libStringUtils.a)
set(MY_STRING_LIB_64_R $ENV{MY_X64_RELEASE_LIBS}/libStringUtils.a)



ENDIF()

file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/*.h
	${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(GameUtilsTest ${SOURCES})


target_link_libraries (GameUtilsTest debug    ${SDL2_64_LIB} ${SDL2MAIN_64_LIB} ${SDL2_IMAGE_64_LIB} ${MY_STRING_LIB_64_D} ${MY_GAME_LIB_64_D} )
#optimized ${SDL2_64_LIB} ${SDL2MAIN_64_LIB} ${SDL2_TTF_64_LIB} ${SDL2_IMAGE_64_LIB} ${MY_STRING_LIB_64_R} ${MY_GAME_LIB_64_R} ${MY_FILE_LIB_64_R} ${MY_CFG_LIB_64_R} )
