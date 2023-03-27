#!/bin/sh
if [ ! -f regtest.py ]; then
  wget https://github.com/erkyrath/plotex/raw/master/regtest.py
fi
inform +../library,../libext +language_name=Russian -DG -Cu '$DICT_CHAR_SIZE=4' -D _Sources/ambiguity.inf
inform +../library,../libext +language_name=Russian -DG -Cu '$DICT_CHAR_SIZE=4' -D _Sources/basic_meta_verbs.inf
inform +../library,../libext +language_name=Russian -DG -Cu '$DICT_CHAR_SIZE=4' -D _Sources/test.inf
inform +../library,../libext +language_name=Russian -DG -Cu '$DICT_CHAR_SIZE=4' -D _Sources/walking.inf
python3 ./regtest.py _Tests/test.test --vital > test.out
python3 ./regtest.py _Tests/walking.test --vital >> test.out
python3 ./regtest.py _Tests/basic_meta_verbs.test --vital >> test.out
python3 ./regtest.py _Tests/ambiguity.test --vital >> test.out
