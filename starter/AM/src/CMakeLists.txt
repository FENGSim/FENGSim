cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(m++_api)

set(CMAKE_CXX_COMPILER /usr/bin/g++-10)

find_package(MPI)
if(MPI_FOUND)
  message("MPI FOUND")
  message(${MPI_LIBRARIES})
  include_directories(${MPI_INCLUDE_DIRS})
  link_directories(${MPI_LIBRARY_DIRS})
  add_definitions(${MPI_DEFINITIONS})
endif()

include_directories("/usr/include/x86_64-linux-gnu/openmpi/")

message(${CMAKE_BINARY_DIR})

add_definitions(-DTETLIBRARY)
include_directories("M++/src")
include_directories(${CMAKE_BINARY_DIR}/../../../toolkit/Geometry/install/tetgen_install/include)

aux_source_directory(AM/src am_DIR_SRCS)
add_executable (AMSolver ${am_DIR_SRCS} M++/src/Identify.C M++/src/MatrixGraph.C M++/src/Algebra.C M++/src/Shape.C M++/src/Point.C M++/src/Parallel.C M++/src/Time.C M++/src/ctools.C M++/src/IO.C M++/src/Mesh.C M++/src/Cell.C M++/src/Distribution.C M++/src/Plot.C M++/src/Quadrature.C M++/src/DoF.C M++/src/Sparse.C M++/src/Interface.C M++/src/Discretization.C M++/src/LinearSolver.C M++/src/DD.C M++/src/Preconditioner.C M++/src/TimeSeries.C M++/src/ESolver.C M++/src/Transfer.C M++/src/Element.C M++/src/FaceElement.C M++/src/Newton.C M++/src/Newmark.C M++/src/Euler.C M++/src/Small.C M++/src/Schur.C)

target_link_libraries (AMSolver /usr/lib/x86_64-linux-gnu/libblas.so /usr/lib/x86_64-linux-gnu/liblapack.so ${MPI_LIBRARIES} /usr/lib/x86_64-linux-gnu/libsuperlu.so ${CMAKE_BINARY_DIR}/../../../toolkit/Geometry/install/tetgen_install/lib/libtetgen.so)
set_target_properties(AMSolver PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message(${CMAKE_BINARY_DIR})
target_link_libraries (AMSolver ${CMAKE_BINARY_DIR}/../../../toolkit/Geometry/install/cura_engine_install/lib/lib_CuraEngine.a)
target_link_libraries (AMSolver ${CMAKE_BINARY_DIR}/../../../toolkit/Geometry/install/cura_engine_install/lib/libclipper.a)
target_link_libraries (AMSolver ${CMAKE_BINARY_DIR}/../../../toolkit/Tools/install/protobuf_install/lib/libprotobuf.so)
target_link_libraries (AMSolver ${CMAKE_BINARY_DIR}/../../../toolkit/Tools/install/protobuf_install/lib/libprotobuf-lite.so)
target_link_libraries (AMSolver ${CMAKE_BINARY_DIR}/../../../toolkit/Tools/install/protobuf_install/lib/libprotoc.so)
target_link_libraries (AMSolver ${CMAKE_BINARY_DIR}/../../../toolkit/Tools/install/libarcus_install/lib/libArcus.so)
target_link_libraries (AMSolver /usr/lib/x86_64-linux-gnu/libgomp.so.1)

file(COPY "../log" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "../data/vtk" DESTINATION ${CMAKE_BINARY_DIR}/data)
file(COPY "../data/am" DESTINATION ${CMAKE_BINARY_DIR}/data)
file(COPY "../conf" DESTINATION ${CMAKE_BINARY_DIR})
file(COPY "AM/conf" DESTINATION ${CMAKE_BINARY_DIR}/AM)
