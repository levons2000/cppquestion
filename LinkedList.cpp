#include <iostream>

struct Node {
    int data;
    Node *next;
};

class LinkedList {
    private:
        Node* firstNode;
		Node* currentNode;
		Node* lastNode;
		bool isFirstNodeInitialized = false;

    public:
	LinkedList() {
	    this->firstNode = NULL;
	    this->currentNode = NULL;
		this->lastNode = NULL;
	}

	void add(int data) {
		if (this->firstNode == NULL) {
			firstNode = new Node();
			firstNode->data = data;
			lastNode = firstNode;
			return;
		}
		
		this->lastNode->next = new Node();
		this->lastNode = this->lastNode->next;
		this->lastNode->data = data;
	}

	void add(int data, int index) {
		if(index < 0) {
	        return;
	    }

		if (firstNode == NULL) {
			firstNode = new Node();
			firstNode->data = data;
			lastNode = firstNode;
			return;
		}
		
	    Node* newNode = new Node();
	    newNode->data = data;
	    Node* nodeToChange = firstNode;
	    

	    if(index == 0) {
	        newNode->next = nodeToChange;
	        firstNode = newNode;
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
	    for(int i = 1; i <= n; ++i) {
               Node* tmpNode = firstNode;

               for(int k = 1; k < i; ++k) {
                   tmpNode = tmpNode->next;
               }

               if(tmpNode == NULL) {
                   return;
               }

	       shuffleList->add(tmpNode->data);
               tmpNode = firstNode;
	       int value = 1;
	       while(tmpNode != NULL) {
                   tmpNode = firstNode;
	           for(int j = 0; j < (value * n + (i - 1)); ++j) {
		       if(tmpNode->next != NULL) {
		           tmpNode = tmpNode->next;
		       }
		   }

		   shuffleList->add(tmpNode->data);

                   for(int m = 0; m < n; ++m) {
                       if(tmpNode != NULL) {
                           tmpNode = tmpNode->next;
                       } else {
                           break;
                       }
                   }

		   ++value;
	       }
	    }

	    firstNode = shuffleList->firstNode;
	}
};
