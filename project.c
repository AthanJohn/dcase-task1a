#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define WORDLEN 30



typedef enum {FALSE,TRUE} orderT;
struct list {
	struct list *next;
	struct list *prev;
	orderT order;
	union {
		char *data;
		int counter;
	} lunion;
};
typedef struct list listT;




char *getWord(char *filename)  {
	char formatstr[15], *word;
	static FILE *input;
	static int firstTime = 1;
	if (firstTime) { 
		input = fopen(filename, "r");
		if (input == NULL) {
			printf("ERROR: Could not open file \"%s\"\n", filename);
			exit(1);
		}
		firstTime = 0;
	}
	word = (char*)malloc(sizeof(char)*WORDLEN);
	if (word == NULL) {
		printf("ERROR: Memory allocation error in getWord\n");
		exit(1);
	}
	sprintf(formatstr, "%%%ds", WORDLEN-1);
	fscanf(input, formatstr, word);
	if (feof(input)) {
		fclose(input);
		firstTime = 1;
		return NULL;
	}
	return word;
}

listT *eksodos() {
	return NULL;
}


int find_word(char *wword,listT *head3) {
	listT *curr;
	int check=0;
	
	curr=(listT *)malloc(sizeof(listT));
	if(curr==NULL) {
		printf("problem\n");
		exit(1);
	}
	for(curr=head3->next;curr!=head3;curr=curr->next) {
		if(strcmp(wword,curr->lunion.data)==0) {
			
			check=1;
			break;
		}
	}
	if(check==0) {
		return 1;
	}
	return 0;
}

void add_node_ordered(listT *head3,char *buffer1) {
	listT *curr,*n_node;
	
	
	n_node=(listT *)malloc(sizeof(listT));
	if(n_node==NULL){
		printf("Problem\n");
		exit(1);
	}
	n_node->lunion.data=strdup(buffer1);
	for(curr=head3;strcmp(curr->lunion.data,n_node->lunion.data)>0;curr=curr->next) {
	}
	n_node->next=curr->next;
	n_node->prev=curr;
	n_node->next->prev=n_node;
	n_node->prev->next=n_node;
	head3->lunion.counter++;
	
}



void words_for_third_list(int m,listT *head2,char *check_word,listT *head3) {  /*m=mikos leksewn*/
	listT *curr;
	char *buffer,*buffer1;
	int i,j,counter=0;
	buffer1=(char *)malloc(WORDLEN*sizeof(char));
	buffer=(char *)malloc(WORDLEN*sizeof(char));
	curr=(listT *)malloc(sizeof(listT));
	if((buffer1==NULL)||(buffer=NULL)||(curr=NULL)) {
		printf("Problem\n");
		exit(1);
	}
	buffer=strdup(check_word);
	for(curr=head2->next;curr!=head2;curr=curr->next) {
		strcpy(buffer1,curr->lunion.data);
		for(i=0;i<=strlen(buffer)-1;i++) {
			for(j=0;j<=strlen(buffer1)-1;j++) {
				if (buffer[i]==buffer1[j]) {
					counter++;
				}
			}
		}
		if(counter==m-1) {
			add_node_ordered(head3,buffer1);
		}
	}
}


char *find_random_word(int ran_num,listT *head2) {
	
	int i;
	listT *curr;
	char *ran_word;
	
	curr=(listT *)malloc(sizeof(listT));
	if(curr==NULL) {
		printf("problem\n");
		exit(1);
	}
	curr=head2;
	for(i=1;i<=ran_num;i++) {
		curr=curr->next;
	}
	ran_word=(char *)malloc(WORDLEN*sizeof(char));
	strcpy(ran_word,curr->lunion.data);
	return ran_word;
}


void add_node(char *datword,listT *head) {
	listT *new_node;
	new_node=(listT *)malloc(sizeof(listT));
	if (new_node==NULL) {
		printf("Problem\n");
		exit(1);
	}
	
	new_node->lunion.data=strdup(datword);
	new_node->next=head->next;
	new_node->prev=head;
	new_node->next->prev = new_node;
	new_node->prev->next = new_node;
	head->lunion.counter++;
}

void add_word_same_len(int len,char *filename,listT *head2) {
	char *word;
	
	word=getWord(filename);
	while (word!=NULL) {
		if(strlen(word)==len) {
			add_node(word,head2);
		}
		word=getWord(filename);
	}
	if(head2->lunion.counter<2) {
		printf("to paixnidi exei ligoteres apo 2 lekseis kai epomenws den mporei na sunexistei.\n");
		head2=eksodos();
		exit(1);
	}
}

void add_node_list1(char *ins_word,listT *head1) {
	listT *new_node;
	new_node=(listT *)malloc(sizeof(listT));
	if (new_node==NULL) {
		printf("Problem\n");
		exit(1);
	}
	new_node->lunion.data=strdup(ins_word);
	new_node->next=head1;
	new_node->prev=head1->prev;
	new_node->next->prev = new_node;
	new_node->prev->next = new_node;
	head1->lunion.counter++;
}

