typedef struct PQst;
typedef int Item;

void initPQ(int max_N, struct PQst *pq);

int isEmpty(struct PQst *pq);

int getSize(struct PQst *pq);

void insert(Item v, struct PQst *pq);

Item removeMax(struct PQst *pq);

void swim(Item *pq, int k);

void sink(Item *pq, int k, int l);  