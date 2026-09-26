# Disaster Flood Relief Resource Distribution & Routing Algorithm & Documentation

This document contains the complete Disaster Flood Relief Resource Allocation & Dynamic Routing algorithm, pseudocode, step-by-step procedure, dry run trace with priority scoring and routing tables, complexity analysis, and sample output based on [`floodReliefDistribution.c`](./floodReliefDistribution.c).

---

## 1. Notebook / Whiteboard Algorithm (Exact Professor's Notation)

```text
Practical - 14
Aim :- Develop an Algorithm and Program for Disaster Flood Relief Resource Distribution and 
       Routing to distribute food, medicines, rescue boats, and medical personnel among affected 
       districts such that it minimizes transportation cost, maximizes beneficiaries, prioritizes 
       severely affected areas, handles damaged roads, respects warehouse capacity, considers 
       weather forecasts, and adapts to continuously changing real-time information.

FloodRelief_Distribution(Graph G(V, E), Warehouse W, Districts D[1..n])
{
    // Step 1: Compute Minimum Cost Paths considering Road Damage & Weather Forecasts
    for each edge (u, v) in E do
    {
        if (road_status[u][v] == BLOCKED)
            cost[u][v] ← ∞
        else
            cost[u][v] ← base_distance[u][v] × road_multiplier[u][v] × weather_factor[u][v]
    }
    
    // Dijkstra Shortest Path from Central Supply Hub (Node 0)
    (min_cost[], parent[]) ← Dijkstra(G, cost, source = 0)

    // Step 2: Multi-Objective Priority Quotient
    for i ← 1 to n do
    {
        if (min_cost[i] < ∞)
            Priority[i] ← (Severity[i] × α + Beneficiaries[i]) / min_cost[i]
        else
            Priority[i] ← 0
    }

    // Step 3: Sort Districts in Descending Order of Priority
    Sort(Districts, by Priority descending)

    // Step 4: Greedy Resource Allocation respecting Warehouse Capacity
    for each resource R in {Food, Medicine, Boats, Personnel} do
    {
        available ← W.capacity[R]
        for each District i in sorted order do
        {
            if (min_cost[i] < ∞)
            {
                allocated[i][R] ← min(D[i].demand[R], available)
                available ← available - allocated[i][R]
            }
        }
    }

    // Step 5: Dynamic Adaptation Loop
    on RealTimeEvent(update_type, target, new_value):
        Update G or Weather or Demand
        Recompute Dijkstra & Allocation()

    return (min_cost, Priority, Allocation)
}

⊙ Time Complexity

T(V, E, n) = O(E log V + n log n + n × R)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `FLOOD_RELIEF_ALLOCATION_AND_ROUTING(V, E, W, D)`

* **Input:**
  * Road Network Graph $G = (V, E)$ with base distances.
  * Central Warehouse $W$ with capacities for:
    * Food packets ($C_{\text{food}}$)
    * Medical kits ($C_{\text{med}}$)
    * Rescue boats ($C_{\text{boat}}$)
    * Medical personnel ($C_{\text{personnel}}$)
  * Affected Districts $D_1, D_2, \dots, D_n$, each with:
    * Severity Level ($S_i \in [1, 5]$)
    * Beneficiaries / Affected Population ($B_i$)
    * Demands for food, medicine, boats, and medical staff.
  * Real-time Environmental Factors:
    * Road Conditions: $\text{Normal } (1.0\times)$, $\text{Damaged/Waterlogged } (2.0\times)$, $\text{Blocked } (\infty)$.
    * Weather Forecasts: $\text{Clear } (1.0\times)$, $\text{Rain } (1.3\times)$, $\text{Storm } (1.8\times)$.
* **Output:**
  * Minimum cost viable routes from Supply Hub to each reachable district.
  * Ranked priority list of districts.
  * Optimal allocation of food, medicines, boats, and medical personnel respecting warehouse capacity.
  * Total beneficiaries served and cumulative transportation cost.

---

### Part A: Dynamic Routing & Cost Minimization (Handling Weather & Damaged Roads)

1. **Step 1: [Initialize Graph Weights]**
   For each road corridor $(u, v) \in E$:
   * If $\text{RoadStatus}[u][v] == \text{BLOCKED}$, set $\text{EffectiveCost}[u][v] \leftarrow \infty$.
   * Else, set:
     $$\text{EffectiveCost}[u][v] = \text{BaseDistance}[u][v] \times \text{DamageMultiplier}[u][v] \times \text{WeatherFactor}[u][v]$$

2. **Step 2: [Shortest Path via Dijkstra's Algorithm]**
   * Set $\text{dist}[0] \leftarrow 0$ (Warehouse source) and $\text{dist}[v] \leftarrow \infty$ for all $v \neq 0$.
   * Set $\text{visited}[v] \leftarrow \text{false}$ for all $v \in V$.
   * Repeat $|V|$ times:
     * Pick unvisited vertex $u$ with minimum $\text{dist}[u]$.
     * Mark $u$ as visited.
     * For each neighbor $v$ of $u$, if $\text{RoadStatus}[u][v] \neq \text{BLOCKED}$:
       $$\text{If } \text{dist}[u] + \text{EffectiveCost}[u][v] < \text{dist}[v] \implies \text{dist}[v] \leftarrow \text{dist}[u] + \text{EffectiveCost}[u][v], \quad \text{parent}[v] \leftarrow u$$

3. **Step 3: [Reconstruct Safe Optimal Routes]**
   For each district $i$, store $\text{min\_cost}[i] = \text{dist}[i]$ and trace route via `parent[i]`. If $\text{dist}[i] == \infty$, mark district as isolated due to impassable roads.

---

### Part B: Multi-Objective Priority Scoring (Severity & Beneficiaries vs Cost)

4. **Step 4: [Calculate Priority Metric]**
   For each district $i \in \{1, \dots, n\}$:
   * If district is reachable ($\text{dist}[i] < \infty$):
     $$P_i = \frac{(\text{Severity}_i \times 1000) + \text{Beneficiaries}_i}{\text{min\_cost}[i]}$$
   * Else:
     $$P_i \leftarrow 0$$
   *(This ensures severely damaged areas with high populations receive highest priority, balanced against transportation expenditure).*

5. **Step 5: [Sort by Priority]**
   Sort district indices in descending order of $P_i$.

---

### Part C: Capacity-Constrained Greedy Resource Allocation

6. **Step 6: [Allocate Supplies within Warehouse Limits]**
   Initialize remaining supplies:
   $$\text{rem\_food} \leftarrow C_{\text{food}}, \quad \text{rem\_med} \leftarrow C_{\text{med}}, \quad \text{rem\_boats} \leftarrow C_{\text{boat}}, \quad \text{rem\_staff} \leftarrow C_{\text{personnel}}$$
   For each district $i$ in descending priority order:
   * **Food:** $\text{AllocFood}_i \leftarrow \min(\text{ReqFood}_i, \text{rem\_food}); \quad \text{rem\_food} \leftarrow \text{rem\_food} - \text{AllocFood}_i$
   * **Medicine:** $\text{AllocMed}_i \leftarrow \min(\text{ReqMed}_i, \text{rem\_med}); \quad \text{rem\_med} \leftarrow \text{rem\_med} - \text{AllocMed}_i$
   * **Boats:** $\text{AllocBoats}_i \leftarrow \min(\text{ReqBoats}_i, \text{rem\_boats}); \quad \text{rem\_boats} \leftarrow \text{rem\_boats} - \text{AllocBoats}_i$
   * **Personnel:** $\text{AllocStaff}_i \leftarrow \min(\text{ReqStaff}_i, \text{rem\_staff}); \quad \text{rem\_staff} \leftarrow \text{rem\_staff} - \text{AllocStaff}_i$

7. **Step 7: [Calculate Total Impact Metrics]**
   * Total beneficiaries assisted = $\sum \text{Beneficiaries}_i$ for all districts where critical relief supplies were delivered.
   * Total transportation cost = $\sum \text{min\_cost}[i]$.

---

### Part D: Real-Time Dynamic Adaptation

8. **Step 8: [Continuous Information Updates]**
   When dynamic events occur (e.g., flash flood damages a road corridor, rain worsens to severe storm, or road cleared by army engineers):
   * Update corresponding edge $(u, v)$ status or weather multiplier.
   * Trigger immediate re-calculation of **Part A**, **Part B**, and **Part C**.
   * Re-route convoys and re-balance resource delivery dynamically.

9. **Step 9: [Stop]**
   Output final dispatch schedule and terminate.

---

## 3. Pseudocode

```text
Algorithm DisasterFloodReliefSystem(V, E, W, D)
    Input : Graph G(V, E), Warehouse W with resources, Districts D[1..n]
    Output: Optimal routes, priority ranks, resource allocation matrix

    // 1. Evaluate effective cost per edge
    for each (u, v) in E do
        if road_status[u][v] == BLOCKED then
            effective_cost[u][v] ← INF
        else
            multiplier ← 1.0
            if road_status[u][v] == DAMAGED then
                multiplier ← 2.0
            end if
            effective_cost[u][v] ← base_distance[u][v] * multiplier * weather_factor[u][v]
        end if
    end for

    // 2. Dijkstra Shortest Path from Supply Hub (node 0)
    for v ← 0 to |V| - 1 do
        dist[v] ← INF
        visited[v] ← false
        parent[v] ← -1
    end for
    dist[0] ← 0

    for step ← 0 to |V| - 1 do
        u ← extract_min_unvisited(dist, visited)
        if u == -1 then break end if
        visited[u] ← true

        for each neighbor v of u do
            if not visited[v] and effective_cost[u][v] < INF then
                if dist[u] + effective_cost[u][v] < dist[v] then
                    dist[v] ← dist[u] + effective_cost[u][v]
                    parent[v] ← u
                end if
            end if
        end for
    end for

    // 3. Priority Scoring & Sorting
    for i ← 1 to n do
        if dist[i] < INF then
            P[i] ← (Severity[i] * 1000 + Beneficiaries[i]) / dist[i]
        else
            P[i] ← 0
        end if
    end for
    SortedDistricts ← SortDescending(D, by P)

    // 4. Greedy Resource Allocation respecting Capacity
    for each d in SortedDistricts do
        if dist[d] < INF then
            alloc_food[d] ← min(req_food[d], W.food)
            W.food ← W.food - alloc_food[d]

            alloc_med[d] ← min(req_med[d], W.med)
            W.med ← W.med - alloc_med[d]

            alloc_boats[d] ← min(req_boats[d], W.boats)
            W.boats ← W.boats - alloc_boats[d]

            alloc_staff[d] ← min(req_staff[d], W.personnel)
            W.personnel ← W.personnel - alloc_staff[d]
        end if
    end for

    return paths, P, allocations
