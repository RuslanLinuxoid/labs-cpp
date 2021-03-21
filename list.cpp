#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


struct Node {
    char name[100];
    char author[100];
    char description[100];
    Node *next;
};


struct List {
    int size;
    Node *head;
    Node *tail;
};


void deleteList(List **list) {
    Node *tmp = (*list)->head;
    Node *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}


List* createList() {
    List *tmp = (List*) malloc(sizeof(List));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;
 
    return tmp;
}


Node* pushBack(List *list) {
    Node *tmp = (Node*) malloc(sizeof(Node));
    if (tmp == NULL) exit(1);
    tmp->next = NULL;
    if (list->tail) list->tail->next = tmp;
    list->tail = tmp;
 
    if (list->head == NULL) list->head = tmp;
    list->size++;

    return tmp;
}


Node* getNth(List *list, int index) {
    Node *tmp = list->head;
    int i = 0;
    
    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }
 
    return tmp;
}


Node* insert(List *list, int index) {
    Node *elm = NULL;
    Node *ins = NULL;
    elm = getNth(list, index);
    if (elm == NULL) exit(1);
    ins = (Node*) malloc(sizeof(Node));
    ins->next = elm->next;
    elm->next = ins;
 
    if (!elm->next) list->tail = elm;
 
    list->size++;

    return ins;
}

 
void deleteNth(List *list, int index) {
    Node *elm = NULL;
    Node *tmp = NULL;

    if (index == 0)
    {
        tmp = list->head->next;
        free(list->head);
        list->head = tmp;
    } else {
        elm = getNth(list, index-1);
        if (elm == NULL) exit(1);

        tmp = elm->next->next;
        free(elm->next);
        elm->next = tmp;
    }
 
    list->size--;
}


int find(List *list, char *value){
    int i = 0;
    for (Node *item = list->head; item; item = item->next)
    {
        if (strcmp(item->name, value) == 0) return i;
        i++;
    }
    return -1;
}


void printList(List *list) {
    for (Node *item = list->head; item; item = item->next) {
        cout << item->name;
        cout << ' ';
        cout << item->author;
        cout << ' ';    
        cout << item->description;
        cout << '\n';
    }
}

void fillNode(Node *item) {
    cout << "Name: ";
    cin >> item->name;
    cout << "Author: ";
    cin >> item->author;
    cout << "description: ";
    cin >> item->description;
}


int main() {
    List *list = createList();

    cout << "point 1\n";
    fillNode(pushBack(list));
    printList(list);

    cout << "point 2\n";
    fillNode(insert(list, 0));
    printList(list);

    cout << "point 3\n";
    char s[100];
    cout << "search: ";
    cin >> s;
    int index = find(list, s);
    if (index == -1) {
        cout << "no such item\n";
        fillNode(insert(list, 0));
    } else fillNode(insert(list, index));
    printList(list);

    cout << "point 4\n";
    cout << "search: ";
    cin >> s;
    index = find(list, s);
    if (index == -1) {
        cout << "no such item\n";
        fillNode(insert(list, 0));
    } else fillNode(insert(list, index-1));
    printList(list);

    cout << "point 5\n";
    fillNode(insert(list, list->size / 2));
    printList(list);

    cout << "point 6\n";
    deleteNth(list, list->size / 2);
    printList(list);
    
    cout << "point 7\n";
    cout << "search: ";
    cin >> s;
    index = find(list, s);
    if (index == -1) cout << "no such item";
    else deleteNth(list, index);
    printList(list);

    cout << "point 8\n";
    deleteNth(list, list->size - 1);
    printList(list);

    cout << "point 9\n";
    cout << "index: ";
    cin >> index;
    deleteNth(list, index);
    printList(list);

    cout << "point 10\n";
    deleteNth(list, 0);
    printList(list);

    deleteList(&list);
    return 0;
}