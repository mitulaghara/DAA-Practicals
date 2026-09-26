# Naïve String Matching Algorithm & Documentation

This document contains the complete Naïve String Matching algorithm, pseudocode, step-by-step procedure, dry run trace with shift tables, complexity analysis, and sample output based on your lab program [`naiveStringMatching.c`](./naiveStringMatching.c).

---

## 1. Notebook / Whiteboard Algorithm (Exact Professor's Notation)

```text
Practical - 13
Aim :- Develop a Program to implement the Naïve String Matching Algorithm.

Naive_String_Matcher(T, P)
{
    n ← length(T)
    m ← length(P)

    for s ← 0 to n - m do
    {
        j ← 0
        while (j < m AND P[j] == T[s + j]) do
            j ← j + 1

        if (j == m) then
            Print "Pattern occurs with shift ", s
    }
}

⊙ Time Complexity

Best Case  : O(n)
Worst Case : O((n - m + 1) × m)
```

---

## 2. Step-by-Step Algorithm (Exam/Lab Writing Format)

**Algorithm:** `NAIVE_STRING_MATCHER(T, P)`

* **Input:** 
  * Text string $T$ of length $n$
  * Pattern string $P$ of length $m$ (where $m \le n$)
* **Output:** 
  * All valid shift positions $s$ where pattern $P$ occurs in text $T$.

1. **Step 1: [Start]**
   Start the algorithm.

2. **Step 2: [Input Strings and Determine Lengths]**
   * Read Text string $T$ and Pattern string $P$.
   * Compute $n \leftarrow \text{length}(T)$ and $m \leftarrow \text{length}(P)$.

3. **Step 3: [Validate Lengths]**
   If $m > n$, print error message "Pattern length cannot exceed text length" and terminate.

4. **Step 4: [Outer Loop for Valid Shifts]**
   For shift $s \leftarrow 0$ to $n - m$, execute Steps 5 to 7:

5. **Step 5: [Character by Character Matching]**
   Initialize inner counter $j \leftarrow 0$.
   While $j < m$ and $P[j] == T[s + j]$:
   * Increment $j \leftarrow j + 1$.

6. **Step 6: [Check Full Pattern Match]**
   If $j == m$:
   * Pattern is found at shift index $s$.
   * Print "Pattern occurs with shift $s$".

7. **Step 7: [End of Outer Loop]**

8. **Step 8: [Stop]**
   End of algorithm.

---

## 3. Pseudocode

```text
Algorithm NaiveStringMatcher(T, P)
    Input : Text T[0..n-1], Pattern P[0..m-1]
    Output: Shift indices s where pattern matches

    n ← length(T)
    m ← length(P)

    // Check all valid shifts s from 0 to n - m
    for s ← 0 to n - m do
        match ← true
        for j ← 0 to m - 1 do
            if T[s + j] ≠ P[j] then
                match ← false
                break
            end if
        end for

        if match == true then
            print "Pattern found at shift index: " + s
        end if
    end for
end Algorithm
```

---

## 4. Dry Run Example

**Input:**
* Text ($T$): `"AABAACAADAABAABA"` ($n = 16$)
* Pattern ($P$): `"AABA"` ($m = 4$)
* Number of possible shifts: $n - m + 1 = 16 - 4 + 1 = 13$ (Shifts $s = 0$ to $12$)

### Shift Comparison Trace Table

| Shift ($s$) | Text Substring $T[s \dots s+m-1]$ | Pattern $P[0 \dots m-1]$ | Character Comparisons | Outcome | Match Index |
|:---:|:---:|:---:|:---|:---:|:---:|
| **0** | `AABA` | `AABA` | $T[0]==P[0]$, $T[1]==P[1]$, $T[2]==P[2]$, $T[3]==P[3]$ | **MATCH** | **$s = 0$** |
| **1** | `ABAA` | `AABA` | $T[1]==P[0]$, $T[2] \neq P[1]$ (`'B' != 'A'`) | Mismatch | - |
| **2** | `BAAC` | `AABA` | $T[2] \neq P[0]$ (`'B' != 'A'`) | Mismatch | - |
| **3** | `AACA` | `AABA` | $T[3]==P[0]$, $T[4]==P[1]$, $T[5] \neq P[2]$ (`'C' != 'B'`) | Mismatch | - |
| **4** | `ACAA` | `AABA` | $T[4]==P[0]$, $T[5] \neq P[1]$ (`'C' != 'A'`) | Mismatch | - |
| **5** | `CAAD` | `AABA` | $T[5] \neq P[0]$ (`'C' != 'A'`) | Mismatch | - |
| **6** | `AADA` | `AABA` | $T[6]==P[0]$, $T[7]==P[1]$, $T[8] \neq P[2]$ (`'D' != 'B'`) | Mismatch | - |
| **7** | `ADAA` | `AABA` | $T[7]==P[0]$, $T[8] \neq P[1]$ (`'D' != 'A'`) | Mismatch | - |
| **8** | `DAAB` | `AABA` | $T[8] \neq P[0]$ (`'D' != 'A'`) | Mismatch | - |
| **9** | `AABA` | `AABA` | $T[9]==P[0]$, $T[10]==P[1]$, $T[11]==P[2]$, $T[12]==P[3]$ | **MATCH** | **$s = 9$** |
| **10** | `ABAA` | `AABA` | $T[10]==P[0]$, $T[11] \neq P[1]$ (`'B' != 'A'`) | Mismatch | - |
| **11** | `BAAB` | `AABA` | $T[11] \neq P[0]$ (`'B' != 'A'`) | Mismatch | - |
| **12** | `AABA` | `AABA` | $T[12]==P[0]$, $T[13]==P[1]$, $T[14]==P[2]$, $T[15]==P[3]$ | **MATCH** | **$s = 12$** |

### Dry Run Summary
* **Total Occurrences:** $3$ (at shift indices **$0$**, **$9$**, and **$12$**)
* **Total Character Comparisons:** $30$

---

## 5. Complexity Analysis

| Case | Time Complexity | Condition / Scenario |
|:---|:---:|:---|
| **Best Case ($\Omega$)** | $\Omega(n)$ | When the first character of the pattern does not match the text at any shift (e.g., $T = \text{"AAAAAAAA"}$, $P = \text{"BA"}$). Only $1$ comparison per shift $\implies (n - m + 1) \times 1 = O(n)$. |
| **Average Case ($\Theta$)** | $\Theta(n)$ | In natural languages with large alphabets, mismatches occur within the first few character comparisons. |
| **Worst Case ($O$)** | $O((n - m + 1) \times m)$ | When all characters match until the very last character of the pattern for every shift (e.g., $T = \text{"AAAAAAAA"}$, $P = \text{"AAAB"}$). |
| **Space Complexity** | $O(1)$ | Auxiliary space is constant since no extra tables or preprocessing arrays are needed. |

> **Key Observations:**
> 1. **Preprocessing Time:** $0$ (No preprocessing is required).
> 2. **Matching Time:** $O((n - m + 1) \times m)$.
> 3. Does not require extra memory like KMP ($\pi$ table) or Rabin-Karp (hash values), making it simple and straightforward for small inputs.

---

## 6. C Code Reference

* **Full Implementation:** [`naiveStringMatching.c`](./naiveStringMatching.c)

---

## 7. Sample Program Output

```text
Enter text: AABAACAADAABAABA
Enter pattern: AABA
Pattern found at index 0
Pattern found at index 9
Pattern found at index 12
```
