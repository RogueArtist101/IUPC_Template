# Formulas

> Math reference formulas from IUPC Template (LaTeX source preserved for rendering)

## General

- Jordan Totient, $J_k(n)= n^k\prod_{p|n}(1-\frac{1}{p^k})$, (k+1) tuples of coprime with n. $\phi(n)=J_1(n)$

## Sequence Permutations

- $d(n) = (n-1)\cdot (d(n-1)+d(n-2))$

- total = n+m-k; ncr(total, n) - ncr(total,m+1): There are M 1s and N 0s. The amount of 0s in prefix can't be more than K more than the number of 1s.
When k = 0, consistently dominated.
When n = m, bracket sequences with k opening brackets at the start.
When n = m and k = 0, catalan number.

- M 1s and N 0s, probability that 1 is always strictly ahead is $\frac{M-N}{M+N}$. If draws allowed, $\frac{M+1-N}{M+1}$

- Eulerian Numbers $A(n,k)$: Number of permutations of n in which exactly k elements are greater than the previous element.

$A(n, k) = (n-k)\,A(n-1, k-1) + (k+1)\,A(n-1, k)$; $A(0,0)=1$, $A(n,k)=0$ for $k<0$ or $k \ge n$

$A(n, k) = \sum_{i=0}^{k+1} (-1)^i \times \binom{n+1}{i} (k+1-i)^n$

## Sum Formulas (Pascal Triangle)

- $\sum_{i=1}^{n} i^{k} = \frac{1}{k+1} \sum_{j=0}^{k} (-1)^j \times \binom{k+1}{j} B_j  n^{ k+1-j}$

- $B_m = -\frac{1}{m+1} \sum_{k=0}^{m-1} \times \binom{m+1}{k} B_k.$

- $\sum_{i=1}^{n} i^4 = \frac{n(n+1)(2n+1)(3n^2+3n-1)}{30}$

- $\sum_{i=1}^{n} i^5 = \frac{n^2 (n+1)^{2} (2n^2+2n-1)}{12}$

- $\sum_{i=0}^{k} (-1)^i \binom{n}{i} = (-1)^k \binom{n-1}{k}$

- $\sum_{i=0}^{n}\binom{i}{r}=  \binom{n+1}{r+1}$

- $\sum_{i=0}^{n} ({\binom{n}{i}})^2= \binom{2n}{n}$

- $\sum_{i=0}^{n}(\binom{n}{i})(\binom{n}{n-i})=\binom{2n}{n}$

- $\sum_{i=0}^{n} i\times \binom{n}{i} \times a^k \times b^{n-k} = na (a+b)^{n-1}$

- $\sum_{i=0}^\infty i^k\times \binom{n}{i} \times a^i \times b^{n-i} = \sum_{j=0}^{k} S(k,j)\times P_{n,j}\times a^j (a+b)^{n-j}$

- $\sum_{i=0}^\infty {\binom{i}{k}}\times p^k \times r^{i-k} \ = \frac{p^k}{(1-r)^{k+1}}$

## Partitions

- The coeffecient of $x^m$ in $P_{x,k}$ is the stirling number of first kind $c(k,m)\times(-1)^{n-k}$

- Stirling Number of First kind: Number of permutations of n elements with exactly k disjoint cycles = $c(n,k)= c(n-1,k-1)+(n-1)c(n-1,k)$ where S(0,0)=1,S(n,0)=S(0,n)=0

- Stirling Number of Second kind: Number of ways to partition n labeled items into exactly k non-empty unlabeled subsets: $S(n,k) = kS(n-1,k)+S(n-1,k-1)$ where S(0,0)=1,S(n,0)=S(0,n)=0

- r-Associated Stirling number of second kind: Each set must have at least $r$ elements: $S_r(n+1,k) = kS_r(n,k)+\binom{n}{r-1}S_r(n-r+1,k-1)$

- Ways to Distribute n labeled items into k labeled boxes: $T(n,k)=k(T(n-1,k-1)+T(n-1,k)=k!\times S(n,k)$

- Partitions of $n$ identical items into $k$ non-empty parts: $p(n,k) = p(n-1,k-1)+p(n-k,k)$ For example, p(4,2)=2 [2+2,1+3].

- If each of $k$ non-empty parts must have at least $r$ elements (Each number must be at least r), $p_r(n,k)=p(n-(r-1)k,k)$

- If all k parts have to be unique, $p^*(n,k)=p\!\left(n-\binom{k}{2},k\right)$. For example, $p^*(4,2)=p(3,2)=1$ [1+3]

- $g_k= \frac{k(3k-1)}{2}$ for $k=1,-1,2,-2,3,\cdots$ are called (generalized) pentagonal numbers. $p(n)=p(n-1)+p(n-2)-p(n-5)-p(n-7)+\cdots=\sum_{k=1}^np(n,k)$ [2 positives, 2 negatives repeat] where p(n) is the number of partitions of n into any size. p(4) = 5 (4,3+1,2+2,1+1+2,1+1+1+1)

## Inversions

- If $P(n)=\sum_{k=0}^{n} \binom{n}{k} Q(k)$, then $Q(n)=\sum_{k=0}^{n} (-1)^{n-k} \binom{n}{k} P(k)$

- If $P(n)=\sum_{k=0}^{n} (-1)^k \binom{n}{k} Q(k)$, then $Q(n)=\sum_{k=0}^{n} (-1)^k \binom{n}{k} P(k)$

- If $f(n)=\sum_{d \mid n} g(d)$, then $g(n)=\sum_{d \mid n} \mu(d)\, f\!\left(\dfrac{n}{d}\right)$

## LTE (Lifting the Exponent)

- **LTE Basic Form (odd p):** $v_p(x^n - y^n) = v_p(x-y) + v_p(n)$, where $p \mid (x-y)$, $p \nmid xy$, and $p$ is odd.

- **LTE for sum when p divides x+y:** $v_p(x^n + y^n) = v_p(x+y) + v_p(n)$, where $n$ is odd, $p \mid (x+y)$, $p \nmid xy$, and $p$ is odd.

- **LTE for p=2, odd difference:** $v_2(x^n - y^n) = v_2(x-y) + v_2(x+y) + v_2(n) - 1$, where $x$ and $y$ are odd.

- **LTE for p=2, sum case:** $v_2(x^n + y^n) = v_2(x+y) + v_2(n)$, where $x$ and $y$ are odd and $n$ is odd.

- **LTE for x=y+k:** $v_p((y+k)^n - y^n) = v_p(k) + v_p(n)$, if $p \mid k$ and $p \nmid y$.

- **Consequence (special):** $v_p(a^p - b^p) = v_p(a-b) + 1$, for odd prime $p$ dividing $a-b$.

- **Consequence (power):** $v_p(x^{p^k} - y^{p^k}) = v_p(x-y) + k$, for odd prime $p$ dividing $x-y$.
