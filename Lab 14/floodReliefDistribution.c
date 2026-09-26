#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 10
#define INF 999999

/* --- Weather Forecast Multipliers --- */
#define WEATHER_CLEAR 1.0f
#define WEATHER_RAIN  1.3f
#define WEATHER_STORM 1.8f

/* --- Road Status --- */
#define ROAD_NORMAL  0
#define ROAD_DAMAGED 1
#define ROAD_BLOCKED 2

typedef struct {
    int id;
    char name[30];
    int severity;          /* Scale: 1 (Low) to 5 (Critical) */
    int beneficiaries;     /* Number of affected people */
    int req_food;          /* Food packets required */
    int req_med;           /* Medical kits required */
    int req_boats;         /* Rescue boats required */
    int req_personnel;     /* Medical personnel required */

    int alloc_food;
    int alloc_med;
    int alloc_boats;
    int alloc_personnel;

    float priority_score;
    int min_cost;
    int parent;
    int is_reachable;
} District;

typedef struct {
    int food;
    int med;
    int boats;
    int personnel;
} Warehouse;

/* Road Network graph */
int num_districts = 5;      /* 1 warehouse (index 0) + 4 affected districts (1 to 4) */
int base_distance[MAX_NODES][MAX_NODES];
int road_status[MAX_NODES][MAX_NODES];
float weather_factor[MAX_NODES][MAX_NODES];

Warehouse central_warehouse;
District districts[MAX_NODES];

/* Initialize default sample data representing severe flood scenario */
void initializeScenario()
{
    int i, j;

    /* Central Warehouse Capacity */
    central_warehouse.food = 10000;       /* Food packets */
    central_warehouse.med = 2500;         /* Medical kits */
    central_warehouse.boats = 40;         /* Rescue boats */
    central_warehouse.personnel = 80;     /* Doctors / Paramedics */

    /* Node 0: Central Supply Base / Warehouse */
    districts[0].id = 0;
    strcpy(districts[0].name, "Supply Base (Hub)");
    districts[0].severity = 0;
    districts[0].beneficiaries = 0;

    /* Affected Districts */
    districts[1].id = 1;
    strcpy(districts[1].name, "District A (North Delta)");
    districts[1].severity = 5;           /* Critical */
    districts[1].beneficiaries = 4200;
    districts[1].req_food = 4500;
    districts[1].req_med = 1200;
    districts[1].req_boats = 20;
    districts[1].req_personnel = 35;

    districts[2].id = 2;
    strcpy(districts[2].name, "District B (River Basin)");
    districts[2].severity = 4;           /* High */
    districts[2].beneficiaries = 3100;
    districts[2].req_food = 3200;
    districts[2].req_med = 800;
    districts[2].req_boats = 15;
    districts[2].req_personnel = 25;

    districts[3].id = 3;
    strcpy(districts[3].name, "District C (Coastal Belt)");
    districts[3].severity = 3;           /* Moderate */
    districts[3].beneficiaries = 2400;
    districts[3].req_food = 2500;
    districts[3].req_med = 500;
    districts[3].req_boats = 8;
    districts[3].req_personnel = 15;

    districts[4].id = 4;
    strcpy(districts[4].name, "District D (Upland Hills)");
    districts[4].severity = 2;           /* Low */
    districts[4].beneficiaries = 1200;
    districts[4].req_food = 1200;
    districts[4].req_med = 300;
    districts[4].req_boats = 2;
    districts[4].req_personnel = 10;

    /* Initialize Road Distances (0 if no direct road) */
    for (i = 0; i < MAX_NODES; i++) {
        for (j = 0; j < MAX_NODES; j++) {
            base_distance[i][j] = (i == j) ? 0 : INF;
            road_status[i][j] = ROAD_NORMAL;
            weather_factor[i][j] = WEATHER_CLEAR;
        }
    }

    /* Road Connections and base distance (in km) */
    base_distance[0][1] = 25; base_distance[1][0] = 25;
    base_distance[0][2] = 40; base_distance[2][0] = 40;
    base_distance[1][2] = 15; base_distance[2][1] = 15;
    base_distance[1][3] = 30; base_distance[3][1] = 30;
    base_distance[2][4] = 35; base_distance[4][2] = 35;
    base_distance[3][4] = 20; base_distance[4][3] = 20;

    /* Weather forecast conditions */
    weather_factor[0][1] = WEATHER_STORM; weather_factor[1][0] = WEATHER_STORM; /* Heavy storm on main north route */
    weather_factor[0][2] = WEATHER_RAIN;  weather_factor[2][0] = WEATHER_RAIN;
    weather_factor[1][2] = WEATHER_RAIN;  weather_factor[2][1] = WEATHER_RAIN;
    weather_factor[1][3] = WEATHER_CLEAR; weather_factor[3][1] = WEATHER_CLEAR;
    weather_factor[2][4] = WEATHER_CLEAR; weather_factor[4][2] = WEATHER_CLEAR;
    weather_factor[3][4] = WEATHER_CLEAR; weather_factor[4][3] = WEATHER_CLEAR;

    /* Road Conditions: Direct highway 0->1 is submerged / damaged */
    road_status[0][1] = ROAD_DAMAGED;
    road_status[1][0] = ROAD_DAMAGED;
}

