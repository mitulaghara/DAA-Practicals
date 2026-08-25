# Activity Selection Algorithm & Documentation

This document contains the exact Activity Selection algorithm, pseudocode, dry run trace, complexity analysis, and sample output based on your professor's handwritten notes and [`activitySelection.c`](./activitySelection.c).

---

## 1. Whiteboard Algorithm (Exact Professor's Notation)

```text
ActivitySelection(A, S, F)
{
    // Sort activity into ascending order w.r.t fi
    S ← A[i]
    i ← 1
    for j ← 0 to n do
    {
        if (S[j] >= F[i]) then
        {
            S ← S U {A[j]}
            i ← j
        }
    }
    return S;
}

⊙ Time Complexity

T(n) = O(n log n)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `ACTIVITY_SELECTION(n, s[], f[])`

* **Input:** Number of activities `n`, start time array `s[]`, finish time array `f[]`.
* **Output:** Maximum set `S` of mutually compatible (non-overlapping) activities.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input Activities]**
   Read `n` (number of activities), `s[i]` (start time), and `f[i]` (finish time) for each activity.

3. **Step 3: [Sort by Finish Time]**
   Sort all activities in **ascending order** of their finish time `f[i]`.

4. **Step 4: [Select First Activity]**
   Add the first activity to selected set `S`.
   Set `last ← 1` (index of last selected activity).

5. **Step 5: [Greedy Selection Loop]**
   For `j ← 2` to `n`, do Steps 6 to 7:

6. **Step 6: [Compatibility Check]**
   If `s[j] >= f[last]` then:
   * Add activity `j` to selected set `S`.
   * Set `last ← j`.

7. **Step 7: [End of Loop]**

8. **Step 8: [Output & Stop]**
   Print all selected activities and total count. Stop.

---

## 3. Pseudocode

```text
Algorithm ActivitySelection(n, s[], f[])
    Input : n activities with start times s[i] and finish times f[i]
    Output: Maximum set S of non-overlapping activities

    // Step 1: Sort activities by finish time in ascending order
    Sort activities by f[i] in non-decreasing order

    // Step 2: Select first activity
    S ← {A[1]}
    last ← 1

    // Step 3: Greedy selection
    for j ← 2 to n do
        if s[j] >= f[last] then
            S ← S ∪ {A[j]}
            last ← j
        end if
    end for

    return S
end Algorithm
```

---

## 4. Dry Run Example (6 Activities)

**Given Activities (`n = 6`):**

| Activity | Start `s[i]` | Finish `f[i]` |
|:--------:|:------------:|:-------------:|
| 1        | 1            | 4             |
| 2        | 3            | 5             |
| 3        | 0            | 6             |
| 4        | 5            | 7             |
| 5        | 3            | 9             |
| 6        | 5            | 9             |

**After Sorting by Finish Time (ascending):**

| Activity | `s[i]` | `f[i]` |
|:--------:|:------:|:------:|
| 1        | 1      | 4      |
| 2        | 3      | 5      |
| 3        | 0      | 6      |
| 4        | 5      | 7      |
| 5        | 3      | 9      |
| 6        | 5      | 9      |

**Greedy Selection Process:**

| j | Activity | `s[j]` | `f[last]` | Condition        | Selected? | `last` |
|:-:|:--------:|:------:|:---------:|:----------------:|:---------:|:------:|
| 1 | A1       | 1      | —         | First → Selected | ✅ Yes    | 1      |
| 2 | A2       | 3      | 4         | 3 >= 4? ❌        | ❌ No     | 1      |
| 3 | A3       | 0      | 4         | 0 >= 4? ❌        | ❌ No     | 1      |
| 4 | A4       | 5      | 4         | 5 >= 4? ✅        | ✅ Yes    | 4      |
| 5 | A5       | 3      | 7         | 3 >= 7? ❌        | ❌ No     | 4      |
| 6 | A6       | 5      | 7         | 5 >= 7? ❌        | ❌ No     | 4      |

**Selected Activities = { A1, A4 }**

**Total Activities Selected = 2**

---

## 5. Complexity Analysis

| Case | Time Complexity | Description |
|:---|:---:|:---|
| **Best Case (Ω)** | Ω(n log n) | Dominated by the sorting step (sorting activities by finish time). Even in the best case, sorting takes n log n comparisons. |
| **Average Case (Θ)** | Θ(n log n) | On average, sorting takes n log n and the greedy loop runs in O(n). Overall: Θ(n log n). |
| **Worst Case (O)** | O(n log n) | All n activities must be checked. Sorting dominates at O(n log n); greedy loop is O(n). |
| **Space Complexity** | O(n) | Extra space used for arrays s[], f[], and selected[] of size n. |

> **Note (from Professor's notes):**
> `T(n) = O(n log n)`
> The greedy selection loop alone is O(n), but the overall complexity is **O(n log n)** due to sorting.

---

## 6. C Code Reference

Your C code implementation is in [`activitySelection.c`](./activitySelection.c) / [`index.c`](./index.c).

---

## 7. Sample Program Output (6 Activities)

```text
Enter the number of activities: 6

---------------Activity[1]---------------
Enter the Start  time : 1
Enter the Finish time : 4

---------------Activity[2]---------------
Enter the Start  time : 3
Enter the Finish time : 5

---------------Activity[3]---------------
Enter the Start  time : 0
Enter the Finish time : 6

---------------Activity[4]---------------
Enter the Start  time : 5
Enter the Finish time : 7

---------------Activity[5]---------------
Enter the Start  time : 3
Enter the Finish time : 9

---------------Activity[6]---------------
Enter the Start  time : 5
Enter the Finish time : 9

Scenario Before Sorting

Activity :     1    2    3    4    5    6
Start    :     1    3    0    5    3    5
Finish   :     4    5    6    7    9    9


Scenario After Sorting (by Finish Time)

Activity :     1    2    3    4    5    6
Start    :     1    3    0    5    3    5
Finish   :     4    5    6    7    9    9


Selected Activities :
  Activity[1] -> Start: 1, Finish: 4
  Activity[4] -> Start: 5, Finish: 7

Total Activities Selected : 2
```
