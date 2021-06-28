#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
typedef struct Book_data
{
	char b_name[30]; // 서적명
	double b_price; // 서적 가격
	int b_Qty; // 서적량
	struct Book_data* next;  // 리스트의 자기 참조 구조체
}book; // 도서의 정보를 저장하는 구조체
typedef struct Author_data
{
	char f_name[30]; // 작가의 first name
	char l_name[30]; // 작가의 last name
	book* list; // 도서의 정보를 리스트로 저장하기 위한 포인터
}author;// 작가의 정보를 저장하는 구조체
void greeting(void); // 감사 인사를 전하는 함수
void printMenu(char array[]); // 메뉴를 print하는 함수 
void readDatabase(author array[]); // 파일의 데이터를 입력받아 array에 저장하고 저자의 이름순에 맞게 정렬하는 함수
void displayInventory(author array[]); // 모든 저자의 도서 정보를 출력하는 함수
void displayAuthorsWork(author array[]); // 입력한 저자의 도서 정보를 출력하는 함수
void addBook(author array[]); // 도서를 추가하는 함수
void changePrice(author array[]); // 가격을 변경해주는 기능의 함수
void changeQty(author array[]); // 재고량을 변경해주는 기능의 함수
void totalQty(author array[]); // 저장되어있는 책의 총 권수를 알려주는 함수
void calculateTotalAmount(author array[]); // 저장되어있는 총의 전체 가격을 알려주는 함수
void makeName(char array[]); // 입력받은 이름을 사용할 형식에 알맞게 전환하는 함수
int main(void)
{
	int flag=1; // 무한 반복문을 위해 사용할 변수
	char input[5]; // printMenu 함수의 입력 배열
	int choice; // 입력 배열의 값을 정수 형태로 변환 
	author theInventory[100]; // 구조체 일차원 배열

	greeting();
	readDatabase(theInventory);
	
	while(flag)
	{
		printMenu(input); // prinMenu에 입력배열을 집어넣는다
		choice=atoi(input); // 변환된 배열을 정수형태로 변환후 choice에 저장

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
	char fileName[30]; // 실행할 파일의 이름을 저장할 문자열 변수
	int i=0,count=0,j=0; // 반복문에 사용할 변수
	int button=0; // 조건문에 사용할 변수
	char c; // 한글자씩 문자를 읽기 위해 필요한 변수
	char string[100]; // 파일을 한줄씩 읽기 위해 사용할 문자열 변수
	char*s_token; // strtok함수를 실행하기 위해 필요한 char형 포인터 변수
	book* temp; // book 리스트를 참조하기 위해 사용할 포인터 변수
	book* cur; // book 리스트를 참조하기 위해 사용할 포인터 변수
	book* pre; // book 리스트를 참조하기 위해 사용할 포인터 변수
	author temp1; // 저자의 정보를 저장할 변수
	FILE* stream; // 파일스트림 생성
	printf("input Filename:"); 
	scanf("%s",fileName); // 파일명을 입력받는다(example : database.txt)
	stream=fopen(fileName,"r"); // 입력받은 제목의 파일을 연다
	if(stream==NULL)
	{
		printf("Error reading database\n");
		exit(-1) ;
	} // 만약 파일을 여는데 실패했을 경우 적절한 메세지 출력후 프로그램 종료
	
	while(!feof(stream)) // 파일의 끝에 도달할때까지 반복문 실행
	{
	for(i=0;(c=fgetc(stream))!=EOF&&c!='\n';i++)
	{
		string[i]=c; // 한글자씩 파일의 줄을 읽어들인다
	}string[i]='\0'; // 문자열의 마지막문자 다음에 종료 문자 삽입
	button=0; // button 초기화

	s_token=strtok(string,","); // 읽어들인 문자열에 strtok 함수 사용하여 , 전의 문자열을 저장
	strcpy(array[count].l_name,s_token); // count번째의 저자의 l_name에 문자열 복사
	
	s_token=strtok(NULL,","); // 읽어들인 문자열에 strtok 함수 사용하여 , 전의 문자열을 저장
	strcpy(array[count].f_name,s_token); // count번째의 저자의 f_name에 문자열 복사
	
	for(j=0;j<count&&button==0;j++) // 구조체(저자) 배열의 0번째 idx부터 count까지 반복문 실행
	{
		
		if(strcmp(array[j].f_name,array[count].f_name)==0&&strcmp(array[j].l_name,array[count].l_name)==0) // 만약 읽어들인 저자의 이름이 기존 배열에 존재할 경우
		{
		
			temp=(book*)malloc(sizeof(book)); // temp에 동적 메모리 할당
			temp->next=NULL; // temp의 next를 NULL값 초기화
		
			s_token=strtok(NULL,","); // 읽어들인 문자열에 strtok 함수 사용하여 , 전의 문자열을 저장
			strcpy(temp->b_name,s_token); // temp의 도서명 부분에 문자열 저장
			
			s_token=strtok(NULL,","); // 읽어들인 문자열에 strtok 함수 사용하여 , 전의 문자열을 저장
			temp->b_Qty=atoi(s_token); // temp의 재고량 부분에 문자열을 정수형태로 변환 후 저장
	
			s_token=strtok(NULL,","); // 읽어들인 문자열에 strtok 함수 사용하여 , 전의 문자열을 저장
			temp->b_price=atof(s_token); // temp의 가격 부분에 문자열을 실수형태로 변환 후 저장

			if(array[j].list->next==NULL) //저자의 리스트에 책이 기존 한권만 저장되어있던 경우
			{
				array[j].list->next=temp; // 바로 다음 위치에 temp 저장
			}
			else // 그러지 않은 경우
			{
				cur=array[j].list; //cur에 리스트의 시작 위치 저장
				while(cur) // cur이 NULL값이 아닐때까지 반복문 실행
				{
					pre=cur; // pre에 cur값 저장
					cur=cur->next; // cur의 위치 변환
				}
				pre->next=temp;	 // pre의 다음 부분에 temp 저장
			}
			button=1; // button 의 값 1설정
		}
	}
	if(button!=1) // button의 값이 1인경우(기존 배열에 저자명이 존재하지 않는 경우)
	{
		array[count].list=(book*)malloc(sizeof(book));// count 순번의 저자배열의 list에 동적메모리 할당
	
		s_token=strtok(NULL,","); // 읽어들인 문자열에 strtok 함수 사용하여 , 전의 문자열을 저장
		strcpy(array[count].list->b_name,s_token); // 도서명 저장

		s_token=strtok(NULL,","); // 읽어들인 문자열에 strtok 함수 사용하여 , 전의 문자열을 저장
		array[count].list->b_Qty=atoi(s_token); // 재고량을 정수형태로 변환 후 저장
	
		s_token=strtok(NULL,","); // 읽어들인 문자열에 strtok 함수 사용하여 , 전의 문자열을 저장
		array[count].list->b_price=atof(s_token); // 가격을 실수형태로 변환 후 저장
	
		array[count].list->next=NULL; // list의 next를 NULL값으로 초기화(참조할때 사용)
		count++; // count 값 증가
	}
	}
	for(i=0;i<count-1;i++) // 전체 저자의 수 -1 만큼 반복문 실행
	{
		for(j=0;j<count-i-1;j++) // 0번째 순번부터 (마지막-1)순번의 저자를 탐색할때까지 반복문 실행
		{
			if(strcmp(array[j].l_name,array[j+1].l_name)>0) // j와 j+1순번의 저자명을 비교후 오름차순으로 정렬하기 위해 조건문 설정 
			{
				temp1=array[j];
				array[j]=array[j+1];
				array[j+1]=temp1; // 데이터 swap(위치를 바꾼다)
			}
		}
	}
	array[count].list=NULL; // 마지막 저자의 정보가 담긴 배열의 다음 순번의 list를 NULL로 초기화(참조할때 사용)
	fclose(stream); // 파일을 닫는다
}
void printMenu(char array[])
{
	int i=0;// 반복문에 사용할 변수
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
	scanf("%s",array); // 배열에 문자열을 입력받는다
	while(array[i]!='\0') // 문자열의 끝에 도달할때까지 반복문 실행
	{
		if(!isdigit(array[i])) // 십진수 형태의 문자가 입력되지 않은 경우
			strcpy(array,"9"); // 9로 배열을 바꾼다
		i++;
	}
}
void displayInventory(author array[])
{
	int i=0; // 반복문에 사용할 변수
	book* j; // 도서 정보를 정렬하기 위해 사용할 포인터 변수
	book* k; // 도서 정보를 정렬하기 위해 사용할 포인터 변수
	book* temp2; // 도서 정보를 정렬하기 위해 사용할 포인터 변수
	while(array[i].list!=NULL) // 모든 저자의 정보를 탐색할때까지 반복문 실행
	{
		for(j=array[i].list;j;j=j->next) // j에 i번째 저자의 리스트 저장후 리스트 끝에 도달할때까지 반복문 실행
		{
			for(k=j->next;k;k=k->next) // k에 j번째 다음의 저자의 리스트 저장후 리스트 끝에 도달할때까지 반복문 실행
			{
				if(strcmp(j->b_name,k->b_name)>0)  // 만약 j와 k의 도서명을 비교후 알파벳의 오름차순 조건에 맞추기 위해
				{
					temp2=(book*)malloc(sizeof(book));
					strcpy(temp2->b_name,j->b_name);
					temp2->b_price=j->b_price;
					temp2->b_Qty=j->b_Qty; // temp에 j의 도서정보 저장

					strcpy(j->b_name,k->b_name);
					j->b_price=k->b_price;
					j->b_Qty=k->b_Qty; // j에 k의 도서정보 저장

					strcpy(k->b_name,temp2->b_name);
					k->b_price=temp2->b_price;
					k->b_Qty=temp2->b_Qty; // k에 temp의 도서 정보 저장
				}// 데이터의 swap 실행
			}
		}
		i++;
	}
	i=0; // i=0 초기화
	while(array[i].list!=NULL) // 모든 저자의 정보를 탐색할때까지 반복문 실행
	{
		printf("The author is: %s, %s\n",array[i].l_name,array[i].f_name); // 저자 명을 출력
		temp2=array[i].list; // 저자의 도서정보를 temp2에 저장

		while(temp2) // 저자의 모든 도서정보를 탐색하기 위해 반복문 실행
		{
			printf("\n\tThe title is: %s\n\t",temp2->b_name); // 도서명 출력
			printf("The qty is: %d\n\t",temp2->b_Qty); // 재고량 출력
			printf("The price is: %.2lf\n\n\t",temp2->b_price); // 가격 출력
			printf("----\n\n");
			temp2=temp2->next; // temp2의 위치 조정
		}
		i++;
	}

}
void displayAuthorsWork(author array[])
{
	int i=0; // 반복문에 사용할 변수
	char c; // 한글자씩 문자를 입력받을때 사용할 변수
	char first[30]; // 저자의 first name
	char last[30]; // 저자의 last name
	book* j; // 도서 정보를 정렬하기 위해 사용할 포인터 변수
	book* k; // 도서 정보를 정렬하기 위해 사용할 포인터 변수
	book* temp2; // 도서 정보를 정렬하기 위해 사용할 포인터 변수
	// 먼저 저장된 도서의 정보를 정렬한다
	while(array[i].list!=NULL) // 모든 저자의 정보를 참조할때까지 반복문 실행
	{
		for(j=array[i].list;j;j=j->next) // j에 i번째 저자의 리스트 저장후 리스트 끝에 도달할때까지 반복문 실행
		{
			for(k=j->next;k;k=k->next) // k에 j번째 다음의 저자의 리스트 저장후 리스트 끝에 도달할때까지 반복문 실행
			{
				if(strcmp(j->b_name,k->b_name)>0) // 만약 j와 k의 도서명을 비교후 오름차순 조건에 맞추기 위해
				{
					temp2=(book*)malloc(sizeof(book));
					strcpy(temp2->b_name,j->b_name);
					temp2->b_price=j->b_price;
					temp2->b_Qty=j->b_Qty; // temp에 j의 도서정보 저장

					strcpy(j->b_name,k->b_name);
					j->b_price=k->b_price;
					j->b_Qty=k->b_Qty; // j에 k의 도서정보 저장

					strcpy(k->b_name,temp2->b_name);
					k->b_price=temp2->b_price;
					k->b_Qty=temp2->b_Qty; // k에 temp의 도서 정보 저장
				} // 데이터의 swap 실행
			}
		}
		i++;
	}
	i=0; // i값 초기화
	rewind(stdin);
	printf("Enter the author's first name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// first에 작가의 이름을 한글자씩 입력받는다
	{
		first[i]=c;
	}first[i]='\0'; // 문자열 끝에 종료문자 삽입
	rewind(stdin);
	printf("Enter the author's last name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// last에 작가의 이름을 한글자씩 입력받는다
	{
		last[i]=c;
	}
	last[i]='\0'; // 문자열 끝에 종료문자 삽입
	makeName(first); // 사용하는 형식에 알맞게 문자열 변환
	makeName(last); // 사용하는 형식에 알맞게 문자열 변환
	
	i=0; // i=0 초기화
	while(array[i].list!=NULL) // 모든 저자의 정보를 참조할때까지 반복문 실행
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0) // 만약 입력받은 저자명과 일치하는 저자명을 찾은 경우
		{
			temp2=array[i].list; // temp2에 저자의 도서 정보가 담긴 리스트의 시작위치를 저장
			while(temp2) // 모든 도서 정보를 참조할때까지 반복문 실행
			{
				printf("\n\tThe title is: %s\n\t",temp2->b_name); // 도서명 출력
				printf("The qty is: %d\n\t",temp2->b_Qty); // 재고량 출력
				printf("The price is: %.2lf\n\n\t",temp2->b_price); // 가격 출력 
				printf("----\n\n");
				temp2=temp2->next; // temp2의 위치 수정
			}
			return; // 함수 종료 
		}
		i++;
	}
	printf("The author you requested does not exist.\n\n"); // 모든 저자의 정보를 탐색하였지만 원하는 저자가 없는 경우 메세지 출력
	return ;
}
void addBook(author array[])
{
	char first[30]; // 저자의 first name
	char last[30]; // 저자의 last name
	char title[30]; // 도서명
	char qty[10]; // 재고량
	char price[10]; // 가격
	int i,j,k,r_qty=0,button; // 변수 i,j,k는 반복문에 사용, button은 가격 입력형태를 판단하는데 사용, r_qty는 정수 형태로 변경한 재고량 저장 변수
	double r_price=0; // r_price에는 실수형태로 변경한 가격이 저장
	char c; // 문자열을 한글자씩 입력받는다
	book* cur; // 도서 정보가 담긴 리스트를 정렬할때 사용
	book* pre; // 도서 정보가 담긴 리스트를 정렬할때 사용
	author temp1; // 저자의 정보를 저장할 변수
	book* temp2=(book*)malloc(sizeof(book)); // 도서의 정보를 담을 포인터 변수 설정후 동적 메모리 할당

	rewind(stdin);
	printf("Enter the author's first name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// first에 작가의 이름을 한글자씩 입력받는다
	{
		first[i]=c;
	}first[i]='\0'; // 문자열 끝에 종료문자 삽입
	makeName(first); // 사용할 형식에 알맞게 문자열 변환
	rewind(stdin);
	printf("Enter the author's last name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// last에 작가의 이름을 한글자씩 입력받는다
	{
		last[i]=c;
	}last[i]='\0'; // 문자열 끝에 종료문자 삽입
	rewind(stdin);
	printf("Enter the title:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// title에 도서의 제목을 한글자씩 입력받는다
	{
		title[i]=c;
	}title[i]='\0'; // 문자열 끝에 종료문자 삽입
	rewind(stdin);
	makeName(first); // 사용할 형식에 맞게 문자열 변환
	makeName(last); // 사용할 형식에 맞게 문자열 변환
	makeName(title); // 사용할 형식에 맞게 문자열 변환
	
	i=0; // i=0 초기화
	while(array[i].list!=NULL) // 저장된 모든 저자의 정보를 참조할때까지 반복문 실행
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0) // 입력한 저자명과 일치하는 저자명을 배열에서 찾은 경우 
		{
			cur=array[i].list; // cur에 현재 저자의 정보를 저장
			while(cur) // 저자의 모든 도서 정보를 참조할때까지 반복문 실행
			{
				if(strcmp(cur->b_name,title)==0) // 만약 입력한 도서명과 일치하는 도서를 찾은 경우
				{
					printf("This book is already in the Inventory and cannot be added again\n");
					return;
				} // 적절한 메세지 출력후 함수 종료
				cur=cur->next; // cur의 위치 변환
			}
		}
		i++;
	}
	i=0; // i=0 초기화
	while(r_qty==0) // r_qty의 값이 변경될때까지 반복문 실행
	{
		i=0;
		printf("Enter the qty:");
		scanf("%s",qty); // 재고량을 문자열 형태로 입력받는다
		rewind(stdin);
		
		while(qty[i]!='\0') // 문자열의 끝에 도달할때까지 반복문 실행
		{
			if(!isdigit(qty[i])) // 십진수 형태의 문자가 입력되지 않은 경우
			{
				printf("Invalid input for qty\n");
				break;
			} // 적절한 메세지 출력후 반복문 종료
			i++;

			if(qty[i]=='\0') // 십진수 형태의 문자만 입력받은 후 문자열의 끝에 도달한 경우
			{
				r_qty=atoi(qty);
			} // r_qty에 정수형태로 변환후 저장
		}
	}
	while(r_price==0) // r_price의 값이 변경될때까지 반복문 실행
	{
		i=0,button=0; // i와 button 0으로 초기화
		printf("Enter the price:");
		scanf("%s",price); // 가격을 문자열 형태로 입력받는다
		rewind(stdin);
		while(price[i]!='\0') // 문자열의 끝에 도달할때까지 반복문 실행
		{
			if(!isdigit(price[0]))
			{
				break;
			}// 첫번째 문자가 십진수 형태가 아닌 경우 반복문 종료
			if(!isdigit(price[i])&&price[i]!='.')
			{
				break;
			}// 입력받은 문자가 .이 아닌 다른 문자인 경우 반복문 종료
			if(price[i]=='.')
			{
				break;
			} // 입력받은 문자가 .인 경우 반복문 종료
			i++;
		}
		if(price[i]=='.') // 입력받은 문자가 .인 경우
		{
			button=i; // .의 위치를 button에 저장
			i++; // i 값 증가
			// 프로그램에서 사용하는 실수의 형태는 소수점 아래 두자리를 무조건 기입해야 실행함.
			//example ) 5.364은 잘못된 입력, 5.35와 같은 형태 의 입력이 올바르다
			if(price[button+1]=='\0') // .을 기준으로 그 다음 문자가 종료문자인 경우
				button=100; // button 값 100으로 변경
			if(price[button+2]=='\0') // .을 기준으로 그 다음 다음 문자가 종료문자인 경우
				button=100; // button 값 100으로 변경
			if(price[button+3]!='\0') // .을 기준으로 그 다음 다음 다음 문자가 종료문자가 아닌 경우
				button=100; // button 값 100으로 변경
			while(price[i]!='\0') // i번째 문자가 종료문자일때까지 반복문 실행
			{
				if(!isdigit(price[i])) // 십진수가 아닌 형태의 문자가 입력된 경우
				{
					button=100;
					break;
				} // button 값 100으로 변경후 반복문 종료
				i++;
			}
			if(button!=100)	// 위의 조건을 모두 만족하지 않은 올바른 형태의 가격이 입력된 경우
			   r_price=atof(price); // r_price에 실수 형태로 변환 후 저장
		}
		if(r_price==0) // 만약 r_price의 값이 변경되지 않은 경우
			printf("invalid input for price\n"); // 메세지 출력
	}
	strcpy(temp2->b_name,title); // temp2의 도서명 부분에 도서 명 복사
	temp2->b_price=r_price; // temp2의 가격 부분에 r_price 저장
	temp2->b_Qty=r_qty; // temp2의 재고량 부분에 r_qty 저장
	temp2->next=NULL; // temp2의 next를 NULL값으로 초기화
	
	i=0; // i=0 초기화
	while(array[i].list!=NULL) // 모든 저자의 정보를 참조할때까지 반복문 실행
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0) // 원하는 저자를 찾은 경우
		{
			cur=array[i].list; // cur의 위치를 시작으로 설정
			pre=array[i].list; // pre의 위치를 시작으로 설정
			while(cur) // cur이 NULL이 아닐때까지 반복문 실행
			{
				pre=cur; // pre에 cur값 저장
				cur=cur->next; // cur의 위치 변환
			}
			pre->next=temp2; // 도서의 마지막 위치 그 다음에 temp2 삽입
			return; // 함수 종료
		}
		i++;
	} 
	// 새로 추가되는 저자의 정보일 경우
	strcpy(array[i].f_name,first); // 그 다음 순번(i)에 저자의 first name 복사
	strcpy(array[i].l_name,last); // 그 다음 순번(i)에 저자의 last name 복사
	array[i].list=temp2; // 새로운 저자의 첫 도서(temp)를 리스트에 저장
	array[i+1].list=NULL; // 그 다음 순번의 저자 위치의 list를 NULL로 초기화(참조시 위치를 찾기 위해 설정)

	// 새로운 저자의 정보가 추가되었으므로 저자정보가 저장된 구조체 배열을 정렬할 필요가 있다
	for(j=0;j<i;j++)
	{
		for(k=0;k<i-j;k++) // 정렬은 버블정렬 사용
		{
			if(strcmp(array[k].l_name,array[k+1].l_name)>0) // k순번의 저자명과 k+1순번의 저자명을 비교하여 알파벳 순으로 오름차순이 되도록
			{
				temp1=array[k];
				array[k]=array[k+1];
				array[k+1]=temp1; // 위치를 바꾼다
			}
		}
	}
}
void changePrice(author array[])
{
	char first[30]; // 작가의 frist name
	char last[30]; // 작가의 last name
	char title[30]; // 도서명
	char price[10]; // 가격을 저장할 문자열
	int i,idx; // i는 반복문에 사용할 변수, idx는 위치를 찾은경우 i값을 저장할 변수
	double r_price; // 실제 실수로 변환된 가격을 저장할 변수
	double del_price=0; // 변경 전의 가격을 저장할 실수형 변수
	int button; // 반복문 탈출 조건에 사용할 변수
	char c; // 문자열을 한글자씩 입력 받을때 사용할 변수
	book* cur; // book 리스트를 참조할 포인터 변수
	rewind(stdin);
	printf("Enter the author's first name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// first에 작가의 이름을 한글자씩 입력받는다
	{
		first[i]=c;
	}first[i]='\0'; // 문자열 끝에 종료문자 삽입
	makeName(first); // 사용할 형식에 알맞게 문자열 변환
	rewind(stdin);
	printf("Enter the author's last name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// last에 작가의 이름을 한글자씩 입력받는다
	{
		last[i]=c;
	}
	last[i]='\0'; // 문자열 끝에 종료문자 삽입
	makeName(last); // 사용할 형식에 알맞게 문자열 변환
	rewind(stdin);
	i=0;
	while(array[i].list!=NULL) // 저장된 모든 저자를 참조할때까지 반복문 실행
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0)
		{
			idx=i;
			break;
		}// 입력받은 저자의 이름과 같은 이름을 배열에서 찾았을 경우 idx에 순번 저장후 반복문 종료
		i++;
	}
	if(array[i].list==NULL)// 모든 저자를 참조하였지만 입력받은 이름을 찾지 못한 경우
	{
		printf("No such author in your database. So you cannot change the price\n");
		return ;
	} // 적절한 메세지 출력 후 함수 종료
	printf("Enter the title:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)
	{
		title[i]=c;
	} // 도서의 제목을 한글자씩 입력받는다
	title[i]='\0'; // 마지막 글자 다음에 종료문자 삽입
	rewind(stdin);
	makeName(title); // 사용할 형식에 알맞게 도서명 변환
	
	cur=array[idx].list; // 찾은 저자의 리스트를 cur에 저장
	
	while(cur) // 모든 도서의 정보를 참조할때까지 반복문 실행
	{
		if(strcmp(cur->b_name,title)==0) // 만약 title과 같은 책제목을 찾은 경우
			break; // 반복문 종료
		cur=cur->next; // cur의 위치 변환
	}
	if(cur==NULL) // 만약 모든 도서의 정보를 참조하였지만 title과 같은 이름의 책 제목을 찾지 못한 경우
	{
		printf("No book with the title %s by %s, %s\n",title,last,first);
		return;
	} // 적절한 메세지 출력후 함수 종료
	r_price=0; // 실수 형태의 가격을 저장할 변수 0으로 초기화

	while(r_price==0) // 제대로된 형태의 가격이 입력될때까지 반복문 실행
	{
		i=0,button=0; // 반복문에 사용할 i, 조건에 사용할 button 초기화 
		printf("Enter the price:");
		scanf("%s",price); // 가격을 입력받아 문자열에 저장
		rewind(stdin);
		while(price[i]!='\0') // 문자열의 끝에 도달할때까지 반복문 실행
		{
			if(!isdigit(price[0])) // 만약 첫번째 문자가 십진수 형태의 문자가 입력되지 않은 경우
			{
				break;
			} // 반복문 종료
			if(!isdigit(price[i])&&price[i]!='.')
			{
				break;
			}// 문자 .이 아닌 문자가 입력된 경우 반복문 종료
			if(price[i]=='.')
			{
				break;
			}// 문자 .이 입력된 경우 반복문 종료
			i++;
		}
		if(price[i]=='.') // i번째 문자가 .인경우
		{
			button=i; // button에 i값 저장
			i++; // i의 값 증가
			// 프로그램에서 사용하는 실수의 형태는 소수점 두자리를 무조건 기입해야 실행함.
			//example ) 5.364은 잘못된 입력, 5.35와 같은 형태 의 입력이 올바르다
			if(price[button+1]=='\0') // 만약 .을 기준으로  그 다음 글자가 종료문자라면
				button=100; // button의 값 변경
			if(price[button+2]=='\0') // .을 기준으로 그 다음 다음 글자가 종료 문자라면
				button=100; // button의 값 변경
			if(price[button+3]!='\0') // .을 기준으로 그 다음 다음 다음 글자가 종료 문자가 아니라면
				button=100; // button의 값 변경
			while(price[i]!='\0') // i순번의 문자열이 종료문자를 만날때까지 반복문 실행
			{
				if(!isdigit(price[i]))
				{
					button=100;
					break;
				}// 만약 십진수 형태의 문자가 입력되지 않은 경우 button값 변경후 반복문 종료
				i++;
			}
			if(button!=100)	// 만약 위의 조건을 모두 만족하지 않은(5.35와 같은 형태의 문자열 입력인 경우)
			   r_price=atof(price); // r_price에 실수형태로 변환 후 저장
		}
		if(r_price==0) // 올바른 형태의 실수 입력이 이루어지지 않은 경우
			printf("invalid input for price\n"); // 메세지 출력
	}
	
	del_price=cur->b_price; // 변경 전의 가격을 del_price에 저장
	cur->b_price=r_price; // 변경 후의 가격을 cur이 가르키는 위치의 가격에 저장
	printf("Price will be updated from %.2lf to %.2lf\n",del_price,cur->b_price);

	return ;
}
void changeQty(author array[])
{
	char first[30]; // 원하는 도서 저자의 first name
	char last[30]; // 원하는 도서 저자의 last name
	char title[30]; // 변경을 원하는 도서명
	char qty[10]; // 재고량의 변수
	int i,idx,r_qty,del_qty=0; // i는 반복문에 사용, idx는 원하는 순번을 찾았을때 저장 변수, r_qty,del_qty는 정수형태의 재고량 저장변수
	char c; // 한글자씩 입력을 받는다
	book* cur; // book을 참조시 사용할 포인터 변수

	rewind(stdin);
	printf("Enter the author's first name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// first에 작가의 이름을 한글자씩 입력받는다
	{
		first[i]=c;
	}first[i]='\0'; // 마지막 글자 다음에 종료문자 삽입
	makeName(first); // 작가의 이름을 프로그램 내에서 사용하는 형식에 맞게 변환
	rewind(stdin);
	printf("Enter the author's last name:");
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)// last에 작가의 이름을 한글자씩 입력받는다
	{
		last[i]=c;
	}
	last[i]='\0'; // 마지막 글자 다음에 종료문자 삽입
	makeName(last); // 작가의 이름을 프로그램 내에서 사용하는 형식에 맞게 변환
	rewind(stdin);
	i=0;
	while(array[i].list!=NULL) // 저장된 모든 저자를 참조할때까지 반복문 실행
	{
		if(strcmp(array[i].f_name,first)==0&&strcmp(array[i].l_name,last)==0)
		{
			idx=i;
			break;
		} // 원하는 작가의 이름을 찾았을경우 반복문 종료후 그 순번의 값을 idx에 저장
		i++;
	}
	if(array[i].list==NULL)// 모든 저자를 참조하였지만 입력받은 저자를 찾지 못한 경우 
	{
		printf("No such author in your database. So you cannot change the qty\n");
		return ;
	} // 적절한 메세지 출력후 함수 종료
	printf("Enter the title:"); 
	for(i=0;(c=getchar())!=EOF&&c!='\n';i++)
	{
		title[i]=c;
	}// titlr에 도서의 제목을 한글자씩 입력받는다
	title[i]='\0'; // title의 마지막 다음 순번에 종료문자 삽입
	rewind(stdin);
	makeName(title); // 형식에 맞게 변형
	cur=array[idx].list; // 현재위치를 찾은 저자의 .list로 설정
	while(cur)// 저자의 모든 도서를 참조하는 동안
	{
		if(strcmp(cur->b_name,title)==0) // 만약 입력한 책제목과 도서명이 같은 경우
			break; // 반복문 탈출
		cur=cur->next; // cur의 위치 조정
	}
	if(cur==NULL) // 저자의 모든 도서를 참조하였지만 입력한 책의 제목을 찾지 못한 경우
	{
		printf("No book with the title %s by %s, %s\n",title,last,first);
		return;
	} // 적절한 메세지 출력후 함수 종료
	r_qty=0; // 실제 책의 수량을 저장할 변수 0으로 초기화
	while(r_qty==0) // r_qty의 값이 변하지 않는 동안 반복문 실행
	{
		i=0; // 반복문에 사용
		printf("Enter the qty:");
		scanf("%s",qty); // 수량을 입력받아 qty에 저장
		rewind(stdin);
		
		while(qty[i]!='\0') // 입력받은 문자열 형태의 qty가 종료문자가 아닐때까지 한 글자씩 파악
		{
			if(!isdigit(qty[i])) // 만약 i번째 문자가 십진수형태의 문자가 아니라면
			{
				printf("Invalid input for qty\n");
				break;
			} // 적절한 메세지 출력후 반복문 탈출
			i++;

			if(qty[i]=='\0')
			{
				r_qty=atoi(qty);
			} // 십진수 형태의 문자만 입력받아 문자열의 끝에 도달한 경우 문자열 qty를 정수형태로 변형 후 r_qty에 저장
		}
	}
	del_qty=cur->b_Qty; // 변경전의 재고량을 del_qty에 저장
	cur->b_Qty=r_qty; // 변경후의 재고량(r_qty)를 현재 cur이 가리키는 list의 재고량에 저장
	printf("Qty will be updated form %d to %d\n",del_qty,cur->b_Qty);
	return ;
}
void totalQty(author array[])
{
	int i=0; // 반복문에 사용할 변수
	int total=0; // 계속해서 값을 저장할 변수
	book* cur; // 도서 정보가 담긴 리스트를 참조하기 위해 사용할 포인터 변수
	while(array[i].list!=NULL)// 모든 저자의 정보를 참조하기 전까지 반복문 실행
	{
		cur=array[i].list; // 현재 순번의 저자의 도서 정보가 담긴 리스트를 cur에 저장
		while(cur)// 모든 도서의 정보를 참조할때까지 반복문 실행
		{
			total=total+cur->b_Qty;// total에 도서의 개수를 계속해서 축적
			cur=cur->next;// 다음 도서의 정보를 참조
		}
		i++;
	}
	printf("The total number of books is %d\n",total);
	return ;
}
void calculateTotalAmount(author array[])
{
	int i=0; // 반복문에 사용할 변수
	double total=0; // 총 가격을 저장할 변수
	int s_book=0; // 도서의 개수를 알려주는 변수
	book* cur; // 도서 정보가 담긴 리스트를 참조하기 위해 사용할 포인터 변수
	while(array[i].list!=NULL)// 모든 저자의 정보를 참조하기 전까지 반복문 실행
	{
		cur=array[i].list; // 현재 순번의 저자의 도서 정보가 담긴 리스트를 cur에 저장
		while(cur)// 모든 도서의 정보를 참조할때까지 반복문 실행
		{
			s_book=cur->b_Qty;//s_book에 현재 도서의 개수 저장
			total=total+(cur->b_price*s_book); // total의 값에 도서의 개수*1개당 가격을 저장
			cur=cur->next;// 다음 도서의 정보 참조
		}
		i++;
	}
	printf("The total number of books is $%.2lf\n",total);
	return ;
}
void makeName(char array[])
{
	int i=0; // 반복문에 사용할 변수
	if(islower(array[0])){
		array[0]=toupper(array[0]);
	} // 만약 입력받은 배열의 첫번째 idx의 값이 소문자라면 대문자로 전환
	i++; // 1번째 인덱스부터 반복문을 실행
	while(array[i]!='\0')// 배열의 끝이 아닐때까지 반복문 실행
		{
			if(array[i-1]==' ') // 만약 그전 idx가 공백(띄어쓰기)라면 대문자로 전환
				array[i]=toupper(array[i]);
			else// 그렇지 않으면 소문자로 전환
				array[i]=tolower(array[i]);
			i++;
		}
}


