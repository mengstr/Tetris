.PHONY: all clean
.SILENT:


#
# Paths
#
SrcDir        = source
AppIncludes   = includes
ACT           = C:/eVoAps/ACT2000/1.9.0
SDK           = C:/eVoAps/SDK/1.2.0/VRXSDK/3.8.6
EOSSDK        = C:/eVoAps/SDK/1.2.0/EOSSDK/EOSSDK011-01100103
EOS           = C:/eVoAps/SDK/1.2.0/EOSSDK/EOS011-01160106

#
#  Compiler/Linker Output Paths
#
ObjDir        = output/$(Target)/obj
OutDir        = output/$(Target)/out


#
# Create destination directories
#
$(shell if not exist $(ObjDir)\NUL mkdir $(ObjDir))
$(shell if not exist $(OutDir)\NUL mkdir $(OutDir))
$(shell if not exist $(OutDir)\files\NUL mkdir $(OutDir)\files)


#
# Includes
# 
Includes =						                                         \
	-I$(ACT)/Include                                             \
	-I$(SDK)/Include			                                       \
	-I$(EOSSDK)/Include			                                     \
	-I$(AppIncludes)


#
# Compiler options
#
ARMCC_OPT="-armcc,--diag_suppress 161,--exceptions"
COptions = -g -b -W -DLOGSYS_FLAG


#
# Dependencies
#
AppObjects =                                                   \
	$(ObjDir)/board.o                                            \
	$(ObjDir)/console.o                                          \
	$(ObjDir)/main.o                                             \
	$(ObjDir)/tetris.o                                           \


#
# Libraries
#
Libs =                                                         \
	$(ACT)/OutPut/RV/Files/Static/Release/ACT2000.a              \
	$(SDK)/lib/VxSTLn.a                                          \
	$(EOSSDK)/lib/CEIF.o                                         \
	$(EOSSDK)/lib/elog.o                                         \
	$(EOSSDK)/lib/svc_net.o                                      \


all: $(OutDir)/$(Target).out


#
#  Default Target Definition
#
$(OutDir)/$(Target).out : $(AppObjects) $(Libs) $(OutDir)/download.bat
	echo Linking...
	$(SDK)\bin\vrxcc -g -map -b $(AppObjects) $(Libs) -o "$@"
	$(SDK)\bin\vrxhdr -s 1750000 -h 2050000 -l ceif.lib=N:/ceif.lib -l net.lib=N:/net.lib -l elog.lib=N:/elog.lib "$@"
	FileSignature --file "$(abspath $@)" F
	if exist Certif.crt move Certif.crt $(subst /,\,$(OutDir))
	if exist SponsorCert.crt move SponsorCert.crt $(subst /,\,$(OutDir))
	echo $@: Build complete.


# Create download script. We pipe the output of ddl through sed to strip out the
# backspace characters ddl uses to update the number of bytes downloaded so far,
# as these are annoying in the logfile.
$(OutDir)/download.bat: $(OutDir)/download.dld
	echo Generating download batch file...
	echo ddl -p9 %%* -fdownload.dld > $@
	echo @pause >> $@


$(OutDir)/download.dld:
	echo Generating download script...
	echo setdrive.i > $@
	echo setgroup.1 >> $@
	echo *GO=F:$(Target).out >> $@
	echo $(Target).out.p7s >> $@
	echo setdrive.f >> $@
	echo $(Target).out >> $@
	echo files\Tetris.bmp >> $@
	echo files\background.bmp >> $@
	echo files\BATTERY.VFT >> $@
	echo setdrive.i >> $@
	echo setgroup.15 >> $@
	echo #LOGPORT=COM1 >> $@
	echo files\lsys.lib.P7S >> $@
	echo setdrive.f >> $@
	$(subst /,\,copy $(ACT)\OutPut\RV\Files\Shlib1\Release\lsys.lib $(OutDir)\files)
	$(subst /,\,copy Resources\Tetris.bmp $(OutDir)\files)
	$(subst /,\,copy Resources\background.bmp $(OutDir)\files)
	$(subst /,\,copy Resources\BATTERY.VFT $(OutDir)\files)
	echo files\lsys.lib >> $@
	FileSignature --file "$(subst /,\,$(OutDir))\files\lsys.lib" F


#
# Compile cpp files
#
$(ObjDir)/%.o: $(SrcDir)/%.cpp
	echo Compiling $<
	$(SDK)\bin\vrxcc -c $(Includes) $(COptions) $(ARMCC_OPT) $< -o "$@"


#
# Compile c files
#
$(ObjDir)/%.o: $(SrcDir)/%.c
	echo Compiling $<
	$(SDK)\bin\vrxcc -c $(Includes) $(COptions) $(ARMCC_OPT) $< -o "$@"


#
# clean target to delete all build products
#
clean:
	del "$(subst /,\,$(OutDir))\*.out"
	del "$(subst /,\,$(OutDir))\*.o"
