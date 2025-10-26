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
void removeCity(char cities[][30], float distance[][MAX_CITIES], int*cityCount)
{

    int index;
    printf("Enter the city index you want to remove: ");
    scanf("%d", &index);

    if (index < 0 || index >= *cityCount)
    {
        printf("Invalid city index!\n");
        return;
    }


    for (int i = index; i < *cityCount - 1; i++)
    {
        strcpy(cities[i], cities[i + 1]);
        for (int j = 0; j < *cityCount; j++)
        {
            distance[i][j] = distance[i + 1][j];
            distance[j][i] = distance[j][i + 1];
        }
    }
    (*cityCount)--;
    printf("City removed successfully!\n");
}

void editDistance(char cities[][30], float distance[][MAX_CITIES], int cityCount)
{

    if (cityCount < 2)
    {
        printf("At least two cities are required!\n");
        return;
    }
    int i, j;
    printf("Enter source city index: ");
    scanf("%d", &i);
    printf("Enter destination city index: ");
    scanf("%d", &j);
    if (i == j)
    {
        printf("Distance from a city to itself is 0.\n");
        return;
    }

    if (i < 0 || j < 0 || i >= cityCount || j >= cityCount)
    {
        printf("Invalid indexes!\n");
        return;
    }

    printf("Enter distance (km): ");
    scanf("%f", &distance[i][j]);
    distance[j][i] = distance[i][j];
    printf("Distance recorded successfully!\n");

}

void displayDistanceTable(char cities[][30],float distance[][MAX_CITIES], int cityCount)
{
    if (cityCount == 0)
    {
        printf("No cities available.\n");
        return;
    }
    printf("\nDistance Table (km):\n\t");
    for (int i = 0; i < cityCount; i++)
        printf("%s\t", cities[i]);
    printf("\n");
    for (int i = 0; i < cityCount; i++)
    {
        printf("%s\t", cities[i]);
        for (int j = 0; j < cityCount; j++)
            printf("%.2f\t", distance[i][j]);
        printf("\n");
    }
}

void displayDistanceTable(char cities[][30],float distance[][MAX_CITIES], int cityCount)
{
    if (cityCount == 0)
    {
        printf("No cities available.\n");
        return;
    }
    printf("\nDistance Table (km):\n\t");
    for (int i = 0; i < cityCount; i++)
        printf("%s\t", cities[i]);
    printf("\n");
    for (int i = 0; i < cityCount; i++)
    {
        printf("%s\t", cities[i]);
        for (int j = 0; j < cityCount; j++)
            printf("%.2f\t", distance[i][j]);
        printf("\n");
    }
}

