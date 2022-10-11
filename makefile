EXECUTABLE_NAME = slot.exe

DIR_SRCS = srcs
DIR_LIBS = libs
DIR_INCLUDES = includes
DIR_BIN = bin
DIR_OBJS = $(DIR_SRCS)\objs

LIBS = SDL2.lib SDL2main.lib SDL2test.lib

all: $(EXECUTABLE_NAME)

clean :
	@if exist $(DIR_BIN)\$(EXECUTABLE_NAME) del /F $(DIR_BIN)\$(EXECUTABLE_NAME)
	@if exist $(DIR_OBJS) rmdir /S /Q $(DIR_OBJS)

$(EXECUTABLE_NAME) : $(DIR_OBJS)\*.obj
	@if not exist $(DIR_BIN) mkdir $(DIR_BIN)
	@echo.
	@echo LINKING $(EXECUTABLE_NAME) ...
	@link /SUBSYSTEM:CONSOLE /LIBPATH:$(DIR_LIBS) /OUT:$(DIR_BIN)\$(EXECUTABLE_NAME) $(LIBS) $(DIR_OBJS)\*.obj

{$(DIR_SRCS)}.cpp{$(DIR_OBJS)}.obj ::
	@if not exist $(DIR_OBJS) mkdir $(DIR_OBJS)
	@echo.
	@echo COMPILING ...
	@cl /c /EHsc /Fo$(DIR_OBJS)\ /I$(DIR_INCLUDES) $<

run : all
	@cd $(DIR_BIN)
	@echo.
	@echo Running $(EXECUTABLE_NAME) ...
	@$(EXECUTABLE_NAME)
	@cd ..