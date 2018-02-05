!
! (With appropriate modifications to support Russian language -- D.Gayev, sep'2004)
!

! ==============================================================================
! SmartCantGo.h -- lists the exits from a room, more helpful than simply saying
! "You can't go that way".
!
! Version 6.2 (Jul04) by Roger Firth (roger@firthworks.com)
!
! Compatibility: for Inform 6.3 (Z-code and Glulx).
!
! Dependencies: none.
!
! License: The Creative Commons Attribution-ShareAlike License published at
! http://creativecommons.org/licenses/by-sa/2.0/ applies to this software.
! In summary: you must credit the original author(s); if you alter, transform,
! or build upon this software, you may distribute the SOURCE FORM of the
! resulting work only under a license identical to this one. Note that the
! ShareAlike clause does not affect the way in which you distribute the COMPILED
! FORM of works built upon this software.
! Copyright remains with the original author(s), from whom you must seek
! permission if you wish to vary any of the terms of this license.
! The author(s) would also welcome bug reports and enhancement suggestions.
!
! ------------------------------------------------------------------------------
! INSTALLATION
!
! Place this line anywhere after VerbLib.h:
!
!   Constant CANTGO_SHOWROOMS;  ! optional; includes destination room names
!   Constant CANTGO_EXITS;      ! optional; implements EXITS verb
!   Include "SmartCantGo";
!
! ------------------------------------------------------------------------------
! USAGE
!
! You need do nothing more; the following room:
!
!   Object  Crystal_Cave "Crystal Cave"
!     with  description "A passage leads south...",
!           s_to Narrow_Passage,
!           ...;
!
! produces the message "You can go only south" if the player tries to move in
! any of the other directions.
!
! ------------------------------------------------------------------------------
! CUSTOMISATION
!
! You can define CANTGO_SHOWROOMS before Including this extension; the message
! then becomes "You can go only south (to the Narrow passage)".
!
! You can similarly define CANTGO_EXITS to provide a EXITS verb which lists the
! possible exits.
!
! You can change the default values of CANTGO_NOEXITS, CANTGO_PREFIX,
! CANTGO_SUFFIX, CANTGO_TO and CANTGO_THROUGH. Before Including this extension,
! define the appropriate constant as a string, or as a routine which prints one:
!
!   Constant CANTGO_NOEXITS "Looks like there's no way out.";
!
!   [ MyCANTGO_NOEXITS; "Looks like there's no way out."; ];
!   Constant CANTGO_NOEXITS MyCANTGO_NOEXITS;
!
! ------------------------------------------------------------------------------
! NOTES
!
! 1.    If the room is dark and hasn't been visited previously, the message is
!       just "You can't go that way."
!
! 2.    SmartCantGo executes direction and door_to properties which are
!       routines, on the assumption that the routine will silently return
!       something sensible. If your routine generates any output, you should
!       test the keep_silent variable, and display nothing if it's true.
!
! 3.    SmartCantGo ignores direction objects (in the Compass) which have a
!       'concealed' attribute.
!
! 4.    SmartCantGo ignores direction properties which point to 'concealed'
!       doors or which are strings. Therefore this code won't work quite as
!       intended in the following room:
!
!           Object  Library "Library"
!             with  description
!                       "A small wood-panelled library. An open window to the
!                        west affords a stunning view of the Tuscan coastline.",
!                   w_to
!                       "Ouch! You discover that the ~window~ is really
!                        an incredibly lifelike mural painted on the wall.",
!                   ...;
!
! ------------------------------------------------------------------------------
! HISTORY
!
! Version 6.2: (Jul04) EXITS verb, optional display of destination names.
! Version 6.1: (Apr04) More internationalisation (thanks to DG).
! Version 6.0: (Feb04) Reworked for Inform 6.3. Self-initialises.
!              Internationalisation (thanks to SK, FR, HH, GR).
! Version 5.0: (Feb99) Minor corrections.
! Version 4.0: (Nov98) Reworked by Roger Firth for Inform 6.
! Version 3.0: (Nov95) Original by David Wagner. All rights given away.
!
! ==============================================================================

System_file;

#Ifdef LIBRARY_VERBLIB; #Ifndef LIBRARY_GRAMMAR; ! Between VerbLib and Grammar

#Ifndef LIBRARY_VERSION;
Message fatalerror "SMARTCANTGO requires library 6/11 or later";
#Endif;
#Iftrue (LIBRARY_VERSION < 611);
Message fatalerror "SMARTCANTGO requires library 6/11 or later";
#Endif;

#Ifdef SMARTCANTGO_H;
Message warning "SMARTCANTGO already Included";
#Ifnot;
Constant SMARTCANTGO_H 62;
#Ifdef DEBUG; Message "[Including SMARTCANTGO]"; #Endif;

Object  "(SmartCantGo)" LibraryExtensions
  with  ext_initialise [; ChangeDefault(cant_go, SmartCantGo); ];

! ==============================================================================

#Ifdef CANTGO_EXITS;

[ DirsSub; SmartCantGo(); ];

Verb meta 'dirs' 'directions' 'exits' * -> Dirs;

#ifdef LIBRARY_RUSSIAN;
Verb meta 'выходы!' 'пути!'	* -> Dirs;
#endif;

#Endif; ! CANTGO_EXITS

! ------------------------------------------------------------------------------

#Ifdef  LIBRARY_DUTCH;
Default CANTGO_NOEXITS "Er zijn hier geen uitgangen.";
Default CANTGO_PREFIX  "U kunt alleen naar ";
Default CANTGO_TO      "to ";
Default CANTGO_THROUGH "through ";
#Endif;

#Ifdef  LIBRARY_FRENCH;
Default CANTGO_NOEXITS "Il n'ya a pas de sortie.";
Default CANTGO_PREFIX  "Vous pouvez aller seulement vers ";
Default CANTGO_TO      "to ";
Default CANTGO_THROUGH "through ";
#Ifdef CANTGO_EXITS; Verb 'sorties' 'issues' = 'dirs'; #Endif;
#Endif;

#Ifdef  LIBRARY_GERMAN;
Default CANTGO_NOEXITS "Es gibt keinen Ausgang.";
Default CANTGO_PREFIX  "Du kannst nur nach ";
Default CANTGO_SUFFIX  " gehen.";
Default CANTGO_TO      "to ";
Default CANTGO_THROUGH "through ";
#Endif;

#Ifdef  LIBRARY_ITALIAN;
Default CANTGO_NOEXITS "Non ci sono uscite.";
Default CANTGO_PREFIX  "Puoi andare solo a ";
Default CANTGO_TO      "to ";
Default CANTGO_THROUGH "through ";
#Endif;

#Ifdef  LIBRARY_RUSSIAN;    ! Uses Windows Cyrillic CP 1251
Default CANTGO_NOEXITS "Отсюда не заметно ни одного выхода.";
Default CANTGO_PREFIX  "Вы можете идти только ";
#Endif;

#Ifdef  LIBRARY_SPANISH;
Default CANTGO_NOEXITS "No hay ninguna salida.";
Default CANTGO_PREFIX  "S@'olo puedes ir hacia el ";
Default CANTGO_TO      "to ";
Default CANTGO_THROUGH "through ";
#Endif;

#Ifdef  LIBRARY_SWEDISH;
Default CANTGO_NOEXITS "Det finns inga utg@oangar.";
Default CANTGO_PREFIX  "Du kan bara g@oa ";
Default CANTGO_TO      "to ";
Default CANTGO_THROUGH "through ";
#Endif;

Default CANTGO_NOEXITS "There are no exits.";
Default CANTGO_PREFIX  "You can go only ";
Default CANTGO_SUFFIX  ".";
Default CANTGO_TO      "to ";
Default CANTGO_THROUGH "through ";

! ------------------------------------------------------------------------------

[ SmartCantGo room dest dirObj dirCount ks;

    if (location == thedark && real_location hasnt visited) return L__M(##Go, 2);

    ! Find what room the player is in.

    room = location;
    while (parent(room)) room = parent(room);

    ! Count the number of exits.

    dirCount = 0;
    ks = keep_silent; keep_silent = true;
    objectloop (dirObj in compass)
        if (DestIsRoomOrDoor(room.(dirObj.door_dir)) && dirObj hasnt concealed)
            dirCount++;
    if (dirCount == 0) {
        keep_silent = ks;
        return PrintOrRunVar(CANTGO_NOEXITS);
    }

    ! Print the exits.

    PrintOrRunVar(CANTGO_PREFIX, true);
    objectloop (dirObj in compass) {
        dest = DestIsRoomOrDoor(room.(dirObj.door_dir));
        if (dest && dirObj hasnt concealed) {
            LanguageDirection(dirObj.door_dir);
            #Ifdef CANTGO_SHOWROOMS;
            print " (";
#Ifdef  LIBRARY_RUSSIAN;
            if (dest has door) print "через ";
            else               print "в ";
	    print "@<<", (cAcc) dest, "@>>";
#ifnot;
            if (dest has door) PrintOrRunVar(CANTGO_THROUGH, true);
            else               PrintOrRunVar(CANTGO_TO, true);
	    print (the) dest;
#endif;
            print ")";
            #Endif;
            switch (--dirCount) {
              0:       keep_silent = ks;
                       return PrintOrRunVar(CANTGO_SUFFIX);
              1:       print (string) OR__TX;
              default: print (string) COMMA__TX;
            }
        }
    }
];

[ DestIsRoomOrDoor dest;
    while (true) {
        if (dest == false or true || dest ofclass String or Class) rfalse;
        if (dest ofclass Routine) { dest = dest(); continue; }
        if (dest hasnt door) break;
        if (dest has concealed) rfalse;
        if (dest hasnt open) break;
        dest = dest.door_to();
    }
    return dest;
];

! ------------------------------------------------------------------------------

#Endif; ! SMARTCANTGO_H

#Endif; #Endif; ! Between VerbLib and Grammar

! ==============================================================================