void calculateDelivery(char cities[][30], float distance[][MAX_CITIES], int *deliveryCount, int cityCount)
{
    if (*deliveryCount >= MAX_DELIVERIES)

        if (cityCount < 2)
        {
            printf("Add at least two cities first!\n");

        }


    int src, dest, vehicleType;
    float weight;
    printf("Enter source city index: ");
    scanf("%d", &src);
    printf("Enter destination city index: ");
    scanf("%d", &dest);
    printf("Enter weight (kg): ");
    scanf("%f", &weight);
    printf("Vehicle (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicleType);
    vehicleType--;
  if (src == dest)
    {
        printf("Error: Same cities!\n");

    }
    if (vehicleType < 0 || vehicleType > 2)
    {
        printf("Invalid vehicle type!\n");

    }
    if (weight > capacity[vehicleType])
    {
        printf("Error: Exceeds capacity!\n");

    }

    float D = distance[src][dest];
    float R = ratePerKm[vehicleType];
    float S = avgSpeed[vehicleType];
    float E = fuelEfficiency[vehicleType];


    float cost = D * R * (1 + weight / 10000.0);
    float fuelUsed = D / E;
    float fuelCost = fuelUsed * FUEL_PRICE;
    float totalCost = cost + fuelCost;
    float profit = cost * 0.25;
    float customerCharge = totalCost + profit;
    float time = D / S;
 int i = *deliveryCount;
    deliverySource[i] = src;
    deliveryDestination[i] = dest;
    deliveryVehicleType[i] = vehicleType;
    deliveryWeight[i] = weight;
    deliveryCost[i] = cost;
    fuelUsedList[i] = fuelUsed;
    totalCostList[i] = totalCost;
    profitList[i] = profit;
    chargeList[i] = customerCharge;
    timeList[i] = time;
    (*deliveryCount)++;

    printf("\n----- DELIVERY SUMMARY -----\n");
    printf("From: %s  To: %s\n", cities[src], cities[dest]);
    printf("Vehicle: %s\n",vehicle[vehicleType]);
    printf("Weight: %.1f kg\n", weight);
    printf("Minimum Distance: %.1f km\n", D);
    printf("Base Cost: %.1f LKR\n", cost);
    printf("Fuel Used: %.1f L\n", fuelUsed);
    printf("Fuel Cost: %.1f LKR\n", fuelCost);
    printf("Operational Cost: %.1f LKR\n", totalCost);
    printf("Profit: %.1f LKR\n", profit);
    printf("Customer Charge: %.1f LKR\n", customerCharge);
    printf("Estimated Time: %.1f hrs\n", time);
    printf("----------------------------\n");
}
void leastDistanceRoute(char cities[][30], float distance[][MAX_CITIES], int cityCount)
{
    int source, destination;

    printf("Enter source index: ");
    scanf("%d", &source);
    printf("Enter destination index: ");
    scanf("%d", &destination);
    if (source == destination)
    {
        printf("Source and destination cannot be same.\n");

    }

    if (distance[source][destination] == 0)
    {
        printf("No direct distance  between recorded cities.\n");

    }

    float min = distance[source][destination];
    int mid= -1;


    for (int i = 0; i < cityCount; i++)
    {
        if (i == source || i == destination)
        {


            if (distance[source][i] > 0 && distance[i][destination] > 0)
            {
                float total = distance[source][i] + distance[i][destination];
                if (total < min)
                {
                    min = total;
                    mid= i;
                }
            }
        }
    }


    if (mid == -1)
    {
        printf("%s -> %s\n", cities[source], cities[destination]);
    }
    else
    {
        printf("%s -> %s -> %s\n", cities[source], cities[mid], cities[destination]);
    }
    printf("Minimum distance: %.2f km\n", min);
}

void report(float distance[][MAX_CITIES], int deliverySource[], int deliveryDestination[], float customerCharge[], float profit[], float time[], int deliveryCount)
{
    float totalDistance = 0, totalRevenue = 0, totalProfit = 0, totalTime = 0;
    for (int i = 0; i < deliveryCount; i++)
    {
        totalDistance += distance[deliverySource[i]][deliveryDestination[i]];
        totalRevenue += chargeList[i];
        totalProfit += profitList[i];
        totalTime += timeList[i];
    }

    printf("\n===== PERFORMANCE REPORT =====\n");
    printf("Total Deliveries: %d\n", deliveryCount);
    printf("Total Distance: %.2f km\n", totalDistance);
    float avgTime;
    if (deliveryCount != 0)
        avgTime = totalTime / deliveryCount;
    else
        avgTime = 0;

    printf("Average Time: %.2f hrs\n", avgTime);

    printf("Total Revenue: %.2f LKR\n", totalRevenue);
    printf("Total Profit: %.2f LKR\n", totalProfit);

    printf("================================\n");
}

int main()
{
    int choice;
    do
    {
        printf("\n------ LOGISTICS MANAGEMENT MENU ------\n");
        printf("1. Add City\n");
        printf("2. Manage Cities\n");
        printf("3. Edit Distance\n");
        printf("4. Display Distance Table\n");
        printf("5. Calculate Delivery\n");
        printf("6. Least Distance Route\n");
        printf("7. Show Report\n");
        printf("8. Rename City\n");
        printf("9. Remove City\n");
        printf("0. Exit\n");
        printf("----------------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

