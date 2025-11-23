# ОТЧЕТ ПО РЕАЛИЗАЦИИ ЗАДАНИЯ №2
## Интеграция компонентов калькулятора через включение и агрегирование

---

## 1. ОБЩАЯ ИНФОРМАЦИЯ

**Название задания:** Интеграция компонентов калькулятора в компонент Eco.Lab1  

**Цель:** Добавить компоненты калькулятора, выполняющие операции сложения, вычитания, умножения и деления, используя приемы включения (composition) и агрегирования (aggregation)  

---

## 2. ПОСТАНОВКА ЗАДАЧИ

### 2.1. Основные требования

Необходимо в ранее созданный компонент Eco.Lab1 добавить компоненты калькулятора, которые выполняют базовые арифметические операции:
- **Сложение** (Addition)
- **Вычитание** (Subtraction)
- **Умножение** (Multiplication)
- **Деление** (Division)

### 2.2. Требования к реализации

1. Использовать приемы программирования:
   - **Включение (Composition)** - объект-компонент является неотъемлемой частью основного объекта
   - **Агрегирование (Aggregation)** - объекты связаны более слабо, жизненные циклы независимы

2. Продемонстрировать свойства интерфейсов:
   - Через любой указатель на интерфейс можно получить указатель на любой другой запрашиваемый интерфейс
   - Использовать метод `QueryInterface` для получения интерфейсов

---


## 3. АРХИТЕКТУРА РЕШЕНИЯ

### 3.1. Компоненты калькулятора

В проекте используются следующие компоненты калькулятора:

- **Eco.CalculatorA** - реализует `IEcoCalculatorX` (сложение, вычитание)
- **Eco.CalculatorB** - реализует `IEcoCalculatorX` (сложение, вычитание)
- **Eco.CalculatorD** - реализует `IEcoCalculatorY` (умножение, деление)
- **Eco.CalculatorE** - реализует `IEcoCalculatorY` (умножение, деление)

### 3.2. Интерфейсы

- **IEcoCalculatorX** - интерфейс для операций сложения и вычитания
  - `Addition(int16_t a, int16_t b)` - сложение
  - `Subtraction(int16_t a, int16_t b)` - вычитание

- **IEcoCalculatorY** - интерфейс для операций умножения и деления
  - `Multiplication(int16_t a, int16_t b)` - умножение
  - `Division(int16_t a, int16_t b)` - деление

### 3.3. Реализация включения и агрегирования

**Включение (Composition):**
- `Eco.CalculatorA` используется через включение
- Создается без `pOuterUnknown`
- Полностью принадлежит компоненту `Eco.Lab1`

**Агрегирование (Aggregation):**
- `Eco.CalculatorB` используется через агрегирование
- Создается с передачей `pOuterUnknown`
- Может существовать независимо от `Eco.Lab1`

**Включение для IEcoCalculatorY:**
- `Eco.CalculatorD` или `Eco.CalculatorE` используются через включение
- Создаются без `pOuterUnknown`

---

## 4. РЕАЛИЗАЦИЯ КОМПОНЕНТА

### 4.1. Структура компонента CEcoLab1

<img width="2912" height="3724" alt="image" src="https://github.com/user-attachments/assets/5093852c-72b2-4089-b947-e0eb9910eb3e" />


### 4.2. Инициализация компонентов калькулятора

**Файл:** `Eco.Lab1/SourceFiles/CEcoLab1.c`

<img width="3496" height="3992" alt="image" src="https://github.com/user-attachments/assets/e5990f1d-dda6-4f4d-b450-a859b6f1f9c6" />


### 4.3. Реализация методов интерфейса IEcoCalculatorX

<img width="3460" height="2824" alt="image" src="https://github.com/user-attachments/assets/c5794fba-4af4-4b3e-aba9-edc3528d7811" />


### 4.4. Реализация методов интерфейса IEcoCalculatorY

<img width="3568" height="2824" alt="image" src="https://github.com/user-attachments/assets/1d51ae2e-0038-450e-9650-71268205a628" />


### 4.5. Реализация QueryInterface

**Ключевая особенность:** Из любого интерфейса можно получить любой другой интерфейс.

<img width="3240" height="7324" alt="image" src="https://github.com/user-attachments/assets/7fcfc797-6f58-4379-9dd9-9bd7e7f421f8" />


---

## 5. РЕАЛИЗАЦИЯ КЛИЕНТА (UnitTest)

### 5.1. Тестирование компонентов калькулятора

**Файл:** `Eco.Lab1/UnitTestFiles/SourceFiles/EcoLab1.c`


<img width="3496" height="3724" alt="image" src="https://github.com/user-attachments/assets/23401894-548b-47dd-bfd1-96ddc4578c69" />




### 6.2. Демонстрация QueryInterface

<img width="3640" height="3724" alt="image" src="https://github.com/user-attachments/assets/dbd55662-320a-43e7-a1e1-f4cb7cd2ccbc" />



---


## 7. ТЕСТИРОВАНИЕ

### 7.1. Тестирование операций калькулятора

<img width="774" height="545" alt="image" src="https://github.com/user-attachments/assets/214adeaa-0c06-4441-8635-3bd86f721e49" />

<img width="750" height="485" alt="image" src="https://github.com/user-attachments/assets/9d3974b0-a2ad-40ae-a416-da272a412d13" />

<img width="350" height="101" alt="image" src="https://github.com/user-attachments/assets/94ae0df9-c13c-4248-8404-f1fa385777ff" />





