#include <iostream>

struct Node {
    int data;
    Node *next;
};

class LinkedList {
    private:
        Node* firstNode;
	Node* currentNode;
	bool isFirstNodeInitialized = false;

    public:
	LinkedList() {
	    this->firstNode = new Node();
	    this->currentNode = this->firstNode;
	}

	void add(int data) {
	    Node* lastNode = firstNode;
	    if(lastNode->next == NULL && !isFirstNodeInitialized) {
	        lastNode->data = data;
		isFirstNodeInitialized = true;
		return;
	    }
	    while(lastNode->next != NULL) {
	        lastNode = lastNode->next;
	    }
	    lastNode->next = new Node();
	    lastNode->next->data = data;
	}

	void add(int data, int index) {
	    Node* newNode = new Node();
	    newNode->data = data;
	    Node* nodeToChange = firstNode;
	    if(index < 0) {
	        return;
	    }

	    if(index == 0 && isFirstNodeInitialized) {
	        newNode->next = nodeToChange;
	        firstNode = newNode;
	        return;	
	    }

	    if(nodeToChange->next == NULL && !isFirstNodeInitialized) {
	        nodeToChange->data = data;
		isFirstNodeInitialized = true;
		return;
	    }
	    for(int i = 0; i < index - 1; ++i) {
		if(nodeToChange->next == NULL) {
		    nodeToChange->next = newNode;
		    return;
		}    
		nodeToChange = nodeToChange->next;
	    }

	    newNode->next = nodeToChange->next;
	    nodeToChange->next = newNode;
	}

	bool hasNext() {
	    return this->currentNode->next != NULL;
	}

	int next() {
	    Node* nodeToReturn = currentNode;

	    if(hasNext()) {
	        currentNode = currentNode->next;
	    }

	    return nodeToReturn->data;
	}

	void initialize(int n) {
	    if(n <= 0) {
	        return;
	    }	
	    for(int i = 1; i <= n; ++i) {
		add(i);
	    }
	}

	void printList() {
	    Node* nodeToPrint = firstNode;
	    while(nodeToPrint != NULL) {
	        std::cout<<nodeToPrint<<":"<<nodeToPrint->data<<" -> ";
		nodeToPrint = nodeToPrint->next;
	    }

	    std::cout<<"NULL"<<std::endl;
	}

	void reverse() {
	    Node* saveNextPointer = firstNode->next;
	    Node* savePreviousPointer = firstNode;
	    firstNode->next = NULL;
	    while(saveNextPointer != NULL) {
		Node* saveNode = saveNextPointer->next;    
		saveNextPointer->next = savePreviousPointer;
		savePreviousPointer = saveNextPointer;
		saveNextPointer = saveNode;
	    }

	    firstNode = savePreviousPointer;
	}

	void shuffle() {
	    LinkedList* shuffleList = new LinkedList();
	    Node* currentNode = firstNode;
	    while(currentNode->next != NULL && currentNode->next->next != NULL) {
	        shuffleList->add(currentNode->data);
		currentNode = currentNode->next->next;
	    }

	    shuffleList->add(currentNode->data);

	    currentNode = firstNode->next;

	    if(currentNode != NULL) {
	        while(currentNode->next != NULL && currentNode->next->next != NULL) {
		    shuffleList->add(currentNode->data);
		    currentNode = currentNode->next->next;
		}    
		shuffleList->add(currentNode->data);
	    }

            firstNode = shuffleList->firstNode;
	}

	void shuffle(int n) {
	    LinkedList* shuffleList = new LinkedList();
	    Node** nodeArray = new Node*[n];
            for(int i = 0; i < n; ++i) {
		Node* node = firstNode;
		for(int j = 0; j < i; ++j) {
		    if(node->next != NULL) {
		        node = node->next;
		    } else {
		        node = NULL;
			return;
		    }
		}
	        nodeArray[i] = node;
	    }

	    for(int i = 1; i < n; ++i) {
	       Node* tmpNode = nodeArray[i-1];
	       shuffleList->add(tmpNode->data);
	       int value = 1;
	       while(tmpNode != NULL) {
	           for(int j = 0; j < (i*n + value); ++j) {
		       if(tmpNode->next != NULL) {
		           tmpNode = tmpNode->next;
		       } else {
		           tmpNode = NULL;
			   break;
		       }
		   }

		   if(tmpNode != NULL) {
		       shuffleList->add(tmpNode->data);
		   }

		   ++value;
	       }
	    }

	    firstNode = shuffleList->firstNode;
	}
};
