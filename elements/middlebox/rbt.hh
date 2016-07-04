#ifndef MIDDLEBOX_RBT_HH
#define MIDDLEBOX_RBT_HH

CLICK_DECLS

class RBTManager;

typedef struct rb_red_blk_node {
    void* key;
    void* info;
    int red; /* if red=0 then the node is black */
    struct rb_red_blk_node* left;
    struct rb_red_blk_node* right;
    struct rb_red_blk_node* parent;
} rb_red_blk_node;

typedef struct rb_red_blk_tree {
    RBTManager* manager;
    /*  A sentinel is used for root and for nil.  These sentinels are */
    /*  created when RBTreeCreate is called.  root->left should always */
    /*  point to the node which is the root of the tree.  nil points to a */
    /*  node which should always be black but has aribtrary children and */
    /*  parent and no key or info.  The point of using these sentinels is so */
    /*  that the root and nil nodes do not require special cases in the code */
    rb_red_blk_node* root;
    rb_red_blk_node* nil;
} rb_red_blk_tree;


/*
 * This abstract class is used to define the behaviour of a RBT manager.
 * The manager must take care of memory management as well as provide
 * methods to handle the objects managed by the tree.
 */
class RBTManager
{
public:
    // Compare(a,b) should return 1 if *a > *b, -1 if *a < *b, and 0 otherwise
    virtual int compareKeys(const void*, const void*) = 0;
    virtual void printKey(const void*) = 0;
    virtual void printInfo(void*) = 0;

    virtual rb_red_blk_node* allocateNode(void)
    {
        return (rb_red_blk_node*)malloc(sizeof(rb_red_blk_node));
    }

    virtual rb_red_blk_tree* allocateTree(void)
    {
        return (rb_red_blk_tree*) malloc(sizeof(rb_red_blk_tree));
    }

    virtual void freeTree(rb_red_blk_tree* tree)
    {
        free(tree);
    }

    virtual void freeNode(rb_red_blk_node* node)
    {
        free(node);
    }

    virtual void freeKey(void* key)
    {
        free(key);
    }

    virtual void freeInfo(void* info)
    {
        free(info);
    }
};

rb_red_blk_tree* RBTreeCreate(RBTManager*);
rb_red_blk_node * RBTreeInsert(rb_red_blk_tree*, void* key, void* info);
void RBTreePrint(rb_red_blk_tree*);
void RBDelete(rb_red_blk_tree*, rb_red_blk_node*);
void RBTreeDestroy(rb_red_blk_tree*);
rb_red_blk_node* TreePredecessor(rb_red_blk_tree*, rb_red_blk_node*);
rb_red_blk_node* TreeSuccessor(rb_red_blk_tree*, rb_red_blk_node*);
rb_red_blk_node* RBExactQuery(rb_red_blk_tree*, void*);
rb_red_blk_node* RBFindElementGreatestBelow(rb_red_blk_tree*, void*);
rb_red_blk_node* RBMin(rb_red_blk_tree* tree);
rb_red_blk_node* RBMax(rb_red_blk_tree* tree);
void RBPrune(rb_red_blk_tree*, void*);

CLICK_ENDDECLS

#endif
