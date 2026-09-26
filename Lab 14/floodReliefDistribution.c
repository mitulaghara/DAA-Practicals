#include <stdio.h>
#include <string.h>

#define MAX_NODES 10
#define INF 999999

#define WEATHER_CLEAR 1.0f
#define WEATHER_RAIN  1.3f
#define WEATHER_STORM 1.8f

#define ROAD_NORMAL  0
#define ROAD_DAMAGED 1
#define ROAD_BLOCKED 2

typedef struct {
    int id;
    char name[30];
    int severity;
    int beneficiaries;
    int req_food, req_med, req_boats, req_personnel;
    int alloc_food, alloc_med, alloc_boats, alloc_personnel;
    float priority_score;
    int min_cost, parent, is_reachable;
} District;

typedef struct {
    int food, med, boats, personnel;
} Warehouse;

int num_districts = 5;
int base_distance[MAX_NODES][MAX_NODES];
int road_status[MAX_NODES][MAX_NODES];
float weather_factor[MAX_NODES][MAX_NODES];

Warehouse central_warehouse;
District districts[MAX_NODES];

void initializeScenario()
{
    int i, j;

    central_warehouse.food = 10000;
    central_warehouse.med = 2500;
    central_warehouse.boats = 40;
    central_warehouse.personnel = 80;

    districts[0].id = 0;
    strcpy(districts[0].name, "Supply Base (Hub)");
    districts[0].severity = 0;
    districts[0].beneficiaries = 0;

    districts[1].id = 1;
    strcpy(districts[1].name, "District A (North Delta)");
    districts[1].severity = 5;
    districts[1].beneficiaries = 4200;
    districts[1].req_food = 4500;
    districts[1].req_med = 1200;
    districts[1].req_boats = 20;
    districts[1].req_personnel = 35;

    districts[2].id = 2;
    strcpy(districts[2].name, "District B (River Basin)");
    districts[2].severity = 4;
    districts[2].beneficiaries = 3100;
    districts[2].req_food = 3200;
    districts[2].req_med = 800;
    districts[2].req_boats = 15;
    districts[2].req_personnel = 25;

    districts[3].id = 3;
    strcpy(districts[3].name, "District C (Coastal Belt)");
    districts[3].severity = 3;
    districts[3].beneficiaries = 2400;
    districts[3].req_food = 2500;
    districts[3].req_med = 500;
    districts[3].req_boats = 8;
    districts[3].req_personnel = 15;

    districts[4].id = 4;
    strcpy(districts[4].name, "District D (Upland Hills)");
    districts[4].severity = 2;
    districts[4].beneficiaries = 1200;
    districts[4].req_food = 1200;
    districts[4].req_med = 300;
    districts[4].req_boats = 2;
    districts[4].req_personnel = 10;

    for (i = 0; i < MAX_NODES; i++) {
        for (j = 0; j < MAX_NODES; j++) {
            base_distance[i][j] = (i == j) ? 0 : INF;
            road_status[i][j] = ROAD_NORMAL;
            weather_factor[i][j] = WEATHER_CLEAR;
        }
    }

    base_distance[0][1] = base_distance[1][0] = 25;
    base_distance[0][2] = base_distance[2][0] = 40;
    base_distance[1][2] = base_distance[2][1] = 15;
    base_distance[1][3] = base_distance[3][1] = 30;
    base_distance[2][4] = base_distance[4][2] = 35;
    base_distance[3][4] = base_distance[4][3] = 20;

    weather_factor[0][1] = weather_factor[1][0] = WEATHER_STORM;
    weather_factor[0][2] = weather_factor[2][0] = WEATHER_RAIN;
    weather_factor[1][2] = weather_factor[2][1] = WEATHER_RAIN;

    road_status[0][1] = road_status[1][0] = ROAD_DAMAGED;
}

void computeShortestPaths()
{
    int dist[MAX_NODES], visited[MAX_NODES] = {0};
    int i, step, u, v;

    for (i = 0; i < num_districts; i++) {
        dist[i] = INF;
        districts[i].parent = -1;
    }
    dist[0] = 0;

    for (step = 0; step < num_districts - 1; step++) {
        int min = INF;
        u = -1;
        for (i = 0; i < num_districts; i++) {
            if (!visited[i] && dist[i] < min) {
                min = dist[i];
                u = i;
            }
        }

        if (u == -1) break;
        visited[u] = 1;

        for (v = 0; v < num_districts; v++) {
            if (!visited[v] && base_distance[u][v] != INF && base_distance[u][v] > 0) {
                if (road_status[u][v] == ROAD_BLOCKED) continue;

                float mult = (road_status[u][v] == ROAD_DAMAGED) ? 2.0f : 1.0f;
                int cost = dist[u] + (int)(base_distance[u][v] * mult * weather_factor[u][v]);

                if (cost < dist[v]) {
                    dist[v] = cost;
                    districts[v].parent = u;
                }
            }
        }
    }

    for (i = 1; i < num_districts; i++) {
        districts[i].min_cost = dist[i];
        districts[i].is_reachable = (dist[i] < INF);
    }
}

