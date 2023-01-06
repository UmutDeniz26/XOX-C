#include<stdio.h>
#include<math.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>

//kümeleri burada tanýmlýyorum çünkü aþþaðýdaki fonksiyonlarda tekrar kullanacaðým 
char playableArea[9];
char board[19]="* * *\n* * *\n* * *";
char board_copy[19];
char board_copy2[19];
char playableArea_copy[9];
int loses[9];
int loses_copy[9];
int i;
int main(void){
	int j;
	//ileride kullanmak için default sahayý yedekliyorum :
	for(j=0;j<19;j++){
		board_copy2[j]=board[j];
	}
	for(j=0;j<9;j++){
		playableArea_copy[j]=playableArea[j];
	}
	
	
	//START
	printf("\tWelcome to Tic Tac Toe (XOX)\n\n");
	int trash,tutorialChoice,tutorial,counter=0,playerchoice,mod,f=0,cnt=0,turncounter=2,k=0; 
	printf("Do you want to see the tutorial ?(1: YES ,2:NO) ");
	scanf("%d",&tutorial);
	system("cls");
	
	//TUTORÝAL
	if(tutorial==1){
		printf("\nBoard's area numbers are (press any key and enter to skip): \n\n\t1 2 3\n\t4 5 6\n\t7 8 9\n");
		scanf("%d",&trash);
		system("cls");
		printf("You should align your symbols vertically, horizontally or diagonally to win the game.(press any key and enter to skip)\n");
		scanf("%d",&trash);
		system("cls");
		printf("You are player 1 (Your symbol is 'X')\n");
		printf("\nWin the game !!!\n ");
		printf("\n\tX O X\n\t* * *\n\tX * *\n\nPlayer 1 turn :");
		scanf("%d",&tutorialChoice);
		system("cls");
		if(tutorialChoice==4||tutorialChoice==5){
			printf("\nCongratulations!!\n");
		}
		else{
			printf("\nYou should chose 4 or 5 :(");
		}
		printf("\n\nSave the game ! ! ");
		printf("\n\tO * O\n\t* X *\n\tX * *\nPlayer 1 turn :");
		scanf("%d",&tutorialChoice);
		system("cls");
		if(tutorialChoice==2){
			printf("\nCongratulations!!\n");
		}
		else{
			printf("\nYou should chose 2 :(");
			printf("\n\tO O O\n\t* X *\n\tX * *\n");
		}
	}
	
	//GAME
	int loop=1;
	while(loop==1){ //--> oyunun art arda oyanabilmesi için 
	
	//1 kiþilik mi 2 kiþilik mi
	printf("\nLet's start the game\n\nType the number of player(1 or 2) :");
	scanf("%d",&mod);
	system("cls");
	
	//Boardý playable areaya iþliyoruz
	boardToPlayableArea();

	//2 kiþilik mod 
	if(mod==2){
		printf("\n%s\n",board);
		while(1==1){
			//Tur ayýrýcý sayýcý
			if(turncounter%2==0){
				printf("\nPlayer 1 turn \n");
			}
			else{
				printf("\nPlayer 2 turn \n");
				}
			playerchoice=chooseMove();
			// NOT : 1. elemanýn gösteriliþi array[0] ,2. nin gösteriliþi array[2] ...
			if(board[playableArea[playerchoice-1]]!='*'){ //playeableArea bir fonksiyon gibi çalýþýyor playerableAreadaki ilk eleman boarddaki ilk oyanabilir elemandýr(playableArea[0]=board[0]) playableAreadaki 2. eleman boarddaki ikinci oynanabilir eleman(playableArea[1}=board[2])böyle gidiyor ... (playableArea[2]=board[4])...  yani 1den 9a kadar olan sayýlarý boarddaki '*'lar (oynanabilir elemanlar) ile eþleþtiriyor
				printf("\nUnvalid Choice !!!\n");		  
				continue;
			} 
			
			if(turncounter%2==0){
				player1Turn(playerchoice);
			}
			else{
				player2Turn(playerchoice);
			}
			printf("\n%s\n",board);
			
			//Oyun bitti mi kontrol etme
			if(boardController()==1){
				if(turncounter%2==0){
					printf("\n\nPlayer 1 Wins !!\n\n");
					printf("%s",board);
					break;
				}
				else{
					printf("\n\nPlayer 2 Wins !!\n\n");
					printf("%s",board);
					break;
				}
			} 			                                            
			turncounter++;
			int drawCounter=0;
			for(i=0;i<9;i++){
				if(board[playableArea[i]]!='*'){
					drawCounter++;
				}
			}	   
			if(drawCounter==9){
				printf("  \nDRAW\n\n%s",board);
				break;
			}
		}
	}
		
		
	//Tek kiþilik mod
	else{
		int diffucltyChoice;
		//Mod seçimi(hard ve 
		printf("Select diffuclty (0:Beginner ,1 : Easy , 2 : Normal , 3 : Hard) :");
		scanf("%d",&diffucltyChoice);
        system("cls");
		while(1==1){
			if(diffucltyChoice==4){
			}
			
			//Player Turn
			printf("\n%s\n",board);
			playerchoice=chooseMove();
			if(board[playableArea[playerchoice-1]]!='*'){
				printf("\nUnvalid choice !!\n");
				continue;
			}
			player1Turn(playerchoice);
			
			if(boardController()==1){
				printf("\nPlayer Wins ! !\n");
				break;
				}
			int drawCounter=0;
			for(i=0;i<9;i++){
				if(board[playableArea[i]]!='*'){
					drawCounter++;
				}
			}	   
			if(drawCounter==9){
				printf("\nDRAW !\n",board);
				break;
			}		
			
			
			//EASY and NORMAL AI(baby xox) turn
			counter=0;
			if(diffucltyChoice == 1 || diffucltyChoice == 2){
			
			//Win scan
			while(counter<9){
				if(board[playableArea[counter]]=='*'){
					player2Turn(counter+1);
					if(boardController()==1){
						break;
					}
					else{
						board[playableArea[counter]]='*';					
					}
				}
				counter++;
			}
			//Lose scan
			if(counter==9){
				counter=0;
				while(counter<9){
					if(board[playableArea[counter]]=='*'){
					player1Turn(counter+1);	
					if(boardController()==1){
						player2Turn(counter+1);
						break;
						}
					else{
						board[playableArea[counter]]='*';	
							}
						}
			counter++;
					}
				}	
			}
			//HARD BOT
			else if(diffucltyChoice == 3){
					
			//Win scan
			while(counter<9){
				if(board[playableArea[counter]]=='*'){
					player2Turn(counter+1);
					if(boardController()==1){
						break;
					}
					else{
						board[playableArea[counter]]='*';					
					}
				}
			counter++;
			}
			
			//Lose scan
			if(counter==9){
				counter=0;
				while(counter<9){
					if(board[playableArea[counter]]=='*'){
						player1Turn(counter+1);	
					if(boardController()==1){
						player2Turn(counter+1);
						break;
						}
					else{
						board[playableArea[counter]]='*';	
						}
					}
					counter++;
				}
			}
			
			//Advanced tactical move
			if(counter==9){
				int i,m=1,analysisMode,turn1Counter_copy=1,turn1Counter,turn2Counter,turn3Counter,turn4Counter,turn5Counter,turn6Counter,turn7Counter,isItWin=0,isItLose=0,isItNothing=0,counter2=0,variantCounter=0;
				printf("Do you want to enable analysis mode ?(1 :Variants ,2 :Sequences ,3 :All Variants ,4 :NO) ");
				scanf("%d",&analysisMode);
				system("cls");
				counter=0;
				copyBoard();
				cnt=0;
				for(turn1Counter=0;turn1Counter<9;turn1Counter++){
					if(turn1Counter_copy!=turn1Counter){
						isItWin=0;
						isItLose=0;
						isItNothing=0;
						m=1;
					}
					
					resetBoard();
					counter2++;
					for(turn2Counter=0;turn2Counter<9;turn2Counter++){
						for(turn3Counter=0;turn3Counter<9;turn3Counter++){
							for(turn4Counter=0;turn4Counter<9;turn4Counter++){
								for(turn5Counter=0;turn5Counter<9;turn5Counter++){
									for(turn6Counter=0;turn6Counter<9;turn6Counter++){
										for(turn7Counter=0;turn7Counter<9;turn7Counter++){
											//printf("%d,%d,%d,%d,%d,%d,%d\n",turn1Counter,turn2Counter,turn3Counter,turn4Counter,turn5Counter,turn6Counter,turn7Counter);
											if(
											  (turn1Counter==turn2Counter || turn1Counter==turn3Counter || turn1Counter==turn4Counter ||turn1Counter==turn5Counter ||turn1Counter==turn6Counter ||turn1Counter==turn7Counter ||
											   turn2Counter==turn3Counter || turn2Counter==turn4Counter ||turn2Counter==turn5Counter ||turn2Counter==turn6Counter ||turn2Counter==turn7Counter ||
											   turn3Counter==turn4Counter||turn3Counter==turn5Counter ||turn3Counter==turn6Counter ||turn3Counter==turn7Counter ||
											   turn4Counter==turn5Counter ||turn4Counter==turn6Counter ||turn4Counter==turn7Counter ||
											   turn5Counter==turn6Counter ||turn5Counter==turn7Counter ||
											   turn6Counter==turn7Counter) 
											   ||
											   (inBoard(turn1Counter)!='*'||inBoard(turn2Counter)!='*'||
											   inBoard(turn3Counter)!='*'||inBoard(turn4Counter)!='*'||
											   inBoard(turn5Counter)!='*'||inBoard(turn6Counter)!='*'||
											   inBoard(turn7Counter)!='*')
											){
												resetBoard();	
												continue;
											}
											else{
												//printf("%d,%d,%d,%d,%d,%d,%d\n",turn1Counter,turn2Counter,turn3Counter,turn4Counter,turn5Counter,turn6Counter,turn7Counter);
												player2Turn(turn1Counter+1);
												player1Turn(turn2Counter+1);
												player2Turn(turn3Counter+1);
												player1Turn(turn4Counter+1);
												player2Turn(turn5Counter+1);
												player1Turn(turn6Counter+1);
												player2Turn(turn7Counter+1);	//YENÝLME SORUNU ÝÇÝN PLAYER 1 YERÝNE BOT KUR !!!!
												
												if(boardControllerWithType()=='X'){
													isItLose++;
												}
												else if(boardControllerWithType()=='O'){
													isItWin++;
												}
												else if(boardControllerWithType()==0){
													isItNothing++;
												}									
												if(analysisMode==2){
													printf("\n%d,%d,%d,%d",turn1Counter,turn2Counter,turn3Counter,turn4Counter);
												}
												if(analysisMode==3){
													variantCounter++;
													printf("\nBoard:\n%s\nWin =%d , Lose =%d ,Nothing =%d ,%d. variant ,area =%d",board,isItWin,isItLose,isItNothing,variantCounter,turn1Counter+1);
												}
												resetBoard();								
											}
										}
									}
								}
							}
						}
				
					}
    				 if(analysisMode==1){
						//printf("\n%d,%d",turn1Counter_copy,turn1Counter);
						if(turn1Counter_copy!=turn1Counter){
							printf("Win =%d , Lose =%d ,Nothing =%d ,%d. move\n",isItWin,isItLose,isItNothing,turn1Counter+1);
						}
					}
					loses[cnt]=isItLose;
					cnt++;
					
					
					
					if(turn1Counter_copy!=turn1Counter){
						turn1Counter_copy=turn1Counter;
					}
					
					
					
				}
				int tem=0,min=9999999,b=1,variableName=0;
				while(tem<9){
						if(loses[tem]<min){
							if(board[playableArea[tem]] !='*'){
								b=0;
							}
							if(b==1){
								min=loses[tem];
								variableName=tem+1;
							}
							b=1;							
						}
						tem++;
					}
					counter=0;
					printf("\n%d.Area is the best variable with %d\n",variableName,min);
					player2Turn(variableName);
				
			}
		}
			//bot ilk hamlesi için playerýn bütün hamlelerine ayrý bir küme açar her bir küme içinde 2. hamlesini dener eðer 2. hamlede mat kaçýnýlmazsa(bütün kümelerde mat kaçýnýlmaz olmalý) karar verir. 
			
			//Beginner mod
			if(diffucltyChoice==0){
				int random;
				srand(time(NULL));
				random=rand()%2;
				if(random==1){
					while(counter<9){
						if(board[playableArea[counter]]=='*'){
							player2Turn(counter+1);
						if(boardController()==1){
							break;
						}
					else{
						board[playableArea[counter]]='*';					
					}
				}
				counter++;
			}
			//Lose scan
			if(counter==9){
				counter=0;
				while(counter<9){
					if(board[playableArea[counter]]=='*'){
					player1Turn(counter+1);	
					if(boardController()==1){
						player2Turn(counter+1);
						break;
						}
					else{
						board[playableArea[counter]]='*';	
							}
						}
			counter++;
					}
				}
				}
				else{
					counter=9;
				}
				}
			//Random MOVE
			if(diffucltyChoice == 1 ||diffucltyChoice==0){
				if(counter==9){
					while(1==1){
						if(board[playableArea[f]]=='*'){
							player2Turn(f+1);
							break;
						}
						f++;
					}
				}	
			}
			if(diffucltyChoice==2 || diffucltyChoice==3 || diffucltyChoice==4){
				int first=0;
				if(counter==9){
					while(1==1){
						if(board[playableArea[f]]=='*'){
							if(first==0&&board[playableArea[4]]=='*'){
								player2Turn(5);
								break;
							}
							player2Turn(f+1);
							break;
						}
						f++;
					}
				}
			}
			
			
			if(boardController()==1){
				printf("\nAI wins ! !\n");
				break;
			}
			
		}
		printf("%s\n",board);
	}
		printf("Do you want a new game ?(1 : YES, 2 : NO) : ");
		scanf("%d",&loop);
		system("cls");
		for(j=0;j<19;j++){
			board[j]=board_copy2[j];
		}
		for(j=0;j<9;j++){
			playableArea[j]=playableArea_copy[j];
		}
	}	
	return 1;
}

