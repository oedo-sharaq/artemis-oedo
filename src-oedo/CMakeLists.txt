set(LIB_NAME oedo)

set(SOURCES
	TDssdProcessor.cc
	TDssdCalProcessor.cc
	TDssdData.cc
	TTinaProcessor2.cc
	TTinaData2.cc
	TDaliProcessor.cc
	TDaliData.cc
	TIonChamberProcessor.cc
	TS1IonChamberProcessor.cc
	TIonChamberProcessor.cc
	TTOF2BetaProcessor.cc
	TBrhoReconstructProcessorS1.cc
	TPIDSingleSectionProcessor.cc
	TRawDataTriggeredList.cc
	TModuleDecoderA3100FreeRunTSI.cc
	TTimingChargeTriggeredListMappingProcessor.cc
	TTimingAverageProcessor.cc
	TModuleDecoderTC842.cc
	TModuleDecoderAPV8008.cc
	TRawDataTimestampCharge.cc
	TTimingChargeAPV8008Processor.cc
	TAPV8008Data.cc
	TMergerData.cc
	TMergerProcessor.cc
	TModuleDecoderTimestamp.cc
	TExpConverter.cc
	TDiaData.cc
	TDiaTimingData.cc
	TDiaPadData.cc
	TDiaStripData.cc
	TDiaTimingDataMappingProcessor.cc
	TDiaStripCalibrationProcessor.cc
	TDiaPadCalibrationProcessor.cc
	TDiaTimingProcessor.cc
	TDiaStripTimingProcessor.cc
	TDiaStripTimingEachProcessor.cc
	TDiaTimingSubtractionProcessor.cc
	TDiaPadTimingSubtractionProcessor.cc
	TMassData.cc
	TMahalaData.cc
	TPIDwTOFPPACSSDProcessor.cc
	TPIDwTOFPPACSSDCalProcessor.cc
	TMassCalibrationConverter.cc
	TMahalanobisDistance.cc
	TMahalanobisDistanceTinc.cc
	TTc842TwoSidedCalibrationProcessor.cc
	TDiaStripTimingEachMergeProcessor.cc
	TDiaStripTimingEachMergeToffsetProcessor.cc
	TMWDCTrackingAllLRCombination.cc
	TMWDCTrackingAllLRCombinationResult.cc
	TQuitProcessor.cc

)

set(HEADERS
	TDssdProcessor.h
	TDssdCalProcessor.h
	TDssdData.h
	TTinaProcessor2.h
	TTinaData2.h
	TDaliProcessor.h
	TDaliData.h
	TIonChamberProcessor.h
	TS1IonChamberProcessor.h
	TIonChamberProcessor.h
	TTOF2BetaProcessor.h
	TBrhoReconstructProcessorS1.h
	TPIDSingleSectionProcessor.h
	TRawDataTriggeredList.h
	TModuleDecoderA3100FreeRunTSI.h
	TTimingChargeTriggeredListMappingProcessor.h
	TTimingAverageProcessor.h
	TModuleDecoderTC842.h
	TModuleDecoderAPV8008.h
	TRawDataTimestampCharge.h
	TTimingChargeAPV8008Processor.h
	TAPV8008Data.h
	TMergerData.h
	TMergerProcessor.h
	TModuleDecoderTimestamp.h
	TExpConverter.h
	TDiaData.h
	TDiaTimingData.h
	TDiaPadData.h
	TDiaStripData.h
	TDiaTimingDataMappingProcessor.h
	TDiaStripCalibrationProcessor.h
	TDiaPadCalibrationProcessor.h
	TDiaTimingProcessor.h
	TDiaStripTimingProcessor.h
	TDiaStripTimingEachProcessor.h
	TDiaTimingSubtractionProcessor.h
	TDiaPadTimingSubtractionProcessor.h
	TMassData.h
	TMahalaData.h
	TPIDwTOFPPACSSDProcessor.h
	TPIDwTOFPPACSSDCalProcessor.h
	TMassCalibrationConverter.h
	TMahalanobisDistance.h
	TMahalanobisDistanceTinc.h
	TTc842TwoSidedCalibrationProcessor.h
	TDiaStripTimingEachMergeProcessor.h
	TDiaStripTimingEachMergeToffsetProcessor.h
	TMWDCTrackingAllLRCombination.h
	TMWDCTrackingAllLRCombinationResult.h
	TQuitProcessor.h

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
