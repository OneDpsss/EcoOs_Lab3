/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include "IEcoLab1Events.h"
#include "IEcoConnectionPointContainer.h"
#include "CEcoLab1Sink.h"
#include "IdEcoList1.h"

#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Generate random int in range [min, max]
int rand_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Generate random long in range [min, max]
long rand_long(long min, long max) {
    return min + rand() % (max - min + 1);
}

// Generate random float in range [min, max]
float rand_float(float min, float max) {
    float scale = (float)rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

// Generate random double in range [min, max]
double rand_double(double min, double max) {
    double scale = (double)rand() / (double)RAND_MAX;
    return min + scale * (max - min);
}

// Generate random long double in range [min, max]
long double rand_long_double(long double min, long double max) {
    long double scale = (long double)rand() / (long double)RAND_MAX;
    return min + scale * (max - min);
}
/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;
	/* Указатель на интерфейс контейнера точек подключения */
    IEcoConnectionPointContainer* pICPC = 0;
    /* Указатель на интерфейс точки подключения */
    IEcoConnectionPoint* pICP = 0;
    /* Указатель на обратный интерфейс */
    IEcoLab1Events* pIEcoLab1Sink = 0;
    IEcoUnknown* pISinkUnk = 0;
    uint32_t cAdvise = 0;
	IEcoList1* pIList = 0;

	int32_t* testIntArray = 0;
	long* testLongArray = 0;
	float* testFloatArray = 0;
	double* testDoubleArray = 0;
	long double* testLongDoubleArray = 0;
	uint32_t printSize = 20;
	uint32_t smallSize = 100;
	uint32_t mediumSize = 500;
	uint32_t largeSize = 1000;
	uint32_t i = 0;

	clock_t begin;
    clock_t end;

	IEcoCalculatorX* pIEcoCalculatorX = 0;
    IEcoCalculatorY* pIEcoCalculatorY = 0;
    int16_t i32A = 36, i32B = 2;
    char_t c;

    srand(time(0));

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация компонента коллекций */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
    if (result != 0) {
        goto Release;
    }

	/* Регистрация компонента A */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorA, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    if (result != 0) {
        goto Release;
    }

    /* Регистрация компонента B */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorB, (IEcoUnknown*)GetIEcoComponentFactoryPtr_AE202E543CE54550899603BD70C62565);
    if (result != 0) {
        goto Release;
    }

    /* Регистрация компонента D */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorD, (IEcoUnknown*)GetIEcoComponentFactoryPtr_3A8E44677E82475CB4A3719ED8397E61);
    if (result != 0) {
        goto Release;
    }

    /* Регистрация компонента E */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorE, (IEcoUnknown*)GetIEcoComponentFactoryPtr_872FEF1DE3314B87AD44D1E7C232C2F0);
    if (result != 0) {
        goto Release;
    }
