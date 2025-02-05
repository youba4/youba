#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
// تعريف العقدة في الشجرة 
typedef struct Node {
    int value;//قيمة العقدة 
    struct Node* left;//مؤشر العقدة لليسار
    struct Node* right;//مؤشر العقدة لليمين 
} Node;
//تعريف هيكل الشجرة الثنائية للبحث
typedef struct BinarySearchTree {
    Node* root;
} BinarySearchTree;


//انشاء عقدة 
Node* createNode(int value) {
    Node* newNode = malloc(sizeof(Node));//تخصيصالذاكرة للعفدة
    newNode->value = value;   //تعين القيمة للعقدة 
    newNode->left = newNode->right = NULL;// العقدة الجديدة ليس لها افرع بعد
    return newNode;
}
//إضافة قيمة إلى الشجرة 
void insertNode(Node** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);// إذا كانت الشجرة فارة نقوم بانشاء العقدة
        return;
    }
    if (value < (*root)->value) {
        insertNode(&(*root)->left, value);//إضافة قيمة للشجرة في اليسار
    } else {
        insertNode(&(*root)->right, value);//إضافة قيمة للشجرة في اليمين
    }
}
//إضافة قيمةإلى الشجرة الموجودة من الاشجار الموجودة 
void addValue(BinarySearchTree* table, int index, int value) {
    insertNode(&table[index].root, value);//إضافة القينة ال الشجر ة في الفهرس المحدد
}
//ملئ الأشجارالفارغة  بقيم عشوائية 
void fillEmptyTrees(BinarySearchTree* table, int size, int maxNodes) {
    for (int i = 0; i < size; i++) {
        if (table[i].root == NULL) {//إذا كانت الشجرة فارغ
            int nodes = rand() % maxNodes + 1;//عدد العقد العشوائية في الشجرة
            for (int j = 0; j < nodes; j++) {
                int value = rand() % 1001; // قيمة عشوائيةبين 0و1000
                insertNode(&table[i].root, value);//إضافة القيمة إلى الشجرة 
            }
        }
    }
}
//ترتيب الأشجار بإستخدام خوارزمية الترتيب الفقاعي بناء على الجذور
void bubbleSort(BinarySearchTree* table, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            // استخراج قيم الجذور للمقارنة 
            int rootValue1 = (table[j].root != NULL) ? table[j].root->value : INT_MAX;
            int rootValue2 = (table[j + 1].root != NULL) ? table[j + 1].root->value : INT_MAX;

            // التبديل إذا كانت القيم غير مركبة 
            if (rootValue1 > rootValue2) {
                // Swap the entire tree objects
                BinarySearchTree temp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = temp;
            }
        }
    }
}
//تهيئة جدول الأشجار بإنشاء الأشجار الفارغة
BinarySearchTree* initializeTable(int size) {
    BinarySearchTree* table = (BinarySearchTree*)malloc(size * sizeof(BinarySearchTree));
    for (int i = 0; i < size; i++) {
        table[i].root = NULL; // تعين الجذور إلى NULL
    }
    return table;
}
// البحث عن عقدة في شجرة معينة
Node* searchNode(Node* root, int value) {
    if (root == NULL) return NULL;  // إذا كانت الشجرة فارغة، العودة بـ NULL
    if (root->value == value) return root;  // إذا تم العثور على القيمة في الجذر
    if (value < root->value) return searchNode(root->left, value);  // البحث في الشجرة اليسرى
    return searchNode(root->right, value);  // البحث في الشجرة اليمنى
}

// البحث عن قيمة في شجرة معينة في الجدول
int searchInTree(BinarySearchTree* table, int size, int index, int value) {
    if (index < 0 || index >= size) {  // التحقق من أن الفهرس ضمن الحدود
        printf("Erreur: Index %d hors limites (0 à %d).\n", index, size - 1);
        return 0; // فهرس غير صالح
    }
    if (table[index].root == NULL) {  // إذا كانت الشجرة فارغة
        printf("L'arbre à l'index %d est vide.\n", index);
        return 0; // الشجرة فارغة
    }
    
    Node* foundNode = searchNode(table[index].root, value);  // البحث في الشجرة
    return (foundNode != NULL);  // إرجاع 1 إذا تم العثور على القيمة، 0 إذا لم يتم العثور عليها
}

// البحث عن قيمة في جميع الأشجار
int searchInAllTrees(BinarySearchTree* table, int size, int value) {
    if (size <= 0) {
        printf("Error: The array is empty.\n");
        return -1;  // جدول الأشجار فارغ
    }

    for (int i = 0; i < size; i++) {
        if (searchInTree(table, size, i, value)) {  // البحث في الشجرة في الفهرس الحالي
            printf("Value %d found in tree %d.\n", value, i);
            return 1; // إذا تم العثور على القيمة في أي شجرة
        }
    }

    printf("Value %d NOT found in any tree.\n", value);
    return 0; // إذا لم يتم العثور على القيمة في أي شجرة
}

// حساب حجم الشجرة (عدد العقد)
int treeSize(Node* root) {
    if (root == NULL) return 0;  // إذا كانت الشجرة فارغة
    return 1 + treeSize(root->left) + treeSize(root->right);  // الحجم هو 1 زائد حجم الأشجار اليسرى واليمنى
}

// البحث عن أصغر قيمة في الشجرة
int findMin(Node* root) {
    while (root && root->left != NULL) {  // البحث في الشجرة اليسرى حتى الوصول إلى النهاية
        root = root->left;
    }
    return root ? root->value : -1;  // إرجاع القيمة إذا وجدنا عقدة، وإلا إرجاع -1
}

