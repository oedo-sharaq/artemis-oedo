set(LIB_NAME oedo)

set(SOURCES
TTinaProcessor.cc
TTinaData.cc
TTinaProcessor2.cc
TTinaData2.cc
TDaliProcessor.cc
TDaliData.cc
TIonChamberProcessor.cc
TS1IonChamberProcessor.cc
TIonChamberProcessor.cc
TSingleTOFProcessor.cc
TTOF2BetaProcessor.cc
TBrhoReconstructProcessorS1.cc
TPIDSingleSectionProcessor.cc
TRawDataTriggeredList.cc
TModuleDecoderA3100FreeRunTSI.cc
TTimingChargeTriggeredListMappingProcessor.cc
TTimingAverageProcessor.cc
TSRPPACPlaneProcessorV2.cc
TCatGETChargeValidator.cc
)


set(HEADERS
TTinaProcessor.h
TTinaData.h
TTinaProcessor2.h
TTinaData2.h
TDaliProcessor.h
TDaliData.h
TIonChamberProcessor.h
TS1IonChamberProcessor.h
TIonChamberProcessor.h
TSingleTOFProcessor.h
TTOF2BetaProcessor.h
TBrhoReconstructProcessorS1.h
TPIDSingleSectionProcessor.h
TRawDataTriggeredList.h
TModuleDecoderA3100FreeRunTSI.h
TTimingChargeTriggeredListMappingProcessor.h
TTimingAverageProcessor.h
TSRPPACPlaneProcessorV2.h
TCatGETChargeValidator.h
)


add_library(${LIB_NAME} SHARED ${SOURCES})

target_include_directories(${LIB_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(${LIB_NAME}
    PRIVATE
        artemis::catcore
        artemis::catloop
        artemis::artcont
        artemis::catcmd
        artemis::catmc
        artemis::artdecoder
        artemis::artridf
        artemis::artrdf
        artemis::arthist
        artemis::artparam
        artemis::artshare
        artemis::CAT
        ${YAML_CPP_LIBRARIES}
)

ROOT_GENERATE_DICTIONARY(G__${LIB_NAME}
    ${HEADERS}
    LINKDEF "linkdef_user.h"
    MODULE ${LIB_NAME}
)

set_target_properties(
    ${LIB_NAME}
    PROPERTIES
        PUBLIC_HEADER "${headers}"
)

install(TARGETS ${LIB_NAME}
    EXPORT oedoTargets
    INCLUDES DESTINATION include
    ARCHIVE DESTINATION lib
    PUBLIC_HEADER DESTINATION include
    LIBRARY DESTINATION lib
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${LIB_NAME}_rdict.pcm
    DESTINATION lib
)
