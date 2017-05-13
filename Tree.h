#ifndef TREE_H_
#define TREE_H_

//******************************************************************************
//----------------------------------<INCLUDE>-----------------------------------
//******************************************************************************

#include <cstddef>
#include <cassert>
#include <functional>
#include <iostream>

/**
 * class Tree - holding the values for the tree.
 *
 * @param root_- Pointer to the first node.
 */
//******************************************************************************
//---------------------------------<CLASS TREE>---------------------------------
//******************************************************************************

template <class T, class Compare = std::less<T> >
class Tree {

//----------------------------<FORWARD DECLARATION>-----------------------------
public:
class Iterator;


	//***********************************************************
	//------------------<TREE :: TREEEXCEPTION>------------------
	//***********************************************************
	class TreeException  : public std::exception {};
	class TreeIsEmpty 	 : public TreeException {};
	class notFoundInTree : public TreeException {};
	class alredyInTree	 : public TreeException {};
	class notSameTree	 : public TreeException {};


	//***********************************************************
	//-----------------------<TREE :: NODE>----------------------
	//***********************************************************

class Node {

	//-------------------<FRIEND DECLARATION>--------------------
	friend class Tree;
	friend class Tree::Iterator;

	//***********************************************************
	//------------------<NODE :: NODEEXCEPTION>------------------
	//***********************************************************
	class NodeException  : public std::exception {};
	class nodeisEmpty 	 : public NodeException {};
	class hasNoFather	 : public NodeException {};
	class hasNoLeftSon	 : public NodeException {};
	class hasNoRightSon	 : public NodeException {};

	public:

	//-----------------------<CONSTRUCTOR>-----------------------

	/**
	 * Node: Creates a node with a given data.
	 *
	 * @complexity O(1).
	 *
	 * @param data   - The given data
	 * @param father - The father node
	 *
	 * @return
	 * 	a new node with the given data and pointer to the
	 * 	previous nodes.
	 */
	Node(const T& data, Node* father=NULL):
		data_(&data), father_(father), left_(NULL), right_(NULL),
		leftHeight_(0),rightHeight_(0){}

	/**
	 * Node: Creates an empty node.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	a new empty node.
	 */
	Node():
		data_(NULL), father_(NULL), left_(NULL), right_(NULL),
		leftHeight_(0),rightHeight_(0){}

	//--------------------<COPY CONSTRUCTOR>---------------------

	/**
	 * Node: Creates a Node by copying a given Node.
	 *
	 * @complexity O(1).
	 *
	 * @param node - The given node to copy
	 *
	 * @return
	 * 	a new node witch is a copy of a given node.
	 */
	Node(const Node& node):
		data_(node.data_), father_(node.father_),left_(node.left_),
		right_(node.right_), leftHeight_(node.leftHeight_),
		rightHeight_(node.rightHeight_){}


	//-----------------------<DESTRUCTOR>------------------------

	/**
	 * ~Node: deallocates
	 *
	 * @complexity O(1).
	 *
	 * @param node - The given node to copy
	 *
	 * @return
	 * 	a new node witch is a copy of a given node.
	 */

	//---------------------<CLASS FUNCTIONS>---------------------

	/**
	 * isFatherOf: Checks whether the calling node (this) is the father of the
	 * given node.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	True if the the calling node (this) is the father of the given node,
	 * 	or false otherwise.
	 */
	bool isFatherOf(Node* node) const{
		if(node){
			return(node->father_==this)?true:false;
		}
		return false;
	}

	/**
	 * isLeftSonOf: Checks whether the calling node (this) is the left son of the
	 * given node.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	True if the calling node (this) is th left son of the given node, or
	 * 	false otherwise.
	 */
	bool isLeftSonOf(Node* node) const{
		if(node){
			return(node->left_==this)?true:false;
		}
		return false;
	}

	/**
	 * isRightSonOf: Checks whether the calling node (this) is the right son of
	 * the given node.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	true if the calling node (this) is the right son of the given node, or
	 * 	false otherwise.
	 */
	bool isRightSonOf(Node* node) const{
		if(node){
			return(node->right_==this)?true:false;
		}
		return false;
	}

	/**
	 * hasFather :checks whether the calling node (this) has a father.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	true if the calling node (this) has a father or false otherwise.
	 */
	bool hasFather()const{
		return (father_)?true:false;
	}

	/**
	 * hasLeftSon :checks whether the calling node (this) has a left son.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	true if the calling node (this) has a left son or false otherwise.
	 */
	bool hasLeftSon()const{
		return (left_)?true:false;
	}