// البحث عن أكبر قيمة في الشجرة
int findMax(Node* root) {
    while (root && root->right != NULL) {  // البحث في الشجرة اليمنى حتى الوصول إلى النهاية
        root = root->right;
    }
    return root ? root->value : -1;  // إرجاع القيمة إذا وجدنا عقدة، وإلا إرجاع -1
}

// التنقل عبر الشجرة بطريقة Inorder (ترتيب تصاعدي)
void inorderTraversal(Node* root) {
    if (root) {
        inorderTraversal(root->left);  // التنقل في الشجرة اليسرى
        printf("%d ", root->value);    // طباعة قيمة العقدة
        inorderTraversal(root->right); // التنقل في الشجرة اليمنى
    }
}

// التنقل عبر الشجرة بطريقة Preorder (الجذر أولاً)
void preorderTraversal(Node* root) {
    if (root) {
        printf("%d ", root->value);    // طباعة قيمة العقدة أولاً
        preorderTraversal(root->left);  // التنقل في الشجرة اليسرى
        preorderTraversal(root->right); // التنقل في الشجرة اليمنى
    }
}

// التنقل عبر الشجرة بطريقة Postorder (الجذر في النهاية)
void postorderTraversal(Node* root) {
    if (root) {
        postorderTraversal(root->left);  // التنقل في الشجرة اليسرى
        postorderTraversal(root->right); // التنقل في الشجرة اليمنى
        printf("%d ", root->value);      // طباعة قيمة العقدة في النهاية
    }
}

// القائمة الرئيسية للبرنامج حيث يتم تفاعل المستخدم
void menu() {
    int size, choice, index, value, maxNodes;
    printf("Enter the size of the array: ");
    scanf("%d", &size);  // إدخال حجم جدول الأشجار

    BinarySearchTree* table = initializeTable(size);  // تهيئة الجدول

    srand(time(NULL)); // تهيئة المولد العشوائي

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add a value to a tree\n");
        printf("2. Automatically fill empty slots\n");
        printf("3. Sort the array by tree root values\n");
        printf("4. Search for a value in a specific tree\n");
        printf("5. Search for a value in all trees\n");
        printf("6. Display a tree (inorder, preorder, postorder)\n");
        printf("7. Show all root values in the array\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // إضافة قيمة إلى شجرة معينة
                printf("Enter the index of the tree and the value to add: ");
                scanf("%d %d", &index, &value);
                if (index < 0 || index >= size) {
                    printf("Error: Index %d is out of bounds (0 to %d).\n", index, size - 1);
                } else {
                    addValue(table, index, value);
                    printf("Value %d added to tree %d.\n", value, index);
                }
                break;

            case 2:
                // ملء الأشجار الفارغة بالقيم العشوائية
                printf("Enter the maximum number of nodes per tree: ");
                scanf("%d", &maxNodes);
                fillEmptyTrees(table, size, maxNodes);
                printf("Empty slots have been filled with random trees.\n");
                break;

            case 3:
                // ترتيب الأشجار باستخدام الترتيب الفقاعي
                bubbleSort(table, size);
                printf("Array sorted by root values of the trees.\n");
                printf("Sorted root values: ");
                for (int i = 0; i < size; i++) {
                    if (table[i].root != NULL)
                        printf("Tree %d Root: %d\n", i, table[i].root->value);
                    else
                        printf("Tree %d is empty\n", i);
                }
                break;

            case 4:
                // البحث عن قيمة في شجرة معينة
                printf("Enter the index of the tree and the value to search for: ");
                scanf("%d %d", &index, &value);
                if (searchInTree(table, size, index, value)) {
                    printf("Value %d found in tree %d.\n", value, index);
                } else {
                    printf("Value %d NOT found in tree %d.\n", value, index);
                }
                break;

            case 5:
                // البحث عن قيمة في جميع الأشجار
                printf("Enter the value to search for in all trees: ");
                scanf("%d", &value);
                searchInAllTrees(table, size, value);
                break;

            case 6:
                // عرض شجرة معينة
                printf("Enter the index of the tree to display: ");
                scanf("%d", &index);
                if (index < 0 || index >= size) {
                    printf("Error: Index %d is out of bounds (0 to %d).\n", index, size - 1);
                } else if (table[index].root == NULL) {
                    printf("The tree at index %d is empty.\n", index);
                } else {
                    printf("Inorder traversal: ");
                    inorderTraversal(table[index].root);  // طباعة الشجرة بتقنية Inorder
                    printf("\nPreorder traversal: ");
                    preorderTraversal(table[index].root); // طباعة الشجرة بتقنية Preorder
                    printf("\nPostorder traversal: ");
                    postorderTraversal(table[index].root); // طباعة الشجرة بتقنية Postorder
                    printf("\n");
                }
                break;

            case 7:
                // عرض قيم الجذور لجميع الأشجار
                printf("Root values of the trees in the array:\n");
                for (int i = 0; i < size; i++) {
                    if (table[i].root != NULL)
                        printf("Tree %d Root: %d\n", i, table[i].root->value);
                    else
                        printf("Tree %d is empty.\n", i);
                }
                break;

            case 0:
                // إنهاء البرنامج
                printf("Exiting the program. Goodbye!\n");
                free(table);  // تحرير الذاكرة المخصصة للجدول
                return;

            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}

// الدالة الرئيسية التي تبدأ البرنامج
int main() {
    printf("Welcome to the binary tree management program !\n");
    menu();  // استدعاء القائمة الرئيسية
    printf("Thank you for using the program. See you soon!!\n");
    return 0;
}