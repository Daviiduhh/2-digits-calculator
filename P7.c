/*
PRACTICA 7 - “CALCULADORA ARITMÉTICA DE 2 DÍGITOS” 
EQUIPO V 
8H1 - ELECTRONICA DIGITAL V
DAVID MADRID NAPOLES 17100201
CARLOS CAMACHO MATA 17100057
HECTOR SAMUEL RIVERA RUIZ 17100287
13/10/2020

DEBE DE MOSTAR LOS NOMBRES Y REGISTROS DE LOS ALUMNOS Y EL NOMBRE DE LA PRACTICA, 
AL PRESIONAR UN BOTON DEBE DE ENTAR A UN MENU DONDE TE PIDO SELECCIONAR UN SP 
QUE SE DEBERA DE CONFIRMAR CON EL MISMO BOTON, AL CONFIRMAR DEBERA DE MOSTRAR 
SI SE ESTA LLENANDO, VACIANDO, O SI EL NIVEL ESTA ESTABLE. EN ESTE MOMENTO SE 
DEBERA DE PODER REGRESAR A CONFIRMAR EL SP

*/
#INCLUDE <16F887.H>
#USE DELAY(CLOCK=4000000)
#FUSES INTRC_IO,NOWDT,NOPUT,MCLR,NOPROTECT,NOCPD,NOBROWNOUT
#FUSES NOIESO,NOFCMEN,NOLVP,NODEBUG,NOWRT,BORV21

#USE FAST_IO(A)
#USE FAST_IO(B)
#USE FAST_IO(C)
#USE FAST_IO(D)

#INCLUDE <LCD1.C>

INT Z = 0, OP = 0;
INT I = 0, J = 0, AUX = 0, CUENTA = 0, D = 0, U = 0, D1 = 0, D2 = 0, RN = 0;
LONG R = 0, LD1 = 0, LD2 = 0;
FLOAT RD = 0, D1D = 0, D2D = 0;

INT RV [16] = {1, 2, 3, 100, 4, 5, 6, 100, 7, 8, 9, 100, 200, 0, 200, 100};

VOID INICIO (){
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "      CETI      \n     COLOMOS    ");         
   DELAY_MS(500);
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "TGO. EN CONTROL \nAUTOMATICO E INS");         
   DELAY_MS(500);
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "   ELECTRONICA  \n    DIGITAL V   ");         
   DELAY_MS(500);
   
   FOR(J = 0; J <= 2; J++){ // EN CADA ITERACION MUESTRA EL R Y N DE UN ALM
      SWITCH (J){
         CASE 0:
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "DAVID MADRID     \n17100201            ");
            BREAK;
               
         CASE 1:
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "HECTOR RUIZ     \n17100287          ");
            BREAK;
                     
         CASE 2:
            LCD_GOTOXY(1,1);
            PRINTF(LCD_PUTC, "CAMACHO MATA     \n17100057         ");
            BREAK;
            }
      DELAY_MS(200);
   }
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "  CALCULADORA   \nARITMETICA 2 DIG");         
   DELAY_MS(500);
}
VOID TECLADO (){ //SE ENCARGA DE DETECTAR PULSACIONES EN EL TECLADO
   AUX = 0XEF;
   CUENTA = 0; //LLEVARA LA CUENTA, DETECTANDO LA CUENTA PRESIONADO
   FOR(I=0;I<4;I++){//EN CADA ITERACION REVISA UNA FILA DIFERENTE
         
      AUX=AUX>>1; //DESPLAZA UN CERO A LA DERECHA
      OUTPUT_A((INPUT_A()&0XF0)|(AUX&0X0F));
         
      IF(INPUT(PIN_A7)==0) //REVISDA ESTADO COLUMNA A7
      BREAK;
      CUENTA++;
      IF(INPUT(PIN_A6)==0) //REVISDA ESTADO COLUMNA A6
      BREAK;
      CUENTA++;
      IF(INPUT(PIN_A5)==0) //REVISDA ESTADO COLUMNA A5
      BREAK;
      CUENTA++;
      IF(INPUT(PIN_A4)==0) //REVISDA ESTADO COLUMNA A4
      BREAK;
      CUENTA++;
         
      DELAY_MS(20); //TIEMPO DE ESPERA NECESARIO PARA DETECTAR CAMBIOS
   }
}
VOID SUMA (){
   RN = D1 + D2;
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "%u + %u = %u      "D1, D2, RN);
}
VOID RESTA (){
   RN = D1 - D2;
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "%u - %u = %d       "D1, D2, RN);
}

VOID MULTI (){
   LD1 = D1;
   LD2 = D2;
   R = LD1 * LD2;
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "%u * %u = %Lu      "D1, D2, R);
}
VOID DIVI (){
   D1D = D1;
   D2D = D2;
   RD = D1D / D2D;
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "%1.0g / %2.0g = %2.2g      "D1D, D2D, RD);
}
VOID CONF () { //MENU DE CONFIRMACION
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "DATO 1 = %1u     "D1);
   LCD_GOTOXY(1,2);
   PRINTF(LCD_PUTC, "DATO 2 = %1u     "D2); 
   DELAY_MS(500);
         
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "SELECCIONA LA   \nOPERACION       ");
   DELAY_MS(500);
          
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "+=1 -=2 *=3 /=4 \nY PRESIONA *       ");
   DELAY_MS(500);
}

