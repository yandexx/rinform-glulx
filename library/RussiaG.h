! ----------------------------------------------------------------------------
!
!  RussiaG:  Grammar table entries for the standard verbs library.
!  Russian version
!  Encoding: CP1251
!
!  Supplied for use with Inform 6 Release 6/11
!
!   (C) Grankin Andrey 2002
!   (C) Gayev Denis 2003-2004
!
!  Based on: English grammar Release 6/11 Serial number 040227
!
! ----------------------------------------------------------------------------

System_file;

! ----------------------------------------------------------------------------
!  "Мета-глаголы" (системные глаголы игры)
! ----------------------------------------------------------------------------

Verb meta 'счет!'
                *				-> Score
                * 'полн'			-> FullScore;

Verb meta 'счетполн!'
                *				-> FullScore;

Verb meta 'q!' 'конец!' 'конец'
	  'конч'
                *				-> Quit;

Verb meta 'восст!' 'вос' 'восстан' 'восстанов'
	  'загр!' 'загр' 'загрузить' 'загруж'
	  'restore'
                *				-> Restore;

Verb meta 'провер' 'проверка!'
                *				-> Verify;

Verb meta 'сохр!' 'сохран'
	  'save'
                *				-> Save;

Verb meta 'нач' 'заново'
	  'начало!'
	  'перезапуск!'
	  'перезапуст' 'рестарт'
                *				-> Restart;

Verb meta 'скрипт!' 'транскрипт!' 'отчет!'
                *         -> ScriptOn
                * 'вкл'   -> ScriptOn
                * 'выкл'  -> ScriptOff;

Verb meta 'остотчет!' * -> ScriptOff;

! Запись команд

Verb meta 'запись!'
		* 'вкл'				-> CommandsOn
		* 'выкл'			-> CommandsOff;

Verb meta 'воспр!'
		*				-> CommandsRead;

Verb meta 'опис!'
                * 'норм'/'нормал'		-> LMode1
                * 'дл'/'длин'			-> LMode2
                * 'кр'/'крат'			-> LMode3;

Verb meta 'извещ!'
                * 'вкл'				-> NotifyOn
                * 'выкл'			-> NotifyOff;

Verb meta 'имена!' 'местоимения!'
                *				-> Pronouns;

Verb meta 'версия!'
                *				-> Version;

#IFNDEF NO_PLACES;

Verb meta 'места!'
                *				-> Places;

Verb meta 'предметы!'
                *				-> Objects;

#ENDIF;

! ----------------------------------------------------------------------------
!  Отладочные глаголы и действия
! ----------------------------------------------------------------------------

#ifdef DEBUG;

Verb meta 'мета!'

	! трассировка парсера
	* 'трасс' number			-> TraceLevel
	* 'трасс' 'вкл'				-> TraceOn
	* 'трасс' 'выкл'			-> TraceOff

	! активация действий
	* 'акт' 'вкл'				-> ActionsOn
	* 'акт' 'выкл'				-> ActionsOff

	! вызовы подпрограмм
	* 'вызов' 'вкл'				-> RoutinesOn
	* 'вызов' 'выкл'			-> RoutinesOff

	! выполнение таймеров/демонов
	* 'таймер'/'демон' 'вкл'		-> TimersOn
	* 'таймер'/'демон' 'выкл'		-> TimersOff

	! изменения
	* 'измен' 'вкл'				-> ChangesOn
	* 'измен' 'выкл'			-> ChangesOff

	! выключение случайностей
	* 'неслуч'				-> Predictable

	! телекинез объектов multi
	* 'тк' multi				-> XPurloin

	! абстрагирование noun в noun
	* 'абс' noun 'в' noun			-> XAbstract

	! вывод иерархии объектов
	* 'иерарх'				-> XTree
	* 'иерарх' noun				-> XTree

	! телепортация
	* 'тп' 'в' number			-> Goto
	* 'тп' 'к' noun				-> Gonear

	! вывод области
	* 'обл'					-> Scope
	* 'обл' noun				-> Scope

	! распечатка глагола
	* 'глагол' special			-> Showverb
	
	! распечатка объекта
	* 'объект'				-> Showobj
	* 'объект' multi			-> Showobj

	! падежные формы
	* 'форм' noun				-> Decline
 ;

#Ifdef TARGET_GLULX;
Verb meta 'глкспис'
	*					-> Glklist;
