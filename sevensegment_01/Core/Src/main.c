/* A->D13
   B->D14
   C->D4
   D->C7
   E->C4
   F->B10
   G->B6
 */







#define AHB1ENR (*((volatile unsigned int*)0x40023830))=0b1111; // Enable clock for GPIOA and GPIOB GPIOC and GPIOD


#define gpiod_moder (*((volatile unsigned int*)0x40020c00))
#define gpiod_odr (*((volatile unsigned int*)0x40020c14))

#define gpioa_idr (*((volatile unsigned int*)0x40020010))

#define gpiob_moder (*((volatile unsigned int*)0x40020400))
#define gpiob_odr (*((volatile unsigned int*)0x40020414))

#define gpioc_moder (*((volatile unsigned int*)0x40020800))
#define gpioc_odr (*((volatile unsigned int*)0x40020814))

#define b_moderset gpiob_moder |= ((0b01<<12)|(0b01<<20)); // Output mode on pins B6, B10
#define c_moderset gpioc_moder |= ((0b01<<8)|(0b01<<14)); // Output mode on pins C4, C7
#define d_moderset gpiod_moder |= ((0b01<<8)|(0b01<<26)|(0b01<<28)); // Output mode on pins D4, D13, D14



#define b_odr_reset gpiob_odr= 0x0; // Reset pins B6, B10,
#define c_odr_reset gpioc_odr= 0x0; // Reset pins C4, C7
#define d_odr_reset gpiod_odr= 0x0; // Reset pins D4, D13, D14
#define A_enable gpiod_odr |= 1<<13; // D13 connected A so A Enable
#define B_enable gpiod_odr |= 1<<14; // D14 connected B so B Enable
#define C_enable gpiod_odr |= 1<<4; // D4 connected C so C Enable
#define D_enable gpioc_odr |= 1<<7; // C7 connected D so D Enable
#define E_enable gpioc_odr |= 1<<4; // C4 connected E so E Enable
#define F_enable gpiob_odr |= 1<<10; // B10 connected F so F Enable
#define G_enable gpiob_odr |= 1<<6; // B6 connected G so G Enable

void delay(){
    int delay=0xFDEAF;
    while(delay--){
        if(gpioa_idr & 1<<0){
                return;
        }
    }
}

void delay2(){
    int delay=0xFDEAF;
    if(gpioa_idr & 1<<0)
    	while(delay--);
}

void init (){
    AHB1ENR;
    b_moderset;
    c_moderset;
    d_moderset;
    b_odr_reset;
    c_odr_reset;
    d_odr_reset;
}

void reset(){
    b_odr_reset;
    c_odr_reset;
    d_odr_reset;
}

void sevensegment(int data){
    switch (data)
    {
    case 0:
        A_enable;
        B_enable;
        C_enable;
        D_enable;
        E_enable;
        F_enable;
        break;
    case 1:
        B_enable;
        C_enable;
        break;
    case 2:
        A_enable;
        B_enable;
        G_enable;
        E_enable;
        D_enable;
        break;
    case 3:
        A_enable;
        B_enable;
        G_enable;
        C_enable;
        D_enable;
        break;
    case 4:
        F_enable;
        G_enable;
        B_enable;
        C_enable;
        break;
    case 5:
        A_enable;
        F_enable;
        G_enable;
        C_enable;
        D_enable;
        break;
    case 6:
        A_enable;
        F_enable;
        G_enable;
        C_enable;
        D_enable;
        E_enable;
        break;
    case 7:
        A_enable;
        B_enable;
        C_enable;
        break;
    case 8:
        A_enable;
        B_enable;
        C_enable;
        D_enable;
        E_enable;
        F_enable;
        G_enable;
        break;
    case 9:
        A_enable;
        B_enable;
        C_enable;
        D_enable;
        F_enable;
        G_enable;
        break;
    default:
        break;
    }
}

void zerotonine(){
    int i;
    for(i=0;i<10;i++){
        sevensegment(i);
        delay();
        reset();
    }
}

int number(){
    char stnumber[]= "20190701027";
    int i=0;
    while(stnumber[i] != '\0'){
        switch(stnumber[i]){
            case '0':
                sevensegment(0);
                delay2();
                reset();
                break;
            case '1':
                sevensegment(1);
                delay2();
                reset();
                break;
            case '2':
                sevensegment(2);
                delay2();
                reset();
                break;
            case '3':
                sevensegment(3);
                delay2();
                reset();
                break;
            case '4':
                sevensegment(4);
                delay2();
                reset();
                break;
            case '5':
                sevensegment(5);
                delay2();
                reset();
                break;
            case '6':
                sevensegment(6);
                delay2();
                reset();
                break;
            case '7':
                sevensegment(7);
                delay2();
                reset();
                break;
            case '8':
                sevensegment(8);
                delay2();
                reset();
                break;
            case '9':
                sevensegment(9);
                delay2();
                reset();
                break;
        }
        i++;
    }
}

int main(){
    init();
    while(1){
        zerotonine();
        while(gpioa_idr & 1<<0){
            number();
        }
    }
}
