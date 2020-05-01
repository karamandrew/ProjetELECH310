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
int ti=10000; //Value morse code
int taah=30000; //Value morse code
float vec[100];
_Bool mode;
_Bool light;
_Bool begin=1;
_Bool rxbegin=0, rxend=0, flag=0;
char *mot;
char formmot[8]; // Char of length 8
int morsecode[4]={0,0,0,0};
int morseint=0, k=0;
int morsetottimespace=0;
uint8 rxData;
char8 rxData_char;
struct pair{
    char let;
    double num;
    double num1;
};// Classe pair qui prend la lettre, angle drapeau 1 et angle drapeau 2

/* Arbitrary semaphore code encoding*/

// On crée on objet pair
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

// Method pour pas toujours devoir les écrire
void pinsWrite(int value){// 1 ou 0
    if (light){ // Si lumière, value se remet à 0
        value=0;
    }
    Pin_1_Write(value);
    Pin_2_Write(value);
    Pin_3_Write(value);
    Pin_4_Write(value);
}

void soundPlay(){
    if (count==99){ // O de base, sert a compter que élément de la liste vec on va jouer.
        count=0;
    }
    Timer_ReadStatusRegister(); // On lit la valeur toutes les 50 milisecondes
    VDAC8_1_SetValue(vec[count]*128); // 128 module l'amplitude plus haut
    count++;
}

/* Encode each letter into 4 or more morse character */
void morse(char letter){ // Ne retourne rien, modifie juste la variable globale morsecode
    morsecode[0]=0; // Morse code is list of 4 values, we initiate all the values to zero. So, a word is made of letter, each made of a list of 4 values
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

// Ask explanations for this!
void modifymorsecode(char letter){ // Char letter= mot[morseint] 
    morse(letter); // letter= mot[0,1,...] It 
    morsecode[1]+=morsecode[0]; //On additionne le temps de chaque lettre 
    morsecode[2]+=morsecode[1];
    morsecode[3]+=morsecode[2];
    // Autre variable: morsetottimespace, on veut savoir combien d'emplacement total il y a dans la lettre
    if (morsecode[1]<=morsecode[0]){    morsetottimespace=0; 
    }else if(morsecode[2]<=morsecode[1]){   morsetottimespace=5000;
    }else if(morsecode[3]<=morsecode[2]){   morsetottimespace=10000;
    }else { morsetottimespace=15000;}
}

CY_ISR( MORSE ){
    if (begin){ // Se fait appeler quan on a finit une lettre
        modifymorsecode(mot[morseint]);// mot is char of length 8 and morseint is equal to 0 --> first element of the char
        // Traduit le morse dans l'uart pour le user screen
        if(morsecode[0]==ti) UART_PutChar('.');
        if(morsecode[0]==taah) UART_PutChar('-');
        if(morsecode[1]-morsecode[0]==ti) UART_PutChar('.'); // Soustraire la valeur précédente car on a additionné avant
        if(morsecode[1]-morsecode[0]==taah) UART_PutChar('-');
        if(morsecode[2]-morsecode[1]==ti) UART_PutChar('.');
        if(morsecode[2]-morsecode[1]==taah) UART_PutChar('-');
        if(morsecode[3]-morsecode[2]==ti) UART_PutChar('.');
        if(morsecode[3]-morsecode[2]==taah) UART_PutChar('-');
        UART_PutChar(' ');
        // Ducoup les drapeaux bougent que lorsqu'on passe à la lettre suivante.
        //if(light){
            for (int ba=0; ba<26; ba++){
                if (semaphore_alphabet[ba].let==mot[morseint]){//si la lettre de l'élément 
                    PWM_1_WriteCompare2((int)((semaphore_alphabet[ba].num/1.8)+26));// offset de 26, et nonus on va de 26 à 126
                    PWM_1_WriteCompare1((int)((semaphore_alphabet[ba].num1/1.8)+26));
                }
            }
        
        //}
    }
    begin = 0; // Once we did this, we set begin back to 0
    
    if(countTime>morsetottimespace+morsecode[3]){//Si contime est plus grand que l'ensemble des valeurs et de l'espace entre les valuers d'un mot, ca veut dire qu'on a fait tout une lettre
        Timer_ReadStatusRegister(); // Permet de doser le timing? 
        if(countTime>morsetottimespace+morsecode[3]+20000){ // countime continue jusqu'a ce qu'on ai ajouté le temps d'un espace entre deux lettre
            begin=1;
            countTime=0;
            morseint++; // Deuxième lettre du mot
            if(strlen(mot)==(morseint)){ // Fin du mOT
                morseint=0;
                rxend=1;//  We active the end of the rx?
                UART_PutChar('\n');// On passe à la ligne
                //memset(formmot, 0, strlen(formmot));
                interrupt_Stop();// On sort de l'interupt MORSE
            }
        }
    }
    else{ // Si on a pas fini la lettre, on est ici
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

CY_ISR( SW4_Handler ){
    soundPlay();
    if (!SW1_Read()){
        pinsWrite(0);
        interrupt_Stop();
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
       vec[i]= sin(i*2*3.14159265/50)+1; // Divise une période de sinus (2pi) en 100 vecteurs
    }
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LCD_Start();
    LCD_ClearDisplay();
    //_Bool allum=1;
    keypadInit();
    Timer_Start();
    VDAC8_1_Start();
    ADC_Start();
    ADC_StartConvert();
    PWM_1_Start();
    AMux_1_Start();
    UART_Start();
    int lcdcount=0; // Why here?

    UART_PutString("Hello\n"); // Why here ?
    UART_GetChar();
    for(;;)
    {
        if(rxbegin){ //Boolean, initially = 0, pass a 1 lorsque l'uart est lancé
            
            rxbegin=0;
            mot=formmot; // formmor= char of length 8
            interrupt_StartEx(MORSE);// We go to morse interrupt
        }
        if(rxend){ // mot fini
            while (k>0){// On remoet formot a 0
            formmot[k]=_NULL;
            k--;
            }
            rxend=0;
        }
        
        if(keypadScan() != 'z'){// on appuye suru une touche
            char keypad=keypadScan();// on récupère la valeur
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
                CyDelay(80);// Ca s'imprime trop vite sinon
            }
        }
        AMux_1_FastSelect(0);//photosensor a l'adc
        if(ADC_CountsTo_mVolts(ADC_Read32())<1000){
            light=0;
        }
        else{
            light=1;
        }
        
        /* 4.5
        overflow=0x80 & Timer_ReadStatusRegister();
        if(overflow){
            count++;
            if (count==1000){
                if(allum){
                    Pin_4_Write(1);
                }
                if(!allum){
                    Pin_4_Write(0);
                }
                allum=!allum;
                count=0;
            }
        }*/
        /* 4.6
        overflow=0x80 & Timer_ReadStatusRegister();
        if(overflow){
            if (count==99){
                count=0;
            }
            VDAC8_1_SetValue(vec[count]*128);
            count++;
        }
        */
        
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
            mode=!mode; // Boolean defines which flag will move
            for(;SW4_Read();){} //La boucle principale est bloquée tant qu'on est appué, et permet de pas changer plusieurs fois
        }
        AMux_1_FastSelect(1);
        float val= (ADC_CountsTo_mVolts(ADC_Read32())/51.06)/10+26;
        if(light){
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
