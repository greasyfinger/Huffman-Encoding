#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct real
{
    int fq;
    char idx;
    struct real *left;
    struct real *right;
} afq;
afq **car(int *dct)
{
    int n = dct[256] + 1;
    afq **arr = malloc(n * sizeof(afq *));
    int idx = 1;
    for (int i = 0; i < 256; i++)
    {
        if (dct[i] != 0)
        {
            afq *temp = malloc(sizeof(afq));
            temp->fq = dct[i];
            temp->idx = i;
            temp->left = temp->right = NULL;
            arr[idx] = temp;
            idx++;
        }
    }
    return arr;
}
int *indict(FILE *fptr)
{
    int *dct = calloc(257, sizeof(int));
    int n = 0;
    char trv = fgetc(fptr);
    while (trv != EOF)
    {
        int key = trv;
        if (dct[key] == 0)
            n += 1;
        dct[key] += 1;
        trv = fgetc(fptr);
    }
    dct[256] = n;
    return dct;
}
typedef struct heap
{
    afq **arr;
    int hlen;
} heap;
heap *intial(int size)
{
    heap *h = malloc(sizeof(heap));
    h->arr = (afq **)malloc((size + 1) * sizeof(afq *));
    h->hlen = size;
    return h;
}
void swap(afq **a, afq **b)
{
    afq *tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}