	/**
	 * hasRightSon :checks whether the calling node (this) has a right son.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	true if the calling node (this) has a right son or false otherwise.
	 */
	bool hasRightSon()const{
		return (right_)?true:false;
	}

	/**
	 * BalanceFactor: returns the balance factor of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  the balance factor of the calling node (this).
	 */
	int balanceFactor() const{
		return leftHeight_-rightHeight_;
	}

	/**
	 * numOfSons: returns the number of sons the calling node (this) has.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	the number of sons the calling node (this) has.
	 */
	int numOfSons() const{
		return ((left_)? 1:0)+((right_)?1:0);
	}

	/**
	 * isLeaf: checks whether the calling node (this) has zero sons.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	true if the calling node (this) has zero sons, or false otherwise.
	 */
	bool isLeaf() const{
		return (numOfSons()==0)?true:false;
	}

	/**
	 * getRightHeight: returns the height of the right sub tree of the calling
	 * node (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	the height of the right sub tree of the calling node (this).
	 */
	int getRightHeight() const{
		return rightHeight_;
	}

	/**
	 * getLeftHeight: returns the height of the left sub tree of the calling
	 * node (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	the height of the left sub tree of the calling node (this).
	 */
	int getLeftHeight() const{
		return leftHeight_;
	}

	/**
	 * getFather: returns the father node of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  the father node of the calling node (this).
	 */
	Node* getFather() const{
		return father_;
	}

	/**
	 * getLeftSon: returns the left son node of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  the left son node of the calling node (this).
	 */
	Node* getLeftSon() const{
		return left_;
	}

	/**
	 * getRightSon: returns the right son node of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  the right son node of the calling node (this).
	 */
	Node* getRightSon() const{
		return right_;
	}

	/**
	 * setFather: sets the father node of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @param node  - The given node.
	 */
	void setFather(Node* node){
		father_=node;
	}

	/**
	 * setLeftSon: sets the left son node of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @param node  - The given node.
	 */
	void setLeftSon(Node* node){
		left_=node;
	}

	/**
	 * setRightSon: sets the right son node of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @param node  - The given node.
	 */
	void setRightSon(Node* node){
		right_=node;
	}

	/**
	 * setRightHeight: sets the height of the right sub tree of the calling
	 * node (this).
	 *
	 * @complexity O(1).
	 */
	void setRightHeight(int height){
		rightHeight_=height;
	}

	/**
	 * setLeftHeight: sets the height of the left sub tree of the calling
	 * node (this).
	 *
	 * @complexity O(1).
	 */
	void setLeftHeight(int height){
		leftHeight_=height;
	}

	//------------------------<OPERATORS>------------------------

	/**
	 * operator(*): returning the data of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  The data of the calling node (this).
	 */
	const T& operator*() const{
		return *data_;
	}

	/**
	 * operator(->): dereferencing to the element of the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  a pointer to the element pointed by the calling node (this).
	 */
	const T*  operator->()const{
		return data_;
	}

	/**
	 * operator(=): assigning the given node to the calling node (this).
	 *
	 * @complexity O(1).
	 *
	 * @param node - The given node
	 *
	 * @return
	 * 	a copy of the calling node (this).
	 */
	Node& operator=(const Node& node){
		data_=node.data_;
		father_=node.father_;
		left_=node.left_;
		right_=node.right_;
		leftHeight_=node.leftHeight_;
		rightHeight_=node.rightHeight_;
		return *this;
	}

	private:

	//----------------------<DATA MEMBERS>-----------------------

	const T* data_ ;
	Node* 	 father_;
	Node* 	 left_;
	Node* 	 right_;
	int   	 leftHeight_;
	int   	 rightHeight_;
	};

	//***********************************************************
	//---------------------<TREE :: ITERATOR>--------------------
	//***********************************************************

class Iterator {

	//-------------------<FRIEND DECLARATION>--------------------
	friend class Tree;

	public:

	//-----------------------<CONSTRUCTOR>-----------------------

	/**
	 * Iterator: creates a new iterator with the given pointer to a node
	 * (starting point).
	 *
	 * @complexity O(1).
	 *
	 * @param Tree 	 - the given Tree the iterator belongs to.
	 * @param node 	 - the given pointer to a node.
	 *
	 * @return
	 * 	a new iterator set to a starting point.
	 */
	Iterator(const Tree& tree, Node* node=NULL):
		tree_(tree),node_(node),father_(NULL){
		if (node && node_->getFather()){
			father_=node_->getFather();
		}
	}
	//--------------------<COPY CONSTRUCTOR>---------------------

