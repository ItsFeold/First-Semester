#include "kd_tree.h"
#include <stdlib.h>
#include <stdio.h>

// Function to create a KDNode
KDNode* kdnode_init(Point *p, int *line, NodeType type) {
    KDNode* node = malloc(sizeof(KDNode));
    if(!node) {
        fprintf(stderr, "Failed to allocate KD-Node memory!\n");
        return NULL;
    }
    // Copy values 
    node->point = p;
    node->line = line;
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to build a kd tree
KDNode* buildKDTree(Point **points, int n, int depth) {
    if(n == 0) { // Failsafe check
        fprintf(stderr, "Point with size 0!\n");
        return NULL;
    } 
    if(n == 1)  // Base case: return leaf node with point
        return kdnode_init(points[0], NULL, LEAF_NODE);
    
    // Initialize members of new node
    KDNode* left = NULL;
    KDNode* right = NULL;
    NodeType type; 
    // Allocate line memory (deallocated at destroyKDtree)
    int *line = malloc(sizeof(int));
    if(!line) {
        fprintf(stderr, "Failed to allocate line memory!\n");
        return NULL;
    }

    // Function pointer for comparison function
    int (*compar)(const void *, const void *);

    // Change node type and comparison function based on depth 
    type = (depth % 2 == 0) ? VERTICAL_LINE : HORIZONTAL_LINE;
    compar = (depth % 2 == 0) ? point_compare_x : point_compare_y;

    // Sort array based on x coordinate
    qsort(points, n, sizeof(Point*), compar);

    // Index for median and size for subsets
    int mid = (n % 2 == 0) ? (n/2 - 1) : (n/2);
    int p1_size = (n % 2 == 0) ? (n/2) : (n/2 + 1);
    int p2_size = n - p1_size;

    // Get line value (median)
    *line = (depth % 2 == 0) ? points[mid]->x : points[mid]->y; 

    // Make first (left) subset p1 
    Point** p1 = malloc(p1_size*sizeof(Point*));
    if(!p1) {
        fprintf(stderr, "Failed to allocate p1 memory!\n");
        return NULL;
    } 
    for(int i=0; i<=mid; i++)
        p1[i] = points[i];

    // Make second (right) subset p2 
    Point** p2 = malloc(p2_size*sizeof(Point*));
    if(!p2) {
        fprintf(stderr, "Failed to allocate p1 memory!\n");
        return NULL;
    }
    int count = 0;
    for(int i=mid+1; i<n; i++) { 
        p2[count] = points[i];
        count++;
    }
    // Get left and right subtrees recursively   
    left = buildKDTree(p1, p1_size, depth+1);
    right = buildKDTree(p2, p2_size, depth+1);
    
    // Deallocate array memory
    free(p1);
    free(p2);
    KDNode* new = kdnode_init(NULL, line, type);
    new->left = left;
    new->right = right;
    return new;

}

// Function to add all points of a region into list
List reportSubtree(KDNode* tree, List l) { 
    // Base case: return point
    if (tree->type == LEAF_NODE) {
        AddFirst(l, tree->point);
        return l;
    }
    // Search for leafs in other subtrees
    l = reportSubtree(tree->left, l);
    l = reportSubtree(tree->right, l);
    return l;
}

// Function to search KDTree (returns list of points)
List searchKDTree(KDNode *root, Range *range, Range *region, List l) { 
    // Base case 1: Leaf node && 
    if (root->type == LEAF_NODE) {
        if(point_in_range(root->point, range))
            AddFirst(l, root->point);
        return l;
    }
    // Get intersection of region and line (plane of left child, lc(v))
    Range* rleft = range_init(0, 0, 0, 0);
    *rleft = *region;   // Copy current region
    // Intersection logic
    if(root->type == VERTICAL_LINE) 
        rleft->xmax = *(root->line);    
    else if(root->type == HORIZONTAL_LINE)
        rleft->ymax = *(root->line);
    
    // If the plane is within the range query, return all points
    if(range_contains(range, rleft)) 
        l = reportSubtree(root->left, l);
    // Otherwise, keep searching in new range
    else if(range_intersect(rleft, range)) 
        l = searchKDTree(root->left, range, rleft, l);

    // Get intersection of region and line (plane of right child, rc(v))
    Range *rright = range_init(0, 0, 0, 0);
    *rright = *region;  // Copy current region
    // Intersection logic
    if(root->type == VERTICAL_LINE)
        rright->xmin = *(root->line);
    else if(root->type == HORIZONTAL_LINE)
        rright->ymin = *(root->line);

    // If the plane is within the range query, return all points
    if(range_contains(range, rright))  
        l = reportSubtree(root->right, l);
        
    // Otherwise, keep searching in new range
    else if(range_intersect(rright, range)) 
        l = searchKDTree(root->right, range, rright, l);

    // Deallocate memory for ranges
    free(rleft);
    free(rright);
    return l;
}

// Function to print KD Tree (in-order)
void print_tree(KDNode* tree) { 
    // Base case
    if (tree == NULL)
        return;
    // Print left
    print_tree(tree->left);

    // Print current
    if(tree->type == LEAF_NODE) {
        printf("Tree value: ");
        point_print(tree->point);
    } 
    else if(tree->type == VERTICAL_LINE) 
        printf("x = %d\n", *(tree->line));
    else if(tree->type == HORIZONTAL_LINE) 
        printf("y = %d\n", *(tree->line));

    // Print right
    print_tree(tree->right);
    return;
}

// Function to destroy (deallocate memory) KD-Tree
void destroyKDTree(KDNode *root) { 
        // Base case
        if (root == NULL)
            return;
        // Destroy left subtree
        destroyKDTree(root->left);

        // Destroy right subtree
        destroyKDTree(root->right);

        // Destroy current
        free(root->line);
        free(root);
        return;
}