#include "ListTemplate.h"



Node* ListTemplate::newNode(std::string n) {
	Node *q;
	q = new Node();
	q->data = n;
	q->next = NULL;
	return q;
}

void ListTemplate::freeNode(Node *p) {
	delete(p);
	return;
}



List* ListTemplate::newList() {
	List *p;
	p = new List();
	p->front = NULL;
	p->rear = NULL;
	return p;
}

Node* ListTemplate::nextNode(Node *p) {
	return p->next;
}

List* ListTemplate::clearList(List *p) {
	Node *q, *w;
	q = p->front;
	while (q != NULL) {
		w = nextNode(q);
		freeNode(q);
		q = w;
	}
	p->front = NULL;
	p->rear = NULL;
	return p;
}

void ListTemplate::freeList(List *p) {
	// Memória usada por cada nó
	clearList(p);
	// Memória usada pela estrutura
	delete(p);
	return;
}

bool ListTemplate::emptyList(List *p) {
	if (p->front == NULL)
		return true;
	else
		return false;
}

List* ListTemplate::insertAtFront(List *p, std::string n) {
	Node *q;
	q = newNode(n);
	q->next = p->front;
	p->front = q;
	if (p->rear == NULL)
		p->rear = q;
	return p;
}

List* ListTemplate::insertAfter(List *p, Node *w, std::string n) {
	Node *q;
	if (w == NULL || p->front == NULL)
		return insertAtFront(p, n);
	q = newNode(n);
	q->next = w->next;
	w->next = q;
	if (w == p->rear)
		p->rear = q;
	return p;
}

List* ListTemplate::insertAtRear(List *p, std::string n) {
	Node *q;
	q = p->rear;
	return insertAfter(p, q, n);
}

std::string ListTemplate::removeFromFront(List *p) {
	std::string n;
	Node *q;
	if (emptyList(p)) {
		return NULL;
	}
	n = p->front->data;
	q = p->front;
	p->front = p->front->next;
	freeNode(q);
	if (p->front == NULL)
		p->rear = NULL;
	return n;
}

Node* ListTemplate::findInList(List *p, std::string n) {
	Node *q;
	q = p->front;
	while (q != NULL) {
		if (q->data == n)
			break;
		q = nextNode(q);
	}
	// retorna NULL se não for encontrado.
	return q;
}


	//List *p;
	//int elem;



	//p = newList(nome);

	//// Inserindo dados na lista
	//cin >> elem;
	//while (elem != 0) {
	//	// Inserindo no final da lista (fila)
	//	insertAtRear(p, elem);

	//	/*
	//	// Inserindo no início da lista (pilha)
	//	insertAtFront(p, elem);
	//	*/

	//	cin >> elem;
	//}