/* Dijkstra's Algorithm taking into account Damaged Roads & Weather Forecast */
void computeShortestPaths()
{
    int dist[MAX_NODES];
    int visited[MAX_NODES];
    int i, step, u, v;

    for (i = 0; i < num_districts; i++) {
        dist[i] = INF;
        visited[i] = 0;
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
                /* Handle Damaged / Blocked Roads */
                if (road_status[u][v] == ROAD_BLOCKED) {
                    continue; /* Route is completely blocked */
                }

                /* If road is damaged, transport cost/time increases by 2.0x */
                float road_multiplier = (road_status[u][v] == ROAD_DAMAGED) ? 2.0f : 1.0f;
                float effective_cost = base_distance[u][v] * road_multiplier * weather_factor[u][v];

                if (dist[u] + (int)effective_cost < dist[v]) {
                    dist[v] = dist[u] + (int)effective_cost;
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

/* Print Path from Warehouse to District */
void printPath(int current)
{
    if (districts[current].parent == -1) {
        printf("%s", districts[current].name);
        return;
    }
    printPath(districts[current].parent);
    printf(" -> %s", districts[current].name);
}

/* Calculate Priority Metric & Allocate Resources within Warehouse Capacity */
void allocateResources()
{
    int i, j;
    int order[MAX_NODES];
    int rem_food = central_warehouse.food;
    int rem_med = central_warehouse.med;
    int rem_boats = central_warehouse.boats;
    int rem_personnel = central_warehouse.personnel;

    /* Reset allocations */
    for (i = 1; i < num_districts; i++) {
        districts[i].alloc_food = 0;
        districts[i].alloc_med = 0;
        districts[i].alloc_boats = 0;
        districts[i].alloc_personnel = 0;
        order[i - 1] = i;

        /* Priority Score formula:
         * Prioritize Severity and Beneficiaries, inversely proportional to cost
         */
        if (districts[i].is_reachable && districts[i].min_cost > 0) {
            districts[i].priority_score =
                ((float)districts[i].severity * 1000.0f + (float)districts[i].beneficiaries)
                / (float)districts[i].min_cost;
        } else {
            districts[i].priority_score = 0.0f;
        }
    }

    /* Sort districts in descending order of priority score (Greedy Strategy) */
    for (i = 0; i < num_districts - 2; i++) {
        for (j = i + 1; j < num_districts - 1; j++) {
            if (districts[order[i]].priority_score < districts[order[j]].priority_score) {
                int temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }

    /* Allocate supplies respecting warehouse capacity and reachable status */
    for (i = 0; i < num_districts - 1; i++) {
        int idx = order[i];

        if (!districts[idx].is_reachable) {
            continue;
        }

        /* Food allocation */
        if (rem_food >= districts[idx].req_food) {
            districts[idx].alloc_food = districts[idx].req_food;
            rem_food -= districts[idx].req_food;
        } else {
            districts[idx].alloc_food = rem_food;
            rem_food = 0;
        }

        /* Medicine allocation */
        if (rem_med >= districts[idx].req_med) {
            districts[idx].alloc_med = districts[idx].req_med;
            rem_med -= districts[idx].req_med;
        } else {
            districts[idx].alloc_med = rem_med;
            rem_med = 0;
        }

        /* Rescue Boats allocation */
        if (rem_boats >= districts[idx].req_boats) {
            districts[idx].alloc_boats = districts[idx].req_boats;
            rem_boats -= districts[idx].req_boats;
        } else {
            districts[idx].alloc_boats = rem_boats;
            rem_boats = 0;
        }

        /* Personnel allocation */
        if (rem_personnel >= districts[idx].req_personnel) {
            districts[idx].alloc_personnel = districts[idx].req_personnel;
            rem_personnel -= districts[idx].req_personnel;
        } else {
            districts[idx].alloc_personnel = rem_personnel;
            rem_personnel = 0;
        }
    }
}

/* Display Complete Results & Allocation Plan */
void displayDistributionPlan()
{
    int i;
    int total_beneficiaries = 0;
    int served_beneficiaries = 0;
    int total_cost = 0;

    printf("\n========================================================================================\n");
    printf("                GOVERNMENT FLOOD RELIEF RESOURCE ALLOCATION PLAN                        \n");
    printf("========================================================================================\n");

    printf("\n[1] WAREHOUSE INITIAL INVENTORY:\n");
    printf("    * Food Packets     : %d\n", central_warehouse.food);
    printf("    * Medicine Kits    : %d\n", central_warehouse.med);
    printf("    * Rescue Boats     : %d\n", central_warehouse.boats);
    printf("    * Medical Personnel: %d\n", central_warehouse.personnel);

    printf("\n[2] ROUTE & ACCESSIBILITY ANALYSIS (Handling Weather & Damaged Roads):\n");
    printf("----------------------------------------------------------------------------------------\n");
    printf("%-4s | %-25s | %-8s | %-12s | %-32s\n", "ID", "District", "Cost/Dist", "Status", "Optimized Path");
    printf("----------------------------------------------------------------------------------------\n");

    for (i = 1; i < num_districts; i++) {
        printf("%-4d | %-25s | ", districts[i].id, districts[i].name);
        if (districts[i].is_reachable) {
            printf("%-8d | %-12s | ", districts[i].min_cost, "Reachable");
            printPath(i);
            printf("\n");
            total_cost += districts[i].min_cost;
        } else {
            printf("%-8s | %-12s | %-32s\n", "INF", "ISOLATED", "No safe route (Blocked roads)");
        }
    }

    printf("\n[3] RESOURCE ALLOCATION BY PRIORITY (Severity & Beneficiaries vs Cost):\n");
    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("%-20s | %-8s | %-12s | %-8s | %-16s | %-16s | %-12s | %-10s\n",
           "District", "Severity", "Beneficiaries", "Priority", "Food (Req/Alloc)", "Med (Req/Alloc)", "Boats (R/A)", "Staff(R/A)");
    printf("---------------------------------------------------------------------------------------------------------\n");

    for (i = 1; i < num_districts; i++) {
        total_beneficiaries += districts[i].beneficiaries;
        if (districts[i].is_reachable && districts[i].alloc_food > 0) {
            served_beneficiaries += districts[i].beneficiaries;
        }

        char food_str[20], med_str[20], boat_str[20], pers_str[20];
        sprintf(food_str, "%d / %d", districts[i].req_food, districts[i].alloc_food);
        sprintf(med_str, "%d / %d", districts[i].req_med, districts[i].alloc_med);
        sprintf(boat_str, "%d / %d", districts[i].req_boats, districts[i].alloc_boats);
        sprintf(pers_str, "%d / %d", districts[i].req_personnel, districts[i].alloc_personnel);

        printf("%-20s | %-8d | %-12d | %-8.2f | %-16s | %-16s | %-12s | %-10s\n",
               districts[i].name,
               districts[i].severity,
               districts[i].beneficiaries,
               districts[i].priority_score,
               food_str, med_str, boat_str, pers_str);
    }

    printf("---------------------------------------------------------------------------------------------------------\n");
    printf("  Summary Metrics:\n");
    printf("  * Total Beneficiaries Targeted : %d / %d (%.2f%%)\n",
           served_beneficiaries, total_beneficiaries,
           (total_beneficiaries > 0) ? ((float)served_beneficiaries / total_beneficiaries) * 100.0f : 0.0f);
    printf("  * Cumulative Transportation Cost: %d\n", total_cost);
    printf("========================================================================================\n");
}

/* Adapt to Continuously Changing Information */
void adaptToChangingConditions()
{
    int choice;
    int u, v, status, weather_code;

    printf("\n--- DYNAMIC REAL-TIME UPDATE SIMULATION ---\n");
    printf("1. Update Road Condition (Clear / Damaged / Flooded & Blocked)\n");
    printf("2. Update Weather Forecast on Road Corridor\n");
    printf("Enter choice (1 or 2): ");
    if (scanf("%d", &choice) != 1) return;

    if (choice == 1) {
        printf("Enter Road Endpoints (u v) [0=Supply Hub, 1=Dist A, 2=Dist B, 3=Dist C, 4=Dist D]: ");
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < num_districts && v >= 0 && v < num_districts) {
            printf("Enter Status (0: Normal, 1: Damaged/Waterlogged, 2: Completely Blocked): ");
            scanf("%d", &status);
            road_status[u][v] = status;
            road_status[v][u] = status;
            printf(">> Road condition between %d and %d updated!\n", u, v);
        } else {
            printf("Invalid nodes!\n");
            return;
        }
    } else if (choice == 2) {
        printf("Enter Road Endpoints (u v): ");
        scanf("%d %d", &u, &v);
        if (u >= 0 && u < num_districts && v >= 0 && v < num_districts) {
            printf("Enter Weather Condition (1: Clear, 2: Heavy Rain, 3: Severe Storm): ");
            scanf("%d", &weather_code);
            if (weather_code == 1) {
                weather_factor[u][v] = WEATHER_CLEAR;
                weather_factor[v][u] = WEATHER_CLEAR;
            } else if (weather_code == 2) {
                weather_factor[u][v] = WEATHER_RAIN;
                weather_factor[v][u] = WEATHER_RAIN;
            } else {
                weather_factor[u][v] = WEATHER_STORM;
                weather_factor[v][u] = WEATHER_STORM;
            }
            printf(">> Weather forecast updated on link (%d, %d)!\n", u, v);
        } else {
            printf("Invalid nodes!\n");
            return;
        }
    }

    printf("\n>> Re-running Dijkstra Routing & Priority Resource Allocation...\n");
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
        printf("\n============================================\n");
        printf("   FLOOD RELIEF DECISION SUPPORT SYSTEM     \n");
        printf("============================================\n");
        printf("1. Display Current Distribution Plan\n");
        printf("2. Adapt to Changing Info (Road/Weather Update)\n");
        printf("3. Reset to Initial Flood Scenario\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1:
                displayDistributionPlan();
                break;
            case 2:
                adaptToChangingConditions();
                break;
            case 3:
                initializeScenario();
                computeShortestPaths();
                allocateResources();
                printf("\n>> Scenario successfully reset to initial disaster parameters.\n");
                displayDistributionPlan();
                break;
            case 4:
                printf("\nExiting Flood Relief Allocation System.\n");
                return 0;
            default:
                printf("\nInvalid selection! Please enter 1-4.\n");
        }
    }

    return 0;
}
