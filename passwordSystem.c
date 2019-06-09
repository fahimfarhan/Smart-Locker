#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h> 
#include <string.h>

#define F_CPU 1000000UL
#define D4 eS_PORTD4
#define D5 eS_PORTD5
#define D6 eS_PORTD6
#define D7 eS_PORTD7
#define RS eS_PORTC6
#define EN eS_PORTC7
#define false 0
#define true 1
#define bool int

#define myPasswordLength 4
#include "lcd.h"

int key = 0;        //allocating integer to reset the LCD once it reaches its display limit
int keypressed = 0; //integer for storing matrix value
char str[100] ;
char keypad()
{
	int i , newKeyPressed;
    if (PINA != 0b11110000)
    {
    	
        _delay_ms(5);
        keypressed = PINA;  //taking the column value into integer
        DDRA ^= 0b11111111; //making rows as inputs and columns as ouput
        _delay_ms(1);
        PORTA ^= 0b11111111; //powering columns
        _delay_ms(1);
        keypressed |= PINA; //taking row value and OR ing it to column value
        newKeyPressed=0;
	for(int i = 7 ; i >=0 ; i-- )
	{
		if((keypressed&(1<<i))!=0) newKeyPressed |= ( 1 << (7-i) ) ;
	}
	//_delay_ms(1000);
	keypressed = newKeyPressed ;
	for(int i = 7 ; i >=0 ; i-- )
	{
		//if((keypressed&(1<<i))==0)str[7-i]='0';
		//else {str[7-i]='1' ; }
	}
	//Lcd4_Set_Cursor(1,1);
	//Lcd4_Write_String(str);
	//Lcd4_Set_Cursor(2,1);
        if (keypressed == 0b01110111)
        {
        		
            //LED_test(1);
            
            //Lcd4_Write_String("1"); //if row1 and column1 is high show “1”
            key++;
            _delay_ms(300);
            return '1' ;
        }

        if (keypressed == 0b10110111)
        {
            // LED_test(4);
           
            //Lcd4_Write_String("4"); // if row1 and column2 is high show “4”
            key++;
            _delay_ms(300);
            return '4' ;
                }

        if (keypressed == 0b11010111)
        {
           
            //Lcd4_Write_String("7"); // if row1 and column3 is high show “7”
            key++;
            _delay_ms(300);
            return '7' ;
        }
        if (keypressed == 0b01111011)
        {
           
            //Lcd4_Write_String("2"); // if row2 and column1 is high show “2”
            key++;
            _delay_ms(300);
            return '2' ;
        }

        if (keypressed == 0b10111011)
        {
           
            //Lcd4_Write_String("5"); // if row2 and column2 is high show “5”
            key++;
            _delay_ms(300);
            return '5' ;
        }

        if (keypressed == 0b11011011)
        {
            //LED_test(8);
            //Lcd4_Write_String("8"); // if row2 and column3 is high show “8”
            key++;
            _delay_ms(300);
            return '8' ;
        }

        if (keypressed == 0b11101011)
        {

            //Lcd4_Write_String("0"); // if row2 and column4 is high show “0”
            key++;
            _delay_ms(300);
            return '0' ;
        }

        if (keypressed == 0b01111101)
        {
            //LED_test(3);
            //Lcd4_Write_String("3");
            key++;
            _delay_ms(300);
            return '3' ;
        }

        if (keypressed == 0b10111101)
        {
            //ED_test(6);
            //Lcd4_Write_String("6");
            key++;
            _delay_ms(300);
            return '6' ;
        }

        if (keypressed == 0b11011101)
        {
            //LED_test(9);
            //Lcd4_Write_String("9");
            key++;
            _delay_ms(300);
            return '9' ;
        }
        if (keypressed == 0b11101101)
        {
            //LED_test(12);
            //Lcd4_Write_String("#");
            key++;
            _delay_ms(300);
            return '#' ;
        }

        if (keypressed == 0b01111110)
        {
            //LED_test(11);
            //Lcd4_Write_String("A");
            key++;
            _delay_ms(300);
            return 'A' ;
        }
        if (keypressed == 0b10111110)
        {
            //LED_test(13);
            //Lcd4_Write_String("B");
            key++;
            _delay_ms(300);
            return 'B' ;
        }

        if (keypressed == 0b11011110)
        {
            //LED_test(14);
            //Lcd4_Write_String("C");
            key++;
            _delay_ms(300);
            return 'C' ;
        }

        if (keypressed == 0b11101110)
        {
            //LED_test(15);
            //Lcd4_Write_String("D");
            key++;
            _delay_ms(300);
            return 'D' ;
        }
        if (keypressed == 0b11100111)
        {
            //LED_test(10);
            //Lcd4_Write_String("*"); //if row1 and column4 is high show “*”
            key++;
            _delay_ms(300);
            return '*' ;
        }
        keypressed = 0;     //after showing integer erasing the row column memory
        DDRA ^= 0b11111111; //shifting input and power port
        _delay_ms(1);
        PORTA ^= 0b11111111; //powering row pins of keypad
        _delay_ms(220);
    }
    if (key == 16)
    {
    //Lcd4_Set_Cursor(1,1);
        key = 0;
          //Lcd4_Clear();
        //index=(index+1)%2;
    }
    //Lcd4_Clear();
    
    return 'x' ;

    
}


void EEPROM_write(unsigned int uiAddress, unsigned char ucData)
{
    /* wait for previous write to finish*/
    while (EECR & (1 << EEWE))
        ;
    /*set up and data registers*/
    EEAR = uiAddress;
    EEDR = ucData;

    /*write logical 1 to eemwe*/
    EECR |= (1 << EEMWE);

    /*start writing*/
    EECR |= (1 << EEWE);
}

