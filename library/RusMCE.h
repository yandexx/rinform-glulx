! ===========================================================================
!
!   RusMCE.h:
!   Системный модуль для русской грамматики
!   (генератор падежей, проверка глаголов, пр.)
!   Source encoding: CP1251
!
!   (c) Gayev D.G. 2003
!
! ---------------------------------------------------------------------------

System_file;

Constant Tlimit = 31;     ! (не больше)
Array  Tbuffer --> TLimit;
Array  Tparse --> Tlimit;

! DL: слегка модифицированная версия для DictionaryLookup
! (из "ParserM.h")

[ DL buf len
  i;

  if (len == 0 || len > Tlimit) return 0;

  Tbuffer-->0 = len;
  for (i = 0: i ~= len: i ++) Tbuffer-->(1+i) = buf-->i;
  Tbuffer-->(1+len) = 0;

  VM_Tokenise(Tbuffer, Tparse);
  return Tparse-->1;
];

! DLx:
! как DL, но для поиска элементов словаря на 'term'

[ DLx buf len term
  i;
  if (len == 0 || len >= Tlimit) return 0;

  Tbuffer-->0 = len+1;
  for (i = 0: i ~= len: i ++) Tbuffer-->(1+i) = buf-->i;
  Tbuffer-->(1+len) = term;
  Tbuffer-->(2+len) = 0;

  VM_Tokenise(Tbuffer, Tparse);
  return Tparse-->1;
];

[ CyrCharToUpperUni ch;
  if (ch >= $0430 && ch <=$044F) {
    return ch - 32;
  }
  if (ch == $0451) {
    return $0401; ! Ё
  }
  return ch;
];

Attribute fem_grammar;      ! (тип склонения женского рода)

Property casegen;     ! (необязательный собственный генератор падежей объекта)

! # падежей (нужно парсеру)
Constant LanguageCases = 6;

! Идентификаторы падежей
Constant csOff =  0;  ! Нет (отключить генератор падежей)

Constant csNom =  1;  ! Именительный падеж  (= номинатив)
Constant csGen =  2;  ! Родительный падеж (= генитив)
Constant csDat =  3;  ! Дательный падеж (= датив)
Constant csAcc =  4;  ! Винительный падеж (= аккузатив)
Constant csIns =  5;  ! Творительный падеж  (= инструментал)
Constant csPre =  6;  ! Предложный падеж  (= препозитив)

! Падеж по умолчанию для вывода ShortName
Global csDflt = csNom;

! Категории объекта
Constant ocSM =   1;  ! Единственное число / Мужской род
Constant ocSF =   2;  ! Единственное число / Женский род
Constant ocSN =   3;  ! Единственное число / Средний род
Constant ocPL =   4;  ! Множественное число

! Категория объекта
! определить категорию
[ objID obj;

  if (obj has pluralname)   return ocPL;
  else if (obj has neuter)  return ocSN;
  else if (obj has female)  return ocSF;
  else if (obj has fem_grammar) return ocSF;
  else        return ocSM;
];

! (Режим отладки генератора падежей)
Constant DEBUG_CASES = false;

! Основная таблица падежных суффиксов

Constant ADJ_TOP = 64;

