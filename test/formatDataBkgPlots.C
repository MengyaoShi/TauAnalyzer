//REGION A DATA 2D HISTOGRAMS ARE NOT BLINDED!!!  BEWARE!!!

void formatDataBkgPlots(const string& inputVersion, const string& outputVersion, 
			const string& versionNarrow, const string& MTBin, 
			const unsigned int firstBinToBlind, const bool doNoHPSIsoCut = false)
{
  //initial
  gROOT->Reset();

  //get CMSSW path
  const char* CMSSWPathCString = gSystem->Getenv("CMSSW_BASE");
  if (!CMSSWPathCString) {
    CMSSWPathCString = "";
    cout << "Error: environment variable CMSSW_BASE is not set.  ";
    cout << "Please run cmsenv from within your CMSSW project area.\n";
  }
  string CMSSWPathCPPString(CMSSWPathCString);


  //needed so vector<Color_t> and vector<Style_t> work

  //set up canvas and graph names and blinded bins for data
  vector<string> canvasNames1D;
  canvasNames1D.push_back("muHadMassCanvas");
  vector<string> graphNames1D;
  graphNames1D.push_back("muHadMass");


  //set up plot style options
  vector<string> legendHeaders19p7InvFb(canvasNames1D.size(), "Normalized to 19.7 fb^{-1}");
  vector<Color_t> colorsMCData;
  colorsMCData.push_back(kCyan + 2); //ZZ
  colorsMCData.push_back(kSpring + 4); //tt
  vector<Style_t> styles;
  styles.push_back(22); //ZZ
  styles.push_back(26); //tt
  vector<string> legendEntriesMCData;
  legendEntriesMCData.push_back("Data 19.7 fb^{-1}");
  legendEntriesMCData.push_back("ZZ");
  legendEntriesMCData.push_back("t#bar{t} + jets");
  const bool setLogY = true;
  const bool setLinY = false;
  const bool drawStack = true;
  const bool drawSame = false;
  const bool dataMC = true;
  const bool sigBkg = false;

  //best available weights according to Dropbox spreadsheet
  vector<float> weightsMCData(8, 1.0); //MC samples already properly weighted during hadding

  //space-saving constant definitions
  string user(gSystem->GetFromPipe("whoami").Data());
  const string analysisFilePath("/afs/cern.ch/work/m/" + user+"/public/data1/");
  const string fileExt(".root");
  const string tag19p7InvFb("_19p7fb-1");
  const string tag1("_normalizedTo1");

  //version tags
  const string outputVTag("_" + outputVersion);
  const string TTJetsVTag("_" + inputVersion);
  const string ZZVTag("_" + inputVersion);

  cout << "Begin hadding...\n";

  //"hadd" ttbar sample just to get the formatting of the 2D plots the same
  cout << "...ttbar\n";
  string TTJetsSuffix(TTJetsVTag + fileExt);
  string TTJetsIsoPrefix(analysisFilePath + "TTJets/analysis/muHadIsoAnalysis" + MTBin + 
			 "_TTJets");
  string TTJetsIsoHaddOutputFile(TTJetsIsoPrefix + "_hadd" + TTJetsSuffix);
  string TTJetsNonIsoPrefix(analysisFilePath + "TTJets/analysis/muHadNonIsoAnalysis" + MTBin + 
			    "_TTJets");
  string TTJetsNonIsoHaddOutputFile(TTJetsNonIsoPrefix + "_hadd" + TTJetsSuffix);
  string TTJetsAllPrefix(analysisFilePath + "TTJets/analysis/muHadAnalysis" + MTBin + "_TTJets");
  string TTJetsAllHaddOutputFile(TTJetsAllPrefix + "_hadd" + TTJetsSuffix);
  vector<string> TTJetsIsoHaddInputFiles;
  vector<string> TTJetsNonIsoHaddInputFiles;
  vector<string> TTJetsAllHaddInputFiles;
  stringstream TTJetsIsoName;
  TTJetsIsoName << TTJetsIsoPrefix << TTJetsSuffix;
  TTJetsIsoHaddInputFiles.push_back(TTJetsIsoName.str());
  stringstream TTJetsNonIsoName;
  TTJetsNonIsoName << TTJetsNonIsoPrefix << TTJetsSuffix;
  TTJetsNonIsoHaddInputFiles.push_back(TTJetsNonIsoName.str());
  stringstream TTJetsAllName;
  TTJetsAllName << TTJetsAllPrefix << TTJetsSuffix;
  TTJetsAllHaddInputFiles.push_back(TTJetsAllName.str());
  haddCanvases(TTJetsIsoHaddOutputFile, TTJetsIsoHaddInputFiles, 
	       vector<float>(1, 3.54800726562391), canvasNames1D, graphNames1D, 
	       canvasNames2D, graphNames2D, nullBlindLow, nullBlindHigh);
  haddCanvases(TTJetsNonIsoHaddOutputFile, TTJetsNonIsoHaddInputFiles, 
	       vector<float>(1, 3.54800726562391), canvasNames1D, graphNames1D, 
	       canvasNames2D, graphNames2D, nullBlindLow, nullBlindHigh);
  if (doNoHPSIsoCut) {
    haddCanvases(TTJetsAllHaddOutputFile, TTJetsAllHaddInputFiles, 
		 vector<float>(1, 3.54800726562391), canvasNames1D, graphNames1D, 
		 canvasNames2D, graphNames2D, nullBlindLow, nullBlindHigh);
  }



  //"hadd" ZZ sample just to get the formatting of the 2D plots the same
  cout << "...ZZ\n";
  string ZZSuffix(ZZVTag + fileExt);
  string ZZIsoPrefix(analysisFilePath + "ZZ/analysis/muHadIsoAnalysis" + MTBin + "_ZZ");
  string ZZIsoHaddOutputFile(ZZIsoPrefix + "_hadd" + ZZSuffix);
  string ZZNonIsoPrefix(analysisFilePath + "ZZ/analysis/muHadNonIsoAnalysis" + MTBin + "_ZZ");
  string ZZNonIsoHaddOutputFile(ZZNonIsoPrefix + "_hadd" + ZZSuffix);
  string ZZAllPrefix(analysisFilePath + "ZZ/analysis/muHadAnalysis" + MTBin + "_ZZ");
  string ZZAllHaddOutputFile(ZZAllPrefix + "_hadd" + ZZSuffix);
  vector<string> ZZIsoHaddInputFiles;
  vector<string> ZZNonIsoHaddInputFiles;
  vector<string> ZZAllHaddInputFiles;
  stringstream ZZIsoName;
  ZZIsoName << ZZIsoPrefix << ZZSuffix;
  ZZIsoHaddInputFiles.push_back(ZZIsoName.str());
  stringstream ZZNonIsoName;
  ZZNonIsoName << ZZNonIsoPrefix << ZZSuffix;
  ZZNonIsoHaddInputFiles.push_back(ZZNonIsoName.str());
  stringstream ZZAllName;
  ZZAllName << ZZAllPrefix << ZZSuffix;
  ZZAllHaddInputFiles.push_back(ZZAllName.str());
  haddCanvases(ZZIsoHaddOutputFile, ZZIsoHaddInputFiles, 
	       vector<float>(1, /*0.0377509625152821*/0.035488476), canvasNames1D, graphNames1D, 
	       canvasNames2D, graphNames2D, nullBlindLow, nullBlindHigh);
  haddCanvases(ZZNonIsoHaddOutputFile, ZZNonIsoHaddInputFiles, 
	       vector<float>(1, /*0.0377509625152821*/0.035488476), canvasNames1D, graphNames1D, 
	       canvasNames2D, graphNames2D, nullBlindLow, nullBlindHigh);
  if (doNoHPSIsoCut) {
    haddCanvases(ZZAllHaddOutputFile, ZZAllHaddInputFiles, 
		 vector<float>(1, /*0.0377509625152821*/0.035488476), canvasNames1D, graphNames1D, 
		 canvasNames2D, graphNames2D, nullBlindLow, nullBlindHigh);
  }

  string dataVsMCOutputFile(analysisFilePath + "results/dataVsMC_muHadNonIsoAnalysis" + MTBin + 
			    tag19p7InvFb + outputVTag + fileExt);
  vector<string> dataVsMCInputFiles;
  dataVsMCInputFiles.push_back(ZZNonIsoHaddOutputFile);
  dataVsMCInputFiles.push_back(TTJetsNonIsoHaddOutputFile);
  cout << "\nPlot data vs. MC normalized to data luminosity\n---\n";
  drawMultipleEfficiencyGraphsOn1Canvas(dataVsMCOutputFile, dataVsMCInputFiles, 
					canvasNames1D, graphNames1D, legendHeaders19p7InvFb, 
					colorsMCData, styles, legendEntriesMCData, 
					weightsMCData, setLogY, drawStack, dataMC);

}
