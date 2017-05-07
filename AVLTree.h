#ifndef AVLTREE_H_
#define AVLTREE_H_

//******************************************************************************
//----------------------------------<INCLUDE>-----------------------------------
//******************************************************************************

#include "Tree.h"

/**
 * class AVLTree - inherits from Tree.
 */
//******************************************************************************
//------------------------------<CLASS AVL TREE>--------------------------------
//******************************************************************************

template <class T,class Compare = std::less<T> >
class AVLTree : public Tree<T,Compare> {

public:

    //***********************************************************
    //-----------------------<CONSTRUCTOR>-----------------------
    //***********************************************************

    /**
     * AVLTree: creates a new empty AVL tree.
     *
     *
     * @return
     * 	a new empty AVL tree.
     */
    AVLTree():Tree<T,Compare>(){}

    /**
     * AVLTree: creates a new empty AVL tree with the given number of node.
     *
     * @param size - the given number of empty nodes for the AVL tree.
     *
     * @return
     * 	a new AVL tree with the given number of empty nodes.
     */
    AVLTree(int size):Tree<T,Compare>(){
    	fillwithEmptyNodes(size);
    }


    //***********************************************************
    //--------------------<COPY CONSTRUCTOR>---------------------
    //***********************************************************

    /**
     * AVLTree: creates a new tree by copying a given AVL tree.
     *
     * @param tree  - The given AVL tree to copy.
     *
     * @return
     * 	a new AVL tree witch is an exact copy of the given AVL tree.
     */

    //***********************************************************
    //-----------------<PROMOTION CONSTRUCTOR>-------------------
    //***********************************************************

    /**
     * AVLTree: creates a new AVL tree by promoting a given node.
     *
     * @param node  - The given node to promote.
     *
     * @return
     * 	a new AVL tree witch is a copy of the given tree.
     */

    //***********************************************************
    //-----------------------<DESTRUCTOR>------------------------
    //***********************************************************

    /**
     * ~Tree: deallocates a Tree.
     */
    virtual ~AVLTree(){
    }

    //***********************************************************
    //---------------------<CLASS FUNCTIONS>---------------------
    //***********************************************************

    /**
     * insert: inserts the given element into the right place in the tree.
     * Using the compare class operator to find the right place for the element.
     * After the insertion of the new node, the tree is balanced according to
     * the definition of AVL tree.
	 *
	 * @complexity O(log(n)).
	 *
	 * @param element - the given element to insert
	 *
     * @return
     * 	true if the element was not already in the tree, or false otherwise.
     */
    virtual typename Tree<T,Compare>::find_iterator
	insert(const T& element){
    	typename Tree<T,Compare>::find_iterator
		iterator=Tree<T,Compare>::insert(element);
    	typename Tree<T,Compare>::Node*
		unbalanced=firstUnbalanced(iterator.node());
    	if(unbalanced){
    		balance(unbalanced);
    		Tree<T,Compare>::uptadeHeightsToRoot(unbalanced->getFather());
    	}
    	return iterator;
    }

    /**
     * erase: removes the given element from the tree.
     * Using the compare class operator to find the element in the tree.
     * After the node erased, the tree is balanced according to the
     * definition of AVL tree.
     *
     * @complexity O(log(n)).
	 *
	 * @param element - the given element to remove
	 *
     * @return
     * 	true if the element was found in the tree, or false otherwise.
     */
    virtual typename Tree<T,Compare>::find_iterator
	erase(const T& element){
    	return erase(Tree<T,Compare>::find(element));
    }

    /**
     * erase: removes the given element from the tree.
     * Using the compare class operator to find the element in the tree.
     * After the node erased, the tree is balanced according to the
     * definition of AVL tree.
     *
     * @complexity O(log(n)).
     *
     * @param element - the given element to remove
     *
     * @return
     * 	true if the element was found in the tree, or false otherwise.
     */
    virtual typename Tree<T,Compare>::find_iterator
	erase(typename Tree<T,Compare>::find_iterator iterator){
    	typename Tree<T,Compare>::find_iterator it=Tree<T,Compare>::erase(iterator);
    	typename Tree<T,Compare>::Node*
		unbalanced=firstUnbalanced(it.node());
    	while(unbalanced){
    		balance(unbalanced);
    		Tree<T,Compare>::uptadeHeightsToRoot(unbalanced->getFather());
    		unbalanced=firstUnbalanced(unbalanced->getFather());
    	}
    	return it;
    }

private:

