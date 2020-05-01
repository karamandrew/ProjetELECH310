/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "cyapicallbacks.h"
#include "keypad.h"
#include "math.h"

int count=0;
int countTimesw2=0;
int countTimesw3=0;
int countTime=0;
int ti=10000;
int taah=30000;
float vec[100];
_Bool mode;
_Bool light;
_Bool begin=1;
_Bool rxbegin=0, rxend=0, flag=0;
char *mot;
char formmot[8];
int morsecode[4]={0,0,0,0};
int morseint=0, k=0;
int morsetottimespace=0;
uint8 rxData;
char8 rxData_char;
struct pair{
    char let;
    double num;
    double num1;
};
struct pair semaphore_alphabet[26] = {{'a',0,0},
  {'b',0,45},
  {'c',0,90},
  {'d',0,135},
  {'e',0,180},
  {'f',45,0},
  {'g',45,45},
  {'h',45,90},
  {'i',45,135},
  {'j',45,180},
  {'k',90,0},
  {'l',90,45},
  {'m',90,90},
  {'n',90,135},
  {'o',90,180},
  {'p',135,0},
  {'q',135,45},
  {'r',135,90},
  {'s',135,135},
  {'t',135,180},
  {'u',180,0},
  {'v',180,45},
  {'w',180,90},
  {'x',180,135},
  {'y',180,180},
  {'z',158,158}};

void pinsWrite(int value){
    if (light){
        value=0;
    }
    Pin_1_Write(value);
    Pin_2_Write(value);
    Pin_3_Write(value);
    Pin_4_Write(value);
}

void soundPlay(){
    if (count==99){
        count=0;
    }
    Timer_ReadStatusRegister();
    VDAC8_1_SetValue(vec[count]*128); //*128 to adapt the magnitude
    count++;
}

void morse(char letter){
    morsecode[0]=0;
    morsecode[1]=0;
    morsecode[2]=0;
    morsecode[3]=0;
    if(letter=='a'){
        morsecode[0]=ti;
        morsecode[1]=taah;
    }
    else if(letter=='b'){
        morsecode[0]=taah;
        morsecode[1]=ti;
        morsecode[2]=ti;
        morsecode[3]=ti;
    }
    else if(letter=='c'){
        morsecode[0]=taah;
        morsecode[1]=ti;
        morsecode[2]=taah;
        morsecode[3]=ti;
    }
    else if(letter=='d'){
        morsecode[0]=taah;
        morsecode[1]=ti;
        morsecode[2]=ti;
    }
    else if(letter=='e'){
        morsecode[0]=ti;
    }
    else if(letter=='f'){
        morsecode[0]=ti;
        morsecode[1]=ti;
        morsecode[2]=taah;
        morsecode[3]=ti;
    }
    else if(letter=='g'){
        morsecode[0]=taah;
        morsecode[1]=taah;
        morsecode[2]=ti;
    }
    else if(letter=='h'){
        morsecode[0]=ti;
        morsecode[1]=ti;
        morsecode[2]=ti;
        morsecode[3]=ti;
    }
    else if(letter=='i'){
        morsecode[0]=ti;
        morsecode[1]=ti;
    }
    else if(letter=='j'){
        morsecode[0]=ti;
        morsecode[1]=taah;
        morsecode[2]=taah;
        morsecode[3]=taah;
    }
    else if(letter=='k'){
        morsecode[0]=taah;
        morsecode[1]=ti;
        morsecode[2]=taah;
    }
    else if(letter=='l'){
        morsecode[0]=ti;
        morsecode[1]=taah;
        morsecode[2]=ti;
        morsecode[3]=ti;
    }
    else if(letter=='m'){
        morsecode[0]=taah;
        morsecode[1]=taah;
    }
    else if(letter=='n'){
        morsecode[0]=taah;
        morsecode[1]=ti;
    }
    else if(letter=='o'){
        morsecode[0]=taah;
        morsecode[1]=taah;
        morsecode[2]=taah;
    }
    else if(letter=='p'){
        morsecode[0]=ti;
        morsecode[1]=taah;
        morsecode[2]=taah;
        morsecode[3]=ti;
    }
    else if(letter=='q'){
        morsecode[0]=taah;
        morsecode[1]=taah;
        morsecode[2]=ti;
        morsecode[3]=taah;
    }
    else if(letter=='r'){
        morsecode[0]=ti;
        morsecode[1]=taah;
        morsecode[2]=ti;
    }
    else if(letter=='s'){
        morsecode[0]=ti;
        morsecode[1]=ti;
        morsecode[2]=ti;
    }
    else if(letter=='t'){
        morsecode[0]=taah;
    }
    else if(letter=='u'){
        morsecode[0]=ti;
        morsecode[1]=ti;
        morsecode[2]=taah;
    }
    else if(letter=='v'){
        morsecode[0]=ti;
        morsecode[1]=ti;
        morsecode[2]=ti;
        morsecode[3]=taah;
    }
    else if(letter=='w'){
        morsecode[0]=ti;
        morsecode[1]=taah;
        morsecode[2]=taah;
    }
    else if(letter=='x'){
        morsecode[0]=taah;
        morsecode[1]=ti;
        morsecode[2]=ti;
        morsecode[3]=taah;
    }
    else if(letter=='y'){
        morsecode[0]=taah;
        morsecode[1]=ti;
        morsecode[2]=taah;
        morsecode[3]=taah;
    }
    else if(letter=='z'){
        morsecode[0]=taah;
        morsecode[1]=taah;
        morsecode[2]=ti;
        morsecode[3]=ti;
    }
}
void modifymorsecode(char letter){
    morse(letter);
    morsecode[1]+=morsecode[0];
    morsecode[2]+=morsecode[1];
    morsecode[3]+=morsecode[2];
    if (morsecode[1]<=morsecode[0]){    morsetottimespace=0;
    }else if(morsecode[2]<=morsecode[1]){   morsetottimespace=5000;
    }else if(morsecode[3]<=morsecode[2]){   morsetottimespace=10000;
    }else { morsetottimespace=15000;}
}

