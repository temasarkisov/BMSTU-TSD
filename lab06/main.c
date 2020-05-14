#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define SPACING 5
#define MAX_LEN_HASH_TABLE 100
#define MAX_LEN_WORD 32
#define EMPTY -1
#define REMAINDER_DIVISION 11 // 97 //11 // Остаток от деления.
#define COLLISION 3
#define MAX_LEN_ANSWER 32
#define TRUE 1
#define FALSE 0
#define OK 0
#define GHZ 3300000000
#define CMP_EQ(a, b) (strcmp(a, b) == 0)
#define CMP_LT(a, b) (strcmp(a, b) < 0)
#define CMP_GT(a, b) (strcmp(a, b) > 0)
 
#define MAX_COUNT_COLLISIONS 10
#define LEN_HASH_TABLE 10
 
#define MODE_HASH_TABLE 1
#define MODE_BST 2 // BINARY SEARCH TREE.
#define MODE_BALANCED_TREE 3
 
#define FILE_OPEN_HASH "text.txt" 
#define MAX_LEN_WORD 32
#define EMPTY -1
#include <stdio.h>
 
uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__ (
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r" (high), "=r" (low)
        :: "%rax", "%rbx", "%rcx", "%rdx"
        );
 
    uint64_t ticks = ((uint64_t)high << 32) | low;
 
    return ticks;
}
 
 
 
 
typedef struct
{
    char name[MAX_LEN_WORD];
} value_s;
 
typedef struct hash_s
{
    int hash_index;
    char name1[MAX_LEN_WORD];
    value_s hash_value;
    struct hash_s *next;
} hash_s;
 
// ДДП _BINARY_SEARCH_TREE_
typedef struct bin_search_s
{
    char data[MAX_LEN_WORD];
    struct bin_search_s *left;
    struct bin_search_s *right;
    struct bin_search_s *parent;
} bin_search_s;
 
//АВЛ
typedef struct node_t
{
    char value[MAX_LEN_WORD]; // значение в вершине
    unsigned int height;      // высота дерева в данной вершине
    struct node_t *left;
    struct node_t *right;
    struct node_t *parent;
} node_t;
 
typedef struct
{
 
    double time_hash_find_start;
    double time_hash_find_end;
 
    double time_hash_add_start;
    double time_hash_add_end;
 
    double time_bst_find_start;
    double time_bst_find_end;
    double time_avl_find_start;
    double time_avl_find_end;
 
    double time_bst_add_start;
    double time_bst_add_end;
 
    double time_file_add_start;
    double time_file_add_end;
 
    double time_avl_add_start;
    double time_avl_add_end;
 
    double time_balance_tree_start;
    double time_balance_tree_end;
 
} time_s;
 
typedef struct
{
    int count_hash_find;
    int count_bst_find;
    int count_avl_find;
} count_s;
 
 
int count_word(FILE *f)
{
    int count = 0;
    char word[MAX_LEN_WORD];
 
    while (!feof(f) && fscanf(f, "%s", word))
    {
        count++; // Cчитаем кол-во слов.}
    }
    return count;
}
 
int instruction()
{
    /* printf("\n1.Вывод хеш-таблицы\n2.Вывод дерева\n3.Добавить элемент\n4.Найти элемент\n5.Заполнить из файла\n6.Сбалансировать дерево\n7.Вывод АВЛ - дерева\n8.Сравнение эффективности по добавлению элементов\n9.Сравнение эффективности по поиску элемента\n0.Выход\n");
    printf("Выберите действие: "); */

    printf("\n\t\tМЕНЮ:\n");
    printf("\t1  -  Сформировать и вывести хеш-таблицу\n");
    printf("\t2  -  Сформировать и вывести дерево\n");
    printf("\t3  -  Сформировать и вывести АВЛ дерево\n");
    printf("\t4  -  Добавление элемента (слово)\n");
    printf("\t5  -  Найти элемент\n");
    printf("\t6  -  Статистика добавления элементов\n");
    printf("\t7  -  Статистика поиска элементов\n");
    printf("\n\t0  -  Выход\n");
    printf("\n\tНомер опции  -  ");
    
    return 0;
}
 
unsigned int height(node_t *p)
{
    return p ? p->height : 0;
}
 
int balance_factor(node_t *p)
{
    return height(p->right) - height(p->left);
}
 
