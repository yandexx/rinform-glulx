# Agent Notes

## Project Overview

rinform-glulx is a Russian language library for the Inform 6 interactive fiction compiler, targeting the Glulx virtual machine.

## Build & Test Environment

### Required tools

- **Inform 6 compiler** (`inform`) — compiles `.inf` source to `.ulx` Glulx game files
- **Glulxe interpreter** — runs `.ulx` files. Tests need the **cheapglk** (dumb terminal) build, installed as `dglulxe`. The curses/ncurses build (e.g. brew's default `glulxe`) does NOT work for automated testing.
- **Python 3** — runs `regtest.py` test harness

### Installing dglulxe from source

The cheapglk build of glulxe is not typically available as a package. To build it:

1. `brew install cheapglk` (or build from https://github.com/erkyrath/cheapglk)
2. Clone https://github.com/erkyrath/glulxe
3. Build with: `make CC=gcc CFLAGS="-g -Wall -Wmissing-prototypes -Wno-unused -DOS_UNIX -I<cheapglk-include-dir>" GLKINCLUDEDIR=<cheapglk-include-dir> GLKLIBDIR=<cheapglk-lib-dir> GLKMAKEFILE=Make.cheapglk`
4. Copy the resulting `glulxe` binary to PATH as `dglulxe`

Requires `build-essential` (gcc, make, libc6-dev) on Ubuntu/Debian.

### Compilation flags

Standard compilation command:

```sh
inform +../library,../libext +language_name=Russian -DG -Cu '$DICT_CHAR_SIZE=4' '$DICT_WORD_SIZE=12' -D <source.inf>
```

**Important:** `$DICT_WORD_SIZE=12` is required with Inform 6.44+. Without it, Russian verb entries like `перезапуск!` and `перезапуст` truncate to the same dictionary word, causing a "Two different verb definitions" compile error. The PR #44 `test.sh` does not include this flag — it needs updating.

### Known compiler warning

`RusMCE.h` line 591 produces a harmless "This statement can never be reached" warning on every compilation.

## Test Suite (post PR #44 merge)

Tests use Andrew Plotkin's `regtest.py` framework. Located in `tests/`.

### Test files

| Source | Test | What it covers |
|---|---|---|
| `_Sources/test.inf` | `_Tests/test.test` | Core verbs: inventory, look, take/drop, put in/on, open/close/lock, enter/exit, NPC interaction, sensory verbs, misc actions, profanity, score/undo |
| `_Sources/walking.inf` | `_Tests/walking.test` | All 14 directions × 10 movement verbs, abbreviations, hyphenated/non-hyphenated forms |
| `_Sources/basic_meta_verbs.inf` | `_Tests/basic_meta_verbs.test` | `тест`/`тест2` meta verbs. Quit/restart marked TODO (hard to test with regtest) |
| `_Sources/ambiguity.inf` | `_Tests/ambiguity.test` | Pronoun resolution, disambiguation, NPC commands, gender variants |

### Running tests

```sh
cd tests
python3 ./regtest.py _Tests/test.test --vital
python3 ./regtest.py _Tests/walking.test --vital
python3 ./regtest.py _Tests/basic_meta_verbs.test --vital
python3 ./regtest.py _Tests/ambiguity.test --vital
```

### Known test issues

- `ambiguity.test`: The `дать это` check expects "кофе" but gets "странная статуя" — pronoun "это" resolves to last-manipulated object. Considered acceptable.
- Quit/restart/version commands are not tested (TODO in test files).

## Russian Declension System

The case declension engine lives in `library/RusMCE.h`.

### Key architecture

- **Case constants**: `csNom`, `csGen`, `csDat`, `csAcc`, `csIns`, `csPre` (nominative through prepositional)
- **Declension tables**: `SM_Req` (singular masculine), `SF_Req` (singular feminine), `SN_Req` (singular neuter), `PL_Req` (plural) — each maps (case, declension class) → ending
- **Object category**: `objID()` determines gender/number from `male`/`female`/`neuter`/`pluralname`/`fem_grammar` attributes
- **Name format**: Object short names use `/` delimiters to mark inflectable segments, e.g. `"оловянн/ый солдатик/"` — the parts between `/` pairs are replaced with case endings

### Two code paths for declension

1. **`CCase(obj, csID, ucase)`** (~line 740) — used when **printing** object names in a given case. Called via print rules like `(cAcc)`, `(cGen)`, etc. defined in `Russian.h`.
2. **`LanguageRefers(obj, wnum)`** (~line 700) — used by the **parser** to match player input against objects. Checks if a typed word matches an object in the current grammatical case.

Both paths have an Acc→Gen redirect for animate masculine nouns.

### Custom attributes for declension

- **`fem_grammar`** — forces feminine declension pattern (SF_Req) on a non-female object. Used for masculine nouns that decline like feminine (e.g. "дядя", "мишка"). Does NOT work for regular masculine consonant-stem nouns — produces garbled output.
- **`anim_grammar`** (added for #25) — triggers animate-style Acc→Gen redirect without the `animate` attribute's game logic side effects. Use on masculine objects that should decline as animate but remain takeable/manipulable (e.g. toy animals, figurines, birds).
- **`casegen`** property — optional custom case-ending generator function on individual objects, for irregular declension.

### Relative pronouns in object listings (WHOM__TX / WHICH__TX)

When the library lists room contents, objects with children (supporters with items on them, open containers with items inside) get a parenthetical like "(на которой находится X)" or "(где находятся X и Y)".

This is controlled by `ListMiscellany` messages 19-22 in `Russian.h` and the constants `WHOM__TX`/`WHICH__TX`:

| Msg | Context | Preposition | Case of "который" |
|-----|---------|-------------|-------------------|
| 19 | terse supporter | "на " | prepositional → `WhomTX` |
| 20 | verbose supporter | "на " | prepositional → `WhomTX` |
| 21 | terse container | — | uses "где " (no pronoun) |
| 22 | verbose container | "внутри " | genitive → `WhomTXGen` |

**Key design decision**: `WHOM__TX` and `WHICH__TX` are set to empty strings `""` in `Russian.h`. The relative pronouns are printed directly inside messages 19-22, which have access to the object `x1` for gender agreement. This avoids changes to `verblibm.h` and `English.h`.

**Print rule functions** in `RusMCE.h` for "который" in different cases:

| Function | Case | m/n | f | pl |
|----------|------|-----|---|-----|
| `WhomTX` | prepositional | котором | которой | которых |
| `WhomTXGen` | genitive | которого | которой | которых |
| `WhomTXIns` | instrumental | которым | которой | которыми |

`WhomTXIns` is defined but not currently used (message 20 was changed from "над" to "на", so it uses `WhomTX`). It's available if a future change needs instrumental case.

### Known limitation

Plural animate nouns (`has pluralname animate`) do NOT get Acc→Gen redirect — the check only fires for `has male`. Plural animate accusative (e.g. "видишь солдатов" vs "видишь солдаты") is not handled.

## Modifying the library

### Principle: avoid changes to shared files

`verblibm.h`, `parserm.h`, and `English.h` are shared with the upstream Inform 6 library. Changes to Russian behavior should be confined to `Russian.h` and `RusMCE.h` wherever possible. Techniques:

- Override behavior inside `ListMiscellany` / `LanguageLM` message handlers in `Russian.h` (they receive the object as `x1`)
- Set constants like `WHOM__TX` / `WHICH__TX` to empty strings and handle the logic inside the message handlers instead
- Add print rule functions to `RusMCE.h` (like `SAEnd`, `VEnd`, `WhomTX`) that can be called from `Russian.h`

## Demo Games

- `demos/Heidi.inf` — simple example game ("Хейди"), Russian translation of Roger Firth's Heidi tutorial. The bird object uses `has male anim_grammar` for correct accusative declension while remaining takeable.
