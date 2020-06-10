# Notebook
Проект является реализацией записной книжки, куда записываются данные о людях.
## Инструкция
### Правила ввода
Каждая записть о человеке состоит из семи полей:
* Имя
* Фамилия
* Отчество
* Номер телефона
* Адрес элетронной почты
* Дата рождения
* Город проживания

При вводе даных через консоль или через файл нужно соблюдать следующие правила:
* Информация о каждом человеке начинается с новой строки. Все поля должны быть заполнены.
* Каждое поле может содержать от 1 до 50 символов.
* Каждое поле информации должно быть отделено от другого символом ' '. Иное употребление оного сивола не допускается.
* В случае отсутствия информации, которая должна находиться в поле, должно использовать символ '-'.
* В строках-образцах символ '%' обозначает любой, то есть соответствует любому набору символов.
### Запуск и параметры
Работа с программой осуществляется через командную строку(cmd.exe). Нужно запускать Notebook.exe с параментрами:
* Адресс текствового файла являющегося основной базой хранящихся данных.
* Цифра от 0 до 7 обозначающих действие, которое нужно совершить.

Далее список параметров зависит от выбранного действия:
* 0 - Добавить строку в базу данных.

     Список параметров: строка.
     
* 1 - Добавить строки из текстового файла в базу данных.

     Список параметров: адресс текствового файла.
     
* 2 - Поиск строк по образцу и запись соответствий в текстовый файл.

     Список параметров: строка-образец, адресс текстового файла для записи соответсвий, цифра от 0 до 6 обозначающая по какому полю сортировать в алфавитном порядке выводные данные.
     
* 3 - Поиск строк по образцам из текствого файла и запись соотвествий в текствовый файл.

     Список параметров: адресс текствового файла с образцами, адресс текстового файла для записи соответсвий, цифра от 0 до 6 обозначающая по какому полю(имя, фамилия, и т.д.) сортировать в алфавитном порядке выводные данные.
     
* 4 - Поиск строк по образцу и последующая их замена на соотвествующие им строки.

     Список параметров: строка-образец, строка для замены.
     
* 5 - Поиск строк по образцам из тестового файла и последующая их замена на соотвествующую строку из текствового файла.

     Список параметров: адрес текстового файла с образцами, адрес текстового файла с записанными для замены строками.
     
* 6 - Поиск строк по образцу и последующее их удаление.

     Список параметров: строка-образец.
     
* 7 - Поиск строк по образцам из тестового файла и последующее их удаление.

     Список параметров: адрес текстового файла.