	/**
	 * Iterator: creates a new iterator by copying a given iterator.
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator to copy..
	 *
	 * @return
	 * 	a new iterator witch is a copy of the given iterator.
	 */
	Iterator(const Iterator& iterator):
		tree_(iterator.tree_), node_(iterator.node_),father_(iterator.father_){}

	//---------------------<CLASS FUNCTIONS>---------------------

	/**
	 * father: returning the father node of the calling iterator (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  a father node of the node pointed by the calling iterator (this).
	 */
	Node* father()const{
		return father_;
	}

	/**
	 * node: returning the node of the calling iterator (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  the node of the node pointed by the calling iterator (this).
	 */
	Node* node()const{
		return node_;
	}

	//------------------------<OPERATORS>------------------------

	/**
	 * operator(*): returning the data of the calling iterator (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  a data of the node pointed by the calling iterator (this).
	 */
	const T&  operator*()const{
		return **node_;
	}

	/**
	 * operator(->): dereferencing to the node of the calling iterator (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  a pointer to the node pointed by the calling iterator (this).
	 */
	Node*  operator->()const{
		return node_;
	}

	/**
	 * operator(==): compares between a calling iterator (this) and a given
	 * iterator.
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator
	 *
	 * @return
	 * 	true  if the given iterator has both the node field and the tree field
	 * 	pointing to the same addresses as the calling iterator (this).
	 *  false otherwise.
	 */
	bool operator==(const Iterator& iterator) const{
		return ((&tree_ == &iterator.tree_) && (node_==iterator.node_));
	}

	/**
	 * operator(!=): compares between a calling iterator (this) and a given
	 * iterator. using the operator==.
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator
	 *
	 * @return
	 * 	true if the given iterator is not equal to the calling iterator (this).
	 *  else it will return false
	 */
	bool operator!=(const Iterator& iterator) const{
		return !(*this==iterator);
	}

	/**
	 * operator(=): assigning the given iterator to the calling iterator
	 * (this).
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator
	 *
	 * @return
	 * 	a copy of the calling iterator (this).
	 */
	Iterator& operator=(const Iterator& iterator){
		if(&tree_!=&iterator.tree_){
			throw notSameTree();
		}
		node_=iterator.node_;
		father_=iterator.father_;
		return *this;
	}

	/**
	 * operator(++): pointing the iterator to the right son (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the last node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the next right node.
	 */
	virtual Iterator operator++(int){
		if(node_){
			father_=node_;
			node_=node_->getRightSon();
		}
		return *this;
	}

	/**
	 * operator(++): pointing the iterator to the left son (prefix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the last node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the next left node.
	 */
	virtual Iterator operator++(){
		if(node_!=NULL){
			father_=node_;
			node_=node_->getLeftSon();
		}
		return *this;
	}

	/**
	 * operator(--): pointing the operator to the father node (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the root node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator befor pointing to the father node.
	 */
	virtual Iterator operator--(int){
		if(father_){
			node_=father_;
			father_=node_->getFather();
			return *this;
		}
		return tree_.end();

	}

	/**
	 * operator(--): pointing the operator to the father node (prefix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the root node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the father node.
	 */
	virtual Iterator operator--(){
		return Iterator::operator --(0);
	}

	private:

	//----------------------<DATA MEMBERS>-----------------------

	const Tree& tree_;
	Node* node_;
	Node* father_;

	};

	//***********************************************************
	//------------------<TREE :: FIND ITERATOR>------------------
	//***********************************************************

class find_iterator: public Iterator{

	public:
	//-----------------------<CONSTRUCTOR>-----------------------

	/**
	 * find_iterator: creates a new find iterator with the given pointer to a
	 * node (starting point).
	 *
	 * @complexity O(1).
	 *
	 * @param Tree 	 - the given Tree the iterator belongs to.
	 * @param node 	 - the given pointer to a node.
	 *
	 * @return
	 * 	a new find iterator set to a starting point.
	 */
	find_iterator(const Tree& tree, Node* node=NULL):Iterator(tree,node){}

	//--------------------<COPY CONSTRUCTOR>---------------------

	/**
	 * find_iterator: creates a new find iterator by copying a given iterator.
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator to copy..
	 *
	 * @return
	 * 	a new iterator witch is a copy of the given iterator.
	 */
	find_iterator(const Iterator& iterator):Iterator(iterator){}

	//------------------------<OPERATORS>------------------------

	/**
	 * operator(++): pointing the iterator to the right son (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the last node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the next right node.
	 */
	virtual Iterator operator++(int){
		return Iterator::operator ++(0);
	}

