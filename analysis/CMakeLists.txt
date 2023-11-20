
function(addExec exec_name)
add_executable(${exec_name} ${exec_name}.cpp)
target_include_directories(${exec_name} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src-oedo)
target_link_libraries(${exec_name} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES}
    artemis::catcmd artemis::catloop artemis::catcore artemis::artcont artemis::catmc
    artemis::artdecoder artemis::artridf artemis::artrdf artemis::arthist
    artemis::artparam artemis::artshare artemis::CAT oedo
    GETDecoder 
)

install(TARGETS ${exec_name}
    RUNTIME DESTINATION bin
)
endfunction()

addExec(run_artemis)
addExec(RDataFrameAnalysis)