## TStarJetPicoMaker

**STAR Collaboration**

**Relativistic Heavy Ion Collider, BNL**

Produces TStarJetPico root files from STAR muDSTs,
Will provide implementation for PicoDSTs as they come
online at BNL. The old StMuJetAnalysisTreeMaker is provided 
for backwards compatibility, testing & comparison, but shouldn't
be used going forward as there are bugs that are fixed in the new
Maker.


These libraries require the root4star framework. Additionally, we use
[StRefMultCorr](https://github.com/GuannanXie/Run14AuAu200GeV_StRefMultCorr.git)
and [eventStructuredAu](https://github.com/kkauder/eventStructuredAu.git).
Versions that are compatible with the Maker are embedded in StRoot 
already. If you want to update, they are kept as submodules 
in external/. You can initialize the submodules via 
```git submodule update --init --recursive```

## Usage

After cloning the repository, you can use  

```
./macros/configure.sh
```

to create some needed directories. Compile the libraries via  

```
./macros/compile.csh
```

You can play around with some of the scripts in sandbox/, where everything is in a
single directory. You must fill a file named test.list with valid muDST 
file paths first to use the scripts provided.