	/**
	 * operator(++): pointing the iterator to the left son (prefix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the last node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the next left node.
	 */
	virtual Iterator operator++(){
		return Iterator::operator ++();
	}

	/**
	 * operator(--): pointing the operator to the father node (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the root node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator befor pointing to the father node.
	 */
	virtual Iterator operator--(int){
		return Iterator::operator --(0);
	}

	/**
	 * operator(--): pointing the operator to the father node (prefix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the root node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the father node.
	 */
	virtual Iterator operator--(){
		return Iterator::operator --();
	}

	};

	//***********************************************************
	//-----------------<TREE :: INORDER ITERATOR>----------------
	//***********************************************************

class inorder_iterator: public Iterator{

	public:
	//-----------------------<CONSTRUCTOR>-----------------------

	/**
	 * inorder_iterator: creates a new inorder iterator with the given pointer
	 * to a node (starting point).
	 *
	 * @complexity O(1).
	 *
	 * @param Tree 	 - the given Tree the iterator belongs to.
	 * @param node 	 - the given pointer to a node.
	 *
	 * @return
	 * 	a new inorder iterator set to a starting point.
	 */
	inorder_iterator(const Tree& tree, Node* node=NULL):Iterator(tree,node){}

	//--------------------<COPY CONSTRUCTOR>---------------------

	/**
	 * inorder_iterator: creates a new inorder iterator by copying a given
	 * iterator.
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator to copy..
	 *
	 * @return
	 * 	a new inorder iterator witch is a copy of the given iterator.
	 */
	inorder_iterator(const Iterator& iterator):Iterator(iterator){}

	//------------------------<OPERATORS>------------------------

	/**
	 * operator(++): pointing the inorder iterator to the next inorder element
	 * (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the last node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the next inorder element
	 */
	virtual Iterator operator++(int){
		if(Iterator::node()){
			if(Iterator::node()->hasRightSon()){
				Iterator::operator ++(0);
				while(Iterator::node()->hasLeftSon()){
					Iterator::operator ++();
				}
			}
			else if(Iterator::father()){
				Iterator next(*this);
				while(next.father()){
					if(next->isLeftSonOf(next.father())){
						next--;
						*this=next;
						break;
					}
					next--;
				}
			}
		}
		return *this;
	}

	/**
	 * operator(++): pointing the inorder iterator to the next inorder element
	 * (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the last node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the next inorder element
	 */
	virtual Iterator operator++(){
		return (*this)++;
	}

	/**
	 * operator(--): pointing the inorder iterator to the previouse inorder
	 * element (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the first node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the previouse inorder node.
	 */
	virtual Iterator operator--(int){
		if(Iterator::node()){
			if(Iterator::node()->hasLeftSon()){
				Iterator::operator ++();
				while(Iterator::node()->hasRightSon()){
					Iterator::operator ++(0);
				}
			}
			else if(Iterator::father()){
				Iterator next(*this);
				while(next.father()){
					if(next->isRightSonOf(next.father())){
						next--;
						*this=next;
						break;
					}
					next--;
				}
			}
		}
		return *this;
	}

	/**
	 * operator(--): pointing the inorder iterator to the previouse inorder
	 * element (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the first node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the previouse inorder node.
	 */
	virtual Iterator operator--(){
		return (*this)--;
	}

	};

	//***********************************************************
	//-------------<TREE :: REVERSE INORDER ITERATOR>------------
	//***********************************************************

class reverse_inorder_iterator: public Iterator{

	public:
	//-----------------------<CONSTRUCTOR>-----------------------

	/**
	 * reverse_inorder_iterator: creates a new reverse inorder iterator with the
	 * given pointer  to a node (starting point).
	 *
	 * @complexity O(1).
	 *
	 * @param Tree 	 - the given Tree the iterator belongs to.
	 * @param node 	 - the given pointer to a node.
	 *
	 * @return
	 * 	a new reverse inorder iterator set to a starting point.
	 */
	reverse_inorder_iterator(const Tree& tree, Node* node=NULL):
			Iterator(tree,node){}

	//--------------------<COPY CONSTRUCTOR>---------------------

	/**
	 * reverse_inorder_iterator: creates a new inorder iterator by copying a
	 * given iterator.
	 *
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator to copy..
	 *
	 * @return
	 * 	a new reverse inorder  iterator witch is a copy of the given iterator.
	 */
	reverse_inorder_iterator(const Iterator& iterator):Iterator(iterator){}

	//------------------------<OPERATORS>------------------------

