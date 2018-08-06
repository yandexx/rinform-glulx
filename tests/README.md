Чтобы избежать регрессий, каждое новое изменение в коде библиотеки должно тестироваться.

## Запуск тестов

1. Скомпилировать игру **test.inf**, если требуется.
2. Запустить игру **test.ulx**, ввести команду **воспр**, выбрать файл с тестовыми командами, **test-replay.txt**.
3. Игра спросит, куда сохранить транскрипт (лог). Здесь нужно ввести имя для *нового* файла.
4. Дать интерпретатору дойти до конца всех команд и закрыть игру.
5. Сравнить новый транскрипт с «мастером» (**test-transcript-master.txt**).

Тесты можно считать пройдёнными, если:

* ухудшений не замечено,
* новый код верно исправляет поведение, баги.

## Текущее покрытие кода тестами

### Навигация
- [x] Go, VagueGo
- [x] Enter
- [x] Exit

### Игровые глаголы
- [x] Yes, No, Mild, Strong
- [x] Inv
- [x] Look
- [x] LookUnder
- [x] Examine
- [x] Search
- [ ] Consult
- [x] Take
- [x] Remove
- [x] Drop
- [x] Insert
- [x] PutOn
- [x] ThrowAt
- [x] Empty
- [x] Wear
- [x] Disrobe
- [x] Open
- [x] Close
- [x] Unlock
- [x] Lock
- [x] SwitchOn, SwitchOff
- [x] SwitchOn, SwitchOff
- [x] Give, Show, Answer, Tell, Ask, AskTo
- [x] Sorry
- [x] Wave, WaveHands
- [x] Set, SetTo
- [x] Push, Pull, Transfer
- [x] Turn
- [x] Attack
- [x] Wait
- [ ] Eat
- [ ] Drink
- [ ] Sleep
- [ ] Wake, WakeOther
- [ ] Sing
- [ ] Sing
- [ ] Climb
- [ ] Buy
- [ ] Squeeze
- [ ] Swim
- [ ] Swing
- [ ] Blow
- [ ] Pray
- [ ] Kiss
- [ ] Think
- [ ] Smell
- [ ] Listen
- [ ] Taste
- [ ] Touch
- [ ] Rub
- [ ] Tie
- [ ] Burn
- [ ] Fill
- [ ] Cut
- [ ] Jump, JumpOver
- [ ] Dig
- [ ] Sense

### Мета-глаголы

### Прочее
- [ ] Уточнения
- [ ] Падежные склонения
