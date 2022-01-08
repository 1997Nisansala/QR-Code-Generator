/*
	CO222 : Programming Methodology
	Project 1 : QR Code Generator
	Morais K.W.G.A.N.D.
*/

#include <stdio.h>	//standard input/output
#include <string.h>	//for string functions

//prototypes of functions
void hashingUrl(int count,unsigned char words[1000]);
void positionSquares(int val,int qr3[1000][1000]);
void printg(int start,int finish,int divide,int s[1000][1000], int qr2[1000][1000]);
void printa(int bval,int bval2,int start, int finish,int s[1000][1000], int qr2[1000][1000]);
int strlength(unsigned char s[]);
void tolowers(char *string);
void setscrn();

//defining values of ansi background colours 
#define BLACK   40
#define RED     41
#define GREEN   42
#define YELLOW  43
#define BLUE    44
#define MAGENTA 45
#define CYAN    46  
#define WHITE 	47 

int main(int argc, char** argv){
	char colours[20][20] = {"black","red","green","yellow","blue","magenta","cyan","white"};	//array of available colours
	int  colournum[]={BLACK,RED,GREEN,YELLOW,BLUE,MAGENTA,CYAN,WHITE}; 				//array of ansi colour values

	unsigned char url2[1000];						//variable for getting copy of hashed URL
	unsigned char url[1000];						//variable for getting input URL
	int bin[1000][1000];							//variable for storing binary values of hashed string
	int qr[1000][1000];								//variable for storing 0,1 values to print QR code
	int bg=-1;										//initializing background colour

	if((argc>3)||(argc==2 && strcmp(argv[1], "-h")!=0)||(argc==3 && strcmp(argv[1],"-c")!=0)){	//condition for checking the input arguments are in correct manner
		//printing appropriate error message
		printf("Incorrect usage of arguments.\n");
		printf("usage :\n");
		printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
		printf("%s -h for the help about the program",argv[0]);
	}

	else if(argc==2 && strcmp(argv[1], "-h")==0){	//condition for checking input argument for asking help
		//printing appropriate error message
		printf("usage :\n");
		printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
		printf("%s -h for the help about the program",argv[0]);
	}

	else if((argc<2)||(argc==3 && strcmp(argv[1], "-c")==0)){	//condition for checking that arguments are correct manner
		if(argc<2){		//condition for checking that count of arguments are one 
			bg=BLACK;	//initializing background colour to BLACK
		}
		else if(argc==3 && strcmp(argv[1], "-c")==0){	//conditin for checking that argument counts are 3 & given colour with '-c' flag
			tolowers(argv[2]);							//converting given colour to lowercase letters
			int i;
			for(i=0;i<8;i++){
				if(strcmp(argv[2],colours[i])==0){		//condition for checking that given colour is available in the list
					bg=colournum[i];					//assigning the ansi value of colour 
				}
			}
		}
		if(bg==-1){	//condition for checking that given colour is not available
			//printing appropriate error message
			printf("Invalid argument for color.\n");
			printf("usage :\n");
			printf("%s -c [black|red|green|yellow|blue|magenta|cyan]\n",argv[0]);
			printf("%s -h for the help about the program\n",argv[0]);
			return 0;
		}

		printf("Enter the URL: ");
		scanf("%s",url);				//taking input for URL
		int q=strlength(url);			//finding the length of the URL
		
		if(q<4){	//condition for checking length of URL is too short
			//printing appropriate error message
			printf("String is too short. Not supported by available QR versions");
		}
		else if(q<=20){			//condition for checking length of URL is less than 21 characters
			int g,count,h,i;
			hashingUrl(24,url);					//hashing the URL to 24 characters
			for(g=0;g<strlength(url);g++){	//assigning characters of hashed URL to new variable 'url2'
			url2[g]=url[g];}
			int y[1000];						//variable for storing ascii values of the characters of hashed string
			
			for(i=0; i<24; i++){
				y[i]=url2[i];			//converting hashed string characters to their ascii decimal values
				//converting to binary values
				for(count=8; count >=0; count--){
					bin[i][8-count]=((y[i] >> count) & 1);
				}
			}

			positionSquares(19,qr);		//values assigning to 3 position squares
			
			for(g=0; g<4; g++){		//assigning binary values to character 1 to 16 in qr code
				printg(4*g,4*(g+1),4,bin,qr);
			}

			printa(1,7,16,18,bin,qr);	//assigning binary values to character 16 to 18 in qr code
			printa(4,7,18,20,bin,qr);	//assigning binary values to character 18 to 20 in qr code
			printa(7,1,20,22,bin,qr);	//assigning binary values to character 20 to 22 in qr code
			printa(10,1,22,24,bin,qr);	//assigning binary values to character 22 to 24 in qr code

			setscrn();	//setting the screen in appropiate way

			//printing QR code black and white colours according to '0,1' values in qr array
			for(g=0; g<=19; g++){
				for(h=0; h<=19; h++){
					if(qr[g][h]==0){	//condition for checking that value is 0
						printf("\x1b[47m""  ");		//printing 0 values in white colour
						}
					else if(qr[g][h]==1){	//condition for checking that value is 1
						printf("\x1b[%dm""  ",bg);	//printing 1 values in black colour
						}
				}
				printf("\n");	//printing a new line
			}
		}

		else if(q>20 && q<120){		//condition for checking length of URL is greater than 20 characters & less than 120 characters
			int g,i,count,h;
			hashingUrl(132,url);	//hashing the URL to 132 characters
			for(g=0;g<strlength(url);g++){	//assigning characters of hashed URL to new variable 'url2'
			url2[g]=url[g];}	
			int y[1000];

			for(i=0; i<132; i++){
				y[i]=url2[i];	//converting hashed string characters to their ascii decimal values
				//converting to binary values
				for(count=8; count >=0; count--){
					bin[i][8-count]=((y[i] >> count) & 1);
					}
				}

			positionSquares(37,qr);		//values assigning to 3 position squares
			int f;
			//assigning binary values to character 1 to 100 in qr code
			for(f=0; f<10;f++){			
				printg(10*f,(f+1)*10,10,bin,qr);
			}

			printa(1,7,100,108,bin,qr);	//assigning binary values to character 100 to 108 in qr code
			printa(4,7,108,116,bin,qr);	//assigning binary values to character 108 to 116 in qr code

			//assigning binary values to character 116 to 132 in qr code
			for(f=116;f<=123;f++){
				printa(7+3*(f-116),1,116+2*(f-116),118+2*(f-116),bin,qr);
				}

			setscrn();	//setting the screen in appropiate way
			
			//printing QR code black and white colours according to '0,1' values in qr array
			for(g=0; g<=37; g++){
				for(h=0; h<=37; h++){
					if(qr[g][h]==0){	//condition for checking that value is 0
						printf("\x1b[47m""  ");		//printing 0 values in white colour spaces
						printf("\x1b[0m");			//resetting the color of terminal
					}
					else if(qr[g][h]==1){	//condition for checking that value is 1
						printf("\x1b[%dm""  ",bg);	//printing 1 values in given colour spaces
						printf("\x1b[0m");			//resetting the color of terminal
					}
				}
				printf("\n");
			}
		}

		else{	//condition for checking that string is too long

			//printing appropriate error message
			printf("String is too long. Not supported by available QR versions");
		}
	}

	printf("\x1b[0m");	//resetting the color of terminal
	printf("\n");		//printing a new line
	return 0;
}

