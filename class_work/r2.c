// бинарное дерево
struct  TreeNode
{
    TypeData data;
    struct TreeNode *pleft;
    struct TreeNode *pright;
};

struct TreeNode *root;

// двоичное дерево(бинарное) поиска это когда слева меньше, а справа больше
// асимпототика дерева - логарифмическая

void WalkTree (struct TreeNode *root)
{
    if (root == NULL)
    {
        return; 
    }
    WalkTree(*root->pleft);
    printf("\n", root->data);
    WalkTree(*root->pright)
};

void Seatch