unsigned char EEPROM_read(unsigned int uiAddress)
{
    while (EECR & (1 << EEWE)) ;
    EEAR = uiAddress;
    EECR |= (1 << EERE);
	_delay_ms(1000);
    return EEDR;
}

// ekhane user jei password dibe seta thabe

unsigned char pass[5][5] , yo[5]="1234";
unsigned char realPassword[5] ;
// ekhane duita password er modhe compare korbo
//duita thik hole rakhbo
//noyto bad

void readPassword()
{	
	 int i,j ;
	 memset(realPassword,0,5);
   	 eeprom_read_block( realPassword,0,4 ) ;
   	 for(i=0;i<4;i++)
   	 {
   	 	if(realPassword[i]<'0'|| realPassword[i] > '9' )
   	 	{
   	 		for(j=0;j<4;j++)realPassword[j]='0' ;
   	 		break;
   	 	}
   	 } 
   	 realPassword[4]='\0' ;

}
void writePassword()
{
	eeprom_write_block(pass[0],0,strlen(pass[0]));
}

bool areBothPasswordSame()
{
    unsigned int i = 0;
    bool b = true;
    for (i = 0; i < myPasswordLength; i++)
    {
        if (pass[0][i] != pass[1][i])
        {
            return false ;
        }
    }
    return true ;

}

void clearArray()
{
    int i = 0;
    for (i = 0; pass[0][i] != '\0'; i++)
    {
        pass[0][i] = 0;
    }
    for (i =0; pass[1][i] != '\0'; i++)
    {
        pass[1][i] = 0;
    }
}

bool passWordMatch()
{
	readPassword() ;
     int i ;
    for (i = 0; i < myPasswordLength; i++)
    {
        if (pass[0][i] != realPassword[i])
        {
            return false ;
        }
    }
    return true ;
}


void readPasswordFromUser(int id){
	int i , last = 0 ;
	for(i = 0; i < myPasswordLength ; i++ )pass[id][i] = 0 ;
	
	while(1)
 	 {
 	 	if(last==myPasswordLength)
 	 	{
 	 		return ; 
 	 	}
	  	char c = keypad();
	  	
	  	if(c<='9'&&c>='0')
	  	{
	  		pass[id][last]= c ;
	  		last++ ;
	  		Lcd4_Clear();
			Lcd4_Set_Cursor(2,1);
			Lcd4_Write_String(pass[id]);
	  	}
	  	
	  	
  	_delay_ms(500);
  	}
}

void updatePassword()
{
	int size = 0 ;
	Lcd4_Clear();
		
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("give Old Password");
	readPasswordFromUser(0); // give old password
	
	bool isCorrectPassword = passWordMatch();// password match
	if(isCorrectPassword==false){
		Lcd4_Clear();		
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("wrong Password");
		return ;
	}
	Lcd4_Clear();
		
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("giveNewPass");
	
	readPasswordFromUser(0);
	
	Lcd4_Clear();	
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("againPassword");
	
	readPasswordFromUser(1);
	
	if ( areBothPasswordSame() == 1 ) 
	{
		Lcd4_Clear();		
		Lcd4_Set_Cursor(1,0);
		Lcd4_Write_String("PasswordUpdated");
		writePassword();
	}
	else
	{
	Lcd4_Clear();
		
	Lcd4_Set_Cursor(1,0);
	Lcd4_Write_String("PasswordNotSame");
	}
	
}

void turnOffAlarm()
{
	Lcd4_Clear();
		
	Lcd4_Set_Cursor(1,1);
	Lcd4_Write_String("give Password");
	readPasswordFromUser(0); // give old password
	
	bool isCorrectPassword = passWordMatch();// password match
	if(isCorrectPassword==false){
		Lcd4_Clear();		
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("wrong Password");
		return ;
	}
	Lcd4_Clear();		
		Lcd4_Set_Cursor(1,1);
		Lcd4_Write_String("RIGHT Password");
	PORTB = 0x1 ;
	_delay_ms(5000);
	PORTB = 0x00 ;
	

}

int main(void)
{

    DDRA = 0xF0; //taking column pins as input and row pins as output
    _delay_ms(1);
    PORTA = 0x0F; // powering the row ins
    _delay_ms(1); 
    DDRD = 0xFF;
    DDRB=0xFF ;
    
  DDRC = 0xFF;
  PORTB = 0x00 ;
  int i;
  Lcd4_Init();
  
  readPassword() ;
  
  Lcd4_Clear();
  Lcd4_Set_Cursor(1,1);
  Lcd4_Write_String(realPassword);
  
  _delay_ms(2000);
  
  Lcd4_Clear();	
  
  	//Lcd4_Clear();
  	//Lcd4_Set_Cursor(1,1);
  	//realPassword[4]='\0' ;
  	//Lcd4_Write_String(realPassword);
  	//_delay_ms(300);

  
  
  while(1)
  {
  	Lcd4_Clear();
  	Lcd4_Set_Cursor(1,0);
  	Lcd4_Write_String("A = alarm off");
  	Lcd4_Set_Cursor(2,0);
  	Lcd4_Write_String("B=updatePassword");
  	_delay_ms(300);
  	char c = keypad();
  	// a = alarm off
  	// b = update password

  	if(c!='x')
  	{
  		if(c=='B')
  		{
  			updatePassword();
  		}
  		else if(c == 'A')
  		{
  			turnOffAlarm() ;
  		}
  	}
  	
  	
  	_delay_ms(500);
  }
    /*Add this at the begining*/
    return 0;
}


