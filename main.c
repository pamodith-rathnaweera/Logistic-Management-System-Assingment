#include <stdio.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define FUEL_PRICE 310.0


char *vehicle[3] = {"Van", "Truck", "Lorry"};
int capacity[3] = {1000, 5000, 10000};
float ratePerKm[3] = {30, 40, 80};
float avgSpeed[3] = {60, 50, 45};
float fuelEfficiency[3] = {12, 6, 4};

char cities[MAX_CITIES][30];
int cityCount = 0;
float distance[MAX_CITIES][MAX_CITIES];

int deliverySource[MAX_DELIVERIES];
int deliveryDestination[MAX_DELIVERIES];
float deliveryWeight[MAX_DELIVERIES];
int deliveryVehicleType[MAX_DELIVERIES];
float deliveryCost[MAX_DELIVERIES];
float fuelUsedList[MAX_DELIVERIES];
float totalCostList[MAX_DELIVERIES];
float profitList[MAX_DELIVERIES];
float chargeList[MAX_DELIVERIES];
float timeList[MAX_DELIVERIES];
int deliveryCount= 0;

void addCity(char cities[][30],int *cityCount);
void manageCities(char cities[][30], int cityCount);
void renameCity(char cities[][30], int cityCount);
void removeCity(char cities[][30], float distance[][30], int*cityCount);
void editDistance(char cities[][30], float distance[][30], int cityCount);
void displayDistanceTable(char cities[][30],float distance[][30], int cityCount);
void calculateDelivery(char cities[][30], float distance[][30], int *deliveryCount, int cityCount);
void leastDistanceRoute(char cities[][30], float distance[][30], int cityCount);
void report(float distance[][30], int deliverySource[], int deliveryDestination[], float customerCharge[], float profit[], float time[], int deliveryCount);

void addCity(char cities[][30],int *cityCount)
{
    if (*cityCount >= MAX_CITIES)
    {
        printf("City limit reached!\n");
        return;
    }
    printf("Enter city name: ");
    scanf("%s", cities[*cityCount]);
    (*cityCount)++;
    printf("City added successfully!\n");
}

void manageCities(char cities[][30], int cityCount)
{
    printf("\nCities:\n");
    if (cityCount == 0)
    {
        printf("No cities added yet.\n");
        return;
    }
    for (int i = 0; i < cityCount; i++)
        printf("%d. %s\n", i, cities[i]);
}

void renameCity(char cities[][30], int cityCount)
{

    int index;
    printf("Enter the city index you want to rename: ");
    scanf("%d", &index);

    if (index < 0 || index >= cityCount)
    {
        printf("Invalid city index!\n");
        return;
    }

    printf("Enter the new city name: ");
    scanf("%s", cities[index]);
    printf("City renamed successfully!\n");
}
