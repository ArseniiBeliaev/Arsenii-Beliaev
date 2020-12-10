#include <iostream>

void acceleeration() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);
    std::cout.tie(0);
}

struct Node {// Так же как и в предыдущей задаче, можно было бы запрятать Node в класс splayTree
    Node() = default;
    Node* parent = nullptr ;
    Node* left = nullptr ;
    Node* right = nullptr;
    char inf; // информация о родителе
    long long sumTree = 0;
    long long key = 0;

    Node(long long value , Node* par , char infPar ) {
        inf = infPar;
        key = value;
        parent = par;
        sumTree = value;
    }
};

class splayTree {
    Node *root = nullptr;

    void insert(long long value, Node *&node) {
        if (node == nullptr) {
            node = new Node(value, nullptr , '0');
        } else {
            Node *nodeChild = node;
            Node *nodeParent = node;
            bool flag = true;
            while (flag) {
                if (nodeChild != nullptr) {
                    if (nodeChild->key > value) {
                        nodeParent = nodeChild;
                        nodeParent->sumTree+=value; // Прибавить к отцу value
                        nodeChild = nodeChild->left;
                    } else if (nodeChild->key < value) {
                        nodeParent = nodeChild;
                        nodeParent->sumTree+=value; // Прибавить к отцу value
                        nodeChild = nodeChild->right;
                    } else if (nodeChild->key == value) {
                        splay(nodeChild);
                        flag = false;
                    }
                } else {
                    if (nodeParent->key > value) {
                        nodeChild = new Node(value, nodeParent , 'l');
                        nodeParent->left = nodeChild;
                        splay(nodeChild);
                        flag = false;
                    }

                    if (nodeParent->key < value) {
                        nodeChild = new Node(value, nodeParent, 'r');
                        nodeParent->right = nodeChild;
                        splay(nodeChild);
                        flag = false;
                    }

                }
            }
        }
    }

    void splay(Node*& node) {
        bool flag = true;
        while (flag) {
            if (node->parent== nullptr) {
                flag = false;
            }
            else {
                Node* nodePar = node->parent;
                if (nodePar->parent== nullptr) {
                    zig(node,nodePar);
                    root = node;
                }
                else {
                    Node* nodeDed = nodePar->parent;
                    if (node->inf == nodePar->inf) {
                        zig_zig(nodeDed,nodePar,node);
                        if ( node->parent == nullptr ) {
                            root = node;
                        }
                    }
                    else {
                        zig_zag(nodeDed,nodePar,node);
                        if ( node->parent == nullptr ) {
                            root = node;
                        }
                    }
                }
            }
        }
    }

    void zig(Node*& nodeChild, Node*& nodePar) {
        if (nodeChild->inf == 'l' ) {
            rotationRight(nodeChild,nodePar);
        }
        if (nodeChild->inf == 'r') {
            rotationLeft(nodeChild,nodePar);
        }
    }

    void zig_zig (Node*& nodeDed,Node*& nodePar,Node*& nodeChild) {
        if ((nodeChild->inf == nodePar->inf) && (nodePar->inf == 'l')) {
            rotationRight(nodeChild,nodePar);
            rotationRight(nodeChild,nodeDed);
        }
        if ((nodeChild->inf == nodePar->inf) && (nodePar->inf == 'r')) {
            rotationLeft(nodeChild,nodePar);
            rotationLeft(nodeChild,nodeDed);
        }
    }
    void zig_zag (Node*& nodeDed,Node*& nodePar,Node*& nodeChild) {
        if ( (nodeChild)->inf == 'l'  &&  (nodePar)->inf == 'r' ) {
            rotationRight(nodeChild,nodePar);
            rotationLeft(nodeChild,nodeDed);
        }
        if ((nodeChild)->inf == 'r' && (nodePar)->inf == 'l' ) {
            rotationLeft(nodeChild,nodePar);
            rotationRight(nodeChild,nodeDed);
        }
    }


    void rotationRight(Node*& nodeChild, Node*& nodePar) {
        nodePar->left = nodeChild->right;
        if (nodeChild->right != nullptr) {
            (nodeChild->right)->inf = 'l';
            (nodeChild->right)->parent = nodePar;
        }
        nodeChild->right=nodePar;
        nodeChild->inf=nodePar->inf;
        nodePar->inf='r';
        nodeChild->parent=nodePar->parent;
        nodePar->parent=nodeChild;
        if (nodeChild->inf == 'l') {
            (nodeChild->parent)->left=nodeChild;
        }
        if (nodeChild->inf == 'r') {//А такой случай возможен??
            (nodeChild->parent)->right=nodeChild;
        }
        // Здесь изменение суммы в дереве ( магия ) (Попросите скинуть фото-инструкцию и все станет ясно :) )
        // Лучше бы ссылку оставил на фото инструкцию. Но и так понятно
        long long blue = nodePar->key;
        long long red = nodeChild->key;
        long long A = 0;
        long long B = 0;
        long long C = 0;
        if (nodeChild->left != nullptr ) {
            A = (nodeChild->left)->sumTree;
        }
        if (nodePar->left != nullptr ) {
            B = (nodePar->left)->sumTree;
        }
        if (nodePar->right != nullptr ) {
            C = (nodePar->right)->sumTree;
        }
        nodePar->sumTree = B + C + blue;
        nodeChild->sumTree = A + red + nodePar->sumTree;
        //=====================================================================================================
    }

