#include<iostream>

#include<stdlib.h>

#include<unistd.h>

using namespace std;

char ubin[6]={'B','I','N','G','O','\0'};

char cbin[6]={'B','I','N','G','O','\0'};

int gp=0;					//game point to check win and finish game (if gp=-1 no win, if gp=1 userwins, if gp=2 computerwin ) (winchk and game function)

int urin_in =0, crin_in =0, ucin_in =0, ccin_in =0; //to store the index to chk repeatiation of row or column  

int ubin_in =0, cbin_in =0; 			//to store index to cross out the bingo

int call=0;							//referrance for display 

// Creating a class to control Entier Game

class bingo
	{
		int def[5][5];       				//array for value of defplayer for bingo board [row][column]	(defplayer function)

		int usr[5][5];  				//array for value of user for bingo board [row][column]		(getvalue function)

		

		int lr;		     				//lr-last removed number (display function)

		int urin[5], crin[5], ucin[5], ccin[5];		//to check the row or column where repeating 
		

		
		public: 
			void defplayer(); //Declaring a default player which act as computer

			void getvalue();

			void game();

			void display();

			void computer();

			void winchk();
			
			int finalchk();
	};

//defining member functions of the class





//assigning a constant value for default player

void bingo::defplayer()
{

	//assigning value using for loop
	int a=(rand()%25+1);
	for(int i =0; i<5; i++)
	{
		for(int j =0; j<5; j++)
		{
			
			
			usr[i][j]=0;		//assigning usr array with 0
			
			
			def[i][j]=a;		//assigning value for def array with rand value
			
			if(a==25)
			{
				a=0;
			}
			a++;
		
		}
	
	}
	


}






//getting value from the user 

void bingo::getvalue()
{
	int nchk[25];
	for(int c=0; c<25; c++)
	{
		nchk[c]=0;
	}
	
	
	int a, in=0;
	for(int i =0; i<5; i++)
	{
	    display();
		for(int j =0; j<5; j++)
		{
				label:
					
					cout<<"\nEnter the value of the element in row "<<i+1<<" and the column "<<j+1<<" :";
					cin>>a;																		//geting value
					
					//checking for repeatiation
			    	if(!(a<=25&&a>=1))
			    	{
				    	cout<<"\n\tplease Enter the number between 1-25"<<endl;
				    	a=0;
				    	goto label;
				    }
				    
				     //checking for repeating of number
				     
					for(int b=0; b<25; b++)
				    {
				    	if(nchk[b]==a)
						{
							cout<<"\n\tTHIS NUMBER ALREADY ENTERED.\n\tPLEASE ENTER ANY OTHE NUMBER"<<endl;
							goto label;
						}
					}
					usr[i][j]=a;
					nchk[in]=a;
					in++;
		}
		if(i==4)
		{
			cout<<"\n\n\tALL SET! LETS BEGIN....";
			sleep(2);
		}
	}
}







//Displaying user's bingo board

void bingo::display()
{
	system("cls");
	cout<<"\n\n\t\t\t\t\t\t"<<ubin<<endl;

//drawing board
    cout<<endl;
	cout<<"\t---------------------------------------------------------------------------------"<<endl;
	
	cout<<"\t|\t"<<usr[0][0]<<"\t|\t"<<usr[0][1]<<"\t|\t"<<usr[0][2]<<"\t|\t"<<usr[0][3]<<"\t|\t"<<usr[0][4]<<"\t|\t"<<endl;
	
	cout<<"\t---------------------------------------------------------------------------------"<<endl;
	
	cout<<"\t|\t"<<usr[1][0]<<"\t|\t"<<usr[1][1]<<"\t|\t"<<usr[1][2]<<"\t|\t"<<usr[1][3]<<"\t|\t"<<usr[1][4]<<"\t|\t"<<endl;
	
	cout<<"\t---------------------------------------------------------------------------------"<<endl;
	
	cout<<"\t|\t"<<usr[2][0]<<"\t|\t"<<usr[2][1]<<"\t|\t"<<usr[2][2]<<"\t|\t"<<usr[2][3]<<"\t|\t"<<usr[2][4]<<"\t|\t"<<endl;
	
	cout<<"\t---------------------------------------------------------------------------------"<<endl;
	
	cout<<"\t|\t"<<usr[3][0]<<"\t|\t"<<usr[3][1]<<"\t|\t"<<usr[3][2]<<"\t|\t"<<usr[3][3]<<"\t|\t"<<usr[3][4]<<"\t|\t"<<endl;
	
	cout<<"\t---------------------------------------------------------------------------------"<<endl;
	
	cout<<"\t|\t"<<usr[4][0]<<"\t|\t"<<usr[4][1]<<"\t|\t"<<usr[4][2]<<"\t|\t"<<usr[4][3]<<"\t|\t"<<usr[4][4]<<"\t|\t"<<endl;
	
	cout<<"\t---------------------------------------------------------------------------------"<<endl;
	

	if(call>6)										//TO MAKE IT VISIBLE ONLY AFTER THE GAME START
	{
	cout<<"\nLast number removed :"<<lr<<endl;
	}
	call++;
}







//defining game 

