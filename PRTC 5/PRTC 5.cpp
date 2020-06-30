#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "windows.h"
#include "time.h"

struct Marsh {
	char destination[20];
	int departure[20];
	int routeID;
	Marsh* next;
};

void push(Marsh**, Marsh*);  // Вставка в самое начало списка

BOOL insertAfter(Marsh*, Marsh*); // Вставка после данного элемента 
									 //	TRUE - вставили успешно, FALSE - ошибка вставки
//Вставка в конец списка
void append(Marsh**, Marsh*);
//Обертка над 3мя вариантами вставки, с нужными проверками
void insertInPlace(Marsh**, Marsh*, int);

//Создать список с заданными данными
Marsh* createRoutes();
//Создать новый элемент
Marsh* createRoute();
//Обертка над ф-цией создания студента
void addRoutes(Marsh**);

//Вывести весь список начиная с первого
void outAll(Marsh*);

//Адрес на предыдущего студента по порядковому номеру следующего
Marsh* prevBySerNum(Marsh*, int);

//Удаление из списка по адресу предыдущего элемента
void deleteRoute(Marsh**, Marsh*);
//Удаление всех элементов списка
Marsh* deleteAll(Marsh* start);
//Обертка над функцией удаления, чтобы удалять по номеру
BOOL deleteByNumber(Marsh**, int);

//Обмен двух элементов, если для них есть предыдущий
void swapNodes(Marsh*, Marsh*, Marsh*);
//Сортировка списка студентов по имени по алфавиту
Marsh* alphabetSort(Marsh*);


int main() {
	Marsh* allRoutes = createRoutes();
	int choice;
	int MarshToDelete;

	while (true) {
		printf("1 - Print all Marshs \n");
		printf("2 - Add Marsh \n");
		printf("3 - Delete Marsh \n");
		printf("4 - Sort by ID \n");
		printf("5 - Delete all Marshs \n");
		printf("0 - Exit \n");
		
		printf(" Your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 0:
			return 0;
			break;
		case 1:
			outAll(allRoutes);
			break;
		case 2:
			addRoutes(&allRoutes);
			break;
		case 3:
			printf("\n You're gonna remove the route.");
			MarshToDelete = 0;
			do {
				printf("\n Enter route number: ");
				scanf("%d", &RouteToDelete);
			} while (MarshToDelete < 1);

			if (deleteByNumber(&allMarshs, MarshToDelete)) {
				printf("\n[Marsh deleted successfully]\n");
				outAll(allMarshs);
			}
			else printf("[Wrong choice]\n\n");
			break;
		case 4:
			allMarshs = alphabetSort(allMarshs);
			printf("\n[Marsh sorted successfully]\n");
			outAll(allMarshs);
			break;
		case 5:
			printf("\n[Marshs with mark 2]");
			outLosers(allMarshs);
			printf("\n\n");
			break;
		case 6:
			allMarshs = deleteAll(allMarshs);
			printf("\n[ALL Marsh DELETED successfully]\n\n");
			break;
		}
	}

	printf("\nBye...\n");
	system("pause");
	return 0;
}

Marsh* createRoutes() {
	Marsh* rt1 = new Marsh;
	Marsh* rt2 = new Marsh;
	Marsh* rt3 = new Marsh;
	Marsh* rt4 = new Marsh;
	Marsh* rt5 = new Marsh;
	Marsh* rt6 = new Marsh;
	Marsh* rt7 = new Marsh;
	Marsh* rt8 = new Marsh;
	Marsh* rt9 = new Marsh;
	Marsh* rt10 = new Marsh;
	Marsh* rt11 = new Marsh;

	*rt = { "\0", 41,{ 5,5,3,4,5 }, st2 };
	strcpy(st1->name, "Douglas V.B.");
	*st2 = { "\0", 32,{ 3,4,4,5,2 },  st3 };
	strcpy(st2->name, "Michael B.D.");
	*st3 = { "\0", 11,{ 3,3,4,5,5 },  st4 };
	strcpy(st3->name, "James M.M.");
	*st4 = { "\0", 41,{ 3,4,3,4,2 },  st5 };
	strcpy(st4->name, "Phillip C.W.");
	*st5 = { "\0", 21,{ 5,5,5,5,5 },  st6 };
	strcpy(st5->name, "Robert H.M.");
	*st6 = { "\0", 11,{ 5,4,3,4,5 },  st7 };
	strcpy(st6->name, "Michael M.H.");
	*st7 = { "\0", 34,{ 3,3,3,2,3 },  st8 };
	strcpy(st7->name, "Joshua A.T.");
	*st8 = { "\0", 43,{ 4,4,2,3,4 },  st9 };
	strcpy(st8->name, "Clinton T.W.");
	*st9 = { "\0", 11,{ 5,4,3,4,5 },  st10 };
	strcpy(st9->name, "Rose W.M.");
	*st10 = { "\0", 34,{ 3,3,3,2,3 }, st11 };
	strcpy(st10->name, "Veronica P.C.");
	*st11 = { "\0", 43,{ 4,4,2,3,4 }, NULL };
	strcpy(st11->name, "Beth J.C.");

	return st1;
}

