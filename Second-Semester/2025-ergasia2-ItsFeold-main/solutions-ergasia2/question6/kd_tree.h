#ifndef KD_TREE_H
#define KD_TREE_H
#include "point.h"
#include "range.h"
#include "linked_list.h"

// Typedef for node type
typedef enum node_type {VERTICAL_LINE, HORIZONTAL_LINE, LEAF_NODE} NodeType;

// Definition of KD-Tree node: 
typedef struct kdnode {
    // The point stored in this node only for leaf nodes
    Point *point;
    // Value for line - NULL on leaf nodes
    int *line;

    // VERTICAL_LINE if Vertical Line (x-axis)
    // HORIZONTAL_LINE if Horizontal Line(y-axis)
    // LEAF_NODE if Leaf Node
    NodeType type;

    struct kdnode *left; // Left subtree
    struct kdnode *right; // Right subtree
} KDNode;


// Function to create a KDNode
KDNode* kdnode_init(Point *p, int *line, NodeType type);


// Function to build a kd tree
// Point **points : An array of points
// int n: The size of array points
// int depth: Depth of the current level. Should ALWAYS be 0 when calling this function
KDNode* buildKDTree(Point **points, int n, int depth);


// Function search for points inside a given range.
// You are free to use any code for the List
// KDNode *root : The tree’s root
// Range *range: The query range
// Range *region: the region of the current node i.e
// region(v). When calling this function initialize a
// Range object with xmin = INT_MIN, xmax = INT_MAX,
// ymin = INT_MIN, ymax = INT_MAX
// List *l: List to store the results
List searchKDTree(KDNode *root, Range *range, Range *region, List l);

// Function to add all points of a region into list
List reportSubtree(KDNode* tree, List l);
 
// Function to destroy a KDTree
void destroyKDTree(KDNode *root);

// Function to print a KDTree (in-order)
void print_tree(KDNode* tree);

#endif