#Endif; ! TARGET_

#ifnot;

[ NoMetaSub;
  "Мета-глаголы доступны только в отладочной версии!";
  ];

Verb meta 'мета'
	*					-> NoMeta;

#endif;

! -----------------------------------------
!  Объект-декодировщик глаголов
! -----------------------------------------

Object VerbDepot;

! -----------------------------------------
!  Специфичные символы парсера
! -----------------------------------------

!! "noun" in nominative
[ cNom_noun;	return c_token (NOUN_TOKEN, csNom);	];

!! "noun" in accusative
[ cAcc_noun;	return c_token (NOUN_TOKEN, csAcc);	];

!! "noun" in genitive
[ cGen_noun;	return c_token (NOUN_TOKEN, csGen);	];

!! "noun" in dative
[ cDat_noun;	return c_token (NOUN_TOKEN, csDat);	];

!! "noun" in instrumental
[ cIns_noun;	return c_token (NOUN_TOKEN, csIns);	];

!! "noun" in prepositive
[ cPre_noun;	return c_token (NOUN_TOKEN, csPre);	];

!! "held" in instrumental
[ cIns_held;	return c_token (HELD_TOKEN, csIns);	];

!! "held" in accusative
[ cAcc_held;	return c_token (HELD_TOKEN, csAcc);	];

!! "held" in genitive
[ cGen_held;	return c_token (HELD_TOKEN, csGen); ];

