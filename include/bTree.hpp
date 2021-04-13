#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <queue>

namespace bTree{
    template<typename t_value>

    class bstTree
    {
    private:
        t_value value;
        bstTree* left;
        bstTree* right;

        bstTree* insert_value_wrap(bstTree* p_cur_node, t_value p_value);
        std::vector<bstTree *> inorderTraversal(bstTree *root);
        void   printTree_wrap(bstTree *root) ;
        bstTree* min_wrap(bstTree*);
        bstTree* max_wrap(bstTree*);

        bstTree* getByValue_wrap(bstTree* p_cur_node, t_value p_value);
        void   destroyTreeNode(bstTree* p_cur_node);

    public:
        bstTree(t_value value) : value(value), left(nullptr), right(nullptr) {}
        ~bstTree();

        bstTree* insert_value(t_value p_value);
        void printTree();

        t_value min();
        t_value max();
        bstTree* getByValue(t_value p_value);
    };

    template<typename t_value>
    bstTree<t_value>::~bstTree(){
       destroyTreeNode(this);
    }

    template<typename t_value>
    void bstTree<t_value>::destroyTreeNode(bstTree<t_value>* p_cur_node){
        if(p_cur_node->left){
            destroyTreeNode(p_cur_node->left);
            // std::cout << "now destroy node:" << p_cur_node->left->value << std::endl; 
            delete(p_cur_node->left);
            p_cur_node->left = nullptr;
        }

        if(p_cur_node->right){
            destroyTreeNode(p_cur_node->right);
            // std::cout << "now destroy node:" << p_cur_node->right->value << std::endl; 
            delete(p_cur_node->right);
            p_cur_node->right = nullptr;
        }
    }

    template<typename t_value>
    bstTree<t_value>* bstTree<t_value>::insert_value_wrap(bstTree<t_value>* p_cur_node, t_value insert_value)
    {
        if( nullptr == p_cur_node)
            return nullptr;

        if(insert_value == p_cur_node->value)
            return nullptr;
        
        if(insert_value > p_cur_node->value) {
            if(p_cur_node->right == nullptr)  {
                p_cur_node->right = new bstTree(insert_value);
            }
            else {
                return insert_value_wrap(p_cur_node->right, insert_value);
            }
        }
        else {
            if(p_cur_node->left == nullptr) {
                p_cur_node->left = new bstTree(insert_value);
            }        
            else {
                return insert_value_wrap(p_cur_node->left, insert_value);    
            }
        }
    }

    template<typename t_value>
    bstTree<t_value>* bstTree<t_value>::insert_value(t_value insert_value)
    {
        return insert_value_wrap(this, insert_value);
    }

    /**
     * 中序遍历返回节点数组
     * @param root 根节点
     * @return 中序遍历节点数组
     */
    template<typename t_value>
    std::vector<bstTree<t_value> *> bstTree<t_value>::inorderTraversal(bstTree<t_value> *root) {
        std::vector<bstTree *> res;
        std::stack<bstTree *> stk;

        while (root != nullptr || !stk.empty()) {
            while (root != nullptr) {
                stk.push(root);
                root = root->left;
            }

            root = stk.top();
            stk.pop();
            res.push_back(root);
            root = root->right;
        }
        return res;
    }

    /**
     * 利用下划线和正反斜杠打印出美观的二叉树，没有破坏二叉树结构，但传入的root会有变化
     * @param root  二叉树根节点
     */
    /* 该函数实现引用自CSDN blog
    https://blog.csdn.net/weixin_41990671/article/details/108885298/
    */
    template<typename t_value>
    void bstTree<t_value>::printTree_wrap(bstTree<t_value>* root) 
    {
        if (!root)return;
        auto tmp = root;
        std::vector<bstTree *> intv = inorderTraversal(tmp);//中序遍历节点数组
        std::string template_str;//模板string，表示每行打印string的长度
        int location = 0;
        std::unordered_map<bstTree *, int> first_locations;//存储节点对应在本行string中的首位置
        for (auto &i : intv) {
            location = template_str.size();
            template_str += std::to_string(i->value) + " ";
            first_locations[i] = location;
        }

        for (auto &i:template_str)i = ' ';//把模板全部置为空格方便后续使用
        
        //层序遍历
        std::queue<bstTree *> q;
        q.push(root);
        while (!q.empty()) {
            int currentLevelSize = q.size();
            int cur_loc = 0;
            std::string tmp_str1 = template_str, tmp_str2 = template_str;//1为节点所在行，2为其下一行
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                cur_loc = first_locations[node];
                std::string num_str = std::to_string(node->value);
                //左边，如果存在左孩子，那么在第二行对应位置打印'/'，在第一行补上'_'
                if (node->left) {
                    q.push(node->left);
                    int first_loc = first_locations[node->left] + 1;
                    tmp_str2[first_loc++] = '/';
                    while (first_loc < cur_loc)tmp_str1[first_loc++] = '_';
                }
                //中间,对应位置打印节点值（有可能为多位数）
                for (int j = 0; j < num_str.length(); ++j, ++cur_loc) {
                    tmp_str1[cur_loc] = num_str[j];
                }
                //右边，如果存在右孩子，那么在第二行对应位置打印'\'，在第一行补上'_'
                if (node->right) {
                    q.push(node->right);
                    int last_loc = first_locations[node->right] - 1;
                    tmp_str2[last_loc] = '\\';
                    while (cur_loc < last_loc) {
                        tmp_str1[cur_loc++] = '_';
                    }
                }
            }
            //打印两行
            std::cout << tmp_str1 << std::endl;
            std::cout << tmp_str2 << std::endl;
        }
    }   

    template<typename t_value>
    void bstTree<t_value>::printTree()  {   
        printTree_wrap(this);
    }

    template<typename t_value>
    bstTree<t_value>* bstTree<t_value>::min_wrap(bstTree<t_value>* p_cur_node)    {
        if(p_cur_node->left == nullptr)
            return p_cur_node;

        return min_wrap(p_cur_node->left);
    }

    template<typename t_value>
    bstTree<t_value>* bstTree<t_value>::max_wrap(bstTree<t_value>* p_cur_node)    {
        if(p_cur_node->right == nullptr)
            return p_cur_node;

        return max_wrap(p_cur_node->right);
    }

    template<typename t_value>
    t_value bstTree<t_value>::min()    {
        return min_wrap(this)->value;
    }

    template<typename t_value>
    t_value bstTree<t_value>::max()    {
        return max_wrap(this)->value;
    }
    
    template<typename t_value>
    bstTree<t_value>* bstTree<t_value>::getByValue_wrap(bstTree<t_value>* p_cur_node, t_value in_value)    {
        if(nullptr == p_cur_node)
            return nullptr;

        if(in_value > p_cur_node->value)        {
            return getByValue_wrap(p_cur_node->right, in_value);
        }
        else if(in_value < p_cur_node->value)     {
            return getByValue_wrap(p_cur_node->left, in_value);
        }
        else {
            return p_cur_node;
        }
    }

    template<typename t_value>
    bstTree<t_value>*  bstTree<t_value>::getByValue(t_value value)    {
        return getByValue_wrap(this, value);
    }

}