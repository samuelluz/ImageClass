#include "Imagem.h"

Imagem teste(300,400);
int num[100][100];

void get_caracteres2(IplImage *imageHSV, int cx, int cy, int r)
{
	int x, y, i,j;
	uchar *canal;
	canal = (uchar *)imageHSV->imageData;

	i=-1; j=-1;
	for(y = cy-r; y < cy+r; y++){
			canal =(uchar *) (imageHSV->imageData + y*(imageHSV->widthStep));
			j++;
			i=0;
		for(x = cx-r; x < cx+r; x++){
			i++;
			if((canal[3*x+1]>200) &&
			   (canal[3*x+2]<40)&& (canal[3*x+2]>10) &&
			   (canal[3*x+0]>85)&&(canal[3*x+0]<120)
				)
			{
				num[i][j]=1;
			}else{
				num[i][j]=0;
			}/*else*/
		}/*for interno*/
	}/*for*/

	//printf("\nNumeros: \n");
	//for(y=0;y<2*r;y++)
	//{
 //     for(x=0;x<2*r;x++)
	//  {
 //      printf("%d ",num[i][j]);
	//  }
	//  printf("\n");
	//}
}/*limiaziracaoHSV*/

void get_caracteres(char* filename)// Obtem dados apartir de uma matriz e salva em uma imagem (Gray).
{
	int x, y, i,j;
	uchar *canal;
	IplImage *image = cvLoadImage(filename,0);
	canal = (uchar *)image->imageData;

	i=-1;
	for(y = 0; y < (image->height); y++)
    {
		canal =(uchar *) (image->imageData + y*(image->widthStep));
		i++; j=0;
		for(x = 0; x < (image->width) ; x++)
		{
    	  teste.imgOri[i][j] = canal[x];
    	  j++;
		}/*for interno*/
	}/*for*/


}

void put_caracteres(int a, int l, int** img) // obtem dados apartir de uma imagem (Gray) e salva em uma matriz
{
    IplImage *image = cvCreateImage(cvSize(l,a),IPL_DEPTH_8U,0);
    cvNamedWindow("TESTE",0);
    cvShowImage("TESTE", image);
	int x, y, i,j;
	uchar *canal;
	canal = (uchar *)image->imageData;

	i=-1;
	for(y = 0; y < (image->height); y++)
    {
		canal =(uchar *) (image->imageData + y*(image->widthStep));
		i++; j=0;
		for(x = 0; x < (image->width); x++)
		{
            canal[x]=img[i][j];
            j++;
		}/*for interno*/
	}/*for*/
    cvNamedWindow("TESTE", 0);
    cvShowImage("TESTE", image);
}

/*liarizacaoHSV
Entrada: ponteiro para uma IplImage.
Sa�da: N�o retorna

		A fun��o recebe uma IplImage por referencia;
			Caso o canal 0 (Hue) esteja no intervalo [170, 180] OU [0 , 15]  E
			o canal 1 (Saturation) maior que 130 E o canal 2 (Value) maior que 100, o pixel �
			colocado para branco (255, 255, 255); caso contr�rio � colocado para preto (0, 0, 0).
*/
void limiarizacaoHSV(IplImage *imageHSV){


	int x, y;
	uchar *canal;
	canal = (uchar *)imageHSV->imageData;

	for(y = 0; y < imageHSV->height; y++){
			canal =(uchar *) (imageHSV->imageData + y*(imageHSV->widthStep));
		for(x = 0; x < imageHSV->width; x++){
			//if( (canal[3*x+0]>90)&&(canal[3*x+0]<110)&&(canal[3*x+1]<100))//cinza
			if((canal[3*x+0]>85)&&(canal[3*x+0]<160)&&

			   (canal[3*x+1]<100) &&

			   (canal[3*x+2]<70)&& (canal[3*x+2]>10)
				)
			{
				canal[3*x+0] = 0;
				canal[3*x+1] = 0;
				canal[3*x+2] = 0;
			}else{
				canal[3*x+0] = 255;
				canal[3*x+1] = 255;
				canal[3*x+2] = 255;
			}/*else*/
		}/*for interno*/
	}/*for*/
}/*limiaziracaoHSV*/

/*valorDoPixel
Entrada: par�metros padr�es de acordo com a biblioteca opencv;
		o par�metro param recebe por referencia a imagem da qual deseja-se vizualizar o valor do pixel
sa�da: n�o retorna.

			A fun��o responde quando o botao esquerdo do mouse baixa. A fun��o imprime os
		valores dos	canais do pixel da coordenada dada por x e y.
*/
void valorDoPixel(int event, int x, int y, int flags, void* param)
  {
	  IplImage *image = (IplImage*) param;
	  uchar *canal; /*ponteiros para os canais de imagens com 3 canais*/

	  switch(event){

		  case CV_EVENT_LBUTTONDOWN:

			 canal = (uchar *) (image->imageData + y*(image->widthStep));

			  /*Mostra valores dos pixels nas imagens com 3 canais*/
			  printf("\n")	;
			  printf("ponto(%d, %d)\n", x, y);
			  printf("H: %d\n", canal[3*x+0]);
			  printf("S: %d\n", canal[3*x+1]);
			  printf("V: %d\n", canal[3*x+2]);

		  default:
			  break;
	  }/*case*/
  }/*valorDoPixel*/

/*main
Entrada: null
Sa�da: void

			A fun��o principal carrega  uma imagem, se a imagem for carregada ela � mostrada, ocorre a limiariza��o,
		e a imagem limiarizada � mostrada; tamb�m permite a verifica��o do valor de cada pixel da imagem; quando
		alguma tecla for pressionada encerra o programa; caso n�o seja poss�vel carregar a imagem imprime mensagem
		de erro.*/

int main(){

	IplImage *imgRgb = cvLoadImage("pic5.png",1);//pl2//f130.bmp",1);
	IplImage *imgHsv, *imgCopy;
	IplImage *imgGray = cvLoadImage("pic5.png",0);
	cvNamedWindow("ImgGray", 0);
	cvShowImage("ImgGray", imgGray);
	cvNamedWindow("ImgRGB", 0);
	cvShowImage("ImgRGB", imgRgb);



		if(imgRgb){

			cvNamedWindow("ImgHSV",1);

            imgHsv = cvCreateImage(cvGetSize(imgRgb), imgRgb->depth, 3);

			/*Conver��o RGB -> HSV*/
			cvCvtColor(imgRgb, imgHsv,CV_BGR2HSV);//CV_BGR2YCrCb);//

			imgCopy = cvCloneImage(imgHsv);

			limiarizacaoHSV(imgCopy);


			//get_caracteres2(imgHsv, imgHsv->width/2, imgHsv->height/2, imgHsv->height/2);
            get_caracteres("pic5.png");

            put_caracteres(300, 400, teste.imgOri);


			cvShowImage("ImgHSV", imgHsv);
			cvNamedWindow("limiarizada", 1);
			cvShowImage("limiarizada", imgCopy);

			cvSetMouseCallback("ImgHSV",valorDoPixel,(void *) imgHsv);

			cvWaitKey(0);	/*Aguarda indeterminadamente um tecla ser pressionado*/

		}else{
			printf("Imagem n�o carregada");}

}/*fim main*/



