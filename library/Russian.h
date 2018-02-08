! ===========================================================================
!
!   RUSSIAN: Language Definition File for Inform 6
!
!   Copyright (C) Grankin Andrey 2002, Gayev Denis 2003-2004
!                 Vsevolod Zubarev 2010-2018
!
!   Based on:
!	English Release 6/11 Serial number 040227
!
! ---------------------------------------------------------------------------

System_file;

! ---------------------------------------------------------------------------
!   Часть I.   Введение
! ---------------------------------------------------------------------------

Constant LanguageVersion = "@<<Информ@>>: Русская версия Glulx v0.8.3 (alpha), 2018-02-08";

!
! Unluckily, there is no conditional operator in Inform.
! So, we'll use this instead:
!
[ IIF c x y;				! (с)? (x) : (y)

  if (c) return x;
  return y;
];

!
! Компас
!
Class   CompassDirection
  with  number 0,
        description [;
            if (location provides compass_look && location.compass_look(self)) rtrue;
            if (self.compass_look()) rtrue;
            L__M(##Look, 7, self);
        ],
        compass_look false,
  has   scenery male;			! male by default

Object Compass "компас/" has concealed male;

IFNDEF WITHOUT_DIRECTIONS;
CompassDirection -> n_obj "север/"
                    with name 'n//' 'с//' 'север',
		    door_dir n_to;
CompassDirection -> s_obj "юг/"
                    with name 's//' 'ю//' 'юг',
		    door_dir s_to;
CompassDirection -> e_obj "восток/"
                    with name 'e//' 'в//' 'восток',
		    door_dir e_to;
CompassDirection -> w_obj "запад/"
                    with name 'w//' 'з//' 'запад',
		    door_dir w_to;
CompassDirection -> ne_obj "северо-восток/"
                    with name 'ne' 'св' 'северовосток' 'северо-восток',
		    door_dir ne_to;
CompassDirection -> nw_obj "северо-запад/"
                    with name 'nw' 'сз' 'северозапад' 'северо-запад',
		    door_dir nw_to;
CompassDirection -> se_obj "юго-восток/"
                    with name 'se' 'юв' 'юговосток' 'юго-восток',
		    door_dir se_to;
CompassDirection -> sw_obj "юго-запад/"
                    with name 'sw' 'юз' 'югозапад' 'юго-запад',
		    door_dir sw_to;
CompassDirection -> u_obj "верх/"
                    with name 'u//' 'вв' 'верх' 'вверх' 'наверх' 'потолок',
		    door_dir u_to;
CompassDirection -> d_obj "низ/"
                    with name 'd//' 'вн' 'низ' 'вниз' 'пол' 'земля',
		    door_dir d_to;
ENDIF;

CompassDirection -> out_obj "выход/"
                    with name 'выход' 'наружу',
		    door_dir out_to;
CompassDirection -> in_obj "вход/"
                    with name 'вход' 'внутрь',
		    door_dir in_to;

! Языково-специфичная инициализация
[ LanguageInitialise;

  give thedark female ~male ~neuter;		! (т.к. "темнота")

];

! ---------------------------------------------------------------------------
!   Часть II.   Словарь
! ---------------------------------------------------------------------------

Constant AGAIN1__WD   = 'g//';
Constant AGAIN2__WD   = 'опять';
Constant AGAIN3__WD   = 'снова';

Constant OOPS1__WD    = 'o//';
Constant OOPS2__WD    = 'ой';
Constant OOPS3__WD    = 'ох';

Constant UNDO1__WD    = 'u//';
Constant UNDO2__WD    = 'отмена';
Constant UNDO3__WD    = 'откат';

Constant ALL1__WD     = 'все';
Constant ALL2__WD     = 'всю';
Constant ALL3__WD     = 'всех';
Constant ALL4__WD     = 'весь';
Constant ALL5__WD     = 'оба';

Constant AND1__WD     = 'и//';
Constant AND2__WD     = 'и//';
Constant AND3__WD     = 'плюс';

Constant BUT1__WD     = 'кроме';
Constant BUT2__WD     = 'без';
Constant BUT3__WD     = 'минус';

Constant ME1__WD      = 'я//';
Constant ME2__WD      = 'меня';
Constant ME3__WD      = 'мне';
Constant ME4__WD      = 'мной';
Constant ME5__WD      = 'себя';
Constant ME6__WD      = 'себе';
Constant ME7__WD      = 'собой';

Constant OF1__WD      = './/';
Constant OF2__WD      = './/';
Constant OF3__WD      = './/';
Constant OF4__WD      = './/';

Constant OTHER1__WD   = 'другой';	! NB: окончания прилагательных!
Constant OTHER2__WD   = 'иной';
Constant OTHER3__WD   = 'прочий';

Constant THEN1__WD    = 'затем';
Constant THEN2__WD    = 'потом';
Constant THEN3__WD    = 'после';

Constant YES1__WD     = 'y//';
Constant YES2__WD     = 'д//';
Constant YES3__WD     = 'да';

Constant NO1__WD      = 'n//';
Constant NO2__WD      = 'н//';
Constant NO3__WD      = 'нет';

Constant AMUSING__WD  = 'интерес';
Constant FULLSCORE1__WD = 'полн';
Constant FULLSCORE2__WD = 'полнсчет';

Constant QUIT1__WD    = 'q//';
Constant QUIT2__WD    = 'конец';

Constant RESTART__WD  = 'начало';
Constant RESTART2__WD  = 'перезапуск';
Constant RESTORE__WD  = 'загр';
Constant RESTORE2__WD  = 'загрузить';

! Местоимения и дескрипторы

Array LanguagePronouns table

   !  word       possible GNAs                   connected
   !             to follow:                      to:
   !                   i
   !             s  p  s  p
   !             mfnmfnmfnmfn                 

      'его'    $$101000101000                   NULL
      'ему'    $$101000101000                   NULL
      'им'     $$101111101000                   NULL
      'ее'     $$010000010000                   NULL
      'ей'     $$010000010000                   NULL
      'их'     $$000111000111                   NULL
      'ими'    $$000111000111                   NULL

      'него'   $$101000101000                   NULL
      'нем'    $$101000101000                   NULL
      'ним'    $$101000101000                   NULL
      'нее'    $$010000010000                   NULL
      'ней'    $$010000010000                   NULL
      'них'    $$000111000111                   NULL
 ;

Array LanguageDescriptors table

   !  word       possible GNAs   descriptor      connected
   !             to follow:      type:           to:
   !                   i
   !             s  p  s  p
   !             mfnmfnmfnmfn                 

      'мой'    $$100000100000    POSSESS_PK      0
      'мою'    $$010000010000    POSSESS_PK      0
      'мое'    $$001000001000    POSSESS_PK      0
      'мои'    $$000111000111    POSSESS_PK      0

      'моего'  $$100000000000    POSSESS_PK      0
      'моих'   $$000111000000    POSSESS_PK      0

      'этот'   $$100000100000    POSSESS_PK      0
      'эту'    $$010000010000    POSSESS_PK      0
      'это'    $$001000001000    POSSESS_PK      0
      'эти'    $$000111000111    POSSESS_PK      0

      'этого'  $$100000000000    POSSESS_PK      0
      'этих'   $$000111000000    POSSESS_PK      0

      'тот'    $$100000100000    POSSESS_PK      1
      'ту'     $$010000010000    POSSESS_PK      1
      'то'     $$001000001000    POSSESS_PK      1
      'те'     $$000111000111    POSSESS_PK      1

      'того'   $$100000000000    POSSESS_PK      1
      'тех'    $$000111000000    POSSESS_PK      1

      'его'    $$101000101000    POSSESS_PK      'его'
      'ее'     $$010000010000    POSSESS_PK      'ее'
      'их'     $$000111000111    POSSESS_PK      'их'
;

! Числительные
! NB: другие формы (троих, четверых, пятерых)????
Array LanguageNumbers table
	'один'		1
	'одна'		1
	'одно'		1
	'два'		2
	'две'		2
	'три'		3
	'четыре'	4
	'пять'		5
	'шесть'		6
	'семь'		7
	'восемь'	8
	'девять'	9
	'десять'	10
	'одиннадцать'	11
	'двенадцать'	12
	'тринадцать'	13
	'четырнадцать'	14
	'пятнадцать'	15
	'шестнадцать'	16
	'семнадцать'	17
	'восемнадцать'	18
	'девятнадцать'	19
	'двадцать'	20
 ;

! ---------------------------------------------------------------------------
!   Часть III.   Перевод
! ---------------------------------------------------------------------------

[ LanguageToInformese
  i;

  glk_buffer_to_lower_case_uni(buffer, INPUT_BUFFER_LEN, buffer-->0*WORDSIZE);
  for (i=1: i <= buffer-->0: i++) { 
    if (buffer-->i == 'ё') {
      buffer-->i = 'е';
    }
  }
];

! ---------------------------------------------------------------------------
!   Часть IV.   Вывод
! ---------------------------------------------------------------------------

Include "RusMCE";

! "может"/"могут"
[ MorM obj;

  if (obj has pluralname) {
    print "могут";
  } else {
    print "может";
  }
];

Constant LanguageAnimateGender   = male;
Constant LanguageInanimateGender = neuter;

! Артикли.
! Как хорошо, что в русском их нет! :)