    /**
     * firstUnbalanced: returns the first unbalanced node in the route from the
     * given node to the root to the tree.
     *
     * @complexity O(log(n)).
     *
     * @param node - the given node.
     *
     * @return
     *  the first unbalanced node in the route from the given node to root of
     *  the tree.
     */
    static typename Tree<T,Compare>::Node*
	firstUnbalanced(typename Tree<T,Compare>::Node* node){
       	if(!node){
       		return NULL;
       	}
       	if(node->balanceFactor()>1 || node->balanceFactor()<-1){
       		return node;
       	}
       	return firstUnbalanced(node->getFather());
       }

    /**
     * balance: Balancing the given node according to the definition of AVL
     * tree. Using on of the four roll functions.
     *
     * @complexity O(1).
     *
	 * @param node - the given node to balance.
	 *
     */
    void balance(typename Tree<T,Compare>::Node* node){
    	if(node->balanceFactor()>1){
    		if(node->getLeftSon()->balanceFactor()>0){
    			rollLL(node);
    		}
    		else{
    			rollLR(node);
    		}
    	}
    	else{
    		if(node->getRightSon()->balanceFactor()<0){
    			rollRR(node);
    		}
    		else{
    			rollRL(node);
    		}
    	}
    }

    /**
     * rollLL: Roll the given node to balance the tree according to the
     * definition of AVL tree. This roll performed in case the unbalancing node
     * located to the left of the given node and to the left of the node's left
     * son.
     *
     * @complexity O(1).
     *
     */
    void rollLL(typename Tree<T,Compare>::Node* node){
    	if (!node->hasFather()){
    		Tree<T,Compare>::setRoot(node->getLeftSon());
    		node->getLeftSon()->setFather(NULL);
    	}
    	else{
    		if(node->isLeftSonOf(node->getFather())){
    			node->getFather()->setLeftSon(node->getLeftSon());
    		}
    		else{
    			node->getFather()->setRightSon(node->getLeftSon());
    		}
    		node->getLeftSon()->setFather(node->getFather());
    	}
    	node->setFather(node->getLeftSon());
    	if(node->getLeftSon()->hasRightSon()){
    		node->setLeftHeight(node->getLeftSon()->getRightHeight());
    		node->setLeftSon(node->getLeftSon()->getRightSon());
    		node->getLeftSon()->setFather(node);
    	}
    	else{
    		node->setLeftSon(NULL);
    		node->setLeftHeight(0);
    	}
    	node->getFather()->setRightSon(node);
    }

    /**
     * rollRR: Roll the given node to balance the tree according to the
     * definition of AVL tree. This roll performed in case the unbalancing node
     * located to the right of the given node and to the right of the node's
     * right son.
     *
     * @complexity O(1).
     *
     */
    void rollRR(typename Tree<T,Compare>::Node* node){
     	if (!node->hasFather()){
     		Tree<T,Compare>::setRoot(node->getRightSon());
     		node->getRightSon()->setFather(NULL);
     	}
     	else{
     		if(node->isRightSonOf(node->getFather())){
     			node->getFather()->setRightSon(node->getRightSon());
     		}
     		else{
     			node->getFather()->setLeftSon(node->getRightSon());
     		}
     		node->getRightSon()->setFather(node->getFather());
     	}
     	node->setFather(node->getRightSon());
     	if(node->getRightSon()->hasLeftSon()){
     		node->setRightHeight(node->getRightSon()->getLeftHeight());
     		node->setRightSon(node->getRightSon()->getLeftSon());
     		node->getRightSon()->setFather(node);
     	}
     	else{
     		node->setRightSon(NULL);
     		node->setRightHeight(0);
     	}
     	node->getFather()->setLeftSon(node);
    }

    /**
     * rollLR: Roll the given node to balance the tree according to the
     * definition of AVL tree. This roll performed in case the unbalancing node
     * located to the left of the given node and to the right of the node's
     * right son.
     *
     * @complexity O(1).
     */
    void rollLR(typename Tree<T,Compare>::Node* node){
    	rollRR(node->getLeftSon());
    	rollLL(node);
    }

    /**
     * rollRL: Roll the given node to balance the tree according to the
     * definition of AVL tree. This roll performed in case the unbalancing node
     * located to the right of the given node and to the left of the node's
     * right son.
     *
     * @complexity O(1).
     */
    void rollRL(typename Tree<T,Compare>::Node* node){
    	rollLL(node->getRightSon());
    	rollRR(node);
    }

