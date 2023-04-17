#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct Booker{
int id;
char name[100];
float bill;
int seats;
};

struct Flight{
    char arrivalTime[100];
    char departureTime[100];
    char startLocation[100];
    char endLocation[100];
    float seatCost;
    int totalSeats;
    struct Booker* passengers;
    struct Flight* next;
    int priority;
};
struct Flight* flightHead=NULL;
int totalFlights = 0;
//we will create a priority queue of flights and admin can add flights and delete departed or cancelled flights from this


void book(struct Booker* customer){

}
void createBooker(){

}
void printDetails(struct Flight *f)
{
    printf("start:%s\n",f->startLocation);
    printf("end:%s\n",f->endLocation);
}

void printFlights(){
    struct Flight* temp = flightHead;
    while(temp!=NULL)
    {
        printf("Flight Priority %d\n",temp->priority);
        printf("Starting Location %s\n",temp->startLocation);
        printf("End Location %s\n",temp->endLocation);

        temp = temp->next;
    }
}

void createFlight(){
    struct Flight* tempFlight = (struct Flight*)malloc(sizeof(struct Flight));


    printf("Starting Location:");
    fgets(tempFlight->startLocation,100,stdin);
    printf("Ending Location:");
    fgets(tempFlight->endLocation,100,stdin);
    printf("Arrival Time:");
    fgets(tempFlight->arrivalTime,100,stdin);
    printf("Departure Time:");
    fgets(tempFlight->departureTime,100,stdin);
    printf("Cost per Seat:");
    scanf("%f",&tempFlight->seatCost);
    printf("\nTotal Seat Count:");
    scanf("%d",&tempFlight->totalSeats);

    if(flightHead==NULL)//means no flights other than this
    {   
        tempFlight->priority = 1;
        tempFlight->next=NULL;
        flightHead = tempFlight;

    }
    else{
        printf("enter the priority of the flight\n");
        int p;
        scanf("%d",&p);
        tempFlight->priority = p;
        printf("you set the priority of this flight as :%d\n",tempFlight->priority);
      
        if(tempFlight->priority==1)
        {
            tempFlight->next=flightHead;
            flightHead = tempFlight;
        }
        else{
            struct Flight* tempHead = flightHead;
            while(tempHead->next!=NULL && tempHead->next->priority<tempFlight->priority){
                tempHead = tempHead->next;
                
            }
            if(tempHead->next==NULL)
            {  
                tempHead->next = tempFlight;
                tempFlight->next=NULL;
            }
            else{
             
                tempFlight->next = tempHead->next;
                tempHead->next = tempFlight;
            }

        }

    }
    
    totalFlights++;


}

int main()
{
    printf("welcome to the flight reservation system\n");
    // char choice;
    // do
    // {
    // printf("press 1 to book flight tickets\npress 2 to login as admin\npress any other key to exit\n");
    //  switch(choice){
    //     case '1':
       
    //     showFlights();
    //     break;

    //     case '2':
    //     adminLogin();
    //     break;

    //     default:
    //     printf("thank you for using our app\n");
    //     return 1;
        
    //  }
    // } while (1);
 int exitChoice;
    do
    {
       
        printf("press 1 to exit\n");
        scanf("%d",&exitChoice);
        getchar();

        createFlight();
        
    } while (exitChoice!=1);
    
   printFlights();


}