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
