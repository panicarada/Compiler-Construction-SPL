#The Target Binary Program
LEX			:= flex
YACC		:= bison
TARGET      := main
CC			:= g++
#The Directories, Source, Includes, Objects, Binary and Resources
SOURCE_DIR  := source
INCLUDE_DIR := include
LEX_YACC	:= lex_yacc
BUILD_DIR   := build
TARGET_DIR  := bin
SRC_EXT     := cpp
DEP_EXT     := d
OBJEXT      := o

#Flags, Libraries and Includes
CPPFLAGS	:= -std=c++17
INCLUDE     := -I$(INCLUDE_DIR)
DEPENDENCY  := -I$(INCLUDE_DIR)

# flex和bison文件名
FLEX_FILE	:= lex
BISON_FILE	:= yacc

#---------------------------------------------------------------------------------
#不要修改下面
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SOURCE_DIR) -type f -name *.$(SRC_EXT))
OBJECTS     := $(patsubst $(SOURCE_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.$(OBJEXT)))

#Defauilt Make
all: lex yacc resources $(TARGET)

lex:
	$(LEX) -o $(SOURCE_DIR)/$(FLEX_FILE).yy.cpp $(LEX_YACC)/$(FLEX_FILE).l

yacc:
	$(YACC) -o $(SOURCE_DIR)/$(BISON_FILE).tab.cpp $(LEX_YACC)/$(BISON_FILE).y -d
# 把生成的yacc.tab.hpp转移到include路径
	@mv $(SOURCE_DIR)/$(BISON_FILE).tab.hpp $(INCLUDE_DIR)/

#Remake
remake: cleaner all

#Make the Directories
directories:
	@mkdir -p $(TARGET_DIR)
	@mkdir -p $(BUILD_DIR)

#Clean only Objecst
clean:
	@$(RM) -rf $(BUILD_DIR)

#Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGET_DIR)

#Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEP_EXT))

#Link
$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET_DIR)/$(TARGET) 

#Compile
$(BUILD_DIR)/%.$(OBJEXT): $(SOURCE_DIR)/%.$(SRC_EXT)
	@mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) $(INCLUDE) -c -o $@ $<
	@$(CC) $(CPPFLAGS) $(DEPENDENCY) -MM $(SOURCE_DIR)/$*.$(SRC_EXT) > $(BUILD_DIR)/$*.$(DEP_EXT)
	@cp -f $(BUILD_DIR)/$*.$(DEP_EXT) $(BUILD_DIR)/$*.$(DEP_EXT).tmp
	@sed -e 's|.*:|$(BUILD_DIR)/$*.$(OBJEXT):|' < $(BUILD_DIR)/$*.$(DEP_EXT).tmp > $(BUILD_DIR)/$*.$(DEP_EXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILD_DIR)/$*.$(DEP_EXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILD_DIR)/$*.$(DEP_EXT)
	@rm -f $(BUILD_DIR)/$*.$(DEP_EXT).tmp

	
#Non-File Targets
.PHONY: all remake clean cleaner resources