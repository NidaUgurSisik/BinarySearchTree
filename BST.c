#include <stdio.h>
#include <stdlib.h>

struct node
{
	int data;
	struct node *left, *right;
};


void iterativeDelete(struct node**, int);
void searchKey(struct node**, int, struct node**);
struct node *newNode(int);
struct node* recursiveInsert(struct node*, int);
struct node* recursiveDelete(struct node*, int);
void iterativeInsert(struct node**, int);
void inorder(struct node *);
int inordersuccessor(struct node*);
struct node* minimumKey(struct node*);
int recursiveNumOfNodes(struct node*);
int recursiveHeight(struct node*);

int main()
{
	
	struct node* root = NULL;
	int keys[] = { 15, 10, 20, 8, 12, 16 };

	for(int i = 0; i < 6; i++)
		iterativeInsert(&root, keys[i]);
	
	iterativeInsert(&root, 22);
	iterativeInsert(&root, 24);
	inorder(root);
	printf("\n%d %d\n", recursiveNumOfNodes(root), recursiveHeight(root));


	return 0;

}

int recursiveHeight(struct node* root)
{
	
	if(root != NULL){
		int leftHeight, rightHeight;

		leftHeight  = recursiveHeight(root -> left);
		rightHeight = recursiveHeight(root -> right);

		if(leftHeight > rightHeight)
			return leftHeight + 1;
		else
			return rightHeight + 1;

	}

	return 0;

}

int inordersuccessor(struct node* root)
{

	int minimum = root -> data;
	while(root -> left != NULL)
	{
		minimum = root -> left -> data;
		root = root -> left;
	}

	return minimum;
}

struct node* recursiveDelete(struct node* root, int val)
{
	if(root != NULL)
	{

		if(root -> data > val)
			root -> left = recursiveDelete(root -> left, val);
		else if(root -> data < val)
			root -> right = recursiveDelete(root -> right, val);
		else
		{
			if(root -> left == NULL)
				return root -> right;
			else if(root -> right == NULL)
				return root -> left;
			
			root -> data = inordersuccessor(root -> right);
			root -> right = recursiveDelete(root -> right, root -> data);


		}
	}

	return root;
}

void inorder(struct node *root)
{
	if (root == NULL)
		return;

	inorder(root->left);
	printf("%d.", root -> data);
	inorder(root->right);
}


struct node* minimumKey(struct node* curr)
{
	while(curr->left != NULL) {
		curr = curr->left;
	}
	return curr;
}

int recursiveNumOfNodes(struct node* root)
{
	int sum = 0;
	if(root != NULL){

		sum += recursiveNumOfNodes(root -> left);
		sum += recursiveNumOfNodes(root -> right);
		sum++;
	}
	

	return sum;
}


void iterativeDelete(struct node** root, int val)
{

	struct node *parent = NULL, *curr = *root;
	searchKey(&curr, val, &parent);

	if(curr == NULL){
		return;
	}

	if (curr->left == NULL && curr->right == NULL)
	{
		
		if (curr != *root)
		{
			if (parent->left == curr)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		
		else
			*root = NULL;
		
		free(curr);	 
	}

	
	else if (curr->left && curr->right)
	{
		
		struct node* successor  = minimumKey(curr->right);
		int val = successor->data;

		iterativeDelete(root, successor->data);

		curr->data = val;
	}


	else
	{
		
		struct node* child = (curr->left)? curr->left: curr->right;

		
		if (curr != *root)
		{
			if (curr == parent->left)
				parent->left = child;
			else
				parent->right = child;

		}


		else
			*root = child;

		
		free(curr);
	}
}

struct node *newNode(int item) 
{ 
    struct node *temp = (struct node *)malloc(sizeof(struct node)); 
    temp->data = item;
    temp->left = temp->right = NULL; 
    return temp; 
} 

struct node* recursiveInsert(struct node* node, int key) 
{ 
    
    if (node == NULL) return newNode(key); 

    if (key < node->data) 
        node->left  = recursiveInsert(node->left, key); 
    else
        node->right = recursiveInsert(node->right, key);

    return node; 
} 

void searchKey(struct node** curr, int key, struct node** parent)
{
	
	while(*curr != NULL && (*curr) -> data != key)
	{
		*parent = *curr;

		if(key > (*curr) -> data)
			*curr = (*curr) -> right;
		else
			*curr = (*curr) -> left;
		

	}
}

void iterativeInsert(struct node** root, int key)
{
	struct node *parent = NULL, *curr = *root;
	searchKey(&curr, key, &parent);

	if(curr == NULL)
	{
		if(parent != NULL)
		{
			if(parent-> data > key)
				parent -> left = newNode(key);
			else
				parent -> right = newNode(key);
		}

		else
			*root = newNode(key);
	}
}