Marsh* createRoute() {
	Marsh* route = new Marsh;
	*route = { "\0", -1,{ -1, -1, -1, -1, -1 }, NULL };

	char MarshName[15] = "";
	char MarshLastName[5] = "";
	char MarshFullName[20] = "";
	do {
		printf("Enter name of the Marsh (<20 symbols): ");
		scanf("%s%s", &MarshName, &MarshLastName);
		strcpy(MarshFullName, MarshName);
		strcat(MarshFullName, " ");
		strcat(MarshFullName, MarshLastName);
	} while (strlen(MarshFullName) < 8);
	strcpy(Marsh->name, MarshFullName);

	do {
		printf("Enter Marsh's group: ");
		scanf("%d", &Marsh->group);
	} while (Marsh->group < 1 || Marsh->group > 999);

	do {
		printf("Enter FIVE Marsh's marks (you can enter 0 as well) [Example: 5 5 4 5 2]: ");
		scanf("%d%d%d%d%d", &Marsh->perfomance[0], &Marsh->perfomance[1], &Marsh->perfomance[2], &Marsh->perfomance[3], &Marsh->perfomance[4]);
	} while (Marsh->perfomance[0] < 0 || Marsh->perfomance[0] > 5
		|| Marsh->perfomance[1] < 0 || Marsh->perfomance[1] > 5
		|| Marsh->perfomance[2] < 0 || Marsh->perfomance[2] > 5
		|| Marsh->perfomance[3] < 0 || Marsh->perfomance[3] > 5
		|| Marsh->perfomance[4] < 0 || Marsh->perfomance[4] > 5);

	return Marsh;
}

//Удаление из списка по адресу предыдущего элемента
void deleteMarsh(Marsh** start, Marsh* previous) {
	Marsh* toDelete;

	//Если список пуст
	if (*start == NULL)
		return;
	//Если нужно удалить первый элемент
	if (previous == NULL) {
		toDelete = *start;
		*start = (*start)->next;
		delete toDelete;
	}
	else {
		toDelete = previous->next;
		previous->next = toDelete->next;
		delete toDelete;
	}

	return;
}

//Удаление всех элементов списка
Marsh* deleteAll(Marsh* start) {
	Marsh* current = start;
	Marsh* next = NULL;

	//Пока не в конце списка
	while (current != NULL) {
		next = current->next;
		delete current;
		current = next;
	}

	return NULL;
}

//Вставка в самое начало списка
void push(Marsh** start, Marsh* newMarsh) {
	newMarsh->next = (*start);
	(*start) = newMarsh;
}

//Вставка после данного элемента
//TRUE - вставили успешно, FALSE - ошибка вставки
BOOL insertAfter(Marsh* previous, Marsh* newMarsh) {
	if (previous == NULL)
		return -1;

	newMarsh->next = previous->next;
	previous->next = newMarsh;
	return TRUE;
}

//Вставка в конец списка
void append(Marsh** start, Marsh* newMarsh) {
	Marsh* last = *start;

	newMarsh->next = NULL;

	//Если список пуст, сделаем этот элемент первым
	if (*start == NULL) {
		*start = newMarsh;
		return;
	}

	//Дойдем до последнего
	while (last->next != NULL)
		last = last->next;

	//И заменим последнему некст
	last->next = newMarsh;
	return;
}

//Адрес на предыдущего студента по порядковому номеру следующего
Marsh* prevBySerNum(Marsh* start, int serNum) {
	//Итератор для цикла, начинаем с самого начала
	Marsh* current = start;
	int serIter = 2;

	if (serNum == 1)
		return NULL;

	//Пока не в конце списка
	while (current != NULL) {
		//Если номера совпадают, вернем адрес
		if (serIter == serNum)
			return current;
		serIter++;
		current = current->next;
	}

	//Если никого не нашли, то вернем NULL
	return NULL;
}