!! "worn" in accusative
!! (note: there's no 'worn' token)
[ cAcc_worn;	return c_token (HELD_TOKEN, csAcc);	];

!! "creature" in accusative
[ cAcc_creat;	return c_token (CREATURE_TOKEN, csAcc);	];

!! "creature" in genitive
[ cGen_creat;	return c_token (CREATURE_TOKEN, csGen);	];

!! "creature" in dative
[ cDat_creat;	return c_token (CREATURE_TOKEN, csDat);	];

!! "multi" in accusative
[ cAcc_multi;	return c_token (MULTI_TOKEN, csAcc);	];

!! "multiheld" in accusative
[ cAcc_multiheld;	return c_token (MULTIHELD_TOKEN, csAcc);	];

!! "multiexcept" in accusative
[ cAcc_multiexcept;	return c_token (MULTIEXCEPT_TOKEN, csAcc);	];

!! "multiinside" in accusative
[ cAcc_multiinside;	return c_token (MULTIINSIDE_TOKEN, csAcc);	];

! ----------------------------------------------------------------------------
!  И собственно рабочие глаголы
! ----------------------------------------------------------------------------

Verb 'да!' 'да'
                *				-> Yes;

Verb 'нет!' 'нет'
                *				-> No;

Verb 'бля' 'хуй' 'дерьмо' 'сука' 'говно' 'трахн' 'трах'
                *                                -> Strong
                * topic                          -> Strong;
Verb 'черт' 'блин'
                *                                -> Mild
                * topic                          -> Mild; 

!
!	Инвентарь
!

Verb	'и//' 'i!'
	'инв!' 'инвент!' 'инвентарь!'
                *					-> Inv
                * 'высок'/'выс'				-> InvTall
                * 'широк'/'шир'				-> InvWide;

Object "инвентарь" VerbDepot
	with name 'и//' 'i!' 'инв!' 'инвент!';

!
!	Осмотр и поиск
!

! "смотреть"/"глядеть"
Verb	'l!' 'x!'
	'смотр' 'см' 'о//'
	'гл' 'гля' 'гляд'
                *					-> Look
                * 'на' cAcc_noun		-> Examine
				* 'в'/'во' cAcc_noun	-> Search
                * 'внутри' cGen_noun		-> Search
                * 'под' cIns_noun			-> LookUnder
                * 'под' cAcc_noun			-> LookUnder
                * 'о'/'об'/'обо'/'про' topic 'в'/'во' cPre_noun		-> Consult
                * 'в'/'во' cPre_noun 'о'/'об'/'обо'/'про' topic		-> Consult
                * cNom_noun             -> Examine
                * cAcc_noun             -> Examine;

Object "смотреть" VerbDepot
	with name 'l!' 'x!' 'смотр' 'см' 'о//' 'гл' 'гля' 'гляд';

Verb 'изуч' 'исследов'
                * cNom_noun -> Search
                * cAcc_noun -> Search;

Object "изучить" VerbDepot
	with name 'изуч' 'исследов';

! "читать"
Verb	'чит' 'прочесть'
                * 'в'/'во' cPre_noun 'о'/'об'/'обо'/'про' topic		-> Consult
                * 'о'/'об'/'обо'/'про' topic 'в'/'во' cPre_noun		-> Consult
                * cAcc_noun             -> Examine;

Object "читать" VerbDepot
	with name 'чит' 'прочесть';

! "искать"
Verb	'иск' 'ищ'
	'ыск' 'ыщ'
                * 'в'/'во' cPre_noun			-> Search
                * 'в'/'во' cPre_noun 'о'/'об'/'обо'/'про' topic		-> Consult
                * 'о'/'об'/'обо'/'про' topic 'в'/'во' cPre_noun		-> Consult
                * topic 'в'/'во' cPre_noun		-> Consult
                * 'в'/'во' cPre_noun topic		-> Consult
                * cAcc_noun             -> Search;

Object "искать" VerbDepot
	with name 'иск' 'ищ' 'ыск' 'ыщ';

!
!	Передвижение (идти; войти в/выйти из)
!

! Предикат, тестирующий направления
[ ADirection; if (noun in compass) rtrue; rfalse; ];

! "идти"/"бежать"/"ехать"
Verb	'ид'
	'беж' 'бег'
	'ех' 'езж' 'пойти'
                *					-> VagueGo
                * noun=ADirection			-> Go
                * 'в'/'во'/'на' noun=ADirection		-> Go
                * cAcc_noun				-> Enter
                * 'в'/'во'/'на' cAcc_noun		-> Enter
		* 'к' cDat_noun				-> Enter;

Object "идти" VerbDepot
	with name 'ид' 'беж' 'бег' 'ех' 'езж' 'пойти';

! "войти", "зайти"
Verb	'вой' 'войд' 'зай' 'зайд'
                *					-> GoIn
                * 'в'/'во'/'на' cAcc_noun		-> Enter;

Object "войти" VerbDepot
	with name 'вой' 'войд' 'зай' 'зайд';

! "выйти"
Verb	'вый' 'выйд'
	'уй' 'уйд'
		*					-> Exit
        * 'наружу' -> Exit
		* 'из'/'с'/'со' cGen_noun		-> Exit;

Object "выйти" VerbDepot
	with name 'вый' 'выйд' 'уй' 'уйд';

! "встать"
Verb	'вст' 'вста'
                *					-> Exit
                * 'из'/'с'/'со' cGen_noun		-> Exit
                * 'на'/'в'/'во' cAcc_noun		-> Enter;

Object "встать" VerbDepot
	with name 'вст' 'вста';

! "сесть"/"лечь"
Verb	'сесть' 'сяд' 'сад'
	'леч' 'ляг'
                * 'на'/'в'/'во' cAcc_noun		-> Enter;

Object "сесть" VerbDepot
	with name 'сесть' 'сяд' 'сад';

Object "лечь" VerbDepot
	with name 'леч' 'ляг';

!
!	(взять/положить; вынуть/вставить; бросить)
!

! "взять"/"брать"/"вынуть"/"извлечь"/"достать"
Verb	'вз' 'возьм'
	'бр' 'бер'
	'вын'
	'извлеч' 'извлек'
	'дост' 'доста' 'достав'
                * multi                         -> Take
                * cAcc_multi					-> Take
                * cAcc_multiinside 'из'/'с'/'со' cGen_noun  -> Remove
                * multiinside 'из'/'с'/'со' noun  -> Remove
                * 'из'/'с'/'со' cGen_noun cAcc_multiinside  -> Remove reverse;

Object "взять" VerbDepot
	with name 'вз' 'возьм' 'бр' 'бер' 'вын'
	'извлеч' 'извлек' 'дост' 'доста' 'достав';

! "положи"/"клади"/"вставь"/"поместить"/"сунуть"
Verb	'лож'
	'класт' 'клад'
	'став'
	'мест' 'мещ'
	'сов' 'су'
                * cAcc_multiheld			-> Drop
                * cAcc_multiexcept 'в'/'во' cAcc_noun	-> Insert
                * 'в'/'во' cAcc_noun cAcc_multiexcept	-> Insert reverse
                * cAcc_multiexcept 'внутрь' cGen_noun	-> Insert
                * 'внутрь' cGen_noun cAcc_multiexcept	-> Insert reverse
                * cAcc_multiexcept 'на' cAcc_noun	-> PutOn
                * 'на' cAcc_noun cAcc_multiexcept	-> PutOn reverse;

Object "положить" VerbDepot
	with name 'лож' 'класт' 'клад' 'став' 'мест' 'мещ' 'сов' 'су';

! "бросить"/"швырнуть"/"метнуть"/"кинуть"
Verb	'брос'
	'швыр'
	'мет'
	'ки' 'кид'
                * cAcc_multiheld			-> Drop
                * held 'в'/'во'/'на' cAcc_noun		-> ThrowAt
                * 'в'/'во'/'на' cAcc_noun held		-> ThrowAt reverse
                * held cDat_creat			-> ThrowAt
                * cDat_creat held			-> ThrowAt reverse;

Object "бросить" VerbDepot
	with name 'брос' 'швыр' 'мет' 'ки' 'кид';

! "[о]порожнить"/"вылить"/"высыпать"
Verb	'порожн'
	'выл'
	'высып'
                * cAcc_noun				-> Empty
                * cAcc_noun 'в'/'во'/'на' cAcc_noun	-> EmptyT
                * 'в'/'во'/'на' cAcc_noun cAcc_noun	-> EmptyT reverse;

Object "опорожнить" VerbDepot
	with name 'порожн' 'выл' 'высып';

!
!	(надеть/снять)
!

! "надеть"/"одеть"
Verb 'над' 'наде' 'оде'
    * cAcc_held                 -> Wear;

Object "надеть" VerbDepot
    with name 'над' 'наде' 'оде';

! "снять"
Verb 'снять' 'сним'
    * cAcc_worn				-> Disrobe;

Object "снять" VerbDepot
    with name 'снять' 'сним';

!
!	(открыть/закрыть; отпереть/запереть; включить/выключить)
!

! "открыть"
Verb	'откр'
                * cAcc_noun			-> Open
                * cAcc_noun cIns_held		-> Unlock
                * cIns_held cAcc_noun		-> Unlock reverse;

! "закрыть"
Verb	'закр'
                * cAcc_noun			-> Close
                * cAcc_noun cIns_held		-> Lock
                * cIns_held cAcc_noun		-> Lock reverse;

Object "открыть" VerbDepot
	with name 'откр';

Object "закрыть" VerbDepot
	with name 'закр';

! "отпереть"
Verb	'отпер' 'отпир' 'отопр'
                * cAcc_noun cIns_held		-> Unlock
                * cIns_held cAcc_noun		-> Unlock reverse;

! "запереть"
Verb	'запер' 'запир' 'запр'
                * cAcc_noun cIns_held		-> Lock
                * cIns_held cAcc_noun		-> Lock reverse;

Object "отпереть" VerbDepot
	with name 'отпер' 'отпир' 'отопр';

Object "запереть" VerbDepot
	with name 'запер' 'запир' 'запр';

! "включить"
Verb	'включ' 'вкл'
                * cAcc_noun			-> SwitchOn;

! "выключить"
Verb	'выключ' 'выкл'
                * cAcc_noun			-> SwitchOff;

Object "включить" VerbDepot
	with name 'включ' 'вкл';

Object "выключить" VerbDepot
	with name 'выключ' 'выкл';

!
!	Общение с NPC
!	(дать; показать; сказать; спросить; ответить)
!

! "дать"/"предложить"
Verb	'дат'
	'предлаг' 'предлож'
                * cAcc_held cDat_creat		-> Give
                * cDat_creat cAcc_held		-> Give reverse;

Object "предложить" VerbDepot
	with name 'дат' 'предлаг' 'предлож';

! "показать"
Verb 'показ' 'покаж'
                * cAcc_held cDat_creat		-> Show
                * cDat_creat cAcc_held		-> Show reverse;

Object "показать" VerbDepot
	with name 'показ' 'покаж';

! "ответить"
Verb 'ответ' 'отвеч'
			* cDat_creat topic		-> Answer reverse
			* topic 'для' cGen_creat	-> Answer;

Object "ответить" VerbDepot
	with name 'ответ' 'отвеч';

! "[рас]сказать"/"сообщить"
Verb	'сказ' 'скаж'
	'сообщ'
                * cDat_creat 'о'/'об'/'обо'/'про' topic	-> Tell
                * cDat_creat topic		-> AskTo;

Object "сказать" VerbDepot
	with name 'сказ' 'скаж' 'сообщ';

! "[рас]спросить"
Verb	'спрос'
                * cAcc_creat 'о'/'об'/'обо'/'про' topic		-> Ask
                * 'у' cAcc_creat 'о'/'об'/'обо'/'про' topic	-> Ask
                * 'о'/'об'/'обо'/'про' topic 'у' cAcc_creat	-> Ask reverse;

Object "спросить" VerbDepot
	with name 'спрос';

! "[по/вы]просить"
Verb	'прос'
                * topic 'у' cAcc_creat		-> AskFor
                * 'у' cAcc_creat topic		-> AskFor reverse
                * cAcc_creat topic		-> AskTo;

Object "просить" VerbDepot
	with name 'прос';

!
!	Прочие действия
!

! "извиниться"/"простить"
Verb	'извин'
	'прост' 'прощ'
                *				-> Sorry;

Object "извинить" VerbDepot
	with name 'извин' 'прост' 'прощ';

! "[по]махать"
Verb	'мах' 'маш'
                *				-> WaveHands
                * 'рукой'/'руками' -> WaveHands
                * cIns_noun			-> Wave;

Object "махать" VerbDepot
	with name 'мах' 'маш';

! "установить"/"настроить"
Verb	'установ'
	'настро'
                * cAcc_noun			-> Set
                * cAcc_noun 'на' special	-> SetTo
                * 'на' special cAcc_noun	-> SetTo reverse;

Object "настроить" VerbDepot
	with name 'установ' 'настр';

! "[пере]двигать"
Verb	'дви' 'двиг'
		* cAcc_noun				-> Push
                * cAcc_noun 'на'/'в'/'во' cAcc_noun	-> Transfer
                * 'на'/'в'/'во' cAcc_noun cAcc_noun	-> Transfer reverse;

Object "двигать" VerbDepot
	with name 'дви' 'двиг';

! "тянуть"/"тащить"/"волочь"
Verb	'тя' 'тяг'
	'тащ' 
	'волоч' 'волок'
	'дерн' 'дерг'
                * cAcc_noun				-> Pull
                * 'за' cAcc_noun			-> Pull
                * cAcc_noun 'на'/'в'/'во' cAcc_noun	-> Transfer
                * 'на'/'в'/'во' cAcc_noun cAcc_noun	-> Transfer reverse;

Object "тянуть" VerbDepot
	with name 'тя' 'тяг' 'тащ' 'волоч' 'волок' 'дерн' 'дерг';

! "толкать"/"пихать"/"нажать"
Verb	'толк'
	'пих'
	'наж' 'нажм' 'нажим'
                * cAcc_noun				-> Push
				* 'на' cAcc_noun		-> Push
                * cAcc_noun 'на'/'в'/'во' cAcc_noun	-> Transfer
                * 'на'/'в'/'во' cAcc_noun cAcc_noun	-> Transfer reverse;

Object "толкать" VerbDepot
	with name 'толк' 'пих' 'наж' 'нажм' 'нажим';

! "вертеть"/"[по]вернуть"/"вращать"
Verb	'вер' 'верт'
	'вращ'
                * cAcc_noun			-> Turn;

Object "вертеть" VerbDepot
	with name 'вер' 'верт' 'вращ';

! "ударить"/"[у]бить"/"атаковать"/"[с]ломать"/"[раз]рушить"
Verb	'би' 'бе'
	'лом'
	'удар'
	'руш'
	'атак' 'атаков'
                * cAcc_noun			-> Attack;

Object "атаковать" VerbDepot
	with name 'би' 'бе' 'лом' 'удар' 'руш' 'атак' 'атаков';

! "напасть"
Verb	'напас' 'напад'
                * 'на' cAcc_noun		-> Attack;

Object "напасть" VerbDepot
	with name 'напас' 'напад';

! "[о]ж[и]дать"
Verb	'z!'
	'ж!'
	'жд' 'жид'
                *				-> Wait;

Object "ждать" VerbDepot
	with name 'z!' 'ж!' 'жд' 'жид';

! "[съ]есть"/"[со]жрать"/"[с]кушать"
Verb	'есть' 'еш'
	'жр'
	'куш'
                * cAcc_held			-> Eat;

Object "есть" VerbDepot
	with name 'есть' 'еш' 'жр';

! "[вы]пить"
Verb	'пи'
                * cAcc_noun			-> Drink;

Object "пить" VerbDepot
	with name 'пи';

! "спать"/"дремать"
Verb 'спа' 'уснуть' 'усни' 'дрем'
    *                                   -> Sleep;

Object "спать" VerbDepot
    with name 'спа' 'уснуть' 'усни' 'дрем';

! "[раз]будить"
Verb	'буд'
                *				-> Wake
                * cAcc_creat			-> WakeOther;

Object "будить" VerbDepot
	with name 'буд';

Verb 'просн'
	*    -> Wake;

Object "проснуться" VerbDepot
	with name 'просн';

! "петь"
Verb	'пе' 'по'
                *				-> Sing;

Object "петь" VerbDepot
	with name 'пе' 'по';

! "[за]лезть"
Verb	'лез' 'лаз'
				* -> Exit
                * 'на' cAcc_noun	-> Climb
                * 'по' cDat_noun    -> Climb
				* 'в'/'во' cAcc_noun -> Enter
				* 'с'/'со' cGen_noun -> Exit;
				

Object "лезть" VerbDepot
	with name 'лез' 'лаз';

! "[по]куп(и/а)ть"
Verb	'куп'
                * cAcc_noun			-> Buy;

Object "купить" VerbDepot
	with name 'куп';

! "сжать"/"[с/раз]давить"
Verb	'сжа' 'жм' 'жим'
	'дав'
                * cAcc_noun			-> Squeeze;

Object "сжать" VerbDepot
	with name 'сжа' 'жм' 'жим' 'дав';

! "плавать"/"нырять"
Verb	'плав' 'плыв' 'пл'
	'ныр'
                *				-> Swim;

Object "плавать" VerbDepot
	with name 'плав' 'плыв'	'ныр' 'пл';

! "качать[ся]"
Verb	'кач'
                * cAcc_noun			-> Swing
                * 'на' cPre_noun		-> Swing;	! "качаться"

Object "качать" VerbDepot
	with name 'кач';

! "дуть"
Verb	'ду'
                * 'в'/'во' cAcc_held		-> Blow
                * cAcc_held			-> Blow;	! "задуть"

Object "дуть" VerbDepot
	with name 'ду';

! "молить[ся]"
Verb	'мол'
                *				-> Pray;

Object "молить" VerbDepot
	with name 'мол';

! "целовать"/"обнимать"
Verb 'целов' 'целуй' 'обнять' 'обним' 
                * cAcc_creat			-> Kiss;

Object "целовать" VerbDepot
    with name 'целов' 'целуй' 'обнять' 'обним';

! "[за]думать[ся]"/"мыслить"
Verb	'дум'
	'мысл' 'мышл'
                *				-> Think;

Object "думать" VerbDepot
	with name 'дум'	'мысл' 'мышл';

! "нюхать"/"нюхнуть"
Verb	'нюх'
                *				-> Smell
                * cAcc_noun			-> Smell;

Object "нюхать" VerbDepot
	with name 'нюх';

! "слушать"
Verb	'слух' 'слуш' 'слыш'
                *				-> Listen
                * cAcc_noun			-> Listen
                * 'к' cDat_noun			-> Listen;	! "прислушаться"

Object "слушать" VerbDepot
	with name 'слух' 'слуш' 'слыш';

! "вку[сить/шать]"/"лизать"/"сосать"
Verb	'вкус' 'вкуш'
	'лиз'
	'сос'
                * cAcc_noun			-> Taste;

Object "вкусить" VerbDepot
	with name 'вкус' 'вкуш' 'лиз';

! "трогать"/"тронуть"
Verb	'тро' 'трог'
	'щуп'
                * cAcc_noun			-> Touch
                * 'до' cGen_noun		-> Touch;	! "дотронуться"

Object "трогать" VerbDepot
	with name 'тро' 'трог' 'щуп';

! "коснуть[ся]"/"касать[ся]"
Verb	'кас' 'кос'
                * cGen_noun			-> Touch
                * 'к' cDat_noun			-> Touch;	! "прикоснуться"

Object "коснуться" VerbDepot
	with name 'кас' 'кос';

! "тереть"
Verb	'тер' 'тир' 'тр'
                * cAcc_noun			-> Rub;

Object "тереть" VerbDepot
	with name 'тер' 'тир' 'тр';

! "вязать"
Verb	'вяз' 'вяж'
                * cAcc_noun			-> Tie
                * cAcc_noun 'к' cDat_noun	-> Tie		! "привязать"
                * 'к' cDat_noun cAcc_noun	-> Tie reverse
                * cAcc_noun 'с'/'со' cIns_noun	-> Tie		! "связать"
                * 'с'/'со' cIns_noun cAcc_noun	-> Tie reverse;

Object "вязать" VerbDepot
	with name 'вяз' 'вяж';

! "жечь"/"жги"
Verb	'жеч' 'жг'
                * cAcc_noun			-> Burn
                * cAcc_noun cIns_held		-> Burn
                * cIns_held cAcc_noun		-> Burn reverse;

Object "жечь" VerbDepot
	with name 'жеч' 'жг';

! "наполнить"
Verb	'полн'
                * cAcc_noun			-> Fill;

Object "наполнить" VerbDepot
	with name 'полн';

! "резать"
Verb	'рез' 'реж'
                * cAcc_noun			-> Cut;

Object "резать" VerbDepot
	with name 'рез' 'реж';

! "прыгать"/"скакать"
Verb	'прыг'
	'скак' 'скач' 'скок'
                *				-> Jump
                * 'через' cAcc_noun		-> JumpOver;

Object "прыгать" VerbDepot
	with name 'прыг' 'скак' 'скач' 'скок';

! "копать"/"рыть"
Verb	'коп'
	'ры' 'ро'
                * cAcc_noun			-> Dig
                * cAcc_noun cIns_held		-> Dig
                * cIns_held cAcc_noun		-> Dig reverse;

Object "копать" VerbDepot
	with name 'коп' 'ры' 'ро';

! ----------------------------------------------------------------------------

Global w_sense;

[ c_sense;

  w_sense = NextWord ();

  if (w_sense == 'вкус' or 'слух' or 'нюх' or 'запах' or 'ощупь')
	return GPR_PREPOSITION;

  return GPR_FAIL;
];

[ SenseSub;

  switch (w_sense) {
	'слух':		<<Listen noun>>;
	'вкус':		<<Taste noun>>;
	'нюх', 'запах':	<<Smell noun>>;
	'ощупь':	<<Touch noun>>;
	}

  "Непонятно, как ты хочешь попробовать ", (cAcc) noun, ".";
  ];

! "пробовать"
Verb	'проб' 'пробов'
		* cAcc_noun 'на' c_sense	-> Sense
		* 'на' c_sense cAcc_noun	-> Sense;

Object "пробовать" VerbDepot
	with name 'проб' 'пробов';

! ----------------------------------------------------------------------------
!  В завершение тривиальные рутины (если они не заданы пользователем)
! ----------------------------------------------------------------------------

#Stub AfterLife         0;
#Stub AfterPrompt       0;
#Stub Amusing           0;
#Stub BeforeParsing     0;
#Stub ChooseObjects     2;
#Stub DarkToDark        0;
#Stub DeathMessage      0;
#Stub GamePostRoutine   0;
#Stub GamePreRoutine    0;
#Stub InScope           1;
#Stub LookRoutine       0;
#Stub NewRoom           0;
#Stub ParseNumber       2;
#Stub ParserError       1;
#Stub PrintTaskName     1;
#Stub PrintVerb         1;
#Stub TimePasses        0;
#Stub UnknownVerb       1;

#Ifdef TARGET_GLULX;
#Stub HandleGlkEvent    2;
#Stub IdentifyGlkObject 4;
#Stub InitGlkWindow     1;
#Endif; ! TARGET_GLULX

#Ifndef PrintRank;
! Constant Make__PR;
! #Endif;
! #Ifdef Make__PR;
[ PrintRank; "."; ];
#Endif;

#Ifndef ParseNoun;
! Constant Make__PN;
! #Endif;
! #Ifdef Make__PN;
[ ParseNoun obj; obj = obj; return -1; ];
#Endif;

#Default Story 0;
#Default Headline 0;

#Ifdef INFIX;
#Include "infix";
#Endif;

! ==============================================================================

Constant LIBRARY_RUSSIAG;

! ==============================================================================
