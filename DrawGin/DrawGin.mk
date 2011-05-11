##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=DrawGin
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/paul/testhg/drawgin"
ProjectPath            := "/home/paul/testhg/drawgin/DrawGin"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Paul Kohut
Date                   :=05/10/2011
CodeLitePath           :="/home/paul/.codelite"
LinkerName             :=g++-4.5
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=g++-4.5 -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=g++-4.5
C_CompilerName         :=gcc-4.5
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)_DEBUG $(PreprocessorSwitch)_CONSOLE $(PreprocessorSwitch)GOOGLE_GLOG_DLL_DECL= 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="/home/paul/testhg/drawgin/DrawGin/DrawGin.txt"
MakeDirCommand         :=mkdir -p
CmpOptions             := -g -Wall -Wextra $(Preprocessors)
C_CmpOptions           := -g -Wall -Wextra $(Preprocessors)
LinkOptions            :=  -O0
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)inc 
RcIncludePath          :=
Libs                   :=$(LibrarySwitch)glog 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)/usr/local/lib 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/DrawGin$(ObjectSuffix) $(IntermediateDirectory)/stdafx$(ObjectSuffix) $(IntermediateDirectory)/OcBs_DwgInArchive$(ObjectSuffix) $(IntermediateDirectory)/OcBs_OcBsDwgCrc$(ObjectSuffix) $(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(ObjectSuffix) $(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(ObjectSuffix) $(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(ObjectSuffix) $(IntermediateDirectory)/OcBs_OcBsStream$(ObjectSuffix) $(IntermediateDirectory)/OcBs_OcBsStreamIn$(ObjectSuffix) $(IntermediateDirectory)/OcDb_OcDbDatabase$(ObjectSuffix) \
	$(IntermediateDirectory)/OcDb_OcDbDwgVersion$(ObjectSuffix) $(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(ObjectSuffix) $(IntermediateDirectory)/OcDb_OcDbHeaderVars$(ObjectSuffix) $(IntermediateDirectory)/OcDb_OcDbObject$(ObjectSuffix) $(IntermediateDirectory)/OcDb_OcDbObjectId$(ObjectSuffix) $(IntermediateDirectory)/OcRx_OcRxObject$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

objects_file:
	@echo $(Objects) > $(ObjectsFileList)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/DrawGin$(ObjectSuffix): DrawGin.cpp $(IntermediateDirectory)/DrawGin$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/DrawGin.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/DrawGin$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/DrawGin$(DependSuffix): DrawGin.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/DrawGin$(ObjectSuffix) -MF$(IntermediateDirectory)/DrawGin$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/DrawGin.cpp"

$(IntermediateDirectory)/DrawGin$(PreprocessSuffix): DrawGin.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/DrawGin$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/DrawGin.cpp"

$(IntermediateDirectory)/stdafx$(ObjectSuffix): stdafx.cpp $(IntermediateDirectory)/stdafx$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/stdafx.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/stdafx$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/stdafx$(DependSuffix): stdafx.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/stdafx$(ObjectSuffix) -MF$(IntermediateDirectory)/stdafx$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/stdafx.cpp"

$(IntermediateDirectory)/stdafx$(PreprocessSuffix): stdafx.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/stdafx$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/stdafx.cpp"

$(IntermediateDirectory)/OcBs_DwgInArchive$(ObjectSuffix): src/OcBs/DwgInArchive.cpp $(IntermediateDirectory)/OcBs_DwgInArchive$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/DwgInArchive.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcBs_DwgInArchive$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcBs_DwgInArchive$(DependSuffix): src/OcBs/DwgInArchive.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcBs_DwgInArchive$(ObjectSuffix) -MF$(IntermediateDirectory)/OcBs_DwgInArchive$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcBs/DwgInArchive.cpp"

$(IntermediateDirectory)/OcBs_DwgInArchive$(PreprocessSuffix): src/OcBs/DwgInArchive.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcBs_DwgInArchive$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/DwgInArchive.cpp"

$(IntermediateDirectory)/OcBs_OcBsDwgCrc$(ObjectSuffix): src/OcBs/OcBsDwgCrc.cpp $(IntermediateDirectory)/OcBs_OcBsDwgCrc$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgCrc.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcBs_OcBsDwgCrc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcBs_OcBsDwgCrc$(DependSuffix): src/OcBs/OcBsDwgCrc.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcBs_OcBsDwgCrc$(ObjectSuffix) -MF$(IntermediateDirectory)/OcBs_OcBsDwgCrc$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgCrc.cpp"

$(IntermediateDirectory)/OcBs_OcBsDwgCrc$(PreprocessSuffix): src/OcBs/OcBsDwgCrc.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcBs_OcBsDwgCrc$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgCrc.cpp"

$(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(ObjectSuffix): src/OcBs/OcBsDwgFileHeader.cpp $(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgFileHeader.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(DependSuffix): src/OcBs/OcBsDwgFileHeader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(ObjectSuffix) -MF$(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgFileHeader.cpp"

$(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(PreprocessSuffix): src/OcBs/OcBsDwgFileHeader.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgFileHeader.cpp"

$(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(ObjectSuffix): src/OcBs/OcBsDwgPreviewImage.cpp $(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgPreviewImage.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(DependSuffix): src/OcBs/OcBsDwgPreviewImage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(ObjectSuffix) -MF$(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgPreviewImage.cpp"

$(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(PreprocessSuffix): src/OcBs/OcBsDwgPreviewImage.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgPreviewImage.cpp"

$(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(ObjectSuffix): src/OcBs/OcBsDwgSentinels.cpp $(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgSentinels.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(DependSuffix): src/OcBs/OcBsDwgSentinels.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(ObjectSuffix) -MF$(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgSentinels.cpp"

$(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(PreprocessSuffix): src/OcBs/OcBsDwgSentinels.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsDwgSentinels.cpp"

$(IntermediateDirectory)/OcBs_OcBsStream$(ObjectSuffix): src/OcBs/OcBsStream.cpp $(IntermediateDirectory)/OcBs_OcBsStream$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsStream.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcBs_OcBsStream$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcBs_OcBsStream$(DependSuffix): src/OcBs/OcBsStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcBs_OcBsStream$(ObjectSuffix) -MF$(IntermediateDirectory)/OcBs_OcBsStream$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsStream.cpp"

$(IntermediateDirectory)/OcBs_OcBsStream$(PreprocessSuffix): src/OcBs/OcBsStream.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcBs_OcBsStream$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsStream.cpp"

$(IntermediateDirectory)/OcBs_OcBsStreamIn$(ObjectSuffix): src/OcBs/OcBsStreamIn.cpp $(IntermediateDirectory)/OcBs_OcBsStreamIn$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsStreamIn.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcBs_OcBsStreamIn$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcBs_OcBsStreamIn$(DependSuffix): src/OcBs/OcBsStreamIn.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcBs_OcBsStreamIn$(ObjectSuffix) -MF$(IntermediateDirectory)/OcBs_OcBsStreamIn$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsStreamIn.cpp"

$(IntermediateDirectory)/OcBs_OcBsStreamIn$(PreprocessSuffix): src/OcBs/OcBsStreamIn.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcBs_OcBsStreamIn$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcBs/OcBsStreamIn.cpp"

$(IntermediateDirectory)/OcDb_OcDbDatabase$(ObjectSuffix): src/OcDb/OcDbDatabase.cpp $(IntermediateDirectory)/OcDb_OcDbDatabase$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbDatabase.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcDb_OcDbDatabase$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcDb_OcDbDatabase$(DependSuffix): src/OcDb/OcDbDatabase.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcDb_OcDbDatabase$(ObjectSuffix) -MF$(IntermediateDirectory)/OcDb_OcDbDatabase$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbDatabase.cpp"

$(IntermediateDirectory)/OcDb_OcDbDatabase$(PreprocessSuffix): src/OcDb/OcDbDatabase.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcDb_OcDbDatabase$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbDatabase.cpp"

$(IntermediateDirectory)/OcDb_OcDbDwgVersion$(ObjectSuffix): src/OcDb/OcDbDwgVersion.cpp $(IntermediateDirectory)/OcDb_OcDbDwgVersion$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbDwgVersion.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcDb_OcDbDwgVersion$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcDb_OcDbDwgVersion$(DependSuffix): src/OcDb/OcDbDwgVersion.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcDb_OcDbDwgVersion$(ObjectSuffix) -MF$(IntermediateDirectory)/OcDb_OcDbDwgVersion$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbDwgVersion.cpp"

$(IntermediateDirectory)/OcDb_OcDbDwgVersion$(PreprocessSuffix): src/OcDb/OcDbDwgVersion.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcDb_OcDbDwgVersion$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbDwgVersion.cpp"

$(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(ObjectSuffix): src/OcDb/OcDbHardOwnershipId.cpp $(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbHardOwnershipId.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(DependSuffix): src/OcDb/OcDbHardOwnershipId.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(ObjectSuffix) -MF$(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbHardOwnershipId.cpp"

$(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(PreprocessSuffix): src/OcDb/OcDbHardOwnershipId.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbHardOwnershipId.cpp"

$(IntermediateDirectory)/OcDb_OcDbHeaderVars$(ObjectSuffix): src/OcDb/OcDbHeaderVars.cpp $(IntermediateDirectory)/OcDb_OcDbHeaderVars$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbHeaderVars.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcDb_OcDbHeaderVars$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcDb_OcDbHeaderVars$(DependSuffix): src/OcDb/OcDbHeaderVars.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcDb_OcDbHeaderVars$(ObjectSuffix) -MF$(IntermediateDirectory)/OcDb_OcDbHeaderVars$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbHeaderVars.cpp"

$(IntermediateDirectory)/OcDb_OcDbHeaderVars$(PreprocessSuffix): src/OcDb/OcDbHeaderVars.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcDb_OcDbHeaderVars$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbHeaderVars.cpp"

$(IntermediateDirectory)/OcDb_OcDbObject$(ObjectSuffix): src/OcDb/OcDbObject.cpp $(IntermediateDirectory)/OcDb_OcDbObject$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbObject.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcDb_OcDbObject$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcDb_OcDbObject$(DependSuffix): src/OcDb/OcDbObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcDb_OcDbObject$(ObjectSuffix) -MF$(IntermediateDirectory)/OcDb_OcDbObject$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbObject.cpp"

$(IntermediateDirectory)/OcDb_OcDbObject$(PreprocessSuffix): src/OcDb/OcDbObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcDb_OcDbObject$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbObject.cpp"

$(IntermediateDirectory)/OcDb_OcDbObjectId$(ObjectSuffix): src/OcDb/OcDbObjectId.cpp $(IntermediateDirectory)/OcDb_OcDbObjectId$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbObjectId.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcDb_OcDbObjectId$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcDb_OcDbObjectId$(DependSuffix): src/OcDb/OcDbObjectId.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcDb_OcDbObjectId$(ObjectSuffix) -MF$(IntermediateDirectory)/OcDb_OcDbObjectId$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbObjectId.cpp"

$(IntermediateDirectory)/OcDb_OcDbObjectId$(PreprocessSuffix): src/OcDb/OcDbObjectId.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcDb_OcDbObjectId$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcDb/OcDbObjectId.cpp"

$(IntermediateDirectory)/OcRx_OcRxObject$(ObjectSuffix): src/OcRx/OcRxObject.cpp $(IntermediateDirectory)/OcRx_OcRxObject$(DependSuffix)
	$(CompilerName) $(SourceSwitch) "/home/paul/testhg/drawgin/DrawGin/src/OcRx/OcRxObject.cpp" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/OcRx_OcRxObject$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/OcRx_OcRxObject$(DependSuffix): src/OcRx/OcRxObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/OcRx_OcRxObject$(ObjectSuffix) -MF$(IntermediateDirectory)/OcRx_OcRxObject$(DependSuffix) -MM "/home/paul/testhg/drawgin/DrawGin/src/OcRx/OcRxObject.cpp"

$(IntermediateDirectory)/OcRx_OcRxObject$(PreprocessSuffix): src/OcRx/OcRxObject.cpp
	@$(CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/OcRx_OcRxObject$(PreprocessSuffix) "/home/paul/testhg/drawgin/DrawGin/src/OcRx/OcRxObject.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/DrawGin$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/DrawGin$(DependSuffix)
	$(RM) $(IntermediateDirectory)/DrawGin$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/stdafx$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/stdafx$(DependSuffix)
	$(RM) $(IntermediateDirectory)/stdafx$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_DwgInArchive$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_DwgInArchive$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_DwgInArchive$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgCrc$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgCrc$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgCrc$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgFileHeader$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgPreviewImage$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsDwgSentinels$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsStream$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsStream$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsStream$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsStreamIn$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsStreamIn$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcBs_OcBsStreamIn$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbDatabase$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbDatabase$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbDatabase$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbDwgVersion$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbDwgVersion$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbDwgVersion$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbHardOwnershipId$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbHeaderVars$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbHeaderVars$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbHeaderVars$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbObject$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbObject$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbObject$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbObjectId$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbObjectId$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcDb_OcDbObjectId$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/OcRx_OcRxObject$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/OcRx_OcRxObject$(DependSuffix)
	$(RM) $(IntermediateDirectory)/OcRx_OcRxObject$(PreprocessSuffix)
	$(RM) $(OutputFile)


