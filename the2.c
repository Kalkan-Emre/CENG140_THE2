#include <stdlib.h>
#include <stdio.h>

#define n_sector 3

/* Fill in the functions and define helper functions if you need to */

float*** create_sector_times(unsigned int* n_drivers, unsigned int* n_laps){    

    float*** drivers;
    int i,j,k;
    int size_of_laps,size_of_sectors;
    
    scanf("%u %u",n_drivers,n_laps);

    size_of_laps = sizeof(float*) * (*n_laps);   /*Deteremines memory allocation sizes*/
    size_of_sectors = sizeof(float)* n_sector;

    drivers = (float***) malloc(sizeof(float**) * *n_drivers);

    for (i=0; i < *n_drivers; i++)
    {
        drivers[i] = (float**) malloc(size_of_laps);
        for (j=0; j < *n_laps; j++)
        {
            drivers[i][j] = (float*) malloc(size_of_sectors);
            for (k=0; k < n_sector; k++) 
            {
                scanf(" %f",&drivers[i][j][k]);   /*Fills the 3-D array with stdi*/
            }
        }
    }
               
    return drivers;
}


unsigned int** create_positions(unsigned int* p_drivers, unsigned int* n_races){ 

    unsigned int** drivers_r;
    int i,j;
    int size_of_races;

    scanf("%u %u",p_drivers,n_races);

    size_of_races = sizeof(unsigned int) * (*n_races);  /*Deteremines memory allocation sizes*/

    drivers_r = (unsigned int**)malloc(sizeof(unsigned int*) * *p_drivers);

    for (i = 0; i < *p_drivers; i++)
    {
        drivers_r[i] = (unsigned int*) malloc(size_of_races);
        for (j = 0; j < *n_races; j++)
        {
            scanf(" %u",&drivers_r[i][j]);  /*Fills the 2-D array with stdi*/
        }
    }
    return drivers_r;
}


float** calculate_lap_times(float*** sector_times, unsigned int n_drivers, unsigned int n_laps){

    float** lap_times;
    int i,j,k;
    float temp;

    lap_times = (float**)malloc(sizeof(float*) * n_drivers);

    for (i = 0; i < n_drivers; i++)
    {
        lap_times[i] = (float*) malloc(sizeof(float) * n_laps);
    }

    for(i=0;i < n_drivers;i++)
    {
        for(j=0;j < n_laps;j++)
        {
            temp = 0;
            for(k=0;k < n_sector;k++)
            {
                temp+=sector_times[i][j][k];
            }
            lap_times[i][j]=temp;
        }
    }
    return lap_times;
}


unsigned int find_fastest_lap(float** lap_times, unsigned int n_drivers, unsigned int n_laps){  

    int i,j,k;
    float fastest_lap;
    unsigned int fastest_driver;

    fastest_lap = lap_times[0][0];
    fastest_driver = 0;

    for(i=0;i < n_drivers;i++)
    {
        for(j=0;j < n_laps;j++)
        {
            if(lap_times[i][j]<fastest_lap)
            {
                fastest_lap = lap_times[i][j];
                fastest_driver = i;
            }
        }
    }
    return fastest_driver;
}


unsigned int find_driver_fastest_lap(float** sector_times_of_driver, unsigned int n_laps){

    unsigned int fastest_lap=0;
    float shortest_time;
    float temp;
    int i,j;

    shortest_time = sector_times_of_driver[0][0] + sector_times_of_driver[0][1] + sector_times_of_driver[0][2];
    
    for(i=0;i<n_laps;i++)
    {
        temp=0;
        for(j=0;j<n_sector;j++)
        {
            temp+=sector_times_of_driver[i][j];
        }
        if(temp<shortest_time)
        {
            shortest_time = temp;
            fastest_lap = i; 
        }
    }
    return fastest_lap;
}


float* selection_sort(float* arr, unsigned int len, char ord){

    float* copy_arr = malloc(sizeof(float)*len);
    float min;
    float temp;
    int i,j,k;
    int min_index=0;


    for(i=0;i<len;i++)
    {
        copy_arr[i]=arr[i];
    }

    for(i=0;i<len;i++)
    {
        min = copy_arr[i];
        min_index = i;
        for(j=i;j<len;j++)
        {
            if(copy_arr[j]<min)
            {
                min=copy_arr[j];
                min_index=j;
            }
        }
        temp = copy_arr[i];
        copy_arr[i] = copy_arr[min_index];
        copy_arr[min_index] = temp;
    }

    if(ord=='D')
    {
        for(i=0;i<(len/2);i++)
        {
            temp = copy_arr[i];
            copy_arr[i] = copy_arr[len-1-i];
            copy_arr[len-1-i] = temp;
        }
    }

    return copy_arr;
}