Constant LanguageContractionForms = 1;

[ LanguageContraction;
  return 0;
];

Array LanguageArticles -->

!  Cdef	Def	Indef
   ""	""	""
   ""	""	"";

                          !      a           i
                          !      s     p     s     p
                          !      m f n m f n m f n m f n

Array LanguageGNAsToArticles --> 0 0 0 0 0 0 0 0 0 0 0 0;

! Вывести полное описание для компасного направления
! (как наречие!)
[ LanguageDirection d;
   switch (d)
   {   n_to:	print "на север";
       s_to:	print "на юг";
       e_to:	print "на восток";
       w_to:	print "на запад";
       ne_to:	print "на северо-восток";
       nw_to:	print "на северо-запад";
       se_to:	print "на юго-восток";
       sw_to:	print "на юго-запад";
       u_to:	print "вверх";
       d_to:	print "вниз";
       in_to:	print "внутрь";
       out_to:	print "наружу";

       default: return RunTimeError(9,d);
   }
];

! Вывести полное название произвольного числа
[ LanguageNumber n;
  ! (ноль)
  if (n==0)    { print "ноль"; rfalse; }

  ! (отрицательное)
  if (n<0)     { print "минус "; n=-n; }

  if (n>=1000) { print (LanguageNumber) n/1000, " тысяч";
		 NEnd (n/1000, 'а//', 'и//', 0);
  		 n=n%1000; if (n ~= 0) print " "; }

  if (n==0) rfalse;

  switch(n)
  {   1:  print "один";				! NB: одна, одно...
      2:  print "два";				! NB: две...
      3:  print "три";
      4:  print "четыре";
      5:  print "пять";
      6:  print "шесть";
      7:  print "семь";
      8:  print "восемь";
      9:  print "девять";
      10: print "десять";
      11: print "одиннадцать";
      12: print "двенадцать";
      13: print "тринадцать";
      14: print "четырнадцать";
      15: print "пятнадцать";
      16: print "шестнадцать";
      17: print "семнадцать";
      18: print "восемнадцать";
      19: print "девятнадцать";

      20 to 99:
          switch(n/10)
          {  2: print "двадцать";
             3: print "тридцать";
             4: print "сорок";
             5: print "пятьдесят";
             6: print "шестьдесят";
             7: print "семьдесят";
             8: print "восемьдесят";
             9: print "девяносто";
          }
          if (n%10 ~= 0) print " ", (LanguageNumber) n%10;

      100 to 999:
          switch(n/100)
          {  1: print "сто";
             2: print "двести";
             3: print "триста";
             4: print "четыреста";
             5: print "пятьсот";
             6: print "шестьсот";
             7: print "семьсот";
             8: print "восемьсот";
             9: print "девятьсот";
          }
          if (n%100 ~= 0) print " ", (LanguageNumber) n%100;
  }
];

