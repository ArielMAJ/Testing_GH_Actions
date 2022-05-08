#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// #include <time.h>

void intArrToString( int arr[], int arrSize, char output[] ){
  char tmp2[2];
  int start;
  
  for( start = 0; start < arrSize; start++){
		if( arr[start] != 0 )
			break;
	}
	
  for( int i = start; i < arrSize; i++){
		tmp2[0] = '\0';
    sprintf(tmp2, "%d", arr[i]);
    strncat(output, &tmp2[0], 1);
   }
   
}

void fillZeros( int arr[], int arraySize ){
	for( int position = 0; position < arraySize; position++ ){
		arr[position] = 0;
	}
}

void printArr( int array[], int arrSize ){

//   printf("\nArray:\n");
  
  int start;
  for( start = 0 ; start < arrSize ; start++ ){
		if( array[start] != 0 )
			break;
	}
	
  for( int i = start; i < arrSize; i++ )
    printf("%d", array[i]);
  
}

void stringToIntArray( char stringInput[], int intArrayOutput[] ){

	int stringLength = strlen(stringInput);
	
	for(int position = 0; position < stringLength; position++)
		intArrayOutput[position] = (int)stringInput[position] - 48;

}

void subtrairArr( int a[], int b[], int res[], int nA, int nB, int nR ){
//Correto para quando a>=b, que é o caso do algoritmo de Karatsuba.
	int i=1, aMb, currPos, nextPos=0;

	while( nR-i >= 0 ){
		aMb=nextPos;
		if ( nA-i >=0 ){
			aMb+=a[nA-i];
		}
		if( nB-i >= 0 ){
			aMb-=b[nB-i];
		}
		if ( aMb >= 0 ){
			currPos=aMb;
			nextPos=0;
		}else{
			currPos=10+aMb;
			nextPos=-1;
		}
		res[nR-i]=currPos;
		i++;
	}
}

void somarArr( int a[], int b[],int res[], int nA, int nB, int nR ){
	int i=1,aPb,currPos,nextPos=0;

	while( nR-i >= 0 ){
		aPb=nextPos;
		if ( nA-i >= 0 ){
			aPb+=a[nA-i];
		}
		if( nB-i >= 0 ){
			aPb+=b[nB-i];
		}
		currPos=aPb%10;
		nextPos=floor(aPb/10.0);
		res[nR-i]=currPos;
		i++;
	}
}

void multiplicacaoTradicional( int numero_A[], int numero_B[], int result[], int lenght_A, int lenght_B, int lenght_R ){
	int i, j, k=lenght_A, aXb, currPos, nextPos=0;

	for( j = lenght_B-1; j >= 0; j-- ){
			k-=lenght_A-1;
			
		for( i = lenght_A-1; i >= 0; i-- ){
			aXb = numero_A[i] * numero_B[j] + result[lenght_R-k];
			currPos=aXb%10;
			nextPos=floor(aXb/10.0);
			result[lenght_R-k]=currPos;
			k++;
			result[lenght_R-k]+=nextPos;
		}
	}
	
	result[lenght_R-k+1]%=10;
	result[lenght_R-k]+=floor(result[lenght_R-k+1]/10.0);
}

void sliceArr( int inputArray[], int outputArray[], int start, int end ){

	for(int position = start; position < end; position++)
		outputArray[position-start] = inputArray[position];
  
}

void checkZeros( int input[], int lenInput,int zeros ){
  for( zeros = 0; zeros < lenInput; zeros++){
    if ( input[zeros] != 0 )
			break;
	}
}

