# Prim's Algorithm & Documentation

This document contains the complete Prim's Minimum Spanning Tree (MST) algorithm, pseudocode, step-by-step procedure, dry run trace with key/parent tables, complexity analysis, and sample output based on your lab program [`prims.c`](./prims.c).

---

## 1. Notebook / Whiteboard Algorithm (Exact Professor's Notation)

```text
Practical - 11
Aim :- Develop a Program to implement Prim’s Algorithm to find the Minimum Spanning Tree (MST) of a given connected undirected graph.

MST-PRIM(G, w, r)
{
    for each u ∈ G.V do
    {
        u.key ← ∞
        u.π ← NIL
    }
    
    r.key ← 0
    Q ← G.V

    while Q ≠ ∅ do
    {
        u ← EXTRACT-MIN(Q)

        for each v ∈ G.Adj[u] do
        {
            if (v ∈ Q AND w(u, v) < v.key) then
            {
                v.π ← u
                v.key ← w(u, v)
            }
        }
    }
}

⊙ Time Complexity

Using Adjacency Matrix  : T(V) = O(V²)
Using Min-Heap          : T(V, E) = O(E log V)
Using Fibonacci Heap    : T(V, E) = O(E + V log V)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `PRIM_MST(graph, V)`

* **Input:**
  * Number of vertices $V$.
  * Weighted connected undirected graph represented via Adjacency Matrix `graph[V][V]`.
* **Output:**
  * Minimum Spanning Tree (MST) consisting of $V - 1$ edges with minimum total weight.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input Graph]**
   Read the number of vertices $V$ and the $V \times V$ adjacency matrix `graph[V][V]`.

3. **Step 3: [Initialize Arrays]**
   For each vertex $i \leftarrow 0$ to $V - 1$:
   * Set `key[i] ← ∞` (stores minimum weight to connect vertex $i$ to tree).
   * Set `mstSet[i] ← 0` (boolean flag: 1 if included in MST, else 0).
   * Set `parent[i] ← -1` (stores parent node in the MST).

4. **Step 4: [Set Root Vertex]**
   * Choose starting vertex $0$ as root:
     * `key[0] ← 0`
     * `parent[0] ← -1`

5. **Step 5: [MST Construction Loop]**
   For `count ← 0` to $V - 1$, execute Steps 6 to 8:

6. **Step 6: [Extract Minimum Key Vertex]**
   Find unvisited vertex $u$ with the minimum `key[u]` such that `mstSet[u] == 0`:
   $$u \leftarrow \text{minKey}(key, mstSet, V)$$
   Include vertex $u$ into the spanning tree:
   $$\text{mstSet}[u] \leftarrow 1$$

7. **Step 7: [Relax Adjacent Edges]**
   For each adjacent vertex $v \leftarrow 0$ to $V - 1$:
   * If `graph[u][v] > 0` AND `mstSet[v] == 0` AND `graph[u][v] < key[v]`:
     * Update parent: `parent[v] ← u`
     * Update key value: `key[v] ← graph[u][v]`

8. **Step 8: [End of Loop]**

9. **Step 9: [Display Results]**
   * Print all MST edges: `(parent[i], i)` and their corresponding weights `graph[i][parent[i]]` for $i = 1$ to $V - 1$.
   * Calculate and print `TotalCost = Σ weight`.

10. **Step 10: [Stop]**
    End of algorithm.

---

## 3. Pseudocode

```text
Algorithm PrimMST(graph, V)
    Input : Adjacency matrix graph[0..V-1][0..V-1], number of vertices V
    Output: Minimum Spanning Tree edges and total minimum cost

    // Step 1: Initialize helper arrays
    for i ← 0 to V - 1 do
        key[i] ← INF
        mstSet[i] ← false
        parent[i] ← -1
    end for

    key[0] ← 0
    parent[0] ← -1

    // Step 2: Loop to pick V vertices
    for count ← 0 to V - 1 do
        // Find vertex with minimum key value not yet in MST
        u ← vertex with min key[u] where mstSet[u] == false
        mstSet[u] ← true

        // Update key values of adjacent vertices
        for v ← 0 to V - 1 do
            if graph[u][v] ≠ 0 and mstSet[v] == false and graph[u][v] < key[v] then
                parent[v] ← u
                key[v] ← graph[u][v]
            end if
        end for
    end for

    // Step 3: Compute and return MST
    totalCost ← 0
    for i ← 1 to V - 1 do
        totalCost ← totalCost + graph[i][parent[i]]
    end for

    return parent, totalCost