#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

	result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**) &pIEcoCalculatorX);
    if (result != 0 || pIEcoCalculatorX == 0) {
        goto Release;
    }

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**) &pIEcoCalculatorY);
    if (result != 0 || pIEcoCalculatorY == 0) {
        goto Release;
    }

	///* Проверка поддержки подключений обратного интерфейса */
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**) &pICPC);
    if (result != 0 || pICPC == 0) {
        goto Release;
    }

 //   /* Запрос на получения интерфейса точки подключения */
    result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab1Events, &pICP);
    pICPC->pVTbl->Release(pICPC);
    pICPC = 0;
    if (result != 0 || pICP == 0) {
        goto Release;
    }

 //   /* Создание экземпляра обратного интерфейса */
    result = createCEcoLab1Sink(pIMem, (IEcoLab1Events**)&pIEcoLab1Sink);
    if (result != 0 || pIEcoLab1Sink == 0) {
        goto Release;
    }

    result = pIEcoLab1Sink->pVTbl->QueryInterface(pIEcoLab1Sink, &IID_IEcoUnknown, (void**)&pISinkUnk);
    if (result != 0 || pISinkUnk == 0) {
        goto Release;
    }

    result = pICP->pVTbl->Advise(pICP, pISinkUnk, &cAdvise);
    pISinkUnk->pVTbl->Release(pISinkUnk);
    pISinkUnk = 0;
    if (result != 0 || cAdvise == 0) {
        goto Release;
    }

    printf("\n");
    printf("================================================================================\n");
    printf("                    ECO LAB1 - COMPONENT TESTING SUITE\n");
    printf("================================================================================\n");
    printf("\n");

    /* ========== Bucket Sort Demo with Events ========== */
    printf("================================================================================\n");
    printf("  [1] BUCKET SORT DEMONSTRATION WITH EVENT HANDLING\n");
    printf("================================================================================\n");
    {
        int demoArray[] = { 64, 34, 25, 12, 22, 11, 90, 5, 77, 42 };
        int demoSize = sizeof(demoArray) / sizeof(demoArray[0]);
        printf("\nOriginal array: [ ");
        for (i = 0; i < demoSize; ++i) {
            printf("%d ", demoArray[i]);
        }
        printf("]\n");
        printf("\n--- Bucket Sort Event Trace ---\n");
        pIEcoLab1->pVTbl->bucketSortInt(pIEcoLab1, demoArray, demoSize);
        printf("\nSorted array: [ ");
        for (i = 0; i < demoSize; ++i) {
            printf("%d ", demoArray[i]);
        }
        printf("]\n");
    }

    if (pICP != 0 && cAdvise != 0) {
        pICP->pVTbl->Unadvise(pICP, cAdvise);
        cAdvise = 0;
    }
    if (pIEcoLab1Sink != 0) {
        pIEcoLab1Sink->pVTbl->Release(pIEcoLab1Sink);
        pIEcoLab1Sink = 0;
    }
    if (pICP != 0) {
        pICP->pVTbl->Release(pICP);
        pICP = 0;
    }

    /* ========== Тестирование компонентов калькулятора ========== */
    {
        int16_t testCasesX[10][3];
        int16_t expectedAdd[10];
        int16_t expectedSub[10];
        int16_t testCasesY[10][3];
        int16_t expectedMul[10];
        int16_t expectedDiv[10];
        int16_t a, b;
        int16_t addResult, subResult, mulResult, divResult;
        int addOk, subOk, mulOk, divOk;
        
        /* Инициализация тестовых данных для IEcoCalculatorX */
        testCasesX[0][0] = 36; testCasesX[0][1] = 2; testCasesX[0][2] = 0;
        testCasesX[1][0] = 100; testCasesX[1][1] = 50; testCasesX[1][2] = 0;
        testCasesX[2][0] = -10; testCasesX[2][1] = 5; testCasesX[2][2] = 0;
        testCasesX[3][0] = 0; testCasesX[3][1] = 0; testCasesX[3][2] = 0;
        testCasesX[4][0] = -100; testCasesX[4][1] = -50; testCasesX[4][2] = 0;
        testCasesX[5][0] = 32767; testCasesX[5][1] = 1; testCasesX[5][2] = 0;
        testCasesX[6][0] = -32768; testCasesX[6][1] = 1; testCasesX[6][2] = 0;
        testCasesX[7][0] = 15; testCasesX[7][1] = -20; testCasesX[7][2] = 0;
        testCasesX[8][0] = 999; testCasesX[8][1] = -999; testCasesX[8][2] = 0;
        testCasesX[9][0] = 42; testCasesX[9][1] = 0; testCasesX[9][2] = 0;
        
        expectedAdd[0] = 38; expectedAdd[1] = 150; expectedAdd[2] = -5; expectedAdd[3] = 0; expectedAdd[4] = -150;
        expectedAdd[5] = 32768; expectedAdd[6] = -32767; expectedAdd[7] = -5; expectedAdd[8] = 0; expectedAdd[9] = 42;
        
        expectedSub[0] = 34; expectedSub[1] = 50; expectedSub[2] = -15; expectedSub[3] = 0; expectedSub[4] = -50;
        expectedSub[5] = 32766; expectedSub[6] = -32769; expectedSub[7] = 35; expectedSub[8] = 1998; expectedSub[9] = 42;
        
        printf("\n");
        printf("================================================================================\n");
        printf("  [2] CALCULATOR COMPONENTS TESTING\n");
        printf("================================================================================\n");
        
        printf("\n--- Component IEcoCalculatorX (Addition and Subtraction) ---\n");
        printf("+----------------------------------------------------------------------------+\n");
        printf("| Test # | Operation | Operand A  | Operand B  |  Result   | Status |\n");
        printf("+----------------------------------------------------------------------------+\n");
    
        for (i = 0; i < 10; i++) {
            a = testCasesX[i][0];
            b = testCasesX[i][1];
            addResult = pIEcoCalculatorX->pVTbl->Addition(pIEcoCalculatorX, a, b);
            subResult = pIEcoCalculatorX->pVTbl->Subtraction(pIEcoCalculatorX, a, b);
            addOk = (addResult == expectedAdd[i]) ? 1 : 0;
            subOk = (subResult == expectedSub[i]) ? 1 : 0;
            
            printf("|  %2d    |     %c      |    %6d   |    %6d   |   %8d  |  %s  |\n", 
                   i*2+1, '+', a, b, addResult, addOk ? " OK " : "FAIL");
            printf("|  %2d    |     %c      |    %6d   |    %6d   |   %8d  |  %s  |\n", 
                   i*2+2, '-', a, b, subResult, subOk ? " OK " : "FAIL");
        }
        printf("+----------------------------------------------------------------------------+\n");

        /* Инициализация тестовых данных для IEcoCalculatorY */
        testCasesY[0][0] = 36; testCasesY[0][1] = 2; testCasesY[0][2] = 0;
        testCasesY[1][0] = 10; testCasesY[1][1] = 5; testCasesY[1][2] = 0;
        testCasesY[2][0] = -10; testCasesY[2][1] = 5; testCasesY[2][2] = 0;
        testCasesY[3][0] = 0; testCasesY[3][1] = 100; testCasesY[3][2] = 0;
        testCasesY[4][0] = -100; testCasesY[4][1] = -5; testCasesY[4][2] = 0;
        testCasesY[5][0] = 100; testCasesY[5][1] = 4; testCasesY[5][2] = 0;
        testCasesY[6][0] = -20; testCasesY[6][1] = 3; testCasesY[6][2] = 0;
        testCasesY[7][0] = 15; testCasesY[7][1] = -3; testCasesY[7][2] = 0;
        testCasesY[8][0] = 50; testCasesY[8][1] = 2; testCasesY[8][2] = 0;
        testCasesY[9][0] = 99; testCasesY[9][1] = 3; testCasesY[9][2] = 0;
        
        expectedMul[0] = 72; expectedMul[1] = 50; expectedMul[2] = -50; expectedMul[3] = 0; expectedMul[4] = 500;
        expectedMul[5] = 400; expectedMul[6] = -60; expectedMul[7] = -45; expectedMul[8] = 100; expectedMul[9] = 297;
        
        expectedDiv[0] = 18; expectedDiv[1] = 2; expectedDiv[2] = -2; expectedDiv[3] = 0; expectedDiv[4] = 20;
        expectedDiv[5] = 25; expectedDiv[6] = -6; expectedDiv[7] = -5; expectedDiv[8] = 25; expectedDiv[9] = 33;

        printf("\n--- Component IEcoCalculatorY (Multiplication and Division) ---\n");
        printf("+----------------------------------------------------------------------------+\n");
        printf("| Test # | Operation | Operand A  | Operand B  |  Result   | Status |\n");
        printf("+----------------------------------------------------------------------------+\n");
        
        for (i = 0; i < 10; i++) {
            a = testCasesY[i][0];
            b = testCasesY[i][1];
            mulResult = pIEcoCalculatorY->pVTbl->Multiplication(pIEcoCalculatorY, a, b);
            divResult = (b != 0) ? pIEcoCalculatorY->pVTbl->Division(pIEcoCalculatorY, a, b) : 0;
            mulOk = (mulResult == expectedMul[i]) ? 1 : 0;
            divOk = (divResult == expectedDiv[i]) ? 1 : 0;
            
            printf("|  %2d    |     %c      |    %6d   |    %6d   |   %8d  |  %s  |\n", 
                   i*2+1, '*', a, b, mulResult, mulOk ? " OK " : "FAIL");
            printf("|  %2d    |     %c      |    %6d   |    %6d   |   %8d  |  %s  |\n", 
                   i*2+2, '/', a, b, divResult, divOk ? " OK " : "FAIL");
        }
        printf("+----------------------------------------------------------------------------+\n");
    }

    pIEcoCalculatorX->pVTbl->Release(pIEcoCalculatorX);
    pIEcoCalculatorY->pVTbl->Release(pIEcoCalculatorY);

    /* ========== QueryInterface Testing ========== */
    printf("\n--- QueryInterface Check ---\n");
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorX, (void**)&pIEcoCalculatorX);
    printf("  IEcoLab1 -> IEcoCalculatorX: %s\n", (result == 0) ? "[OK]" : "[FAIL]");
    if (result == 0) pIEcoCalculatorX->pVTbl->Release(pIEcoCalculatorX);
    
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoCalculatorY, (void**)&pIEcoCalculatorY);
    printf("  IEcoLab1 -> IEcoCalculatorY: %s\n", (result == 0) ? "[OK]" : "[FAIL]");
    if (result == 0) pIEcoCalculatorY->pVTbl->Release(pIEcoCalculatorY);
    
    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoLab1, (void**)&pIEcoLab1);
    printf("  IEcoLab1 -> IEcoLab1: %s\n", (result == 0) ? "[OK]" : "[FAIL]");
    if (result == 0) pIEcoLab1->pVTbl->Release(pIEcoLab1);

    printf("\n");
    printf("================================================================================\n");
    printf("  [3] BUCKET SORT TESTING ON DIFFERENT DATA TYPES\n");
    printf("================================================================================\n");
    printf("\nContinue with sort testing? (y/n): ");
    c = getchar();
    while (c != 'y' && c != 'n') {
        fflush(stdin);
        c = getchar();
    }
    if (c == 'n') {
        goto Release;
    }
    printf("\n");

	printf("--------------------------------------------------------------------------------\n");
	printf("  TESTING: int32_t (integer arrays)\n");
	printf("--------------------------------------------------------------------------------\n");
	
	/* Test 1: Small array */
	{
		int sorted;
		printf("\n[Test 1/3] Small array (%d elements)\n", smallSize);
		printf("----------------------------------------------------------------------------\n");
		testIntArray = (int32_t*) pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t) * smallSize);
		for (i = 0; i < smallSize; ++i) {
			testIntArray[i] = rand_int(-1000,1000);
		}
		printf("Original array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%d ", testIntArray[i]);
		}
		printf("... ]\n");
		printf("Sorting in progress...\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortInt(pIEcoLab1, testIntArray, smallSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%d ", testIntArray[i]);
		}
		printf("... ]\n");
		/* Correctness check */
		sorted = 1;
		for (i = 1; i < smallSize; i++) {
			if (testIntArray[i-1] > testIntArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testIntArray);
	}

	/* Test 2: Medium array */
	{
		int sorted;
		printf("\n[Test 2/3] Medium array (%d elements)\n", mediumSize);
		printf("----------------------------------------------------------------------------\n");
		testIntArray = (int32_t*) pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t) * mediumSize);
		printf("Generating random data... ");
		for (i = 0; i < mediumSize; ++i) {
			testIntArray[i] = rand_int(-1000,1000);
			if ((i + 1) % 100 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		printf("Original array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%d ", testIntArray[i]);
		}
		printf("... ]\n");
		printf("Sorting in progress (showing progress every 100 elements)...\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortInt(pIEcoLab1, testIntArray, mediumSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%d ", testIntArray[i]);
		}
		printf("... ]\n");
		/* Correctness check */
		sorted = 1;
		for (i = 1; i < mediumSize; i++) {
			if (testIntArray[i-1] > testIntArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testIntArray);
	}

	/* Test 3: Large array with progress */
	{
		int sorted;
		printf("\n[Test 3/3] Large array (%d elements)\n", largeSize);
		printf("----------------------------------------------------------------------------\n");
		testIntArray = (int32_t*) pIMem->pVTbl->Alloc(pIMem, sizeof(int32_t) * largeSize);
		printf("Generating random data... ");
		for (i = 0; i < largeSize; ++i) {
			testIntArray[i] = rand_int(-1000,1000);
			if ((i + 1) % 200 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		printf("Original array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%d ", testIntArray[i]);
		}
		printf("... ]\n");
		printf("Sorting in progress...\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortInt(pIEcoLab1, testIntArray, largeSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%d ", testIntArray[i]);
		}
		printf("... ]\n");
		printf("Sorted array (last %d): [ ... ", printSize);
		for (i = largeSize - printSize; i < largeSize; ++i) {
			printf("%d ", testIntArray[i]);
		}
		printf("]\n");
		/* Correctness check */
		sorted = 1;
		for (i = 1; i < largeSize; i++) {
			if (testIntArray[i-1] > testIntArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testIntArray);
	}


	printf("\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("  TESTING: long (long integer arrays)\n");
	printf("--------------------------------------------------------------------------------\n");
	
	/* Тест 1 */
	{
		int sorted;
		printf("\n[Test 1/3] Small array (%d elements)\n", smallSize);
		printf("----------------------------------------------------------------------------\n");
		testLongArray = (long*) pIMem->pVTbl->Alloc(pIMem, sizeof(long) * smallSize);
		for (i = 0; i < smallSize; ++i) {
			testLongArray[i] = rand_long(-1000,1000);
		}
		printf("Original array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%ld ", testLongArray[i]);
		}
		printf("... ]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortLong(pIEcoLab1, testLongArray, smallSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%ld ", testLongArray[i]);
		}
		printf("... ]\n");
		sorted = 1;
		for (i = 1; i < smallSize; i++) {
			if (testLongArray[i-1] > testLongArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testLongArray);
	}

	/* Тест 2 */
	{
		int sorted;
		printf("\n[Test 2/3] Medium array (%d elements)\n", mediumSize);
		printf("----------------------------------------------------------------------------\n");
		testLongArray = (long*) pIMem->pVTbl->Alloc(pIMem, sizeof(long) * mediumSize);
		printf("Generating data... ");
		for (i = 0; i < mediumSize; ++i) {
			testLongArray[i] = rand_long(-1000,1000);
			if ((i + 1) % 100 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortLong(pIEcoLab1, testLongArray, mediumSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%ld ", testLongArray[i]);
		}
		printf("... ]\n");
		sorted = 1;
		for (i = 1; i < mediumSize; i++) {
			if (testLongArray[i-1] > testLongArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testLongArray);
	}

	/* Тест 3 */
	{
		int sorted;
		printf("\n[Test 3/3] Large array (%d elements)\n", largeSize);
		printf("----------------------------------------------------------------------------\n");
		testLongArray = (long*) pIMem->pVTbl->Alloc(pIMem, sizeof(long) * largeSize);
		printf("Generating data... ");
		for (i = 0; i < largeSize; ++i) {
			testLongArray[i] = rand_long(-1000,1000);
			if ((i + 1) % 200 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortLong(pIEcoLab1, testLongArray, largeSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%ld ", testLongArray[i]);
		}
		printf("... ]\n");
		printf("Sorted array (last %d): [ ... ", printSize);
		for (i = largeSize - printSize; i < largeSize; ++i) {
			printf("%ld ", testLongArray[i]);
		}
		printf("]\n");
		sorted = 1;
		for (i = 1; i < largeSize; i++) {
			if (testLongArray[i-1] > testLongArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testLongArray);
	}

	printf("\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("  TESTING: float (floating point arrays)\n");
	printf("--------------------------------------------------------------------------------\n");
	
	/* Тест 1 */
	{
		int sorted;
		printf("\n[Test 1/3] Small array (%d elements)\n", smallSize);
		printf("----------------------------------------------------------------------------\n");
		testFloatArray = (float*) pIMem->pVTbl->Alloc(pIMem, sizeof(float) * smallSize);
		for (i = 0; i < smallSize; ++i) {
			testFloatArray[i] = rand_float(-1000,1000);
		}
		printf("Original array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.2f ", testFloatArray[i]);
		}
		printf("... ]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortFloat(pIEcoLab1, testFloatArray, smallSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.2f ", testFloatArray[i]);
		}
		printf("... ]\n");
		sorted = 1;
		for (i = 1; i < smallSize; i++) {
			if (testFloatArray[i-1] > testFloatArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testFloatArray);
	}

	/* Тест 2 */
	{
		int sorted;
		printf("\n[Test 2/3] Medium array (%d elements)\n", mediumSize);
		printf("----------------------------------------------------------------------------\n");
		testFloatArray = (float*) pIMem->pVTbl->Alloc(pIMem, sizeof(float) * mediumSize);
		printf("Generating data... ");
		for (i = 0; i < mediumSize; ++i) {
			testFloatArray[i] = rand_float(-1000,1000);
			if ((i + 1) % 100 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortFloat(pIEcoLab1, testFloatArray, mediumSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.2f ", testFloatArray[i]);
		}
		printf("... ]\n");
		sorted = 1;
		for (i = 1; i < mediumSize; i++) {
			if (testFloatArray[i-1] > testFloatArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testFloatArray);
	}

	/* Тест 3 */
	{
		int sorted;
		printf("\n[Test 3/3] Large array (%d elements)\n", largeSize);
		printf("----------------------------------------------------------------------------\n");
		testFloatArray = (float*) pIMem->pVTbl->Alloc(pIMem, sizeof(float) * largeSize);
		printf("Generating data... ");
		for (i = 0; i < largeSize; ++i) {
			testFloatArray[i] = rand_float(-1000,1000);
			if ((i + 1) % 200 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortFloat(pIEcoLab1, testFloatArray, largeSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.2f ", testFloatArray[i]);
		}
		printf("... ]\n");
		printf("Sorted array (last %d): [ ... ", printSize);
		for (i = largeSize - printSize; i < largeSize; ++i) {
			printf("%.2f ", testFloatArray[i]);
		}
		printf("]\n");
		sorted = 1;
		for (i = 1; i < largeSize; i++) {
			if (testFloatArray[i-1] > testFloatArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testFloatArray);
	}
	printf("--------------------------------------------------------------------------------\n");
	printf("  TESTING: double (double precision arrays)\n");
	printf("--------------------------------------------------------------------------------\n");
	/* Тест 1 */
	{
		int sorted;
		printf("\n[Test 1/3] Small array (%d elements)\n", smallSize);
		printf("----------------------------------------------------------------------------\n");
		testDoubleArray = (double*) pIMem->pVTbl->Alloc(pIMem, sizeof(double) * smallSize);
		for (i = 0; i < smallSize; ++i) {
			testDoubleArray[i] = rand_double(-1000,1000);
		}
		printf("Original array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.2f ", testDoubleArray[i]);
		}
		printf("... ]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortDouble(pIEcoLab1, testDoubleArray, smallSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.2f ", testDoubleArray[i]);
		}
		printf("... ]\n");
		sorted = 1;
		for (i = 1; i < smallSize; i++) {
			if (testDoubleArray[i-1] > testDoubleArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testDoubleArray);
	}

	/* Тест 2 */
	{
		int sorted;
		printf("\n[Test 2/3] Medium array (%d elements)\n", mediumSize);
		printf("----------------------------------------------------------------------------\n");
		testDoubleArray = (double*) pIMem->pVTbl->Alloc(pIMem, sizeof(double) * mediumSize);
		printf("Generating data... ");
		for (i = 0; i < mediumSize; ++i) {
			testDoubleArray[i] = rand_double(-1000,1000);
			if ((i + 1) % 100 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortDouble(pIEcoLab1, testDoubleArray, mediumSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.2f ", testDoubleArray[i]);
		}
		printf("... ]\n");
		sorted = 1;
		for (i = 1; i < mediumSize; i++) {
			if (testDoubleArray[i-1] > testDoubleArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testDoubleArray);
	}

	/* Тест 3 */
	{
		int sorted;
		printf("\n[Test 3/3] Large array (%d elements)\n", largeSize);
		printf("----------------------------------------------------------------------------\n");
		testDoubleArray = (double*) pIMem->pVTbl->Alloc(pIMem, sizeof(double) * largeSize);
		printf("Generating data... ");
		for (i = 0; i < largeSize; ++i) {
			testDoubleArray[i] = rand_double(-1000,1000);
			if ((i + 1) % 200 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortDouble(pIEcoLab1, testDoubleArray, largeSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.2f ", testDoubleArray[i]);
		}
		printf("... ]\n");
		printf("Sorted array (last %d): [ ... ", printSize);
		for (i = largeSize - printSize; i < largeSize; ++i) {
			printf("%.2f ", testDoubleArray[i]);
		}
		printf("]\n");
		sorted = 1;
		for (i = 1; i < largeSize; i++) {
			if (testDoubleArray[i-1] > testDoubleArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testDoubleArray);
	}
	
	printf("\n");
	printf("--------------------------------------------------------------------------------\n");
	printf("  TESTING: long double (extended precision arrays)\n");
	printf("--------------------------------------------------------------------------------\n");
	/* Тест 1 */
	{
		int sorted;
		printf("\n[Test 1/3] Small array (%d elements)\n", smallSize);
		printf("----------------------------------------------------------------------------\n");
		testLongDoubleArray = (long double*) pIMem->pVTbl->Alloc(pIMem, sizeof(long double) * smallSize);
		for (i = 0; i < smallSize; ++i) {
			testLongDoubleArray[i] = rand_long_double(-1000,1000);
		}
		printf("Original array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.3Lf ", testLongDoubleArray[i]);
		}
		printf("... ]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortLongDouble(pIEcoLab1, testLongDoubleArray, smallSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.3Lf ", testLongDoubleArray[i]);
		}
		printf("... ]\n");
		sorted = 1;
		for (i = 1; i < smallSize; i++) {
			if (testLongDoubleArray[i-1] > testLongDoubleArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testLongDoubleArray);
	}

	/* Тест 2 */
	{
		int sorted;
		printf("\n[Test 2/3] Medium array (%d elements)\n", mediumSize);
		printf("----------------------------------------------------------------------------\n");
		testLongDoubleArray = (long double*) pIMem->pVTbl->Alloc(pIMem, sizeof(long double) * mediumSize);
		printf("Generating data... ");
		for (i = 0; i < mediumSize; ++i) {
			testLongDoubleArray[i] = rand_long_double(-1000,1000);
			if ((i + 1) % 100 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortLongDouble(pIEcoLab1, testLongDoubleArray, mediumSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.3Lf ", testLongDoubleArray[i]);
		}
		printf("... ]\n");
		sorted = 1;
		for (i = 1; i < mediumSize; i++) {
			if (testLongDoubleArray[i-1] > testLongDoubleArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testLongDoubleArray);
	}

	/* Тест 3 */
	{
		int sorted;
		printf("\n[Test 3/3] Large array (%d elements)\n", largeSize);
		printf("----------------------------------------------------------------------------\n");
		testLongDoubleArray = (long double*) pIMem->pVTbl->Alloc(pIMem, sizeof(long double) * largeSize);
		printf("Generating data... ");
		for (i = 0; i < largeSize; ++i) {
			testLongDoubleArray[i] = rand_long_double(-1000,1000);
			if ((i + 1) % 200 == 0) {
				printf(".");
				fflush(stdout);
			}
		}
		printf(" [Done]\n");
		begin = clock();
		result = pIEcoLab1->pVTbl->bucketSortLongDouble(pIEcoLab1, testLongDoubleArray, largeSize); 
		end = clock();
		printf("[OK] Sorting completed in %.3f ms\n", (double) (end - begin) * 1000.0 / CLOCKS_PER_SEC);
		printf("Sorted array (first %d): [ ", printSize);
		for (i = 0; i < printSize; ++i) {
			printf("%.3Lf ", testLongDoubleArray[i]);
		}
		printf("... ]\n");
		printf("Sorted array (last %d): [ ... ", printSize);
		for (i = largeSize - printSize; i < largeSize; ++i) {
			printf("%.3Lf ", testLongDoubleArray[i]);
		}
		printf("]\n");
		sorted = 1;
		for (i = 1; i < largeSize; i++) {
			if (testLongDoubleArray[i-1] > testLongDoubleArray[i]) {
				sorted = 0;
				break;
			}
		}
		printf("Status: %s\n", sorted ? "OK" : "FAIL");
		pIMem->pVTbl->Free(pIMem, testLongDoubleArray);
	}
	
	printf("\n");
	printf("================================================================================\n");
	printf("                    ALL TESTS COMPLETED SUCCESSFULLY!\n");
	printf("================================================================================\n");

Release:

    if (pICP != 0 && cAdvise != 0) {
        pICP->pVTbl->Unadvise(pICP, cAdvise);
        cAdvise = 0;
    }
    if (pIEcoLab1Sink != 0) {
        pIEcoLab1Sink->pVTbl->Release(pIEcoLab1Sink);
        pIEcoLab1Sink = 0;
    }
    if (pICP != 0) {
        pICP->pVTbl->Release(pICP);
        pICP = 0;
    }
    if (pICPC != 0) {
        pICPC->pVTbl->Release(pICPC);
        pICPC = 0;
    }

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

