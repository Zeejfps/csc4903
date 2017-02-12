OUT = ZsAwesomeGame9000

OGRE_PATH = /home/zeejfps/Programming/Game-Engine/libs/ogre_src_v1-8-1
BOOST_PATH = /home/zeejfps/Programming/Game-Engine/libs/boost_1_63_0

CC = g++

SRCDIR = ./src
OUTDIR = ./out
INCDIR = -I$(SRCDIR) -I$(OGRE_PATH)/OgreMain/include -I$(BOOST_PATH) -I$(OGRE_PATH)/build/include
LIBDIR = -L$(OUTDIR) -L$(OGRE_PATH)/build/lib -L$(BOOST_PATH)/stage/lib

LIBS = -lboost_system -lOgreMain -ltinyxml

COMPILE = $(CC) $(INCDIR) -c $< -o $@
LINK = $(CC) $(LIBDIR) -o

FILES = $(OUTDIR)/GameDriver.o $(OUTDIR)/GameManager.o $(OUTDIR)/RenderManager.o $(OUTDIR)/SimpleScene.o

$(OUT): $(FILES)
	$(LINK)  $(OUT) $(FILES) $(LIBS)

run: $(OUT)
	export LD_LIBRARY_PATH=/home/zeejfps/Programming/Game-Engine/libs/ogre_src_v1-8-1/build/lib/ && ./$(OUT)

$(OUTDIR)/GameDriver.o: $(SRCDIR)/GameDriver.cpp
	$(COMPILE)

$(OUTDIR)/GameManager.o: $(SRCDIR)/GameManager.cpp $(SRCDIR)/GameManager.h
	$(COMPILE)

$(OUTDIR)/RenderManager.o: $(SRCDIR)/RenderManager.cpp $(SRCDIR)/RenderManager.h $(SRCDIR)/SceneParser.h
	$(COMPILE)

$(OUTDIR)/SimpleScene.o: $(SRCDIR)/SimpleScene.cpp $(SRCDIR)/SimpleScene.h $(SRCDIR)/SceneParser.h
	$(COMPILE)

.PHONY: clean
clean:
	rm -f $(OUTDIR)/*.o $(OUT) Ogre.log