	/**
	 * operator(++): pointing the reverse inorder iterator to the previouse
	 * inorder element (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the last node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the previouse inorder element.
	 */
	virtual Iterator operator++(int){
		if(Iterator::node()){
			if(Iterator::node()->hasLeftSon()){
				Iterator::operator ++(0);
				while(Iterator::node()->hasRightSon()){
					Iterator::operator ++();
				}
			}
			else if(Iterator::father()){
				Iterator next(*this);
				while(next.father()){
					if(next->isRightSonOf(next.father())){
						next--;
						*this=next;
						continue;
					}
					next--;
				}
			}
		}
		return *this;
	}

	/**
	 * operator(++): pointing the reverse inorder iterator to the previouse
	 * inorder element (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the last node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the previouse inorder element.
	 */
	virtual Iterator operator++(){
		return (*this)++;
	}

	/**
	 * operator(--): pointing the reverse inorder iterator to the next
	 * inorder element (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the first node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the next inorder node.
	 */
	virtual Iterator operator--(int){
		if(Iterator::node()){
			if(Iterator::node()->hasRightSon()){
				Iterator::operator ++();
				while(Iterator::node()->hasLeftSon()){
					Iterator::operator ++(0);
				}
			}
			else if(Iterator::father()){
				Iterator next(*this);
				while(next.father()){
					if(next->isRightSonOf(next.father())){
						next--;
						*this=next;
						continue;
					}
					next--;
				}
			}
		}
		return *this;
	}

	/**
	 * operator(--): pointing the reverse inorder iterator to the next
	 * inorder element (postfix).
	 *
	 * @complexity O(1).
	 *
	 * if the iterator invalid or pointing to the first node nothing will
	 * be done
	 *
	 * @return
	 *  the iterator after pointing to the next inorder node.
	 */
	virtual Iterator operator--(){
		return (*this)--;
	}


	};

	//***********************************************************
	//-----------------<TREE :: PREORDER ITERATOR>---------------
	//***********************************************************

class preorder_iterator: public Iterator{

	public:
	//-----------------------<CONSTRUCTOR>-----------------------

	/**
	 * preorder_iterator: creates a new preorder iterator with the given pointer
	 * to a node (starting point).
	 *
	 * @complexity O(1).
	 *
	 * @param Tree 	 - the given Tree the iterator belongs to.
	 * @param node 	 - the given pointer to a node.
	 *
	 * @return
	 * 	a new preorder iterator set to a starting point.
	 */
	preorder_iterator(const Tree& tree, Node* node=NULL):Iterator(tree,node){}

	//--------------------<COPY CONSTRUCTOR>---------------------

	/**
	 * preorder_iterator: creates a new preorder iterator by copying a
	 * given iterator.
	 *
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator to copy..
	 *
	 * @return
	 * 	a new preorder iterator witch is a copy of the given iterator.
	 */
	preorder_iterator(const Iterator& iterator):Iterator(iterator){}

	//------------------------<OPERATORS>------------------------

	};

	//***********************************************************
	//----------------<TREE :: POSTORDER ITERATOR>---------------
	//***********************************************************

class postorder_iterator: public Iterator{

	public:
	//-----------------------<CONSTRUCTOR>-----------------------

	/**
	 * postorder_iterator: creates a new postorder iterator with the given
	 * pointer to a node (starting point).
	 *
	 * @complexity O(1).
	 *
	 * @param Tree 	 - the given Tree the iterator belongs to.
	 * @param node 	 - the given pointer to a node.
	 *
	 * @return
	 * 	a new postorder iterator set to a starting point.
	 */
	postorder_iterator(const Tree& tree, Node* node=NULL):Iterator(tree,node){}

	//--------------------<COPY CONSTRUCTOR>---------------------

	/**
	 * postorder_iterator: creates a new postorder iterator by copying a
	 * given iterator.
	 *
	 *
	 * @complexity O(1).
	 *
	 * @param iterator  - The given iterator to copy..
	 *
	 * @return
	 * 	a new postorder iterator witch is a copy of the given iterator.
	 */
	postorder_iterator(const Iterator& iterator):Iterator(iterator){}

	//------------------------<OPERATORS>------------------------

	};

	//***********************************************************
	//-----------------------<CONSTRUCTOR>-----------------------
	//***********************************************************

	/**
	 * Tree: creates a new empty tree.
	 *
	 * @complexity O(1).
	 *
	 *
	 * @return
	 * 	a new tree with the given node as root.
	 */
	Tree():
		root_(NULL),max_(NULL),min_(NULL),size_(0){}

	//***********************************************************
	//-----------------------<DESTRUCTOR>------------------------
	//***********************************************************

