#ifndef Imagem_h
#define Imagem_h

#include <fstream>
#include <iostream>
#include <math.h>
#include "highgui.h"
#include "cv.h"
#include "cxcore.h"
#include "cvaux.h"
using namespace std;


class Imagem
{
  public:

    Imagem (void);
    Imagem (int a, int l);
    Imagem (int a, int l, int** img);
    Imagem (int a, int l, char* filename);

    ~Imagem (void);

    void fNew (int alt,int larg);
    void fCopyFile(int a, int l,char*file);

		void setAltura(int a);
		void setLargura(int l);
		void setImagem(int** img);
		void setImagem(int a, int l, int** img);
		void convertCinza(void);

    void media(int d);
    void mediana(int d);
    void limiar(int l);
		void crescRegiao(int s);
    void setJanela(int l, int n);
		void gaussiana5(void);
		void gaussiana7(void);
    void sobel(void);
    void prewitt(void);
    void roberts(void);
    void calcHistograma(void);

    int* getHistograma(void);

		int** getImgOri(void);
		int** getImgPro(void);
		int** getImgCinza(void);


	//private:
    int alt, larg;
    int** imgPro;
    int** imgOri;
    int** imgCinza;
    int* imgHistograma;

};
#endif
