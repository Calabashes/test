#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include "test.h"
#include "bmplib.h"



#define FB_DEV_NAME		"/dev/fb0"
#define RED_COLOR565	0X0F100
#define GREEN_COLOR565	0X007E0
#define BLUE_COLOR565	0X0001F

#define RED_COLOR888		0XFF0000
#define GREEN_COLOR888	0X00FF00
#define BLUE_COLOR888	0XFF

#if 0

int main()
{
	fb_dev_t *fbd;
	fbd = (fb_dev_t *)malloc(sizeof(fb_dev_t));

	fb_open(fbd, FB_DEV_NAME);
	printf("\n%s\n",FB_DEV_NAME);


	printf("fbd->bpp = %d\n",fbd->bpp);
	

	if(fbd->bpp == 16) {
		fb_drawrect(fbd, 0, 0, fbd->xres, fbd->yres, RED_COLOR565);
//		printf("22222222222222\n");
		//fb_drawrect(fbd, 0, fbd->yres/3, fbd->xres, fbd->yres * 2/3, GREEN_COLOR565);
		printf("kkkkkkkkkkkkkk\n");
		//fb_drawrect(fbd, 0, fbd->yres * 2/3, fbd->xres, fbd->yres/3, BLUE_COLOR565);
	}else {

		//fb_drawrect(fbd, 0, 0, fbd->xres, fbd->yres, 0Xffffffff);
		printf("mmmmmmmmmmmmmmmmmmmmmmm\n");
	

		fb_drawrect(fbd, 0, 0, fbd->xres, fbd->yres, RED_COLOR888);
		
	//	fb_drawrect(fbd, 0, fbd->yres, fbd->xres, fbd->yres, GREEN_COLOR888);
		//printf("444444444444444\n");
	//	fb_drawrect(fbd, 0, 0, fbd->xres, fbd->yres, BLUE_COLOR888);


	}


	free(fbd);
	return 0;
}

#endif

#if 1
int main(int argc, char *argv[])
{
	fb_dev_t *fbd;

	fbd = (fb_dev_t*)malloc(sizeof(fb_dev_t));
	if(fbd == NULL) {
		printf("malloc fail\n");
		return -1;
	}

	printf("Input the picture is %s\n",argv[1]);
	printf("DEV_NAME = %s\n", FB_DEV_NAME);
	fb_open(fbd, FB_DEV_NAME);

	fb_drawbmp(fbd, 0, 0, argv[1]);

	fb_close(fbd);

	free(fbd);

	return 0;

}


#endif