	/**
	 * ~Tree: deallocates a Tree.
	 */
	virtual ~Tree(){
		clear();
	}

	//***********************************************************
	//---------------------<CLASS FUNCTIONS>---------------------
	//***********************************************************

	/**
	 * insert: inserts the given element into the right place in the tree.
	 * Using the compare class operator to find the right place for the element.
	 *
	 * @complexity O(n). n is the number of elements in the tree.
	 *
	 * @param element - the given element to insert
	 *
	 * @return
	 * 	the inserted node if the element was not already in the tree, or NULL
	 * 	otherwise.
	 */
	virtual find_iterator insert(const T& element){
		Compare compare;
		find_iterator iterator=find(element);
		if(iterator!=fend()){
			throw alredyInTree();
		}
		iterator.node_=new Node(element,iterator.father());
		if(!iterator.father()){
			setRoot(iterator.node());
			setMax(iterator.node());
			setMin(iterator.node());
		}
		else {
			find_iterator prev(iterator);
			prev--;
			if(compare(element,*prev)){
				prev->setLeftSon(iterator.node());
				if(compare(element,min())){
					setMin(iterator.node());
				}
			}
			else{
				prev->setRightSon(iterator.node());
				if(compare(max(),element)){
					setMax(iterator.node());
				}
			}
			uptadeHeightsToRoot(prev.node());
		}
		size_++;
		return iterator;
		}

	/**
	 * erase: removes the given element from the tree.
	 * Using the compare class operator to find the element in the tree.
	 *
	 * @complexity O(n). n is the number of elements in the tree.
	 *
	 * @param element - the given element to remove
	 *
	 * @return
	 * 	the father of the erased node if the element was found in the tree,
	 * 	or NULL otherwise.
	 */
	virtual find_iterator erase(const T& element){
		return erase(find(element));
	}

	/**
	 * erase: removes the element pointed by the given iterator.
	 * Using the compare class operator to find the element in the tree.
	 *
	 * @complexity O(n). n is the number of elements in the tree.
	 *
	 * @param iterator - the given iterator.
	 *
	 * @return
	 * 	the father of the erased node if the element was found in the tree,
	 * 	or NULL otherwise.
	 */
	virtual find_iterator erase(Iterator iterator){
		Compare compare;
		if(iterator==fend()){
			throw notFoundInTree();
		}
		if(iterator->numOfSons()==2){
			inorder_iterator next(iterator);
			next++;
			swap(*iterator.node(),*next.node());
			iterator=next;
		}
		if(!compare(*iterator,max())){
			inorder_iterator prev(iterator);
			prev--;
			setMax(prev.node());
		}
		if(!compare(min(),*iterator)){
			inorder_iterator next(iterator);
			next++;
			setMin(next.node());
		}
		if(iterator->numOfSons()==1){
			Node* son((iterator->hasLeftSon())?
					iterator->getLeftSon(): iterator->getRightSon());
			if(iterator.father()){
				if(iterator->isLeftSonOf(iterator.father())){
					iterator.father()->setLeftSon(son);
				}
				else{
					iterator.father()->setRightSon(son);
				}
				son->setFather(iterator.father());
			}
			else{
				setRoot(son);
				son->setFather(NULL);
			}
		}
		if(iterator->numOfSons()==0){
			if(iterator.father()){
				if(iterator->isLeftSonOf(iterator.father())){
					iterator.father()->setLeftSon(NULL);
				}
				else{
					iterator.father()->setRightSon(NULL);
				}
			}
			else{
				setRoot(NULL);
				setMax(NULL);
				setMin(NULL);
			}
		}
		uptadeHeightsToRoot(iterator.father());
		size_--;
		delete(iterator.node_);
		iterator.node_=NULL;
		iterator--;
		return iterator;
	}

	/**
	 * empty: Checks whether the given tree is empty or not
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  True if the given tree is empty. False otherwise.
	 */
	bool empty() const{
		return (size()==0)? true: false;
	}

	/**
	 * clear: Removes all the elements in a Tree.
	 *
	 * @complexity O(n). n is the number of elements in the tree.
	 */
	void clear(){
		setMax(NULL);
		setMin(NULL);
		if(root_==NULL){
			return;
		}
		clear(root_);
		setRoot(NULL);
		setSize(0);
	}

	/**
	 * size: Returns the number of elements in the tree.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	the number of elements in the tree.
	 */
	int size()const{
		return size_;
	}