//Вывести студентов, у кого есть двойки
void outLosers(Marsh* start) {
	//Нашли ли хоть кого-то
	BOOL isFound = FALSE;
	//Итератор для цикла, начинаем с самого начала
	Marsh* current = start;

	//Пока не в конце списка
	while (current != NULL) {
		//Проходим по всем оценкам
		for (int n = 0; n < PERF_NUM; n++) {
			//Если нашли хоть одну двойку
			if (current->perfomance[n] == 2) {
				//Выведем студента, и отметим что нашли кого-то
				printf("\n%20s | Group: %d", current->name, current->group);
				isFound = TRUE;
				break;
			}
		}
		//Продвинемся вперед
		current = current->next;
	}

	//Если никого не нашли,
	if (!isFound) //то сообщим об этом
		printf("\nNothing found!");
}



//Вывести весь список начиная с первого
void outAll(Marsh* start) {
	//Итератор для цикла, начинаем с начала
	Marsh* current = start;
	int serNum = 1;

	printf("\nAll Marshs:\n");

	//Пока мы не в конце списка
	while (current != NULL) {
		//Выводим элемент и продвигаемся вперед
		printf("[#%2d] %20s (Group: %3d) | Marks: [", serNum, current->name, current->group);
		//Выводим все оценки
		for (int n = 0; n < PERF_NUM; n++) {
			if (n != PERF_NUM - 1)
				printf("%d, ", current->perfomance[n]);
			else printf("%d", current->perfomance[n]);

		}
		printf("] | Next: %d\n", current->next);

		serNum++;
		current = current->next;
	}
	printf("\n");
}

//Обмен двух элементов, если для них есть предыдущий
void swapNodes(Marsh* prev, Marsh* one, Marsh* two) {
	prev->next = two;
	one->next = two->next;
	two->next = one;
}

//Сортировка списка студентов по имени по алфавиту
Marsh* alphabetSort(Marsh* start) {
	//Указатель на предыдущий от текущего элемент, 
	//"тератор" для цикла и буфферные переменные для обмена
	Marsh* previous, * current, * buff1, * buff2;
	//Флаг, стоит ли снова запускать цикл сортировки
	BOOL sorted = FALSE;

	//Пока массив не отсортирован
	while (!sorted) {
		sorted = TRUE;
		//Текущий элемент = первый
		current = start;
		//Предыдущего нет
		previous = NULL;

		//Пока есть с кем сравнивать
		while (current->next != NULL) {
			//Алфавитное сравнение
			if (strcmp(current->name, current->next->name) > 0) {
				//Если мы в самом начале списка, то обмен выгдяит
				//следующим образом
				if (previous == NULL) {
					buff1 = start;
					buff2 = start->next->next;
					start = start->next;
					start->next = buff1;
					start->next->next = buff2;
					previous = start;
					current = start->next;
				}
				//Иначе можно просто воспользоваться удобной
				//функцией для обмена
				else {
					swapNodes(previous, current, current->next);
					previous = previous->next;
				}
				//Если была хоть одна замена, значит
				//массив еще не отсортирован до конца
				sorted = FALSE;
			}
			//Если элементы на своих местах, то просто
			//продвинемся вперед
			else {
				previous = current;
				current = current->next;
			}
		}
	}

	//Вернем указатель на новый первый элемент
	return start;
}

//Обертка над 3мя вариантами вставки, с нужными проверками
void insertInPlace(Marsh** start, Marsh* newMarsh, int newPlace) {
	//Если вставляем на 1е место
	if (newPlace == 1)
		push(start, newMarsh);
	else {
		Marsh* previous = prevBySerNum(*start, newPlace);
		//Если элемента перед данным нет
		//(вероятно введено число больше размера списка)
		if (previous == NULL)
			//Вставим в конец списка
			append(start, newMarsh);
		else
			//Если есть, то вставим за предыдущим
			insertAfter(previous, newMarsh);
	}
}

// Добавление маршрута
void addRoute(Marsh** start) {
	int newPlace = -1;

	printf("\n[Add Marsh]\n");

	Marsh* newMarsh = createRoute();
	do {
		printf("Enter place number for new Marsh: ");
		scanf("%d", &newPlace);
	} while (newPlace < 0);

	insertInPlace(start, newMarsh, newPlace);

	printf("\n[Marsh successfully added]\n");
	outAll(*start);
}

//Обертка над функцией удаления, чтобы удалять по номеру
BOOL deleteByNumber(Marsh** start, int delNum) {
	//Если удаляем первый
	if (delNum == 1) {
		deleteMarsh(start, NULL);
	}
	//Если удаляем любой другой
	else {
		Marsh* dels = prevBySerNum(*start, delNum);
		//Ошибка при вводе номера, и такого нет в списке
		if (dels == NULL || dels->next == NULL)
			return FALSE;
		//Удаляем
		else
			deleteMarsh(start, dels);
	}

	return TRUE;
}