! Окончание числительных (согласованное с 'val')
[ NEnd val eI eII eV;

  switch (val % 100) {
	11 to 19:	if (eV) print (address) eV; return;
  	}

  switch (val % 10) {
	1:		if (eI) print (address) eI;
	2 to 4:		if (eII) print (address) eII;
	default:	if (eV) print (address) eV;
	}

];

! Время дня
[ LanguageTimeOfDay hours mins i;
   i=hours;
   if (i<10) print " ";
   print i, ":", mins/10, mins%10;
];

#ifdef DEBUG;

[ LanguageVerbIsDebugging w;
    return w == 'мета!';
];

#Endif;

[ LanguageVerbLikesAdverb w;
    w = w;
    rfalse;				! NB ???
];

[ LanguageVerbMayBeName w;
    w = w;
    rfalse;				! NB ??????
];

Constant NKEY__TX     = "N = вниз";
Constant PKEY__TX     = "P = вверх";
Constant QKEY1__TX    = "   Q = возврат";
Constant QKEY2__TX    = "Q = возврат";
Constant RKEY__TX     = "ENTER = выбор";

Constant NKEY1__KY    = 'n';
Constant NKEY2__KY    = 'т';
Constant PKEY1__KY    = 'p';
Constant PKEY2__KY    = 'з';
Constant QKEY1__KY    = 'q';
Constant QKEY2__KY    = 'й';

Constant SCORE__TX    = "Счёт: ";
Constant MOVES__TX    = "Ходы: ";
Constant TIME__TX     = "Время: ";
Constant CANTGO__TX   = "Ты не можешь пойти туда.";
Constant YOURSELF__TX = "ты";
Constant YOU__TX      = "Ты";
Constant FORMER__TX   = "ты (ранее)";
Constant DARKNESS__TX = "В темноте";

Constant THOSET__TX   = "эти объекты";
Constant THAT__TX     = "этот объект";
Constant OR__TX       = " или ";
Constant NOTHING__TX  = "ничего";
Constant IS__TX       = " находится";
Constant ARE__TX      = " находятся";
Constant IS2__TX      = "находится ";
Constant ARE2__TX     = "находятся ";
Constant AND__TX      = " и ";
Constant WHOM__TX     = "кто ";
Constant WHICH__TX    = "где ";
Constant COMMA__TX      = ", ";

! Cимвольный идентификатор для грамматической категории
[ ocLabel ocID;
  switch (ocID) {
  	ocSM:	print "Ед.ч./М.р.";
  	ocSF:	print "Ед.ч./Ж.р.";
  	ocSN:	print "Ед.ч./С.р.";
  	ocPL:	print "Мн.ч.";
	};
];

! Cимвольный идентификатор для падежа
[ csLabel csID;
  switch (csID) {
    csNom:	print "И.п.";		! (Именительный Падеж)
    csGen:	print "Р.п.";		! (Родительный Падеж)
    csDat:	print "Д.п.";		! (Дательный Падеж)
    csAcc:	print "В.п.";		! (Винительный Падеж)
    csIns:	print "Т.п.";		! (Творительный Падеж)
    csPre:	print "П.п.";		! (Предложный Падеж)
  };
];

! - Именительный падеж
[ cNom obj; CCase (obj, csNom, false); ];

! - Родительный падеж
[ cGen obj; CCase (obj, csGen, false); ];

! - Дательный падеж
[ cDat obj; CCase (obj, csDat, false); ];

! - Винительный падеж
[ cAcc obj; CCase (obj, csAcc, false); ];

! - Творительный падеж
[ cIns obj; CCase (obj, csIns, false); ];

! - Предложный падеж
[ cPre obj; CCase (obj, csPre, false); ];

! (то же, но с заглавной буквы)
[ CCNom obj;  CCase (obj, csNom, true); ];
[ CCGen obj;  CCase (obj, csGen, true); ];
[ CCDat obj;  CCase (obj, csDat, true); ];
[ CCAcc obj;  CCase (obj, csAcc, true); ];
[ CCIns obj;  CCase (obj, csIns, true); ];
[ CCPre obj;  CCase (obj, csPre, true); ];