	/**
	 * find: returns an iterator set to the given element if the key is found
	 * in the tree. Using the compare class operator to find the element in the
	 * tree.
	 *
	 * @complexity O(n). n is the number of elements in the tree.
	 *
	 * @param key - the given key to find in the tree.
	 *
	 * @return
	 *  an iterator to the element in the tree if found, or an iterator
	 *  to the right place for the element otherwise.
	 */
	find_iterator find(const T& element) const{
		Compare compare;
		find_iterator iterator=fbegin();
		while(iterator!=fend()){
			if(compare(element,*iterator)==true){
				++iterator;
				continue;
			}
			if(compare(*iterator,element)==true){
				iterator++;
				continue;
			}
			return iterator;
		}
		return iterator;
	}

	/**
	 * at: returns a referance to the element in the tree.
	 * if the element is not in the tree throws an TreeIsNotFound exception.
	 *
	 * @complexity O(n). n is the height of  the tree.
	 *
	 * @param element - the given element to find in the tree.
	 *
	 * @return
	 *  a referance to the element in the tree.
	 */
	const T& at(const T& element) const{
		find_iterator iterator=find(element);
		if(iterator==fend()){
			throw notFoundInTree();
		}
		return *iterator;
	}

	Iterator begin() const{
		return Iterator(*this,root_);
	}

	Iterator end() const{
		return Iterator(*this,NULL);
	}

	/**
	 * fbegin: Returns an find iterator to the root element in the Tree.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	a find iterator pointing to the root element in the Tree, or an "empty"
	 * 	iterator.
	 */
	find_iterator fbegin() const{
		return find_iterator(*this,root_);
	}

	/**
	 * fend: Returns an "empty" find iterator.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	an "empty" iterator.
	 */
	find_iterator fend() const{
		return find_iterator(*this,NULL);
	}

	/**
	 * ibegin: Returns an inorder iterator to the first inorder element in the
	 * Tree.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	an inorder iterator pointing to the first inorder element in the Tree,
	 * 	or an "empty" iterator.
	 */
	inorder_iterator ibegin() const{
		return inorder_iterator(*this,min_);
	}

	/**
	 * iend: Returns an "empty" inorder iterator.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	an "empty" inorder iterator.
	 */
	inorder_iterator iend() const{
		return inorder_iterator(*this,max_);
	}

	/**
	 * ribegin: Returns a reverse inorder iterator to the last inorder element
	 * in the Tree.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	a reverse inorder iterator to the last inorder element in the Tree,
	 * 	or an "empty" iterator.
	 */
	reverse_inorder_iterator ribegin() const{
		return reverse_inorder_iterator(*this,max_);
	}

	/**
	 * riend: Returns an "empty" reverse inorder iterator.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	an "empty" reverse inorder iterator.
	 */
	reverse_inorder_iterator riend() const{
			return reverse_inorder_iterator(*this,min_);
	}

	/**
	 * prbegin: Returns a preorder iterator to the root element in the
	 * Tree.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	a preorder iterator to the root element in the Tree,
	 * 	or an "empty" iterator.
	 */
	preorder_iterator prbegin() const{
		return preorder_iterator(*this,root_);
	}

	/**
	 * prend: Returns an "empty" preorder iterator.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	an "empty" preorder iterator.
	 */
	preorder_iterator prend() const{
		return preorder_iterator(*this,NULL);
	}

	/**
	 * pobegin: Returns a postorder iterator to the root element in the
	 * Tree.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	a postorder iterator to the root element in the Tree,
	 * 	or an "empty" iterator.
	 */
	postorder_iterator pobegin() const{
		return postorder_iterator(*this,root_);
	}

	/**
	 * poend: Returns an "empty" postorder iterator.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	an "empty" postorder iterator.
	 */
	postorder_iterator poend() const{
			return postorder_iterator(*this,NULL);
		}

	/**
	 * max: Return the element with the biggest key.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	the the element with the biggest key.
	 */
	const T& max() const{
		if (empty()){
			throw TreeIsEmpty();
		}
		return **max_;
	}

	/**
	 * min: Return the element with the smallest key.
	 *
	 * @complexity O(1).
	 *
	 * @return
	 * 	the the element with the smallest key.
	 */
	const T& min() const{
		if (empty()){
			throw TreeIsEmpty();
		}
		return **min_;
	}

	/**
	 * toArray: Returns an allocated array of all the elements in the calling
	 * tree (this) inorder (from small to big).
	 *
	 * @complexity O(n). n is the number of elements in the tree.
	 *
	 * @return
	 *  an array of all the elements in the calling tree (this).
	 */
	const T** toArray() const{
		if(root_==NULL){
			return NULL;
		}
		const T** elements = new const T* [size_];
		int x=0;
		toArray(root_,x,elements);
		return elements;
	}

