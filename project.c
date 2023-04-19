#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>



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
struct userpanel
{
    char passport[10];
    char name[20];
    char boardingstation[20];
    int seat_num;
    char email[20];
    char destination[20];
    struct userpanel *following ;
}*stream,*begin;

void details()
{
    printf("\n\t Enter your passport number:");
	scanf("%s",stream->passport);//reads a line from stdin and stores it into the string pointed
	printf("\n\t Enter your  name:");
	scanf("%s",stream->name); 
	printf("\n\t Enter your email address:");
	scanf("%s",stream->email); 
    printf("\n\t Enter the Boarding station: ");
    scanf("%s",stream->boardingstation);
    printf("\n\t Enter the Destination : ");
    scanf("%s",stream->destination);
}



void reserveflight(int x)
{
	stream = begin;
	if (begin == NULL)
	{
		// first user
		begin = stream = (struct userpanel*)malloc(sizeof(struct userpanel));
		details();
		stream->following = NULL;
		printf("\n\t Seat booking successful!");
		printf("\n\t your seat number is: Seat A-%d", x);
		stream->seat_num = x;
		return;
	}
	else if (x > 50) // FULL SEATS
	{
		printf("\n\t\t Seat Full.");
		return;
	}
	else
	{
		// next user
		while (stream->following)
			stream = stream->following;
		stream->following = (struct userpanel *)malloc(sizeof(struct userpanel));
		stream = stream->following;
		details();
		stream->following = NULL;
		printf("\n\t Seat booking succesful!");
		printf("\n\t your seat number is: Seat A-%d", x);
		stream->seat_num = x;
		return;
	}
} 

void cancelflight()
{
    struct userpanel *dummy;
	stream = begin;
	system("cls");
	char passport[10];
	printf("\n\n Enter passport number to delete record?:");
	fgets(passport,10,stdin);
	if (strcmp(begin->passport, passport) == 0)
	{
		dummy = begin;
		begin = begin->following;
		free(dummy);
		printf(" booking has been deleted");
		
		return;

	}

	while (stream->following)
	{
		if (strcmp(stream->following->passport, passport) == 0)
		{
			dummy = stream->following;
			stream->following = stream->following->following;
			free(dummy);
			printf("has been deleted ");
			// getch();
			// Sleep(800);
			return;
		}
		stream = stream->following;
	}
	printf("passport number is wrong please check your passport");

}

void display()
{
   stream = begin;
	while (stream)
	{
		printf("\n\n Passport Number : %-20s", stream->passport);
		printf("\n         name : %-20s", stream->name);
		printf("\n      email address: %-20s", stream->email);
		printf("\n      Seat number: A-%d", stream->seat_num);
		printf("\n     Boarding station:%-20s",stream->boardingstation);
        printf("\n     Destination:%-20s", stream->destination);
		stream = stream->following;
	}
}
void savefile()
{
	FILE *fpointer = fopen("user panel records", "w");
	if (!fpointer)
	{
		printf("\n Error in opening file!");
		return;
		// Sleep(800);
	}
	stream = begin;
	while (stream)
	{
		fprintf(fpointer, "%-10s", stream->passport);
		fprintf(fpointer, "%-20s", stream->name);
		fprintf(fpointer, "%-20s", stream->email);
        fprintf(fpointer,"%-20s",stream->boardingstation);
        fprintf(fpointer, "%-20s", stream->destination);
        fprintf(fpointer, "\n");
		stream = stream->following;
	}
	printf("\n\n\t Details have been saved to a file (user panel records)");
	fclose(fpointer);
}
void userLogin(){
    int choice,num=1;
    begin=stream=NULL;
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

               case 1 : reserveflight(num);
                        num++;
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
                printf("Thank you for using our app\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (1);

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
    case 3:
        return  0;
    
    default:
        printf("\nplease enter valid choice!\n");
        break;
    }while(true);
   
// getch();
    }while(true);

}


