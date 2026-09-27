#include <xc.h>
#include <pic16f877a.h>

#define _XTAL_FREQ 20000000

#define LcdDataBus PORTD
#define LcdControlBus PORTC
#define LcdDataBusDirnReg TRISD

#define LCD_RS 0
#define LCD_EN 2

#define RowA RB0
#define RowB RB1
#define RowC RB2
#define RowD RB3

#define C1 RB4
#define C2 RB5
#define C3 RB6
#define C4 RB7

#define MOTOR1 RC4
#define MOTOR2 RC5

void delay(int cnt)
{
    int i, j;

    for(i = 0; i < cnt; i++)
    {
        for(j = 0; j < 1275; j++);
    }
}

/* Write Command to LCD */
void Lcd_CmdWrite(char cmd)
{
    /* Send Higher Nibble */
    LcdDataBus = (cmd & 0xF0);

    LcdControlBus &= ~(1 << LCD_RS);
    LcdControlBus |=  (1 << LCD_EN);

    delay(1);

    LcdControlBus &= ~(1 << LCD_EN);

    /* Send Lower Nibble */
    LcdDataBus = ((cmd << 4) & 0xF0);

    LcdControlBus &= ~(1 << LCD_RS);
    LcdControlBus |=  (1 << LCD_EN);

    delay(1);

    LcdControlBus &= ~(1 << LCD_EN);
}

/* Write Data to LCD */
void Lcd_DataWrite(char dat)
{
    /* Higher Nibble */
    LcdDataBus = (dat & 0xF0);

    LcdControlBus |= (1 << LCD_RS);
    LcdControlBus |= (1 << LCD_EN);

    delay(1);

    LcdControlBus &= ~(1 << LCD_EN);

    /* Lower Nibble */
    LcdDataBus = ((dat << 4) & 0xF0);

    LcdControlBus |= (1 << LCD_RS);
    LcdControlBus |= (1 << LCD_EN);

    delay(1);

    LcdControlBus &= ~(1 << LCD_EN);
}

/* LCD String Display */
void LCD_PutStr(const char *str)
{
    char i = 0;

    while(str[i])
    {
        Lcd_DataWrite(str[i++]);
    }
}

/* LCD Initialization */
void Lcd_Init()
{
    delay(20);

    Lcd_CmdWrite(0x02);   // 4-bit mode
    Lcd_CmdWrite(0x28);   // 2 line
    Lcd_CmdWrite(0x0E);   // Display ON
    Lcd_CmdWrite(0x01);   // Clear display
    Lcd_CmdWrite(0x80);   // First line
}
void InitKeypad()
{
    PORTB = 0x00;
    TRISB = 0xF0;

    OPTION_REG &= 0x7F;
}

char READ_SWITCHES()
{
    RowA=0; RowB=1; RowC=1; RowD=1;

    if(C1==0){delay(250); while(C1==0); return '7';}
    if(C2==0){delay(250); while(C2==0); return '8';}
    if(C3==0){delay(250); while(C3==0); return '9';}
    if(C4==0){delay(250); while(C4==0); return '/';}

    RowA=1; RowB=0; RowC=1; RowD=1;

    if(C1==0){delay(250); while(C1==0); return '4';}
    if(C2==0){delay(250); while(C2==0); return '5';}
    if(C3==0){delay(250); while(C3==0); return '6';}
    if(C4==0){delay(250); while(C4==0); return 'X';}

    RowA=1; RowB=1; RowC=0; RowD=1;

    if(C1==0){delay(250); while(C1==0); return '1';}
    if(C2==0){delay(250); while(C2==0); return '2';}
    if(C3==0){delay(250); while(C3==0); return '3';}
    if(C4==0){delay(250); while(C4==0); return '-';}

    RowA=1; RowB=1; RowC=1; RowD=0;

    if(C1==0){delay(250); while(C1==0); return 'C';}
    if(C2==0){delay(250); while(C2==0); return '0';}
    if(C3==0){delay(250); while(C3==0); return '=';}
    if(C4==0){delay(250); while(C4==0); return '+';}

    return 'n';
}

void main()
{
    char key;
    char password[5];
    char i = 0;

    TRISC = 0x00;
    PORTC = 0x00;
    
    TRISD = 0x00;
    PORTD = 0x00;

    Lcd_Init();
    InitKeypad();
    MOTOR1 = 0;
    MOTOR2 = 0;
   __delay_ms(100);

    
    while(1)
    {
        
        Lcd_CmdWrite(0x01);
        Lcd_CmdWrite(0x80);
        LCD_PutStr("Enter Password:");
        i = 0;

    while(i < 4)
    {
        key = READ_SWITCHES();

        if(key != 'n')
        {
            password[i] = key;
            Lcd_DataWrite('*');
            i++;
            __delay_ms(200);
        }
    }

    if(password[0]=='1' && password[1]=='2' &&
           password[2]=='3' && password[3]=='4')      
         {
            Lcd_CmdWrite(0x01);
            LCD_PutStr("Password Correct");
            MOTOR1 = 1;
            MOTOR2 = 0;
             __delay_ms(2000);

                        
            Lcd_CmdWrite(0xC0);
            LCD_PutStr("Welcome Home!!");
            __delay_ms(2000);
            MOTOR1 = 0;
            MOTOR2 = 1;
            __delay_ms(2000);
            MOTOR1 = 0;
            MOTOR2 = 0;
            
        }
        else
        {
            Lcd_CmdWrite(0x01);
            LCD_PutStr("Password Wrong");
          
            
            Lcd_CmdWrite(0xC0);
            LCD_PutStr("Try Again!");
            __delay_ms(1000);
        }
    }
}