VOID MAIN (){
   SET_TRIS_A(0XF0); //DECLARAR SALIDAS
   OUTPUT_A(INPUT_A()&0XF0); //LIMPIAR BITS DE SALIDA
   LCD_INIT(); //INICIAR LCD
   
   INICIO (); //MUESTRA LOS MENSAJES DEL INICIO DEL PROGRAMA
   
   LCD_GOTOXY(1,1);
   PRINTF(LCD_PUTC, "INGRESA EL D1 Y \n   PRESIONA *   ");
   
   WHILE (TRUE){ //ESTADO PARA MOSTRAR EL MENSAJE DE D1
      WHILE(Z == -1){
         LCD_GOTOXY(1,1);
         PRINTF(LCD_PUTC, "INGRESA EL D1 Y \n   PRESIONA *   ");
         Z = 0; //PASA A ETAPA 1
      }
      WHILE(Z == 0){ //ETAPA 1
         TECLADO ();
         IF(CUENTA<16){ //SI SE PRESIONA EL TECLADO MATRICIAL
            
            IF(RV[CUENTA]<10){ //SI SE PRESIONA TECLA DIFERENTE A LAS DE NUMERO
               IF(U!=0){ //REVISA QUE UNIDADES TENGA UN VALOR
                  D = U; //TRANSFIERE SU VALOR A LAS DECENAS
               }
               U = RV[CUENTA]; //ASIGAN EL VALOR LEIDO A U
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "DATO 1 = %u%u     \n                "D,U);      
               D1 = (D*10)+(U); //GUARDA EL VALOR REAL DE D Y U
            }
            
            IF(CUENTA==12){ //SI SE PRESIONA EL ASTERISCO
               WRITE_EEPROM(D1,1);
               D = 0;
               U = 0;
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "INGRESA EL D2 Y \n   PRESIONA *   ");
               Z=1; //PASA A ETAPA 2
            }
            DO{
               TECLADO();
            }WHILE(CUENTA<16);
         }
      }
      
      WHILE(Z == 1){ //ETAPA 2
         TECLADO ();
         IF(CUENTA<16){ //SI SE PRESIONA EL TECLADO MATRICIAL
            
            IF(RV[CUENTA]<10){ //SI SE PRESIONA TECLA DIFERENTE A LAS DE NUMERO
               IF(U!=0){ //REVISA QUE UNIDADES TENGA UN VALOR
                  D = U; //TRANSFIERE SU VALOR A LAS DECENAS
               }
               U = RV[CUENTA]; //ASIGAN EL VALOR LEIDO A U
               LCD_GOTOXY(1,1);
               PRINTF(LCD_PUTC, "DATO 2 = %u%u     \n                "D,U);      
               D2 = (D*10)+(U); //GUARDA EL VALOR REAL DE D Y U
            }
            
            IF(CUENTA==12){ //SI SE PRESIONA EL ASTERISCO
               WRITE_EEPROM(D2,2);
               D = 0;
               U = 0;
               CONF ();
               Z=2; //PASA A ETAPA 3
            }
            DO{
               TECLADO();
            }WHILE(CUENTA<16);
         }
      }
      
      WHILE(Z == 2){ //ETAPA 3
         TECLADO ();
         IF(CUENTA<16){ //SI SE PRESIONA EL TECLADO MATRICIAL
            SWITCH(CUENTA){
               CASE 0: //CONFIRMA SUMA
                  LCD_GOTOXY(1,1);
                  PRINTF(LCD_PUTC, "+=1 -=2 *=3 /=4 \n      SUMA      ");
                  OP = 1;
                  BREAK;
               CASE 1: //CONFIRMA RESTA
                  LCD_GOTOXY(1,1);
                  PRINTF(LCD_PUTC, "+=1 -=2 *=3 /=4 \n      RESTA     ");
                  OP = 2;
                  BREAK;
               CASE 2: //CONFIRMA MULTIPLICACION
                  LCD_GOTOXY(1,1);
                  PRINTF(LCD_PUTC, "+=1 -=2 *=3 /=4 \n MULTIPLICACION ");
                  OP = 3;
                  BREAK;
               CASE 4: //CONFIRMA DIVISION
                  IF(D2==0){
                     LCD_GOTOXY(1,1);
                     PRINTF(LCD_PUTC, "+=1 -=2 *=3 /=4 \nERROR D2 = 0    ");
                  }
                  LCD_GOTOXY(1,1);
                  PRINTF(LCD_PUTC, "+=1 -=2 *=3 /=4 \n    DIVISION    ");
                  OP = 4;
            }
            IF(CUENTA==12){ //SI SE PRESIONA EL ASTERISCO
               Z = 3; //PASA A ETAPA 4
            }
            DO{
               TECLADO();
            }WHILE(CUENTA<16);
         }
      }
      
      WHILE(Z == 3){ //ETAPA 4
         SWITCH(OP){ //REALIZA LA OPERACION
            CASE 1:
               SUMA ();
               BREAK;
               
            CASE 2:
               RESTA ();
               BREAK;
               
            CASE 3:
               MULTI ();
               BREAK;
               
            CASE 4:
               DIVI ();
               BREAK;             
         }
         
         DELAY_MS(1000);
         Z=-1; //REGRSA A INICIO
      }
   }
}
      
      
      
