set (USE_PRECOMPILED_HEADER 1)

# Macro for setting up precompiled header support in MSVC
# Found at StackOverflow, Question 148570
# "Using pre compiled headers with CMake"
MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    GET_FILENAME_COMPONENT(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    SET(PrecompiledBinary "$(IntDir)/${PrecompiledBasename}.pch")
    SET(Sources ${${SourcesVar}})

    SET_SOURCE_FILES_PROPERTIES(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    SET_SOURCE_FILES_PROPERTIES(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")
    # Add precompiled header to SourcesVar
    #LIST(APPEND ${SourcesVar} ${PrecompiledSource})

  ENDIF(MSVC)
ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)


# Set the relative path to the source and header directories
# for this library (these are private to the library)
set (OCAP_DIR OcAp)
set (OCBS_DIR OcBs)
set (OCDB_DIR OcDb)
set (OCGE_DIR OcGe)
set (OCRX_DIR OcRx)

# Find the relative path to the public header facing header files.
# Probably ../inc
file (RELATIVE_PATH HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}/inc/OcCommon.h")
string(REGEX REPLACE "/OcCommon.h$" "" HEADERS_DIR ${HEADERS_DIR})

# Public facing header files for the library. This list
# will also be used to set the group filter PublicHeaders
# in the MSVC IDE
set(PUBLIC_HEADERS
	${HEADERS_DIR}/ClassMacros.h
	${HEADERS_DIR}/OcApApplication.h
	${HEADERS_DIR}/OcApClassFactory.h
	${HEADERS_DIR}/OcCommon.h
	${HEADERS_DIR}/OcConfig.h
	${HEADERS_DIR}/OcDbDatabase.h
	${HEADERS_DIR}/OcDbDwgVersion.h
	${HEADERS_DIR}/OcDbEntity.h
	${HEADERS_DIR}/OcDbHardOwnershipId.h
	${HEADERS_DIR}/OcDbObject.h
	${HEADERS_DIR}/OcDbObjectId.h
	${HEADERS_DIR}/OcDbSmartPtrs.h
	${HEADERS_DIR}/OcError.h
	${HEADERS_DIR}/OcGePoint2D.h
	${HEADERS_DIR}/OcGePoint3D.h
	${HEADERS_DIR}/OcRxClass.h
	${HEADERS_DIR}/OcRxObject.h
	${HEADERS_DIR}/OcTypes.h
	${HEADERS_DIR}/wchar_logging.h
)

# Private files in the OcAp directory. Will also be
# used for the group filter OcAp in MSVC IDE
set (OCAP_FILES
	${OCAP_DIR}/OcApApplication.cpp
	${OCAP_DIR}/OcApClassFactory.cpp
)

# Private files in the OcBs directory. Will also be
# used for the group filter OcBs in MSVC IDE
set (OCBS_FILES
	${OCBS_DIR}/DwgInArchive.cpp
	${OCBS_DIR}/DwgInArchive.h
	${OCBS_DIR}/OcBsDwgCrc.cpp
	${OCBS_DIR}/OcBsDwgCrc.h
	${OCBS_DIR}/OcBsDwgFileHeader.cpp
	${OCBS_DIR}/OcBsDwgFileHeader.h
	${OCBS_DIR}/OcBsDwgPreviewImage.cpp
	${OCBS_DIR}/OcBsDwgPreviewImage.h
	${OCBS_DIR}/OcBsDwgSentinels.cpp
	${OCBS_DIR}/OcBsDwgSentinels.h
	${OCBS_DIR}/OcBsStream.cpp
	${OCBS_DIR}/OcBsStream.h
	${OCBS_DIR}/OcBsStreamIn.cpp
	${OCBS_DIR}/OcBsStreamIn.h
	${OCBS_DIR}/OcBsTypes.h
)

# Private files in the OcDb directory. Will also be
# used for the group filter OcDb in MSVC IDE
set (OCDB_FILES
	${OCDB_DIR}/OcDbClass.cpp
	${OCDB_DIR}/OcDbClass.h
	${OCDB_DIR}/OcDbClasses.cpp
	${OCDB_DIR}/OcDbClasses.h	
	${OCDB_DIR}/OcDbDatabase.cpp	
	${OCDB_DIR}/OcDbDwgObjectMap.cpp
	${OCDB_DIR}/OcDbDwgObjectMap.h
	${OCDB_DIR}/OcDbDwgVersion.cpp
	${OCDB_DIR}/OcDbEntity.cpp
	${OCDB_DIR}/OcDbHardOwnershipId.cpp
	${OCDB_DIR}/OcDbHeaderVars.cpp
	${OCDB_DIR}/OcDbHeaderVars.h
	${OCDB_DIR}/OcDbObject.cpp
	${OCDB_DIR}/OcDbObjectId.cpp
)

# Private files in the OcGe directory. Will also be
# used for the group filter OcGe in MSVC IDE
set (OCGE_FILES
	${OCGE_DIR}/OcGePoint2D.cpp
	${OCGE_DIR}/OcGePoint3D.cpp
)

# Private files in the OcRx directory. Will also be
# used for the group filter OcRx in MSVC IDE
set (OCRX_FILES
	${OCRX_DIR}/OcRxClass.cpp
	${OCRX_DIR}/OcRxObject.cpp
)

# Add IDE file group filters
source_group(PublicHeaders FILES ${PUBLIC_HEADERS})
source_group(OcAp          FILES ${OCAP_FILES})
source_group(OcBs          FILES ${OCBS_FILES})
source_group(OcDb          FILES ${OCDB_FILES})
source_group(OcGe          FILES ${OCGE_FILES})
source_group(OcRx          FILES ${OCRX_FILES})

# Add precompiled header support
if(MSVC AND USE_PRECOMPILED_HEADER)
	foreach (ITEM IN LISTS OCBS_FILES OCDB_FILES OCGE_FILES OCRX_FILES)
		string (REGEX MATCH ".\\(c|cc|cpp|cxx\\)" MATCHED ${ITEM})
		if(MATCHED)
			set (PRECOMP_FILES ${PRECOMP_FILES} ${ITEM})
		endif(MATCHED)
	endforeach(ITEM)
	ADD_MSVC_PRECOMPILED_HEADER("precompiled.h" "precompiled.cpp" PRECOMP_FILES)
	set(PRECOMP_FILES precompiled.cpp precompiled.h)
endif(MSVC AND USE_PRECOMPILED_HEADER)

add_library(libDrawGin
		${PUBLIC_HEADERS}
		${OCAP_FILES}
		${OCBS_FILES}
		${OCDB_FILES}
		${OCGE_FILES}
		${OCRX_FILES}
		${PRECOMP_FILES}
)

