#define __APPLE__ 1

#include <simple2d.h>

void DrawCircle() {
	S2D_DrawCircle(100, 100, 200, 100, 1, 1, 0, 1) ;
}
int main(int argc, char *argv[]) {
	S2D_Window *pWin = S2D_CreateWindow("MainWindow", 800, 600, nullptr, &DrawCircle, 
		S2D_RESIZABLE) ;
	S2D_Show(pWin) ;
	S2D_FreeWindow(pWin) ;
	return 0;
}