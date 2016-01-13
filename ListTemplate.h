#ifndef _LISTTEMPLATE_H_
#define _LISTTEMPLATE_H_

#include <string>

struct node {
	std::string data;
	struct node *next;
};

typedef struct node Node;
typedef Node *Ptrnode;

typedef struct {
	Node *front;
	Node *rear;
} List;

class ListTemplate {
private:
	Node *newNode(std::string n);
	void freeNode(Node *p);

	Node* nextNode(Node *p);

	List *clearList(List *p);

public:
	List *newList();
	void freeList(List *p);
	bool emptyList(List *p);
	List* insertAtFront(List *p, std::string n);
	List* insertAfter(List *p, Node *w, std::string n);
	List* insertAtRear(List *p, std::string n);
	std::string removeFromFront(List *p);
	Node* findInList(List *p, std::string n);
};

#endif // _LINES_H_
