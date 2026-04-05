// Including all the basic Libraries I will need to complete the project
 #include <stdio.h>
 #include <stdlib.h>
 #include <ctype.h>

// these are the variable that I will need to initialise at the start of the code
 char ArrayTime[24][9];

 float settingsHeating = 0.00;
 float settingsVentilation = 0.00;
 float settingsLighting = 0.00;
 float ArrayTemperature[24][2];
 float ArrayHumidity[24];
 float ArrayMotion[24][6];


 int HourlyEnergy;
 int exitProgram;
 int DailyEnergy = 0;
 int TotalEnergy;

 float ArraySensors[10][24] = {
 //The array is to indicate what the times over the 24 hour period
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}
 };


 int ArrayConsumption[2][24] = {
 //The array is to indicate what the times over the 24 hour period
 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}};
//
 //The rooms in which are included in the specification are here
 void FilesRead(char *location) {

 int t;
 int k;

 //The fp with a * indicates to the user that it is a pointer
 FILE *fp;
 //The r in the brackets will mean that the access is read only 
 fp = fopen(location, "r");

 //When a null occurs in the code this means that an error occurs and a file cannot be found
 if(fp == NULL){
 printf("There is no file found for this room in this directory - Please make sure the files are there before continuing\n");
 //Exiting the programme
 exit(1);
 }

 // 24 hours a day the loop will occur 
 for(t=0; (t<24 && !feof(fp)); t++){
 //The t in the brackets indicates it is being used in an array
 fscanf(fp, "%s", ArrayTime[t]);
 //This will be used for temperatures
 fscanf(fp, "%f%f", &ArrayTemperature[t][0], &ArrayTemperature[t][1]);
 //This row is for humidity
 fscanf(fp, "%f", &ArrayHumidity[t]);

 //Due to the nature of the information that we will need to provide the loop will have 6 rows, hence the loop is 6
 //so a for loop would be most effective
 for(k=0; k<6; k++){
 //This row is for the motion array
 fscanf(fp,"%f", &ArrayMotion[t][k]);
                    }
                                    }
                                }

 //Main function
 int main()
 {

 int Selection;
 int RoomType;

 int Selection2;
 int Initialisation = 0;
 int Validate = 0;




 //Initialisation is the loop that will be needed to ensure that the threshold values have not been set yet
 if(Initialisation == 0){

    printf("The values for when the devices should be turned on have not been initialised yet - please do it now\n\n");

    printf("What value for the temperature do you want the heating to turn on?\n\n");
    scanf("%f", &settingsHeating);

    printf("What value for the humidity do you want the ventilation to turn on?\n\n");
    scanf("%f", &settingsVentilation);

    printf("What value for the distance do you want the lights to turn on? \n\n");
    scanf("%f", &settingsLighting);
 //The initialisation is set to one now, this means that it won't run through again.
    Initialisation = 1;
                        }





    do{
    printf("1. Bedroom \n 2. Kitchen \n 3. Living Room");
    scanf("%d", &RoomType);

        if(RoomType == 0){
        FilesRead("Bedroom.txt");
 //Setting the Validate to complete so the program can continue
        Validate = 1;
                                            }


        else if(RoomType == 1){
        FilesRead("Kitchen.txt");
        Validate = 1;
                                                }

        else if(RoomType == 2){
        FilesRead("LivingRoom.txt");
        Validate = 1;
                                                    }


        else{
        printf("You have not entered a valid location, your locations to choose from are:\n\n");
        printf("\n1. Bedroom \n2. Kitchen \n\3. Living Room\n");
            }

        } while(Validate == 0);



 while(exitProgram == 0){
 //This is the sub menu which is shown once the user enters the threshold values on initialisation
            printf("\n\n Can you please choose one of the two options?n\n");

            printf(" \n 1. Device configuration");

            printf(" \n 2. Exit");
            scanf("%d", &Selection);
 //When a one is entered
        if(Selection == 1){
        printf(" \n 1.Heating \n 2. Ventilation \n 3. Lighting\n");
        scanf("%d", &Selection2);


//When a one is entered
 if(Selection2 == 1){
 printf("\n\nThe temperature at which the heating turns on currently at %.2f\n\n",settingsHeating);
 printf("What would you like to new value to be?\n\n");
 scanf("%f", &settingsHeating);
 printf("The value has been changed to a new one\n\n");
 //This will leave the switch
 }


    else if(Selection2 == 2){
 printf("The humidity at which the ventilation turns on is currently at %.2f\n\n",settingsVentilation);
 printf("What would you like to new value to be?\n\n");
 scanf("%f", &settingsVentilation);
 printf("The value has been changed to a new one\n\n");
    }


else{
 printf("The distance at which the lighting turns on is currently at %f\n\n",settingsLighting);
 printf("What would you like to new value to be?\n\n");
 scanf("%f", &settingsLighting);
 printf("The value has been changed to a new one\n\n");
}

                }
                                        }

 //When a two is entered
 if(Selection2 == 2){
 exitProgram = exitProgram + 1;
 }

 //When a non valid value is entered

 //This will be used in the do while loop that takes the data from the array and processes it
 int z = 0;

 //This is the file pointer to energy
 FILE *Energy;
//This will give write access to Energy
 Energy = fopen("Energy.txt", "w+");




 FILE *LivFile;
 LivFile = fopen("LivingRoomDevices.txt", "w+");

 FILE *BedFile;
 BedFile = fopen("BedroomDevices.txt", "w+");


 FILE *KitFile;
 KitFile = fopen("KitchenDevices.txt", "w+");






 do{
 if(ArrayTemperature[z][1] < settingsHeating){
 ArraySensors[1][z] = 1;
 HourlyEnergy = HourlyEnergy + 300;
 }
 else{
 ArraySensors[1][z] = 0;
 }

 if(ArrayTemperature[z][2] < settingsHeating){
 ArraySensors[2][z] = 1;
 HourlyEnergy = HourlyEnergy + 300;
 }
 else{
 ArraySensors[2][z] = 0;
 }

 if(ArrayHumidity[0] > settingsVentilation){
 ArraySensors[3][z] = 1;
 HourlyEnergy = HourlyEnergy + 250;
 }
 else{
 ArraySensors[3][z] = 0;
 }

 if(ArrayMotion[z][0] > settingsLighting){
 ArraySensors[4][z] = 1;
 HourlyEnergy = HourlyEnergy + 100;
 }
 else{
 ArraySensors[4][z] = 0;
 }

 if(ArrayMotion[z][1] > settingsLighting){
 ArraySensors[5][z] = 1;
 HourlyEnergy = HourlyEnergy + 100;
 }
 else{
 ArraySensors[5][z] = 0;
 }


 if(ArrayMotion[z][2] > settingsLighting){
 ArraySensors[6][z] = 1;
 HourlyEnergy = HourlyEnergy + 100;
 }
 else{
 ArraySensors[6][z] = 0;
 }


 if(ArrayMotion[z][3] > settingsLighting){
 ArraySensors[7][z] = 1;
 HourlyEnergy = HourlyEnergy + 100;
 }
 else{
 ArraySensors[7][z] = 0;
 }


 if(ArrayMotion[z][4] > settingsLighting){
 ArraySensors[8][z] = 1;
 HourlyEnergy = HourlyEnergy + 100;
 }
 else{
 ArraySensors[8][z] = 0;
 }

 if(ArrayMotion[z][5] > settingsLighting){
 ArraySensors[9][z] = 1;
 HourlyEnergy = HourlyEnergy + 100;
 }
 else{
 ArraySensors[9][z] = 0;
 }

 z = z + 1;

 DailyEnergy = DailyEnergy + HourlyEnergy;
 HourlyEnergy = 0;

 }while(z != 24);

 z = 0;





 HourlyEnergy = 0;

 TotalEnergy = TotalEnergy + DailyEnergy;

 DailyEnergy = 0;

 fprintf(Energy, "\n\nThe amount of energy consumption on day one is: %d\n\n", TotalEnergy);


}