void bingo::game()
{
	int rnum;          //variable to store the number to be removed
	do
	{
		display();
		label:
		cout<<"\nEnter The Number To be Removed : ";
		cin>>rnum;
		if(!(rnum<=25&&rnum>=1))
		{
			cout<<"\nplease Enter the number between 1-25"<<endl;
			goto label;
		}
		
	//checking for repetation of the number
	
		int c=0;
		for( int i=0; i<5; i++)
		{
			for(int j=0; j<5; j++)
			{
				if(rnum==usr[i][j])
				{
					usr[i][j]=0;		//removing the number from the usr array
					c=1;
				}
				
				if(rnum==def[i][j])
				{
					def[i][j]=0;		//removing the number from the def array
				}
			}
		}
		
		if(c==0)
		{
			cout<<"\nThis number is already removed please enter any other number 1-25"<<endl;
			goto label;
		}
		
		lr=rnum;					//for display purpose
		
		display();					//displaying board after removing the rnum
		
		winchk();
		
		if(gp!=1)
		{
			computer();
			cout<<"\n\nCOMPUTER REMOVED "<<lr;
			cout<<"\nPLEASE WAIT...";
			sleep(4);							//MAKING SLEEP BECAUSE USER WANT TO SEE WHICH NUMBER WAS REMOVED
		}
		
	}while(gp==-1);
}







//defining a function to remove a number as a 2nd player

void bingo::computer()
{
	int cnum;
	label:
		
	cnum=(rand()%25+1);			//picking a random number in 1-25 to be eliminated from def array
	


	int c=0;
	for( int i=0; i<5; i++)
	{
		for(int j=0; j<5; j++)
		{
			if(cnum==usr[i][j])
			{
			usr[i][j]=0;		//removing the number from the usr array
			c=1;
			}
			if(cnum==def[i][j])
			{
			def[i][j]=0;		//removing the number from the def array
			c=1;
			}
			
		}
	}
	
	//gettin the new number again if it already enter
	
	if(c==0)
	{
	goto label;
	}
	lr=cnum;
	display();
	winchk();
}








//Checking for row only with 0

void bingo::winchk()
{

//row checking


//check usr row for 0

	for(int i=0; i<5; i++)
	{
		int chk=0;
		
		//checking row 

		for(int j=0; j<5; j++)
		{
			
			//checkig for repeating row

			for(int a=0; a<=urin_in; a++)				
			{
				if(urin[a]==i)
				{
					j=4;
					break;
				}
			}

			if(usr[i][j]==0)
			{
			chk++;
			}
			else
			{
			break;
			}
		}
		
		if(chk==5)
		{
			cout<<"\n-->\'"<<ubin[ubin_in]<<"\'  REMOVED FROM BINGO (R)";
			ubin[ubin_in]='*';
			urin[urin_in]=i;
			ubin_in++;
			urin_in++;
			sleep(2);
			
		}
	}



//checking def row for  0

	for(int i=0; i<5; i++)
	{
		int chk=0;
		
		//checking row 

		for(int j=0; j<5; j++)					
		{
			
		//checkig for repeating row

			for(int a=0; a<=crin_in; a++)				
			{
				if(crin[a]==i)
				{
					j=4;
					break;
					
				}
			}

			if(def[i][j]==0)
			{
			chk++;
			}
			else
			{
			break;
			}
		}
		
		if(chk==5)
		{
			cbin[cbin_in]='*';
			crin[crin_in]=i;
			cbin_in++;
			crin_in++;
			sleep(2);
			
		}
	}
	
	
	
//_________________________________________________________________________________//


//column checking


//check usr column for 0
	
	for(int i=0; i<5; i++)
	{
		int chk=0;
		
		//checking column 

		for(int j=0; j<5; j++)
		{
		//checkig for repeating column

			for(int a=0; a<=ucin_in; a++)				
			{
				if(ucin[a]==i)
				{
					j=4;
					break;
				}
			}

			if(usr[j][i]==0)
			{
				chk++;
			}
			else
			{
				break;
			}
		}
		
		if(chk==5)
		{
			cout<<"\n-->\'"<<ubin[ubin_in]<<"\' REMOVED FROM BINGO(C)";			//NOTIFYING HE USER ABOUT REMOVED LETTER
			
			ubin[ubin_in]='*';
			ucin[ucin_in]=i;
			
			ubin_in++;
			ucin_in++;
			
			sleep(2);			//GIVING TIME TO USER FOR READ
			
		}
	}

//checking def column for  0

	for(int i=0; i<5; i++)
	{
		int chk=0;
		
		//checking column  

		for(int j=0; j<5; j++)					
		{
			
			//checkig for repeating column
			
			for(int a=0; a<=ccin_in; a++)				
			{
				if(ccin[a]==i)
				{
					j=4;
					break;
				}
			}

			if(def[j][i]==0)
			{
			chk++;
			}
			else
			{
			break;
			}
		}
		
		if(chk==5)
		{
			cbin[cbin_in]='*';
			ccin[ccin_in]=i;
			cbin_in++;
			ccin_in++;
			sleep(2);
			
		}
	}
	
	gp=finalchk();	

}









//final check for the winner

int bingo::finalchk()
{
	//checking whether the user is won

	if(ubin[4]=='*')
	{
		return 1;
	}

	//checking whether computer is won
	
	if(cbin[4]=='*')
	{
		return 2;
	}

	return -1;
	
}









int main()
{ 
	bingo play;
	play.defplayer();
	play.getvalue();
	play.game();

//displaying the victory message

	if(gp==1)						//IF USER WON
	{
		cout<<"\a\n\t\t \".....BINGO.....\"";
		cout<<"\n\t\t\"YOU WON THE MATCH\"";
		cout<<"\n\nCOMPUTER'S BINGO - "<<cbin;
	}
	

	if(gp==2)						//IF USER LOST
	{
		cout<<"\a\n\t\t\".....OOPS.....\"\n\t\tALMOST CLOSE";
		cout<<"\n\t\t\"SORRY. You Lost The Match\"\n \t\t\"BETTER LUCK NEXT TIME\"";
		cout<<"\n\nYOUR BINGO = "<<ubin;
		
	}	
	
	
}
