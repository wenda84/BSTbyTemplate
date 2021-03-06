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
     * ??????????????????????????????
     * @param root ?????????
     * @return ????????????????????????
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
     * ??????????????????????????????????????????????????????????????????????????????????????????????????????root????????????
     * @param root  ??????????????????
     */
    /* ????????????????????????CSDN blog
    https://blog.csdn.net/weixin_41990671/article/details/108885298/
    */
    template<typename t_value>
    void bstTree<t_value>::printTree_wrap(bstTree<t_value>* root) 
    {
        if (!root)return;
        auto tmp = root;
        std::vector<bstTree *> intv = inorderTraversal(tmp);//????????????????????????
        std::string template_str;//??????string?????????????????????string?????????
        int location = 0;
        std::unordered_map<bstTree *, int> first_locations;//???????????????????????????string???????????????
        for (auto &i : intv) {
            location = template_str.size();
            template_str += std::to_string(i->value) + " ";
            first_locations[i] = location;
        }

        for (auto &i:template_str)i = ' ';//?????????????????????????????????????????????
        
        //????????????
        std::queue<bstTree *> q;
        q.push(root);
        while (!q.empty()) {
            int currentLevelSize = q.size();
            int cur_loc = 0;
            std::string tmp_str1 = template_str, tmp_str2 = template_str;//1?????????????????????2???????????????
            for (int i = 1; i <= currentLevelSize; ++i) {
                auto node = q.front();
                q.pop();
                cur_loc = first_locations[node];
                std::string num_str = std::to_string(node->value);
                //?????????????????????????????????????????????????????????????????????'/'?????????????????????'_'
                if (node->left) {
                    q.push(node->left);
                    int first_loc = first_locations[node->left] + 1;
                    tmp_str2[first_loc++] = '/';
                    while (first_loc < cur_loc)tmp_str1[first_loc++] = '_';
                }
                //??????,??????????????????????????????????????????????????????
                for (int j = 0; j < num_str.length(); ++j, ++cur_loc) {
                    tmp_str1[cur_loc] = num_str[j];
                }
                //?????????????????????????????????????????????????????????????????????'\'?????????????????????'_'
                if (node->right) {
                    q.push(node->right);
                    int last_loc = first_locations[node->right] - 1;
                    tmp_str2[last_loc] = '\\';
                    while (cur_loc < last_loc) {
                        tmp_str1[cur_loc++] = '_';
                    }
                }
            }
            //????????????
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