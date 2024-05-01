#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io.h"
#include "tm4c123gh6pm.h"
#include "UART.h"
#include "GPS.h"
#include "distance.h"

		char j=0;
		float lat[100];
		float lon[100];
		float Dis=0;
		float total_distance =0 ;
		float longitude,latitude;

float GPS_format2(void){
    
	
    char GPS_data [100];            //array to save the desired data of GPS
    char GPS_logname[] = "$GPRMC";  //logname of desired data
		char fill_gps_counter = 0;
    char recieved_char;
    const char delimiter[] = ","; //to separate data from eachother
    char tokens[7][20];  // 7 is the number of desired data from GPS_module
  // Tokenize the string using strtok
    char *token = strtok(GPS_data, delimiter);
    char token_count = 0;
		char i=0;
    char flag = 1;
    do {
    flag = 1;
    for (i=0; i<7;i++) {
    if (UART1_ReadChar()!=GPS_logname[i]) { 
    flag=0; 
    break;
    }
    }
    }while(flag == 0);

    strcpy(GPS_data , "");
 
    do
    {
    recieved_char = UART1_ReadChar();
    GPS_data[fill_gps_counter++] = recieved_char ;

    }while(recieved_char!='*') ;


    
    //instead of making another loop to terminate at '*'
    
  

    // Loop through each token and save them in string array
    while (token != NULL && token_count < 10) {
        strcpy(tokens[token_count], token);
        token_count++;
        token = strtok(NULL, delimiter);
    }
    //extracting desired variables of the string array
      if (strcmp (tokens[3],"N")==0)
             {
        latitude = atof(tokens[2]);
             lat[j]=latitude ;
             }
        else
                {
        latitude = -atof(tokens[2]) ;
                    lat[j]=latitude ;

                }
     if (strcmp (tokens[5],"E")==0)
         {
 longitude = atof(tokens[4]);
         lon[j]= longitude ; 
         }
 else
 {
    longitude = -atof(tokens[4]);
      lon[j]= longitude ; 
 }
 
 j++ ;
 
 Dis = calcdistance(lon[j],lat[j],lon[j+1],lat[j+1]);
 total_distance += Dis;
 return total_distance;
}

/*void GPS_format(void){										//intial function was made if the passed data was a char array
    
    char GPS_data [100];            //array to save the desired data of GPS
    char GPS_logname[] = "$GPRMC";  //logname of desired data
    const char delimiter[] = ","; //to separate data from eachother
    char tokens[7][20];  // 7 is the number of desired data from GPS_module
  // Tokenize the string using strtok
    char *token = strtok(GPS_data, delimiter);
    char token_count = 0;

    //simple function to find the required GPS_logname
    char *result = strstr(UART1_ReadChar(),GPS_logname);
    //intializing an array starting after the this logname
    strcpy(GPS_data,result+strlen(GPS_logname));
    

    // Loop through each token and save them in string array
    while (token != NULL && token_count < 10) {
        strcpy(tokens[token_count], token);
        token_count++;
        token = strtok(NULL, delimiter);
    }
    //extracting desired variables of the string array
       if (strcmp (tokens[3],"N")==0)
        latitude = atof(tokens[2]);
        else
        latitude = -atof(tokens[2]) ;

     if (strcmp (tokens[5],"E")==0)
 longitude = atof(tokens[4]);
 else
    longitude = -atof(tokens[4]);
}*/
