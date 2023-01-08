BUILDDIR := Build
SRCCLIENTDIR := Client
SRCSERVERDIR := Server
SRCSHAREDDIR := Shared
CC := g++.exe
CPPFLAGS := -std=c++23 -MMD
INCLUDES := -I../SFML-2.5.1/include/
LIBS := -L../SFML-2.5.1/lib/
LDLIBS := -lm -lsfml-main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network
LDLIBSSTATIC := -lm -DSFML_STATIC -lwinmm -lsfml-system-s -lws2_32 -lsfml-network-s -lopengl32 -lgdi32 -lsfml-window-s -lfreetype -lsfml-graphics-s -lsfml-main
.PHONY: clean server client
CLIENTOBJS = $(BUILDDIR)/Client/Application.o $(BUILDDIR)/Client/Display/Color.o $(BUILDDIR)/Client/Display/Font.o $(BUILDDIR)/Client/Display/Graphics.o $(BUILDDIR)/Client/Display/Image.o $(BUILDDIR)/Client/Display/Input.o $(BUILDDIR)/Client/Display/Text.o $(BUILDDIR)/Client/Display/Window.o $(BUILDDIR)/Client/Game.o $(BUILDDIR)/Client/GameObjects/Food.o $(BUILDDIR)/Client/GameObjects/GameSpace.o $(BUILDDIR)/Client/GameObjects/Snake.o $(BUILDDIR)/Client/GameStates/GameState.o $(BUILDDIR)/Client/GameStates/GameStateDraw.o $(BUILDDIR)/Client/GameStates/GameStateDummy.o $(BUILDDIR)/Client/GameStates/GameStateLose.o $(BUILDDIR)/Client/GameStates/GameStateMenu.o $(BUILDDIR)/Client/GameStates/GameStatePlaying.o $(BUILDDIR)/Client/GameStates/GameStateSelectIPAndPort.o $(BUILDDIR)/Client/GameStates/GameStateTryToConnect.o $(BUILDDIR)/Client/GameStates/GameStateWin.o $(BUILDDIR)/Client/main.o $(BUILDDIR)/Client/Server.o $(BUILDDIR)/Client/Utility/KeyPresses.o
SERVEROBJS = $(BUILDDIR)/Server/Application.o $(BUILDDIR)/Server/Client.o $(BUILDDIR)/Server/Game.o $(BUILDDIR)/Server/GameObjects/GameSpace.o $(BUILDDIR)/Server/GameObjects/Snake.o $(BUILDDIR)/Server/main.o $(BUILDDIR)/Server/ServerStates/ServerState.o $(BUILDDIR)/Server/ServerStates/ServerStatePlayingGame.o $(BUILDDIR)/Server/ServerStates/ServerStateWaitingForPlayers.o
SHAREDOBJS = $(BUILDDIR)/Shared/DataFromClient.o $(BUILDDIR)/Shared/DataFromServer.o $(BUILDDIR)/Shared/GameObjects/Food.o $(BUILDDIR)/Shared/GameObjects/GameSpaceBase.o $(BUILDDIR)/Shared/GameObjects/Snake.o $(BUILDDIR)/Shared/Utility/Stopwatch.o

$(BUILDDIR):
	mkdir -p $@
	mkdir -p $(BUILDDIR)/Shared
	mkdir -p $(BUILDDIR)/Shared/GameObjects
	mkdir -p $(BUILDDIR)/Shared/Utility
	mkdir -p $(BUILDDIR)/Server
	mkdir -p $(BUILDDIR)/Server/GameObjects
	mkdir -p $(BUILDDIR)/Server/ServerStates
	mkdir -p $(BUILDDIR)/Client
	mkdir -p $(BUILDDIR)/Client/Display
	mkdir -p $(BUILDDIR)/Client/GameObjects
	mkdir -p $(BUILDDIR)/Client/GameStates
	mkdir -p $(BUILDDIR)/Client/Resources
	mkdir -p $(BUILDDIR)/Client/Utility

clean:
	rm -rf $(BUILDDIR)

$(BUILDDIR)/Shared/%.o: Shared/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Shared/$*.o

$(BUILDDIR)/Shared/GameObjects/%.o: Shared/GameObjects/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Shared/GameObjects/$*.o

$(BUILDDIR)/Shared/Utility/%.o: Shared/Utility/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Shared/Utility/$*.o

$(BUILDDIR)/Server/%.o: Server/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Server/$*.o

$(BUILDDIR)/Server/GameObjects/%.o: Server/GameObjects/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Server/GameObjects/$*.o

$(BUILDDIR)/Server/ServerStates/%.o: Server/ServerStates/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Server/ServerStates/$*.o

$(BUILDDIR)/Client/%.o: Client/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Client/$*.o

$(BUILDDIR)/Client/Display/%.o: Client/Display/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Client/Display/$*.o

$(BUILDDIR)/Client/GameObjects/%.o: Client/GameObjects/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Client/GameObjects/$*.o

$(BUILDDIR)/Client/GameStates/%.o: Client/GameStates/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Client/GameStates/$*.o

$(BUILDDIR)/Client/Resources/%.o: Client/Resources/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Client/Resources/$*.o

$(BUILDDIR)/Client/Utility/%.o: Client/Utility/%.cpp $(BUILDDIR)
	$(CC) $< $(INCLUDES) $(CPPFLAGS) -c -o $(BUILDDIR)/Client/Utility/$*.o


client.exe: $(CLIENTOBJS) $(SHAREDOBJS)
	$(CC) $(CPPFLAGS) -o $(BUILDDIR)/$@ $^ $(LIBS) $(LDLIBS) -mwindows
server.exe:	$(SERVEROBJS) $(SHAREDOBJS)
	$(CC) $(CPPFLAGS) -o $(BUILDDIR)/$@ $^ $(LIBS) $(LDLIBS)
all: client.exe server.exe libs
	
libs:
	cp DLL/* $(BUILDDIR)/