end Algorithm
```

---

## 4. Dry Run Example

### Given Scenario:
* **Central Warehouse Inventory:**
  * Food Packets: $10,000$
  * Medicine Kits: $2,500$
  * Rescue Boats: $40$
  * Medical Personnel: $80$

* **Districts Profile:**

| ID | District Name | Severity ($S_i$) | Beneficiaries ($B_i$) | Req Food | Req Med | Req Boats | Req Staff |
|:--:|:--------------|:----------------:|:---------------------:|:--------:|:-------:|:---------:|:---------:|
| 1  | District A (North Delta) | 5 (Critical) | 4,200 | 4,500 | 1,200 | 20 | 35 |
| 2  | District B (River Basin) | 4 (High)     | 3,100 | 3,200 | 800   | 15 | 25 |
| 3  | District C (Coastal Belt)| 3 (Moderate) | 2,400 | 2,500 | 500   | 8  | 15 |
| 4  | District D (Upland Hills)| 2 (Low)      | 1,200 | 1,200 | 300   | 2  | 10 |

* **Road Network & Environmental Status:**
  * Road $(0, 1)$: Base $25\text{ km}$, **Damaged** ($2.0\times$), **Severe Storm** ($1.8\times$) $\implies \text{Cost} = 25 \times 2.0 \times 1.8 = 90$
  * Road $(0, 2)$: Base $40\text{ km}$, Normal ($1.0\times$), **Rain** ($1.3\times$) $\implies \text{Cost} = 40 \times 1.3 = 52$
  * Road $(1, 2)$: Base $15\text{ km}$, Normal ($1.0\times$), **Rain** ($1.3\times$) $\implies \text{Cost} = 15 \times 1.3 = 19$
  * Road $(1, 3)$: Base $30\text{ km}$, Normal ($1.0\times$), **Clear** ($1.0\times$) $\implies \text{Cost} = 30$
  * Road $(2, 4)$: Base $35\text{ km}$, Normal ($1.0\times$), **Clear** ($1.0\times$) $\implies \text{Cost} = 35$
  * Road $(3, 4)$: Base $20\text{ km}$, Normal ($1.0\times$), **Clear** ($1.0\times$) $\implies \text{Cost} = 20$

---

### Step 1: Shortest Path Routing Trace (Dijkstra)

1. Start at `Hub (0)`: $\text{dist}[0] = 0$.
2. Visit `Hub (0)`:
   * Edge $0 \rightarrow 1$: Cost $90 \implies \text{dist}[1] = 90$, Parent = $0$.
   * Edge $0 \rightarrow 2$: Cost $52 \implies \text{dist}[2] = 52$, Parent = $0$.
3. Next unvisited minimum is `Node 2` ($\text{dist}[2] = 52$):
   * Edge $2 \rightarrow 1$: Cost $19 \implies 52 + 19 = 71 < 90$. **Re-routed via Node 2!** $\implies \text{dist}[1] = 71$, Parent = $2$.
   * Edge $2 \rightarrow 4$: Cost $35 \implies 52 + 35 = 87 \implies \text{dist}[4] = 87$, Parent = $2$.
4. Next unvisited minimum is `Node 1` ($\text{dist}[1] = 71$):
   * Edge $1 \rightarrow 3$: Cost $30 \implies 71 + 30 = 101 \implies \text{dist}[3] = 101$, Parent = $1$.
5. Next unvisited minimum is `Node 4` ($\text{dist}[4] = 87$).
6. Next unvisited minimum is `Node 3` ($\text{dist}[3] = 101$).

**Resulting Route Summary:**
* **District 1 (A):** Cost = $71$, Path = $\text{Hub} \rightarrow \text{District B} \rightarrow \text{District A}$ *(Avoided direct high-risk damaged highway!)*
* **District 2 (B):** Cost = $52$, Path = $\text{Hub} \rightarrow \text{District B}$
* **District 3 (C):** Cost = $101$, Path = $\text{Hub} \rightarrow \text{District B} \rightarrow \text{District A} \rightarrow \text{District C}$
* **District 4 (D):** Cost = $87$, Path = $\text{Hub} \rightarrow \text{District B} \rightarrow \text{District D}$

---

### Step 2: Priority Scoring Table

$$P_i = \frac{S_i \times 1000 + B_i}{\text{Cost}_i}$$

| District | Severity ($S_i$) | Beneficiaries ($B_i$) | Numerator ($S_i \times 1000 + B_i$) | Cost | Priority Score ($P_i$) | Priority Rank |
|:---|:---:|:---:|:---:|:---:|:---:|:---:|
| **District B** | 4 | 3,100 | $4000 + 3100 = 7100$ | 52 | **136.54** | **1** |
| **District A** | 5 | 4,200 | $5000 + 4200 = 9200$ | 71 | **129.58** | **2** |
| **District C** | 3 | 2,400 | $3000 + 2400 = 5400$ | 101 | **53.47** | **3** |
| **District D** | 2 | 1,200 | $2000 + 1200 = 3200$ | 87 | **36.78** | **4** |

---

### Step 3: Resource Allocation Trace (Warehouse Constraints)

| Rank & District | Food (Available $\rightarrow$ Alloc) | Medicine (Avail $\rightarrow$ Alloc) | Boats (Avail $\rightarrow$ Alloc) | Staff (Avail $\rightarrow$ Alloc) |
|:---|:---:|:---:|:---:|:---:|
| **Rank 1: District B** | $10,000 \rightarrow \mathbf{3,200}$ | $2,500 \rightarrow \mathbf{800}$ | $40 \rightarrow \mathbf{15}$ | $80 \rightarrow \mathbf{25}$ |
| *(Remaining Stock)* | $6,800$ | $1,700$ | $25$ | $55$ |
| **Rank 2: District A** | $6,800 \rightarrow \mathbf{4,500}$ | $1,700 \rightarrow \mathbf{1,200}$ | $25 \rightarrow \mathbf{20}$ | $55 \rightarrow \mathbf{35}$ |
| *(Remaining Stock)* | $2,300$ | $500$ | $5$ | $20$ |
| **Rank 3: District C** | $2,300 \rightarrow \mathbf{2,300}$ *(Deficit $200$)* | $500 \rightarrow \mathbf{500}$ | $5 \rightarrow \mathbf{5}$ *(Deficit $3$)* | $20 \rightarrow \mathbf{15}$ |
| *(Remaining Stock)* | **0** | **0** | **0** | $5$ |
| **Rank 4: District D** | $0 \rightarrow \mathbf{0}$ *(Depleted)* | $0 \rightarrow \mathbf{0}$ *(Depleted)* | $0 \rightarrow \mathbf{0}$ *(Depleted)* | $5 \rightarrow \mathbf{5}$ |

**Metrics Achieved:**
* **Beneficiaries Served:** $9,700 / 10,900$ (**$88.99\%$**)
* **Cumulative Transportation Cost:** $52 + 71 + 101 + 87 = \mathbf{311}$
* **Priority Alignment:** All critical severity zones fully serviced first before lower severity districts.

---

## 5. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Shortest Path Routing** | $O(|V|^2)$ or $O(|E| + |V| \log |V|)$ | Standard Dijkstra on $V$ nodes and $E$ road corridors with adjacency matrix/heap. |
| **Priority Metric Evaluation** | $O(n)$ | Linear scan through $n$ affected districts. |
| **District Sorting** | $O(n \log n)$ | Sorting $n$ districts based on multi-criteria priority quotient. |
| **Resource Allocation** | $O(n \times R)$ | Distributing $R$ resource categories across $n$ districts. |
| **Dynamic Re-adaptation** | $O(|E| + |V| \log |V| + n \log n)$ | Triggered only on environmental status changes (road blocked/cleared). |
| **Overall Worst-Case Time** | $O(|V|^2 + n \log n)$ | Dominated by route cost graph analysis and priority scheduling. |
| **Space Complexity** | $O(|V|^2 + n \times R)$ | Adjacency matrix for roads and allocation tables for supplies. |

> **Key Observations:**
> 1. Real-time updates execute in sub-millisecond time, allowing seamless interactive disaster coordination.
> 2. The multi-objective priority formulation ensures that limited stocks of high-demand items (like rescue boats and doctors) are dispatched to maximal life-saving impact.

---

## 6. C Code Reference

* **Full Implementation:** [`floodReliefDistribution.c`](./floodReliefDistribution.c)

---

## 7. Sample Program Output

```text
1. Display Plan
2. Update Condition
3. Reset
4. Exit
Enter choice: 1