end Algorithm
```

---

## 4. Dry Run Example

**Input Graph:**
* Vertices: $V = 5$ ($\{0, 1, 2, 3, 4\}$)
* Adjacency Matrix:

| Vertex | 0 | 1 | 2 | 3 | 4 |
|:---:|:---:|:---:|:---:|:---:|:---:|
| **0** | 0 | 2 | 0 | 6 | 0 |
| **1** | 2 | 0 | 3 | 8 | 5 |
| **2** | 0 | 3 | 0 | 0 | 7 |
| **3** | 6 | 8 | 0 | 0 | 9 |
| **4** | 0 | 5 | 7 | 9 | 0 |

---

### Step-by-Step State Trace Table

#### Initialization:
* `key = [0, ∞, ∞, ∞, ∞]`
* `parent = [-1, -1, -1, -1, -1]`
* `mstSet = [0, 0, 0, 0, 0]`

---

#### Iteration 1:
* Pick vertex with $\min(\text{key})$ where `mstSet == 0`: **Vertex $0$** (`key[0] = 0`).
* Mark `mstSet[0] = 1`.
* Relax adjacent edges of $0$:
  * Neighbor $1$: weight $2 < \infty \implies \text{key}[1] = 2, \text{parent}[1] = 0$
  * Neighbor $3$: weight $6 < \infty \implies \text{key}[3] = 6, \text{parent}[3] = 0$
* **State:**
  * `key = [0, 2, ∞, 6, ∞]`
  * `parent = [-1, 0, -1, 0, -1]`
  * `mstSet = [1, 0, 0, 0, 0]`

---

#### Iteration 2:
* Pick vertex with $\min(\text{key})$ where `mstSet == 0`: **Vertex $1$** (`key[1] = 2`).
* Mark `mstSet[1] = 1`.
* **Edge Added:** $(0, 1)$ with weight $2$.
* Relax adjacent edges of $1$:
  * Neighbor $2$: weight $3 < \infty \implies \text{key}[2] = 3, \text{parent}[2] = 1$
  * Neighbor $3$: weight $8 \not< \text{key}[3](6) \implies$ No change.
  * Neighbor $4$: weight $5 < \infty \implies \text{key}[4] = 5, \text{parent}[4] = 1$
* **State:**
  * `key = [0, 2, 3, 6, 5]`
  * `parent = [-1, 0, 1, 0, 1]`
  * `mstSet = [1, 1, 0, 0, 0]`

---

#### Iteration 3:
* Pick vertex with $\min(\text{key})$ where `mstSet == 0`: **Vertex $2$** (`key[2] = 3`).
* Mark `mstSet[2] = 1`.
* **Edge Added:** $(1, 2)$ with weight $3$.
* Relax adjacent edges of $2$:
  * Neighbor $4$: weight $7 \not< \text{key}[4](5) \implies$ No change.
* **State:**
  * `key = [0, 2, 3, 6, 5]`
  * `parent = [-1, 0, 1, 0, 1]`
  * `mstSet = [1, 1, 1, 0, 0]`

---

#### Iteration 4:
* Pick vertex with $\min(\text{key})$ where `mstSet == 0`: **Vertex $4$** (`key[4] = 5`).
* Mark `mstSet[4] = 1`.
* **Edge Added:** $(1, 4)$ with weight $5$.
* Relax adjacent edges of $4$:
  * Neighbor $3$: weight $9 \not< \text{key}[3](6) \implies$ No change.
* **State:**
  * `key = [0, 2, 3, 6, 5]`
  * `parent = [-1, 0, 1, 0, 1]`
  * `mstSet = [1, 1, 1, 0, 1]`

---

#### Iteration 5:
* Pick vertex with $\min(\text{key})$ where `mstSet == 0`: **Vertex $3$** (`key[3] = 6`).
* Mark `mstSet[3] = 1`.
* **Edge Added:** $(0, 3)$ with weight $6$.
* All vertices are now included in `mstSet`.

---

### Final MST Summary

| No. | Edge $(u - v)$ | Weight |
|:---:|:---:|:---:|
| 1 | $(0, 1)$ | 2 |
| 2 | $(1, 2)$ | 3 |
| 3 | $(0, 3)$ | 6 |
| 4 | $(1, 4)$ | 5 |

$$\text{Minimum Total Cost} = 2 + 3 + 6 + 5 = \mathbf{16}$$

---

## 5. Complexity Analysis

| Implementation | Time Complexity | Best For |
|:---|:---:|:---|
| **Adjacency Matrix (Standard)** | $O(V^2)$ | **Dense Graphs** (where $E \approx V^2$). |
| **Adjacency List + Binary Heap** | $O(E \log V)$ | **Sparse Graphs** (where $E \ll V^2$). |
| **Adjacency List + Fibonacci Heap** | $O(E + V \log V)$ | Theoretically optimal for large network topologies. |
| **Space Complexity** | $O(V^2)$ / $O(V)$ | $O(V^2)$ for adjacency matrix representation; auxiliary arrays (`key`, `parent`, `mstSet`) take $O(V)$ space. |

> **Key Takeaway:**
> * Prim's algorithm grows a single tree continuously from an arbitrary starting root vertex.
> * Unlike Kruskal's algorithm (which sorts all edges upfront), Prim's algorithm always maintains a connected component throughout its execution.

---

## 6. C Code Reference

* **Full Implementation:** [`prims.c`](./prims.c)

---

## 7. Sample Program Output

```text
Enter number of vertices: 5
Enter adjacency matrix:
0 2 0 6 0
2 0 3 8 5
0 3 0 0 7
6 8 0 0 9
0 5 7 9 0

Edge 	Weight
0 - 1 	2
1 - 2 	3
0 - 3 	6
1 - 4 	5
Total Cost = 16
```