void fix_height(node_t *p)
{
    unsigned int hl = height(p->left);
    unsigned int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}
 
 
int is_empty_hash_table(hash_s **hash_table, int count)
{
    printf("%d\n", count);
    for (int i = 0; i < count; i++)
        if (hash_table[i] != NULL)
            return FALSE;
    return TRUE;
}
 
node_t *rotate_right(node_t *p)
{
    node_t *q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}
 
node_t *rotate_left(node_t *q)
{
    node_t *p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}
 
node_t *create_node(char word[MAX_LEN_WORD])
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    if (!node)
        return NULL;
 
    node->height = 1;
    node->left = (node->right = NULL);
    strcpy(node->value, word);
    return node;
}
 
node_t *balance(node_t *p)
{
    fix_height(p);
 
    if (balance_factor(p) == 2)
    {
        if (balance_factor(p->right) < 0)
            p->right = rotate_right(p->right);
        return rotate_left(p);
    }
 
    else if (balance_factor(p) == -2)
    {
        if (balance_factor(p->left) > 0)
            p->left = rotate_left(p->left);
        return rotate_right(p);
    }
    // балансировка не нужна.
    return p;
}
 
 
int output_hash_table(FILE *f, hash_s **hash_table, int count)
{
    char word[MAX_LEN_WORD];
 
    hash_s *temp;
 
    printf("\t%4s           %25s\n\n", "ХЭШ", "ЗНАЧЕНИЯ");
 
    // Итерируемся по всему массиву.
    for (int i = 0; i < count; i++)
    {
        // Если есть слово, то выводим слово.
        if (hash_table[i])
        {
            printf("\t%4d ", hash_table[i]->hash_index);
            temp = hash_table[i];
            while (temp)
            {
                printf("      ->      %8s", temp->hash_value.name);
                temp = temp->next;
            }
            puts("");
        }
    }
    return 0;
}
 
void print_bin_search(bin_search_s *root, const char *dir, int level)
{
    if (root)
    {
        printf("lvl %d %s = %s(От вершины %s)\n", level, dir, root->data, root->parent->data);
        print_bin_search(root->left, "left", level + 1);
        print_bin_search(root->right, "right", level + 1);
    }
}

void print_tree(bin_search_s *root, int space)
{
    if (root == NULL)
        return;
 
    space += SPACING;
 
    print_tree(root->right, space);
 
    printf("\n");
    for (int i = SPACING; i < space; i++)
        printf(" ");
    printf("%s\n", root->data);
 
    print_tree(root->left, space);
} 

void print_tree_avl(node_t *root, int space)
{
    if (root == NULL)
        return;
 
    space += SPACING;
 
    print_tree_avl(root->right, space);
 
    printf("\n");
    for (int i = SPACING; i < space; i++)
        printf(" ");
    printf("%s\n", root->value);
 
    print_tree_avl(root->left, space);
}
 
bin_search_s *create_bin_search(char value[MAX_LEN_WORD], bin_search_s *parent)
{
    bin_search_s *tmp = (bin_search_s *)malloc(sizeof(bin_search_s));
    tmp->left = tmp->right = NULL;
    strcpy(tmp->data, value);
    tmp->parent = parent;
    return tmp;
}
 
void insert_bin_search(bin_search_s **head, char value[MAX_LEN_WORD])
{
    bin_search_s *tmp = NULL;
    bin_search_s *ins = NULL;
 
    if (*head == NULL)
    {
        *head = create_bin_search(value, NULL);
        return;
    }
 
    tmp = *head;
    while (tmp)
    {
        if (CMP_GT(value, tmp->data))
        {
            if (tmp->right)
            {
                tmp = tmp->right;
                continue;
            }
            else
            {
                tmp->right = create_bin_search(value, tmp);
                return;
            }
        }
        else if (CMP_LT(value, tmp->data))
        {
            if (tmp->left)
            {
                tmp = tmp->left;
                continue;
            }
            else
            {
                tmp->left = create_bin_search(value, tmp);
                return;
            }
        }
        else
        {
            return;
        }
    }
}
 