void karatsuba_multiplication_algorithm( int numero_A[], int numero_B[], int nAB, int n0, int resultado[] ){
	
	if ( nAB <= n0 ){
		multiplicacaoTradicional(numero_A, numero_B, resultado, nAB, nAB, nAB*2);
		return;
	}
	
	int m=ceil(nAB/2.0), mC=nAB-m, mC2=mC*2, m2=m*2;
	
	int A0[mC], A1[m], B0[mC], B1[m];
	int C0[mC2], C1[m2], C2[m2+2];
	int AA[m+1], BB[m+1];
	
	fillZeros(A0, mC);
	fillZeros(A1, m);
	fillZeros(B0, mC);
	fillZeros(B1, m);
	fillZeros(C0, mC2);
	fillZeros(C1, m2);
	fillZeros(C2, m2+2);

	sliceArr(numero_A, A0, 0, mC);
	sliceArr(numero_A, A1, mC, nAB);
	sliceArr(numero_B, B0, 0, mC);
	sliceArr(numero_B, B1, mC, nAB);

  karatsuba_multiplication_algorithm(A0, B0, mC, n0, C0);
  karatsuba_multiplication_algorithm(A1, B1, m, n0, C1);

  somarArr(A0, A1, AA, mC, m, m+1);
  somarArr(B0, B1, BB, mC, m, m+1);
  karatsuba_multiplication_algorithm(AA, BB, m+1, n0, C2);

	int P2[m2+2];
	fillZeros(P2, m2+2);
	somarArr(C0, C1, P2, mC2, m2, m2+2);

	int P22[m2+2];
	fillZeros(P22, m2+2);
	subtrairArr(C2, P2, P22, m2+2, m2+2, m2+2);

	int zerosP=0;
	checkZeros(P22, m2+2, zerosP);
	
	int P2toTheX[m2+2+m-zerosP];
	fillZeros(P2toTheX, m2+2+m-zerosP);
	sliceArr(P22, P2toTheX, zerosP, m2+2);

	int zerosC0=0;
	checkZeros(C0, mC2, zerosC0);
	
	int C0toTheX[mC2+m2-zerosC0];
	fillZeros(C0toTheX, mC2+m2-zerosC0);
	sliceArr(C0, C0toTheX, zerosC0, mC2);

	somarArr(C1, P2toTheX, resultado, m2, m2+2+m-zerosP, nAB*2);
	somarArr(C0toTheX, resultado, resultado, mC2+m2-zerosC0, nAB*2, nAB*2);
	
}

int getNumbersSizeFromFile( FILE *fileObject  ){
	
	int nInt=0;
	char  n[9999];
	fgets(n, 9999, fileObject);
	
	int nLen=strlen(n), k=0,t=0;
	for ( int c = nLen-2; c >= 0; c-- ){
		t=(int)(n[c])-48;
		for ( int p = 0; p < k; p++ ){
			t*=10;
		}
		nInt+=t;
		k++;
	}
	return nInt;
}

void loadNumbersFromFile(FILE *fileObject, int nInt, int arrA[], int arrB[])
{
	char aFile[nInt+1], bFile[nInt+1], tmp[9999]; //Criando strings do tamanho necessário para ler cada linha;
	fgets(aFile, nInt+1, fileObject); //Lendo exatamente a quantidade de caracteres indicado na primeira linha;
	fgets(tmp, 9999, fileObject); //Ignorando o resto dos caracteres (Sempre haverá, pelo menos, um '\n');
	fgets(bFile, nInt+1, fileObject); //Lendo exatamente a quantidade de caracteres indicado na primeira linha;

	fillZeros(arrA, nInt);
	fillZeros(arrB, nInt);

	stringToIntArray(aFile, arrA);
	stringToIntArray(bFile, arrB);
}

void saveResultsToOutputTxt( int resultado[], int lenR, char *output_file_name){
	FILE *fileObject;
	char resultAsString[lenR+1];

	resultAsString[0]='\0';
	intArrToString(resultado, lenR, resultAsString);

	fileObject = fopen(output_file_name, "w+");
	fprintf(fileObject, "%s", resultAsString);
	fclose(fileObject);
}

