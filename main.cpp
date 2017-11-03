//Algoritma Bresenham

#include <GL\glut.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

//identifier fungsi
void init();
void display(void);
void bresenham(void);

//  posisi window di layar
int window_x,window_y;

int x1,y1,x2,y2;

//  ukuran window
int window_width = 512;
int window_height = 512;

//  judul window
char *judul_window = "Algoritma Bresenham";

int main(int argc, char **argv)
{
 	int inputx1,inputy1,inputx2,inputy2;
	awal:
	cout<<"ALGORITMA BRESENHAM\n\n";
	cout<<"Input nilai harus integer positif \n";
    cout<<"Masukkan nilai x1 : ";cin>>inputx1;
    cout<<"Masukkan nilai y1 : ";cin>>inputy1;
    cout<<"\nMasukkan nilai x2 : ";cin>>inputx2;
    cout<<"Masukkan nilai y2 : ";cin>>inputy2;
    if((inputx1 < 0) || (inputy1 < 0) || (inputx2 < 0) || (inputy2 < 0)){
        cout<<"Nilai masukan ada yang bernilai negatif\n";
        goto awal;
    }else{
        x1 = inputx1;
        y1 = inputy1;
        x2 = inputx2;
        y2 = inputy2;
    }
    cout<<endl;
	//  inisialisasi GLUT (OpenGL Utility Toolkit)
	glutInit(&argc, argv);
	// set posisi window supaya berada di tengah
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
	glutInitWindowSize(window_width, window_height); //set ukuran window
	glutInitWindowPosition(window_x, window_y); //set posisi window

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE); // set display RGB dan double buffer
	glutCreateWindow(judul_window); //set judul window


	init(); //jalankan fungsi init
	glutDisplayFunc(display); //  set fungsi display
	glutMainLoop(); // set loop pemrosesan GLUT
}

void init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0); //set warna background
	glColor3f(1.0, 1.0, 1.0); //set warna titik
	glPointSize(2.0); //set ukuran titik
	glMatrixMode(GL_PROJECTION); //set mode matriks yang digunakan
	glLoadIdentity(); // load matriks identitas
	gluOrtho2D(0.0, 800.0, 0.0, 600.0); // set ukuran viewing window
}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //clear color
	bresenham(); //jalankan fungsi bresenham
	glutSwapBuffers(); //swap buffer
}

void bresenham(void) {
	int x, y, dx, dy, yend, p, duadx, duadxdy;
	int duady,duadydx,xend;

	///hitung dx dan dy
	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	//hitung p
	if(dy>dx){   ///untuk garis yang mendekati vertikal
        p = 2*dx - dy;
        duadx = 2*dx;
        duadxdy = 2 * (dx - dy);

        ///Menentukan titik awal dan akhir
        if(y1<y2){
            //cout<<"\nMasuk dy dg y1 lebih kecil\n";
            x = x1;
            xend = x2;
            y = y1;
            yend = y2;
        }else{
            //cout<<"\nMasuk dy dg y2 lebih kecil\n";
            x = x2;
            xend = x1;
            y = y2;
            yend = y1;
        }
	}else{  ///untuk garis yang mendekati horisontal
        p = 2*dy - dx;
        duady = 2*dy;
        duadydx = 2*(dy - dx);

        ///Menentukan titik awal dan akhir
        if(x1<x2){
            //cout<<"\nMasuk dx dg x1 lebih kecil\n";
            x = x1;
            xend = x2;
            y = y1;
            yend = y2;
        }else{
            //cout<<"\nMasuk dx dg x2 lebih kecil x\n";
            x = x2;
            xend = x1;
            y = y2;
            yend = y1;
        }
	}
	///gambar titik awal
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	cout<<"("<<x<<","<<y<<")\n";

	///perulangan untuk menggambar titik-titik

	do { ///kondisi : (garis -> vertikal || garis -> hor) (dy>dx || dy=<dx)
        if(dy>dx){ ///kondisi dy lebih besar
            y++; ///y selalu nambah
            if (p < 0) {
                p += duadx;
            }
            else{
                if (x > xend){ ///cek x
                    x--;
                }else
                    x++;
                p += duadxdy;
            }
        }else{ ///kondisi dx lebih besar
            x++; ///x selalu nambah
            if (p < 0) {
                p += duady;
            }
            else{
                if (y > yend){ ///cek x
                    y--;
                }else
                    y++;
                p += duadydx;
            }
        }
        glVertex2i(x, y);
        cout<<"("<<x<<","<<y<<")\n";
	}while(y < yend || x < xend); ///kondisi : (garis -> vertikal || garis -> hor) (dy>dx || dy=<dx)

	glEnd();
	glFlush();
}