unsigned int* find_finishing_positions(float** lap_times, unsigned int n_drivers, unsigned int n_laps){
    unsigned int* ordered_positions;
    float** positions_and_ids;
    int i,j;
    float temp;
    int temp_positions;
    float min;
    int min_index=0;

    ordered_positions = (unsigned int*) malloc(sizeof(unsigned int)*n_drivers);

    positions_and_ids = (float**) malloc(sizeof(float*)*n_drivers);

    for (i = 0; i < n_drivers; i++)
    {
        positions_and_ids[i] = (float*) malloc(sizeof(float)*2);
        positions_and_ids[i][0]=i;
        positions_and_ids[i][1]=0;
    }

    for(i=0;i < n_drivers;i++)
    {   
        temp=0;
        for(j=0;j < n_laps;j++)
        {
            temp+=lap_times[i][j];
        }
        positions_and_ids[i][1]=temp;
    }

    for(i=0;i<n_drivers;i++)
    {
        min = positions_and_ids[i][1];
        min_index = i;
        for(j=i;j<n_drivers;j++)
        {
            if(positions_and_ids[j][1]<min)
            {
                min=positions_and_ids[j][1];
                min_index=j;
            }
        }
        temp = positions_and_ids[i][1];
        positions_and_ids[i][1] = positions_and_ids[min_index][1];
        positions_and_ids[min_index][1] = temp;

        temp_positions = positions_and_ids[i][0];
        positions_and_ids[i][0] = positions_and_ids[min_index][0];
        positions_and_ids[min_index][0] = temp_positions;
    }

    for(i=0;i<n_drivers;i++)
    {
        ordered_positions[i]=positions_and_ids[i][0];
    }

    return ordered_positions;
}


float* find_time_diff(float** lap_times, unsigned int n_drivers, unsigned int n_laps, unsigned int driver1,
    unsigned int driver2){

    float* time_diff;
    int i;
    float temp_diff=0.0;

    time_diff = (float*) malloc(sizeof(float)*n_laps);

    for(i=0;i<n_laps;i++)
    {
        temp_diff += (lap_times[driver1][i] - lap_times[driver2][i]);
        time_diff[i] = temp_diff;
    }

    return time_diff;
}


unsigned int* calculate_total_points(unsigned int** positions, unsigned int p_drivers, unsigned int n_races){

    unsigned int* total_points;
    unsigned int* score_range;
    unsigned int total_point=0;
    unsigned int place;
    int i,j;

    total_points = (unsigned int*) malloc(sizeof(unsigned int)*p_drivers);

    score_range = (unsigned int*) malloc(sizeof(unsigned int)*p_drivers);
    for(i=0; i<p_drivers; i++)
    {
        scanf("%u",&score_range[i]);
    }

    for(i=0;i<p_drivers;i++)
    {
        for(j=0;j<n_races;j++)
        {
            place = positions[i][j];
            total_point+=(score_range[place-1]);
        }
        total_points[i] = total_point;
        total_point = 0;
    }

    return total_points;
}


unsigned int find_season_ranking(unsigned int* total_points, unsigned int p_drivers, unsigned int id){

    unsigned int** rankings_and_ids;
    unsigned int temp;
    unsigned int min;
    unsigned int check_equality;
    unsigned int temp_positions;
    int i,j;
    int min_index=0;


    rankings_and_ids = (unsigned int**) malloc(sizeof(unsigned int*)*p_drivers);
    for (i = 0; i < p_drivers; i++)
    {
        rankings_and_ids[i] = (unsigned int*) malloc(sizeof(unsigned int)*2);
        rankings_and_ids[i][0]=i;
        rankings_and_ids[i][1]=total_points[i];
    }

    for(i=0;i<p_drivers;i++)
    {
        min = rankings_and_ids[i][1];
        min_index = i;
        for(j=i;j<p_drivers;j++)
        {
            if(rankings_and_ids[j][1]<min)
            {
                min=rankings_and_ids[j][1];
                min_index=j;
            }
        }
        temp = rankings_and_ids[i][1];
        rankings_and_ids[i][1] = rankings_and_ids[min_index][1];
        rankings_and_ids[min_index][1] = temp;

        temp_positions = rankings_and_ids[i][0];
        rankings_and_ids[i][0] = rankings_and_ids[min_index][0];
        rankings_and_ids[min_index][0] = temp_positions;
    }

    for(i=0;i<p_drivers;i++)
    {
        check_equality = rankings_and_ids[i][1];
        for(j=i;j<p_drivers;j++)
        {
            if(rankings_and_ids[j][1]==check_equality)
            {
                if(rankings_and_ids[i][0]<rankings_and_ids[j][0])
                {
                    temp_positions = rankings_and_ids[i][0];
                    rankings_and_ids[i][0] = rankings_and_ids[j][0];
                    rankings_and_ids[j][0] = temp_positions;
                }
            }
        }
    }

    for(i=0;i<p_drivers;i++)
    {
        if(rankings_and_ids[i][0]==id)
        {
            return p_drivers - i;
        }
    }
}
