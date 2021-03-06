#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


struct Node { //узел списка
    char name[100];
    char author[100];
    char description[100];
    Node *next;
    Node *prev; 
};


struct DblLinkedList { //сам список
    int size;
    Node *head;
    Node *tail;
};


void deleteDblLinkedList(DblLinkedList **list) { //функция удаления списка
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp); //удаляем каждый элемент
        tmp = next;
    }
    free(*list); // в конце удаляем сам список
    (*list) = NULL;
}


DblLinkedList* createDblLinkedList() { //создание пустого списка
    DblLinkedList *tmp = (DblLinkedList*) malloc(sizeof(DblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL; 
 
    return tmp;
}


Node* pushBack(DblLinkedList *list) { // вставка элемента в конец списка
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) exit(1);
    tmp->next = NULL;
    tmp->prev = list->tail;
    if (list->tail) list->tail->next = tmp;
    list->tail = tmp;
 
    if (list->head == NULL) list->head = tmp;
    list->size++;

    return tmp;
}


Node* getNth(DblLinkedList *list, int index) { // взятие элемента из списка по номеру index
    Node *tmp = list->head;
    int i = 0;
    
    while (tmp && i < index) {
        tmp = tmp->next; 
        i++;
    }
 
    return tmp;
}


Node* insert(DblLinkedList *list, int index) { // вставка в произвольное место списка
    Node *elm = NULL;
    Node *ins = NULL;
    elm = getNth(list, index);
    if (elm == NULL) exit(1);
    ins = (Node*) malloc(sizeof(Node));
    ins->prev = elm;
    ins->next = elm->next;
    if (elm->next) elm->next->prev = ins;
    elm->next = ins;
        //тут лучше нарисуй на бумажке, без этого не понять

 
    if (!elm->prev) list->head = elm;
    if (!elm->next) list->tail = elm;
 
    list->size++;

    return ins;
}

 
void deleteNth(DblLinkedList *list, int index) { // удаление элемента
    Node *elm = NULL;
    void *tmp = NULL;
    elm = getNth(list, index);
    if (elm == NULL) exit(1);

    if (elm->prev) elm->prev->next = elm->next;
    if (elm->next) elm->next->prev = elm->prev;
    //тут лучше нарисуй на бумажке, без этого не понять
 
    if (!elm->prev) list->head = elm->next;
    if (!elm->next) list->tail = elm->prev;
 
    free(elm);
 
    list->size--;
}


int find(DblLinkedList *list, char *value){ // поиск книги по ее имнени
	int i = 0;
    for (Node *item = list->head; item; item = item->next)
    {
    	if (strcmp(item->name, value) == 0) return i; // просто идем по всему списку и сравниваем имена со строкой
    	i++;
    }
    return -1;
}


void printDblLinkedList(DblLinkedList *list) { //вывод всего списка
    for (Node *item = list->head; item; item = item->next) {
        cout << item->name;
        cout << ' ';
        cout << item->author;
        cout << ' ';    
        cout << item->description;
        cout << '\n';
    }
}

void fillNode(Node *item) { //заполнение полей узла списка
	cout << "Name: ";
    cin >> item->name;
    cout << "Author: ";
    cin >> item->author;
    cout << "description: ";
    cin >> item->description;
}


int main() {
    DblLinkedList *list = createDblLinkedList();

    cout << "point 1\n";
    fillNode(pushBack(list));
    printDblLinkedList(list);

    cout << "point 2\n";
    fillNode(insert(list, 0));
    printDblLinkedList(list);

    cout << "point 3\n";
    char s[100];
    cout << "search: ";
    cin >> s;
    int index = find(list, s);
    if (index == -1) {
    	cout << "no such item\n";
    	fillNode(insert(list, 0));
    } else fillNode(insert(list, index));
    printDblLinkedList(list);

    cout << "point 4\n";
    cout << "search: ";
    cin >> s;
	index = find(list, s);
	if (index == -1) {
    	cout << "no such item\n";
    	fillNode(insert(list, 0));
    } else fillNode(insert(list, index-1));
    printDblLinkedList(list);

    cout << "point 5\n";
    fillNode(insert(list, list->size / 2));
    printDblLinkedList(list);

    cout << "point 6\n";
    deleteNth(list, list->size / 2);
    printDblLinkedList(list);
    
    cout << "point 7\n";
    cout << "search: ";
    cin >> s;
	index = find(list, s);
	if (index == -1) cout << "no such item";
    else deleteNth(list, index);
    printDblLinkedList(list);

    cout << "point 8\n";
    deleteNth(list, list->size - 1);
    printDblLinkedList(list);

    cout << "point 9\n";
    cout << "index: ";
    cin >> index;
	deleteNth(list, index);
    printDblLinkedList(list);

    cout << "point 10\n";
	deleteNth(list, 0);
    printDblLinkedList(list);

    deleteDblLinkedList(&list);
	return 0;
}