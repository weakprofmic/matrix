# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-src"
  "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-build"
  "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-subbuild/googletest-populate-prefix"
  "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Desktop/Programming/C,C++/projects_n_vs/matrix/build/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
