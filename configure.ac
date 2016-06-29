AC_PREREQ(2.69)
AC_INIT([ProFPA], [1.0])
AM_INIT_AUTOMAKE
AC_PROG_CC



OCAML_EXECUTABLE="ocaml"
FRAMA_C_EXECUTABLE="frama-c"
LATTE_EXECUTABLE="integrate"
INVGEN_EXECUTABLE="invgen"
FRONTEND_EXECUTABLE="frontend"
INTERVAL_ANALYZER_EXECUTABLE="yara"



OCAML=""
FRAMA_C=""
LATTE=""
INVGEN=""
FRONTEND=""
INTERVAL_ANALYZER=""

AC_SUBST(OCAML)
AC_SUBST(FRAMA_C)
AC_SUBST(LATTE)
AC_SUBST(INVGEN)
AC_SUBST(INTERVAL_ANALYZER)



################ OCAML #####################
OCAML_PREREQ="3.12.1"
OCAML_BIN="`pwd`/binary/ocaml"
AC_CHECK_PROG(OCAML_EXE, ocaml, yes, no)
if test "$OCAML_EXE" == "yes"
then
  if test ! "`ocaml -vnum`" \< "$OCAML_PREREQ"
  then
    AC_MSG_NOTICE([ocaml version >= 3.12.1 already exists in the system.])
    OCAML="ocaml"
  else
    OCAML_EXE="no"
  fi
fi
if test "$OCAML_EXE" == "no"
then
  wget -c http://caml.inria.fr/pub/distrib/ocaml-3.12/ocaml-3.12.1.tar.gz
  mkdir -p $OCAML_BIN
  tar -xzf ocaml-3.12.1.tar.gz
  pushd ocaml-3.12.1
  ./configure -prefix $OCAML_BIN
  make --silent world && make --silent install
  popd
  rm -rf ocaml-3.12.1
  OCAML="$OCAML_BIN/bin/$OCAML_EXECUTABLE"
fi
############################################



################ FRAMA-C ####################
FRAMA_C_BIN="`pwd`/binary/framac"
wget -c http://frama-c.com/download/frama-c-Neon-20140301.tar.gz
mkdir -p $FRAMA_C_BIN
tar -xzf frama-c-Neon-20140301.tar.gz
pushd frama-c-Neon-20140301
./configure --prefix=$FRAMA_C_BIN
make --silent && make --silent install
popd
rm -rf frama-c-Neon-20140301
FRAMA_C="$FRAMA_C_BIN/bin/$FRAMA_C_EXECUTABLE"
############################################



################ LATTE ####################
LATTE_BIN="`pwd`/binary/latte"
wget -c https://www.math.ucdavis.edu/~latte/software/packages/latte_current/latte-integrale-1.7.3.tar.gz
mkdir -p $LATTE_BIN
tar -xzf latte-integrale-1.7.3.tar.gz
pushd latte-integrale-1.7.3
./configure --prefix=$LATTE_BIN
make --silent && make --silent install
popd
rm -rf latte-integrale-1.7.3
LATTE="$LATTE_BIN/bin/$LATTE_EXECUTABLE"
############################################



################ INVGEN ####################
INVGEN_BIN="`pwd`/binary/invgen"
mkdir -p $INVGEN_BIN
wget -c http://www.tcs.tifr.res.in/~agupta/invgen/invgen
chmod +x invgen
wget -c http://www.tcs.tifr.res.in/~agupta/invgen/frontend
chmod +x frontend
mv invgen $INVGEN_BIN
mv frontend $INVGEN_BIN
INVGEN="$INVGEN_BIN/$INVGEN_EXECUTABLE"
FRONTEND="$INVGEN_BIN/$FRONTEND_EXECUTABLE"
############################################


################ INTERVAL_ANALYZER ####################
INTERVAL_ANALYZER_BIN="`pwd`/binary/interval"
wget -c https://storage.googleapis.com/dibyendu-profile.appspot.com/yara.tar.gz
mkdir -p $INTERVAL_ANALYZER_BIN
tar -xzf yara.tar.gz
pushd yara
./configure --prefix=$INTERVAL_ANALYZER_BIN
make --silent && make --silent install
popd
rm -rf yara
INTERVAL_ANALYZER="$INTERVAL_ANALYZER_BIN/bin/$INTERVAL_ANALYZER_EXECUTABLE"
#######################################################



AC_OUTPUT([src/Makefile])
rm config.*
