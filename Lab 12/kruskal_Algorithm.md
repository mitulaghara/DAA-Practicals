# Kruskal's Algorithm & Documentation

This document contains the complete Kruskal's Minimum Spanning Tree (MST) algorithm, pseudocode, step-by-step procedure, dry run trace with edge selection tables, complexity analysis, and sample output based on your lab program [`kruskal.c`](./kruskal.c).

---

## 1. Notebook / Whiteboard Algorithm (Exact Professor's Notation)

```text
Practical - 12
Aim :- Develop a Program to implement Kruskal’s Algorithm to find the Minimum Spanning Tree (MST) of a given connected undirected graph.

Kruskal(V, E, w)
{
    A ← ∅

    // Initialize Disjoint Sets
    for each vertex v ∈ V do
        MAKE-SET(v)

    // Sort edges in non-decreasing order of weight
    Sort E into non-decreasing order by weight w

    for each edge (u, v) ∈ E in sorted order do
    {
        if FIND-SET(u) ≠ FIND-SET(v) then
        {
            A ← A ∪ {(u, v)}
            UNION(u, v)
        }
    }

    return A
}

⊙ Time Complexity

T(V, E) = O(E log E)  or  O(E log V)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

### Part A: Disjoint Set Operations (`FIND` & `UNION`)

* **`FIND(parent, i)`:**
  1. If `parent[i] == i`, return `i`.
  2. Else recursively call `FIND(parent, parent[i])` (with path compression).

* **`UNION(parent, rank, u, v)`:**
  1. Find root of `u`: `rootU ← FIND(parent, u)`.
  2. Find root of `v`: `rootV ← FIND(parent, v)`.
  3. Attach tree with smaller rank under root of tree with higher rank. If ranks are equal, make one root and increment its rank.

---

### Part B: Kruskal's MST Construction

**Algorithm:** `KRUSKAL_MST(V, E)`

* **Input:**
  * Number of vertices $V$.
  * Number of edges $E$, where each edge is represented as $(u, v)$ with weight $w$.
* **Output:**
  * Set of $V - 1$ edges forming the Minimum Spanning Tree and the minimum total cost.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input Graph]**
   Read number of vertices $V$ and number of edges $E$. Read source $u$, destination $v$, and weight $w$ for each edge.

3. **Step 3: [Initialize Disjoint Sets]**
   For each vertex $i \leftarrow 0$ to $V - 1$:
   * Set `parent[i] ← i`
   * Set `rank[i] ← 0`

4. **Step 4: [Sort Edges]**
   Sort all $E$ edges in **ascending order** of their weights ($w$).

5. **Step 5: [Initialize MST Trackers]**
   Set `mstEdgeCount ← 0` and `totalCost ← 0`.

6. **Step 6: [Greedy Edge Selection Loop]**
   For each sorted edge $(u, v, w)$ from index $0$ to $E - 1$:
   * Find root of $u$: `rootU ← FIND(parent, u)`
   * Find root of $v$: `rootV ← FIND(parent, v)`
   * **Cycle Check:**
     * If `rootU ≠ rootV`:
       * Add edge $(u, v)$ to MST.
       * `totalCost ← totalCost + w`
       * Call `UNION(parent, rank, rootU, rootV)`.
       * `mstEdgeCount ← mstEdgeCount + 1`.
       * If `mstEdgeCount == V - 1`, break the loop (MST is complete).
     * Else:
       * Edge forms a cycle; discard edge.

7. **Step 7: [Connectivity Validation]**
   If `mstEdgeCount < V - 1`, print "Graph is disconnected; MST cannot be formed."

8. **Step 8: [Display Results & Stop]**
   Print selected MST edges and `totalCost`. End of algorithm.

---

## 3. Pseudocode

```text
Algorithm KruskalMST(V, E)
    Input : Set of vertices V, set of weighted edges E
    Output: Minimum Spanning Tree MST and minimum cost

    // Step 1: Initialize Disjoint Sets
    for each v ∈ V do
        parent[v] ← v
        rank[v] ← 0
    end for

    // Step 2: Sort all edges in non-decreasing order of weight
    Sort(E, by weight ascending)

    MST ← ∅
    totalCost ← 0
    count ← 0

    // Step 3: Iterate through sorted edges
    for each edge (u, v) with weight w in E do
        rootU ← Find(parent, u)
        rootV ← Find(parent, v)

        if rootU ≠ rootV then
            MST ← MST ∪ {(u, v)}
            totalCost ← totalCost + w
            Union(parent, rank, rootU, rootV)
            count ← count + 1

            if count == |V| - 1 then
                break
            end if
        end if
    end for

    return MST, totalCost