void printPath(int current)
{
    if (districts[current].parent == -1) {
        printf("%s", districts[current].name);
        return;
    }
    printPath(districts[current].parent);
    printf(" -> %s", districts[current].name);
}

int allocate(int req, int *rem)
{
    int a = (*rem >= req) ? req : *rem;
    *rem -= a;
    return a;
}

void allocateResources()
{
    int i, j, order[MAX_NODES];
    int rem_food = central_warehouse.food;
    int rem_med = central_warehouse.med;
    int rem_boats = central_warehouse.boats;
    int rem_personnel = central_warehouse.personnel;

    for (i = 1; i < num_districts; i++) {
        districts[i].alloc_food = districts[i].alloc_med = districts[i].alloc_boats = districts[i].alloc_personnel = 0;
        order[i - 1] = i;
        if (districts[i].is_reachable && districts[i].min_cost > 0) {
            districts[i].priority_score = ((float)districts[i].severity * 1000.0f + districts[i].beneficiaries) / districts[i].min_cost;
        } else {
            districts[i].priority_score = 0.0f;
        }
    }

    for (i = 0; i < num_districts - 2; i++) {
        for (j = i + 1; j < num_districts - 1; j++) {
            if (districts[order[i]].priority_score < districts[order[j]].priority_score) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    for (i = 0; i < num_districts - 1; i++) {
        int idx = order[i];
        if (!districts[idx].is_reachable) continue;

        districts[idx].alloc_food = allocate(districts[idx].req_food, &rem_food);
        districts[idx].alloc_med = allocate(districts[idx].req_med, &rem_med);
        districts[idx].alloc_boats = allocate(districts[idx].req_boats, &rem_boats);
        districts[idx].alloc_personnel = allocate(districts[idx].req_personnel, &rem_personnel);
    }
}

void displayDistributionPlan()
{
    int i, total_cost = 0;

    printf("\n=== FLOOD RELIEF DISTRIBUTION PLAN ===\n");
    printf("\nWarehouse Stock: Food=%d, Med=%d, Boats=%d, Staff=%d\n\n",
           central_warehouse.food, central_warehouse.med, central_warehouse.boats, central_warehouse.personnel);

    printf("Routes:\n");
    for (i = 1; i < num_districts; i++) {
        printf("District %d (%s): ", districts[i].id, districts[i].name);
        if (districts[i].is_reachable) {
            printf("Cost=%d | Path: ", districts[i].min_cost);
            printPath(i);
            printf("\n");
            total_cost += districts[i].min_cost;
        } else {
            printf("ISOLATED (No route)\n");
        }
    }

    printf("\nResource Allocation:\n");
    printf("%-25s | Priority | Food(Req/Alloc) | Med(Req/Alloc) | Boats(Req/Alloc) | Staff(Req/Alloc)\n", "District");
    printf("-------------------------------------------------------------------------------------------------\n");
    for (i = 1; i < num_districts; i++) {
        printf("%-25s | %8.2f | %5d / %-5d   | %4d / %-4d  | %3d / %-3d      | %3d / %-3d\n",
               districts[i].name, districts[i].priority_score,
               districts[i].req_food, districts[i].alloc_food,
               districts[i].req_med, districts[i].alloc_med,
               districts[i].req_boats, districts[i].alloc_boats,
               districts[i].req_personnel, districts[i].alloc_personnel);
    }
    printf("-------------------------------------------------------------------------------------------------\n");
    printf("Total Transport Cost = %d\n", total_cost);
}

void adaptToChangingConditions()
{
    int choice, u, v, status, weather_code;

    printf("\n1. Update Road Condition\n2. Update Weather Condition\nEnter choice: ");
    if (scanf("%d", &choice) != 1) return;

    if (choice == 1) {
        printf("Enter endpoints (u v) [0 to 4]: ");
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < num_districts && v >= 0 && v < num_districts) {
            printf("Enter Status (0: Normal, 1: Damaged, 2: Blocked): ");
            scanf("%d", &status);
            road_status[u][v] = road_status[v][u] = status;
        }
    } else if (choice == 2) {
        printf("Enter endpoints (u v) [0 to 4]: ");
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < num_districts && v >= 0 && v < num_districts) {
            printf("Enter Weather (1: Clear, 2: Rain, 3: Storm): ");
            scanf("%d", &weather_code);
            float f = (weather_code == 1) ? WEATHER_CLEAR : (weather_code == 2) ? WEATHER_RAIN : WEATHER_STORM;
            weather_factor[u][v] = weather_factor[v][u] = f;
        }
    }

    computeShortestPaths();
    allocateResources();
    displayDistributionPlan();
}

int main()
{
    int choice;

    initializeScenario();
    computeShortestPaths();
    allocateResources();

    while (1) {
        printf("\n1. Display Plan\n2. Update Condition\n3. Reset\n4. Exit\nEnter choice: ");
        if (scanf("%d", &choice) != 1) break;

        if (choice == 1) {
            displayDistributionPlan();
        } else if (choice == 2) {
            adaptToChangingConditions();
        } else if (choice == 3) {
            initializeScenario();
            computeShortestPaths();
            allocateResources();
            displayDistributionPlan();
        } else if (choice == 4) {
            break;
        }
    }

    return 0;
}
