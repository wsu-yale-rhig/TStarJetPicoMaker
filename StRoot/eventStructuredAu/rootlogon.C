{
  Int_t ierr = 0;

  char *clibs[] =
    {
      "$ROOTSYS/lib/libPhysics.so",
      "$ROOTSYS/lib/libRIO.so",
      "$ROOTSYS/lib/libHist.so",
      "$ROOTSYS/lib/libEG.so",
      "$ROOTSYS/lib/libTree.so",

      "./libTStarJetPico.so",
      0
    };

  Int_t i = 0;
  while (clibs[i++] != 0)
    {
      ierr = gSystem->Load(clibs[i-1]);
      if (ierr != 0)
	{
	  cerr <<  "Unable to load " << clibs[i-1] << endl;
	}
    }

}
