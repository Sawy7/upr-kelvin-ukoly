#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#define _USE_MATH_DEFINES

typedef struct
{
    int obyvatele;
    float lat;
    float lon;
} Mesto;

int main(int argc, char **argv)
{
    //nacitani parametru
    char* input = argv[1];
    //printf("%s\n", input);
    char* mesto = argv[2];
    //printf("%s\n", mesto);
    float vzdalenost = atof(argv[3]);
    //printf("%f\n", vzdalenost);
    char* output = argv[4];
    //printf("%s\n", output);

    //Ostrava
    float lat1 = 49.8349139;
    float lon1 = 18.2820084;
    float lat1_rad = (lat1/180)*M_PI;
    float lon1_rad = (lon1/180)*M_PI;
    //Brno
    float lat2 = 49.1922443;
    float lon2 = 16.6113382;
    float lat2_rad = (lat2/180)*M_PI;
    float lon2_rad = (lon2/180)*M_PI;

    float a = pow(sin((lat2_rad-lat1_rad)/2),2) + cos(lat1_rad) * cos(lat2_rad) * pow(sin((lon2_rad-lon1_rad)/2),2);
    float distance = 6371 * 2 * atan2(sqrt(a),sqrt(1-a));

    //printf("a: %f\n", a);
    //printf("distance: %f\n", distance);

    char reading[100];
    Mesto* center = (Mesto*) malloc(sizeof(Mesto));
    char* city_name;
    FILE * file = fopen(input,"r");
    while (fscanf(file, "%s", reading) != EOF)
    {
        //fscanf(file, "%s", reading);
        /*
        printf("city_name: %s\n", strtok(reading, ";"));
        printf("center_obyvatele: %s\n", strtok(NULL, ";"));
        printf("center_lat: %s\n", strtok(NULL, ";"));
        printf("center_lon: %s\n\n", strtok(NULL, ";"));
        */

        city_name = strtok(reading, ";");
        if (strcmp(mesto, city_name) == 0)
        {
            city_name = city_name;
            center->obyvatele = atoi(strtok(NULL, ";"));
            center->lat = atof(strtok(NULL, ";"));
            center->lon = atof(strtok(NULL, ";"));
            center->lat = (center->lat/180)*M_PI;
            center->lon = (center->lon/180)*M_PI;
            //printf("city_name: %s\n", city_name);
            //printf("center_obyvatele: %d\n", center->obyvatele);
            //printf("center_lat: %f\n", center->lat);
            //printf("center_lon: %f\n", center->lon);
        }
    }
    fclose(file);

    int populationsum = 0;
    FILE * file2 = fopen(input,"r");
    FILE * fileo = fopen(output,"w");
    Mesto* zapisovane = (Mesto*) malloc(sizeof(Mesto));
    while (fscanf(file2, "%s", reading) != EOF)
    {
        city_name = strtok(reading, ";");
        zapisovane->obyvatele = atoi(strtok(NULL, ";"));
        zapisovane->lat = atof(strtok(NULL, ";"));
        zapisovane->lon = atof(strtok(NULL, ";"));
        zapisovane->lat = (zapisovane->lat/180)*M_PI;
        zapisovane->lon = (zapisovane->lon/180)*M_PI;

        float a = pow(sin(((zapisovane->lat) - (center->lat))/2),2) + cos(center->lat) * cos(zapisovane->lat) * pow(sin(((zapisovane->lon) - (center->lon))/2),2);
        distance = 6371 * 2 * atan2(sqrt(a),sqrt(1-a));

        //printf("%s\n", city_name);
        //printf("obyvatele: %d\n", zapisovane->obyvatele);
        //printf("lat: %f\n", zapisovane->lat);
        //printf("lon: %f\n", zapisovane->lon);
        //printf("distance: %f\n", distance);

        if (distance <= vzdalenost)
        {
            //printf("%s, %d, %f\n", city_name, zapisovane->obyvatele, distance);
            fprintf(fileo, "%s %d %.2f km\n", city_name, zapisovane->obyvatele, distance);
            populationsum += zapisovane->obyvatele;
        }
    }

    fclose(file2);    
    fclose(fileo);
    free(center);
    free(zapisovane);

    printf("total population: %d\n", populationsum);

    return 0;
}