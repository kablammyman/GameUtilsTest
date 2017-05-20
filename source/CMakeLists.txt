project(GameUtilsTest)
include_directories($ENV{MY_GAME_UTILS} )



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

set(MY_GAME_LIB_32_D $ENV{MY_X86_DEBUG_LIBS}/GameUtils.lib)
set(MY_GAME_LIB_64_D $ENV{MY_X64_DEBUG_LIBS}/GameUtils.lib)
set(MY_GAME_LIB_32_R $ENV{MY_X86_RELEASE_LIBS}/GameUtils.lib)
set(MY_GAME_LIB_64_R $ENV{MY_X64_RELEASE_LIBS}/GameUtils.lib)



ELSEIF(APPLE)
set(SDL2_32_LIB ${CMAKE_SOURCE_DIR}/lib/osx/x86/SDL2.a)
set(SDL2_64_LIB ${CMAKE_SOURCE_DIR}/lib/osx/x64/SDL2.a)
set(SDL2MAIN_32_LIB ${CMAKE_SOURCE_DIR}/lib/osx/x86/SDL2main.a)
set(SDL2MAIN_64_LIB ${CMAKE_SOURCE_DIR}/lib/osx/x64/SDL2main.a)
set(SDL2_TTF_32_LIB ${CMAKE_SOURCE_DIR}/lib/osx/x86/SDL2_ttf.a)
set(SDL2_TTF_64_LIB ${CMAKE_SOURCE_DIR}/lib/osx/x64/SDL2_ttf.a)
set(SDL2_IMAGE_32_LIB ${CMAKE_SOURCE_DIR}/lib/osx/x86/SDL2_image.a)
set(SDL2_IMAGE_64_LIB ${CMAKE_SOURCE_DIR}/lib/osx/x64/SDL2_image.a)

set(MY_GAME_LIB_32_D $ENV{MY_X86_DEBUG_LIBS}/GameUtils.a)
set(MY_GAME_LIB_64_D $ENV{MY_X64_DEBUG_LIBS}/GameUtils.a)
set(MY_GAME_LIB_32_R $ENV{MY_X86_RELEASE_LIBS}/GameUtils.a)
set(MY_GAME_LIB_64_R $ENV{MY_X64_RELEASE_LIBS}/GameUtils.a)
 

ELSE()
set(SDL2_32_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x86/SDL2.a)
set(SDL2_64_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x64/SDL2.a)
set(SDL2MAIN_32_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x86/SDL2main.a)
set(SDL2MAIN_64_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x64/SDL2main.a)
set(SDL2_TTF_32_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x86/SDL2_ttf.a)
set(SDL2_TTF_64_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x64/SDL2_ttf.a)
set(SDL2_IMAGE_32_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x86/SDL2_image.a)
set(SDL2_IMAGE_64_LIB ${CMAKE_SOURCE_DIR}/lib/lin/x64/SDL2_image.a)

set(MY_GAME_LIB_32_D $ENV{MY_X86_DEBUG_LIBS}/GameUtils.a)
set(MY_GAME_LIB_64_D $ENV{MY_X64_DEBUG_LIBS}/GameUtils.a)
set(MY_GAME_LIB_32_R $ENV{MY_X86_RELEASE_LIBS}/GameUtils.a)
set(MY_GAME_LIB_64_R $ENV{MY_X64_RELEASE_LIBS}/GameUtils.a)

MESSAGE("here is game util lib: ")
MESSAGE(${MY_GAME_LIB_64_D})
ENDIF()

file(GLOB SOURCES
	${PROJECT_SOURCE_DIR}/*.h
	${PROJECT_SOURCE_DIR}/*.cpp)
add_executable(GameUtilsTest ${SOURCES})


target_link_libraries (GameUtilsTest debug    ${SDL2_64_LIB} ${SDL2MAIN_64_LIB} ${SDL2_TTF_64_LIB} ${SDL2_IMAGE_64_LIB} ${MY_STRING_LIB_64_D} ${MY_GAME_LIB_64_D} )
#optimized ${SDL2_64_LIB} ${SDL2MAIN_64_LIB} ${SDL2_TTF_64_LIB} ${SDL2_IMAGE_64_LIB} ${MY_STRING_LIB_64_R} ${MY_GAME_LIB_64_R} ${MY_FILE_LIB_64_R} ${MY_CFG_LIB_64_R} )