void heapify(heap *h, int i)
{
    int left = 0, right = 0;
    if (2 * i <= h->hlen)
        left = 2 * i;
    if ((2 * i + 1) <= h->hlen)
        right = 2 * i + 1;
    int lrg = i;
    if (left != 0)
        lrg = h->arr[lrg]->fq > h->arr[left]->fq ? left : lrg;
    if (right != 0)
        lrg = h->arr[lrg]->fq > h->arr[right]->fq ? right : lrg;
    if (lrg != i)
    {
        swap(&(h->arr[i]), &(h->arr[lrg]));
        heapify(h, lrg);
    }
}
afq *heapmin(heap *h)
{
    swap(&(h->arr[1]), &(h->arr[h->hlen]));
    h->hlen -= 1;
    if (3 <= h->hlen)
        heapify(h, 1);
    return h->arr[(h->hlen) + 1];
}
void byldhp(heap *h)
{
    for (int i = (h->hlen) / 2; i >= 1; i--)
    {
        heapify(h, i);
    }
}
afq *huffing(heap *h)
{
    afq *left, *right;
    while (h->hlen > 1)
    {
        left = heapmin(h);
        right = heapmin(h);
        afq *root = malloc(sizeof(afq));
        root->fq = left->fq + right->fq;
        root->idx = '\0';
        root->left = left;
        root->right = right;
        h->hlen += 1;
        h->arr[h->hlen] = root;
        heapify(h, 1);
    }
    return h->arr[1];
}
void hufcde(afq *root, int **adct, int *ans, int i)
{
    if (root->right)
    {
        ans = (int *)realloc(ans, 1 + sizeof(ans));
        ans[i] = 1;
        hufcde(root->right, adct, ans, i + 1);
    }
    if (root->left)
    {
        ans = (int *)realloc(ans, 1 + sizeof(ans));
        ans[i] = 0;
        hufcde(root->left, adct, ans, i + 1);
    }
    if (root->right == NULL && root->left == NULL)
    {
        adct[root->idx] = malloc(i * sizeof(ans));
        memcpy(adct[root->idx], ans, i * sizeof(int));
        adct[root->idx][i] = -1;
        return;
    }
}
afq *insert(FILE *inptr, char trv, afq *root)
{
    if (trv == '0')
    {
        if (!root)
        {
            root = malloc(sizeof(afq));
            root->fq = 0;
            root->idx = '\0';
            root->left = NULL;
            root->right = NULL;
        }
        root->left = insert(inptr, fgetc(inptr), root->left);
    }
    else if (trv == '1')
    {
        if (!root)
        {
            root = malloc(sizeof(afq));
            root->fq = 0;
            root->idx = '\0';
            root->left = NULL;
            root->right = NULL;
        }
        root->right = insert(inptr, fgetc(inptr), root->right);
    }
    else if (trv != '\0')
    {
        afq *node = malloc(sizeof(afq));
        node->fq = 0;
        node->idx = trv;
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    return root;
}
int outdecompress(afq *root, FILE *inptr, FILE *outptr)
{
    if (root->right == NULL && root->left == NULL)
    {
        fputc(root->idx, outptr);
        return 0;
    }
    else
    {
        char trv = fgetc(inptr);
        if (trv == '0')
            outdecompress(root->left, inptr, outptr);
        else if (trv == '1')
            outdecompress(root->right, inptr, outptr);
        else if (trv == EOF)
            return 1;
    }
    return 0;
}
void decompress(FILE *outptr, FILE *inptr)
{
    char trv = fgetc(inptr);
    afq *root = NULL;
    int n = 0;
    while (trv != '\0')
    {
        if (trv != '0' && trv != '1')
        {
            n += 1;
        }
        trv = fgetc(inptr);
    }
    printf("Generating output File\n");
    rewind(inptr);
    for (int i = 0; i < n; i++)
    {
        root = insert(inptr, fgetc(inptr), root);
    }
    fgetc(inptr);
    n = 0;
    while (n == 0)
    {
        n = outdecompress(root, inptr, outptr);
    }
}
void compress(FILE *outptr, FILE *inptr)
{
    int *dct = indict(inptr);
    heap *h = intial(dct[256]);
    h->arr = car(dct);
    afq **fiar = car(dct);
    int n = dct[256];
    free(dct);
    byldhp(h);
    afq *root = huffing(h);
    int **adct = calloc(256, sizeof(int *));
    int *ans = malloc(sizeof(int));
    hufcde(root, adct, ans, 0);
    free(ans);
    printf("OUTPUT:\n");
    for (int i = 1; i < n + 1; i++)
    {
        printf("%c -> ", fiar[i]->idx);
        int j = 0;
        while (adct[fiar[i]->idx][j] != -1)
        {
            printf("%d", adct[fiar[i]->idx][j]);
            fprintf(outptr, "%d", adct[fiar[i]->idx][j]);
            j++;
        }
        fprintf(outptr, "%c", fiar[i]->idx);
        printf("\n");
    }
    fprintf(outptr, "%c", '\0');
    free(fiar);
    rewind(inptr);
    char trv = fgetc(inptr);
    printf("Generating output File\n");
    int rl = 0;
    int ascii = 0;
    // while (trv != EOF)
    // {
    //     int j = 0;
    //     while (adct[trv][j] != -1)
    //     {
    //         ascii += pow(2 * adct[trv][j], 7 - rl);
    //         rl += 1;
    //         if (rl == 8)
    //         {
    //             fprintf(outptr, "%c", ascii);
    //             rl = 0;
    //             ascii = 0;
    //         }
    //         j++;
    //     }
    //     trv = fgetc(inptr);
    // }
    while (trv != EOF)
    {
        int j = 0;
        while (adct[trv][j] != -1)
        {
            fprintf(outptr, "%d", adct[trv][j]);
            j++;
        }
        trv = fgetc(inptr);
    }
}
int main()
{
    printf("Enter the name of the input file\n");
    char inpfile[100];
    scanf("%s", inpfile);
    int n = strlen(inpfile);
    char inptxt[n];
    strcpy(inptxt, inpfile);
    FILE *inptr = fopen(inptxt, "r");
    printf("Enter the name of the output file\n");
    char outfile[100];
    scanf("%s", outfile);
    n = strlen(outfile);
    char outxt[n];
    strcpy(outxt, outfile);
    FILE *outptr = fopen(outxt, "w");
    printf("Enter mode (0 for compression, 1 for decompression)\n");
    scanf("%d", &n);
    if (n)
    {
        decompress(outptr, inptr);
    }
    else
        compress(outptr, inptr);
    fclose(inptr);
    fclose(outptr);
    return 0;
}