#ifndef __RBTREE_H__
#define __RBTREE_H__

#include "BSTree.h"

#define IsBlack(p) (!(p) || (RB_BLACK == (p)->color_))
#define IsRed(p) (!IsBlack(p))
#define BlackHeightUpdated(x) ( \
	(stature((x).lChild_) == stature((x).rChild_)) && \
	((x).height_ == (IsRed(&x) ? stature((x).lChild_) : stature((x).lChild_) + 1)) \
)

template<typename T>
class RBTree : public BSTree<T>
{
	public:
		BinNode<T>* insert(const T& e);
		bool remove(const T& e);
		// BSTree::search()
	private:
		void solveDoubleRed(BinNode<T>* x);
		void solveDoubleBlack(BinNode<T>* x);
		int updateHeight(BinNode<T>* x);
};

template<typename T>
int RBTree<T>::updateHeight(BinNode<T>* x)
{
	x->height_ = max(stature(x->lChild_), stature(x->rChild_));
	return IsBlack(x) ? x->height_++ : x->height_;
}

template<typename T>
BinNode<T>* RBTree<T>::insert(const T& e)
{
	BinNode<T>* &x = search(e);
	if (x)
		return x;
	x = new BinNode<T>(e, hot_, NULL, NULL, -1);
	size_++;
	solveDoubleRed(x);
	return x;
}

template<typename T>
void RBTree<T>::solveDoubleRed(BinNode<T>* x)
{
	if (IsBlack(x))
		return;
	if (IsRoot(*x)) {
		root_->color_ = RB_BLACK;
		root_->height_++;
		return;
	}
	BinNode<T>* p = x->parent_;
	if (IsBlack(p) || IsRoot(*p))
		return;
	BinNode<T>* g = p->parent_;
	BinNode<T>* u = uncle(x);
	if (IsBlack(u)) {
		if (IsLChild_(*x) == IsLChild_(*p))
			p->color_ = RB_BLACK;
		else
			x->color_ = RB_BLACK;
		g->color_ = RB_RED;
		BinNode<T>* gg = g->parent_;
		BinNode<T>* r = FromParentTo(*g) = rotateAt(x);
		r->parent_ = gg;
	} else {
		p->color_ = RB_BLACK;
		p->height_++;
		u->color_ = RB_BLACK;
		u->height_++;
		IsRoot(*g) ? g->height_++ : g->color_ = RB_RED;
		solveDoubleRed(g);
	}
}

template<typename T>
bool RBTree<T>::remove(const T& e)
{
	BinNode<T>* &x = search(e);
	if (!x)
		return false;
	BinNode<T>* r = removeAt(x, hot_);
	if (0 >= --size_)
		return true;
	if (!hot_) {
		root_->color_ = RB_BLACK;
		updateHeight(root_);
		return true;
	}
	if (BlackHeightUpdated(*(hot_)))
		return true;
	if (IsRed(r)) {
		r->color_ = RB_BLACK;
		r->height_++;
		return true;
	}
	solveDoubleBlack(r);
	return true;
}

template<typename T>
void RBTree<T>::solveDoubleBlack(BinNode<T>* r)
{
	BinNode<T>* p = r ? r->parent_ : hot_;
	if (!p)
		return;
	BinNode<T>* s = (r == p->lChild_) ? p->rChild_ : p->lChild_;
	if (IsBlack(s)) {
		BinNode<T>* t = NULL;
		if (HasLChild(*s) && IsRed(s->lChild_))
			t = s->lChild_;
		else if (HasRChild(*s) && IsRed(s->rChild_))
			t = s->rChild_;
		if (t) {
			RBColor oldColor = p->color_;
			BinNode<T>* b = FromParentTo(*p) = rotateAt(t);
			if (HasLChild(*b))
				b->lChild_->color_ = RB_BLACK;
			updateHeight(b->lChild_);
			if (HasRChild(*b))
				b->rChild_->color_ = RB_BLACK;
			updateHeight(b->rChild_);
			b->color_ = oldColor;
			updateHeight(b);
		} else {
			s->color_ = RB_RED;
			s->height_--;
			if (IsRed(p)) {
				p->color_ = RB_BLACK;
			} else {
				p->height_--;
				solveDoubleBlack(P);
			}
		}
	} else {
		s->color_ = RB_BLACK;
		p->color_ = RB_RED;
		BinNode<T>* t = IsLChild(*s) ? s->lChild_ : s->rChild_;
		hot_ = p;
		FromParentTo(*p) = rotateAt(t);
		solveDoubleBlack(r);
	}
}

#endif
