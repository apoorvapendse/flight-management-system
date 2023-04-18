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
    int id;
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
        printf("Starting Location: %s\n",temp->startLocation);
        printf("End Location: %s\n",temp->endLocation);
        printf("Arrival Time: %s\n", temp->arrivalTime);
        printf("Departure Time: %s\n", temp->departureTime);
        printf("Seat Cost: %f\n", temp->seatCost);
        printf("Total Seat Count: %d\n", temp->totalSeats);
        printf("unique id: %d\n", temp->id);

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
    printf("\nUnique ID:");
    scanf("%d",&tempFlight->id);

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

void deleteFlights(int uniqueID){
    struct Flight* tempHead = flightHead;
    if(tempHead==NULL){
        printf("Cannot delete, no flights are scheduled!\n");
        return;
    }
    if(tempHead->id==uniqueID)
    {
        struct Flight* del = tempHead;
        tempHead=tempHead->next;
        flightHead=tempHead;
        free(del);
        return;
    }

    //this will execute if list is not empty and head is not the flight to be deleted
    while(tempHead->next!=NULL && tempHead->next->id!=uniqueID){
        tempHead=tempHead->next;
    }
    
    //if temphead doesn't point to null we will delete the node just after tempHead
    if(tempHead->next!=NULL){
        struct Flight *del = tempHead->next;
        tempHead->next=tempHead->next->next;
        free(del);
        
    }
    else//meaning no such flight with given id exists
    {
        printf("flight does not exist!\n");
    }


}
int main()
{
    printf("welcome to the flight reservation system\n");
   int choice;
    do
    {
        printf("Press 1 to view available flights\n");
        printf("Press 2 to add a new flight\n");
        printf("Press 3 to Delete Flight\n");
        printf("Press 4 to exit\n");

        scanf("%d",&choice);
        getchar();

        switch(choice){
            case 1:
                printFlights();
                break;

            case 2:
                createFlight();
                break;

            case 3:
                int id;printf("enter the unique id of the flight you want to delete\n");
                scanf("%d",&id);
                deleteFlights(id);
                break;
          
            case 4:
                printf("Thank you for using our app\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (1);
 


}