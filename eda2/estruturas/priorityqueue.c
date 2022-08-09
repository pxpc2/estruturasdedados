typedef int Item;
#define key(A) (A)
#define less(A, B) ( key(A) < key(B) )
#define exch(A, B) { Item temp = A; (A) = B; (B) = temp; }
#define cmpexch(A, B) { if (less(B,A)) exch(A, B) }

