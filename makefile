all: main.o menu.o jeu.o fenetre.o map.o personnage.o boundBox.o scrolling.o sauvegarde.o
	gcc main.o fenetre.o menu.o jeu.o scrolling.o boundBox.o personnage.o map.o sauvegarde.o -o Game -lSDL -lSDL_image  -lSDL_ttf -lSDL_mixer -lSDL_gfx 

main.o: main.c menu.h fenetre.h jeu.h map.h personnage.h scrolling.h sauvegarde.h
	gcc -c main.c -o main.o  -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf
menu.o: menu.c
	gcc -c menu.c -o menu.o -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
jeu.o: jeu.c personnage.h map.h scrolling.h boundBox.h sauvegarde.h
	gcc -c jeu.c  -o jeu.o -lSDL -lSDL_image -lSDL_gfx
map.o: map.c
	gcc -c map.c -o map.o -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

personnage.o: personnage.c
	gcc -c personnage.c -o personnage.o -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf
 
fenetre.o: fenetre.c
	gcc -c fenetre.c -o fenetre.o  -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

scrolling.o: scrolling.c boundBox.h sauvegarde.h
	gcc -c scrolling.c -o scrolling.o  -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf
boundBox.o: boundBox.h
	gcc -c boundBox.c -o boundBox.o -lSDL -lSDL_image
sauvegarde.o:sauvegarde.h
	gcc -c sauvegarde.c -o sauvegarde.o -lSDL -lSDL_image
clean:
	rm -rf *.o

mrproper:
	rm -rf Jeu
