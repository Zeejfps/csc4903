CXX := g++
CXXFLAGS := -c -Wall
LDFLAGS := -lboost_system -lOgreMain -ltinyxml
# LDFLAGS := -lboost_system-mgw51-mt-1_63 -lOgreMain -ltinyxml

############## PATHS FOR WINDOWS ###############
################################################
# OGRE_PATH := J:/Game_Engine/Ogre-1.8.1	  #		
# BOOST_PATH := J:/Game_Engine/boost_1_63_0	  #
# TINYXML_PATH := J:/Game_Engine/tinyxml_2.6.2 #
################################################

OGRE_PATH := /home/zeejfps/Programming/Game-Engine/libs/ogre_src_v1-8-1
BOOST_PATH := /home/zeejfps/Programming/Game-Engine/libs/boost_1_63_0

EXECUTABLE := ZsAwesomeGame9000
OBJ_DIR := out
SRC_DIR := src
INC_DIR := -I$(SRC_DIR) -I$(OGRE_PATH)/OgreMain/include -I$(BOOST_PATH) -I$(OGRE_PATH)/build/include #-I$(TINYXML_PATH)/include
LIB_DIR := -L$(OBJ_DIR) -L$(OGRE_PATH)/build/lib -L$(BOOST_PATH)/stage/lib #-L$(TINYXML_PATH)/lib


SOURCES := GameDriver.cpp GameManager.cpp RenderManager.cpp SimpleScene.cpp
OBJECTS := $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(LIB_DIR) -o $(EXECUTABLE) $(OBJECTS) $(LDFLAGS)
	
run: $(EXECUTABLE)
	export LD_LIBRARY_PATH=/home/zeejfps/Programming/Game-Engine/libs/ogre_src_v1-8-1/build/lib/ && ./$(EXECUTABLE)
	
$(SRC_DIR)/%.d : $(SRC_DIR)/%.cpp
	$(CXX) -MM -MT "$(OBJ_DIR)/$*.o $@" $(INC_DIR) $< -MF $@

	
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INC_DIR) $< -o $@
	

ifneq ($(MAKECMDGOALS),clean)
-include $(SOURCES:%.cpp=$(SRC_DIR)/%.d)
endif

.PHONY: clean
clean:
	@rm -f $(OBJ_DIR)/*.o $(EXECUTABLE) Ogre.log *$(SRC_DIR)/*.d
