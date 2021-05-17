#================Copyright: JunZhe Fan =====================#
cmake_minimum_required(VERSION 3.8)
project(Group6_Project)
include(CTest)



if(UNIX) 
  
     add_subdirectory(./Testing)
     add_subdirectory(./Semester1-Libs)

else()
add_subdirectory(./Semester1-Libs)
add_subdirectory(./Semester2-ModelViewer)
add_subdirectory(./Testing)
endif()

    
     