void print_list1(listT *head1) {


	listT *current;
	for (current = head1->next; current != head1; current = current->next) {
			printf("%s ", current->lunion.data);
			if(current!=head1->prev) {
				printf("--> ");
			}
	}
	printf("\n");


}

void print_list3(listT *head3) {
	listT *curr;
	int counter;
	for (curr=head3->next;curr!=head3;curr=curr->next) {
		printf("%s ",curr->lunion.data);
		counter++;
		if(counter%4==0) {
			printf("\n");
		}
	}
	if(counter%4!=0) {
		printf("\n:");
	}
}

listT *init_list(orderT order) {
	listT *head;
	head=(listT *)malloc(sizeof(listT));
	if (head == NULL) {
		printf("Problem\n");
		return(NULL);
	}
	head->next=head;
	head->prev=head;
	head->lunion.counter=0;
	head->order=order;
	return head;
}


int epeksergasia_orismatwn(int a,char *b[]) {
	
	int num; /*metatrepw string se int*/
	
	
	if (a<4) {
		printf("Insufficient arguments.\n");
		printf("project LENGTH STEPS DICTIONARY\n\tLENGTH: requested length of word.\n\tSTEPS: requested number of steps. Must be >0\n\tDICTIONARY: name of dictionary file\n");
		
		return (0);
	}
	else {
		
		if (a>4) {
			printf("Too many arguments.\n");
			printf("project LENGTH STEPS DICTIONARY\n\tLENGTH: requested length of word.\n\tSTEPS: requested number of steps. Must be >0\n\tDICTIONARY: name of dictionary file\n");
		
			return (0);
		}
	}
	num=atoi(b[2]);
	while(num<=0) {
		printf("You may not have fewer than one steps. Specify a different number of steps: ");
		scanf(" %s",b[2]);
		num=atoi(b[2]);
	}
	return (1);
}
	
	
	


int main(int argc, char *argv[]) {     /*argv[1]=mhkos 2 leksewn argv[2]=vimata argv[3]=arxeio leksikou*/
	
	
	
	listT *head1; /*sth list1 apo8hkeuontai oi lekseis tou monopatiou ka8e xronikh stigmh*/
	listT *head2; /*sth list2 apo8hkeuontai oles oi lekseis tou sugkekrimenou mikous*/
	listT *head3; /*sth list3 apo8hkeuontai oles oi lekseis pou einai dia8esimes pros epilogh gia to epomeno vima*/
	int mikos,check,checking;
	int vimata;
	int r_num1,r_num2; /*r_num1=starting word & r_num2=target word*/
	char *s_word,*t_word;
	char *choosen_word; /*h leksh pou epilegei o paixths gia to epomeno vhma*/
	char formatstr[15];
	
	srand(time(NULL));
	
	check=epeksergasia_orismatwn(argc,&argv[0]);
	mikos=atoi(argv[1]);
	if(check==0) {
		return (0);
	}
	
	head1=init_list(FALSE);
	head2=init_list(FALSE);
	head3=init_list(TRUE);
	
	
	add_word_same_len(mikos,argv[3],head2);
	
	r_num1=rand() % head2->lunion.counter + 1;
	r_num2=rand() % head2->lunion.counter + 1;
	while(r_num1==r_num2) {
		r_num1=rand() % head2->lunion.counter + 1;
		r_num2=rand() % head2->lunion.counter + 1;
	}
	
	s_word= find_random_word(r_num1,head2);
	t_word= find_random_word(r_num2,head2);
	add_node(s_word,head1);
	vimata=atoi(argv[2]);
	printf("\tStarting word: %s\n",s_word);
	printf("\tTarget word: %s\n",t_word);
	printf("Try to go from %s to %s in no more than %d steps\n",s_word,t_word,vimata);
	while(1) {
		printf("Progress so far: ");
		print_list1(head1);
		printf("Remaining steps: %d\n",vimata); 
		printf("Target: %s\n",t_word);
		words_for_third_list(mikos,head2,s_word,head3);
		if(head3!=NULL) {
		printf("Choose one of the following words: \n");
		print_list3(head3);
		}
		else {
			printf("There are no words to choose from. Sorry!\n");
		}
		printf("Enter selection: ");
		choosen_word=(char *)malloc(WORDLEN*sizeof(char));
		if(choosen_word==NULL) {
			printf("Problem\n");
			exit(1);
		}
		sprintf(formatstr, "%%%ds", WORDLEN-1);
		scanf(" %s",choosen_word);
		checking=find_word(choosen_word,head3);
		if(checking==1) {
		printf("ERROR: Your selection is not available. Try again\n");
		}
		else {
			add_node_list1(choosen_word,head1);
			vimata--;
		}
		if(vimata==0) {
			break;
		}
	}
	
	
	
	
	printf("its ok :)\n");
	return (0);
}