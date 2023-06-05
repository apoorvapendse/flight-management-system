#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>



struct userSchema
{
    char passport[12];
    char name[20];
    char boardingstation[20];
    int seat_num;
    char email[20];
    char destination[20];
    struct userpanel *following ;
};
struct Flight{
    char arrivalTime[100];
    char departureTime[100];
    char startLocation[100];
    char endLocation[100];
    float seatCost;
    int totalSeatCount;
    int seatsLeft;
    int *seatArray;
    int seatIndex;
    struct Booker* passengers;
    struct Flight* next;
    int priority;
    int id;
    struct userSchema* users;
};
struct Flight* flightHead=NULL;
int totalFlights = 0;
//we will create a priority queue of flights and admin can add flights and delete departed or cancelled flights from this



void printFlights(){
     struct Flight* temp = flightHead;
    while(temp!=NULL)
    {
        
        printf("\n\n---------------------------------------------------\n");
      

        printf("\n\nFlightID:%d\n",temp->id);
        printf("Starting Location: %s\n",temp->startLocation);
        printf("End Location: %s\n",temp->endLocation);
        printf("Arrival Time: %s\n", temp->arrivalTime);
        printf("Departure Time: %s\n", temp->departureTime);
        printf("Seat Cost: %f\n", temp->seatCost);
        printf("Seats Left: %d\n", temp->seatsLeft);
        

        temp = temp->next;
    }
}

int bookFlight(int flightID){
    struct Flight* temphead = flightHead;
    while(temphead->id!=flightID){
        temphead=temphead->next;
    }
    //now i am on the flight whose seat is to be booked
    struct Flight* currFLight = temphead;
    if(currFLight->seatsLeft<=0){
        printf("Sorry all seats all full");
        return -1;
    }

    printf("enter the passport number:");
    scanf("%s",currFLight->users[currFLight->seatIndex].passport);
    
    printf("enter the name:");
    scanf("%s",currFLight->users[currFLight->seatIndex].name);
    
    printf("enter the email:"); 
    scanf("%s",currFLight->users[currFLight->seatIndex].email);
    
   
    
    
    currFLight->seatIndex++;
    currFLight->seatsLeft--;
    return currFLight->seatIndex-1;//this will be the index of the seat that got booked right now



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
    scanf("%d",&tempFlight->totalSeatCount);

    //creating the seat Array 
    tempFlight->seatArray = (int*)malloc(sizeof(int)*tempFlight->totalSeatCount);
    tempFlight->seatIndex = 0;
    tempFlight->seatsLeft = tempFlight->totalSeatCount;
    tempFlight->users =(struct userSchema*)malloc(sizeof(struct userSchema)*(tempFlight->totalSeatCount));


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


void details()
{
    
printFlights();
    printf("\namong the above displayed flights enter the id of the flight you want to book\n");
    int flightID;
    scanf("%d",&flightID);
   int bookedSeatNumber =  bookFlight(flightID);
    printf("\nCongratulations Your Flight is Booked!\nYour Seat Number is:%d\n\n\n",bookedSeatNumber);
    

}





void cancelflight()
{
   
}

void display(int passportNumber)
{
   struct Flight* currentFlight = flightHead;
   while(currentFlight!=NULL){
    for(int i = 0 ; i < currentFlight->totalSeatCount;i++){
        if(currentFlight->users[i].passport){
            
        }
    }
   }
}
void savefile()
{
	// FILE *fpointer = fopen("user panel records", "w");
	// if (!fpointer)
	// {
	// 	printf("\n Error in opening file!");
	// 	return;
	// 	// Sleep(800);
	// }
	// stream = begin;  
	// while (stream)
	// {
	// 	fprintf(fpointer, "%-10s", stream->passport);
	// 	fprintf(fpointer, "%-20s", stream->name);
	// 	fprintf(fpointer, "%-20s", stream->email);
    //     fprintf(fpointer,"%-20s",stream->boardingstation);
    //     fprintf(fpointer, "%-20s", stream->destination);
    //     fprintf(fpointer, "\n");
	// 	stream = stream->following;
	// }
	// printf("\n\n\t Details have been saved to a file (user panel records)");
	// fclose(fpointer);
}
void userLogin(){
     printf("\n\n---------------------------------------------------\n");
    int choice,num=1;
   
     do{
   printf("\nPlease choose an action:\n");
                printf("1. Reserve a flight\n");
                printf("2. Cancel a reservation\n");
                printf("3. Exit\n");
                printf("4.Display records\n");
                printf("5.Save a file\n");
                printf("Your choice: ");
                scanf("%d", &choice);
                switch (choice) { 

               case 1 : details();
                        break;
                case 2 : cancelflight();
                         break;
                case 3  :exit(0);
                         break;
                case 4  :display();
                         break;
                case 5 : savefile();
                        break;
                default: printf("Enter the valid choice.");
                        break;
}
}while (choice!=3);

}
void adminLogin(){
     printf("Welcome to admin login\n");
   int choice;
    do
    {
        printf("\n\n---------------------------------------------------\n");
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
                int id;
                printf("enter the unique id of the flight you want to delete\n");
                scanf("%d",&id);
                deleteFlights(id);
                break;
          
            case 4:
                printf("Exiting admin login...\n\n\n");
               break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice!=4);

}


int main()
{
  printf(" *************\n");
  printf(" *************\n");
  printf(" *      WELCOME TO VIT AIRWAY      *\n");
  printf(" *************\n");
  printf(" *************");

    int loginChoice;
    do{
        printf("press 1 to login as user\npress 2 to login as admin\npress 3 to exit the program\n");
    scanf("%d",&loginChoice);
    switch (loginChoice)
    {
    case 1:
        userLogin();
        break;
    case 2:
        adminLogin();
        break;
    case 3:
        return  0;
    
    default:
        printf("\nplease enter valid choice!\n");
        break;
    }
   
// getch();
    }while(true);

}


