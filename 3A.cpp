#include <iostream>
long long const INF = 1e18;
void acceleeration() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
}
struct Node {
    Node* left;
    Node* right;
    long long key;
    long long height;
    Node ( long long x ) {
        key = x;
        left = NULL;
        right = NULL;
        height = 1;
    }
};
class BiBaTree {
    Node* root = NULL ;
 
    long long fixHeight(Node* node) {
 
        if (( node->right == NULL ) && ( node->left == NULL )) {
            return 1;
        }
        if (( node->right == NULL ) && ( node->left != NULL )) {
            return (node->left)->height + 1;
        }
        if (( node->right != NULL ) && ( node->left == NULL )) {
            return (node->right)->height + 1;
        }
        if (( node->right != NULL ) && (node->left != NULL )) {
            return std::max( (node->left)->height,(node->right)->height ) + 1;
        }
    }
    Node* rotationRight(Node* node) {
        Node* swp = node->left;
        node->left = swp->right;
        swp->right = node;
        node->height = fixHeight(node);
        swp->height = fixHeight(swp);
        return swp;
    }
    Node* rotationLeft(Node* node) {
        Node* swp = node->right;
        node->right = swp->left;
        swp->left = node;
        node->height = fixHeight(node);
        swp->height = fixHeight(swp);
        return swp;
    }
    Node* min(Node* node) {
        if (node->left != NULL ) {
            min(node->left);
        }
        else {
            return node;
        }
    }
    Node* delMin(Node* node) {
        if ( node->left == NULL ) {
            return node->right;
        }
        else {
            node->left =  delMin(node->left);
        }
        return balance(node);
    }
    long long balanceDiff (Node* node) {
        long long  rez;
        if (( node->left == NULL ) && (node->right == NULL )) {
            rez = 0;
        }
        if ((node->left != NULL) && (node->right == NULL )) {
            rez = 0 - (node->left)->height;
        }
        if ((node->left == NULL) && (node->right != NULL )) {
            rez = (node->right)->height - 0;
        }
        if ((node->left != NULL) && (node->right != NULL )) {
            rez = (node->right)->height - (node->left)->height;
        }
        return rez;
    }
    Node* balance(Node* node) {
        node->height = fixHeight(node);
        long long diff = balanceDiff(node);
        if (diff == 2) {
            if (balanceDiff(node->right) < 0) {
                node->right = rotationRight(node->right);
            }
            return rotationLeft(node);
        }
        if (diff == -2 ) {
            if (balanceDiff(node->left) > 0 ) {
                node->left = rotationLeft(node->left);
            }
            return rotationRight(node);
        }
        return node;
    }
    Node* insert(long  long value , Node* node) {
 
        if ( node == NULL ) {
            node = new Node(value);
            return node;
        }
        else {
            if ( value > node->key ) {
                node->right = insert(value , node->right);
            }
            if ( value < node->key ) {
                node->left = insert(value , node->left );
            }
        }
        return balance(node); // здесь вызовем баланс дерево , чтобы все было
    }
    Node* del(long long value , Node* node ) {
        if ( node!=NULL ) {
            if (value > node->key ) {
                node->right = del(value , node->right );
            }
            else if (value < node->key ) {
                node->left =  del(value , node->left );
            }
            else if ( value == node->key ) {
                Node* l = node->left;
                Node* r = node->right;
                delete node;
                if ( r == NULL ) {
                    return l;
                }
                Node* swp = min(r);
 
                swp->right = delMin(r);
                swp->left = l;
                return balance(swp);
            }
        }
        else {
            return NULL;
        }
        return balance(node);
    }
    void print(Node* node) {
        if (node != NULL ) {
            print(node->left);
            std::cout << node->key << " [" << node->height << "] " << " ";
            print(node->right);
        }
 
    }
    void  downL (Node* node , long long value ) {
        if (node != NULL ) {
            downL(node->left,value);
            if (node->key > value) {
                std::cout << node->key;
            }
        }
    }
    long long  next ( long long val , Node* node ) {
        if ( node==NULL ) {
            return INF;
        }
        if ( node->key == val )
            return val;
        else if ( node->key > val )
            return std::min(node->key, next(val, node->left));
        else
            return next(val, node->right);
    }
    long long prev ( long long val , Node* node ) {
        if ( node == NULL ) {
            return -INF;
        }
        if (node->key == val ) {
            return val;
        }
        else if ( node->key > val ) {
            return prev(val , node->left );
        }
        else
            return std::max(node->key,prev(val,node->right));
    }
    bool exists(long long value , Node* node ) {
        if ( node == NULL )
            return false;
        if (node->key == value )
            return true;
        if (node->key > value )
            return exists(value, node->left);
        else
            return exists(value, node->right);
    }
public:
    void add(long long x) {
        root = insert(x,root);
    }
    void kick(long  long x) {
        root = del(x,root);
    }
    void prt() {
       print(root);
    }
    void nxt(long long x) {
        long long rez = next(x+1,root);
        if ( rez == INF ) std::cout << "none" << '\n';
        else std::cout << rez << '\n';
    }
    void prv(long long x) {
        long long rez = prev(x-1,root);
        if ( rez == -INF ) std::cout << "none" << '\n';
        else std::cout << rez << '\n';
    }
    void ex(long long x) {
         std::cout << (exists(x,root)? "true":"false") << '\n';
    }
};
 
int main() {
    acceleeration();
    BiBaTree tree;
    std::string s;
    while (std::cin >> s) {
        long long value;
        if ( s == "insert" ) {
            std::cin >> value;
            tree.add(value);
        }
        if (s == "delete" ) {
            std::cin >> value;
            tree.kick(value);
        }
        if ( s == "exists" ) {
            std::cin >> value;
            tree.ex(value);
        }
        if ( s == "next" ) {
            std::cin >> value;
            tree.nxt(value);
        }
        if ( s == "prev") {
            std::cin >> value;
            tree.prv(value);
        }
    }
 
    return 0;
}

