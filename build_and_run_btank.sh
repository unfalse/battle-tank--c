gcc -Wextra -pedantic -g btank.c graphics.c events.c keyboard.c ltimer.c -c ; gcc btank.o graphics.o events.o keyboard.o ltimer.o -lSDL2 -lSDL2_image -lSDL2_ttf -o btank ; ./btank