int scanf_answer()
{
    char answer_char[MAX_LEN_ANSWER];
 
    scanf("%s", answer_char);
 
    int answer = atoi(answer_char);
    while (!answer)
    {
        if (strcmp(answer_char, "0") == 0)
            break;
        printf("\nВаш ответ мне не понятен.");
        printf("\nВыберите действие:");
 
        scanf("%s", answer_char);
        answer = atoi(answer_char);
    }
 
    return answer;
}
 
 
void add_element_in_file(FILE *f, char word[MAX_LEN_WORD])
{
    fprintf(f, " %s", word);
}

/* int hash_function(char *s, int n)
{
    unsigned long code_pow = 0;

    do
    {
        code_pow += *s;;
    } while (*(s++));

    return code_pow % n;
} */


int hash_function(char *s, int n)
{
    unsigned long pow = 1, code_pow = 0;
    int pow_mult = 26;
 
    do
    {
        code_pow += *s * pow;
        pow *= pow_mult;
    } while (*(s++));
   
 
    return code_pow % n;
}

hash_s *add_list(char word[MAX_LEN_WORD], int len)
{
    hash_s *temp = (hash_s *)malloc(sizeof(hash_s));
 
    strcpy(temp->hash_value.name, word);
    strcpy(temp->name1, word);
    temp->hash_index = hash_function(word, len);
    temp->next = NULL;
 
    return temp;
}
 
 
int add_element_hash_table(FILE *f, hash_s **hash_table, char word[MAX_LEN_WORD], int *collision, int len)
{
    // Узнаем хeш слова.
    int h = hash_function(word, len);
    int count = 1;
   
    hash_s *temp = hash_table[h];
 
    // Если по данному хешу уже есть слово.
    if (hash_table[h])
    {
        // printf("!%d\n", strcmp(temp->hash_value.name, word));
        if (strcmp(temp->hash_value.name, word) == 0)
            return 0;
 
        while (temp->next)
        {
            temp = temp->next;
            count++;
            // printf("!%d\n", strcmp(temp->hash_value.name, word));
            if (strcmp(temp->hash_value.name, word) == 0)
                return 2;
 
            // printf("Collision%d %d\n", count, *collision);
            if (count == COLLISION - 1)
            {
                (*collision)++;
            }
            if (*collision > 100)
            {
                printf("Коллизия!(Hash = %d)\n", h);
                return 0;
            }
        }
        temp->next = add_list(word, len);
    }
    else
        hash_table[h] = add_list(word, len);
 
    return 1;
}
 
node_t *insert(node_t *p, char word[MAX_LEN_WORD]) // вставка ключа k в дерево с корнем p
{
    if (!p)
        return create_node(word);
 
    if (strcmp(p->value, word) > 0)
        p->left = insert(p->left, word);
 
    else if (strcmp(p->value, word) < 0)
        p->right = insert(p->right, word);
 
    return balance(p);
}
 
node_t *balance_tree(bin_search_s *bts, node_t **tree_avl)
{
    if (bts)
    {
        *tree_avl = insert(*tree_avl, bts->data);
        balance_tree(bts->left, tree_avl);
        balance_tree(bts->right, tree_avl);
    }
 
    return *tree_avl;
}
 
bin_search_s *find_bin_search(bin_search_s *root, char value[MAX_LEN_WORD], count_s *count_h)
{
    while (root)
    {
        if (CMP_GT(root->data, value))
        {
            (count_h->count_bst_find)++;
            root = root->left;
            continue;
        }
        else if (CMP_LT(root->data, value))
        {
            (count_h->count_bst_find)++;
            root = root->right;
            continue;
        }
        else
        {
            return root;
        }
    }
    return NULL;
}
 
node_t *find_avl(node_t *p, char word[MAX_LEN_WORD], count_s *count_all)
{
    node_t *target;
 
    if (!p)
        return NULL;
 
    if (strcmp(word, p->value) < 0)
    {
        (count_all->count_avl_find)++;
        target = find_avl(p->left, word, count_all);
    }
    else if (strcmp(word, p->value) > 0)
    {
        (count_all->count_avl_find)++;
        target = find_avl(p->right, word, count_all);
    }
    else
        return p;
 
    return target;
}
 
int find_hash(hash_s **hash_table, char word[MAX_LEN_WORD], count_s *count_h, int len)
{
    int h = hash_function(word, len);
 
    while (hash_table[h])
    {
        if (!strcmp(word, hash_table[h]->hash_value.name))
        {
            return TRUE;
        }
        else
        {
            (count_h->count_hash_find)++;
        }
 
        hash_table[h] = hash_table[h]->next;
    }
 
    return FALSE;
}
 