end Algorithm
```

---

## 4. Dry Run Example

**Input Graph:**
* Vertices: $V = 4$ (Vertices: $\{0, 1, 2, 3\}$)
* Edges: $E = 5$

| Edge Index | Edge $(u, v)$ | Weight ($w$) |
|:---:|:---:|:---:|
| 1 | $(0, 1)$ | 10 |
| 2 | $(0, 2)$ | 6 |
| 3 | $(0, 3)$ | 5 |
| 4 | $(1, 3)$ | 15 |
| 5 | $(2, 3)$ | 4 |

---

### Step 1: Sort Edges in Ascending Order of Weight

| Sorted Rank | Edge $(u - v)$ | Weight |
|:---:|:---:|:---:|
| 1 | $(2, 3)$ | 4 |
| 2 | $(0, 3)$ | 5 |
| 3 | $(0, 2)$ | 6 |
| 4 | $(0, 1)$ | 10 |
| 5 | $(1, 3)$ | 15 |

---

### Step 2: Disjoint Sets Trace & Cycle Detection

Initial Sets: $\{0\}, \{1\}, \{2\}, \{3\}$

1. **Edge $(2, 3)$, Weight = 4:**
   * $\text{Find}(2) = 2$, $\text{Find}(3) = 3$ ($2 \neq 3$) $\implies$ **No Cycle**.
   * **Action:** **SELECT** edge $(2, 3)$.
   * $\text{Union}(2, 3) \implies$ Sets: $\{0\}, \{1\}, \{2, 3\}$.
   * Current MST Edges = $1$, Cost = $4$.

2. **Edge $(0, 3)$, Weight = 5:**
   * $\text{Find}(0) = 0$, $\text{Find}(3) = 2$ ($0 \neq 2$) $\implies$ **No Cycle**.
   * **Action:** **SELECT** edge $(0, 3)$.
   * $\text{Union}(0, 2) \implies$ Sets: $\{1\}, \{0, 2, 3\}$.
   * Current MST Edges = $2$, Cost = $4 + 5 = 9$.

3. **Edge $(0, 2)$, Weight = 6:**
   * $\text{Find}(0) = 0$, $\text{Find}(2) = 0$ ($0 == 0$) $\implies$ **Cycle Detected!**
   * **Action:** **DISCARD** edge $(0, 2)$.

4. **Edge $(0, 1)$, Weight = 10:**
   * $\text{Find}(0) = 0$, $\text{Find}(1) = 1$ ($0 \neq 1$) $\implies$ **No Cycle**.
   * **Action:** **SELECT** edge $(0, 1)$.
   * $\text{Union}(0, 1) \implies$ Sets: $\{0, 1, 2, 3\}$.
   * Current MST Edges = $3$ ($V - 1 = 4 - 1 = 3$).
   * Cost = $9 + 10 = 19$.
   * **Stop:** MST complete ($V - 1$ edges found).

---

### Final MST Summary

| No. | Edge $(u - v)$ | Weight |
|:---:|:---:|:---:|
| 1 | $(2, 3)$ | 4 |
| 2 | $(0, 3)$ | 5 |
| 3 | $(0, 1)$ | 10 |

$$\text{Minimum Total Cost} = 4 + 5 + 10 = \mathbf{19}$$

---

## 5. Complexity Analysis

| Operation | Time Complexity | Details |
|:---|:---:|:---|
| **Edge Sorting** | $O(E \log E)$ | Sorting $E$ edges by weight using comparison sorts (Merge/Quick sort). |
| **Disjoint Set Operations** | $O(E \cdot \alpha(V))$ | Performing $2E$ `FIND` and $V-1$ `UNION` operations with path compression ($\alpha$ is the Inverse Ackermann function, practically $\le 4$). |
| **Overall Time Complexity** | $O(E \log E)$ or $O(E \log V)$ | Since $E \le V^2$, $\log E = O(\log V)$. Sorting dominates the runtime. |
| **Space Complexity** | $O(V + E)$ | Requires arrays `parent[]` and `rank[]` of size $V$, plus edge storage of size $E$. |

> **Key Takeaway:**
> * Kruskal's algorithm is a **Greedy Algorithm**.
> * It performs particularly well on **sparse graphs** (where $E \ll V^2$).

---

## 6. C Code Reference

* **Full Implementation:** [`kruskal.c`](./kruskal.c)

---

## 7. Sample Program Output

```text
============================================
           KRUSKAL'S MST ALGORITHM          
============================================

Enter number of vertices: 4
Enter number of edges: 5

Enter each edge as: <Source> <Destination> <Weight>
(Vertices are numbered 0 to 3 or 1 to 4)

Edge 1: 0 1 10
Edge 2: 0 2 6
Edge 3: 0 3 5
Edge 4: 1 3 15
Edge 5: 2 3 4

Sorted Edges:
Index  | Edge (u - v) | Weight  
-------------------------------
1      |  2 - 3       | 4       
2      |  0 - 3       | 5       
3      |  0 - 2       | 6       
4      |  0 - 1       | 10      
5      |  1 - 3       | 15      

--- Edge Selection Trace ---
Edge         | Weight   | Status       | Reason / Action     
------------------------------------------------------------------
( 2,  3)     | 4        | SELECTED     | Added to MST (No cycle)
( 0,  3)     | 5        | SELECTED     | Added to MST (No cycle)
( 0,  2)     | 6        | DISCARDED    | Rejected (Forms cycle)
( 0,  1)     | 10       | SELECTED     | Added to MST (No cycle)
------------------------------------------------------------------

============================================
     MINIMUM SPANNING TREE (MST) RESULT     
============================================
No.    | Edge (u - v) | Weight  
--------------------------------------------
1      |  2 - 3       | 4       
2      |  0 - 3       | 5       
3      |  0 - 1       | 10      
--------------------------------------------
Minimum Total Cost of Spanning Tree = 19
============================================
```