CY_ISR( MORSE ){
    if (begin){
        modifymorsecode(mot[morseint]);
        if(morsecode[0]==ti) UART_PutChar('.');
        if(morsecode[0]==taah) UART_PutChar('-');
        if(morsecode[1]-morsecode[0]==ti) UART_PutChar('.');
        if(morsecode[1]-morsecode[0]==taah) UART_PutChar('-');
        if(morsecode[2]-morsecode[1]==ti) UART_PutChar('.');
        if(morsecode[2]-morsecode[1]==taah) UART_PutChar('-');
        if(morsecode[3]-morsecode[2]==ti) UART_PutChar('.');
        if(morsecode[3]-morsecode[2]==taah) UART_PutChar('-');
        UART_PutChar(' ');
        
        if(light){
            for (int ba=0; ba<26; ba++){
                if (semaphore_alphabet[ba].let==mot[morseint]){
                    PWM_1_WriteCompare2((int)((semaphore_alphabet[ba].num/1.8)+26)); //flags move from 26(0°) to 126(180°)
                    PWM_1_WriteCompare1((int)((semaphore_alphabet[ba].num1/1.8)+26));
                }
            }
        
        }
    }
    begin = 0;
    
    if(countTime>morsetottimespace+morsecode[3]){
        Timer_ReadStatusRegister();
        if(countTime>morsetottimespace+morsecode[3]+20000){ //20000 represent the space between 2 letters
            begin=1;
            countTime=0;
            morseint++;
            if(strlen(mot)==(morseint)){
                morseint=0;
                rxend=1;
                UART_PutChar('\n');
                interrupt_Stop();
            }
        }
    }
    else{
        if(countTime<morsecode[0] || ((countTime>(morsecode[0]+5000)) && (countTime<morsecode[1]+5000)) || (countTime>morsecode[1]+10000 && countTime<morsecode[2]+10000) || (countTime>morsecode[2]+15000 && countTime<morsecode[3]+15000)){           
            soundPlay();
        }
        else{
            Timer_ReadStatusRegister();
        }       
    }
    countTime++;
}

CY_ISR( SW1_Handler ){
    soundPlay();
    if (!SW1_Read()){
        pinsWrite(0);
        interrupt_Stop();
    }
}