//FONKSÝYONLAR

void player1Turn(int playere1Choice){ // player1 in hareketini yapan fonksiyon 
	int movingplace=playableArea[playere1Choice-1];
	board[movingplace]='X'; //movingplace -> oynamayý seçtiðimiz yer(1den 9a kadar)
}
void player2Turn(int playere2Choice){ // player2 nin hareketini yapan fonksiyon 
	int movingplace=playableArea[playere2Choice-1];
	board[movingplace]='O';
}
int boardController(){ //Oyun bitiyorsa 1 bitmiyorsa 0 döndürür
	int k=0,y=0;
	while(k<18){
		if(((board[k]==board[k+2])&&(board[k]==board[k+4])&&(board[k]!='*'))&&((k==0)||(k==6)||(k==12))||
		(board[k]==board[k+6])&&(board[k]==board[k+12])&&(board[k]!='*')||	
		(k==0)&&(board[k]==board[k+8])&&(board[k]==board[k+16])&&(board[k]!='*')||
		(k==4)&&(board[k]==board[k+4])&&(board[k]==board[k+8])&&(board[k]!='*')){
			y++;
			return 1;
		}
		k=k+2;
	}
	if(y==0){
		return 0;
	}


}
void boardToPlayableArea(void){
	int i,j=0,counter=0;
	for(i=0;i<19;i++){
			if(counter<3){  //counter -> 3 farklý sýrayý birbirinden ayýrmak için
				if(i%2==0){
					playableArea[j]=i;
					counter++;j++;
				}
			}
			else if(counter<6){
				if(i%2==0){
					playableArea[j]=i;
					counter++;j++;
				}
			}
			else if(counter<9){
				if(i%2==0){
					playableArea[j]=i;
					counter++;j++;
				}
			}
		}
}
int chooseMove(void){
	int playerchoice;
	printf("Your Choice (Type a number(1<=number<=9)) : ");
	scanf("%d",&playerchoice);
	system("cls");
	return playerchoice;
}

int boardControllerWithType(){ //Oyun bitiyorsa 1 bitmiyorsa 0 döndürür
	int k=0,y=0;
	while(k<18){
		if(((board[k]==board[k+2])&&(board[k]==board[k+4])&&(board[k]!='*'))&&((k==0)||(k==6)||(k==12))||
		(board[k]==board[k+6])&&(board[k]==board[k+12])&&(board[k]!='*')||	
		(k==0)&&(board[k]==board[k+8])&&(board[k]==board[k+16])&&(board[k]!='*')||
		(k==4)&&(board[k]==board[k+4])&&(board[k]==board[k+8])&&(board[k]!='*')){
			y++;
			if(board[playableArea[k]]=='X'){
				return 'X';	
			}
			else if(board[playableArea[k]=='O']){
				return 'O';
			}
		}
		k=k+2;
	}
	if(y==0){
		return 0;
	}
}

int inBoard(int x){
	return board[playableArea[x]];
	}

void resetBoard(void){
	for(i=0;i<19;i++){
		board[i]=board_copy[i];
	}
}
void copyBoard(void){
	for(i=0;i<19;i++){
		board_copy[i]=board[i];
	}
}