/*
double KaratsubaTimer( int arrA[], int arrB[], int nInt, int resultado[] ){

	double tempo_exec;
	clock_t time;

	time = clock();
	karatsuba_multiplication_algorithm(arrA, arrB, nInt, 3, resultado);
	time = clock() - time;
	tempo_exec = ((double)time)/CLOCKS_PER_SEC;
	// printf("\nKaratsuba demorou %f segundos para executar com %d digits.\n", tempo_exec, nInt);
	
	return tempo_exec;
}

double MTradicionalTimer( int arrA[], int arrB[], int nInt, int resultado[] ){
	double tempo_exec;
	clock_t time;
	
	time = clock();
	multiplicacaoTradicional( arrA, arrB, resultado, nInt, nInt, nInt*2 );
	time = clock() - time;
	tempo_exec = ((double)time)/CLOCKS_PER_SEC;
	// printf("\nMT demorou %f segundos para executar com %d digits.\n", tempo_exec, nInt);
	
	return tempo_exec;
}

void gerar_CSV_de_Tempos_Com_Numeros_Aleatorios(){

	FILE *fileObject;
	fileObject = fopen("tempos_MK_e_MT.csv", "w+");
	fprintf(fileObject, "\n;n (dígitos);Multiplicação Tradicional;Multiplicação Karatsuba\n");

	double MT_time, MK_time;
	int inputSize=2300; // Até quantos dígitos deve ser testado.
	int digitsAddedPerIteration=25; //Quantos dígitos a mais por iteração. Ex.: testar de 100 em 100 dígitos.
	int totalIterations = inputSize/digitsAddedPerIteration; //Escolher valores com cuidados pois precisa resultar em um inteiro.
	int averageOfN=5; // Repetições das multiplicações para calcular tempo médio.
	
	int iteration, numberLenght, aTest[inputSize], bTest[inputSize];
	int MK_resultado[inputSize*2],MT_resultado[inputSize*2];
	fillZeros(aTest, inputSize);
	fillZeros(bTest, inputSize);
	fillZeros(MK_resultado, inputSize*2);
	fillZeros(MT_resultado, inputSize*2);
	char tmp[2], aString[inputSize+1], bString[inputSize+1];

	for ( iteration = 1; iteration <= totalIterations; iteration++ ){
	  srand(time(0));

	  aString[0]='\0';
	  bString[0]='\0';
	  numberLenght=iteration*digitsAddedPerIteration;
	  
	  
	  for(int currentDigit = 0; currentDigit < numberLenght; currentDigit++){
			tmp[0]='\0';
	    sprintf(tmp, "%d", rand()%6 + 4);
	    strncat(aString, &tmp[0], 1);
	    tmp[0]='\0';
	    sprintf(tmp, "%d", rand()%6 + 4);
	    strncat(bString, &tmp[0], 1);
		}
		
		stringToIntArray(aString, aTest);
		stringToIntArray(bString, bTest);

		
		MK_time=0;
		MT_time=0;
		for (int test = 0; test < averageOfN; test++){
			fillZeros(MK_resultado, inputSize*2); //Popula o vetor de saída com zeros.
			MK_time += KaratsubaTimer(aTest, bTest, numberLenght, MK_resultado);

			
			fillZeros(MT_resultado, inputSize*2);
			MT_time += MTradicionalTimer(aTest, bTest, numberLenght, MT_resultado);

			for (int digit = 0; digit < numberLenght; digit++){
				if (MK_resultado[digit]!=MT_resultado[digit]){
					printf("\n\nOcorreu um erro, vetores de saída de MK e MT são diferentes... \n\n");
					printArr(aTest,numberLenght);
					printArr(bTest,numberLenght);
					printArr(MK_resultado,numberLenght*2);
					printArr(MT_resultado,numberLenght*2);
					fclose(fileObject);
					exit(1);
				}
			}

		}
		// system("cls"); //Para windows;
	  printf("\n%d%% concluido...\n",iteration*100/totalIterations);
		fprintf(fileObject, ";%d;%f;%f\n", numberLenght,MT_time/averageOfN,MK_time/averageOfN);
	}
	fclose(fileObject);
}
*/

int main(int argc, char *argv[])
{
	// if (argc != 3)
	// {
	// 	printf("Usage: ./karatsuba input.txt output.exe");
	// 	return 1;
	// }
	if (argc != 2)
	{
		printf("Usage: ./karatsuba input.txt");
		return 1;		
	}
	// gerar_CSV_de_Tempos_Com_Numeros_Aleatorios(); //Funções comentadas acima.
	
	FILE *fileObject;

	char *inputFilePath = argv[1];
	fileObject = fopen(inputFilePath, "r");

	if ( fileObject == NULL ){
		printf("Problema ao abrir arquivo no caminho: %s\n", inputFilePath);
		printf("Favor verificar/alterar caminho do local do arquivo.\n");
		return 1;
	}

	int	nInt=0;
	nInt = getNumbersSizeFromFile(fileObject); // Obtém primeira linha.
	int arrA[nInt], arrB[nInt];
	loadNumbersFromFile(fileObject, nInt, arrA, arrB); //Lê segunda e terceira linha
	// e retorna um array de inteiros com um dígito por posição.
	fclose(fileObject);
	
	
	int resultado[nInt*2];
	fillZeros(resultado, nInt*2);
	karatsuba_multiplication_algorithm(arrA, arrB, nInt, 3, resultado);
	// multiplicacaoTradicional( arrA, arrB, resultado, nInt, nInt, nInt*2 );

	printArr(resultado, nInt*2);
	// saveResultsToOutputTxt(resultado, nInt*2, argv[2]);

  return 0;
}
