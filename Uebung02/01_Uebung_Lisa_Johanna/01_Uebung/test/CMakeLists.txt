project(01_Sequence_Tests)

include_directories("${GTEST_SRC_DIR}/include")

# Etwas Magie um das Hinzufügen von Tests zu vereinfachen.
# Sie können diesen Code ignorieren.
function(add_gtest TEST_NAME)
    # Parse the additional arguments
    set(MULTI_ARGUMENTS LIBRARIES SOURCE_FILES)
    cmake_parse_arguments(MY_ARGS "" "" "${MULTI_ARGUMENTS}" ${ARGN})

    # Setup the executable
    add_executable(${TEST_NAME} "${TEST_NAME}.cpp" ${MY_ARGS_SOURCE_FILES})
    target_link_libraries(${TEST_NAME} gtest gtest_main test_driver ${MY_ARGS_LIBRARIES} ${CIP_STD_LIBS})

    # Add the test to CTest
    add_test(NAME ${TEST_NAME} WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test" COMMAND ${TEST_NAME})
endfunction()

# Füge einen Treiber hinzu, der die Tests
# mittels 'make test' aufrufbar macht.
add_library(test_driver main_test.cpp)

# Füge einen Test hinzu. Sie können die folgende
# Zeile für neue Tests einfach kopieren und anpassen.
add_gtest(Sequence_test LIBRARIES sequence)
add_gtest(DNA_test LIBRARIES sequence)
add_gtest(RNA_test LIBRARIES sequence)
add_gtest(Peptide_test LIBRARIES sequence)
add_gtest(Fasta_test LIBRARIES sequence)
add_gtest(2Bit_test LIBRARIES sequence)