! SM_Req: запрос к таблице падежей (#nreq)
! (ед. число, мужской род)
[ SM_Req csID nreq;

  switch (nreq) {

  ! II склонение, на согласный:
  ! (дом, снег, баран, кнут, мир, парад):
  ! -, -а, -у, -, -ом, -е
  0:  switch (csID) {
  csNom:  return 0;
  csGen:  return 'а//';
  csDat:  return 'у//';
  csAcc:  return 0;
  csIns:  return 'ом';
  csPre:  return 'е//';
  }

  ! II склонение, на -ь:
  ! (снегирь, апрель, пароль, кремень, фонарь, окунь, медведь):
  ! -ь, -я, -ю, -ь, -ем, -е
  1:  switch (csID) {
  csNom:  return 'ь//';
  csGen:  return 'я//';
  csDat:  return 'ю//';
  csAcc:  return 'ь//';
  csIns:  return 'ем';
  csPre:  return 'е//';
  }

  ! II склонение, на -й:
  ! (иней, лакей, зной, май):
  ! -й, -я, -ю, -й, -ем, -е
  2:  switch (csID) {
  csNom:  return 'й//';
  csGen:  return 'я//';
  csDat:  return 'ю//';
  csAcc:  return 'й//';
  csIns:  return 'ем';
  csPre:  return 'е//';
  }

  ! II склонение, на -ий:
  ! (литий, планетарий, крематорий, Евгений, Василий):
  ! -ий, -ия, -ию, -ий, -ием, -ии
  3:  switch (csID) {
  csNom:  return 'ий';
  csGen:  return 'ия';
  csDat:  return 'ию';
  csAcc:  return 'ий';
  csIns:  return 'ием';
  csPre:  return 'ии';
  }

  ! Прилагательные, на -ый:
  ! (красный, белый, сильный, здоровый):
  ! -ый, -ого, -ому, -ый, -ым, -ом
  64:   switch (csID) {
  csNom:  return 'ый';
  csGen:  return 'ого';
  csDat:  return 'ому';
  csAcc:  return 'ый';
  csIns:  return 'ым';
  csPre:  return 'ом';
    }

  ! Прилагательные, на -ой:
  ! (большой, злой, плохой, лихой, нагой):
  ! -ой, -ого, -ому, -ой, -ым, -ом
  65:   switch (csID) {
  csNom:  return 'ой';
  csGen:  return 'ого';
  csDat:  return 'ому';
  csAcc:  return 'ой';
  csIns:  return 'ым';
  csPre:  return 'ом';
  }

  ! Прилагательные, на -ий:
  ! (синий, средний, хороший):
  ! -ий, -его, -ему, -ий, -им, -ем
  66:   switch (csID) {
  csNom:  return 'ий';
  csGen:  return 'его';
  csDat:  return 'ему';
  csAcc:  return 'ий';
  csIns:  return 'им';
  csPre:  return 'ем';
  }

  } ! switch (nreq)

return -1;
];  ! SM_Req

! SF_Req: запрос к таблице падежей (#nreq)
! (ед. число, женский род)
[ SF_Req csID nreq;

  switch (nreq) {

  ! I склонение, на -а:
  ! (вода, стрела, зола, комната):
  ! -а, -ы, -е, -у, -ой, -е
  0:  switch (csID) {
  csNom:  return 'а//';
  csGen:  return 'ы//';
  csDat:  return 'е//';
  csAcc:  return 'у//';
  csIns:  return 'ой';
  csPre:  return 'е//';
  }

  ! I склонение, на -я:
  ! (земля, башня):
  ! -я, -и, -е, -ю, -ей, -е
  1:  switch (csID) {
  csNom:  return 'я//';
  csGen:  return 'и//';
  csDat:  return 'е//';
  csAcc:  return 'ю//';
  csIns:  return 'ей';
  csPre:  return 'е//';
    }

  ! III склонение, на -ь:
  ! (метель, ночь, медь, осень):
  ! -ь, -и, -и, -ь, -ью, -и
  2:  switch (csID) {
  csNom:  return 'ь//';
  csGen:  return 'и//';
  csDat:  return 'и//';
  csAcc:  return 'ь//';
  csIns:  return 'ью';
  csPre:  return 'и//';
    }

  ! I склонение, на -ия:
  ! (сессия, лекция, пародия, агония):
  ! -ия, -ии, -ии, -ию, -ией, -ии
  3:  switch (csID) {
  csNom:  return 'ия';
  csGen:  return 'ии';
  csDat:  return 'ии';
  csAcc:  return 'ию';
  csIns:  return 'ией';
  csPre:  return 'ии';
    }

  ! Прилагательные, на -ая:
  ! (красная, большая, приятная):
  ! -ая, -ой, -ой, -ую, -ой, -ой
  64: switch (csID) {
  csNom:  return 'ая';
  csGen:  return 'ой';
  csDat:  return 'ой';
  csAcc:  return 'ую';
  csIns:  return 'ой';
  csPre:  return 'ой';
    }

  ! Прилагательные, на -яя:
  ! (синяя, средняя):
  ! -яя, -ей, -ей, -юю, -ей, -ей
  65: switch (csID) {
  csNom:  return 'яя';
  csGen:  return 'ей';
  csDat:  return 'ей';
  csAcc:  return 'юю';
  csIns:  return 'ей';
  csPre:  return 'ей';
    }

  } ! switch (nreq)

return -1;
];  ! SF_Req

! SN_Req: запрос к таблице падежей (#nreq)
! (ед. число, средний род)
[ SN_Req csID nreq;

  switch (nreq) {

  ! II склонение, на -о:
  ! (облако, озеро, утро, ведро, зеркало):
  ! -о, -а, -у, -о, -ом, -е
  0:  switch (csID) {
  csNom:  return 'о//';
  csGen:  return 'а//';
  csDat:  return 'у//';
  csAcc:  return 'о//';
  csIns:  return 'ом';
  csPre:  return 'е//';
    }

  ! II склонение, на -е:
  ! (поле, ложе):
  ! -е, -я, -ю, -е, -ем, -е
  1:  switch (csID) {
  csNom:  return 'е//';
  csGen:  return 'я//';
  csDat:  return 'ю//';
  csAcc:  return 'е//';
  csIns:  return 'ем';
  csPre:  return 'е//';
    }

  ! II склонение, на -ие:
  ! (известие, занятие, приветствие, мышление):
  ! -ие, -ия, -ию, -ие, -ием, -ии
  2:  switch (csID) {
  csNom:  return 'ие';
  csGen:  return 'ия';
  csDat:  return 'ию';
  csAcc:  return 'ие';
  csIns:  return 'ием';
  csPre:  return 'ии';
    }

  ! Разносклоняемое, на -я:
  ! (время, племя, имя, знамя):
  ! -я, -ени, -ени, -я, -енем, -ени
  3:  switch (csID) {
  csNom:  return 'я//';
  csGen:  return 'ени';
  csDat:  return 'ени';
  csAcc:  return 'я//';
  csIns:  return 'енем';
  csPre:  return 'ени';
    }

  ! Прилагательные, на -ое:
  ! (красное, малое, мертвое):
  ! -ое, -ого, -ому, -ое, -ым, -ом
  64: switch (csID) {
  csNom:  return 'ое';
  csGen:  return 'ого';
  csDat:  return 'ому';
  csAcc:  return 'ое';
  csIns:  return 'ым';
  csPre:  return 'ом';
    }

  ! Прилагательные, на -ее:
  ! (синее, среднее):
  ! -ее, -его, -ему, -ее, -им, -ем
  65: switch (csID) {
  csNom:  return 'ее';
  csGen:  return 'его';
  csDat:  return 'ему';
  csAcc:  return 'ее';
  csIns:  return 'им';
  csPre:  return 'ем';
    }

  } ! switch (nreq)

return -1;
];  ! SN_Req

! PL_Req: запрос к таблице падежей (#nreq)
! (мн. число)
[ PL_Req csID nreq;

  switch (nreq) {

  ! TMP: нерегулярность Gen Pl

  ! Множественное, на -и:
  ! (овраги, цели, недели):
  ! -и, -ов/-ей/-, -ам/-ям, -и, -ами/-ями, -ах/-ях
  0:  switch (csID) {
  csNom:  return 'и//';
  csGen:  return 'ев';      ! TMP: не всегда! - ей, 
  csDat:  return 'ям';
  csAcc:  return 'и//';
  csIns:  return 'ями';
  csPre:  return 'ях';
    }

  ! Множественное, на -ы:
  ! (работы, солдаты, заботы, закаты):
  ! -ы, -ов/-ей/-, -ам/-ям, -и, -ами/-ями, -ах/-ях
  1:  switch (csID) {
  csNom:  return 'ы//';
  csGen:  return 'ов';      ! TMP: не всегда!
  csDat:  return 'ам';
  csAcc:  return 'ы//';
  csIns:  return 'ами';
  csPre:  return 'ах';
    }

  ! Множественное, на -а:
  ! (облака, дома, номера):
  ! -а, -ов, -ам, -а, -ами, -ах
  2:  switch (csID) {
  csNom:  return 'а//';
  csGen:  return 'ов';
  csDat:  return 'ам';
  csAcc:  return 'а//';
  csIns:  return 'ами';
  csPre:  return 'ах';
    }

  ! Множественное, на -я:
  ! (поля, моря, якоря):
  ! -я, -ей, -ям, -я, -ями, -ях
  3:  switch (csID) {
  csNom:  return 'я//';
  csGen:  return 'ей';
  csDat:  return 'ям';
  csAcc:  return 'я//';
  csIns:  return 'ями';
  csPre:  return 'ях';
    }

  ! Множественное, на -ья:
  ! (листья, деревья, коренья, стулья, перья):
  ! -ья, -ьев, -ьям, -ья, -ьями, -ьях
  4:  switch (csID) {
  csNom:  return 'ья';
  csGen:  return 'ьев';
  csDat:  return 'ьям';
  csAcc:  return 'ья';
  csIns:  return 'ьями';
  csPre:  return 'ьях';
    }

  ! Множественное, на -ия:
  ! (изделия, решения, стремления, понятия):
  ! -ия, -ий, -иям, -ия, -иями, -иях
  5:  switch (csID) {
  csNom:  return 'ия';
  csGen:  return 'ий';
  csDat:  return 'иям';
  csAcc:  return 'ия';
  csIns:  return 'иями';
  csPre:  return 'иях';
    }

  ! Множественное, на -ии:
  ! (станции, реляции, апатии):
  ! -ия, -ий, -иям, -ия, -иями, -иях
  6:  switch (csID) {
  csNom:  return 'ии';
  csGen:  return 'ий';
  csDat:  return 'иям';
  csAcc:  return 'ии';
  csIns:  return 'иями';
  csPre:  return 'иях';
    }

  ! Прилагательные, на -ые:
  ! (красные, опасные, тяжелые):
  ! -ые, -ых, -ым, -ые, -ыми, -ых
  64: switch (csID) {
  csNom:  return 'ые';
  csGen:  return 'ых';
  csDat:  return 'ым';
  csAcc:  return 'ые';
  csIns:  return 'ыми';
  csPre:  return 'ых';
    }

  ! Прилагательные, на -ие:
  ! (синие, легкие, пологие):
  ! -ие, -их, -им, -ие, -ими, -их
  65: switch (csID) {
  csNom:  return 'ие';
  csGen:  return 'их';
  csDat:  return 'им';
  csAcc:  return 'ие';
  csIns:  return 'ими';
  csPre:  return 'их';
  }

  } ! switch (nreq)

return -1;
];  ! PL_Req

! Ending PostProcess (as after 'prch')
[ EndingPost u prch;
  if (u) {
  ! Модификация после 'г'/'к'/'х'/'ж'/'ш'/'ч'/'щ':
  ! сапог -> сапоги, клубок -> клубки, сполох -> сполохи
  if (prch == 'г' or 'к' or 'х' or 'ж' or 'ш' or 'ч' or 'щ')
    switch (u) {
    'ы//':    return 'и//';
    'ый':   return 'ий';
    'ые':   return 'ие';
    'ым':   return 'им';
    'ыми':    return 'ими';
    'ых':   return 'их';
    }

  ! TMP: больше вариантов!

  ! после ц: ов, ом -> ев, ем (если окончание безударное)
  ! после ж, ш: я -> а, ю -> у
  }

  return u;
];

! Ending PreProcess (as after 'prch')
[ EndingPre u prch;
  if (u) {
    if (prch == 'г' or 'к' or 'х' or 'ж' or 'ш' or 'ч' or 'щ')
      switch (u) {
        'и//':    return 'ы//';
        'ий':   return 'ый';
        'ие':   return 'ые';
        'им':   return 'ым';
        'ими':    return 'ыми';
        'их':   return 'ых';
      }
  }

  return u;
  ];

! CCaseEnd:
! перевести падежное окончание (start..end) в соответствующий падеж (csID)
! ocFN - генератор окончаний; disc - дискриминатор; prch - символ перед окончанием
[ CCaseEnd start end csID ocFN disc prch
  i u v;

  v = EndingPre (DL (start, (end-start)/4), prch);

  ! Выполнить поиск по таблицам...
  for (i = 0: : ++ i) {
    u = indirect (ocFN, csNom, i);

    if (u == -1) { 
      if (i >= ADJ_TOP) ! (больше нет вариантов)
        { print "?"; return; }
      else      ! (прилагательные)
       { i = ADJ_TOP - 1; }
    } else if (u == v) {

      if (disc) { -- disc; continue; }

      if (csID ~= csNom) u = EndingPost (indirect (ocFN, csID, i), prch);
      else u = EndingPost (u, prch);

      if (u) print (address) u;
      return;
    }
  }
];

! Специфичная версия для 'LanguageRefers'

[ EndingLookup addr len csID
  v u ocFN i;

  if (csID == 0) rtrue;     !! (любой падеж допустим)

  if (len ~= 0) {
    v = DL (addr, len);
    if (v == 0) rfalse;
  }
  else v = 0;

  ocFN = SM_Req;

  for (::) {
    for (i = 0: : ++ i) {
      u = indirect (ocFN, csID, i);

      if (u == -1) { 
        if (i >= ADJ_TOP) break;  ! (больше нет вариантов)
        else i = ADJ_TOP - 1;   ! (прилагательные)
      }
      else if (u == v) rtrue;
    }

    switch (ocFN) {
      SM_Req: ocFN = SF_Req;
      SF_Req: ocFN = SN_Req;
      SN_Req: ocFN = PL_Req;
      PL_Req: rfalse;     ! (больше нет вариантов)
    }
  }

  rfalse;
];

!
! Проверить корректность глагольного суффикса
!
[ IsVerbSuffix start len;

  ! ("-ся|-сь": убрать)
  if (len >= 2 && start-->(len-2) == 'с' && start-->(len-1) == 'я' or 'ь')
    len = len - 2;

  if (len == 1 && start-->0 == 'и' or 'ь') rtrue;

  ! "[аеиоуыюя]([ийь]|ть)"
  if (start-->0 == 'а' or 'е' or 'и' or 'о' or 'у' or 'ы' or 'ю' or 'я') {
    start = start + 4;
    len--;

    if (len == 1 && start-->0 == 'й') rtrue;
  }

  ! "ти|ть"
  if (len == 2 && start-->0 == 'т' && start-->1 == 'ь' or 'и') rtrue;

  ! "нь|ни|нуть"
  if (start-->0 == 'н' &&
     ((len == 2 && start-->1 == 'и' or 'ь') ||
      (len == 4 && start-->1 == 'у' && start-->2 == 'т' && start-->3 == 'ь')))
    rtrue;

  rfalse;
];

!
! Проверить корректность глагольного префикса
!
[ IsVerbPrefix start len
  w;

  w = DL (start, len);
  if (w == 0) return false;

  return w ==
  'в//' or 'вз' or 'во' or 'вы' or
  'до' or
  'за' or
  'из' or 'ис' or
  'на' or
  'о//' or 'об' or 'обо' or 'от' or 'ото' or
  'по' or 'под' or 'подо' or 'пре' or 'при' or 'про' or 'пере' or
  'раз' or 'рас' or
  'с//' or 'со' or 'съ' or 'у//';
];

!
! Проверить корректность глагола (#wnum)
!
[ LanguageIsVerb buffer parse wnum
  adr beg len end w;

  adr = buffer + (parse-->(wnum*3))*4; 
  len = parse-->(wnum*3-1);

  w = DLx (adr, len, '!');
  if (w) return w;
  
  for (end = len: end > 0: -- end) {
    if (end == len || IsVerbSuffix (adr + end * 4, len - end))
      for (beg = 0: beg < end: ++ beg)
        if (beg == 0 || IsVerbPrefix (adr, beg)) {
          w = DL (adr + beg * 4, end - beg);
          if (w ~= 0 && (w->#dict_par1 & 1) ~= 0)
            return w;       ! (verb entry found)
        }
  }

  return 0;
];

! Расшифровка глаголов (LanguageVerb):
! просмотреть объекты в VerbDepot

[ LanguageVerb word
  obj;

  objectloop (obj in VerbDepot) {
  if (WordInProperty (word, obj, name))
    { print (object) obj; rtrue; }
  }

  rfalse;
];

! Падеж по умолчанию для вывода LanguageRefers
Global csLR = 0;
Global csLRU = 0;

! Обработчик соответствующего символа парсера
[ c_token idtok csID
  retval;

  csLR = csID;
  csLRU = csID; ! последний падеж, который вызывался

  retval = ParseToken (ELEMENTARY_TT, idtok);

  csLR = 0;

  return retval;
];

! LanguageRefers
! Запрос от парсера:
! может ли слово #wnum в данном контексте обращаться к объекту obj?

[ LanguageRefers obj wnum
  adr len end w csID;

  adr = WordAddress(wnum); len = WordLength(wnum);

  ! Для компасных направлений -- упрощенная обработка
  if (parent (obj) == Compass) {
    w = DL (adr, len);
    if (w ~= 0 && WordInProperty (w, obj, name)) rtrue;
    rfalse;
  }

  ! Для мужских одушевленных предметов Acc -> Gen
  csID = csLR;
  if (csID == csAcc && obj has animate && obj has male && obj hasnt fem_grammar)
    csID = csGen;

  for (end = len: end ~= 0: -- end) {
    w = DL (adr, end);
    if (w ~= 0 && WordInProperty (w, obj, name) && EndingLookup (adr + end * 4, len - end, csID))
      rtrue;
  }

  rfalse;
];

Constant ScrLen = 200;
Array Scratch --> ScrLen;

! CCase:
! перевести имя объекта (obj) в соответствующий падеж (csID)

[ CCase obj csID ucase as_obj
  i dlm limit ocFN;

  #iftrue DEBUG_CASES;

  ! (отладочный вывод)
  csLabel (csID);
  print " (", (object) obj, ")";

  #ifnot;
  
  if (as_obj == false && obj == player) {
    if (ucase) {
      switch (csID) {
        csNom: print "Ты";
        csGen: print "Себя";
        csDat: print "Себе";
        csAcc: print "Себя";
        csIns: print "Собой";
        csPre: print "Себе";
      }
    } else {
      switch (csID) {
        csNom: print "ты";
        csGen: print "себя";
        csDat: print "себе";
        csAcc: print "себя";
        csIns: print "собой";
        csPre: print "себе";
      }
    }
    return;
  }

  switch (objID (obj)) {
    ocSM: ocFN = SM_Req;
    ocSF: ocFN = SF_Req;
    ocSN: ocFN = SN_Req;
    ocPL: ocFN = PL_Req;
    default:  return;
  }

  ! Для мужских одушевленных предметов Acc -> Gen
  if (csID == csAcc && obj has animate && 
      obj has male && obj hasnt fem_grammar)
    csID = csGen;

  if (csID ~= 0) {
    Scratch-->0 = VM_PrintToBuffer(Scratch, ScrLen, obj);
    
    if (ucase) {
      Scratch-->1 = CyrCharToUpperUni(Scratch-->1);
    }

    dlm = 0;
    limit = Scratch-->0;
    for (i = 1: i <= limit: ++ i) {
      if (Scratch-->i == '/') {
        if (dlm == 0) { 
          dlm = Scratch + i * 4; 
        } else {  
          CCaseF (obj, ocFN, csID, dlm + 4, Scratch + i * 4);
          dlm = 0;
        }
      } else {  
        if (dlm ~= 0 && Scratch-->i == ' ') {
          CCaseF (obj, ocFN, csID, dlm + 4, Scratch + i * 4);
          dlm = 0;
        }

        if (dlm == 0) print (char) (Scratch-->i);
      }
    }
!
    if (dlm ~= 0) { 
      CCaseF (obj, ocFN, csID, dlm + 4, Scratch + i * 4); 
    }
  } else {
    print (object) obj;
  }

  #endif;
];

[ CCaseF obj ocFN csID beg end disc;

  ! (discriminator present?)
  while (end-->(-1) == '!') { -- end; ++ disc; }

  if (obj provides casegen && obj.casegen (beg, end, csID));
  else CCaseEnd (beg, end, csID, ocFN, disc, beg-->(-2));

];

! Вывод краткого имени объекта (через CCase)
[ LanguagePrintShortName obj
  sn;

  sn = short_name;

  if (obj provides sn && PrintOrRun(obj, sn, 1) ~= 0) rtrue;

  CCase (obj, csDflt, false);

  rtrue;
];

! Вывод списка в падеже csID
[ WriteListFromCase obj flag csID
  rval csSV;

  csSV = csDflt; csDflt = csID;

  rval = WriteListFrom (obj, flag);
  
  csDflt = csSV;
  return rval;
];

! Подходящее местоимение для 'obj'
[ Pronoun obj;
  print (string) (
    IIF (obj == player, "Ты", IIF (obj has pluralname, "Они",
    IIF (obj has female, "Она", IIF (obj has neuter, "Оно", "Он")))));
];

[ PronounS obj;
  print (string) (
    IIF (obj == player, "ты", IIF (obj has pluralname, "они",
    IIF (obj has female, "она", IIF (obj has neuter, "оно", "он")))));
];

! Окончание краткой формы прилагательных/причастий, согласованных с 'obj'
! ("открыт[а|о|ы]", "пуст[а|о|ы]")
[ SAEnd obj;

  switch (objID (obj)) {
    ocSM: ;
    ocSF: print (address) 'а//';
    ocSN: print (address) 'о//';
    ocPL: print (address) 'ы//';
  }
];

! Окончание глаголов, согласованных с 'obj':
! (f1 ? 1-ое : 2-ое) спряжение;
!  f2 ? 'ют'/'ят' : 'ут'/'ат'
[ VEnd obj f1 f2;

  print (address) IIF (obj has pluralname,
    IIF (f1,
      IIF (f2, 'ют', 'ут'),
      IIF (f2, 'ят', 'ат')),
    IIF (f1, 'ет', 'ит'));
];

! Окончание глаголов: '-ет'/'-ут'
[ V1aEnd x; VEnd (x,  true,  false); ];

! Окончание глаголов: '-ет'/'-ют'
[ V1bEnd x; VEnd (x,  true, true); ];

! Окончание глаголов: '-ит'/'-ат'
[ V2aEnd x; VEnd (x, false,  false); ];

! Окончание глаголов: '-ит'/'-ят'
[ V2bEnd x; VEnd (x, false, true); ];

! Окончание глаголов в прошедшем времени
[ VPEnd noun;
  if (noun has pluralname)  {print "и"; rtrue;}
  else if (noun has neuter) {print "о"; rtrue;}
  else if (noun has female) {print "а"; rtrue;}
  else        {print ""; rtrue;}
];

!
! Обработчик беглых гласных
! (возвращает true если обработана)
!
[ ICVowel csID beg end ch0 ch1;

  if ((beg == end && ch0 == 0) || (beg + 4 == end && beg-->0 == ch0)) {
    if (csID == csNom || csID == csAcc) { 
      if (ch0) print (char) ch0;
    }
    else { 
      if (ch1) print (char) ch1;
    }
    rtrue;
  }

  rfalse;
];

[ AEnd noun;
  if (noun has pluralname)  {print "ые"; rtrue;}
  else if (noun has neuter) {print "ое"; rtrue;}
  else if (noun has female) {print "ая"; rtrue;}
  else        {print "ый"; rtrue;}
  ]; 
[ AEnd2 noun;
  if (noun has pluralname)  {print "ие"; rtrue;}
  else if (noun has neuter) {print "ое"; rtrue;}
  else if (noun has female) {print "ая"; rtrue;}
  else        {print "ий"; rtrue;}
  ]; 
[ AEnd3 noun;
  if (noun has pluralname)  {print "ие"; rtrue;}
  else if (noun has neuter) {print "ое"; rtrue;}
  else if (noun has female) {print "ая"; rtrue;}
  else        {print "ой"; rtrue;}
  ]; 
[ PEnding1 n;
  if (n has pluralname) {print "ими"; rtrue;}
  if (n has female) {print "ой"; rtrue;}
  print "им"; rtrue;
];
[ PEnding2 n;
  if (n has pluralname) {print "ыми"; rtrue;}
  if (n has female) {print "ой"; rtrue;}
  print "ым"; rtrue;
];
[ GenIt n;
  if (n has female) {print "её"; rtrue;}
  if (n has pluralname) {print "их"; rtrue;}
  print "его"; rtrue;
];
[ GenIt2 n;
  print "н";
  if (n has female) {print "её"; rtrue;}
  if (n has pluralname) {print "их"; rtrue;}
  print "его"; rtrue;
];
[ DatIt n;
  if (n has female) {print "ей"; rtrue;}
  if (n has pluralname) {print "им"; rtrue;}
  print "ему"; rtrue;
]; 
[ DatIt2 n;
  print "н";
  if (n has female) {print "ей"; rtrue;}
  if (n has pluralname) {print "им"; rtrue;}
  print "ему"; rtrue;
]; 
[ InsIt n;
  if (n has female) {print "ей"; rtrue;}
  if (n has pluralname) {print "ими"; rtrue;}
  print "им"; rtrue;
]; 
[ InsIt2 n;
  print "н";
  if (n has female) {print "ей"; rtrue;}
  if (n has pluralname) {print "ими"; rtrue;}
  print "им"; rtrue;
]; 
