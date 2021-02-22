gcc -Wextra -pedantic -g btank.c csw.c graphics.c events.c keyboard.c ltimer.c -c ; gcc btank.o csw.o graphics.o events.o keyboard.o ltimer.o -lSDL2 -lSDL2_image -lSDL2_ttf -o btank
