# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-src")
  file(MAKE_DIRECTORY "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-src")
endif()
file(MAKE_DIRECTORY
  "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-build"
  "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-subbuild/box2d-populate-prefix"
  "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-subbuild/box2d-populate-prefix/tmp"
  "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-subbuild/box2d-populate-prefix/src/box2d-populate-stamp"
  "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-subbuild/box2d-populate-prefix/src"
  "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-subbuild/box2d-populate-prefix/src/box2d-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-subbuild/box2d-populate-prefix/src/box2d-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/lolek/Desktop/prj2/LightYears/build/_deps/box2d-subbuild/box2d-populate-prefix/src/box2d-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
