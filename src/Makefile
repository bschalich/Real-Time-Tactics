all: linux

remake: clean all

mac:
	g++ ActiveHeroIcon.cpp Billboard.cpp Main.cpp AwesomeGL.cpp Camera.cpp Font.cpp UI.cpp ParticleEmitter.cpp Warrior.cpp Archer.cpp Mage.cpp Tween.cpp AStar.cpp Combatant.cpp Projectile.cpp StateMachine.cpp GameController.cpp Entity.cpp GameMap.cpp MapTile.cpp EventHandler.cpp GLSL_helper.cpp MStackHelp.cpp -framework SFML -framework OpenGL -framework SFML-window -framework SFML-system -framework SFML-audio -I/usr/local/Cellar/freetype/2.5.3_1/include/freetype2 -lassimp -L/usr/local/Cellar/freetype/2.5.3_1/lib -lfreetype -lz -lbz2 -L/usr/local/Cellar/libpng/1.6.10/lib -lpng16


linux:
	g++ cube.cpp
clean:
	rm -f *~
	rm -f a.out
	rm -f *.o

