#include "Imagem.h"


Imagem::Imagem (void)
{
    alt = 0;
    larg = 0;
    imgOri = NULL;
    imgPro = NULL;
    imgCinza = NULL;
    imgHistograma = NULL;
}
Imagem::Imagem (int a,int l)
{
    alt = a;
    larg = l;
    fNew (alt,larg);
}
Imagem::Imagem ( int a, int l, int**img )
{
    alt = a;
    larg = l;
    fNew (alt,larg);
    setImagem(img);  //imgOri = img.

}
Imagem::Imagem (int a,int l,char*filename)
{
    alt = a;
    larg = l;
    fNew (alt,larg);
    fCopyFile(a, l, filename);  //imgHistograma = filename.

}
Imagem::~Imagem (void)      //Destrutor.
{
    for(int i=0 ; i < alt ; i++)
    {
        delete[]imgOri[i];
        delete[]imgPro[i];
        delete[]imgCinza[i];
    }

    delete[]imgOri;
    delete[]imgPro;
    delete[]imgCinza;
    delete[]imgHistograma;

}
void Imagem::fNew (int alt,int larg)
{

imgOri = new int*[larg];
imgPro = new int*[larg];
imgCinza = new int*[larg];
imgHistograma = new int[larg];

for(int i=0 ; i<larg ; i++)
{
  imgOri[i] = new int[alt];
  imgPro[i] = new int[alt];
  imgCinza[i] = new int[alt];
}
}
void Imagem::fCopyFile(int i, int j, char*file )
{
    int x,y;
    ifstream fin(file);

    if(!fin)
    cerr<<"Arquivo nao existe";

    else{
                for( int j=0 ; j<larg ; j++ )
                for(int i=0 ; i<alt; i++)
                {
                fin >> y;
                x = ((y+2048)*255)/4096;

                imgOri[i][j] = x;
                }
        }
}
void Imagem::setAltura(int a){
    alt = a;
}
void Imagem::setLargura(int l){
    larg = l;
}
void Imagem::setImagem(int** img){
    for( int j = 0 ; j < alt ; j++ )
	    for( int i = 0 ; i < larg ; i++ ){
	        imgOri[i][j] = img[i][j];
	    }
}
void Imagem::setImagem(int a, int l, int** img){
    for( int i=0 ; i<a ; i++ ){
	    for( int j=0 ; j<l ; j++ ){
	        imgOri[i][j] = img[i][j];
	    }
	}
}
void Imagem::convertCinza(void){
}
void Imagem::media(int d){
    // Despreza as posições que a mascara transponha a borda da imagem.
    int h = (d-1)/2;
    for(int i = h ; i < alt-h ; i++){
        for(int j = h ; j < larg-h ; j++){
            int  S = 0;
            for(int y = -h ; y <= h ; y++){
                for(int x = -h ; x <= h -1 ; x++){
                    //soma elementos presentes da mascara.
                    S += imgOri[i+x][j+y]; 
                }
            }
            imgPro[i][j]=S/(d*d);//Calcula a media e subistitui no valor central da mascara.
        }
    }

}
void Imagem::mediana(int d){
    int vet[d*d];
    int exit = 0;
    int l=0;
    int aux;
    for (int i = 0 ; i<= alt-d ; i++){
        for (int j = 0 ; j<= larg-d ; j++){
            //percorre a mascara.
            for(int x = i ; x < i+d ; x++)
                for(int y = j ; y < j+d ; y++){
                    //preenche o vetor.
                    vet[l] = imgOri[x][y];
                    l++;
                }
        //organiza o vetor em ordem crescente.
        do{
            exit = 0;
            for(l = 0 ; l < (d*d)-1 ; l++)
            if(vet[l]>vet[l+1]){
                aux = vet[l];
                vet[l] = vet[l+1];
                vet[l+1] = aux;
                exit = 1;
            }
        }while(exit != 0);

        //((d-1)/2)  elemento central da mascara.
        //(((d*d)-1)/2)  elemento central do vetor.

        imgPro[i+((d-1)/2)][j+((d-1)/2)] = vet [(((d*d)-1)/2)];
        }
    }
}

void Imagem::limiar(int l){
    for(int i = 0 ; i < larg ; i++)
        for(int j = 0 ; j < alt ; j++){
            if(imgOri[i][j]<=l)
                imgPro[i][j] = 0;
            else{
                //if(imgOri[i][j]>l)
                imgPro[i][j] = 255;
            }
        }
}

void Imagem::gaussiana5(void){
	for(int i=2; i<((alt)-2); i++)
	    for(int j=2; j<((larg)-2); j++)
            imgPro[i][j]=(-imgOri[i][j-3]-imgOri[i][j+3]-imgOri[i+3][j]-imgOri[i-3][j]-imgOri[i-1][j-1]
                     -imgOri[i+1][j+1]-imgOri[i+1][j-1]-imgOri[i-1][j+1]+((imgOri[i][j+1])*(-2))+((imgOri[i][j-1])*(-2))
                     +((imgOri[i+1][j])*(-2))+((imgOri[i-1][j])*(-2))+((imgOri[i][j])*(16)));
}

