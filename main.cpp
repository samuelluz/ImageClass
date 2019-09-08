/**
 * @author Samuel Luz Gomes <samuelluz.g@gmail.com>
*/
#include "Imagem.h"

/**
 * Obtem dados apartir de uma imagem (Gray) e retorn uma matriz de pixels
 * 
 * @param altura da imagem
 * @param largura da imagem
 * @param nome do arquivo de imagem
 * @return matriz de pixels da imagem
*/
int** get_caracteres(int& a, int& l, char* filename)
{
    int** img;

  	int x, y;
	uchar *canal;
	IplImage *image = cvLoadImage(filename,0);
	canal = (uchar *)image->imageData;

	a = (image->height);//Numero de linhas(altura).
	l = (image->width);//Numero de colunas(largura).

	img = new int*[image->width];//da um New em uma matriz do tamanho da imagem carregada.
    for(int i=0 ; i<(image->width) ; i++)
    {
    img[i] = new int[image->height];
    }

	for(y = 0; y < a; y++)
    {
		canal =(uchar *) (image->imageData + y*(image->widthStep));
		for(x = 0; x < l; x++)
		  img[x][y] = canal[x];

	}/*for*/

	return img;
}

/**
 * Exibe uma imagem
 * 
 * @param altura da imagem
 * @param largura da imagem
 * @param matriz de pixels
 * @param nome da imagem
 */
void put_caracteres(int a, int l, int** img, char* filename)
{
    IplImage *image = cvCreateImage(cvSize(l,a),IPL_DEPTH_8U,0);
	int i,j;
	uchar *canal;
	canal = (uchar *)image->imageData;

	for(j = 0; j < (image->height); j++)
    {
		canal =(uchar *) (image->imageData + j*(image->widthStep));
		for(i = 0; i < (image->width); i++)
		{
            canal[i]=img[i][j];
		}/*for interno*/
	}/*for*/
    cvNamedWindow(filename, 0);
    cvShowImage(filename, image);
}
/**
 * Destrutor de imagens.
 * 
 * @param altura da imagem
 * @param matriz de pixels
*/
void del(int a,int** img)
{
    for(int i=0 ; i < a ; i++)
    {
        delete[]img[i];
    }
    delete[]img;
}
main()
{
    int a,l;
    int** img;
    img = get_caracteres(a, l, "pic5.png");

    Imagem teste1(a , l);
    teste1.setImagem(img);
    teste1.limiar(60);
    put_caracteres(a, l, teste1.imgPro,"ImgPro1");
    del(a, img);

    Imagem teste(512 , 512);
    teste.fCopyFile(teste.alt,teste.larg ,"Dpoc3.txt");
    put_caracteres(teste.alt, teste.larg, teste.imgOri,"Dpoc3.txt");

    teste.fCopyFile(teste.alt,teste.larg ,"test5.txt");
    put_caracteres(teste.alt, teste.larg, teste.imgOri,"test5.txt");

    teste.fCopyFile(teste.alt,teste.larg ,"porco_desc.txt");
    put_caracteres(teste.alt, teste.larg, teste.imgOri,"porco_desc.txt");

    teste.fCopyFile(teste.alt,teste.larg ,"IM0013_0.txt");
    put_caracteres(teste.alt, teste.larg, teste.imgOri,"IM0013_0.txt");


    teste.media(3);
    put_caracteres(teste.alt, teste.larg, teste.imgPro,"ImgPro");

    cvWaitKey(0);

}/*fim main*/



