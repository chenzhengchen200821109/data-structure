#include "BTNode.h"

template<typename T>
class BTree
{
    public:
        BTree(int order = 3) : order_(order), size_(0)
        {
            root_ = new BTNode<T>;
        }
        ~BTree()
        {
            if (root_)
                delete root_;
        }
        int order() const { return order_; }
        int size() const { return size_; }
        BTNode<T>*& root() { return root_; }
        bool empty() const { return !root_; }
        BTNode<T>* search(const T& e);
        BTNode<T>* insert(const T& e);
        bool remove(const T& e);
    private:
        int size_;
        int order_;
        BTNode<T>* root_;
        BTNode<T>* hot_;
        void solveOverFlow(BTNode<T>* );
        void solveUnderFlow(BTNode<T>* );
};

template<typename T>
BTNode<T>* BTree<T>::search(const T& e)
{
    BTNode<T>* v = hot_ = root_;
    while (true) {
        if (!v)
            return v;
        int r = v->data.search(e);
        if ((0 <= r) && (e == v->data[r]))
            return v;
        hot_ = v;
        v = v->child_[r+1];
    }
}

template<typename T>
BTNode<T>* BTree<T>::insert(const T& e)
{
    BTNode<T>* v = search(e);
    if (v)
        return v;
    int r = hot_->data.search(e);
    hot_->data.insert(r+1, e);
    hot_->child_.insert(r+1, NULL);
    size_++;
    solveOverFlow(hot_);
    return v;
}

template<typename T>
bool BTree<T>::remove(const T& e)
{
    BTNode<T>* v = search(e);
    if (!v)
        return false;
    int r = v->data.search(e);
    if (v->child[0]) {
        BTNode<T>* u = v->child[r+1];
        while (u->child[0])
            u = u->child[0];
        v->data[r] = u->data[0];
        v = u;
        r = 0;
    }
    v->data.remove(r);
    v->child.remove(r);
    size_--;
    solveUnderFlow(v);
    return true;
}

template<typename T>
void BTree<T>::solveOverFlow(BTNode<T>* v)
{
    if (order_ >= v->child_.size()) return;
    int s = order_ / 2;
    BTNode<T>* u = new BTNode<T>();
    for (int j = 0; j < order_-s-1; j++) {
        u->child_.insert(j, v->child_.remove(s+1));
        u->child_.insert(j, v->child_.remove(s+1));
    }
    u->child_[order_-s-1] = v->child_.remove(s+1);
    if (u->child_[0]) {
        for (int j = 0; j < order_-s; j++)
            u->child_[j]->parent_ = u;
    }
    BTNode<T>* p = new BTNode<T>();
    p->child_[0] = v;
    v->parent_ = p;
    int r = 1 + p->data_.search(v->data_[0]);
    p->data_.insert(r, v->data_.remove(s));
    p->child_.insert(r+1, u);
    u->parent_ = p;
    solveOverFlow(p);
}

template<typename T>
void BTree<T>::solveUnderFlow(BTNode<T>* v)
{
	if ((order_ + 1) / 2 <= v->child_.size())
		return;
	BTNode<T>* p = v->parent_;
	if (!p) {
		if (!v->data_.size() && v->child_[0]) {
			root_ = v->child_[0];
			root_->parent_ = NULL;
			v->child_[0] = NULL;
			release(v);
		}
		return;
	}
	int r = 0;
	while (p->child_[r] != v)
		r++;
	// case 1
	if ( r > 0) {
		BTNode<T>* ls = p->child_[r-1];
		if ((order_ + 1) / 2 < ls->child_.size()) {
			v->data_.insert(0, p->data_[r-1]);
			p->data_[r-1] = ls->data_.remove(ls->data_.size() - 1);
			v->child_.insert(0, ls->child_.remove(ls->child_.size() - 1));
			if (v->child_[0])
				v->child_[0]->parent_ = v;
			return;
		}
	}
	// case 2
	if (p->child_.size() - 1 > r) {
		BTNode<T>* rs = p->child_[r+1];
		if ((order_ + 1) / 2 < rs->child_.size()) {
			v->data_.insert(v->data_.size(), p->data_[r]);
			p->data_[r] = rs->data_.remove(0);
			v->child_.insert(v->child_.size(), rs->child_.remove(0));
			if (v->child_[v->child_.size() - 1])
				v->child_[v->child_.size() - 1]->parent_ = v;
			return;
		}
	}
	// case 3
	if (0 < r) {
		BTNode<T>* ls = p->child_[r-1];
		ls->data_.insert(ls->child_.size(), p->data_.remove(r - 1));
		p->child_.remove(r);
		ls->child_.insert(ls->child_.size(), v->child_.remove(0));
		if (ls->child_[ls->child_.size() - 1])
			ls->child_[ls->child_.size() - 1]->parent_ = ls;
		while (!v->data_.empty()) {
			ls->data_.insert(ls->data_.size(), v->data_.remove(0));
			ls->child_.insert(ls->child_.size(), v->child_.remove(0));
			if (ls->child_[ls->child_.size() - 1])
				ls->child_[ls->child_.size() - 1]->parent_ = ls;
		}
		release();
	} else {
		BTNode<T>* rs = p->child_[r + 1];
		rs->data_.insert(0, p->data_.remove(r));
		p->child_.remove(r);
		rs->child_.insert(0, v->child_.remove(v->child_.size() - 1));
		if (rs->child_[0])
			rs->child_[0]->parent_ = rs;
		while (!v->data_.empty()) {
			rs->data_.insert(0, v->data_.remove(v->data_.size() - 1));
			rs->child_.insert(0, v->child_.remove(v->child_.size() - 1));
			if (rs->child_[0])
				rs->child_[0]->parent_ = rs;
		}
		release(v);
	}
	solveUnderFlow(p);
	return;
}