CY_ISR( SW2_Handler ){
    if (countTimesw2>=5000){
        pinsWrite(0);
        interrupt_Stop();
    }
    else{
        pinsWrite(1);
        soundPlay();
        countTimesw2++; //5000*50µs = 250ms
    }
}

CY_ISR( SW3_Handler ){
    if (countTimesw3>=15000){
        pinsWrite(0);
        interrupt_Stop();
    }
    else{
        pinsWrite(1);
        soundPlay();
        countTimesw3++; //15000*50µs = 750ms
    }
}

CY_ISR ( uart_rx_Handler ) {
uint8_t status = 0;
do{
    // Checks if no UART Rx errors
    status = UART_ReadRxStatus ();
    if (( status & UART_RX_STS_PAR_ERROR ) |
        ( status & UART_RX_STS_STOP_ERROR ) |
        ( status & UART_RX_STS_BREAK ) |
        ( status & UART_RX_STS_OVERRUN ) ) {
    // Parity , framing , break or overrun error
    LCD_Position (1 ,0);
    LCD_PrintString (" UART err");
    }
    // Check that rx buffer is not empty and get rx data
    if ( ( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0){
        
        rxData = UART_ReadRxData ();
        rxData_char = rxData+'0';
        formmot[k]=rxData;
        k++;
        LCD_PutChar(rxData);
        rxbegin=1;
    }
} while (( status & UART_RX_STS_FIFO_NOTEMPTY ) != 0);
}

int main(void)
{
    isr_StartEx(uart_rx_Handler);
    CyGlobalIntEnable; /* Enable global interrupts. */
    for(int i=0; i<=99; i++){
       vec[i]= sin(i*2*3.14159265/50)+1;
    }
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    LCD_ClearDisplay();
    keypadInit();
    Timer_Start();
    VDAC8_1_Start();
    ADC_Start();
    ADC_StartConvert();
    AMux_1_Start();
    PWM_1_Start();
    UART_Start();
    int lcdcount=0;

    UART_PutString("Hello\n");
    UART_GetChar();

    for(;;)
    {
        if(rxbegin){
            
            rxbegin=0;
            mot=formmot;
            interrupt_StartEx(MORSE);
        }
        if(rxend){
            while (k>0){
            formmot[k]=_NULL;
            k--;
            }
            rxend=0;
        }
        
        if(keypadScan() != 'z'){
            char keypad=keypadScan();
            if(keypad == '*'){
                mot="alexis";
                interrupt_StartEx(MORSE);
            }
            else if(keypad == '#'){
                mot="arthur";
                interrupt_StartEx(MORSE);
            }
            else if(keypad!= 'z'){
                if(lcdcount==8){LCD_Position(1,0);}
                if(lcdcount==16){LCD_Position(0,0);}
                lcdcount++;
                LCD_PutChar(keypad);
                CyDelay(80);
            }
        }
        AMux_1_FastSelect(0);
        if(ADC_CountsTo_mVolts(ADC_Read32())<1000){
            light=0;
        }
        else{
            light=1;
        }
        
        //SW1 HANDLER
        if(SW1_Read()){
            pinsWrite(1);
            interrupt_StartEx(SW1_Handler);
        }
        //SW2 HANDLER
        if(SW2_Read() && countTimesw2==0){
            interrupt_StartEx(SW2_Handler);
        }
        if(countTimesw2>=5000){
            CyDelay(1); //prevent the bug of fast clicking
            if(!SW2_Read()){
                countTimesw2=0;
            }
        }
        //SW3 HANDLER
        if(SW3_Read() && countTimesw3==0){
            interrupt_StartEx(SW3_Handler);
        }
        if(countTimesw3>=15000){
            CyDelay(1); //prevent the bug of fast clicking
            if(!SW3_Read()){
                countTimesw3=0;
            }
        }
        //SW4
        if(SW4_Read()){
            mode=!mode; //define if flag 1 or two moves with the potentiometer
            for(;SW4_Read();){} //prevent mode to change too fast, blocks the main for loop
        }
        
        if(light){
            AMux_1_FastSelect(1);
            float val= (ADC_CountsTo_mVolts(ADC_Read32())/51.06)+26;
            if(mode){
                PWM_1_WriteCompare2(val);
            }
            else{
                PWM_1_WriteCompare1(val);
            }
        }
    }
}

/* [] END OF FILE */