int input_hash_table(FILE *f, hash_s **hash_table, int *collision, int len)
{
    char word[MAX_LEN_WORD]; // Слово.
    int count = 0;           // Кол-во слов.
 
    // Итерируемся, пока не конец файла и записываем слово в word.
    while (!feof(f) && fscanf(f, "%s", word))
    {
        count += add_element_hash_table(f, hash_table, word, collision, len);
    }
 
    return count; // Возвращаем кол-во слов.
}
 
int input_bin_search(FILE *f, bin_search_s **root)
{
    char word[MAX_LEN_WORD]; // Слово.
    int count = 0;           // Кол-во слов.
 
    while (!feof(f) && fscanf(f, "%s", word))
    {
        insert_bin_search(root, word); // Добавляем элемент
        count++;                       // Считаем кол-во слов.
    }
 
    return count;
}
 
 
 
 
void print_avl(node_t *root, const char *dir, int level)
{
    if (root)
    {
        printf("lvl %d %s = %s (left %s) (right %s)\n", level, dir, root->value, root->left->value, root->right->value);
        print_avl(root->left, "left", level + 1);
        print_avl(root->right, "right", level + 1);
    }
}
 
int main(int argc, const char * argv[])
{
    char word[MAX_LEN_WORD];
    int answer = -1;
    time_s my_time = {0};
    count_s count_all = {0};
 
    int collision = 0;
 
    FILE *f = fopen(FILE_OPEN_HASH, "r");
    if(!f)
    {
        printf("File was not open!\n");
    }
    int count_hash = 1;
    //printf("Кол-во слов в файле : %d\nВведите размерность Хеш-таблицы : ", count_word(f));
    printf("Введите размерность Хеш-таблицы (Кол-во слов  -  %d)  -  ", count_word(f)); 
    fseek(f, 0, 0);
    scanf("%d", &count_hash);
 
    hash_s **hash_table = (hash_s **)malloc(sizeof(hash_s *) * count_hash);
    int flag;
    int data;
 
    bin_search_s *root = NULL; // ДДП
    bin_search_s *find_root = NULL;
 
    node_t *tree_avl = NULL; // АВЛ
    node_t *find_node_avl = NULL;

    f = fopen(FILE_OPEN_HASH, "r");
 
    input_hash_table(f, hash_table, &collision, count_hash);
    fseek(f, 0, 0);
    input_bin_search(f, &root);
 
    printf("\n\tТаблица успешно сформирована!\n");
 
    fclose(f);

    while (answer)
    {
        instruction();
        answer = scanf_answer();
        printf("\n");
 
        switch (answer)
        {
               
 
        case 0:
            break;
        case 1:
            if (is_empty_hash_table(hash_table, count_hash) == TRUE)
            {
                printf("\tТаблица пуста!\n");
            }
            else
            {
                output_hash_table(stdout, hash_table, count_hash);
            }
            break;
        case 2:
            if (root)
            {
                //print_bin_search(root, "root", 0);
                print_tree(root, 0);
            }
            else
            {
                printf("\tДерево пусто!\n");
            }
            break;
        case 3:
            if (root)
            {
                uint64_t start_time_balance = tick();
                tree_avl = balance_tree(root, &tree_avl);
                uint64_t end_time_balance = tick();
 
                printf("\tВремя затраченное на балансировку  -  %llu\n", (end_time_balance - start_time_balance) / GHZ);
            }
            else
            {
                printf("Заполните дерево, чтобы получить АВЛ дерево!\n");
            }
 
            if (tree_avl)
            {
                //print_avl(tree_avl, "root", 0);
                print_tree_avl(tree_avl, 0);
            }
            else
            {
                printf("\tСбалансируйте дерево, чтобы получить АВЛ дерево!\n");
            }
 
            break;
        case 4:
            printf("\tВведите элемент, который хотели бы добавить (слово)  -  ");
 
            scanf("%s", word);
 
            uint64_t start_time_tree = tick();
            insert_bin_search(&root, word);
            uint64_t end_time_tree = tick();
 
            printf("\tВремя добавления в дерево  -  %llu\n", (end_time_tree - start_time_tree));
 
            uint64_t start_time_hash = tick();
            flag = add_element_hash_table(stdin, hash_table, word, &collision, count_hash);
            uint64_t end_time_hash = tick();
 
            printf("\tВремя добавления в хеш-таблицу  -  %llu\n", (end_time_hash - start_time_hash));
 
            f = fopen(FILE_OPEN_HASH, "a");
            uint64_t start_time_file = tick();
            add_element_in_file(f, word);
            uint64_t end_time_file = tick();
            fclose(f);
 
            printf("\tВремя добавления в файл  -  %llu\n", (end_time_file - start_time_file) / 3);
 
            if (tree_avl)
            {
                uint64_t start_time_avl_tree = tick();
                tree_avl = insert(tree_avl, word);
                tree_avl = balance_tree(root, &tree_avl);
                uint64_t end_time_avl_tree = tick();
 
                printf("\tВремя добавления в АВЛ дерево  -  %llu\n", (end_time_avl_tree - start_time_avl_tree));
            }
 
            break;
        case 5:
            printf("\tВведите слово, которое нужно найти  -  ");
 
            scanf("%s", word);
 
            if (root)
            {
                count_all.count_hash_find = 0;
                count_all.count_avl_find = 0;
                count_all.count_bst_find = 0;
 
                my_time.time_bst_find_start = clock();
                find_root = find_bin_search(root, word, &count_all);
                my_time.time_bst_find_end = clock();
 
                if (find_root)
                {
                    printf("\tКол-во сравнений (ДДП)  -  %d\n", count_all.count_bst_find + 1);
                }
 
            }
 
            if (tree_avl)
            {
                my_time.time_avl_find_start = clock();
                find_node_avl = find_avl(tree_avl, word, &count_all);
                my_time.time_avl_find_end = clock();
 
                if (find_node_avl)
                {
 
                    printf("\tКол-во сравнений (АВЛ)  -  %d\n", count_all.count_avl_find + 1);
                }
            }
 
            my_time.time_hash_find_start = clock();
            data = find_hash(hash_table, word, &count_all, count_hash);
            my_time.time_hash_find_end = clock();
 
            if (!data)
            {
                printf("\nНет данного элемента.\n");
            }
            else
            {
                printf("Кол-во сравнений (Хеш-таблица): %d\n", count_all.count_hash_find + 1);
            }
 
            break; 
        case 6:
            printf("Время для добавления 100 элементов\n");
            char * ar[100] = {"a", "b", "c", "d", "e", "f", "g", "h", "n", "q", "w", "к", "p", "o", "l", "z", "f", "x", "y",
            "r", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
            char matrix[120][120];
           
            for (int i = 0; i < 120; i++)
                strcpy(matrix[i], "\0");
           
            for (int i = 0; i < 100; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    strcat(matrix[i], ar[rand() % 20]);
                }
           
            }
           
            //Добавление в ДДП
            uint64_t start_time_ddp = tick();
            for (int i = 0; i < 100; i++)
            {
                insert_bin_search(&root, matrix[i]);
            }
            uint64_t end_time_ddp = tick();
            //Добавление в АВЛ
            uint64_t start_time_avl = tick();
            for (int i = 0; i < 100; i++)
            {
                tree_avl = insert(tree_avl, matrix[i]);
            }

            tree_avl = balance_tree(root, &tree_avl);
            uint64_t end_time_avl = tick();
           
            //Добавление в хэш
            uint64_t start_time_hash_100 = tick();
            for (int i = 0; i < 100; i++)
            {
                char string[100] = "\0";
                strcpy(string, matrix[i]);
                flag = add_element_hash_table(stdin, hash_table, string, &collision, count_hash);
            }
            uint64_t end_time_hash_100 = tick();
           
            FILE *file_pointer = fopen("text.txt", "w");
            uint64_t start_time_file_100 = tick();
                
                for (int i = 0; i < 100; i++)
                {
                    fprintf(file_pointer, "%s ", matrix[i]);
                }
            uint64_t end_time_file_100 = tick();
            fclose(file_pointer);
               
            printf("%llu - Время добавления 100 элементов в ддп\n", (end_time_ddp - start_time_ddp));
            printf("%llu - Время добавления 100 элементов в авл\n", (end_time_avl - start_time_avl));
            printf("%llu - Время добавления 100 элементов в Хэш\n", (end_time_hash_100 - start_time_hash_100));
            printf("%llu - Время добавления 100 элементов в файл\n", (end_time_file_100 - start_time_file_100));
            printf("\n\n");
            printf("%llu - Среднее время добавления одного элемента в ддп\n", (end_time_ddp - start_time_ddp) / 100);
            printf("%llu - Среднее время добавления одного элемента в авл\n", (end_time_avl - start_time_avl) / 100);
            printf("%llu - Среднее время добавления одного элемента в хэш\n", (end_time_hash_100 - start_time_hash_100) / 100);
            printf("%llu - Среднее время добавления одного элемента в файл\n", (end_time_file_100 - start_time_file_100) / 100);
            break;
    case 7:
        printf("Сравнение поиска элемента\n");
        uint64_t sum_time_find_ddp = 0;
        int count_sum_find_ddp = 0;
        uint64_t sum_time_find_avl = 0;
        int count_sum_find_avl = 0;
        uint64_t sum_time_find_hash = 0;
        int count_sum_find_hash = 0;
        uint64_t sum_time_find_file = 0;
        int count_sum_find_file = 0;
        int check;
        char string_2[100] = "\0";
 
        FILE *file_ptr = fopen("text.txt", "r");
        while (1)
        {
            check = fscanf(file_ptr, "%s", string_2);
            if (check == -1)
                break;
            if (root)
            {
                count_all.count_hash_find = 0;
                count_all.count_avl_find = 0;
                count_all.count_bst_find = 0;
 
                uint64_t start_time_find_ddp = tick();
                find_root = find_bin_search(root, string_2, &count_all);
                uint64_t end_time_find_ddp = tick();
               
                sum_time_find_ddp += end_time_find_ddp - start_time_find_ddp;
 
                if (find_root)
                {
                    //printf("Кол-во сравнений (ДДП): %d\n", count_all.count_bst_find + 1);
                    count_sum_find_ddp += count_all.count_bst_find + 1;
                }
            }
           
           
            if (tree_avl)
            {
                uint64_t start_time_find_avl = tick();
                find_node_avl = find_avl(tree_avl, string_2, &count_all);
                uint64_t end_time_find_avl = tick();
                sum_time_find_avl += end_time_find_avl - start_time_find_avl;
                if (find_node_avl)
                {
                  //  printf("Кол-во сравнений (АВЛ): %d\n", count_all.count_avl_find + 1);
                    count_sum_find_avl += count_all.count_avl_find + 1;
                }
            }
 
            uint64_t start_time_find_hash = tick();
            data = find_hash(hash_table, string_2, &count_all, count_hash);
            uint64_t end_time_find_hash = tick();
           
            sum_time_find_hash += end_time_find_hash - start_time_find_hash;
           
            if (!data)
            {
                //printf("\nНет данного элемента.\n");
            }
            else
            {
               // printf("Кол-во сравнений (Хеш-таблица): %d\n", count_all.count_hash_find + 1);
                count_sum_find_hash += count_all.count_hash_find + 1;
            }

            FILE *file_pointer = fopen("text.txt", "w");
            char word[20];
            uint64_t start_time_file_100 = tick();
                for (int i = 0; i < 100; i++)
                {
                    fscanf(file_pointer, "%s ", word);
                    //strcmp(word, "gogogo")
                    count_sum_find_file++;
                }
            uint64_t end_time_file_100 = tick();
            sum_time_find_file += end_time_file_100 - start_time_file_100;
            fclose(file_pointer);
   
        }
        fclose(file_ptr);
       
        printf("Время  -  %llu и количесто сравнений  -  %d всех слов в таблицу ДДП\n", (sum_time_find_ddp), count_sum_find_ddp);
               
        printf("Время  -  %llu и количесто сравнений  -  %d всех слов в таблице АВЛ\n", (sum_time_find_avl), count_sum_find_avl);
               
        printf("Время  -  %llu и количесто сравнений  -  %d всех слов в хеше\n", (sum_time_find_hash), count_sum_find_hash);

        printf("Время  -  %llu и количесто сравнений  -  %d всех слов в файл\n", (sum_time_find_file), count_sum_find_file);
               
        break;
               
        default:
            printf("\tНет данного действия.\n");
            break;
        }
    }
 
    printf("\tЗавершение программы!\n");
 
    return OK;
}
