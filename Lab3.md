# ОТЧЕТ ПО РЕАЛИЗАЦИИ КОМПОНЕНТА Eco.Lab1

## 1. ОБЩАЯ ИНФОРМАЦИЯ

**Название компонента:** Eco.Lab2



## 2. ОПИСАНИЕ КОМПОНЕНТА

### 2.1. Основная функциональность

Компонент Eco.Lab1 реализует алгоритм сортировки Bucket Sort для следующих типов данных:
- `int32_t` (32-битные целые числа)
- `long` (длинные целые числа)
- `float` (числа с плавающей точкой одинарной точности)
- `double` (числа с плавающей точкой двойной точности)
- `long double` (числа с плавающей точкой расширенной точности)

### 2.2. Алгоритм Bucket Sort

Алгоритм работает в несколько этапов:

1. **Поиск минимального и максимального значений** в массиве
2. **Создание корзин** (до 100 корзин для оптимизации памяти)
3. **Распределение элементов** по корзинам на основе их значений
4. **Сортировка каждой корзины** с помощью алгоритма сортировки вставками
5. **Объединение отсортированных корзин** обратно в исходный массив

**Временная сложность:** O(n+k) в среднем случае, где n - количество элементов, k - количество корзин

### 2.3. Система событий

Компонент реализует механизм точек подключения (connection points), позволяющий клиентам получать уведомления о процессе сортировки в реальном времени:

- **OnBucketSortDistribute** - вызывается при распределении элемента в корзину
- **OnBucketSortBucketSort** - вызывается при сортировке корзины
- **OnBucketSortCompleted** - вызывается при завершении сортировки


---

## 3. СТРУКТУРА КОМПОНЕНТА

### 3.1. Интерфейсы

Компонент реализует следующие интерфейсы:

- **IEcoLab1** - основной интерфейс, предоставляющий методы сортировки
- **IEcoLab1Events** - интерфейс событий для получения уведомлений
- **IEcoConnectionPointContainer** - управление точками подключения

### 3.2. Структура файлов

```
Eco.Lab1/
├── HeaderFiles/
│   ├── CEcoLab1.h
│   ├── CEcoLab1Factory.h
│   ├── CEcoLab1ConnectionPoint.h
│   ├── CEcoLab1EnumConnectionPoints.h
│   └── CEcoLab1EnumConnections.h
├── SourceFiles/
│   ├── CEcoLab1.c (основная реализация)
│   ├── CEcoLab1Factory.c
│   ├── CEcoLab1ConnectionPoint.c
│   ├── CEcoLab1EnumConnectionPoints.c
│   └── CEcoLab1EnumConnections.c
├── SharedFiles/
│   ├── IEcoLab1.h (определение интерфейса)
│   ├── IEcoLab1Events.h (интерфейс событий)
│   └── IdEcoLab1.h
└── UnitTestFiles/
    ├── SourceFiles/
    │   ├── EcoLab1.c (тестовый клиент)
    │   └── CEcoLab1Sink.c (реализация приемника событий)
    └── HeaderFiles/
        └── CEcoLab1Sink.h
```

---

## 4. РЕАЛИЗАЦИЯ КОМПОНЕНТА

### 4.1. Основная функция сортировки

**Файл:** `Eco.Lab1/SourceFiles/CEcoLab1.c`

Функция `CEcoLab1_bucketSortInt` реализует алгоритм Bucket Sort для типа `int32_t`. Аналогичные функции реализованы для других типов данных.

**Ключевые особенности реализации:**
- Ограничение количества корзин до 100 для оптимизации
- Автоматическое перераспределение памяти при переполнении корзины
- Генерация событий на каждом этапе сортировки

### 4.2. Вспомогательная функция сортировки вставками

Для сортировки отдельных корзин используется алгоритм сортировки вставками, реализованный в функции `insertionSortInt` (и аналогичных для других типов).

### 4.3. Система событий

Механизм событий реализован через:
- `CEcoLab1ConnectionPoint` - точка подключения
- `CEcoLab1_Fire_OnBucketSortDistribute` - генерация события распределения
- `CEcoLab1_Fire_OnBucketSortBucketSort` - генерация события сортировки корзины
- `CEcoLab1_Fire_OnBucketSortCompleted` - генерация события завершения

---

## 5. ИСХОДНЫЙ КОД

### 5.1. Реализация функции Bucket Sort

<img width="3680" height="7952" alt="image" src="https://github.com/user-attachments/assets/7b33a173-9516-4ad3-95be-9795cd1e1d1c" />


### 5.2. Вспомогательная функция сортировки вставками

<img width="2080" height="1472" alt="image" src="https://github.com/user-attachments/assets/2ce0dcee-2bc9-4e61-9de0-da3dcac2deff" />



### 5.3. Обработчик событий 

<img width="3204" height="1652" alt="image" src="https://github.com/user-attachments/assets/ac1f9b82-399b-4f7b-abd8-3b540b5075ce" />

<img width="3680" height="3272" alt="image" src="https://github.com/user-attachments/assets/7a1d5d68-e293-4dba-bd2f-de3fc1725b81" />

<img width="3680" height="3092" alt="image" src="https://github.com/user-attachments/assets/224ff517-f151-4ce7-9c1f-273da9ff2d43" />

<img width="3680" height="3184" alt="image" src="https://github.com/user-attachments/assets/539fe496-6260-468d-82db-6c580a5cdf3e" />




## 6. РЕАЛИЗАЦИЯ КЛИЕНТА (UnitTest)


Тестовый клиент реализован в файле `Eco.Lab1/UnitTestFiles/SourceFiles/EcoLab1.c` и демонстрирует:

1. **Демонстрацию сортировки с обработкой событий** - показывает пошаговую работу алгоритма
3. **Тестирование сортировки для различных типов данных** - проверка корректности работы алгоритма
4. **Тестирование производительности** - измерение времени сортировки для массивов разного размера



## 7. ТЕСТИРОВАНИЕ

### 7.1. Демонстрация сортировки с событиями


<img width="737" height="562" alt="image" src="https://github.com/user-attachments/assets/fcc539b5-1ce6-4f53-a439-2f43abcf0e35" />


**Описание:** Программа демонстрирует пошаговую работу алгоритма Bucket Sort с выводом событий распределения элементов по корзинам и сортировки корзин.

---

<img width="1402" height="500" alt="image" src="https://github.com/user-attachments/assets/692f4fe4-c454-4843-95bf-b16253b88d63" />

<img width="1413" height="572" alt="image" src="https://github.com/user-attachments/assets/e43c9c0c-adca-43ae-8213-68ca5a9fae4c" />

---





