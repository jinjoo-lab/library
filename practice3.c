#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Book_data
{
	char b_name[30]; // ������
	double b_price; // ���� ����
	int b_Qty; // ������
	struct Book_data* next;  // ����Ʈ�� �ڱ� ���� ����ü
}book; // ������ ������ �����ϴ� ����ü
typedef struct Author_data
{
	char f_name[30]; // �۰��� first name
	char l_name[30]; // �۰��� last name
	book* list; // ������ ������ ����Ʈ�� �����ϱ� ���� ������
}author;// �۰��� ������ �����ϴ� ����ü
void greeting(void); // ���� �λ縦 ���ϴ� �Լ�
void printMenu(char array[]); // �޴��� print�ϴ� �Լ� 
void readDatabase(author array[]); // ������ �����͸� �Է¹޾� array�� �����ϰ� ������ �̸����� �°� �����ϴ� �Լ�
void displayInventory(author array[]); // ��� ������ ���� ������ ����ϴ� �Լ�
void displayAuthorsWork(author array[]); // �Է��� ������ ���� ������ ����ϴ� �Լ�
void addBook(author array[]); // ������ �߰��ϴ� �Լ�
void changePrice(author array[]); // ������ �������ִ� ����� �Լ�
void changeQty(author array[]); // ����� �������ִ� ����� �Լ�
void totalQty(author array[]); // ����Ǿ��ִ� å�� �� �Ǽ��� �˷��ִ� �Լ�
void calculateTotalAmount(author array[]); // ����Ǿ��ִ� ���� ��ü ������ �˷��ִ� �Լ�
void makeName(char array[]); // �Է¹��� �̸��� ����� ���Ŀ� �˸°� ��ȯ�ϴ� �Լ�
int main(void)
{
	int flag=1; // ���� �ݺ����� ���� ����� ����
	char input[5]; // printMenu �Լ��� �Է� �迭
	int choice; // �Է� �迭�� ���� ���� ���·� ��ȯ 
	author theInventory[100]; // ����ü ������ �迭

	greeting();
	readDatabase(theInventory);
	
	while(flag)
	{
		printMenu(input); // prinMenu�� �Է¹迭�� ����ִ´�
		choice=atoi(input); // ��ȯ�� �迭�� �������·� ��ȯ�� choice�� ����

		if(choice==1)
			displayInventory(theInventory);
		else if(choice==2)
			displayAuthorsWork(theInventory);
		else if(choice==3)
			addBook(theInventory);
		else if(choice==4)
			changePrice(theInventory);
		else if(choice==5)
			changeQty(theInventory);
		else if(choice==6)
			totalQty(theInventory);
		else if(choice==7)
			calculateTotalAmount(theInventory);
		else if(choice==8)
		{
			printf("Thank you for using this program\n");
			flag=0;
		}
		else
			printf("Invalid choice\n\n");
	}
	return 0;
}
void greeting(void)
{
	printf("Welcome to the bookstore program!\n\n");
}
void readDatabase(author array[])
{
	char fileName[30]; // ������ ������ �̸��� ������ ���ڿ� ����
	int i=0,count=0,j=0; // �ݺ����� ����� ����
	int button=0; // ���ǹ��� ����� ����
	char c; // �ѱ��ھ� ���ڸ� �б� ���� �ʿ��� ����
	char string[100]; // ������ ���پ� �б� ���� ����� ���ڿ� ����
	char*s_token; // strtok�Լ��� �����ϱ� ���� �ʿ��� char�� ������ ����
	book* temp; // book ����Ʈ�� �����ϱ� ���� ����� ������ ����
	book* cur; // book ����Ʈ�� �����ϱ� ���� ����� ������ ����
	book* pre; // book ����Ʈ�� �����ϱ� ���� ����� ������ ����
	author temp1; // ������ ������ ������ ����
	FILE* stream; // ���Ͻ�Ʈ�� ����
	printf("input Filename:"); 
	scanf("%s",fileName); // ���ϸ��� �Է¹޴´�(example : database.txt)
	stream=fopen(fileName,"r"); // �Է¹��� ������ ������ ����
	if(stream==NULL)
	{
		printf("Error reading database\n");
		exit(-1) ;
	} // ���� ������ ���µ� �������� ��� ������ �޼��� ����� ���α׷� ����
	
	while(!feof(stream)) // ������ ���� �����Ҷ����� �ݺ��� ����
	{
	for(i=0;(c=fgetc(stream))!=EOF&&c!='\n';i++)
	{
		string[i]=c; // �ѱ��ھ� ������ ���� �о���δ�
	}string[i]='\0'; // ���ڿ��� ���������� ������ ���� ���� ����
	button=0; // button �ʱ�ȭ

	s_token=strtok(string,","); // �о���� ���ڿ��� strtok �Լ� ����Ͽ� , ���� ���ڿ��� ����
	strcpy(array[count].l_name,s_token); // count��°�� ������ l_name�� ���ڿ� ����
	
	s_token=strtok(NULL,","); // �о���� ���ڿ��� strtok �Լ� ����Ͽ� , ���� ���ڿ��� ����
	strcpy(array[count].f_name,s_token); // count��°�� ������ f_name�� ���ڿ� ����
	
	for(j=0;j<count&&button==0;j++) // ����ü(����) �迭�� 0��° idx���� count���� �ݺ��� ����
	{
		
		if(strcmp(array[j].f_name,array[count].f_name)==0&&strcmp(array[j].l_name,array[count].l_name)==0) // ���� �о���� ������ �̸��� ���� �迭�� ������ ���
		{
		
			temp=(book*)malloc(sizeof(book)); // temp�� ���� �޸� �Ҵ�
			temp->next=NULL; // temp�� next�� NULL�� �ʱ�ȭ
		
			s_token=strtok(NULL,","); // �о���� ���ڿ��� strtok �Լ� ����Ͽ� , ���� ���ڿ��� ����
			strcpy(temp->b_name,s_token); // temp�� ������ �κп� ���ڿ� ����
			
			s_token=strtok(NULL,","); // �о���� ���ڿ��� strtok �Լ� ����Ͽ� , ���� ���ڿ��� ����
			temp->b_Qty=atoi(s_token); // temp�� ��� �κп� ���ڿ��� �������·� ��ȯ �� ����
	
			s_token=strtok(NULL,","); // �о���� ���ڿ��� strtok �Լ� ����Ͽ� , ���� ���ڿ��� ����
			temp->b_price=atof(s_token); // temp�� ���� �κп� ���ڿ��� �Ǽ����·� ��ȯ �� ����

			if(array[j].list->next==NULL) //������ ����Ʈ�� å�� ���� �ѱǸ� ����Ǿ��ִ� ���
			{
				array[j].list->next=temp; // �ٷ� ���� ��ġ�� temp ����
			}
			else // �׷��� ���� ���
			{
				cur=array[j].list; //cur�� ����Ʈ�� ���� ��ġ ����
				while(cur) // cur�� NULL���� �ƴҶ����� �ݺ��� ����
				{
					pre=cur; // pre�� cur�� ����
					cur=cur->next; // cur�� ��ġ ��ȯ
				}
				pre->next=temp;	 // pre�� ���� �κп� temp ����
			}
			button=1; // button �� �� 1����
		}
	}
	if(button!=1) // button�� ���� 1�ΰ��(���� �迭�� ���ڸ��� �������� �ʴ� ���)
	{
		array[count].list=(book*)malloc(sizeof(book));// count ������ ���ڹ迭�� list�� �����޸� �Ҵ�
	
		s_token=strtok(NULL,","); // �о���� ���ڿ��� strtok �Լ� ����Ͽ� , ���� ���ڿ��� ����
		strcpy(array[count].list->b_name,s_token); // ������ ����

		s_token=strtok(NULL,","); // �о���� ���ڿ��� strtok �Լ� ����Ͽ� , ���� ���ڿ��� ����
		array[count].list->b_Qty=atoi(s_token); // ����� �������·� ��ȯ �� ����
	
		s_token=strtok(NULL,","); // �о���� ���ڿ��� strtok �Լ� ����Ͽ� , ���� ���ڿ��� ����
		array[count].list->b_price=atof(s_token); // ������ �Ǽ����·� ��ȯ �� ����
	
		array[count].list->next=NULL; // list�� next�� NULL������ �ʱ�ȭ(�����Ҷ� ���)
		count++; // count �� ����
	}
	}
	for(i=0;i<count-1;i++) // ��ü ������ �� -1 ��ŭ �ݺ��� ����
	{
		for(j=0;j<count-i-1;j++) // 0��° �������� (������-1)������ ���ڸ� Ž���Ҷ����� �ݺ��� ����
		{
			if(strcmp(array[j].l_name,array[j+1].l_name)>0) // j�� j+1������ ���ڸ��� ���� ������������ �����ϱ� ���� ���ǹ� ���� 
			{
				temp1=array[j];
				array[j]=array[j+1];
				array[j+1]=temp1; // ������ swap(��ġ�� �ٲ۴�)
			}
		}
	}
	array[count].list=NULL; // ������ ������ ������ ��� �迭�� ���� ������ list�� NULL�� �ʱ�ȭ(�����Ҷ� ���)
	fclose(stream); // ������ �ݴ´�
}
void printMenu(char array[])
{
	int i=0;// �ݺ����� ����� ����
	printf("--------------------------------\n");
	printf("Enter 1 to display the inventory\n");
	printf("Enter 2 to display the books by one author\n");
	printf("Enter 3 to add a book\n");
	printf("Enter 4 to change the price\n");
	printf("Enter 5 to change the qty on hand\n");
	printf("Enter 6 to view the total number of books in the inventory\n");
	printf("Enter 7 to see the total amount of the entire inventory\n");
	printf("Enter 8 to exit\n");
	rewind(stdin);
	printf("Enter your choice:");
	scanf("%s",array); // �迭�� ���ڿ��� �Է¹޴´�
	while(array[i]!='\0') // ���ڿ��� ���� �����Ҷ����� �ݺ��� ����
	{
		if(!isdigit(array[i])) // ������ ������ ���ڰ� �Էµ��� ���� ���
			strcpy(array,"9"); // 9�� �迭�� �ٲ۴�
		i++;
	}
}
void displayInventory(author array[])
{
	int i=0; // �ݺ����� ����� ����
	book* j; // ���� ������ �����ϱ� ���� ����� ������ ����
	book* k; // ���� ������ �����ϱ� ���� ����� ������ ����
	book* temp2; // ���� ������ �����ϱ� ���� ����� ������ ����
	while(array[i].list!=NULL) // ��� ������ ������ Ž���Ҷ����� �ݺ��� ����
	{
		for(j=array[i].list;j;j=j->next) // j�� i��° ������ ����Ʈ ������ ����Ʈ ���� �����Ҷ����� �ݺ��� ����
		{
			for(k=j->next;k;k=k->next) // k�� j��° ������ ������ ����Ʈ ������ ����Ʈ ���� �����Ҷ����� �ݺ��� ����
			{
				if(strcmp(j->b_name,k->b_name)>0)  // ���� j�� k�� �������� ���� ���ĺ��� �������� ���ǿ� ���߱� ����
				{
					temp2=(book*)malloc(sizeof(book));
					strcpy(temp2->b_name,j->b_name);
					temp2->b_price=j->b_price;
					temp2->b_Qty=j->b_Qty; // temp�� j�� �������� ����

					strcpy(j->b_name,k->b_name);
					j->b_price=k->b_price;
					j->b_Qty=k->b_Qty; // j�� k�� �������� ����

					strcpy(k->b_name,temp2->b_name);
					k->b_price=temp2->b_price;
					k->b_Qty=temp2->b_Qty; // k�� temp�� ���� ���� ����
				}// �������� swap ����
			}
		}
		i++;
	}
	i=0; // i=0 �ʱ�ȭ
	while(array[i].list!=NULL) // ��� ������ ������ Ž���Ҷ����� �ݺ��� ����
	{
		printf("The author is: %s, %s\n",array[i].l_name,array[i].f_name); // ���� ���� ���
		temp2=array[i].list; // ������ ���������� temp2�� ����

		while(temp2) // ������ ��� ���������� Ž���ϱ� ���� �ݺ��� ����
		{
			printf("\n\tThe title is: %s\n\t",temp2->b_name); // ������ ���
			printf("The qty is: %d\n\t",temp2->b_Qty); // ��� ���
			printf("The price is: %.2lf\n\n\t",temp2->b_price); // ���� ���
			printf("----\n\n");
			temp2=temp2->next; // temp2�� ��ġ ����
		}
		i++;
	}

}
void displayAuthorsWork(author array[])
{
	int i=0; // �ݺ����� ����� ����
	char c; // �ѱ��ھ� ���ڸ� �Է¹����� ����� ����
	char first[30]; // ������ first name
	char last[30]; // ������ last name
	book* j; // ���� ������ �����ϱ� ���� ����� ������ ����
	book* k; // ���� ������ �����ϱ� ���� ����� ������ ����
	book* temp2; // ���� ������ �����ϱ� ���� ����� ������ ����
	// ���� ����� ������ ������ �����Ѵ�
	while(array[i].list!=NULL) // ��� ������ ������ �����Ҷ����� �ݺ��� ����
	{
		for(j=array[i].list;j;j=j->next) // j�� i��° ������ ����Ʈ ������ ����Ʈ ���� �����Ҷ����� �ݺ��� ����
		{
			for(k=j->next;k;k=k->next) // k�� j��° ������ ������ ����Ʈ ������ ����Ʈ ���� �����Ҷ����� �ݺ��� ����
			{
				if(strcmp(j->b_name,k->b_name)>0) // ���� j�� k�� �������� ���� �������� ���ǿ� ���߱� ����
				{
					temp2=(book*)malloc(sizeof(book));
					strcpy(temp2->b_name,j->b_name);
					temp2->b_price=j->b_price;
					temp2->b_Qty=j->b_Qty; // temp�� j�� �������� ����

					strcpy(j->b_name,k->b_name);
					j->b_price=k->b_price;
					j->b_Qty=k->b_Qty; // j�� k�� �������� ����

					strcpy(k->b_name,temp2->b_name);
					k->b_price=temp2->b_price;
					k->b_Qty=temp2->b_Qty; // k�� temp�� ���� ���� ����
				} // �������� swap ����
			}
		}
		i++;
	}
	i=0; // i�� �ʱ�ȭ
	rewind(stdin);
	printf("Enter the author's first name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// first�� �۰��� �̸��� �ѱ��ھ� �Է¹޴´�
	{
		first[i]=c;
	}first[i]='\0'; // ���ڿ� ���� ���Ṯ�� ����
	rewind(stdin);
	printf("Enter the author's last name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// last�� �۰��� �̸��� �ѱ��ھ� �Է¹޴´�
	{
		last[i]=c;
	}
	last[i]='\0'; // ���ڿ� ���� ���Ṯ�� ����
	makeName(first); // ����ϴ� ���Ŀ� �˸°� ���ڿ� ��ȯ
	makeName(last); // ����ϴ� ���Ŀ� �˸°� ���ڿ� ��ȯ
	
	i=0; // i=0 �ʱ�ȭ
	while(array[i].list!=NULL) // ��� ������ ������ �����Ҷ����� �ݺ��� ����
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0) // ���� �Է¹��� ���ڸ�� ��ġ�ϴ� ���ڸ��� ã�� ���
		{
			temp2=array[i].list; // temp2�� ������ ���� ������ ��� ����Ʈ�� ������ġ�� ����
			while(temp2) // ��� ���� ������ �����Ҷ����� �ݺ��� ����
			{
				printf("\n\tThe title is: %s\n\t",temp2->b_name); // ������ ���
				printf("The qty is: %d\n\t",temp2->b_Qty); // ��� ���
				printf("The price is: %.2lf\n\n\t",temp2->b_price); // ���� ��� 
				printf("----\n\n");
				temp2=temp2->next; // temp2�� ��ġ ����
			}
			return; // �Լ� ���� 
		}
		i++;
	}
	printf("The author you requested does not exist.\n\n"); // ��� ������ ������ Ž���Ͽ����� ���ϴ� ���ڰ� ���� ��� �޼��� ���
	return ;
}
void addBook(author array[])
{
	char first[30]; // ������ first name
	char last[30]; // ������ last name
	char title[30]; // ������
	char qty[10]; // ���
	char price[10]; // ����
	int i,j,k,r_qty=0,button; // ���� i,j,k�� �ݺ����� ���, button�� ���� �Է����¸� �Ǵ��ϴµ� ���, r_qty�� ���� ���·� ������ ��� ���� ����
	double r_price=0; // r_price���� �Ǽ����·� ������ ������ ����
	char c; // ���ڿ��� �ѱ��ھ� �Է¹޴´�
	book* cur; // ���� ������ ��� ����Ʈ�� �����Ҷ� ���
	book* pre; // ���� ������ ��� ����Ʈ�� �����Ҷ� ���
	author temp1; // ������ ������ ������ ����
	book* temp2=(book*)malloc(sizeof(book)); // ������ ������ ���� ������ ���� ������ ���� �޸� �Ҵ�

	rewind(stdin);
	printf("Enter the author's first name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// first�� �۰��� �̸��� �ѱ��ھ� �Է¹޴´�
	{
		first[i]=c;
	}first[i]='\0'; // ���ڿ� ���� ���Ṯ�� ����
	makeName(first); // ����� ���Ŀ� �˸°� ���ڿ� ��ȯ
	rewind(stdin);
	printf("Enter the author's last name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// last�� �۰��� �̸��� �ѱ��ھ� �Է¹޴´�
	{
		last[i]=c;
	}last[i]='\0'; // ���ڿ� ���� ���Ṯ�� ����
	rewind(stdin);
	printf("Enter the title:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// title�� ������ ������ �ѱ��ھ� �Է¹޴´�
	{
		title[i]=c;
	}title[i]='\0'; // ���ڿ� ���� ���Ṯ�� ����
	rewind(stdin);
	makeName(first); // ����� ���Ŀ� �°� ���ڿ� ��ȯ
	makeName(last); // ����� ���Ŀ� �°� ���ڿ� ��ȯ
	makeName(title); // ����� ���Ŀ� �°� ���ڿ� ��ȯ
	
	i=0; // i=0 �ʱ�ȭ
	while(array[i].list!=NULL) // ����� ��� ������ ������ �����Ҷ����� �ݺ��� ����
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0) // �Է��� ���ڸ�� ��ġ�ϴ� ���ڸ��� �迭���� ã�� ��� 
		{
			cur=array[i].list; // cur�� ���� ������ ������ ����
			while(cur) // ������ ��� ���� ������ �����Ҷ����� �ݺ��� ����
			{
				if(strcmp(cur->b_name,title)==0) // ���� �Է��� ������� ��ġ�ϴ� ������ ã�� ���
				{
					printf("This book is already in the Inventory and cannot be added again\n");
					return;
				} // ������ �޼��� ����� �Լ� ����
				cur=cur->next; // cur�� ��ġ ��ȯ
			}
		}
		i++;
	}
	i=0; // i=0 �ʱ�ȭ
	while(r_qty==0) // r_qty�� ���� ����ɶ����� �ݺ��� ����
	{
		i=0;
		printf("Enter the qty:");
		scanf("%s",qty); // ����� ���ڿ� ���·� �Է¹޴´�
		rewind(stdin);
		
		while(qty[i]!='\0') // ���ڿ��� ���� �����Ҷ����� �ݺ��� ����
		{
			if(!isdigit(qty[i])) // ������ ������ ���ڰ� �Էµ��� ���� ���
			{
				printf("Invalid input for qty\n");
				break;
			} // ������ �޼��� ����� �ݺ��� ����
			i++;

			if(qty[i]=='\0') // ������ ������ ���ڸ� �Է¹��� �� ���ڿ��� ���� ������ ���
			{
				r_qty=atoi(qty);
			} // r_qty�� �������·� ��ȯ�� ����
		}
	}
	while(r_price==0) // r_price�� ���� ����ɶ����� �ݺ��� ����
	{
		i=0,button=0; // i�� button 0���� �ʱ�ȭ
		printf("Enter the price:");
		scanf("%s",price); // ������ ���ڿ� ���·� �Է¹޴´�
		rewind(stdin);
		while(price[i]!='\0') // ���ڿ��� ���� �����Ҷ����� �ݺ��� ����
		{
			if(!isdigit(price[0]))
			{
				break;
			}// ù��° ���ڰ� ������ ���°� �ƴ� ��� �ݺ��� ����
			if(!isdigit(price[i])&&price[i]!='.')
			{
				break;
			}// �Է¹��� ���ڰ� .�� �ƴ� �ٸ� ������ ��� �ݺ��� ����
			if(price[i]=='.')
			{
				break;
			} // �Է¹��� ���ڰ� .�� ��� �ݺ��� ����
			i++;
		}
		if(price[i]=='.') // �Է¹��� ���ڰ� .�� ���
		{
			button=i; // .�� ��ġ�� button�� ����
			i++; // i �� ����
			// ���α׷����� ����ϴ� �Ǽ��� ���´� �Ҽ��� �Ʒ� ���ڸ��� ������ �����ؾ� ������.
			//example ) 5.364�� �߸��� �Է�, 5.35�� ���� ���� �� �Է��� �ùٸ���
			if(price[button+1]=='\0') // .�� �������� �� ���� ���ڰ� ���Ṯ���� ���
				button=100; // button �� 100���� ����
			if(price[button+2]=='\0') // .�� �������� �� ���� ���� ���ڰ� ���Ṯ���� ���
				button=100; // button �� 100���� ����
			if(price[button+3]!='\0') // .�� �������� �� ���� ���� ���� ���ڰ� ���Ṯ�ڰ� �ƴ� ���
				button=100; // button �� 100���� ����
			while(price[i]!='\0') // i��° ���ڰ� ���Ṯ���϶����� �ݺ��� ����
			{
				if(!isdigit(price[i])) // �������� �ƴ� ������ ���ڰ� �Էµ� ���
				{
					button=100;
					break;
				} // button �� 100���� ������ �ݺ��� ����
				i++;
			}
			if(button!=100)	// ���� ������ ��� �������� ���� �ùٸ� ������ ������ �Էµ� ���
			   r_price=atof(price); // r_price�� �Ǽ� ���·� ��ȯ �� ����
		}
		if(r_price==0) // ���� r_price�� ���� ������� ���� ���
			printf("invalid input for price\n"); // �޼��� ���
	}
	strcpy(temp2->b_name,title); // temp2�� ������ �κп� ���� �� ����
	temp2->b_price=r_price; // temp2�� ���� �κп� r_price ����
	temp2->b_Qty=r_qty; // temp2�� ��� �κп� r_qty ����
	temp2->next=NULL; // temp2�� next�� NULL������ �ʱ�ȭ
	
	i=0; // i=0 �ʱ�ȭ
	while(array[i].list!=NULL) // ��� ������ ������ �����Ҷ����� �ݺ��� ����
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0) // ���ϴ� ���ڸ� ã�� ���
		{
			cur=array[i].list; // cur�� ��ġ�� �������� ����
			pre=array[i].list; // pre�� ��ġ�� �������� ����
			while(cur) // cur�� NULL�� �ƴҶ����� �ݺ��� ����
			{
				pre=cur; // pre�� cur�� ����
				cur=cur->next; // cur�� ��ġ ��ȯ
			}
			pre->next=temp2; // ������ ������ ��ġ �� ������ temp2 ����
			return; // �Լ� ����
		}
		i++;
	} 
	// ���� �߰��Ǵ� ������ ������ ���
	strcpy(array[i].f_name,first); // �� ���� ����(i)�� ������ first name ����
	strcpy(array[i].l_name,last); // �� ���� ����(i)�� ������ last name ����
	array[i].list=temp2; // ���ο� ������ ù ����(temp)�� ����Ʈ�� ����
	array[i+1].list=NULL; // �� ���� ������ ���� ��ġ�� list�� NULL�� �ʱ�ȭ(������ ��ġ�� ã�� ���� ����)

	// ���ο� ������ ������ �߰��Ǿ����Ƿ� ���������� ����� ����ü �迭�� ������ �ʿ䰡 �ִ�
	for(j=0;j<i;j++)
	{
		for(k=0;k<i-j;k++) // ������ �������� ���
		{
			if(strcmp(array[k].l_name,array[k+1].l_name)>0) // k������ ���ڸ�� k+1������ ���ڸ��� ���Ͽ� ���ĺ� ������ ���������� �ǵ���
			{
				temp1=array[k];
				array[k]=array[k+1];
				array[k+1]=temp1; // ��ġ�� �ٲ۴�
			}
		}
	}
}
void changePrice(author array[])
{
	char first[30]; // �۰��� frist name
	char last[30]; // �۰��� last name
	char title[30]; // ������
	char price[10]; // ������ ������ ���ڿ�
	int i,idx; // i�� �ݺ����� ����� ����, idx�� ��ġ�� ã����� i���� ������ ����
	double r_price; // ���� �Ǽ��� ��ȯ�� ������ ������ ����
	double del_price=0; // ���� ���� ������ ������ �Ǽ��� ����
	int button; // �ݺ��� Ż�� ���ǿ� ����� ����
	char c; // ���ڿ��� �ѱ��ھ� �Է� ������ ����� ����
	book* cur; // book ����Ʈ�� ������ ������ ����
	rewind(stdin);
	printf("Enter the author's first name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// first�� �۰��� �̸��� �ѱ��ھ� �Է¹޴´�
	{
		first[i]=c;
	}first[i]='\0'; // ���ڿ� ���� ���Ṯ�� ����
	makeName(first); // ����� ���Ŀ� �˸°� ���ڿ� ��ȯ
	rewind(stdin);
	printf("Enter the author's last name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// last�� �۰��� �̸��� �ѱ��ھ� �Է¹޴´�
	{
		last[i]=c;
	}
	last[i]='\0'; // ���ڿ� ���� ���Ṯ�� ����
	makeName(last); // ����� ���Ŀ� �˸°� ���ڿ� ��ȯ
	rewind(stdin);
	i=0;
	while(array[i].list!=NULL) // ����� ��� ���ڸ� �����Ҷ����� �ݺ��� ����
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0)
		{
			idx=i;
			break;
		}// �Է¹��� ������ �̸��� ���� �̸��� �迭���� ã���� ��� idx�� ���� ������ �ݺ��� ����
		i++;
	}
	if(array[i].list==NULL)// ��� ���ڸ� �����Ͽ����� �Է¹��� �̸��� ã�� ���� ���
	{
		printf("No such author in your database. So you cannot change the price\n");
		return ;
	} // ������ �޼��� ��� �� �Լ� ����
	printf("Enter the title:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)
	{
		title[i]=c;
	} // ������ ������ �ѱ��ھ� �Է¹޴´�
	title[i]='\0'; // ������ ���� ������ ���Ṯ�� ����
	rewind(stdin);
	makeName(title); // ����� ���Ŀ� �˸°� ������ ��ȯ
	
	cur=array[idx].list; // ã�� ������ ����Ʈ�� cur�� ����
	
	while(cur) // ��� ������ ������ �����Ҷ����� �ݺ��� ����
	{
		if(strcmp(cur->b_name,title)==0) // ���� title�� ���� å������ ã�� ���
			break; // �ݺ��� ����
		cur=cur->next; // cur�� ��ġ ��ȯ
	}
	if(cur==NULL) // ���� ��� ������ ������ �����Ͽ����� title�� ���� �̸��� å ������ ã�� ���� ���
	{
		printf("No book with the title %s by %s, %s\n",title,last,first);
		return;
	} // ������ �޼��� ����� �Լ� ����
	r_price=0; // �Ǽ� ������ ������ ������ ���� 0���� �ʱ�ȭ

	while(r_price==0) // ����ε� ������ ������ �Էµɶ����� �ݺ��� ����
	{
		i=0,button=0; // �ݺ����� ����� i, ���ǿ� ����� button �ʱ�ȭ 
		printf("Enter the price:");
		scanf("%s",price); // ������ �Է¹޾� ���ڿ��� ����
		rewind(stdin);
		while(price[i]!='\0') // ���ڿ��� ���� �����Ҷ����� �ݺ��� ����
		{
			if(!isdigit(price[0])) // ���� ù��° ���ڰ� ������ ������ ���ڰ� �Էµ��� ���� ���
			{
				break;
			} // �ݺ��� ����
			if(!isdigit(price[i])&&price[i]!='.')
			{
				break;
			}// ���� .�� �ƴ� ���ڰ� �Էµ� ��� �ݺ��� ����
			if(price[i]=='.')
			{
				break;
			}// ���� .�� �Էµ� ��� �ݺ��� ����
			i++;
		}
		if(price[i]=='.') // i��° ���ڰ� .�ΰ��
		{
			button=i; // button�� i�� ����
			i++; // i�� �� ����
			// ���α׷����� ����ϴ� �Ǽ��� ���´� �Ҽ��� ���ڸ��� ������ �����ؾ� ������.
			//example ) 5.364�� �߸��� �Է�, 5.35�� ���� ���� �� �Է��� �ùٸ���
			if(price[button+1]=='\0') // ���� .�� ��������  �� ���� ���ڰ� ���Ṯ�ڶ��
				button=100; // button�� �� ����
			if(price[button+2]=='\0') // .�� �������� �� ���� ���� ���ڰ� ���� ���ڶ��
				button=100; // button�� �� ����
			if(price[button+3]!='\0') // .�� �������� �� ���� ���� ���� ���ڰ� ���� ���ڰ� �ƴ϶��
				button=100; // button�� �� ����
			while(price[i]!='\0') // i������ ���ڿ��� ���Ṯ�ڸ� ���������� �ݺ��� ����
			{
				if(!isdigit(price[i]))
				{
					button=100;
					break;
				}// ���� ������ ������ ���ڰ� �Էµ��� ���� ��� button�� ������ �ݺ��� ����
				i++;
			}
			if(button!=100)	// ���� ���� ������ ��� �������� ����(5.35�� ���� ������ ���ڿ� �Է��� ���)
			   r_price=atof(price); // r_price�� �Ǽ����·� ��ȯ �� ����
		}
		if(r_price==0) // �ùٸ� ������ �Ǽ� �Է��� �̷������ ���� ���
			printf("invalid input for price\n"); // �޼��� ���
	}
	
	del_price=cur->b_price; // ���� ���� ������ del_price�� ����
	cur->b_price=r_price; // ���� ���� ������ cur�� ����Ű�� ��ġ�� ���ݿ� ����
	printf("Price will be updated from %.2lf to %.2lf\n",del_price,cur->b_price);

	return ;
}
void changeQty(author array[])
{
	char first[30]; // ���ϴ� ���� ������ first name
	char last[30]; // ���ϴ� ���� ������ last name
	char title[30]; // ������ ���ϴ� ������
	char qty[10]; // ����� ����
	int i,idx,r_qty,del_qty=0; // i�� �ݺ����� ���, idx�� ���ϴ� ������ ã������ ���� ����, r_qty,del_qty�� ���������� ��� ���庯��
	char c; // �ѱ��ھ� �Է��� �޴´�
	book* cur; // book�� ������ ����� ������ ����

	rewind(stdin);
	printf("Enter the author's first name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// first�� �۰��� �̸��� �ѱ��ھ� �Է¹޴´�
	{
		first[i]=c;
	}first[i]='\0'; // ������ ���� ������ ���Ṯ�� ����
	makeName(first); // �۰��� �̸��� ���α׷� ������ ����ϴ� ���Ŀ� �°� ��ȯ
	rewind(stdin);
	printf("Enter the author's last name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// last�� �۰��� �̸��� �ѱ��ھ� �Է¹޴´�
	{
		last[i]=c;
	}
	last[i]='\0'; // ������ ���� ������ ���Ṯ�� ����
	makeName(last); // �۰��� �̸��� ���α׷� ������ ����ϴ� ���Ŀ� �°� ��ȯ
	rewind(stdin);
	i=0;
	while(array[i].list!=NULL) // ����� ��� ���ڸ� �����Ҷ����� �ݺ��� ����
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0)
		{
			idx=i;
			break;
		} // ���ϴ� �۰��� �̸��� ã������� �ݺ��� ������ �� ������ ���� idx�� ����
		i++;
	}
	if(array[i].list==NULL)// ��� ���ڸ� �����Ͽ����� �Է¹��� ���ڸ� ã�� ���� ��� 
	{
		printf("No such author in your database. So you cannot change the qty\n");
		return ;
	} // ������ �޼��� ����� �Լ� ����
	printf("Enter the title:"); 
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)
	{
		title[i]=c;
	}// titlr�� ������ ������ �ѱ��ھ� �Է¹޴´�
	title[i]='\0'; // title�� ������ ���� ������ ���Ṯ�� ����
	rewind(stdin);
	makeName(title); // ���Ŀ� �°� ����
	cur=array[idx].list; // ������ġ�� ã�� ������ .list�� ����
	while(cur)// ������ ��� ������ �����ϴ� ����
	{
		if(strcmp(cur->b_name,title)==0) // ���� �Է��� å����� �������� ���� ���
			break; // �ݺ��� Ż��
		cur=cur->next; // cur�� ��ġ ����
	}
	if(cur==NULL) // ������ ��� ������ �����Ͽ����� �Է��� å�� ������ ã�� ���� ���
	{
		printf("No book with the title %s by %s, %s\n",title,last,first);
		return;
	} // ������ �޼��� ����� �Լ� ����
	r_qty=0; // ���� å�� ������ ������ ���� 0���� �ʱ�ȭ
	while(r_qty==0) // r_qty�� ���� ������ �ʴ� ���� �ݺ��� ����
	{
		i=0; // �ݺ����� ���
		printf("Enter the qty:");
		scanf("%s",qty); // ������ �Է¹޾� qty�� ����
		rewind(stdin);
		
		while(qty[i]!='\0') // �Է¹��� ���ڿ� ������ qty�� ���Ṯ�ڰ� �ƴҶ����� �� ���ھ� �ľ�
		{
			if(!isdigit(qty[i])) // ���� i��° ���ڰ� ������������ ���ڰ� �ƴ϶��
			{
				printf("Invalid input for qty\n");
				break;
			} // ������ �޼��� ����� �ݺ��� Ż��
			i++;

			if(qty[i]=='\0')
			{
				r_qty=atoi(qty);
			} // ������ ������ ���ڸ� �Է¹޾� ���ڿ��� ���� ������ ��� ���ڿ� qty�� �������·� ���� �� r_qty�� ����
		}
	}
	del_qty=cur->b_Qty; // �������� ����� del_qty�� ����
	cur->b_Qty=r_qty; // �������� ���(r_qty)�� ���� cur�� ����Ű�� list�� ����� ����
	printf("Qty will be updated form %d to %d\n",del_qty,cur->b_Qty);
	return ;
}
void totalQty(author array[])
{
	int i=0; // �ݺ����� ����� ����
	int total=0; // ����ؼ� ���� ������ ����
	book* cur; // ���� ������ ��� ����Ʈ�� �����ϱ� ���� ����� ������ ����
	while(array[i].list!=NULL)// ��� ������ ������ �����ϱ� ������ �ݺ��� ����
	{
		cur=array[i].list; // ���� ������ ������ ���� ������ ��� ����Ʈ�� cur�� ����
		while(cur)// ��� ������ ������ �����Ҷ����� �ݺ��� ����
		{
			total=total+cur->b_Qty;// total�� ������ ������ ����ؼ� ����
			cur=cur->next;// ���� ������ ������ ����
		}
		i++;
	}
	printf("The total number of books is %d\n",total);
	return ;
}
void calculateTotalAmount(author array[])
{
	int i=0; // �ݺ����� ����� ����
	double total=0; // �� ������ ������ ����
	int s_book=0; // ������ ������ �˷��ִ� ����
	book* cur; // ���� ������ ��� ����Ʈ�� �����ϱ� ���� ����� ������ ����
	while(array[i].list!=NULL)// ��� ������ ������ �����ϱ� ������ �ݺ��� ����
	{
		cur=array[i].list; // ���� ������ ������ ���� ������ ��� ����Ʈ�� cur�� ����
		while(cur)// ��� ������ ������ �����Ҷ����� �ݺ��� ����
		{
			s_book=cur->b_Qty;//s_book�� ���� ������ ���� ����
			total=total+(cur->b_price*s_book); // total�� ���� ������ ����*1���� ������ ����
			cur=cur->next;// ���� ������ ���� ����
		}
		i++;
	}
	printf("The total number of books is $%.2lf\n",total);
	return ;
}
void makeName(char array[])
{
	int i=0; // �ݺ����� ����� ����
	if(islower(array[0])){
		array[0]=toupper(array[0]);
	} // ���� �Է¹��� �迭�� ù��° idx�� ���� �ҹ��ڶ�� �빮�ڷ� ��ȯ
	i++; // 1��° �ε������� �ݺ����� ����
	while(array[i]!='\0')// �迭�� ���� �ƴҶ����� �ݺ��� ����
		{
			if(array[i-1]==' ') // ���� ���� idx�� ����(����)��� �빮�ڷ� ��ȯ
				array[i]=toupper(array[i]);
			else// �׷��� ������ �ҹ��ڷ� ��ȯ
				array[i]=tolower(array[i]);
			i++;
		}
}


