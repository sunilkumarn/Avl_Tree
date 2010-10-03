#include<stdio.h>
#include<stdlib.h>
#include"decl.c"
struct node{
	int data;
	struct node *parent,*left,*right;
}*p,*root=0;

void insert(struct node* move,int item)
{
		if(move==0 && move==root) root=create_node(move,item);
		else if((item>move->data) && (move->right!=0)) return insert(move->right,item);
		else if((item<move->data) && (move->left!=0)) return insert(move->left,item);
		else if(item>move->data) move->right=create_node(move,item);
		else if(item<move->data) move->left=create_node(move,item);
}

struct node* create_node(struct node* move,int item)
{
		struct node* temp;
		temp=malloc(sizeof(struct node));
		temp->data=item;
		temp->right=temp->left=0;
		temp->parent=move;
		return temp;
}

struct node* delete_replace(struct node* victim)
{
		struct node* t;
		if((!victim->right) && (!victim->left)) return victim;
		else if(victim->right)
		{
				if(!victim->right->left) return victim->right;
				else{
						for(t=victim->right;t->left!=0;t=t->left);
						return t;}
		}
		else if(victim->left)
		{
				if(!victim->left->right) return victim->left;
				else{
						for(t=victim->left;t->right!=0;t=t->right);
						return t;}
		}
}
		
void parent_change(struct node* min,struct node* p)
{
		min->parent=p->parent;
		if(p->parent && p==p->parent->right) p->parent->right=min;
		else if(p->parent && p==p->parent->left) p->parent->left=min;
		else root=min;
}

struct node* p_delete(int item)
{
		struct node *p,*min,*temp;
		p=find_pos(item,root);
		min=delete_replace(p);
		if(p->right){
			if(min!=p->right){
				min->parent->left=0;
				min->right=p->right;
				min->right->parent=min;}
			if(p->left){
				min->left=p->left;
				min->left->parent=min;
				parent_change(min,p);}}
		else if(min==p->left){
				min->right=0;
				parent_change(min,p);}
		else{
			if(p->parent){
			if(p==p->parent->right) p->parent->right=0;
			else p->parent->left=0;}}
		free(p);
		return min;
}


struct node* find_pos(int item,struct node *move)
{
		if (item>move->data) return find_pos(item,move->right);
		else if(item<move->data) return find_pos(item,move->left);
		else return move;
}

int height(struct node* cur)
{
		int l,r;
		if(cur)
		{
			l=1+height(cur->left);
			r=1+height(cur->right);
			return l>r?l:r;
		}
		else
		return 0;
}


int bal_fac(struct node* p)
{
		if(p)
			return height(p->left) - height(p->right);
}


void rotate_right(struct node* main,struct node* pivot)
{
		struct node *temp, *hold=0;
		temp = main;
		pivot -> parent = main -> parent;
		if(main->parent!=0&&main==main->parent->left)
		main->parent->left=pivot;
		else if(main->parent!=0&&main==main->parent->right)
		main->parent->right=pivot;
		else
		{
		pivot->parent=0;
		root=pivot;
		}
		if (pivot -> right)
			hold = pivot -> right;
		pivot -> right = main;
		pivot -> right -> left = hold;
		if(hold)
		hold->parent=pivot->right;
		main -> parent = pivot;
}

void rotate_left(struct node* main,struct node* pivot)
{
		struct node *temp, *hold=0;
		temp = main;
		pivot -> parent = temp -> parent;
		if(main->parent!=0&&main==main->parent->right)
		main->parent->right=pivot;
		else if(main->parent!=0&&main==main->parent->left)
		main->parent->left=pivot;
		else
		{
			pivot->parent=0;
			root=pivot;
		}
		if (pivot -> left)
			hold = pivot -> left;
		pivot -> left = main;
		pivot -> left -> right = hold;
		if(hold)
		hold->parent=pivot->left;
		main -> parent = pivot;
}
void balance(struct node* p)
{

		if(bal_fac(p)==2 && bal_fac(p->left)>=0) rotate_right(p,p->left);
		if(bal_fac(p)==-2 && bal_fac(p->right)<=0)rotate_left(p,p->right);
		if(bal_fac(p)==-2 && bal_fac(p->right)>=0){
				rotate_right(p->right,p->right->left);
				rotate_left(p,p->right);}
		if(bal_fac(p)==2 && bal_fac(p->left)<=0){
				rotate_left(p->left,p->left->right);
				rotate_right(p,p->left);}
}

void self_bal(struct node *par_node)
{
		while(par_node->parent!=0)
		{
			balance(par_node->parent);
			if(par_node->parent) par_node=par_node->parent;
		}
}

void my_insert(int item)
{
		insert(root,item);
		if(root!=0)
		self_bal(find_pos(item,root));
}

void my_delete(int item)
{
		struct node* par;
		par=p_delete(item);
		if(par->left) self_bal(par->left);
		else if(par->right) self_bal(par->right);
		else self_bal(par);
}

void inorder(struct node *point)
{
		if (point->left!=0) inorder(point->left);
		printf("%d ",point->data);
		if (point->right!=0) inorder(point->right);
}
	
void preorder(struct node *point)
{
		printf("%d ",point->data);
		if (point->left!=0) preorder(point->left);
		if (point->right!=0) preorder(point->right);
}

void postorder(struct node *point)
{
		if (point->left!=0) postorder(point->left);
		if (point->right!=0) postorder(point->right);
		printf("%d ",point->data);
}

void traverse(int notation)
{
		if(notation==1) 
		{
				printf("\n\n");
				printf("inorder  \t:");
				inorder(root);
		}
		if(notation==2) 
		{
				printf("\n\n");
				printf("preorder  \t:");
				preorder(root);
		}
		if(notation==3) 
		{	
				printf("\n\n");
				printf("postorder  \t:");
				postorder(root);
		}
}
main()
{
		my_insert(23);
		my_insert(17);
		my_insert(41);
		my_insert(16);
		my_insert(19);
		my_insert(18);
		my_insert(85);
		my_insert(14);
		my_insert(12);
		my_delete(16);
		/* 1 for inorder , 2 for preorder and 3 for postorder traversals*/
		traverse(1);
		traverse(2);
		traverse(3);
		printf("\n\n");
}


