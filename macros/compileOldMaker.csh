#!/bin/tcsh

# builds all libraries from scratch & test
# loads them into root4star
#
# Currently builds:
# 1) TStarJetPicoEvent structure
# 2) JetPicoMaker


echo "[i] Remove any existing libs"
rm -v libJetPicoMaker.so
rm -v libs/libJetPicoMaker.so
rm -v sandbox/libJetPicoMaker.so

setenv JETPICODIR "${PWD}/StRoot/eventStructuredAu"

echo "[i] Recompile event structure"
cd ${JETPICODIR}
make clean && make
cd - 

setenv CXXFLAGSNEW "-pipe -fPIC -Wall -Woverloaded-virtual -ansi -Wno-long-long -pthread -I${JETPICODIR} -m32"
#LDFLAGS       += -m32

echo "[i] Changing CXXFLAGS to:"${CXXFLAGSNEW}
setenv COMPILEDIR /tmp/picojetcompile${USER}
echo "[i] Running cons for JetPicoMaker in a temp directory "${COMPILEDIR}

rm  -rf ${COMPILEDIR}
mkdir -pv ${COMPILEDIR}/StRoot
cp -rv StRoot/JetPicoMaker ${COMPILEDIR}/StRoot/
cp -rv StRoot/StRefMultCorr ${COMPILEDIR}/StRoot/

cd ${COMPILEDIR}

cons +StRefMultCorr #ly 2015.06.17
cons CXXFLAGS="${CXXFLAGSNEW}" +JetPicoMaker

# places copies of the libraries into the local lib directory
# as well as into sandbox/
cd -
echo "[i] Copying libraries to the local directory"
find ${COMPILEDIR}/.sl*/lib -name "libJetPicoMaker.so" -exec cp -v {} ./libs/ \;
find ${COMPILEDIR}/.sl*/lib -name "libStRefMultCorr.so" -exec cp -v {} ./libs/ \;
find ${COMPILEDIR}/.sl*/lib -name "libJetPicoMaker.so" -exec cp -v {} ./sandbox/ \;
find ${COMPILEDIR}/.sl*/lib -name "libStRefMultCorr.so" -exec cp -v {} ./sandbox/ \;

cp -v ${JETPICODIR}/*.so ./libs/
cp -v ${JETPICODIR}/*.so ./sandbox/

ls *.so -ltr

echo "[i] Run a zero level test"
root4star macros/LoadLibsOldMaker.C -q -b