	/**
	 *
	 */
	void fromArray(const T** elements, int size){
		int x=0;
		setSize(size);
		fromArray(root_,x,elements,size);

	}

	/**
	 * setMax: Sets the given node as the new max node for the calling tree
	 * (this).
	 *
	 * @complexity O(1).
	 *
	 * @param node - the given node
	 */
	void setMax(Node* node){
		max_=node;
	}

	/**
	 * setMin: Sets the given node as the new min node for the calling tree
	 * (this).
	 *
	 * @complexity O(1).
	 *
	 * @param node - the given node
	 */
	void setMin(Node* node){
		min_=node;
	}

protected:

	/**
	 * getRoot: Returns the root node of the calling tree (this).
	 *
	 * @complexity O(1).
	 *
	 * @return
	 *  The root node of the calling tree (this).
	 */
	Node* getRoot(){
		return root_;
	}

	/**
	 * setRoot: Sets the given root as the new root for the calling tree (this).
	 *
	 * @complexity O(1).
	 *
	 * @param node - the given node.
	 */
	void setRoot(Node* node){
		root_=node;
	}

	/**
	 * setSize: Sets the given size as the new siez for the calling tree (this).
	 *
	 * @complexity O(1).
	 *
	 * @param size - the given size
	 */
	void setSize(int size){
		size_=size;
	}

	/**
	 * uptadeHeightsToRoot: Updating the sub heights of all the node along the
	 * route from the given node and the root of the tree.
	 *
	 * @complexity O(h). h is the height of the.
	 *
	 * @param node - the given node from witch to update the sub heights.
	 */
	static void uptadeHeightsToRoot(Node* node){
		if(node==NULL){
			return;
		}
		updateHeights(node);
		uptadeHeightsToRoot(node->getFather());
	}

	/**
	 * updateHeights: Updating the sub heights of the given node.
	 *
	 * @complexity O(1).
	 *
	 * @param node - the given node from witch to update the sub heights.
	 */
	static void updateHeights(Node* node){
		if(node==NULL){
			return;
		}
		if(node->hasLeftSon()){
			int RH(node->getLeftSon()->getRightHeight());
			int LH(node->getLeftSon()->getLeftHeight());
			node->leftHeight_=1+((RH>LH)?RH:LH);
		}
		else{
			node->leftHeight_=0;
		}
		if(node->hasRightSon()){
			int RH(node->getRightSon()->getRightHeight());
			int LH(node->getRightSon()->getLeftHeight());
			node->rightHeight_=1+((RH>LH)?RH:LH);
		}
		else{
			node->rightHeight_=0;
		}
	}



private:

    /**
     * clear: Removes all the elements in a Tree witch the given node is his
     * root.
     *
     * @complexity O(n). n is the number of elements in the tree.
     *
     * @param node - the given node.
     */
    static void clear(Node* node){
    	if(node==NULL){
    		return;
    	}
    	clear(node->getLeftSon());
    	node->setLeftSon(NULL);
    	clear(node->getRightSon());
    	node->setRightSon(NULL);
    	delete(node);
    }

    /**
     * toArray: Returns an allocated array of all the elements in the calling
     * tree (this) inorder (from small to big).
     *
     * @complexity O(n). n is the number of elements in the tree.
     *
     * @return
     *  an array of all the elements in the calling tree (this).
     */
    static void toArray(Node* node, int& index, const T** elements) {
    	if(node==NULL){
    		return;
    	}
    	toArray(node->getLeftSon(),index, elements);
    	elements[index]=node->data_;
    	index++;
    	toArray(node->getRightSon(),index,elements);
    }

    /**
     * swap: Swapping between the two given nodes.
     *
     * @complexity O(1).
     *
     * @param node1 - the first given node.
     * @param node2 - the second given node.
     */
    void swap(Node& node1, Node& node2){
    	const T* temp=node1.data_;
    	node1.data_=node2.data_;
    	node2.data_=temp;
    }

    /**
     *
     */
   	void fromArray(Node* node, int& index, const T** elements,int size) {
   		if(node==NULL){
   			return;
   		}
   		fromArray(node->getLeftSon(),index,elements,size);
   		node->data_=elements[index];

   		if (index==0){
   			setMin(node);
   		}
   		if (index==size-1){
   			setMax(node);
   		}
   		index++;
   		fromArray(node->getRightSon(),index,elements,size);
   	}

private:

	//***********************************************************
	//----------------------<DATA MEMBERS>-----------------------
	//***********************************************************

	Node* root_;
	Node* max_;
	Node* min_;
	int   size_;
};



#endif /* TREE_H_ */
