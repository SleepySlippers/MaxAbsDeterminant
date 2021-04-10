Для запуска множества тестов из input.txt нужно раскоментить строчку `#add_definitions(-D_TEST)` в `CmakeLists.txt`. При тестировании в поток ошибок выводиться количество уже обработанных вариантов

Build project:
```
mkdir build && cd build && cmake .. && make && cd ..
```

Синопсис решения: Полный перебор (лучше не особо придумал) с помощью bfs

Асимптотика: `Variants` - количество различных возможных матриц получаемых операцией из начальной. Время: `O(Variants * n ^ 8)`. `Variants <= (ceil(n * n / 2)!) ^ 2`так как данной операцией можно переставлять только числа на чёрных или только на белых полях, при том можно получить любую конфигураци из этих. Детерминант считается за `O(n^3)` с помощю Гаусса в даблах

Из-за асимптотики уже при `n >= 4` будет работать долго.

Формат ввода:

размер матрицы, матрица из целых чисел.

Формат вывода:

Матрица, максимальный модуль детерминанта (возможна погрешность из-за даблов), минимальное количество шагов для его получения 

Пример ввода:
```
3
1 0 0
0 1 0
1 0 0
```

Пример вывода:
```
Matrix:
0 0 1 
0 1 0 
1 0 0 
Max det abs: 1
Min steps: 2
```