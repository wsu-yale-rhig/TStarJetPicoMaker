TStarJetPicoMaker

STAR Collaboration
Relativistic Heavy Ion Collider, BNL

Produces TStarJetPico root files from STAR muDSTs,
Will provide implementation for PicoDSTs as they come
online at BNL. The old StMuJetAnalysisTreeMaker is provided 
for backwards compatibility, testing & comparison, but shouldn't
be used going forward as there are bugs that are fixed in the new
Maker.

Depends on StRefMultCorr and eventStructuredAu libraries
which can be found at 
https://github.com/GuannanXie/Run14AuAu200GeV_StRefMultCorr.git
https://github.com/kkauder/eventStructuredAu.git

versions that are compatible with the Maker are embedded in StRoot
folder already. If you want to update, they are kept as submodules 
in external/. You can initialize the submodules via 
git submodule update --init --recursive

       To Use

before running anything
mkdir libs
mkdir sandbox
mkdir -p scheduler/report
mkdir -p scheduler/list
mkdir -p scheduler/csh
cp -r StRoot sandbox/
cp -r macros/*cxx sandbox/


compile the library via 
csh macros/compile.csh

you can play around with some of the scripts in sandbox/, where everything is in a
single directory. You must fill a file named test.list with valid muDST 
file paths first to use the scripts provided.

