#include <stdio.h>
#include<stdlib.h>
#include<time.h>

//generate number in range [min,max)
int myrandom(int min, int max){
    int number = min + rand() % (max - min);
    return number; 
}

//Driver code
int random_main() {
    srand(time(NULL));
    for(int i = 1; i <= 10; i++){
        printf("%d\t", myrandom(10, 100));
    }
	printf("\n");
    return 0;
}
void func() {
    printf("Hello from func!\n");
}

void files_OpenFIMG() {
    // 1. open file
    FILE *fd;
    unsigned char fbuf[400];
    int filePos = 0;
    int color = 0;
    
    printf("Opening file...\n");
    fd = fopen("images/CSW-MT5.C20", "r");
    if (!fd) {
        printf("ERROR!\n");
    } else {
        printf("SUCCESS!\n");
        printf("Reading...\n");
        fread(fbuf, 400, 1, fd);
        printf("Closing...\n");
	    fclose(fd);
        printf("Results: ");

        // load!
        for (int i=0; i<20; i++) {
            for (int j=0; j<20; j++) {
                color = fbuf[filePos] - 176;
                printf("%d ", color);
                //data.display[i][j] = graphics_editor_colors[color];
                // data.display[i][j].r = 0;
                //data.display[i][j].g = 0;
                //data.display[i][j].b = 0;
                //data.display[i][j].a = 0;
                filePos++;
            }
        }
    }
    printf("\n");
    // 2. read all data from the file
    // 4. copy data to display
}

/*
void Csw_init(struct Csw *csw) {
    *csw.x = 0;
    *csw.y = 0;
}

struct Csw {
    int x;
    int y;
} csw;

struct PCsw {
    Csw cur;
    Csw *next;
} beg, curr, pend;

void CreateCsw() {
    PCsw c1;
    if (beg == null) {
        // new(c1);
        curr = c1;
        //*curr.cur.
        Csw_init(&curr.cur);
        pend = curr;
        curr.next = null;
        beg = c1;
    } else {
        pend.next = c1;
        Csw_init(&c1.cur);
        c1.next = null;
        pend = c1;
        curr = c1;
    }
}
*/

/*
Procedure CreateCsw;
var	c1:pcsw;
begin
	if beg=nil then begin
		new(c1);
		curr:=c1;
		curr^.cur.init(x,y,who,num);
		pend:=curr;
		curr^.next:=nil;
		beg:=c1;
        end
        else begin
		new(c1);
		pend^.next:=c1;
		c1^.cur.init(x,y,who,num);
		c1^.next:=nil;
		pend:=c1;
		curr:=c1;
end;
end;
        */

int main() {
    void (*f)();
    f = func;
    f();
    int i = 100;
    unsigned char c = 200;
    i = c - 176;
    printf("i = %d\n", i);

    //files_OpenFIMG();

    //CreateCsw();
    
	random_main();

    // segfault!
    //const char * s = "hello world";
    //* (char *) s = 'H';
    return 0;
}