    void rotationLeft(Node*& nodeChild, Node*& nodePar) {
        nodePar->right = nodeChild->left;
        if (nodeChild->left != nullptr) {
            (nodeChild->left)->inf = 'r';
            (nodeChild->left)->parent = nodePar;
        }
        nodeChild->left = nodePar;
        nodeChild->inf=nodePar->inf;
        nodePar->inf='l';
        nodeChild->parent = nodePar->parent;
        nodePar->parent = nodeChild;
        if (nodeChild->inf =='l') {// аналогично
            (nodeChild->parent)->left = nodeChild;
        }
        if (nodeChild->inf == 'r') {
            (nodeChild->parent)->right = nodeChild;
        }
        // Здесь изменение суммы в дереве ( магия ) (Попросите скинуть фото-инструкцию и все станет ясно :) )
        long long red = nodeChild->key;
        long long blue = nodePar->key;
        long long A =0;
        long long B =0;
        long long C =0;
        if (nodeChild->right != nullptr ) {
            C = (nodeChild->right)->sumTree;
        }
        if (nodePar->left != nullptr ) {
            A = (nodePar->left)->sumTree;
        }
        if (nodePar->right != nullptr ) {
            B = (nodePar->right)->sumTree;
        }
        nodePar->sumTree = blue + A + B;
        nodeChild->sumTree = C + red + nodePar->sumTree;
        //=======================================================================================================
    }

    Node* findMin(Node* node ) {//!!! после поиска элемента дерево должно его выводить в корень, иначе теряется смысл. Доделать
        if(node->left != nullptr) {
            return findMin(node->left);
        }
        else return node;
    }

    void del(long long value) {
        add(value);//Это вместо splay? А если такого элемента реально не было??
        Node* node_left  = root->left;
        Node* node_right = root->right;
        if (node_left!= nullptr) {
            (node_left)->parent = nullptr; //!!! просто присваивания nullptr не хватит, нужно освободить память по указателю, а это утечка
            (node_left)->inf = '0';
        }
        if (node_right!= nullptr) {
            (node_right)->parent = nullptr;
            (node_right)->inf = '0';
        }

        Node* min;
        if (node_right == nullptr) {
            min = nullptr;
        }
        else min = findMin(node_right);

        if ( min!= nullptr ) {
            splay(min);
            root = min;
            root->left = node_left;
            if ( node_left!= nullptr) {
                node_left->parent = root;
                node_left->inf = 'l';
            }
            root->sumTree = root->key;
            if (root->left != nullptr) {
                root->sumTree +=(root->left)->sumTree;
            }
            if (root->right != nullptr ) {
                root->sumTree += (root->right)->sumTree;
            }
        }
        else {
            root = node_left;
        }
    }


    void print(Node* node) {
        if (node != nullptr) {
            print(node->left);
            std::cout << node->key  << " " << "[" << node->sumTree << "]" << ' ';
            print(node->right);
        }
    }

    bool find(Node* node , long long value ) {
        if (node!= nullptr) {
            if (node->key > value) {
                return find(node->left,value);
            }
            if (node->key < value) {
                return find(node->right,value);
            }
            if (node->key == value ) {
                return true;
            }
        }// и вновь по хорошему после поиска элемента нужно помочь ему всплыть наверх
        else return false;
    }

    long long interval(long long left , long long right) {
        long long result=0;
        bool left_in = find(root,left);
        bool right_in = find(root,right);
        add(left);
        if (root->right != nullptr) {
            result+=(root->right)->sumTree;
        }
        add(right);
        //result-=root->key;
        if (root->right!= nullptr) {
            result-=(root->right)->sumTree;
        }
        if (right_in == true) {
            //result += right;
        }
        if (left_in == true ) {
            result += left;
        }
        if (right_in == false ) {
            //result-=root->key;
            del(right);
        }
        if (left_in == false) {
            del(left);
        }
        return result;
    }


public:

    void add(long long value) {
        insert(value,root);
    }

    void prt() {
        print(root);
    }
    void dlt(long long value) {
        del(value);
    }
    long long inter(long long left , long long right) {// print_interval_sum
        return  interval(left,right); // find_interval_sum
    }

 };

int main() {
    acceleeration();
    splayTree x;
    long long number;
    long long value_1;
    long long value_2;
    long long result;
    std::cin >> number;
    char command_old;
    char command_new;

    std::cin >> command_old;
    if (command_old == '+') {
        std::cin >> value_1;
        x.add(value_1);
    }
    if (command_old == '?') {
        std::cin >> value_1 >> value_2;
        result = x.inter(value_1,value_2);
    }
    for (long long i = 0; i < number - 1; ++i ) {
        std::cin>>command_new;
        if (command_new == '+') {
            std::cin>>value_1;
            if (command_old == '?') {
                value_1 = (value_1 + result ) % 1'000'000'000;// 1e9
                x.add(value_1);
            }
            else {
                x.add(value_1);
            }
        }
        if (command_new == '?' ) {
            std::cin >> value_1 >> value_2;
            result = x.inter(value_1,value_2);
            std::cout << result << '\n';
        }
        command_old = command_new;
    }

    return 0;
}


