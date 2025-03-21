#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
} LinkedList;

LinkedList *initialize()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    return list;
}

void insertAtBeginning(LinkedList *l, int x)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = l->head;
    l->head = newNode;
}

void insertAtEnd(LinkedList *l, int x)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = x;
    newNode->next = NULL;
    if (l->head == NULL)
    {
        l->head = newNode;
        return;
    }
    Node *temp = l->head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

void deleteFromBeginning(LinkedList *l)
{
    if (l->head == NULL)
        return;
    Node *temp = l->head;
    l->head = l->head->next;
    free(temp);
}

void deleteFromEnd(LinkedList *l)
{
    if (l->head == NULL)
        return;
    if (l->head->next == NULL)
    {
        free(l->head);
        l->head = NULL;
        return;
    }
    Node *temp = l->head;
    while (temp->next->next != NULL)
        temp = temp->next;
    free(temp->next);
    temp->next = NULL;
}

void displayList(LinkedList *l)
{
    Node *temp = l->head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

Node *search(LinkedList *list, int value)
{
    Node *temp = list->head;
    while (temp != NULL)
    {
        if (temp->data == value)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

void insert(LinkedList *list, int index, int value)
{
    if (index < 0)
    {
        printf("Invalid index\n");
        return;
    }
    if (index == 0)
    {
        insertAtBeginning(list, value);
        return;
    }
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    Node *temp = list->head;
    for (int i = 0; temp != NULL && i < index - 1; i++)
        temp = temp->next;
    if (temp == NULL)
    {
        printf("Invalid index\n");
        return;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

int identical(LinkedList *x, LinkedList *y)
{
    Node *a = x->head, *b = y->head;
    while (a && b)
    {
        if (a->data != b->data)
            return 0;
        a = a->next;
        b = b->next;
    }
    return (a == NULL && b == NULL);
}

LinkedList *merge(LinkedList *x, LinkedList *y)
{
    LinkedList *result = initialize();
    Node *a = x->head, *b = y->head;
    while (a && b)
    {
        if (a->data < b->data)
        {
            insertAtEnd(result, a->data);
            a = a->next;
        }
        else
        {
            insertAtEnd(result, b->data);
            b = b->next;
        }
    }
    while (a)
    {
        insertAtEnd(result, a->data);
        a = a->next;
    }
    while (b)
    {
        insertAtEnd(result, b->data);
        b = b->next;
    }
    return result;
}

LinkedList *intersection(LinkedList *x, LinkedList *y)
{
    LinkedList *result = initialize();
    Node *a = x->head, *b = y->head;
    while (a && b)
    {
        if (a->data == b->data)
        {
            insertAtEnd(result, a->data);
            a = a->next;
            b = b->next;
        }
        else if (a->data < b->data)
        {
            a = a->next;
        }
        else
        {
            b = b->next;
        }
    }
    return result;
}

int main()
{
    LinkedList *list1 = initialize();
    LinkedList *list2 = initialize();
    int choice, val, index;

    do
    {
        printf("\n1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Delete from Beginning\n");
        printf("4. Delete from End\n");
        printf("5. Display List\n");
        printf("6. Search Value\n");
        printf("7. Insert at Index\n");
        printf("8. Check Identical\n");
        printf("9. Merge Lists\n");
        printf("10.Find Intersection\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter value: ");
            scanf("%d", &val);
            insertAtBeginning(list1, val);
            break;
        case 2:
            printf("Enter value: ");
            scanf("%d", &val);
            insertAtEnd(list1, val);
            break;
        case 3:
            deleteFromBeginning(list1);
            break;
        case 4:
            deleteFromEnd(list1);
            break;
        case 5:
            displayList(list1);
            break;
        case 6:
            printf("Enter value to search: ");
            scanf("%d", &val);
            if (search(list1, val))
            {
                printf("Found\n");
            }
            else
            {
                printf("Not found\n");
            }
            break;
        case 7:
            printf("Enter index and value: ");
            scanf("%d %d", &index, &val);
            insert(list1, index, val);
            break;
        case 8:
            printf("Enter values for second list (enter -1 to stop):\n");
            while (1)
            {
                scanf("%d", &val);
                if (val == -1)
                    break;
                insertAtEnd(list2, val);
            }
            if (identical(list1, list2))
                printf("Lists are identical\n");
            else
                printf("Lists are not identical\n");
            break;
        case 9:
        {
            printf("Enter values for second sorted list (enter -1 to stop):\n");
            while (1)
            {
                scanf("%d", &val);
                if (val == -1)
                    break;
                insertAtEnd(list2, val);
            }
            LinkedList *mergedList = merge(list1, list2);
            printf("Merged List: ");
            displayList(mergedList);
            break;
        }
        case 10:
        {
            printf("Enter values for second sorted list (enter -1 to stop):\n");
            while (1)
            {
                scanf("%d", &val);
                if (val == -1)
                    break;
                insertAtEnd(list2, val);
            }
            LinkedList *intersectedList = intersection(list1, list2);
            printf("Intersection List: ");
            displayList(intersectedList);
            break;
        }
        case 0:
            printf("Bye Bye!\n");
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (choice != 0);

    return 0;
}