add_executable(RDataFrameAnalysis RDataFrameAnalysis.cpp)
target_include_directories(RDataFrameAnalysis PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src-oedo)
target_link_libraries(RDataFrameAnalysis ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES}
    artemis::catcmd artemis::catloop artemis::catcore artemis::artcont artemis::catmc
    artemis::artdecoder artemis::artridf artemis::artrdf artemis::arthist
    artemis::artparam artemis::artshare artemis::CAT oedo
    #GETDecoder 
)

install(TARGETS RDataFrameAnalysis
    RUNTIME DESTINATION bin
)