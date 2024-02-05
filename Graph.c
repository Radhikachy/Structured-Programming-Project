
//Code title : Finding out the Paths with essential nodes.
//Author : Radhika Chowdhury, Undergrduate student, Khulna University.
//Student id : 220239.
//N.B.: This code doesn't work only for trees which have more than 10 adjacent nodes.
#include <stdio.h>
int pathCount = 0;
struct Node {
    int pathOccurence;
    int nodeid;
    int adjcount;
    int adjs[10];
    int costs[10];
};

int addNode (struct Node * p, int nid, int count) {
    int i = 0, ncount = count;
    for (i = 0; i < count; ++i) {
        if (p[i].nodeid == nid)
            break;
    }
    if (i == count) {
        p[i].pathOccurence = 0;
        p[i].nodeid = nid;
        p[i].adjcount = 0;
        ncount++;
    }
    return ncount;
}

void addAdjacent (struct Node *p, int nid1, int nid2, int cost, int count) {
    //This adds the adjacent nodes to each nodes.
    int i =0;
    for (i = 0; i < count; ++i) {
        if (p[i].nodeid == nid1) {
            int c = p[i].adjcount;
            p[i].adjs[c] = nid2;
            p[i].costs[c] = cost;
            p[i].adjcount = c+1;
            break;
        }
    }
}
//Now the nodeid is checked;
int added (int * list, int lcount, int nid) {
    int i = 0;
    for (i = 0; i < lcount; ++i) {
        if (list[i] == nid)
            return 1;
    }
    return 0;
}
//this function findpath is used to get the paths
void findpath (struct Node * p, int count, int start, int end, int * list, int *clist, int lcount) {
    int index = 0, i = 0;

    //This has the condition to check whether the path has the end node
    if (list[lcount-1] == end) {
        pathCount++;
        int tcost = 0;
        for (i = 0; i < lcount; ++i) {
            for(int j = 0; j < count; j++) {
                if(p[j].nodeid == list[i])
                    p[j].pathOccurence++;
            }
            printf (" %d ", list[i]);
            tcost += clist[i];
        }
        printf (" cost = %d", tcost);
        printf ("\n");
        return;
    }
   
    for (i = 0; i < count; ++i) {
        if (p[i].nodeid == start) {
            index = i;
            break;
        }
    }
   
    for (i = 0; i < p[index].adjcount; ++i) {
        int a = added (list, lcount, p[index].adjs[i]);
        if (a == 0) {
            list[lcount] = p[index].adjs[i];
            clist[lcount] = p[index].costs[i];
            lcount++;
           
            findpath (p, count, p[index].adjs[i], end, list, clist, lcount);
            lcount--;
        }
    }
}

int main() {
    struct Node nodes[50];
    int nodecount = 0;
    int n1 = 0, n2 = 0, c = 0;
   
    while (1) {
        printf ("n1, n2, cost ? ");
        scanf("%d %d %d", &n1, &n2, &c);
        if (n1 == -9 || n2 == -9 || c== -9) {break;}
        nodecount = addNode (&nodes[0], n1, nodecount);
        nodecount = addNode (&nodes[0], n2, nodecount);
       
        addAdjacent (&nodes[0], n1, n2, c, nodecount);
        addAdjacent (&nodes[0], n2, n1, c, nodecount);
    }
   
    int start, end;
    printf ("start, end ? ");
    scanf ("%d %d", &start, &end);
    int list[50], clist[50], lcount = 0;
    list[0] = start; clist[0] = 0; lcount = 1;

    findpath (nodes, nodecount, start, end, list, clist, lcount);
    printf("The essential nodes are as follows :\n");
    for (int i = 0; i < nodecount; ++i) {
        if ((nodes[i].nodeid != start) && (nodes[i].nodeid != end)) {
            if(nodes[i].pathOccurence == pathCount)
                printf("%d ", nodes[i].nodeid);
        }
    }
    return 0;
}