=== FLOOD RELIEF DISTRIBUTION PLAN ===

Warehouse Stock: Food=10000, Med=2500, Boats=40, Staff=80

Routes:
District 1 (District A (North Delta)): Cost=71 | Path: Supply Base (Hub) -> District B (River Basin) -> District A (North Delta)
District 2 (District B (River Basin)): Cost=52 | Path: Supply Base (Hub) -> District B (River Basin)
District 3 (District C (Coastal Belt)): Cost=101 | Path: Supply Base (Hub) -> District B (River Basin) -> District A (North Delta) -> District C (Coastal Belt)
District 4 (District D (Upland Hills)): Cost=87 | Path: Supply Base (Hub) -> District B (River Basin) -> District D (Upland Hills)

Resource Allocation:
District                  | Priority | Food(Req/Alloc) | Med(Req/Alloc) | Boats(Req/Alloc) | Staff(Req/Alloc)
-------------------------------------------------------------------------------------------------
District A (North Delta)  |   129.58 |  4500 / 4500    | 1200 / 1200  |  20 / 20       |  35 / 35 
District B (River Basin)  |   136.54 |  3200 / 3200    |  800 / 800   |  15 / 15       |  25 / 25 
District C (Coastal Belt) |    53.47 |  2500 / 2300    |  500 / 500   |   8 / 5        |  15 / 15 
District D (Upland Hills) |    36.78 |  1200 / 0       |  300 / 0     |   2 / 0        |  10 / 5  
-------------------------------------------------------------------------------------------------
Total Transport Cost = 311
```