! DeclineSub: принудительно склоняет 'noun' по всем падежам
[ DeclineSub
  csID;

  print "Объект @<<";
  CCase (noun, csOff, false);			! (вне падежа)
  print "@>> (";
  style bold; ocLabel (objID (noun)); style roman;
  print "):^^";

  for (csID = csNom: csID <= csPre: ++ csID) {
    style bold; csLabel (csID); style roman;
    print ": ";
    CCase (noun, csID, true);
    print "^";
	}
];

! Вывести текущий счет
[ PScore val;
  print val, " очк";
  NEnd (val, 'о//', 'а//', 'ов');
];

! Вывести текущее количество ходов
[ PTurns val;
  print val, " ход";
  NEnd (val, 0, 'а//', 'ов');
];

[ LanguageLM n x1;

  Prompt:  print "^>";

  Miscellany:
           switch (n)
           {   1: "(ограничиваясь первыми 16 объектами)^";
               2: "Но делать ничего не надо!";
               3: print " Вы проиграли ";
               4: print " Вы выиграли ";
               5: print "^Вы хотите вернуться в НАЧАЛО игры, ЗАГРузить сохранённую игру";
                  #IFDEF DEATH_MENTION_UNDO;
                  print ", сделать ОТКАТ последнего хода, ";
                  #ENDIF;
                  if (TASKS_PROVIDED==0)
                      print ", получить полный СЧЁТ по игре";
                  if (deadflag==2 && AMUSING_PROVIDED==0)
                      print ", получить некоторые ИНТЕРЕСные подсказки";
                  " или закончить (КОНЕЦ) игру?";
               6: "[Интерпретатор не поддерживает отмену хода.]";
               7: "[Отменить ход не удалось.]";
               8: "Нужен один из перечисленных ответов.";
               9: "^Теперь здесь непроглядная тьма!";
              10: "Простите?";
              11: "[Нельзя отменить то, что не сделано!]";
              12: "[Нельзя отменить два хода подряд!]";
              13: "[Предыдущий ход отменён.]";
              14: "Это невозможно исправить.";
              15: "Исправить это нельзя.";
              16: "Команда @<<ой@>> исправляет только одно слово.";
              17: "Кромешная тьма -- не видно ни зги!";
              18: print "ты";
              19: "Ты выглядишь как обычно.";
              20: "Чтобы повторить команду @<<жаба, прыг@>>,
                   введите @<<опять@>> (но не @<<жаба, опять@>>).";
              21: "Это вряд ли можно повторить.";
              22: "Команда не может начинаться с запятой.";
              23: "Непонятно, к кому ты обращаешься.";
              24: "Бессмысленно говорить с ", (cIns) x1, ".";
              25: "Чтобы обратиться к собеседнику,
                   введите @<<собеседник, привет@>>.";
              26: print "(сначала взяв ";
				if(not_holding == player) "себя)";
				print (cAcc) not_holding; ")";
              27: "Эта команда непонятна.";
              28: print "Из команды понятно только: ";
              29: "Это число непонятно.";
              30: "Этого предмета здесь нет.";
              31: "Похоже, надо сказать что-то ещё!";
              32: "Этого предмета у тебя нет.";
              33: "С этим действием не допускается много объектов.";
              34: "Множественные объекты допустимы только один раз.";
              35: "Непонятно, к чему относится @<<", (address) pronoun_word, "@>>.";
              36: "Вы исключили нечто не включённое!";
              37: "Действие применимо только к одушевлённым объектам.";
              38: "Этот глагол непонятен.";
              39: "Упоминать это в игре нет необходимости.";
              40: "В данный момент отсутствует @<<",
                  (address) pronoun_word, "@>> (", (cNom) pronoun_obj, ").";
              41: "Конец команды непонятен.";
              42: if (x1==0) print "Ни одного из них нет";
                  else print "Только ", (number) x1, " из них есть";
                  " в наличии.";
              43: "Действий нет!";
              44: "Нет совсем ничего подходящего.";
              45: print "Что имеется в виду: ";
              46: print "Что имеется в виду: ";
              47: "Но здесь доступен только один предмет. Какой именно?";
              48: print "К кому вы хотите";
                  if (actor~=player) {
                    print ", чтобы ", (cNom) actor, " применил", (VPEnd) actor;
                  } else {
                    print " применить";
                  }
                  print " команду @<<"; PrintCommand(); print "@>>?^";
              49: print "К чему вы хотите";
                  if (actor~=player) {
                    print ", чтобы ", (cNom) actor, " применил", (VPEnd) actor;
                  } else {
                    print " применить";
                  }
                  print " команду @<<"; PrintCommand(); print "@>>?^";
              50: print "Ваш счёт ";
                  if (x1 > 0) print "увеличился";
                  else { x1 = -x1; print "уменьшился"; }
                  print " на ", (PScore) x1;
              51: "(Произошло что-то, что укоротило ваш список команд.)";
              52: "^Введите число от 1 до ", x1,
                  ", 0 для перевывода или нажмите ENTER.";
              53: "^[Нажмите ПРОБЕЛ.]";
              54: "[Комментарий записан.]";
              55: "[Комментарий не записан.]";
              56: print ".^";
              57: print "?^";
           }

  ListMiscellany:
           switch(n)
           {   1: print " (свет", (V2bEnd) x1, ")";
               2: print " (закрыт", (SAEnd) x1, ")";
               3: print " (свет", (V2bEnd) x1, " и закрыт", (SAEnd) x1, ")";
               4: print " (пуст", (SAEnd) x1, ")";
               5: print " (свет", (V2bEnd) x1, " и пуст", (SAEnd) x1, ")";
               6: print " (закрыт", (SAEnd) x1, " и пуст", (SAEnd) x1, ")";
               7: print " (свет", (V2bEnd) x1, ", закрыт", (SAEnd) x1, " и пуст", (SAEnd) x1, ")";
               8: print " (свет", (V2bEnd) x1, " и надет", (SAEnd) x1;
               9: print " (свет", (V2bEnd) x1;
              10: print " (надет", (SAEnd) x1;
              11: print " (";
              12: print "открыт", (SAEnd) x1;
              13: print "открыт", (SAEnd) x1, " и пуст", (SAEnd) x1;
              14: print "закрыт", (SAEnd) x1;
              15: print "закрыт", (SAEnd) x1, " и заперт", (SAEnd) x1;
              16: print " и пуст", (SAEnd) x1;
              17: print " (пуст", (SAEnd) x1, ")";
              18: print " содерж", (V2aEnd) x1, " ";
              19: print " (на ";
              20: print ", над ";
              21: print " (";
              22: print ", внутри ";
           }

  Pronouns: switch(n)
           {   1: print "В данный момент: ";
               2: print "означает ";
               3: print "отсутствует";
               4: "местоимения не определены.";
               5:  ".";
           }

  Order:   print_ret (CCNom) x1, " явно не собира", (V1bEnd) x1, "ся тебя слушать.";

  Quit:    switch (n)
           {   1: print "Ответьте @<<да@>> или @<<нет@>>.";
               2: print "Вы хотите покинуть игру? ";
           }

  Restart: switch(n)
           {   1: print "Вы хотите перезапустить игру? ";
               2: "Перезапустить игру не удалось.";
           }

  Restore: switch(n)
           {   1: "Восстановить игру не удалось.";
               2: "Игра восстановлена.";
           }

  Save:    switch(n)
           {   1: "Сохранить игру не удалось.";
               2: "Игра сохранена.";
           }

  Verify:  switch(n)
           {   1: "Файл игры проверен успешно.";
               2: "Файл игры не прошёл проверку и может быть повреждён.";
           }

  ScriptOn: switch(n)
           {   1: "Режим транскрипта уже включён.";
               2: "Включение транскрипта:";
               3: "Включить транскрипт не удалось.";
           }

  ScriptOff: switch(n)
           {   1: "Режим транскрипта уже выключен.";
               2: "^Выключение транскрипта.";
               3: "Выключить транскрипт не удалось.";
           }

  NotifyOn:     "Извещения о счёте включены.";

  NotifyOff:    "Извещения о счёте выключены.";

  Places:    switch (n) {
        1:  print "Посещённые места: ";
        2:  print ".^";
	}

  Objects: switch(n)
           {   1: "Найденные предметы:^";
               2: "отсутствуют.";
               3: print " (на себе)";
               4: print " (у тебя)";
               5: print " (у кого-то ещё)";
               6: print " (в @<<", (cNom) x1, "@>>)";
               7: print " (в ", (cPre) x1, ")";
               8: print " (внутри ", (cGen) x1, ")";
               9: print " (на ", (cPre) x1, ")";
              10: print " (нигде нет)";
           }

  Score:   switch (n) {
        1:  print (string) IIF (deadflag, "В эту попытку", "К этому моменту"),
                  " вы набрали ", (PScore) score,
                  " (из ", MAX_SCORE, " возможных) за ", (PTurns) turns;
        2:  "В этой игре счёт не предусмотрен.";
    }

  FullScore: switch(n)
           {   1: "Полный счёт состо", (string) IIF (deadflag, "ял", "ит"), " из:^";
               2: "за найденные предметы";
               3: "за посещённые места";
               4: "всего (из ", MAX_SCORE, " возможных)";
           }

  Inv:     switch(n)
           {   1: "У тебя с собой ничего нет.";
               2: print "У тебя с собой есть";
               3:  print ":^";
               4:  print ".^";
           }

  Take:    switch(n)
           {   1: print "Ты берёшь ", (cAcc) noun ; 
                !if (noun has female) print "её";
                !else if (noun has pluralname) print "их";
                !else print "его"; 
				".";
               2: "Ты всегда есть у себя.";
               3: print_ret (CCDat) x1, " это вряд ли понравится.";
               4: "Сначала тебе необходимо покинуть ", (cAcc) x1, ".";
               5: print_ret (CCNom) x1, " у тебя уже есть.";
               6: print_ret (CCNom) noun, " явно принадлеж", (V2aEnd) noun, " ",
               		(cDat) x1, ".";
               7: print_ret (CCNom) noun, " явно явля", (V1bEnd) noun, "ся частью ",
               		(cGen) x1, ".";
               8: print_ret (CCNom) x1, " недосягаем", (SAEnd) x1, ".";
               9: print_ret (CCNom) x1, " закрыт", (SAEnd) x1, ".";
              10: print_ret (CCAcc) x1, " невозможно взять.";
              11: print_ret (CCNom) x1, " жёстко закреплён", (SAEnd) x1, ".";
              12: "У тебя с собой слишком много вещей.";
              13: "(укладывая ", (cAcc) x1, " внутрь ", (cGen) SACK_OBJECT,
                  ", чтобы освободить место)";
           }

  Drop:    switch(n)
           {   1: print_ret "У тебя нет ", (cGen) x1, ".";
               2: print_ret (CCNom) x1, " не у тебя.";
               3: "(сначала сняв ", (cAcc) x1, " с себя)";
               4: print_ret "Брошен", (SAEnd) x1, ".";
           }

  Remove:  switch(n)
           {   1: print_ret (CCNom) x1, " закрыт", (SAEnd) x1, ".";
               2: print_ret (CCNom) x1, " не наход", (V2bEnd) x1, "ся ",
               (string)	IIF (second has supporter, "на ", "в "), (cPre) second, ".";
               3: print_ret (CCNom) x1, (string) IIF (second has supporter, " поднят", " извлечен"), (SAEnd) x1,
               		(string) IIF (second has supporter, " c ", " из "), (cGen) second, ".";
           }

  PutOn:   switch(n)
           {   1: "Сначала тебе нужно взять ", (cAcc) x1, " в руки.";
               2: "Невозможно положить что-либо на себя.";
               3: "Класть что-либо на ", (cAcc) x1, " бессмысленно.";
               4: "У тебя не хватит ловкости.";
               5: "(сначала сняв ", (cAcc) x1, " с себя)^";
               6: "Больше нет места на ", (cPre) x1, ".";
               7: "Ты кладёшь всё на ", (cAcc) second, ".";
               8: "Ты кладёшь ", (cAcc) x1, " на ", (cAcc) second, ".";
           }

  Insert:  switch(n)
           {   1: "Сначала тебе нужно взять ", (cAcc) x1, " в руки.";
               2: print_ret (CCNom) x1, " не ", (MorM) x1, " что-либо содержать.";
               3: print_ret (CCNom) x1, " закрыт", (SAEnd) x1, ".";
               4: "Сперва тебе нужно снять ", (cAcc) x1, " с себя.";
               5: "Невозможно вложить что-либо внутрь себя.";
               6: "(сначала сняв ", (cAcc) x1, " с себя)^";
               7: "Больше нет места в ", (cPre) x1, ".";
               8: "Ты кладёшь всё в ", (cAcc) second, ".";
               9: "Ты кладёшь ", (cAcc) x1, " в ", (cAcc) second, ".";
           }

  EmptyT:  switch(n)
           {   1: print_ret (CCNom) x1, " не ", (MorM) x1, " что-либо содержать.";
               2: print_ret (CCNom) x1, " закрыт", (SAEnd) x1, ".";
               3: print_ret (CCNom) x1, " уже пуст", (SAEnd) x1, ".";
               4: "То есть оставить все как есть?";
           }

  Give:    switch(n)
           {   1: "У тебя нет ", (cGen) x1, " с собой.";
               2: print_ret (CCNom) x1, " и так у тебя есть.";
               3: print_ret (CCAcc) x1, " это не заинтересовало.";
           }

  Show:    switch(n)
           {   1: "У тебя нет ", (cGen) x1, " с собой.";
               2: print_ret (CCAcc) x1, " это не впечатлило.";
           }

  Enter:   switch(n)
           {   1: "Но ты уже ", (string) IIF (x1 has supporter, "на ", "в "),
           	(cPre) x1, ".";
               2: "Но на/в ", (cAcc) x1,
                  " невозможно войти, встать, сесть или лечь.";
               3: print_ret (CCNom) x1, " закрыт", (SAEnd) x1,
               	", и ты не можешь войти туда.";
               4: "Ты не можешь войти в то, что у тебя в руках.";
               5: "Ты ", (string) IIF (x1 has supporter, "влезаешь на ", "залезаешь в "),
               		(cAcc) x1, ".";
               6: "(", (string) IIF (x1 has supporter, "слезая с ",
               	       IIF (x1 has container, "вылезая из ", "выходя из ")),
               		  (cGen) x1, ")^";
               7: "(", (string) IIF (x1 has supporter, "залезая на ",
               	       IIF (x1 has container, "влезая в ", "входя в ")),
               		  (cAcc) x1, ")^";
           }

  GetOff:  "Но ты не находишься ", (string) IIF (x1 has supporter, "на ", "в "), (cPre) x1, ".";

  Exit:    switch(n)
           {   1: "Но ты сейчас не находишься в/на чём-либо.";
               2: print_ret (CCNom) x1, " закрыт", (SAEnd) x1,
                  ", и ты не можешь выйти.";
               3: "Ты ", (string) IIF (x1 has supporter, "слезаешь с ", "выходишь из "),
               		(cGen) x1, ".";
               4:  "Но ты сейчас не ", (string) IIF (x1 has supporter, "на ", "в "),
               		(cPre) x1, ".";
           }

  VagueGo:       "Идти можно только в некотором направлении.";

  Go:      switch(n)
           {   1: "Сперва тебе нужно ",
           	   (string) IIF (x1 has supporter, "встать с ", "выйти из "),
           	   (cGen) x1, ".";
               2: "Этот путь недоступен.";
               3: "Ты не можешь подняться по ", (cDat) x1, ".";
               4: "Ты не можешь спуститься по ", (cDat) x1, ".";
               5: print_ret (CCNom) x1, " меша", (V1bEnd) x1, " тебе пройти.";
               6: print_ret (CCNom) x1, " никуда не вед", (V1aEnd) x1, ".";
           }

  LMode1:         " сейчас в @<<нормальном@>> режиме^
  		   (длинные описания для новых мест, краткие для старых).";

  LMode2:         " сейчас в @<<длинном@>> режиме^(всегда длинные описания мест).";

  LMode3:         " сейчас в @<<кратком@>> режиме^(всегда краткие описания мест).";

  Look:    switch(n)
           {   1: print " (на ", (cPre) x1, ")";
               2: print " (в ", (cPre) x1, ")";
               3: print " (как ";
                  CCase(x1, csNom, false, true);
                  print ")";
               4: print "^На ", (cPre) x1;
                  WriteListFromCase (child(x1),
                      ENGLISH_BIT + RECURSE_BIT + PARTINV_BIT
                      + TERSE_BIT + ISARE_BIT + CONCEAL_BIT, csNom);
                  ".";
               5, 6:
                  if (x1~=location)
                     print (string) IIF (x1 has supporter, "^На ", "^В "), (cPre) x1, " ";
                  else print "^Здесь";
                  if (n==5) print " также";
                  WriteListFromCase (child(x1),
                      ENGLISH_BIT + WORKFLAG_BIT + RECURSE_BIT + ISARE_BIT
                      + PARTINV_BIT + TERSE_BIT + CONCEAL_BIT, csNom);
                  ".";
               7: "В этом направлении не видно ничего примечательного.";
           }

  Examine: switch(n)
           {   1: "ТЕМНОТА (сущ., ж.р.): полное отсутствие света.";
               2: "Ничего особенного в ", (cPre) x1, " ты не видишь.";
               3: print_ret (CCNom) x1, " сейчас ",
               	(string) IIF (x1 has on, "в", "вы"), "ключен", (SAEnd) x1, ".";
           }

  LookUnder: switch(n)
           {   1: "Здесь слишком темно для поисков.";
               2: "Ты не находишь под ", (cIns) noun, " ничего интересного.";
           }

  Search:  switch(n)
           {   1: "Здесь слишком темно для поисков.";
               2: "На ", (cPre) x1, " ничего нет.";
               3: print "На ", (cPre) x1;
                  WriteListFromCase (child(x1),
                      TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT, csNom);
                  ".";
               4: "Ты не находишь в ", (cPre) noun, " ничего интересного.";
               5: print_ret (CCNom) x1, " закрыт", (SAEnd) x1,
               	  ", и ты не можешь заглянуть внутрь.";
               6: "В ", (cPre) x1, " ничего нет.";
               7: print "В ", (cPre) x1;
                  WriteListFromCase (child(x1),
                      TERSE_BIT + ENGLISH_BIT + ISARE_BIT + CONCEAL_BIT, csNom);
                  ".";
           }

  Lock:    switch(n)
           {   1: print_ret (CCAcc) x1, " невозможно запереть.";
               2: print_ret (CCNom) x1, " уже заперт", (SAEnd) x1, ".";
               3: "Сначала необходимо закрыть ", (cAcc) x1, ".";
               4: print_ret (CCNom) x1, " не подход", (V2bEnd) x1, " к замку.";
               5: "Ты запираешь ", (cAcc) x1, ".";
           }

  Unlock:  switch(n)
           {   1: print_ret (CCAcc) x1, " невозможно отпереть.";
               2: print_ret (CCNom) x1, " не заперт", (SAEnd) x1, ".";
               3: print_ret (CCNom) x1, " не подход", (V2bEnd) x1, " к замку.";
               4: "Ты отпираешь ", (cAcc) x1, ".";
           }

  SwitchOn: switch(n)
           {   1: print_ret (CCAcc) x1, " невозможно включить.";
               2: print_ret (CCNom) x1, " уже включён", (SAEnd) x1, ".";
               3: "Ты включаешь ", (cAcc) x1, ".";
           }

  SwitchOff: switch(n)
           {   1: print_ret (CCAcc) x1, " невозможно выключить.";
               2: print_ret (CCNom) x1, " уже выключен", (SAEnd) x1, ".";
               3: "Ты выключаешь ", (cAcc) x1, ".";
           }

  Open:    switch(n)
           {   1: print_ret (CCAcc) x1, " невозможно открыть.";
               2: "Похоже, что ", (cNom) x1, " заперт", (SAEnd) x1, ".";
               3: print_ret (CCNom) x1, " уже открыт", (SAEnd) x1, ".";
               4: print "Ты открываешь ", (cAcc) x1, ". Внутри";
                  if (WriteListFromCase (child(x1),
                      ISARE_BIT+ ENGLISH_BIT + TERSE_BIT + CONCEAL_BIT, csNom) == 0)
                      	"... пустота.";
                  ".";
               5: "Ты открываешь ", (cAcc) x1, ".";
           }

  Close:   switch(n)
           {   1: print_ret (CCAcc) x1, " невозможно закрыть.";
               2: print_ret (CCNom) x1, " уже закрыт", (SAEnd) x1, ".";
               3: "Ты закрываешь ", (cAcc) x1, ".";
           }

  Wear:    switch(n)
           {   1: "Надеть ", (cAcc) x1, " на себя невозможно.";
               2: "У тебя нет ", (cGen) x1, " с собой.";
               3: print_ret (CCNom) x1, " уже на тебе.";
               4: "Ты надеваешь ", (cAcc) x1, " на себя.";
           }

  Disrobe: switch(n)
           {   1: print_ret (CCNom) x1, " не на тебе.";
               2: "Ты снимаешь ", (cAcc) x1, " с себя.";
           }

  Eat:     switch(n)
           {   1: print_ret (CCNom) x1, " явно не год", (V2bEnd) x1, "ся в пищу.";
               2: "Ты съедаешь ", (cAcc) x1, ". Вполне съедобно.";
           }

  Yes, No:        "Вопрос был риторическим.";

  Burn:           print "Поджигать ", (cAcc) x1;
		  if (second ~= 0) print " ", (cIns) second;
		  " бессмысленно.";

  Pray:           "То ли Бога нет, то ли Он не услышал твои молитвы.";

  Wake:           "Поверь, это не сон, а явь.";

  WakeOther:      "Будить ", (cAcc) x1, " не стоит.";

  Kiss:           "Будет лучше сосредоточиться на игре.";

  Think:          "Отличная идея.";

  Smell:          "Никакого необычного запаха нет.";

  Listen:         "Никаких необычных звуков нет.";

  Taste:          "Никакого необычного вкуса нет.";

  Touch:   switch(n)
           {   1: "Не стоит давать волю рукам.";
               2: "Никаких необычных ощущений нет.";
               3: "Если тебе очень хочется.";
           }

  Dig:            print "Копать ", (cAcc) x1;
		  if (second ~= 0) print " ", (cIns) second;
		  " бессмысленно.";

  Cut:            "Резать ", (cAcc) x1, " бессмысленно.";

  Jump:           "Ты глупо подпрыгиваешь на месте.";

  JumpOver:	  "Прыгать через ", (cAcc) x1, " бессмысленно.";

  Tie:  	  print "Привязывать ", (cAcc) x1;
		  if (second ~= 0) print " к ", (cDat) second;
		  " бессмысленно.";

  Drink:          "Выпить ", (cAcc) x1, " невозможно.";

  Fill:           "Наполнять ", (cAcc) x1, " бессмысленно.";

  Sorry:          "О, не нужно извинений.";

  Strong:        "Настоящие квестеры так не выражаются."; 
  Mild:           "Точно.";

  Attack:         "Сила есть -- ума не надо?";

  Swim:           "Для этого здесь недостаточно воды.";

  Swing:          "Качать ", (cAcc) x1, " бессмысленно.";

  Blow:           "Дуть в ", (cAcc) x1, " бессмысленно.";

  Rub:            "Тереть ", (cAcc) x1, " бессмысленно.";

  Set:            "Невозможно установить ", (cAcc) x1, ".";

  SetTo:          "Невозможно установить ", (cAcc) x1, " на что-либо.";

  WaveHands:      "Ты глупо машешь руками.";

  Wave:    switch(n)
           {   1: "Сперва надо взять ", (cAcc) x1, ".";
               2: "Ты глупо машешь ", (cIns) x1, ".";
           }

  Pull, Push, Turn:
           switch(n)
           {   1: print_ret (CCAcc) x1, " трудно сдвинуть с места.";
               2: print_ret (CCAcc) x1, " двигать невозможно.";
               3: "Ничего не произошло.";
               4: print_ret (CCDat) x1, " это вряд ли понравится.";
           }

  PushDir: switch(n)
           {   1: "Передвигать это нет смысла.";
               2: "Двигать можно только в определённом направлении.";
               3: "Двигать в этом направлении невозможно.";
           }

  Squeeze: switch(n)
           {   1: "Не стоит давать волю рукам.";
               2: "Сжимать ", (cAcc) x1, " бессмысленно.";
           }

  ThrowAt: switch(n)
           {   1: "Бросать ", (cAcc) noun, " в ", (cAcc) second, " бесполезно.";
               2: "У тебя не хватает решимости бросить ", (cAcc) noun, " в ", (cAcc) second,
               ".";
           }

  Tell:    switch(n)
           {   1: "Беседы с собой -- занятие нездоровое.";
               2: "Твой собеседник никак не отреагировал.";
           }

  Answer, Ask:    "Ответа не последовало.";

  Buy:            print_ret (CCNom) x1, " не прода", (V1bEnd) x1, "ся.";

  Sing:           "С твоим слухом и голосом этого лучше не делать.";

  Climb:          "Забираться на ", (cAcc) x1, " бессмысленно.";
  
  Wait:           "Проходит немного времени.";

  Sleep:          "Сейчас тебя не клонит ко сну.";

  Consult:        "Ты не находишь в ", (cPre) x1, " ничего подходящего.";

  CommandsOff: switch (n) {
        1: "[Запись команд выключена.]";
        #Ifdef TARGET_GLULX;
        2: "[Запись команд уже выключена.]";
        #Endif; ! TARGET_
    }
  CommandsOn: switch (n) {
        1: "[Запись команд включена.]";
        #Ifdef TARGET_GLULX;
        2: "[Воспроизведение записи.]";
        3: "[Запись команд уже включена.]";
        4: "[Запись команд невозможна!]";
        #Endif; ! TARGET_
    }
  CommandsRead: switch (n) {
        1: "[Воспроизведение записи.]";
        #Ifdef TARGET_GLULX;
        2: "[Воспроизведение уже включено.]";
        3: "[Воспроизведение невозможно. Включена запись.]";
        4: "[Воспроизведение невозможно.]";
        5: "[Возпроизведение закончено.]";
        #Endif; ! TARGET_
    }

];

! ==============================================================================

Constant LIBRARY_RUSSIAN;

! ==============================================================================