void Imagem::gaussiana7(void){
	for(int i=3; i<((alt)-3); i++)
	    for(int j=3; j<((larg)-3); j++){
            imgPro[i][j]= -imgOri[i-3][j-1]-imgOri[i-3][j]-imgOri[i-3][j+1]
                        -imgOri[i-1][j-3]-imgOri[i][j-3]-imgOri[i+1][j-3]
                        -imgOri[i+3][j-1]-imgOri[i+3][j]-imgOri[i+3][j-1]
                        -imgOri[i-1][j+3]-imgOri[i][j+3]-imgOri[i+1][j+3]
                        +(imgOri[i-2][j-2]*(-2))+(imgOri[i+2][j+2]*(-2))+(imgOri[i+2][j-2]*(-2))+(imgOri[i-2][j+2]*(-2))
                        -(imgOri[i-2][j-1]*(3))-(imgOri[i-2][j]*(3))-(imgOri[i-2][j+1]*(3))
                        -(imgOri[i-1][j-2]*(3))-(imgOri[i][j-2]*(3))-(imgOri[i+1][j-2]*(3))
                        -(imgOri[i+2][j-1]*(3))-(imgOri[i+2][j]*(3))-(imgOri[i+2][j-1]*(3))
                        -(imgOri[i-1][j+2]*(3))-(imgOri[i][j+2]*(3))-(imgOri[i+1][j+2]*(3))
                        +(imgOri[i-1][j]*(5))+(imgOri[i+1][j]*(5))+(imgOri[i][j-1]*(5))+(imgOri[i][j+1]*(5))+(imgOri[i-1][j+1]*(5))+(imgOri[i+1][j-1]*(5))+(imgOri[i-1][j-1]*(5))+(imgOri[i+1][j+1]*(5))
                        +(imgOri[i][j]*(16));
        }
}

void Imagem::sobel(void){
    int gx;
    int gy;
    int f;
    for(int i = 1 ; i < alt-1 ; i++){
        for(int j = 1 ; j < larg-1 ; j++){
            gx = (imgOri[i+1][j-1] + 2*imgOri[i+1][j] + imgOri[i+1][j+1]) -
                    (imgOri[i-1][j-1] + 2*imgOri[i-1][j] + imgOri[i-1][j+1]);
            gy = (imgOri[i+1][j-1] + 2*imgOri[i][j+1] + imgOri[i+1][j+1]) -
                    (imgOri[i-1][j-1] + 2*imgOri[i][j-1] + imgOri[i+1][j-1]);
            f = pow((gx*gx) + (gy*gy),(1/2));
        }
    }
}

void Imagem::prewitt(void){
	for(int i=1; i<((alt)-1); i++)
        for(int j=1; j<((larg)-1); j++){
            float somaMascara1=0,somaMascara2=0;
            for(int x=-1;x<1;x++) //Varrendo a matriz
                for(int y=-1;y<1;y++){
                    if (y==-1)
                    somaMascara1+=((imgOri[i+x][j+y])*(-1));
                    if(y==1)
                    somaMascara1+=(imgOri[i+x][j+y]);

                    if (x==-1)
                    somaMascara2+=((imgOri[i+x][j+y])*(-1));
                    if(x==1)
                    somaMascara2+=(imgOri[i+x][j+y]);

                    somaMascara1 = ((somaMascara1*somaMascara1)+(somaMascara2*somaMascara2));//elevando os o somatorio de cara uma das duas mascaras ao quadrado
                    somaMascara1 = pow(somaMascara1,1/2); //tirando raiz
                }
            imgPro[i][j]=somaMascara1;
        }
}
void Imagem::roberts(void){
	for(int i=1; i<((alt)-1); i++)
        for(int j=1; j<((larg)-1); j++){
           float  somaMascara1=0,somaMascara2=0;
            somaMascara1+=((imgOri[i][j])+(imgOri[i+1][j+1]*(-1))); //aplicando a primeira mascara 1,0,0,-1
            somaMascara2+=((imgOri[i+1][j])+(imgOri[i][j+1]*(-1))); //aplicando a segunda mascara 0,-1,1,0
            somaMascara1 = ((somaMascara1*somaMascara1)+(somaMascara2*somaMascara2)); //elevando os o somatorio de cara uma das duas mascaras ao quadrado
            somaMascara1 = pow(somaMascara1,1/2); //tirando raiz
            imgPro[i][j]=somaMascara1;
        }
}

int** Imagem::getImgOri(void){
    return imgOri;
}

int** Imagem::getImgPro(void){
    return imgPro;
}

int** Imagem::getImgCinza(void){
    return imgCinza;
}