/*
	FUNCTIONS
*/

//Function for hashing the URL according to given count
void hashingUrl(int count,unsigned char words[1000]){
	unsigned char reword[1000],rewords[1000];
	int p=strlength(words);
	int j=0,k=0,h;
	reword[0]=50+p;	//adding 50 to the length of the url
	//filling the remaining part of the array 
	for(h=1;h<count;h++){
		if(j==p){
			j=0;
			k++;}
		reword[h]=words[j]+k;
		j++;
		}
	//making a new array
	for(h=0;h<count;h++){
		rewords[h]=reword[h];
		}
	//reversing the part of appended
	for(h=p+1;h<count;h++){
		reword[h]=rewords[count-h+p];
		}
	for(h=0;h<count;h++){
		words[h]=reword[h];
		}
	words[count]='\0'; //assigning the last character to null
}

//function for assigning '0,1' values to print 3 position squares
void positionSquares(int val,int qr3[1000][1000]){
	int i,k;
	for(i=0; i<=val; i++){
		for(k=0 ; k<=val; k++){
                	if(((i==1 || i==6) && ((k>=1 && k<=6) ||(k>=val-6 && k<=val-1))) || ((i==val-6 || i==val-1) && (k>=1 && k<=6))) {
				qr3[i][k]=1;
			}
			else if(((k==1 || k==6) && ((i>1 && i<6) || (i>val-6 && i<val-1))) || ((k==val-6 || k==val-1) && (i>1 && i<6))){
				qr3[i][k]=1;
			}
			else if(((i==3 || i==4 ) && (k==3 || k==4 || k==val-4|| k==val-3)) || ((i==val-3 || i==val-4) &&(k==3 ||k==4))){
				qr3[i][k]=1;
			}
			else if(i==0 || i==val || k==0 || k==val){
				qr3[i][k]=0;
			}}}}

//function for printing block 1
void printg(int start,int finish,int divide,int s[1000][1000], int qr2[1000][1000]){
	int b=0,d=0,j,k;
	for(j=start;j<finish;j++){
		for(k=0;k<9;k++){
			qr2[b+7+(3*(start/divide))][d+7+(j-start)*3]=s[j][k];
			d++;
			if(d==3){
				b++;
				d=0;
			}
			if(b==3){
				b=0;
	}}}}

//function for printing block 2
void printa(int bval,int bval2,int start, int finish,int s[1000][1000], int qr2[1000][1000]){
	int b=bval,d=0,j,k;
	for(j=start;j<finish;j++){
		for(k=0;k<9;k++){
			qr2[b][d+bval2+(j-start)*3]=s[j][k];
			d++;
		if(d==3){
			b++;
			d=0;
		}
		if(b==bval+3){
			b=bval;
	}}}}

//function for finding length of unsigned char string
int strlength(unsigned char s[]){
    int c=0;
    while (s[c] != '\0'){
        c++;
    }
    return c;
}

//function to convert a string to lower case letters
void tolowers(char *string){
	int i=0;
	while (string[i] != '\0'){
		if(string[i] >= 'A' && string[i] <= 'Z'){
			string[i]=string[i]+32;	
		}
		i++;
	}
}

//function to set the screen
void setscrn(){
	printf("\x1b[2J");		//clearing the screen
	printf("\x1b[0;0f");	//moving cursor to left top corner
}

//end of the code
