To do:
[ ] Check triggers (500001 vs 500004)
[ ] Use trigSet = 3

# Done with diff ./macros
The only changes where to the trigger set and to use the MonteCarlo studies
So, we can use Nick's online one out of the box

# in StRoot/eventStructuredAu/TStarJetPicoEventHeader.{h,cxx}
 - there are TOFMULT changes; we won't use these, but take these as-written form I. Mooney's version.

# in StRoot/TStarJetPicoMaker/TStarJetPicoMaker.{h,cxx}
 There are many changes to allow the making of MC trees.
 These are taken from I. Mooney's version and edited to allow smoothly *not* taking
 MC trees, as well.

# The submit/jetPicoProduction_example.xml files are quite different
 + I will update these by hand to use STAR's "canonical usage" methods.
 + I anticipate that I will not have to use the python submission script or custom 
   nameing schemes.

# It all compiles, not editing TStarJetPicoMaker for control of MuDst vs MC files.

 