    /**
     * fillwithEmptyNodes: Fills the calling tree (this) with empty nodes up to
     * the given height.
     *
     * @complexity O(n). n is the number of empty nodes in a full tree with the
     * 					 given height.
     */
    void fillwithEmptyNodes(int size){
    	Tree<T,Compare>::clear();
    	int topSize=1,height=0;
    	while(topSize<size){
    		topSize=topSize*2+1;
    		height++;
    	}
    	int remove=topSize-size;
    	Tree<T,Compare>::setRoot(new typename Tree<T,Compare>::Node());
    	Tree<T,Compare>::setSize(Tree<T,Compare>::size()+1);
    	addEmptyNodes(Tree<T,Compare>::getRoot(),height);
    	removeEmptyNodes(Tree<T,Compare>::getRoot(),remove);
       }

    /**
     * addEmptyNodes:
     */
    void addEmptyNodes(typename Tree<T,Compare>::Node* node, int height){
    	if(height==0){
    		return;
    	}
    	if(!node->hasLeftSon()){
    		node->setLeftSon(new typename Tree<T,Compare>::Node());
    		node->getLeftSon()->setFather(node);
    		Tree<T,Compare>::setSize(Tree<T,Compare>::size()+1);
    	}
    	if(!node->hasRightSon()){
    		node->setRightSon(new typename Tree<T,Compare>::Node());
    		node->getRightSon()->setFather(node);
    		Tree<T,Compare>::setSize(Tree<T,Compare>::size()+1);
    	}
    	--height;
    	addEmptyNodes(node->getLeftSon(),height);
    	addEmptyNodes(node->getRightSon(),height);
    	Tree<T,Compare>::updateHeights(node);
    }

    /**
     * removeEmptyNodes:
     */
    void removeEmptyNodes(typename Tree<T,Compare>::Node* node, int& index){
    	if(!node || !index){
    		return;
    	}
    	if(node->isLeaf()){
    		if(node->hasFather()){
    			if(node->isRightSonOf(node->getFather())){
    				node->getFather()->setRightSon(NULL);
    			}
    			else{
    				node->getFather()->setLeftSon(NULL);
    			}
    		}
    		else{
    			Tree<T,Compare>::setRoot(NULL);
    		}
    		Tree<T,Compare>::setSize(Tree<T,Compare>::size()-1);
    		delete(node);
    		index--;
    		return;
    	}
    	removeEmptyNodes(node->getRightSon(),index);
    	removeEmptyNodes(node->getLeftSon(),index);
    	Tree<T,Compare>::updateHeights(node);
        }

    //***********************************************************
    //------------------------<OPERATORS>------------------------
    //***********************************************************

public:

    /**
     *
     * operator(+=): creates a new tree which is a union of the two given
     * trees.
     *
     * @param tree1  - The first given tree.
     * @param tree2  - The second given tree.
     *
     * @return
     *  a new tree which is a union of the two given tree.
     */
    const AVLTree& operator+=(const AVLTree& tree){
    	Compare compare;
    	int totalSize=Tree<T,Compare>::size()+tree.size();
    	if (!totalSize){
    		throw typename Tree<T,Compare>::TreeIsEmpty();
    	}
    	const T** elements = new const T* [totalSize];
    	const T** elements1=Tree<T,Compare>::toArray();
    	const T** elements2=tree.toArray();
    	int index1=0,index2=0,index=0;
    	while(index1<(Tree<T,Compare>::size()) &&index2<tree.size()){
    		if(compare(*(elements2[index2]),*(elements1[index1]))==true){
    			elements[index]=elements2[index2];
    			index2++;
    		}
    		else{
    			elements[index]=elements1[index1];
    			index1++;
    		}
    		index++;
    	}
    	while(index1<(Tree<T,Compare>::size())){
    		elements[index]=elements1[index1];
    		index1++;
    		index++;
    	}
    	while(index2<tree.size()){
    		elements[index]=elements2[index2];
    		index2++;
    		index++;
    	}
    	fillwithEmptyNodes(totalSize);
    	Tree<T,Compare>::fromArray(elements,totalSize);
    	if(elements1){
    		delete[](elements1);
    	}
    	if(elements2){
    		delete[](elements2);
    	}
    	delete[](elements);
    	return *this;
    }

private:

    //***********************************************************
    //-----------------------<MEMBER TYPES>----------------------
    //***********************************************************

};

//******************************************************************************
//----------------------------<EXTERNAL FUNCTIONS>------------------------------
//******************************************************************************



#endif /* AVLTREE_H_ */
